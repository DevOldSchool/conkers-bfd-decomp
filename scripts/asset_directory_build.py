"""Rebuild directories whose linker inputs still use preserved binary storage.

Directory and supported child formats are rebuilt from editable sources.
Each report family owns disjoint ranges; other payloads and gaps stay backing.
"""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import struct
try:
    from scripts import asset_directory_codec as codec, asset_inputs, asset_receipts, bank_index_inputs
    from scripts import rzip_archive, model_assets, texture_build, save_layout_inputs, camera_tracks_inputs, menu_text_inputs, dialogue_inputs, scene_header_inputs, spawn_record_inputs, model_placement_inputs
    from scripts.build_files import write_if_changed
    from scripts.model_character_alpha import checked_spans
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_directory_codec as codec, asset_inputs, asset_receipts, bank_index_inputs
    import rzip_archive, model_assets, texture_build, save_layout_inputs, camera_tracks_inputs, menu_text_inputs, dialogue_inputs, scene_header_inputs, spawn_record_inputs, model_placement_inputs
    from build_files import write_if_changed
    from model_character_alpha import checked_spans
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
MODEL_STARTS = {1: 0xAF4918, 2: 0xBB1BA0, 3: 0xF8F278, 4: 0xF9E660, 9: 0x1204780}
RAW_BANKS = (7, 8, 11, 13, 14, 17, 18, 21, 24, 26, 27, 28)
PARTS = {'outer': 'asset_bank_index',
         **{f'bank{bank:02X}': f'models/raw/{start:08X}' for bank, start in MODEL_STARTS.items()},
         **{f'bank{bank:02X}': f'asset_bank_{bank:02x}' for bank in RAW_BANKS}}
CODE_SPANS = ((0x1502AC88, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
              (0x1502B5C8, 244, '9c411ce6bf78e69583215fa8484bfd0f137edc72'))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def input_directory(key):
    if key not in PARTS:
        raise ValueError('unsupported asset directory')
    return Path('build/assets/asset-directories/us') / key


def object_extents(root):
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    result = {}
    for segment, following in zip(segments, segments[1:]):
        if not isinstance(segment, dict):
            continue
        end = following['start'] if isinstance(following, dict) else following[0]
        if segment.get('type') == 'bin' and segment.get('name') in PARTS.values():
            result[segment['name']] = (segment['start'], end)
        elif segment.get('type') == 'group':
            rows = segment['subsegments']
            for row, after in zip(rows, rows[1:] + [[end]]):
                if isinstance(row, list) and len(row) == 3 and row[1] == 'bin' and row[2] in PARTS.values():
                    result[row[2]] = (row[0], after[0])
    if set(result) != set(PARTS.values()):
        raise ValueError('directory object selection differs from the canonical profile')
    return result


def reviewed_directories(root=ROOT):
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.read_rom(path)
    if rzip_archive.rom_sha1(rom) != ROM_SHA1:
        raise ValueError('US asset directory ROM checksum mismatch')
    game = rzip_archive.game_archive(rom, layout['game_start'], layout['game_end'])
    consumers = checked_spans(game.code, layout['game_vram'], CODE_SPANS)
    save_layout_inputs.verify_consumers(game.code, layout['game_vram'])
    camera_tracks_inputs.verify_consumers(game.code, layout['game_vram'])
    menu_text_inputs.verify_consumers(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    dialogue_inputs.verify_consumers(game.code, layout['game_vram'], game.data, layout['game_data_vram'])
    scene_header_inputs.verify_consumers(rom, game.code, layout['game_vram'])
    spawn_record_inputs.verify_consumers(game.code, layout['game_vram'])
    model_placement_inputs.verify_consumers(game.code, layout['game_vram'])
    banks = rzip_archive.parse_asset_banks(rom, layout['asset_table'])
    extents, result = object_extents(root), []
    for key, name in PARTS.items():
        if key == 'outer':
            start = layout['asset_table']
            size = len(banks) * 8
        else:
            bank = banks[int(key[4:], 16)]
            if bank.flags:
                raise ValueError('indexed directory unexpectedly names a raw bank')
            rzip_archive.parse_asset_entries(rom, bank)
            start = bank.start
            size = struct.unpack_from('>I', rom, start)[0]
        left, right = extents[name]
        if left != start or not left < start + size <= right:
            raise ValueError('directory is not at the beginning of its canonical object')
        source = codec.decode(rom[start:start + size])
        expected = {'schema_version': 1, 'profile': 'us', 'key': key, 'part': name,
                    'rom_sha1': ROM_SHA1, 'rom_start': left, 'rom_end': right,
                    'rom_ranges': [[start, start + size]], 'directory_size': size,
                    'directory_sha256': sha256(rom[start:start + size]),
                    'original_sha256': sha256(rom[left:right]), 'consumers': consumers,
                    'format': codec.FORMAT}
        result.append((expected, source))
    return rom, result


def input_files(rom, expected, source):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'directory.json': (json.dumps(source, indent=2) + '\n').encode(),
            'backing.bin': rom[expected['rom_start']:expected['rom_end']]}


def input_error(directory, expected, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      f'./conker asset-directories recover --part {expected["key"]} '
                      'to back up this folder and restore the reviewed sources.')


def input_hashes(directory, expected, *, include_save_layout=False, include_camera_tracks=False, include_menu_text=False, include_dialogue=False, include_scene_headers=False, include_spawn_records=False, include_model_placements=False, include_alignment=False):
    try:
        hashes = asset_inputs.manifest_hashes(directory, expected,
            ('manifest.json', 'directory.json', 'backing.bin'), 'asset directory')
        if hashes['backing.bin'] != expected['original_sha256']:
            raise ValueError('asset directory backing changed')
        if include_save_layout and expected['key'] == 'bank07':
            hashes.update(save_layout_inputs.input_hashes(directory, expected, (directory / 'backing.bin').read_bytes()))
        if include_camera_tracks and expected['key'] == 'bank1B':
            hashes.update(camera_tracks_inputs.input_hashes(directory, expected, (directory / 'backing.bin').read_bytes()))
        if (include_menu_text or include_alignment) and expected['key'] == 'bank1C':
            hashes.update(menu_text_inputs.input_hashes(directory, expected, (directory / 'backing.bin').read_bytes()))
        if (include_dialogue or include_alignment) and expected['key'] == 'bank1A':
            hashes.update(dialogue_inputs.input_hashes(directory, expected, (directory / 'backing.bin').read_bytes()))
        if include_scene_headers and expected['key'] == 'bank15':
            hashes.update(scene_header_inputs.input_hashes(directory, expected, (directory / 'backing.bin').read_bytes()))
        if include_spawn_records and expected['key'] == 'bank0E':
            hashes.update(spawn_record_inputs.input_hashes(directory, expected, (directory / 'backing.bin').read_bytes()))
        if include_model_placements and expected['key'] == 'bank0B':
            hashes.update(model_placement_inputs.input_hashes(directory, expected, (directory / 'backing.bin').read_bytes()))
        return hashes
    except (OSError, ValueError, KeyError, TypeError) as error:
        raise input_error(directory, expected, str(error)) from error


def packed_directory(directory, expected, *, include_save_layout=False, include_camera_tracks=False, include_menu_text=False, include_dialogue=False, include_scene_headers=False, include_spawn_records=False, include_model_placements=False, include_alignment=False):
    before = input_hashes(directory, expected, include_save_layout=include_save_layout,
                          include_camera_tracks=include_camera_tracks, include_menu_text=include_menu_text, include_dialogue=include_dialogue, include_scene_headers=include_scene_headers, include_spawn_records=include_spawn_records, include_model_placements=include_model_placements, include_alignment=include_alignment)
    try:
        fresh = codec.encode(json.loads((directory / 'directory.json').read_text()))
        if len(fresh) != expected['directory_size'] or sha256(fresh) != expected['directory_sha256']:
            raise ValueError('directory fields no longer reproduce the reviewed table')
        backing = (directory / 'backing.bin').read_bytes()
        packed = fresh + backing[len(fresh):]
        if include_save_layout and expected['key'] == 'bank07':
            widths = save_layout_inputs.encoded(directory, expected, backing)
            packed = packed[:8] + widths + packed[8 + len(widths):]
        if include_camera_tracks and expected['key'] == 'bank1B':
            for offset, track in camera_tracks_inputs.encoded(directory, expected, backing):
                packed = packed[:offset] + track + packed[offset + len(track):]
        if (include_menu_text or include_alignment) and expected['key'] == 'bank1C':
            for offset, text in menu_text_inputs.encoded(directory, expected, backing):
                packed = packed[:offset] + text + packed[offset + len(text):]
        if (include_dialogue or include_alignment) and expected['key'] == 'bank1A':
            for offset, payload in dialogue_inputs.encoded(directory, expected, backing):
                packed = packed[:offset] + payload + packed[offset + len(payload):]
        if include_scene_headers and expected['key'] == 'bank15':
            for offset, payload in scene_header_inputs.encoded(directory, expected, backing):
                packed = packed[:offset] + payload + packed[offset + len(payload):]
        if include_spawn_records and expected['key'] == 'bank0E':
            for offset, payload in spawn_record_inputs.encoded(directory, expected, backing):
                packed = packed[:offset] + payload + packed[offset + len(payload):]
        if include_model_placements and expected['key'] == 'bank0B':
            for offset, payload in model_placement_inputs.encoded(directory, expected, backing):
                packed = packed[:offset] + payload + packed[offset + len(payload):]
        if include_alignment:
            for offset, payload in bank_index_inputs.existing_alignment(directory, expected):
                packed = packed[:offset] + payload + packed[offset + len(payload):]
        if sha256(packed) != expected['original_sha256']:
            raise ValueError('directory object differs from reviewed ROM storage')
    except (OSError, ValueError, KeyError, TypeError, struct.error) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected, include_save_layout=include_save_layout,
                          include_camera_tracks=include_camera_tracks, include_menu_text=include_menu_text, include_dialogue=include_dialogue, include_scene_headers=include_scene_headers, include_spawn_records=include_spawn_records, include_model_placements=include_model_placements, include_alignment=include_alignment) != before:
        raise ValueError('asset directory sources changed during packing')
    return packed, [(0, fresh)], before


def build_parts(root=ROOT, *, include_alignment=False):
    rom, reviewed = reviewed_directories(root)
    candidates = []
    for expected, source in reviewed:
        directory = root / input_directory(expected['key'])
        if not directory.exists():
            texture_build.publish_inputs(directory, input_files(rom, expected, source))
        # Validate existing sources before adding the new, separately editable table.
        input_hashes(directory, expected)
        if expected['key'] == 'bank07':
            save_layout_inputs.ensure_inputs(directory, expected, rom[expected['rom_start']:expected['rom_end']])
        if expected['key'] == 'bank1B':
            camera_tracks_inputs.ensure_inputs(directory, expected, rom[expected['rom_start']:expected['rom_end']])
        if expected['key'] == 'bank1C':
            menu_text_inputs.ensure_inputs(directory, expected, rom[expected['rom_start']:expected['rom_end']])
        if expected['key'] == 'bank1A':
            dialogue_inputs.ensure_inputs(directory, expected, rom[expected['rom_start']:expected['rom_end']])
        if expected['key'] == 'bank15':
            scene_header_inputs.ensure_inputs(directory, expected, rom[expected['rom_start']:expected['rom_end']])
        if expected['key'] == 'bank0E':
            spawn_record_inputs.ensure_inputs(directory, expected, rom[expected['rom_start']:expected['rom_end']])
        if expected['key'] == 'bank0B':
            model_placement_inputs.ensure_inputs(directory, expected, rom[expected['rom_start']:expected['rom_end']])
        packed, spans, hashes = packed_directory(directory, expected, include_save_layout=True, include_camera_tracks=True, include_menu_text=True, include_dialogue=True, include_scene_headers=True, include_spawn_records=True, include_model_placements=True, include_alignment=include_alignment)
        if packed != rom[expected['rom_start']:expected['rom_end']]:
            raise ValueError('directory candidate differs from independent ROM')
        candidates.append((expected, directory, (packed, spans), hashes))
    asset_inputs.check_batch_sources(candidates,
        lambda directory, expected: input_hashes(directory, expected, include_save_layout=True, include_camera_tracks=True, include_menu_text=True, include_dialogue=True, include_scene_headers=True, include_spawn_records=True, include_model_placements=True, include_alignment=include_alignment), 'asset directory')
    receipts, proof = {}, []
    for expected, _, (packed, spans), hashes in candidates:
        relative = Path('build/us/asset-directories/parts') / (expected['part'] + '.bin')
        write_if_changed(root / relative, packed)
        receipts[expected['part']] = asset_receipts.part_record(
            output=relative, payload=packed, source_inputs=hashes,
            input_directory=input_directory(expected['key']), extent=expected, spans=spans)
        proof.append({**expected, 'source_inputs': hashes, 'rebuilt_bytes': expected['directory_size']})
    asset_receipts.write(root, 'asset-directories', __file__, receipts)
    write_if_changed(root / 'build/us/asset-directories/proof.json', (json.dumps(proof, indent=2) + '\n').encode())
    return proof


def recover_inputs(key, root=ROOT):
    input_directory(key)
    rom, reviewed = reviewed_directories(root)
    expected, source = next(row for row in reviewed if row[0]['key'] == key)
    backup = asset_inputs.recover_directory(root / input_directory(key),
        root / 'build/assets/asset-directories/recovery', key + '-', input_files(rom, expected, source))
    return {'input_directory': str(root / input_directory(key)), 'backup_directory': backup}


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('build', 'recover', 'list-parts'))
    parser.add_argument('--part', choices=tuple(PARTS))
    args = parser.parse_args(argv)
    if args.command == 'recover' and args.part is None:
        parser.error('recover requires --part')
    if args.command != 'recover' and args.part is not None:
        parser.error('--part is only valid with recover')
    try:
        if args.command == 'list-parts':
            print(' '.join(PARTS.values()))
        elif args.command == 'recover':
            print(json.dumps(recover_inputs(args.part), indent=2))
        else:
            proof = build_parts(include_alignment=True)
            print(f'Verified {len(proof)} asset directories: {sum(r["rebuilt_bytes"] for r in proof)} ROM bytes')
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
