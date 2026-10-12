"""Rebuild reviewed US MP3 decoder tables from editable Huffman seed records."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

try:
    from scripts import asset_inputs, audio_boundaries, model_assets, mp3_assets, mp3_table_codec, rzip_archive, texture_build
    from scripts.build_files import write_if_changed
except ModuleNotFoundError:
    import asset_inputs, audio_boundaries, model_assets, mp3_assets, mp3_table_codec, rzip_archive, texture_build
    from build_files import write_if_changed

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
SEED_SOURCE = Path('lib/libultrare/src/libultrare/mp3/decoder.c')
INPUT_DIRECTORY = Path('build/assets/mp3-tables/us')
NAMES = ('mp3_huffman_offsets', 'mp3_lookup', 'mp3_huffman')


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def part_name(name):
    return 'audio/bank17/' + name


def reviewed_tables(root=ROOT):
    _, rom, _, family = mp3_assets.load_profile_mp3_assets('us', root / 'roms/baserom.us.z64')
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        raise ValueError('US MP3 table ROM checksum mismatch')
    _, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    game = rzip_archive.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    mp3_table_codec.verify_consumers(game.code)
    start, end, splits = audio_boundaries.bank_layout(root / 'config/profiles/us.yaml')
    if (start, end) != (family.decoder_bank_start, family.decoder_bank_end):
        raise ValueError('MP3 decoder bank YAML range differs from reviewed ROM')
    extents = {name: (address, splits[i + 1][0] if i + 1 < len(splits) else end)
               for i, (address, name) in enumerate(splits)}
    if len(extents) != len(splits):
        raise ValueError('duplicate audio YAML names')
    source = (root / SEED_SOURCE).read_bytes()
    records = mp3_table_codec.seed_records(source.decode())
    packed = mp3_table_codec.encode_tables(records)
    parts = []
    for name, asset in zip(NAMES, (family.offsets, family.lookup, family.huffman)):
        if (asset.compressed or extents.get(part_name(name)) != (asset.rom_start, asset.rom_end)
                or packed[name] != asset.data):
            raise ValueError(f'{name} seeds or YAML differ from original MP3 table')
        parts.append({'name': name, 'entry': asset.entry_index, 'rom_start': asset.rom_start,
                      'rom_end': asset.rom_end, 'original_sha256': sha256(asset.data)})
    expected = {'schema_version': 1, 'profile': 'us', 'rom_sha1': ROM_SHA1,
                'encoder': mp3_table_codec.FORMAT, 'seed_source': str(SEED_SOURCE),
                'seed_source_sha256': sha256(source), 'parts': parts}
    return rom, expected, records


def input_files(expected, records):
    return {name: (json.dumps(value, indent=2) + '\n').encode()
            for name, value in [('manifest.json', expected), ('tables.json', records)]}


def input_error(directory, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      './conker mp3-assets recover-tables to back up this folder and restore reviewed C seeds.')


def input_hashes(directory, expected):
    try:
        return asset_inputs.manifest_hashes(directory, expected, ('manifest.json', 'tables.json'), 'MP3 tables')
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error


def packed_tables(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = mp3_table_codec.encode_tables(json.loads((directory / 'tables.json').read_text()))
        for part in expected['parts']:
            payload = packed[part['name']]
            if (len(payload) != part['rom_end'] - part['rom_start']
                    or sha256(payload) != part['original_sha256']):
                raise ValueError('Huffman seeds no longer reconstruct original tables')
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('MP3 table inputs changed during packing')
    return packed, before


def recover_inputs(root=ROOT):
    _, expected, records = reviewed_tables(root)
    backup = asset_inputs.recover_directory(root / INPUT_DIRECTORY, root / 'build/assets/mp3-tables/recovery',
                                           'us-', input_files(expected, records))
    return {'input_directory': str(root / INPUT_DIRECTORY), 'backup_directory': backup}


def build_parts(root=ROOT):
    rom, expected, records = reviewed_tables(root)
    directory = root / INPUT_DIRECTORY
    if not directory.exists():
        texture_build.publish_inputs(directory, input_files(expected, records))
    packed, hashes = packed_tables(directory, expected)
    for part in expected['parts']:
        if packed[part['name']] != rom[part['rom_start']:part['rom_end']]:
            raise ValueError('MP3 table differs from independent original ROM bytes')
    if input_hashes(directory, expected) != hashes:
        raise ValueError('MP3 table inputs changed during batch packing')
    for name, payload in packed.items():
        write_if_changed(root / 'build/us/mp3-tables/parts' / (part_name(name) + '.bin'), payload)
    result = {**expected, 'source_inputs': hashes, 'stored_bytes': sum(map(len, packed.values())),
              'verification': 'typed_c_seeds_and_independent_rom_bytes', 'matches_original': True}
    write_if_changed(root / 'build/us/mp3-tables/batch.json', (json.dumps(result, indent=2) + '\n').encode())
    return result


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('build-parts', 'recover'))
    args = parser.parse_args(argv)
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(), indent=2))
        else:
            result = build_parts()
            print(f"Verified {len(result['parts'])} MP3 decoder tables: {result['stored_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
