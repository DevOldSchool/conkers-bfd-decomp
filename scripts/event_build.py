"""Reconstruct the complete US event bank from instructions and constant strings."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct

try:
    from scripts import asset_inputs, model_assets, model_event_activation, event_codec, rzip_archive, texture_build
    from scripts.build_files import write_if_changed
    from scripts.model_character_alpha import checked_spans
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_inputs, model_assets, model_event_activation, event_codec, rzip_archive, texture_build
    from build_files import write_if_changed
    from model_character_alpha import checked_spans
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
INPUT_DIRECTORY = Path('build/assets/event-build/us')
PART_NAME = 'asset_bank_14'
STRING_CALL_STUBS = ((0x1509DD20, 16, 'a1202dec3ebeae33c0a71fe2f27dd1ebd096193c'),
                     (0x1509DD30, 16, 'a1202dec3ebeae33c0a71fe2f27dd1ebd096193c'))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def verify_consumers(game, layout):
    code = checked_spans(game.code, layout['game_vram'], model_event_activation.CODE_SPANS + STRING_CALL_STUBS)
    tables = checked_spans(game.data, layout['game_data_vram'], model_event_activation.DATA_SPANS)
    offset = 0x80087358 - layout['game_data_vram']
    if game.data[offset:offset + len(event_codec.ARITY)] != bytes(n + 1 for n in event_codec.ARITY):
        raise ValueError('event instruction arities differ from native interpreter table')
    return {'code': code, 'tables': tables}


def reviewed_bank(root=ROOT):
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.normalize_rom(path.read_bytes())
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        raise ValueError('US event ROM checksum mismatch')
    game = rzip_archive.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    consumers = verify_consumers(game, layout)
    bank = next(b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table']) if b.index == 0x14)
    if bank.flags:
        raise ValueError('event bank has unsupported outer flags')
    slots = struct.unpack_from('>I', rom, bank.start)[0] // 8
    if slots != 204:
        raise ValueError('event bank slot count differs from reviewed inventory')
    records = {'format': event_codec.FORMAT, 'programs': [None] * slots}
    programs = []
    for entry in rzip_archive.parse_asset_entries(rom, bank):
        if not entry.compressed or entry.type_flags & ~0x90:
            raise ValueError('event program has unsupported entry flags')
        raw = rom[entry.start:entry.end]
        decoded = rzip_archive.decode_rzip_chunk(raw)
        if decoded.consumed != len(raw):
            raise ValueError('event RZIP entry has unexplained trailing bytes')
        program = event_codec.decode_program(decoded.data)
        records['programs'][entry.index] = program
        programs.append({'entry': entry.index, 'rom_start': entry.start, 'rom_end': entry.end,
                         'decoded_bytes': len(decoded.data), 'decoded_sha256': sha256(decoded.data),
                         'instruction_count': len(program['instructions']), 'string_count': len(program['strings'])})
    if [i for i, p in enumerate(records['programs']) if p is None] != [106]:
        raise ValueError('event bank populated slots differ from reviewed inventory')
    packed = event_codec.encode_bank(records)
    if packed != rom[bank.start:bank.end]:
        raise ValueError('event instructions fail fresh whole-bank ROM reconstruction')
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    indices = [i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == PART_NAME]
    if len(indices) != 1 or indices[0] + 1 >= len(segments):
        raise ValueError('missing or duplicate event YAML segment')
    segment, following = segments[indices[0]:indices[0] + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    if (segment.get('type') != 'bin' or segment.get('start') != bank.start or end != bank.end
            or segment.get('align') != 1 or segment.get('subalign') != 1):
        raise ValueError('event YAML extent differs from the reviewed ROM bank')
    expected = {'schema_version': 1, 'profile': 'us', 'bank': 0x14, 'rom_sha1': ROM_SHA1,
                'rom_start': bank.start, 'rom_end': bank.end, 'original_sha256': sha256(packed),
                'format': event_codec.FORMAT, 'encoder': {'implementation': 'zlib', 'level': 6, 'wbits': -15},
                'programs': programs, 'consumers': consumers}
    return rom, expected, records


def input_files(expected, records):
    return {name: (json.dumps(value, indent=2) + '\n').encode()
            for name, value in [('manifest.json', expected), ('programs.json', records)]}


def input_error(directory, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      './conker event-assets recover to back up this folder and restore reviewed programs.')


def input_hashes(directory, expected):
    try:
        return asset_inputs.manifest_hashes(directory, expected, ('manifest.json', 'programs.json'), 'event bank')
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error


def packed_bank(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = event_codec.encode_bank(json.loads((directory / 'programs.json').read_text()))
        if len(packed) != expected['rom_end'] - expected['rom_start'] or sha256(packed) != expected['original_sha256']:
            raise ValueError('event instructions no longer reconstruct original bank')
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('event inputs changed during packing')
    return packed, before


def recover_inputs(root=ROOT):
    _, expected, records = reviewed_bank(root)
    backup = asset_inputs.recover_directory(root / INPUT_DIRECTORY, root / 'build/assets/event-build/recovery',
                                           'us-', input_files(expected, records))
    return {'input_directory': str(root / INPUT_DIRECTORY), 'backup_directory': backup}


def build_parts(root=ROOT):
    rom, expected, records = reviewed_bank(root)
    directory = root / INPUT_DIRECTORY
    if not directory.exists():
        texture_build.publish_inputs(directory, input_files(expected, records))
    packed, hashes = packed_bank(directory, expected)
    if packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('event bank differs from independent original ROM bytes')
    if input_hashes(directory, expected) != hashes:
        raise ValueError('event inputs changed during batch packing')
    write_if_changed(root / 'build/us/events/parts' / (PART_NAME + '.bin'), packed)
    proof = {**expected, 'source_inputs': hashes, 'stored_bytes': len(packed),
             'verification': 'typed_instructions_strings_fresh_compression_and_independent_rom', 'matches_original': True}
    write_if_changed(root / 'build/us/events/batch.json', (json.dumps(proof, indent=2) + '\n').encode())
    return proof


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('build', 'recover'))
    args = parser.parse_args(argv)
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(), indent=2))
        else:
            proof = build_parts()
            print(f"Verified whole event bank: {proof['stored_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
