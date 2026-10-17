"""Reconstruct the US script bank from tracks, bindings, commands and text."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct

try:
    from scripts import asset_inputs, model_assets, script_codec, rzip_archive, texture_build
    from scripts.build_files import write_if_changed
    from scripts import asset_receipts
    from scripts.model_character_alpha import checked_spans
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_inputs, model_assets, script_codec, rzip_archive, texture_build
    from build_files import write_if_changed
    import asset_receipts
    from model_character_alpha import checked_spans
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
INPUT_DIRECTORY = Path('build/assets/script-build/us')
PART_NAME = 'asset_bank_06'
CODE_SPANS = (
    (0x1501CE54, 420, '72c5d711393c3def29bbc25c8acd8b455e33282b'),
    (0x1501D1D4, 132, 'a956c60b89ac78dc93a1b0879259c2749cf59fec'),
    (0x1501D348, 1892, '438ba4bb6e8349c0e0e649dadfad11df5e4c9d25'),
    (0x1501E73C, 224, 'dc0ffcd977a3ef1507d00d35424cf23602aa243c'),
    (0x1501EC38, 2804, '4347699857882b234fa82b977564c68add6800d1'),
    (0x1501F72C, 1376, '9e2245bce04874de8c8e66c9128f3fb49c65b898'),
    (0x1501FC8C, 476, '3121f3c020de77610d62290975de63504cd5d668'),
    (0x1501FE68, 384, 'a9594b41ac6a07d83dc66a4c3bc4a871d80be979'),
    (0x1501FFE8, 928, '7533806e953fc13f48436f49dc546c43106b3ecd'),
    (0x15020388, 1264, '9c7edcf3feb3a08d50ab6d0371ad90fc6a9ba9b7'),
    (0x15020878, 1612, '74dca67cdfe49f5d6399e2c41cbe43b5089ea70d'),
    (0x15020EC4, 2248, 'e23a788f95a2609d596b5e23138ae2844c9963ae'),
    (0x1502178C, 1580, '84644587ba542fe85361eafb473a4a48e8d74b53'),
    (0x15021DB8, 620, '50e425861487dc30a81406e6d1df78ba66ed49cf'),
    (0x15022024, 364, '5d1e17adcae1e0a8b0e8ce0e7b57ad0a9aa763fc'),
    (0x150222E0, 184, 'f6c6c381ad9718cd2c2b7d0d904468e91af25a44'),
    (0x15022398, 400, '57111be545a15f9f9d05f2ef0a339b9d8fd19a5a'),
    (0x15022528, 280, '3f574631f5cee2361abafe8eed2c14fe1bde9659'),
    (0x150226BC, 152, '0425cd163b00d123fe5ecf083baef7fa805fcf8a'),
    (0x150229E4, 292, 'c27a56776ab8fac7449acb03e43bd8f46e98a960'),
    (0x15022B08, 156, '47be7754e3674c3de3ef6049455111e9ad16e3a3'),
    (0x15022BA4, 1728, 'fc2e8ef377bb8dc85be1ab2e931376f4ef579ba1'),
    (0x15023264, 344, 'b1084c213dbcf4798fac4b6c247b48f00e5e91cc'),
    (0x15023870, 96, 'a2e75fe1ce4d8da79bd3e9368ad912bb03c47148'),
    (0x15023BB0, 560, '078b56fd1dbc11555e080e7b44e46d8304fc0e3d'),
    (0x150242F8, 788, '4b85a67da8029cd004c5fe4c8ccf7fc484171718'),
    (0x1502460C, 8128, '363af55b580310f7cfa3dee99c50a0065274dffd'),
    (0x150265CC, 13804, '32032af0b879068fc27718c536bcea6e5617b9a0'),
    (0x1502A8A0, 592, '99742f426a0b5da3f225112ae76d1b83b0ee4c8b'),
    (0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
    (0x1502AF04, 284, 'b8f786b34a0b0f6db12c039c68a860a08bd52d1b'),
    (0x1502B6BC, 308, '91ed9cccb2168331f871d0b5b3597f9cfc8f558f'),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def verify_consumers(game, layout):
    return {'code': checked_spans(game.code, layout['game_vram'], CODE_SPANS)}


def reviewed_bank(root=ROOT):
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.read_rom(path)
    if rzip_archive.rom_sha1(rom) != ROM_SHA1:
        raise ValueError('US script ROM checksum mismatch')
    game = rzip_archive.game_archive(rom, layout['game_start'], layout['game_end'])
    consumers = verify_consumers(game, layout)
    bank = next(b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table']) if b.index == 6)
    if bank.flags:
        raise ValueError('script bank has unsupported outer flags')
    slots = struct.unpack_from('>I', rom, bank.start)[0] // 8
    if slots != 69:
        raise ValueError('script scene slot count differs from reviewed inventory')
    records = {'format': script_codec.FORMAT, 'scenes': [None] * slots}
    programs = []
    for scene in rzip_archive.parse_asset_entries(rom, bank):
        if scene.type_flags & ~0x80 or scene.compressed:
            raise ValueError('script scene directory flags changed')
        script_slots = struct.unpack_from('>I', rom, scene.start)[0] // 8
        source = {'scripts': [None] * script_slots}
        records['scenes'][scene.index] = source
        nested = rzip_archive.AssetBank(scene.index, scene.start, scene.end, 0)
        for entry in rzip_archive.parse_asset_entries(rom, nested):
            if not entry.compressed or entry.type_flags & ~0x90:
                raise ValueError('script program has unsupported entry flags')
            raw = rom[entry.start:entry.end]
            decoded = rzip_archive.decode_rzip_chunk(raw)
            if decoded.consumed != len(raw):
                raise ValueError('script RZIP entry has unexplained trailing bytes')
            program = script_codec.decode(decoded.data)
            source['scripts'][entry.index] = program
            programs.append({'scene': scene.index, 'script': entry.index,
                             'rom_start': entry.start, 'rom_end': entry.end,
                             'decoded_bytes': len(decoded.data), 'decoded_sha256': sha256(decoded.data),
                             'position_keys': sum(map(len, program['position_tracks'])),
                             'bindings': len(program['bindings']),
                             'value_keys': sum(map(len, program['value_tracks'])),
                             'commands': sum(map(len, program['command_tracks'])),
                             'texts': len(program['texts'])})
    if len(programs) != 483 or sum(s is not None for s in records['scenes']) != 50:
        raise ValueError('script bank populated slots differ from reviewed inventory')
    packed = script_codec.encode_bank(records)
    if packed != rom[bank.start:bank.end]:
        raise ValueError('script instructions fail fresh whole-bank ROM reconstruction')
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    indices = [i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == PART_NAME]
    if len(indices) != 1 or indices[0] + 1 >= len(segments):
        raise ValueError('missing or duplicate script YAML segment')
    segment, following = segments[indices[0]:indices[0] + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    if (segment.get('type') != 'bin' or segment.get('start') != bank.start or end != bank.end
            or segment.get('align') != 1 or segment.get('subalign') != 1):
        raise ValueError('script YAML extent differs from the reviewed ROM bank')
    expected = {'schema_version': 1, 'profile': 'us', 'bank': 6, 'rom_sha1': ROM_SHA1,
                'rom_start': bank.start, 'rom_end': bank.end, 'original_sha256': sha256(packed),
                'format': script_codec.FORMAT, 'encoder': {'implementation': 'zlib', 'level': 6, 'wbits': -15},
                'programs': programs, 'consumers': consumers}
    return rom, expected, records


def input_files(expected, records):
    return {name: (json.dumps(value, indent=2) + '\n').encode()
            for name, value in [('manifest.json', expected), ('scripts.json', records)]}


def input_error(directory, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      './conker script-assets recover to back up this folder and restore reviewed programs.')


def input_hashes(directory, expected):
    try:
        return asset_inputs.manifest_hashes(directory, expected, ('manifest.json', 'scripts.json'), 'script bank')
    except (OSError, ValueError, KeyError, TypeError, IndexError, struct.error) as error:
        raise input_error(directory, str(error)) from error


def packed_bank(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = script_codec.encode_bank(json.loads((directory / 'scripts.json').read_text()))
        if len(packed) != expected['rom_end'] - expected['rom_start'] or sha256(packed) != expected['original_sha256']:
            raise ValueError('script instructions no longer reconstruct original bank')
    except (OSError, ValueError, KeyError, TypeError, IndexError, struct.error) as error:
        raise input_error(directory, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('script inputs changed during packing')
    return packed, before


def recover_inputs(root=ROOT):
    _, expected, records = reviewed_bank(root)
    backup = asset_inputs.recover_directory(root / INPUT_DIRECTORY, root / 'build/assets/script-build/recovery',
                                           'us-', input_files(expected, records))
    return {'input_directory': str(root / INPUT_DIRECTORY), 'backup_directory': backup}


def build_parts(root=ROOT):
    rom, expected, records = reviewed_bank(root)
    directory = root / INPUT_DIRECTORY
    if not directory.exists():
        texture_build.publish_inputs(directory, input_files(expected, records))
    packed, hashes = packed_bank(directory, expected)
    if packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('script bank differs from independent original ROM bytes')
    if input_hashes(directory, expected) != hashes:
        raise ValueError('script inputs changed during batch packing')
    write_if_changed(root / 'build/us/scripts/parts' / (PART_NAME + '.bin'), packed)
    asset_receipts.write(root, 'scripts', __file__, {PART_NAME: asset_receipts.part_record(
        output=f'build/us/scripts/parts/{PART_NAME}.bin', payload=packed, source_inputs=hashes,
        input_directory=INPUT_DIRECTORY, extent=expected)})
    proof = {**expected, 'source_inputs': hashes, 'stored_bytes': len(packed),
             'verification': 'typed_tracks_bindings_commands_text_fresh_compression_and_independent_rom', 'matches_original': True}
    write_if_changed(root / 'build/us/scripts/batch.json', (json.dumps(proof, indent=2) + '\n').encode())
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
            print(f"Verified whole script bank: {proof['stored_bytes']} ROM bytes")
    except (OSError, ValueError, KeyError, TypeError, IndexError, struct.error) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
