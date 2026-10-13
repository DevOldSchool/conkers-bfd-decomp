"""Rebuild complete MPEG frame ranges from editable quantized coefficients."""
from __future__ import annotations

from concurrent.futures import ProcessPoolExecutor
import hashlib
import tempfile
import json
from pathlib import Path

try:
    from scripts import asset_inputs, mp3_assets, mp3_bank, mp3_spectral_codec as codec
    from scripts import mp3_table_build, texture_build
    from scripts.build_files import write_if_changed, cached_sha256
    from scripts.build_jobs import job_count
except ModuleNotFoundError:
    import asset_inputs, mp3_assets, mp3_bank, mp3_spectral_codec as codec
    import mp3_table_build, texture_build
    from build_files import write_if_changed, cached_sha256
    from build_jobs import job_count

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = mp3_table_build.ROM_SHA1


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def part_name(index):
    return f'audio/mp3/streams/{index:04d}'


def input_directory(index):
    return Path(f'build/assets/mp3-spectral/us/{index:04d}')


def raw_relative_name(index):
    # Both paths are generated from the reviewed integer entry index, never JSON.
    return f'../../../mp3-bank/us/streams/{index:04d}.mp3'


def reviewed_streams(root=ROOT):
    _, rom, _, family = mp3_assets.load_profile_mp3_assets('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        raise ValueError('US spectral reconstruction ROM checksum mismatch')
    # Pin all four full consumers and prove the C codebooks against the original
    # external Huffman/lookup tables before interpreting any audio coefficients.
    checked, _, _ = mp3_table_build.reviewed_tables(root)
    if checked != rom:
        raise ValueError('MP3 decoder table reference differs from stream ROM')
    bank = mp3_bank.describe_bank(rom, family)
    expected_splits = [(bank['rom_start'], 'audio/mp3/index')] + sorted(
        (bank['rom_start'] + entry['offset'], 'audio/mp3/' + str(Path(entry['file']).with_suffix('')))
        for entry in bank['streams'] + bank['padding'])
    if mp3_bank.layout_bins(root / 'config/profiles/us.yaml') != expected_splits:
        raise ValueError('spectral stream YAML differs from original indexed storage')
    seed_sha = sha256((root / codec.SEED_SOURCE).read_bytes())
    selected = []
    for stream in family.streams:
        ranges, count, selected_count = codec.reviewed_ranges(stream.data)
        expected = {'schema_version': 1, 'profile': 'us', 'entry': stream.entry_index,
                    'rom_sha1': ROM_SHA1, 'rom_start': stream.rom_start, 'rom_end': stream.rom_end,
                    'original_sha256': sha256(stream.data), 'encoder': codec.FORMAT,
                    'seed_source_sha256': seed_sha, 'frame_count': count, 'selected_frames': selected_count,
                    'rom_ranges': [[stream.rom_start + start, stream.rom_start + end] for start, end in ranges]}
        selected.append((expected, stream.data))
    return rom, selected


def input_files(expected, records):
    # One complete semantic frame per line stays editable without multiplying
    # file size through per-coefficient indentation.
    source = '{"format":' + json.dumps(codec.FORMAT) + ',"frames":[\n'
    source += ',\n'.join(json.dumps(frame, separators=(',', ':')) for frame in records['frames'])
    source += '\n]}\n'
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'stream.json': source.encode()}


def input_error(directory, expected, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore the listed file or run '
                      f"./conker mp3-assets recover-spectral --entry {expected['entry']} "
                      'to back up and restore typed coefficients. Original MP3 files are never replaced.')


def input_hashes(directory, expected):
    try:
        hashes = asset_inputs.manifest_hashes(directory, expected, ('manifest.json', 'stream.json'), 'MPEG coefficients')
        raw = raw_relative_name(expected['entry'])
        hashes[raw] = sha256((directory / raw).read_bytes())
        if hashes[raw] != expected['original_sha256']:
            raise ValueError('original MP3 input changed; restore it before spectral reconstruction')
        return hashes
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error


def encoded_spans(records, expected, hashes, include_partial, cache_directory=None):
    """Reuse typed encoding only for identical sources, codec and output hashes."""
    def encode():
        return codec.encode_stream(records, include_partial=True) if include_partial else codec.encode_stream(records)
    if cache_directory is None:
        return encode()
    implementation = {p: cached_sha256(ROOT / 'scripts' / p) for p in
                      ('mp3_spectral_build.py', 'mp3_spectral_codec.py', 'mp3_table_codec.py',
                       'mp3_assets.py', 'build_files.py')}
    identity = {'sources': hashes, 'expected': expected, 'partial': include_partial,
                'implementation': implementation}
    key = sha256(json.dumps(identity, sort_keys=True).encode())
    path = cache_directory / (key + '.json')
    try:
        receipt = json.loads(path.read_text())
        payload = bytes.fromhex(receipt['payload'])
        if receipt['identity'] == identity and sha256(payload) == receipt['sha256']:
            spans, cursor = [], 0
            for start, size in receipt['spans']:
                if type(start) is not int or type(size) is not int or start < 0 or size <= 0:
                    raise ValueError('invalid cached spectral span')
                spans.append((start, payload[cursor:cursor + size])); cursor += size
            if cursor == len(payload):
                return spans
    except (OSError, ValueError, KeyError, TypeError):
        pass
    spans = encode()
    payload = b''.join(data for _, data in spans)
    receipt = {'identity': identity, 'spans': [[start, len(data)] for start, data in spans],
               'payload': payload.hex(), 'sha256': sha256(payload)}
    cache_directory.mkdir(parents=True, exist_ok=True)
    # Independent builders/report workers may publish the same deterministic key.
    with tempfile.NamedTemporaryFile(mode='w', dir=cache_directory, delete=False) as temporary:
        json.dump(receipt, temporary, separators=(',', ':'))
    Path(temporary.name).replace(path)
    return spans


def packed_stream(directory, expected, *, include_partial=False, cache_directory=None):
    before = input_hashes(directory, expected)
    try:
        records = json.loads((directory / 'stream.json').read_text())
        spans = encoded_spans(records, expected, before, include_partial, cache_directory)
        if len(records['frames']) != expected['frame_count']:
            raise ValueError('MPEG frame count differs from original stream')
        ranges = [[expected['rom_start'] + start, expected['rom_start'] + start + len(data)] for start, data in spans]
        original = (directory / raw_relative_name(expected['entry'])).read_bytes()
        wanted_ranges = expected['rom_ranges']
        if include_partial:
            old_ranges, count, selected = codec.reviewed_ranges(original)
            if ([[expected['rom_start'] + a, expected['rom_start'] + z] for a, z in old_ranges] != wanted_ranges
                    or count != expected['frame_count'] or selected != expected['selected_frames']):
                raise ValueError('MPEG original full-frame contract changed')
            extra_ranges, _, _ = codec.reviewed_ranges(original, include_partial=True)
            wanted_ranges = [[expected['rom_start'] + a, expected['rom_start'] + z] for a, z in extra_ranges]
        if ranges != wanted_ranges:
            raise ValueError('MPEG reconstructed ranges differ from reviewed physical frames')
        packed = bytearray(original)
        if len(packed) != expected['rom_end'] - expected['rom_start']:
            raise ValueError('original MP3 input extent changed')
        # Only excluded cue/tail/gap bytes come from this original backing.
        for start, payload in spans:
            packed[start:start + len(payload)] = payload
        if sha256(packed) != expected['original_sha256']:
            raise ValueError('MPEG coefficients no longer reconstruct original stream bytes')
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('MPEG inputs changed during packing')
    return bytes(packed), spans, before


def recover_inputs(entry, root=ROOT):
    _, selected = reviewed_streams(root)
    pair = next((pair for pair in selected if pair[0]['entry'] == entry), None)
    if pair is None:
        raise ValueError('MP3 entry is not in the reviewed stream inventory')
    expected, original = pair
    records = codec.decode_stream(original)
    backup = asset_inputs.recover_directory(root / input_directory(entry),
        root / 'build/assets/mp3-spectral/recovery/us', f'{entry:04d}-', input_files(expected, records))
    return {'entry': entry, 'input_directory': str(root / input_directory(entry)), 'backup_directory': backup}


def prepare_candidate(task):
    root, expected, original = task
    directory = root / input_directory(expected['entry'])
    if not directory.exists():
        records = codec.decode_stream(original)
        texture_build.publish_inputs(directory, input_files(expected, records))
    packed, spans, hashes = packed_stream(directory, expected, include_partial=True,
                                          cache_directory=root / 'build/us/mp3-spectral/cache')
    if packed != original:
        raise ValueError('MPEG candidate differs from independent original stream')
    return expected, directory, packed, hashes


def build_parts(root=ROOT, entries=None):
    _, selected = reviewed_streams(root)
    if entries is not None:
        requested = set(entries)
        if not requested <= {e['entry'] for e, _ in selected}:
            raise ValueError('requested MP3 entry is not in the reviewed inventory')
        selected = [(e, raw) for e, raw in selected if e['entry'] in requested]
    # Initialize the established raw inputs only through their existing builder;
    # it preserves existing files. These inputs back uncredited holes only.
    mp3_bank.build_bank(root / 'build/assets/mp3-bank/us', root / 'build/us/audio/asset_bank_16.bin')
    with ProcessPoolExecutor(max_workers=job_count()) as workers:
        candidates = list(workers.map(prepare_candidate, ((root, e, raw) for e, raw in selected)))
    asset_inputs.check_batch_sources(candidates, input_hashes, 'MPEG spectral')
    proofs = []
    for expected, directory, packed, hashes in candidates:
        write_if_changed(root / 'build/us/mp3-spectral/parts' / (part_name(expected['entry']) + '.bin'), packed)
        ranges, _, _ = codec.reviewed_ranges(packed, include_partial=True)
        physical = [[expected['rom_start'] + a, expected['rom_start'] + z] for a, z in ranges]
        proofs.append({**expected, 'rom_ranges': physical, 'source_inputs': hashes, 'matches_original': True,
                       'reconstructed_bytes': sum(end - start for start, end in physical)})
    result = {'stream_count': len(proofs), 'reconstructed_bytes': sum(p['reconstructed_bytes'] for p in proofs),
              'verification': 'native_coefficients_and_linkable_original_streams', 'streams': proofs}
    # Focused runs have a distinct receipt so they cannot masquerade as a batch.
    receipt = 'batch.json' if entries is None else 'selected-' + '-'.join(str(i) for i in sorted(set(entries))) + '.json'
    write_if_changed(root / 'build/us/mp3-spectral' / receipt, (json.dumps(result, indent=2) + '\n').encode())
    return result


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    commands.add_parser('build-parts').add_argument('--entry', type=int, action='append')
    commands.add_parser('recover').add_argument('--entry', type=int, required=True)
    args = parser.parse_args(argv)
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(args.entry), indent=2))
        else:
            proof = build_parts(entries=args.entry)
            print(f"Verified {proof['stream_count']} coefficient-built MP3 streams: "
                  f"{proof['reconstructed_bytes']} reconstructed ROM bytes; opaque ranges excluded")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
