"""Rebuild reviewed US sprite ranges from editable color and intensity PNGs."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import struct
import zlib

try:
    from scripts import asset_inputs, model_assets, rzip_archive, rzip_gzip, rzip_bounded, sprite_codec as codec, texture_build
    from scripts.build_files import write_if_changed
    from scripts.model_character_alpha import checked_spans
    from scripts.profile_config import load_profile
except ModuleNotFoundError:
    import asset_inputs, model_assets, rzip_archive, rzip_gzip, rzip_bounded, sprite_codec as codec, texture_build
    from build_files import write_if_changed
    from model_character_alpha import checked_spans
    from profile_config import load_profile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
INPUT_DIRECTORY = Path('build/assets/sprites/us')
PART_NAME = 'asset_bank_00'
CODE_SPANS = ((352365588, 368, 'e2d376dd1513f6db8a3f2f446a357f38fc5aa7fe'),
 (352365956, 388, '11e8ef10442d2438eb832885eacc4cb7da488a81'),
 (352496776, 636, '24f02469c9605e212ed65a4c75b216d50ef8577e'),
 (352497696, 240, 'cf808816ca9e3df778eb77490c317e7eb4b57c02'),
 (353876908, 5144, '1b0cf7e0210f000e00e10d946f61767eadc59aea'),
 (353882052, 176, '796ec079b8936ea7c9a5e31de22a9362f51316d8'),
 (353884080, 1708, '3410f75e0ce79d74db75ace5f6ce5380a9e2a389'),
 (353422776, 168, '282363991e81e8426bba40fac6a6d38fe7dc2b54'))
DATA_SPANS = ((2148097248, 690, 'da3f9d6a21bb81210a02c7cf334baa8676275456'),
 (2148061088, 72, '248788b65bccc0794f12d56ae36df18196792c29'))
# Keep prior encoders stable; the five additions use EOF-bounded DEFLATE.
ENCODERS = {0: 'gzip6',
 1: 6,
 2: 6,
 3: 6,
 6: 'gzip6',
 12: 'gzip6',
 13: 'gzip6',
 14: 'gzip6',
 15: 6,
 16: 6,
 17: 6,
 18: 6,
 21: 6,
 22: 6,
 23: 6,
 24: 6,
 25: 6,
 26: 6,
 27: 6,
 28: 6,
 29: 6,
 30: 6,
 31: 6,
 32: 6,
 33: 'gzip6',
 34: 'gzip6',
 35: 'gzip6',
 36: 'gzip6',
 37: 6,
 38: 6,
 40: 'raw',
 41: 'raw',
 42: 'raw',
 43: 'raw',
 44: 'raw',
 45: 'raw',
 46: 6,
 48: 6,
 49: 6,
 50: 'gzip6',
 51: 6,
 54: 6,
 55: 6,
 56: 6,
 57: 6,
 58: 6,
 62: 6,
 65: 'gzip6',
 66: 'gzip6',
 67: 'gzip6',
 68: 6}
ENCODERS = dict(sorted({**ENCODERS, **dict.fromkeys((4, 5, 19, 47, 63), 'bounded6')}.items()))


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def verify_consumers(game, layout):
    return {'code': checked_spans(game.code, layout['game_vram'], CODE_SPANS),
            'tables': checked_spans(game.data, layout['game_data_vram'], DATA_SPANS)}


def encode_payload(data, encoder):
    if encoder == 'bounded6':
        return rzip_bounded.encode_payload(data)
    if encoder == 'raw':
        return data
    if encoder in ('gzip6', 'gzip9'):
        return rzip_gzip.encode_payload(data, int(encoder[-1]))
    if type(encoder) is not int or encoder not in (6, 9):
        raise ValueError('unsupported sprite encoder')
    compressor = zlib.compressobj(level=encoder, wbits=-15)
    return struct.pack('>I', len(data)) + compressor.compress(data) + compressor.flush()


def image_name(entry, frame, fmt):
    return f'{entry:02d}-{frame:02d}.{fmt}.png'


def image_names(expected):
    return [image_name(row['entry'], frame, fmt) for row in expected['entries']
            for frame in range(row['frames']) for fmt in codec.FORMATS]


def reviewed_bank(root=ROOT):
    path, layout = model_assets.resolve_rom('us', root / 'roms/baserom.us.z64')
    rom, _ = rzip_archive.normalize_rom(path.read_bytes())
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        raise ValueError('US sprite ROM checksum mismatch')
    game = rzip_archive.parse_game_archive(rom[layout['game_start']:layout['game_end']])
    consumers = verify_consumers(game, layout)
    bank = next(b for b in rzip_archive.parse_asset_banks(rom, layout['asset_table']) if b.index == 0)
    if bank.flags or struct.unpack_from('>I', rom, bank.start)[0] != 69 * 8:
        raise ValueError('sprite bank index differs from reviewed inventory')
    table_offset = 0x80095CE0 - layout['game_data_vram']
    entries, decoded = [], {}
    for entry in rzip_archive.parse_asset_entries(rom, bank):
        if entry.index not in ENCODERS:
            continue
        encoder = ENCODERS[entry.index]
        if entry.type_flags & ~0x90 or entry.compressed != (encoder != 'raw'):
            raise ValueError('sprite entry flags differ from reviewed storage')
        original = rom[entry.start:entry.end]
        chunk = rzip_archive.decode_rzip_chunk(original) if entry.compressed else None
        data = chunk.data if chunk else original
        if chunk and chunk.consumed != len(original):
            raise ValueError('sprite compressed entry has unexplained trailing bytes')
        flags, frames, length, x, y, width, last = struct.unpack_from('>BBHhhBB', game.data, table_offset + entry.index * 10)
        if not width or not frames or length * 2 % (width * 5):
            raise ValueError('sprite descriptor has non-integral frame dimensions')
        height = length * 2 // (width * 5)
        if codec.dimensions(width, height) != length or len(data) != frames * length:
            raise ValueError('sprite descriptor does not cover complete image planes')
        if encode_payload(data, encoder) != original:
            raise ValueError('sprite fresh compressor differs from reviewed ROM entry')
        entries.append({'entry': entry.index, 'rom_start': entry.start, 'rom_end': entry.end,
                        'frames': frames, 'width': width, 'height': height, 'frame_bytes': length,
                        'decoded_sha256': sha256(data), 'encoder': encoder})
        decoded[entry.index] = data
    if [row['entry'] for row in entries] != list(ENCODERS):
        raise ValueError('sprite bank selected entries differ from reviewed inventory')
    segments = load_profile(root / 'config/profiles/us.yaml')['segments']
    indices = [i for i, s in enumerate(segments) if isinstance(s, dict) and s.get('name') == PART_NAME]
    if len(indices) != 1 or indices[0] + 1 >= len(segments):
        raise ValueError('missing or duplicate sprite YAML segment')
    segment, following = segments[indices[0]:indices[0] + 2]
    end = following['start'] if isinstance(following, dict) else following[0]
    if (segment.get('type') != 'bin' or segment.get('start') != bank.start or end != bank.end
            or segment.get('align') != 1 or segment.get('subalign') != 1):
        raise ValueError('sprite YAML extent differs from reviewed ROM bank')
    expected = {'schema_version': 1, 'profile': 'us', 'bank': 0, 'rom_sha1': ROM_SHA1,
                'rom_start': bank.start, 'rom_end': bank.end, 'original_sha256': sha256(rom[bank.start:bank.end]),
                'entries': entries, 'consumers': consumers,
                'rom_ranges': [[r['rom_start'], r['rom_end']] for r in entries],
                'planes': ['rgba16', 'i4'], 'source_origin': 'increasing-tile-t',
                'row_layout': 'native-loadblock-dxt-and-render-tile-swaps'}
    return rom, expected, decoded


def input_files(rom, expected, decoded):
    files = {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
             'backing.bin': rom[expected['rom_start']:expected['rom_end']]}
    for row in expected['entries']:
        data = decoded[row['entry']]
        for frame in range(row['frames']):
            at = frame * row['frame_bytes']
            images = codec.decode_frame(data[at:at + row['frame_bytes']], row['width'], row['height'])
            for fmt, png in images.items():
                files[image_name(row['entry'], frame, fmt)] = png
    return files


def input_error(directory, reason):
    return ValueError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
                      './conker sprite-assets recover to back up this folder and restore reviewed PNGs.')


def input_hashes(directory, expected):
    try:
        hashes = asset_inputs.manifest_hashes(directory, expected,
            ('manifest.json', 'backing.bin', *image_names(expected)), 'sprite bank')
        if hashes['backing.bin'] != expected['original_sha256']:
            raise ValueError('sprite backing changed; restore it before reconstruction')
        return hashes
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error


def packed_bank(directory, expected):
    before = input_hashes(directory, expected)
    try:
        packed = bytearray((directory / 'backing.bin').read_bytes())
        spans = []
        for row in expected['entries']:
            data = b''.join(codec.encode_frame({fmt: (directory / image_name(row['entry'], frame, fmt)).read_bytes()
                         for fmt in codec.FORMATS}, row['width'], row['height']) for frame in range(row['frames']))
            if sha256(data) != row['decoded_sha256']:
                raise ValueError('sprite PNGs no longer reconstruct original pixels')
            fresh = encode_payload(data, row['encoder'])
            if len(fresh) != row['rom_end'] - row['rom_start']:
                raise ValueError('sprite compression extent differs from reviewed ROM')
            at = row['rom_start'] - expected['rom_start']
            packed[at:at + len(fresh)] = fresh
            spans.append((at, fresh))
        if sha256(packed) != expected['original_sha256']:
            raise ValueError('sprite PNGs no longer reconstruct original storage')
    except (OSError, ValueError) as error:
        raise input_error(directory, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('sprite inputs changed during packing')
    return bytes(packed), spans, before


def recover_inputs(root=ROOT):
    rom, expected, decoded = reviewed_bank(root)
    backup = asset_inputs.recover_directory(root / INPUT_DIRECTORY, root / 'build/assets/sprites/recovery',
                                           'us-', input_files(rom, expected, decoded))
    return {'input_directory': str(root / INPUT_DIRECTORY), 'backup_directory': backup}


def build_parts(root=ROOT):
    rom, expected, decoded = reviewed_bank(root)
    directory = root / INPUT_DIRECTORY
    if not directory.exists():
        texture_build.publish_inputs(directory, input_files(rom, expected, decoded))
    packed, spans, hashes = packed_bank(directory, expected)
    if packed != rom[expected['rom_start']:expected['rom_end']]:
        raise ValueError('sprite candidate differs from independent original ROM')
    if input_hashes(directory, expected) != hashes:
        raise ValueError('sprite inputs changed during batch packing')
    write_if_changed(root / 'build/us/sprites/parts' / (PART_NAME + '.bin'), packed)
    proof = {**expected, 'source_inputs': hashes, 'rebuilt_bytes': sum(len(data) for _, data in spans),
             'verification': 'png_planes_fresh_compression_actual_rom_ranges', 'matches_original': True}
    write_if_changed(root / 'build/us/sprites/batch.json', (json.dumps(proof, indent=2) + '\n').encode())
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
            print(f"Verified sprite PNG ranges: {proof['rebuilt_bytes']} ROM bytes")
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
