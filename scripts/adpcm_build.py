"""Rebuild native ADPCM frame regions from PCM16 WAVs and semantic encoding plans."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import tempfile
import struct

try:
    from scripts import adpcm_codec, adpcm_layout, audio_assets, audio_boundaries, sound_bank_codec, texture_build
    from scripts.build_files import write_if_changed
except ModuleNotFoundError:
    import adpcm_codec
    import adpcm_layout
    import audio_assets
    import audio_boundaries
    import sound_bank_codec
    import texture_build
    from build_files import write_if_changed

ROOT = Path(__file__).resolve().parent.parent
SOURCE_NAMES = ('manifest.json', 'encoding.json', 'sample.wav')


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def plan_digest(plan):
    return sha256(json.dumps(plan, sort_keys=True, separators=(',', ':')).encode())


def input_directory(sample):
    adpcm_layout.part_name(sample, 0)
    return Path('build/assets/adpcm-build/us') / f'{sample:04d}'


def reviewed_samples(root=ROOT):
    _, rom, _, family = audio_assets.load_profile_audio_assets('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() != adpcm_layout.ROM_SHA1:
        raise ValueError('US ADPCM ROM checksum mismatch')
    sound_bank_codec.verify_consumers(rom)
    graph = family.sound_graph.manifest
    asset = family.assets[2]
    contract = adpcm_layout.load_contract(root)
    partition = adpcm_layout.partition(asset, graph['samples'], contract)
    start, end, splits = audio_boundaries.bank_layout(root / 'config/profiles/us.yaml')
    if (start, end) != (family.bank_start, family.bank_end):
        raise ValueError('ADPCM YAML bank extent differs from reviewed ROM')
    extents = {name: (at, splits[i + 1][0] if i + 1 < len(splits) else end)
               for i, (at, name) in enumerate(splits)}
    actual = [(at, extents[name][1], name) for at, name in splits
              if asset.rom_start <= at < asset.rom_end]
    if len(extents) != len(splits) or actual != partition:
        raise ValueError('ADPCM YAML differs from reviewed complete-frame partition')
    runs = adpcm_layout.selected_runs(graph['samples'], contract)
    selected = []
    for sample, regions in zip(graph['samples'], runs, strict=True):
        if not regions:
            continue
        index = sample['index']
        wave = graph['wavetables'][sample['wavetable_indices'][0]]
        book = graph['adpcm_books'][wave['book_index']]
        begin = asset.rom_start + int(sample['base'], 16)
        raw = rom[begin:begin + sample['runtime_payload_length']]
        plan = adpcm_codec.frame_plan(raw, book['coefficients'], book['order'], book['predictor_count'])
        pcm = audio_assets.decode_n64_vadpcm(raw, book['coefficients'], book['order'], book['predictor_count'])
        wav = adpcm_codec.source_wav(pcm, family.sound_bank.sample_rate)
        parts = [{'first_frame': first, 'end_frame': stop, 'rom_start': begin + first * 9,
                  'rom_end': begin + stop * 9, 'original_stored_sha256': sha256(raw[first * 9:stop * 9])}
                 for first, stop in regions]
        expected = {'schema_version': 1, 'profile': 'us', 'sample': index,
                    'rom_sha1': adpcm_layout.ROM_SHA1, 'rom_start': begin,
                    'runtime_bytes': len(raw), 'pcm_frames': len(pcm),
                    'sample_rate': family.sound_bank.sample_rate,
                    'context_wavetable': wave['index'], 'context_book': wave['book_index'],
                    'original_pcm_sha256': sha256(struct.pack(f'<{len(pcm)}h', *pcm)),
                    'native_plan_sha256': plan_digest(plan), 'parts': parts}
        selected.append((expected, plan, wav))
    return rom, selected


def input_error(directory, expected, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      f"./conker audio-assets recover-adpcm --sample {expected['sample']} "
                      'to back up this folder and restore reviewed ROM inputs.')


def input_files(expected, plan, wav):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'encoding.json': (json.dumps(plan, indent=2) + '\n').encode(), 'sample.wav': wav}


def input_hashes(directory, expected):
    try:
        if json.loads((directory / 'manifest.json').read_text()) != expected:
            raise ValueError('ADPCM manifest differs from reviewed native contract')
        return {name: sha256((directory / name).read_bytes()) for name in SOURCE_NAMES}
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error


def packed_sample(directory, expected):
    before = input_hashes(directory, expected)
    try:
        plan = json.loads((directory / 'encoding.json').read_text())
        adpcm_codec.validate_plan(plan)
        if plan_digest(plan) != expected['native_plan_sha256']:
            raise ValueError('ADPCM frame parameters or native book context changed')
        pcm = adpcm_codec.read_wav((directory / 'sample.wav').read_bytes(),
                                   expected['sample_rate'], expected['pcm_frames'])
        # Check the entire PCM context, including ambiguous frames not published
        # as candidates. Never silently ignore an edit outside a credited region.
        if sha256(struct.pack(f'<{len(pcm)}h', *pcm)) != expected['original_pcm_sha256']:
            raise ValueError('ADPCM source PCM differs from reviewed decoded samples')
        encoded = adpcm_codec.encode_pcm(pcm, plan)
        if len(encoded) != expected['runtime_bytes']:
            raise ValueError('ADPCM encoder produced an incorrect sample extent')
        parts = []
        for part in expected['parts']:
            raw = encoded[part['first_frame'] * 9:part['end_frame'] * 9]
            if (len(raw) != part['rom_end'] - part['rom_start']
                    or sha256(raw) != part['original_stored_sha256']):
                raise ValueError('ADPCM encoding differs from original complete-frame region')
            parts.append((part, raw))
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('ADPCM inputs changed during encoding')
    return parts, before


def recover_inputs(sample, root=ROOT):
    input_directory(sample)
    _, selected = reviewed_samples(root)
    row = next((row for row in selected if row[0]['sample'] == sample), None)
    if row is None:
        raise ValueError(f'ADPCM sample {sample} is not in the reviewed selection')
    expected, plan, wav = row
    directory = root / input_directory(sample)
    if directory.is_symlink() or (directory.exists() and not directory.is_dir()):
        raise ValueError(f'refusing recovery of a non-directory or symlink: {directory}')
    backup = None
    if directory.exists():
        backups = root / 'build/assets/adpcm-build/recovery/us'
        backups.mkdir(parents=True, exist_ok=True)
        backup = Path(tempfile.mkdtemp(prefix=f'{sample:04d}-', dir=backups)) / 'inputs'
        directory.rename(backup)
    try:
        texture_build.publish_inputs(directory, input_files(expected, plan, wav))
    except Exception:
        if backup is not None and not directory.exists():
            backup.rename(directory)
        raise
    return {'sample': sample, 'input_directory': str(directory),
            'backup_directory': str(backup) if backup is not None else None}


def build_parts(root=ROOT):
    rom, selected = reviewed_samples(root)
    candidates = []
    for expected, plan, wav in selected:
        directory = root / input_directory(expected['sample'])
        if not directory.exists():
            texture_build.publish_inputs(directory, input_files(expected, plan, wav))
        parts, hashes = packed_sample(directory, expected)
        for part, raw in parts:
            if raw != rom[part['rom_start']:part['rom_end']]:
                raise ValueError('ADPCM part differs from independent original ROM bytes')
        candidates.append((expected, directory, parts, hashes))
    for expected, directory, _, hashes in candidates:
        if input_hashes(directory, expected) != hashes:
            raise ValueError('ADPCM inputs changed during batch encoding')
    proofs = []
    for expected, _, parts, hashes in candidates:
        for part, raw in parts:
            name = adpcm_layout.part_name(expected['sample'], part['first_frame'])
            write_if_changed(root / 'build/us/adpcm/parts' / (name + '.bin'), raw)
            proofs.append({**part, 'sample': expected['sample'], 'source_inputs': hashes,
                           'stored_sha256': sha256(raw), 'matches_original': True})
    result = {'sample_count': len(selected), 'part_count': len(proofs),
              'stored_bytes': sum(p['rom_end'] - p['rom_start'] for p in proofs),
              'parts': proofs, 'verification': 'pcm16_and_native_frame_plan', 'matches_original': True}
    write_if_changed(root / 'build/us/adpcm/batch.json', (json.dumps(result, indent=2) + '\n').encode())
    return result


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    commands.add_parser('build-parts')
    commands.add_parser('recover').add_argument('--sample', required=True, type=int)
    args = parser.parse_args(argv)
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(args.sample), indent=2))
        else:
            proof = build_parts()
            print(f"Verified {proof['part_count']} ADPCM parts: {proof['stored_bytes']} ROM bytes")
    except (ValueError, OSError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
