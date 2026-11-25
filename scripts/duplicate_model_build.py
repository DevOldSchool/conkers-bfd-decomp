"""Reconstruct bank-04 model 58 and its index-derived alignment."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

try:
    from scripts import (asset_directory_build as directories, asset_inputs, asset_receipts,
                         bank_index_inputs, model_assets, model_build, model_duplicate_normals as codec,
                         rzip_archive, rzip_bounded, texture_build)
    from scripts.build_files import write_if_changed
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import asset_directory_build as directories, asset_inputs, asset_receipts, bank_index_inputs
    import model_assets, model_build, model_duplicate_normals as codec, rzip_archive, rzip_bounded, texture_build
    from build_files import write_if_changed
    from model_character_alpha import checked_spans

ROOT = Path(__file__).resolve().parent.parent
SOURCE_ROOT = Path('build/assets')
DIRECTORY = SOURCE_ROOT / 'duplicate-models/us/58'
PART = 'models/raw/010F8131'
CODE_SPANS = (
    (0x150031EC, 712, 'ed48d58ffb38dab90c140a0d547dbdae13f3225a'),
    (0x150039BC, 36, '3158e418c38cbfc95446c9535ecc73bed4bc28ea'),
    (0x150450CC, 576, 'e6792bb72b55c4d4ff70be77513bc6dd9fc789be'),
    (0x1503D368, 208, 'abef1711e0dda14ca8b45eb3689aa144f101bb5f'),
    (0x1503D438, 36, 'add9aec5cb5ff6df58ba80704156c1463b4a2071'),
)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def reviewed(root=ROOT):
    rom, parents = directories.reviewed_directories(root)
    parent, index = next(row for row in parents if row[0]['key'] == 'bank04')
    _, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    game = rzip_archive.game_archive(rom, layout['game_start'], layout['game_end'])
    consumers = checked_spans(game.code, layout['game_vram'], CODE_SPANS)
    bank = rzip_archive.parse_asset_banks(rom, layout['asset_table'])[4]
    entry = next(e for e in rzip_archive.parse_asset_entries(rom, bank) if e.index == 58)
    if bank.flags or bank.start != parent['rom_start'] or not entry.compressed:
        raise ValueError('duplicate-model directory or compression contract changed')
    rows, end = model_build.layout_bins(root / 'config/profiles/us.yaml', bank=4)
    start, stop = next((a, b) for (a, name), (b, _) in zip(rows, rows[1:] + [(end, '')]) if name == PART)
    if not start <= entry.start < entry.end <= stop:
        raise ValueError('duplicate model exceeds its original raw object')
    original = rom[entry.start:entry.end]
    chunk = rzip_archive.decode_rzip_chunk(original)
    source = codec.decode(chunk.data)
    if (chunk.consumed != len(original) or codec.encode(source) != chunk.data
            or rzip_bounded.encode_payload(chunk.data) != original):
        raise ValueError('duplicate model is not an exact fresh reconstruction')
    gaps = bank_index_inputs.alignment_spans(index, bank.start, bank.end)
    alignment = [[a, b] for a, b in gaps if start <= a < b <= stop]
    expected = {'schema_version': 1, 'profile': 'us', 'bank': 4, 'entry': 58, 'part': PART,
                'rom_sha1': directories.ROM_SHA1, 'rom_start': start, 'rom_end': stop,
                'original_sha256': sha(rom[start:stop]), 'parent': parent, 'bank_end': bank.end,
                'entry_start': entry.start, 'entry_end': entry.end,
                'decoded_sha256': sha(chunk.data), 'stored_sha256': sha(original),
                'alignment_ranges': alignment, 'consumers': consumers}
    return rom, expected, source


def input_files(expected, source):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'model.json': (json.dumps(source, indent=2) + '\n').encode()}


def input_error(error):
    return ValueError(f'{DIRECTORY}: {error}. Inputs were preserved; restore your files or use '
                      './conker duplicate-models recover to back up and recover this model. '
                      'Shared index inputs use ./conker asset-directories recover --part bank04.')


def input_hashes(root, expected):
    try:
        own = asset_inputs.manifest_hashes(root / DIRECTORY, expected, ('manifest.json', 'model.json'),
                                          'duplicate-normal model')
        prefix = DIRECTORY.relative_to(SOURCE_ROOT)
        hashes = {(prefix / p).as_posix(): h for p, h in own.items()}
        parent = expected['parent']; shared = directories.input_directory(parent['key'])
        hashes.update({(shared.relative_to(SOURCE_ROOT) / p).as_posix(): h
                       for p, h in directories.input_hashes(root / shared, parent).items()})
        return hashes
    except (OSError, ValueError) as error:
        raise input_error(error) from error


def packed_part(root, expected):
    before = input_hashes(root, expected)
    try:
        source = json.loads((root / DIRECTORY / 'model.json').read_text())
        decoded = codec.encode(source)
        fresh = rzip_bounded.encode_payload(decoded)
        if (sha(decoded) != expected['decoded_sha256'] or sha(fresh) != expected['stored_sha256']
                or len(fresh) != expected['entry_end'] - expected['entry_start']):
            raise ValueError('duplicate model fields differ from reviewed storage')
        parent = expected['parent']
        index = json.loads((root / directories.input_directory(parent['key']) / 'directory.json').read_text())
        if sha(directories.codec.encode(index)) != parent['directory_sha256']:
            raise ValueError('duplicate model index fields changed')
        gaps = bank_index_inputs.alignment_spans(index, parent['rom_start'], expected['bank_end'])
        alignment = [[a, b] for a, b in gaps if expected['rom_start'] <= a < b <= expected['rom_end']]
        if alignment != expected['alignment_ranges']:
            raise ValueError('duplicate model alignment ranges changed')
        chunks = [(expected['entry_start'], fresh)] + [(a, gaps[a, b]) for a, b in alignment]
        cursor, parts = expected['rom_start'], []
        for at, data in sorted(chunks):
            if at != cursor:
                raise ValueError('duplicate model fields overlap or leave unexplained storage')
            parts.append(data); cursor += len(data)
        packed = b''.join(parts)
        if cursor != expected['rom_end'] or sha(packed) != expected['original_sha256']:
            raise ValueError('duplicate model object differs from reviewed storage')
    except (OSError, ValueError, TypeError, KeyError, IndexError) as error:
        raise input_error(error) from error
    if input_hashes(root, expected) != before:
        raise ValueError('duplicate model sources changed during packing')
    return packed, before


def recover_inputs(root=ROOT):
    _, expected, source = reviewed(root)
    backup = asset_inputs.recover_directory(root / DIRECTORY, root / 'build/assets/duplicate-models/recovery',
                                           'us-58-', input_files(expected, source))
    return {'input_directory': str(root / DIRECTORY), 'backup_directory': backup}


def build_parts(root=ROOT):
    rom, expected, source = reviewed(root)
    if not (root / DIRECTORY).exists():
        texture_build.publish_inputs(root / DIRECTORY, input_files(expected, source))
    packed, hashes = packed_part(root, expected)
    if packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('duplicate-model candidate differs from independent ROM')
    if input_hashes(root, expected) != hashes:
        raise ValueError('duplicate-model sources changed before publication')
    output = Path('build/us/duplicate-models/parts') / (PART + '.bin')
    write_if_changed(root / output, packed)
    receipt = asset_receipts.part_record(output=output, payload=packed, source_inputs=hashes,
                                        input_directory=SOURCE_ROOT, extent=expected)
    asset_receipts.write(root, 'duplicate-models', __file__, {PART: receipt})
    return {**expected, 'source_inputs': hashes, 'rebuilt_bytes': len(packed), 'matches_original': True}


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
            print(f"Verified duplicate-normal model: {proof['rebuilt_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
