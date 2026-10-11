"""Reconstruct reviewed bank-03, bank-04 and bank-09 model storage from structured native records."""
from __future__ import annotations

import hashlib
import json
import struct
import subprocess
import tempfile
import zlib
from pathlib import Path

try:
    from scripts import (model_assets, model_bundle_build, model_color_build, model_aux_build,
                         model_effect_format, model_emission_points, rzip_archive, rzip_pack, texture_build)
    from scripts.build_files import write_if_changed
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import model_assets, model_bundle_build, model_color_build
    import model_aux_build, model_effect_format, model_emission_points
    import rzip_archive, rzip_pack, texture_build
    from build_files import write_if_changed
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
INPUT_DIRECTORY = Path('build/assets/model-build/us')
BANKS = (3, 4, 9)
CONTRACT = Path('config/model_build.us.json')
sha256 = texture_build.sha256
LEVEL6_ENCODER = dict(texture_build.ENCODERS['zlib'], level=6)
GZIP6_ENCODER = dict(texture_build.ENCODERS['gzip'], level=6)


def part_name(index: int, bank: int) -> str:
    return f'models/bank{bank:02d}/{index:04d}'


def input_directory(index: int, bank: int) -> Path:
    return INPUT_DIRECTORY / f'{bank:02d}' / f'{index:04d}'


def layout_bins(profile: Path, *, bank: int, configuration: dict | None = None):
    segments = (load_profile(profile) if configuration is None else configuration)['segments']
    position = next((i for i, s in enumerate(segments)
                     if isinstance(s, dict) and s.get('name') == f'asset_bank_{bank:02d}'), None)
    if position is None:
        raise ValueError(f'missing required asset group: asset_bank_{bank:02d}')
    group, following = segments[position:position + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    rows = group.get('subsegments', [])
    if (group['type'] != 'group' or group.get('align') != 1 or group.get('subalign') != 1
            or not rows or any(len(r) != 3 or r[1] != 'bin' or not r[2].startswith('models/')
                               or '..' in Path(r[2]).parts for r in rows)
            or rows[0][0] != group['start'] or len({r[2] for r in rows}) != len(rows)
            or any(a[0] >= b[0] for a, b in zip(rows, rows[1:] + [[end]]))):
        raise ValueError(f'invalid bank-{bank:02d} model YAML partition')
    return [(r[0], r[2]) for r in rows], end


def partition(bank, entries):
    rows, cursor = [], bank.start
    for entry in sorted(entries, key=lambda e: e.start):
        if not cursor <= entry.start < entry.end <= bank.end:
            raise ValueError('overlapping or out-of-range model storage')
        if cursor < entry.start:
            rows.append((cursor, f'models/raw/{cursor:08X}'))
        rows.append((entry.start, part_name(entry.index, bank.index)))
        cursor = entry.end
    if cursor < bank.end:
        rows.append((cursor, f'models/raw/{cursor:08X}'))
    return rows


def attachment_records(payload: bytes) -> dict:
    """Decode all three-pair container regions into editable native fields."""
    geometry, layout = model_assets.parse_attachment_model(payload, model_assets.parse_model_geometry)
    header = list(geometry.header_words)
    display_start = layout['display_list_pointers'][0]
    display_end = display_start + geometry.display_list_size
    normal_start, normal_size = layout['normal_offset'], layout['normal_size']
    if normal_size % 64:
        raise ValueError('attachment normal region does not contain complete tables')
    records = {
        'format': 'attachment-three-pair',
        'header_words': header,
        'vertices': [[v.x, v.y, v.z, v.flag, v.s, v.t, *v.color] for v in geometry.vertices],
        'part_pointers': layout['display_list_pointers'],
        'joints': [list(row) for row in struct.iter_unpack(
            '>bBBB3f', payload[header[2]:header[2] + header[3]])],
        'display_commands': [list(row) for row in struct.iter_unpack(
            '>II', payload[display_start:display_end])],
        'normal_xy_s8': [list(row) for row in struct.iter_unpack(
            '>bb', payload[normal_start:normal_start + normal_size])],
        'zero_regions': [],
    }
    ranges = [(0, header[0] + header[1]), (display_start, display_end)]
    ranges += [(start, start + size) for start, size in
               ((header[2], header[3]), (normal_start, normal_size)) if size]
    cursor = 0
    for start, end in sorted(ranges) + [(len(payload), len(payload))]:
        if start < cursor or any(payload[cursor:start]):
            raise ValueError('attachment contains overlapping regions or an opaque gap')
        if start > cursor:
            if start - cursor not in (4, 8):
                raise ValueError('attachment has an unsupported zero region')
            records['zero_regions'].append([cursor, start - cursor])
        cursor = end
    return records


def encode_attachment_records(records: dict) -> bytes:
    fields = {'format', 'header_words', 'vertices', 'part_pointers', 'joints',
              'display_commands', 'normal_xy_s8', 'zero_regions'}
    if set(records) != fields:
        raise ValueError('invalid attachment record schema')
    try:
        header = records['header_words']
        chunks = [(0, struct.pack('>6I', *header)),
                  (24, b''.join(struct.pack('>hhhHhh4B', *row) for row in records['vertices'])),
                  (header[0], b''.join(struct.pack('>I', p) for p in records['part_pointers'])),
                  (records['part_pointers'][0], b''.join(
                      struct.pack('>II', *row) for row in records['display_commands']))]
        for offset, rows, fmt in ((header[2], records['joints'], '>bBBB3f'),
                                  (header[4], records['normal_xy_s8'], '>bb')):
            if rows:
                chunks.append((offset, b''.join(struct.pack(fmt, *row) for row in rows)))
        for offset, size in records['zero_regions']:
            if type(offset) is not int or type(size) is not int or size not in (4, 8):
                raise ValueError('invalid attachment zero region')
            chunks.append((offset, bytes(size)))
    except (struct.error, TypeError, IndexError, OverflowError) as error:
        raise ValueError('invalid native attachment record') from error
    cursor, parts = 0, []
    for offset, data in sorted(chunks):
        if offset != cursor:
            raise ValueError('attachment records overlap or leave an uncovered gap')
        parts.append(data)
        cursor += len(data)
    payload = b''.join(parts)
    if attachment_records(payload) != records:
        raise ValueError('attachment records disagree with their declared boundaries')
    return payload


def verify_attachment_consumers(code: bytes, base: int) -> None:
    """Pin the whole US loader and vertex-copy functions for three-pair records."""
    for address, size, digest in (
        (0x1502FE10, 456, '8637778facf0ce5e9a4cd03316b390e02fdf84e2'),
        (0x1502FFD8, 384, 'd03a13f16beb1aacae4a2c964a393164e8a477c4'),
    ):
        offset = address - base
        if offset < 0 or hashlib.sha1(code[offset:offset + size]).hexdigest() != digest:
            raise ValueError(f'ROM attachment consumer changed at 0x{address:08X}')


def model_records(payload: bytes, *, bank: int, entry: int | None = None) -> dict:
    if bank not in BANKS:
        raise ValueError('unsupported direct-model bank')
    if bank == 4:
        return model_bundle_build.bundle_records(payload, lambda raw: model_records(raw, bank=3))
    if bank == 9 and entry in model_emission_points.ENTRIES:
        return model_aux_build.point_records(payload)
    if bank == 9 and entry in range(173, 184):
        return model_aux_build.effect_records(payload)
    if bank == 9 and model_assets.is_attachment_model(payload):
        return attachment_records(payload)
    geometry = model_assets.parse_model_geometry(payload, model_relative_vertices=bank == 9)
    if any(geometry.header_words[2:9]) or geometry.header_words[9] != 0x80000000:
        raise ValueError('model has unsupported auxiliary regions')
    display_end = geometry.display_list_offset + geometry.display_list_size
    commands = list(struct.iter_unpack('>II', payload[geometry.display_list_offset:display_end]))
    # DC38000E transfers 32 signed XY pairs, addressed by vertex-cache slot.
    # Admit only complete, contiguous, referenced tables; do not absorb gaps.
    normal_offsets = sorted({argument for command, argument in commands
                             if command == model_assets.CHARACTER_CUSTOM_MOVEMEM_COMMAND})
    normal_end = display_end + 64 * len(normal_offsets)
    if (normal_offsets != list(range(display_end, normal_end, 64))
            or normal_end > len(payload)):
        raise ValueError('model normal tables are incomplete or noncontiguous')
    suffix = payload[normal_end:]
    if suffix not in (b'', bytes(8)):
        raise ValueError('model has unsupported trailing bytes')
    records = {'header_words': list(geometry.header_words),
               'vertices': [[v.x, v.y, v.z, v.flag, v.s, v.t, *v.color] for v in geometry.vertices],
               'display_commands': [list(pair) for pair in commands]}
    if normal_offsets:
        records['normal_xy_s8'] = [[list(pair) for pair in struct.iter_unpack(
            '>bb', payload[offset:offset + 64])] for offset in normal_offsets]
    if suffix:
        # This is an observed zero suffix, not an inferred alignment rule.
        records['zero_suffix_bytes'] = 8
    return records


def encode_records(records: dict, *, bank: int) -> bytes:
    if bank == 4:
        return model_bundle_build.encode_bundle_records(records,
            lambda rows: encode_records(rows, bank=3), lambda raw: model_records(raw, bank=3))
    if isinstance(records, dict) and records.get('format') in ('effect-four-pair', 'emission-points'):
        if bank != 9:
            raise ValueError('effect and emission records require bank 09')
        if records['format'] == 'effect-four-pair':
            return model_aux_build.encode_effect_records(records)
        return model_aux_build.encode_point_records(records)
    if isinstance(records, dict) and records.get('format') == 'attachment-three-pair':
        if bank != 9:
            raise ValueError('attachment records require bank 09')
        return encode_attachment_records(records)
    required = {'header_words', 'vertices', 'display_commands'}
    if (not isinstance(records, dict) or not required <= set(records)
            or set(records) - required - {'normal_xy_s8', 'zero_suffix_bytes'}):
        raise ValueError('invalid model record schema')
    normals = records.get('normal_xy_s8', [])
    suffix_size = records.get('zero_suffix_bytes', 0)
    if (not isinstance(normals, list) or any(not isinstance(table, list) or len(table) != 32
                                           for table in normals)
            or type(suffix_size) is not int or suffix_size not in (0, 8)):
        raise ValueError('invalid model normal table or zero suffix')
    try:
        payload = (struct.pack('>10I', *records['header_words'])
                   + b''.join(struct.pack('>hhhHhh4B', *row) for row in records['vertices'])
                   + b''.join(struct.pack('>II', *row) for row in records['display_commands'])
                   + b''.join(struct.pack('>bb', *pair) for table in normals for pair in table)
                   + bytes(suffix_size))
    except (struct.error, TypeError, OverflowError) as error:
        raise ValueError('invalid native model record') from error
    if model_records(payload, bank=bank) != records:
        raise ValueError('model records disagree with their declared boundaries')
    return payload


def level6_selections(contract: dict) -> dict:
    """Validate explicit reviewed overrides; old level-nine contracts stay valid."""
    choices = contract.get('level6_entries', {b: [] for b in contract['banks']})
    if not isinstance(choices, dict) or set(choices) != set(contract['banks']):
        raise ValueError('invalid model level-six encoder selection')
    for bank, entries in choices.items():
        if (not isinstance(entries, list) or any(type(i) is not int for i in entries)
                or entries != sorted(set(entries))
                or not set(entries) <= set(contract['banks'][bank])):
            raise ValueError('invalid model level-six encoder selection')
    return choices


def gzip6_selections(contract: dict) -> dict:
    choices = contract.get('gzip6_entries', {b: [] for b in contract['banks']})
    if not isinstance(choices, dict) or set(choices) != set(contract['banks']):
        raise ValueError('invalid model gzip-six encoder selection')
    level6 = level6_selections(contract)
    for bank, entries in choices.items():
        if (not isinstance(entries, list) or any(type(i) is not int for i in entries)
                or entries != sorted(set(entries))
                or not set(entries) <= set(contract['banks'][bank])
                or set(entries) & set(level6[bank])):
            raise ValueError('invalid model gzip-six encoder selection')
    return choices


def encode_model_payload(payload: bytes, encoder: dict) -> bytes:
    if encoder == texture_build.ENCODERS['zlib']:
        return rzip_pack.encode_rzip_chunk(payload)
    if encoder == GZIP6_ENCODER:
        texture_build.require_gnu_gzip()
        gz = subprocess.run(['gzip', '-n', '-6', '-c'], input=payload,
                            stdout=subprocess.PIPE, check=True).stdout
        if (len(gz) < 18 or gz[:8] != bytes.fromhex('1f8b080000000000')
                or struct.unpack('<II', gz[-8:]) != (zlib.crc32(payload), len(payload) & 0xffffffff)):
            raise ValueError('unexpected GNU gzip wrapper or checksum')
        packed = struct.pack('>I', len(payload)) + gz[10:-8]
    elif encoder == LEVEL6_ENCODER:
        compressor = zlib.compressobj(level=6, wbits=-15, memLevel=8, strategy=0)
        packed = struct.pack('>I', len(payload)) + compressor.compress(payload) + compressor.flush()
    else:
        raise ValueError('unsupported reviewed model encoder')
    try:
        decoded = rzip_archive.decode_rzip_chunk(packed)
    except zlib.error as error:
        raise ValueError('new model RZIP chunk failed independent decoding') from error
    if decoded.data != payload or decoded.consumed != len(packed):
        raise ValueError('new model RZIP chunk did not validate after compression')
    return packed


def reviewed_models(root: Path = ROOT, *, bank: int | None = None):
    """Review one bank independently, or the complete explicit selection."""
    if bank is not None and bank not in BANKS:
        raise ValueError('unsupported direct-model bank')
    requested = BANKS if bank is None else (bank,)
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.normalize_rom(path.read_bytes())
    digest = hashlib.sha1(rom).hexdigest()
    if digest not in layout['normalized_sha1']:
        raise ValueError('US model ROM checksum mismatch')
    contract = json.loads((root / CONTRACT).read_text())
    selections = contract.get('banks')
    if (contract.get('schema_version') != 2 or contract.get('profile') != 'us'
            or contract.get('rom_sha1') != digest
            or contract.get('encoder') != texture_build.ENCODERS['zlib']
            or not isinstance(selections, dict) or set(selections) not in ({'03', '09'}, {'03', '04', '09'})):
        raise ValueError('invalid committed US model reconstruction contract')
    if bank is not None and f'{bank:02d}' not in selections:
        raise ValueError('requested model bank has no reviewed selection')
    requested = tuple(b for b in requested if f'{b:02d}' in selections)
    for bank_id in requested:
        selected = selections[f'{bank_id:02d}']
        if (not isinstance(selected, list) or not selected
                or any(type(i) is not int or i < 0 for i in selected)
                or selected != sorted(set(selected))):
            raise ValueError('invalid committed US model reconstruction selection')
    level6 = level6_selections(contract)
    gzip6 = gzip6_selections(contract)
    banks = rzip_archive.parse_asset_banks(rom, layout['asset_table'])
    result = []
    for bank_id in requested:
        selected = selections[f'{bank_id:02d}']
        bank = next((b for b in banks if b.index == bank_id), None)
        if bank is None or bank.flags:
            raise ValueError(f'reviewed model bank {bank_id:02d} is missing or not an indexed ROM bank')
        if bank_id in (4, 9):
            if layout.get('game_format') != 'rzip':
                raise ValueError(f'bank-{bank_id:02d} consumer proof requires the RZIP game archive')
            game = rzip_archive.parse_game_archive(rom[layout['game_start']:layout['game_end']])
            if bank_id == 4:
                model_bundle_build.verify_consumers(game.code, int(layout['game_vram']))
            else:
                model_assets.verify_direct_model_consumers(game.code, int(layout['game_vram']))
        entries = [e for e in rzip_archive.parse_asset_entries(rom, bank) if e.index in selected]
        if bank_id == 9 and set(selected) & set(range(173, 184)):
            types = model_effect_format.verify_effect_consumers(
                game.code, int(layout['game_vram']), game.data, int(layout['game_data_vram']))
            payloads = {e.index: rzip_archive.decode_rzip_chunk(rom[e.start:e.end]).data
                        for e in entries if e.index in range(173, 184)}
            sources = model_effect_format.resolve_effect_sources(payloads, types)
            for index, source in sources.items():
                model_effect_format.parse_effect_model(
                    payloads[index], model_assets.parse_model_geometry, source)
        if bank_id == 9 and set(selected) & set(model_emission_points.ENTRIES):
            model_emission_points.verify_consumers(
                game.code, int(layout['game_vram']), game.data, int(layout['game_data_vram']))
        rows, end = layout_bins(root / 'config/profiles/us.yaml', bank=bank_id)
        if ([e.index for e in entries] != selected or rows != partition(bank, entries) or end != bank.end):
            raise ValueError(f'model YAML splits differ from reviewed bank-{bank_id:02d} boundaries')
        attachment_consumers_checked = False
        for entry in entries:
            if not entry.compressed:
                raise ValueError('reviewed model must use RZIP storage')
            stored = rom[entry.start:entry.end]
            chunk = rzip_archive.decode_rzip_chunk(stored)
            if chunk.consumed != len(stored):
                raise ValueError('model stored extent includes unowned trailing bytes')
            records = model_records(chunk.data, bank=bank_id, entry=entry.index)
            if bank_id == 4 and records['segments'][0]['format'] == 'primary-color-surface-direct':
                model_color_build.verify_consumers(game.code, int(layout['game_vram']))
            if records.get('format') == 'attachment-three-pair' and not attachment_consumers_checked:
                verify_attachment_consumers(game.code, int(layout['game_vram']))
                attachment_consumers_checked = True
            if encode_records(records, bank=bank_id) != chunk.data:
                raise ValueError('model records failed independent decoded comparison')
            expected = {'schema_version': 1, 'profile': 'us', 'bank': bank_id, 'entry': entry.index,
                        'rom_sha1': digest, 'rom_start': entry.start, 'rom_end': entry.end,
                        'decoded_size': len(chunk.data), 'original_decoded_sha256': sha256(chunk.data),
                        'original_stored_sha256': sha256(stored),
                        'encoder': (dict(GZIP6_ENCODER) if entry.index in gzip6[f'{bank_id:02d}']
                                    else dict(LEVEL6_ENCODER) if entry.index in level6[f'{bank_id:02d}']
                                    else contract['encoder'])}
            result.append((expected, records))
    return rom, result


def input_error(directory: Path, expected: dict, reason: str) -> ValueError:
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      f"./conker model-assets recover --bank {expected['bank']} --entry {expected['entry']} "
                      'to back up this folder and restore reviewed ROM inputs.')


def input_hashes(directory: Path, expected: dict):
    try:
        if json.loads((directory / 'manifest.json').read_text()) != expected:
            raise ValueError('model manifest differs from reviewed ROM contract')
        return {name: sha256((directory / name).read_bytes()) for name in ('manifest.json', 'model.json')}
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error


def input_files(expected: dict, records: dict) -> dict[str, bytes]:
    return {name: (json.dumps(value, indent=2) + '\n').encode()
            for name, value in [('manifest.json', expected), ('model.json', records)]}


def recover_inputs(entry: int, root: Path = ROOT, *, bank: int) -> dict:
    """Explicitly restore one reviewed bundle, retaining the complete old folder."""
    _, selected = reviewed_models(root, bank=bank)
    chosen = next((pair for pair in selected if pair[0]['bank'] == bank and pair[0]['entry'] == entry), None)
    if chosen is None:
        raise ValueError(f'model entry {entry} is not in the reviewed bank-{bank:02d} selection')
    expected, records = chosen
    directory = root / input_directory(entry, bank)
    if directory.is_symlink() or (directory.exists() and not directory.is_dir()):
        raise ValueError(f'refusing recovery of a non-directory or symlink: {directory}')
    backup = None
    if directory.exists():
        backups = root / 'build/assets/model-build/recovery/us' / f'{bank:02d}'
        backups.mkdir(parents=True, exist_ok=True)
        backup = Path(tempfile.mkdtemp(prefix=f'{entry:04d}-', dir=backups)) / 'inputs'
        directory.rename(backup)
    try:
        texture_build.publish_inputs(directory, input_files(expected, records))
    except Exception:
        if backup is not None and not directory.exists():
            backup.rename(directory)
        raise
    return {'bank': bank, 'entry': entry, 'input_directory': str(directory),
            'backup_directory': str(backup) if backup is not None else None}


def packed_model(directory: Path, expected: dict):
    before = input_hashes(directory, expected)
    try:
        payload = encode_records(json.loads((directory / 'model.json').read_text()), bank=expected['bank'])
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error
    if len(payload) != expected['decoded_size'] or sha256(payload) != expected['original_decoded_sha256']:
        raise ValueError('model records no longer reconstruct original payload')
    packed = encode_model_payload(payload, expected['encoder'])
    if (len(packed) != expected['rom_end'] - expected['rom_start']
            or sha256(packed) != expected['original_stored_sha256']):
        raise ValueError('reviewed model encoder differs from original RZIP storage')
    if input_hashes(directory, expected) != before:
        raise ValueError('model inputs changed during packing')
    return packed, before


def build_parts(root: Path = ROOT, *, bank: int | None = None):
    rom, selected = reviewed_models(root, bank=bank)
    candidates = []
    for expected, records in selected:
        directory = root / input_directory(expected['entry'], expected['bank'])
        if not directory.exists():
            texture_build.publish_inputs(directory, input_files(expected, records))
        packed, hashes = packed_model(directory, expected)
        if packed != rom[expected['rom_start']:expected['rom_end']]:
            raise ValueError(f"model {expected['bank']:02d}:{expected['entry']:04d} differs from independent original ROM bytes")
        candidates.append((expected, directory, packed, hashes))
    for expected, directory, _, hashes in candidates:
        if input_hashes(directory, expected) != hashes:
            raise ValueError('model inputs changed during batch packing')
    proofs = []
    for expected, directory, packed, hashes in candidates:
        write_if_changed(root / 'build/us/models/parts' / (part_name(expected['entry'], expected['bank']) + '.bin'), packed)
        proofs.append({**expected, 'source_inputs': hashes, 'stored_sha256': sha256(packed),
                       'matches_original': packed == rom[expected['rom_start']:expected['rom_end']]})
    result = {'model_count': len(proofs), 'stored_bytes': sum(len(p) for _, _, p, _ in candidates),
              'decoded_bytes': sum(e['decoded_size'] for e in proofs), 'models': proofs,
              'verification': 'decoded_and_stored_hashes_and_independent_rom_bytes',
              'matches_original': all(e['matches_original'] for e in proofs)}
    receipt = root / 'build/us/models'
    if bank is not None:
        receipt /= f'bank{bank:02d}'
    write_if_changed(receipt / 'batch.json', (json.dumps(result, indent=2) + '\n').encode())
    return result


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    build = commands.add_parser('build-parts')
    build.add_argument('--bank', type=int, choices=BANKS, help='build only this bank (default: all)')
    recover = commands.add_parser('recover', help='back up and restore one reviewed input bundle')
    recover.add_argument('--bank', type=int, choices=BANKS, required=True, help='model bank')
    recover.add_argument('--entry', required=True, type=int, help='decimal model entry ID')
    args = parser.parse_args(argv)
    try:
        if args.command == 'recover':
            print(json.dumps(recover_inputs(args.entry, bank=args.bank), indent=2))
        else:
            proof = build_parts(bank=args.bank)
            print(f"Verified {proof['model_count']} assets in model banks: {proof['stored_bytes']} RZIP bytes; "
                  'decoded/stored hashes and original ROM bytes agree')
    except (ValueError, OSError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
