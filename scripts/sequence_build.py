"""Rebuild reviewed US compact sequences from editable native event records."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import tempfile

try:
    from scripts import audio_assets, audio_boundaries, sequence_codec, texture_build
    from scripts.build_files import write_if_changed
except ModuleNotFoundError:
    import audio_assets
    import audio_boundaries
    import sequence_codec
    import texture_build
    from build_files import write_if_changed

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def part_name(index):
    return f'audio/bank17/sequences/{index:04d}'


def input_directory(index):
    return Path(f'build/assets/sequence-build/us/{index:04d}')


def reviewed_sequences(root=ROOT):
    _, rom, _, family = audio_assets.load_profile_audio_assets('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        raise ValueError('US sequence ROM checksum mismatch')
    sequence_codec.verify_consumers(rom)
    bank_start, bank_end, splits = audio_boundaries.bank_layout(root / 'config/profiles/us.yaml')
    if (bank_start, bank_end) != (family.bank_start, family.bank_end):
        raise ValueError('sequence bank YAML range differs from reviewed ROM')
    extents = {name: (start, splits[i + 1][0] if i + 1 < len(splits) else bank_end)
               for i, (start, name) in enumerate(splits)}
    if len(extents) != len(splits):
        raise ValueError('duplicate audio YAML names')
    asset = family.assets[3]
    selected = []
    for sequence in family.sequences:
        start = asset.rom_start + sequence.offset
        end = start + len(sequence.data)
        if extents.get(part_name(sequence.index)) != (start, end):
            raise ValueError('sequence YAML extent differs from reviewed descriptor')
        records = sequence_codec.parse_records(sequence.data)
        if sequence_codec.encode_records(records) != sequence.data:
            raise ValueError('sequence events fail independent ROM comparison')
        expected = {'schema_version': 1, 'profile': 'us', 'entry': sequence.index,
                    'rom_sha1': ROM_SHA1, 'rom_start': start, 'rom_end': end,
                    'original_sha256': sha256(sequence.data),
                    'encoder': 'conker-compact-sequence-v1'}
        selected.append((expected, records))
    names = {name for _, name in splits if name.startswith('audio/bank17/sequences/')
             and not name.startswith('audio/bank17/sequences/padding/') and name != 'audio/bank17/sequences/index'}
    if names != {part_name(e['entry']) for e, _ in selected}:
        raise ValueError('sequence YAML selection differs from reviewed descriptors')
    return rom, selected


def input_error(directory, expected, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      f"./conker audio-assets recover-sequence --entry {expected['entry']} "
                      'to back up this folder and restore reviewed ROM inputs.')


def input_files(expected, records):
    return {name: (json.dumps(value, indent=2) + '\n').encode()
            for name, value in [('manifest.json', expected), ('sequence.json', records)]}


def input_hashes(directory, expected):
    try:
        if json.loads((directory / 'manifest.json').read_text()) != expected:
            raise ValueError('sequence manifest differs from reviewed ROM contract')
        return {name: sha256((directory / name).read_bytes()) for name in ('manifest.json', 'sequence.json')}
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error


def packed_sequence(directory, expected):
    before = input_hashes(directory, expected)
    try:
        payload = sequence_codec.encode_records(json.loads((directory / 'sequence.json').read_text()))
        if (len(payload) != expected['rom_end'] - expected['rom_start']
                or sha256(payload) != expected['original_sha256']):
            raise ValueError('sequence events no longer reconstruct original payload')
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('sequence inputs changed during packing')
    return payload, before


def recover_inputs(entry, root=ROOT):
    _, selected = reviewed_sequences(root)
    pair = next((pair for pair in selected if pair[0]['entry'] == entry), None)
    if pair is None:
        raise ValueError(f'sequence {entry} is not in the reviewed selection')
    expected, records = pair
    directory = root / input_directory(entry)
    if directory.is_symlink() or (directory.exists() and not directory.is_dir()):
        raise ValueError(f'refusing recovery of a non-directory or symlink: {directory}')
    backup = None
    if directory.exists():
        backups = root / 'build/assets/sequence-build/recovery/us'
        backups.mkdir(parents=True, exist_ok=True)
        backup = Path(tempfile.mkdtemp(prefix=f'{entry:04d}-', dir=backups)) / 'inputs'
        directory.rename(backup)
    try:
        texture_build.publish_inputs(directory, input_files(expected, records))
    except Exception:
        if backup is not None and not directory.exists():
            backup.rename(directory)
        raise
    return {'entry': entry, 'input_directory': str(directory),
            'backup_directory': str(backup) if backup is not None else None}


def build_parts(root=ROOT):
    rom, selected = reviewed_sequences(root)
    candidates = []
    for expected, records in selected:
        directory = root / input_directory(expected['entry'])
        if not directory.exists():
            texture_build.publish_inputs(directory, input_files(expected, records))
        packed, hashes = packed_sequence(directory, expected)
        if packed != rom[expected['rom_start']:expected['rom_end']]:
            raise ValueError('sequence differs from independent original ROM bytes')
        candidates.append((expected, directory, packed, hashes))
    for expected, directory, _, hashes in candidates:
        if input_hashes(directory, expected) != hashes:
            raise ValueError('sequence inputs changed during batch packing')
    proofs = []
    for expected, directory, packed, hashes in candidates:
        write_if_changed(root / 'build/us/sequences/parts' / (part_name(expected['entry']) + '.bin'), packed)
        proofs.append({**expected, 'source_inputs': hashes, 'stored_sha256': sha256(packed),
                       'matches_original': True})
    result = {'sequence_count': len(proofs), 'stored_bytes': sum(len(p) for _, _, p, _ in candidates),
              'sequences': proofs, 'verification': 'typed_events_and_independent_rom_bytes', 'matches_original': True}
    write_if_changed(root / 'build/us/sequences/batch.json', (json.dumps(result, indent=2) + '\n').encode())
    return result


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    commands.add_parser('build-parts')
    commands.add_parser('recover').add_argument('--entry', required=True, type=int)
    args = parser.parse_args(argv)
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(args.entry), indent=2))
        else:
            proof = build_parts()
            print(f"Verified {proof['sequence_count']} compact sequences: {proof['stored_bytes']} ROM bytes")
    except (ValueError, OSError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
