"""Rebuild typed US B1 control and bounded external sound-bank regions."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re
import tempfile

try:
    from scripts import audio_assets, audio_boundaries, sound_bank_codec, texture_build, rzip_pack
    from scripts.build_files import write_if_changed
except ModuleNotFoundError:
    import audio_assets
    import audio_boundaries
    import sound_bank_codec
    import texture_build
    import rzip_pack
    from build_files import write_if_changed

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def part_name(part):
    if part == 'control':
        return 'audio/bank17/sound_bank_control_rzip'
    if not isinstance(part, str) or not re.fullmatch(r'[0-9A-F]{8}', part):
        raise ValueError('invalid sound-bank part selector')
    return 'audio/bank17/sound-bank/regions/' + part


def input_directory(part):
    part_name(part)
    return Path('build/assets/sound-bank-build/us') / part


def external_partition(asset, regions):
    return sound_bank_codec.external_partition(asset, regions)


def reviewed_parts(root=ROOT):
    _, rom, _, family = audio_assets.load_profile_audio_assets('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        raise ValueError('US sound-bank ROM checksum mismatch')
    sound_bank_codec.verify_consumers(rom)
    regions = sound_bank_codec.typed_regions(*(asset.data for asset in family.assets[:3]))
    if len(regions['control']) != 1:
        raise ValueError('sound-bank control requires one complete typed region')
    control, external = family.assets[:2]
    raw = sound_bank_codec.encode_region(regions['control'][0])
    if raw != control.data:
        raise ValueError('sound-bank control reconstruction differs from original decoded bytes')
    start, end, splits = audio_boundaries.bank_layout(root / 'config/profiles/us.yaml')
    if (start, end) != (family.bank_start, family.bank_end):
        raise ValueError('sound-bank YAML range differs from reviewed ROM')
    extents = {name: (at, splits[i+1][0] if i+1 < len(splits) else end)
               for i, (at, name) in enumerate(splits)}
    if len(extents) != len(splits):
        raise ValueError('duplicate audio YAML names')
    partition = external_partition(external, regions)
    actual = [(at, extents[name][1], name) for at, name in splits
              if external.rom_start <= at < external.rom_end]
    if actual != partition:
        raise ValueError('external sound-bank YAML differs from typed and excluded ranges')
    selected = []
    for part, asset, records in [('control', control, regions['control'][0])] + [
            (f"{r['start']:08X}", external, r) for r in regions['external']]:
        begin = asset.rom_start if part == 'control' else asset.rom_start + records['start']
        finish = asset.rom_end if part == 'control' else asset.rom_start + records['end']
        if extents.get(part_name(part)) != (begin, finish):
            raise ValueError('sound-bank candidate YAML extent differs from native records')
        decoded = sound_bank_codec.encode_region(records)
        stored = rzip_pack.encode_rzip_chunk(decoded) if part == 'control' else decoded
        if stored != rom[begin:finish]:
            raise ValueError('sound-bank encoding differs from independent original storage')
        expected = {'schema_version': 1, 'profile': 'us', 'part': part, 'rom_sha1': ROM_SHA1,
                    'rom_start': begin, 'rom_end': finish, 'decoded_size': len(decoded),
                    'original_decoded_sha256': sha256(decoded), 'original_stored_sha256': sha256(stored),
                    'encoder': 'rzip-zlib9' if part == 'control' else 'native-records'}
        selected.append((expected, records))
    return rom, selected


def input_error(directory, expected, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      f"./conker audio-assets recover-sound-bank --part {expected['part']} "
                      'to back up this folder and restore reviewed ROM inputs.')


def input_files(expected, records):
    return {name: (json.dumps(value, indent=2) + '\n').encode()
            for name, value in [('manifest.json', expected), ('records.json', records)]}


def input_hashes(directory, expected):
    try:
        if json.loads((directory / 'manifest.json').read_text()) != expected:
            raise ValueError('sound-bank manifest differs from reviewed ROM contract')
        return {name: sha256((directory / name).read_bytes()) for name in ('manifest.json', 'records.json')}
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error


def packed_part(directory, expected):
    before = input_hashes(directory, expected)
    try:
        decoded = sound_bank_codec.encode_region(json.loads((directory / 'records.json').read_text()))
        if (len(decoded) != expected['decoded_size'] or sha256(decoded) != expected['original_decoded_sha256']):
            raise ValueError('sound-bank records no longer reconstruct original payload')
        if expected['encoder'] == 'rzip-zlib9':
            packed = rzip_pack.encode_rzip_chunk(decoded)
        elif expected['encoder'] == 'native-records':
            packed = decoded
        else:
            raise ValueError('unsupported sound-bank encoder')
        if len(packed) != expected['rom_end'] - expected['rom_start'] or sha256(packed) != expected['original_stored_sha256']:
            raise ValueError('sound-bank encoding differs from original stored bytes')
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('sound-bank inputs changed during packing')
    return packed, before


def recover_inputs(part, root=ROOT):
    part_name(part)
    _, selected = reviewed_parts(root)
    pair = next((pair for pair in selected if pair[0]['part'] == part), None)
    if pair is None:
        raise ValueError(f'sound-bank part {part} is not in the reviewed selection')
    expected, records = pair
    directory = root / input_directory(part)
    if directory.is_symlink() or (directory.exists() and not directory.is_dir()):
        raise ValueError(f'refusing recovery of a non-directory or symlink: {directory}')
    backup = None
    if directory.exists():
        backups = root / 'build/assets/sound-bank-build/recovery/us'
        backups.mkdir(parents=True, exist_ok=True)
        backup = Path(tempfile.mkdtemp(prefix=part+'-', dir=backups)) / 'inputs'
        directory.rename(backup)
    try:
        texture_build.publish_inputs(directory, input_files(expected, records))
    except Exception:
        if backup is not None and not directory.exists():
            backup.rename(directory)
        raise
    return {'part': part, 'input_directory': str(directory),
            'backup_directory': str(backup) if backup is not None else None}


def build_parts(root=ROOT):
    rom, selected = reviewed_parts(root)
    candidates = []
    for expected, records in selected:
        directory = root / input_directory(expected['part'])
        if not directory.exists():
            texture_build.publish_inputs(directory, input_files(expected, records))
        packed, hashes = packed_part(directory, expected)
        if packed != rom[expected['rom_start']:expected['rom_end']]:
            raise ValueError('sound-bank part differs from independent original ROM bytes')
        candidates.append((expected, directory, packed, hashes))
    for expected, directory, _, hashes in candidates:
        if input_hashes(directory, expected) != hashes:
            raise ValueError('sound-bank inputs changed during batch packing')
    proofs = []
    for expected, directory, packed, hashes in candidates:
        write_if_changed(root / 'build/us/sound-bank/parts' / (part_name(expected['part']) + '.bin'), packed)
        proofs.append({**expected, 'source_inputs': hashes, 'stored_sha256': sha256(packed), 'matches_original': True})
    result = {'part_count': len(proofs), 'stored_bytes': sum(len(p) for _, _, p, _ in candidates),
              'parts': proofs, 'verification': 'typed_records_and_independent_rom_bytes', 'matches_original': True}
    write_if_changed(root / 'build/us/sound-bank/batch.json', (json.dumps(result, indent=2) + '\n').encode())
    return result


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    commands.add_parser('build-parts')
    commands.add_parser('recover').add_argument('--part', required=True)
    args = parser.parse_args(argv)
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(args.part), indent=2))
        else:
            proof = build_parts()
            print(f"Verified {proof['part_count']} sound-bank parts: {proof['stored_bytes']} ROM bytes")
    except (ValueError, OSError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
