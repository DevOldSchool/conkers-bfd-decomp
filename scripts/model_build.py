"""Reconstruct reviewed bank-03 and bank-09 model storage from structured native records."""
from __future__ import annotations

import hashlib
import json
import struct
import tempfile
from pathlib import Path

try:
    from scripts import model_assets, rzip_archive, rzip_pack, texture_build
    from scripts.build_files import write_if_changed
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import model_assets, rzip_archive, rzip_pack, texture_build
    from build_files import write_if_changed
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
INPUT_DIRECTORY = Path('build/assets/model-build/us')
BANKS = (3, 9)
CONTRACT = Path('config/model_build.us.json')
sha256 = texture_build.sha256


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


def model_records(payload: bytes, *, bank: int) -> dict:
    if bank not in BANKS:
        raise ValueError('unsupported direct-model bank')
    geometry = model_assets.parse_model_geometry(payload, model_relative_vertices=bank == 9)
    if (geometry.display_list_offset + geometry.display_list_size != len(payload)
            or any(geometry.header_words[2:8])):
        raise ValueError('model has unsupported auxiliary regions or trailing bytes')
    return {'header_words': list(geometry.header_words),
            'vertices': [[v.x, v.y, v.z, v.flag, v.s, v.t, *v.color] for v in geometry.vertices],
            'display_commands': [list(pair) for pair in struct.iter_unpack(
                '>II', payload[geometry.display_list_offset:])]}


def encode_records(records: dict, *, bank: int) -> bytes:
    if not isinstance(records, dict) or set(records) != {'header_words', 'vertices', 'display_commands'}:
        raise ValueError('invalid model record schema')
    try:
        payload = (struct.pack('>10I', *records['header_words'])
                   + b''.join(struct.pack('>hhhHhh4B', *row) for row in records['vertices'])
                   + b''.join(struct.pack('>II', *row) for row in records['display_commands']))
    except (struct.error, TypeError, OverflowError) as error:
        raise ValueError('invalid native model record') from error
    if model_records(payload, bank=bank) != records:
        raise ValueError('model records disagree with their declared boundaries')
    return payload


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
            or not isinstance(selections, dict) or set(selections) != {f'{b:02d}' for b in BANKS}):
        raise ValueError('invalid committed US model reconstruction contract')
    for bank_id in requested:
        selected = selections[f'{bank_id:02d}']
        if (not isinstance(selected, list) or not selected
                or any(type(i) is not int or i < 0 for i in selected)
                or selected != sorted(set(selected))):
            raise ValueError('invalid committed US model reconstruction selection')
    banks = rzip_archive.parse_asset_banks(rom, layout['asset_table'])
    result = []
    for bank_id in requested:
        selected = selections[f'{bank_id:02d}']
        bank = next((b for b in banks if b.index == bank_id), None)
        if bank is None or bank.flags:
            raise ValueError(f'reviewed model bank {bank_id:02d} is missing or not an indexed ROM bank')
        if bank_id == 9:
            if layout.get('game_format') != 'rzip':
                raise ValueError('bank-09 consumer proof requires the RZIP game archive')
            game = rzip_archive.parse_game_archive(rom[layout['game_start']:layout['game_end']])
            model_assets.verify_direct_model_consumers(game.code, int(layout['game_vram']))
        entries = [e for e in rzip_archive.parse_asset_entries(rom, bank) if e.index in selected]
        rows, end = layout_bins(root / 'config/profiles/us.yaml', bank=bank_id)
        if ([e.index for e in entries] != selected or rows != partition(bank, entries) or end != bank.end):
            raise ValueError(f'model YAML splits differ from reviewed bank-{bank_id:02d} boundaries')
        for entry in entries:
            if not entry.compressed:
                raise ValueError('reviewed model must use RZIP storage')
            stored = rom[entry.start:entry.end]
            chunk = rzip_archive.decode_rzip_chunk(stored)
            if chunk.consumed != len(stored):
                raise ValueError('model stored extent includes unowned trailing bytes')
            records = model_records(chunk.data, bank=bank_id)
            if encode_records(records, bank=bank_id) != chunk.data:
                raise ValueError('model records failed independent decoded comparison')
            expected = {'schema_version': 1, 'profile': 'us', 'bank': bank_id, 'entry': entry.index,
                        'rom_sha1': digest, 'rom_start': entry.start, 'rom_end': entry.end,
                        'decoded_size': len(chunk.data), 'original_decoded_sha256': sha256(chunk.data),
                        'original_stored_sha256': sha256(stored), 'encoder': contract['encoder']}
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
    if expected['encoder'] != texture_build.ENCODERS['zlib']:
        raise ValueError('unsupported reviewed model encoder')
    packed = rzip_pack.encode_rzip_chunk(payload)
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
            print(f"Verified {proof['model_count']} models: {proof['stored_bytes']} RZIP bytes; "
                  'decoded/stored hashes and original ROM bytes agree')
    except (ValueError, OSError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
