"""Editable fields consumed by the US MP3 L-command animation path."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
try:
    from scripts import mp3_cue_codec as codec, mp3_assets, asset_inputs, texture_build, rzip_archive
    from scripts.model_character_alpha import checked_spans
except ModuleNotFoundError:
    import mp3_cue_codec as codec, mp3_assets, asset_inputs, texture_build, rzip_archive
    from model_character_alpha import checked_spans

ROOT = Path(__file__).resolve().parent.parent
# Full transport/consumer spans: docs/evidence/data-layout/us_mp3_cue_fields.md.
ENTRIES = (
    0, 3, 4, 7, 9, 10, 12, 13, 16, 17, 18, 23, 25, 26,
    29, 30, 33, 34, 35, 36, 37, 38, 41, 42, 43, 45, 46, 48,
    51, 52, 53, 55, 56, 57, 58, 75, 76, 77, 78, 79, 82, 83,
    85, 87, 88, 89, 90, 91, 92, 93, 98, 99, 100, 101, 102, 103,
    105, 106, 107, 111, 119, 122, 123, 124, 129, 130, 131, 132, 133, 134,
    136, 137, 139, 140, 141, 142, 143, 144, 147, 150, 160, 161, 162, 165,
    184, 187, 203, 212, 213, 214, 215, 216, 217, 218, 221, 222, 223, 224,
    231, 232, 233, 234, 235, 236, 242, 243, 244, 245, 246, 247, 248, 249,
    251, 252, 253, 254, 255, 256, 257, 260, 261, 262, 263, 264, 265, 266,
    268, 269, 270, 272, 277, 279, 280, 295, 296, 297, 298, 299, 300, 301,
    302, 305, 307, 309, 310, 311, 312, 314, 315, 316, 317, 319, 321, 322,
    323, 324, 325, 335, 336, 340, 343, 344, 345, 346, 347, 351, 358, 359,
    360, 361, 363, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382,
    385, 387, 388, 389, 390, 391, 393, 398, 399, 400, 401, 402, 403, 404,
    405, 406, 407, 409, 410, 411, 412, 413, 414, 415, 416, 417, 425, 426,
    428, 429, 430, 431, 436, 437, 450, 454, 455, 456,
)
MAIN_SPANS = (
    (0x80012560, 40, '891d4b000acebe7251dee825974542e2a74212c5'),
    (0x80012588, 68, 'a7d7983558e28d6af01912d7c3baf6d9eb841850'),
    (0x800126E8, 48, '002e44a318f56df2b5313c0e2e1c6b145e9b5f39'),
)
GAME_SPANS = (
    (0x15043A00, 32, '79822b53f37d06c0cf08afdeb29580c138155b46'),
    (0x15043A20, 168, 'a8f08074a03814baa3e3db1a21bf2ed69350a9fe'),
    (0x15043AC8, 168, 'f2fb9139029b3f4a49582cd44f30f0f47298ddb3'),
    (0x15043B70, 72, '3b994815cf19f20042240c6513cf206ca2bab71d'),
    (0x15043BB8, 236, 'fdf0bfe5d63d14e4b28a1144ed6ed826eee23911'),
    (0x15043CA4, 232, 'c7101091b6d8149f51f5e7733bfddd215fc86f64'),
    (0x15080228, 288, 'c6151197222d84208ae36f32a183fd0f8e1569ac'),
    (0x15080430, 204, 'd874d3ff162bcefda9530ef55c22883b88b33701'),
    (0x151F3C1C, 24, '19e438e8442b48db32bfbb32a486f5a7a2feb464'),
    (0x151F86B0, 436, '07873affa142228a4e117b1993e2b16bee24b7e3'),
)


class InputError(ValueError):
    """Preserve cue-specific recovery guidance through the stream builder."""


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def verify_consumers(rom, layout):
    main = checked_spans(rom, 0x80000000, MAIN_SPANS)
    game = rzip_archive.game_archive(rom, layout['game_start'], layout['game_end'])
    return {'main': main, 'game': checked_spans(game.code, layout['game_vram'], GAME_SPANS)}


def input_directory(index):
    if type(index) is not int or index not in ENTRIES:
        raise ValueError('unsupported US MP3 cue entry')
    return Path(f'build/assets/mp3-cues/us/{index:04d}')


def relative_directory(index):
    input_directory(index)
    return Path(f'../../../mp3-cues/us/{index:04d}')


def reviewed_stream(original, stream):
    if stream['entry'] not in ENTRIES:
        return None
    if sha256(original) != stream['original_sha256']:
        raise ValueError('cue backing differs from the checked MP3 stream')
    walk = mp3_assets.parse_mp3_cue_stream(original)
    if not walk.cues:
        raise ValueError('reviewed MP3 cue stream contains no commands')
    records, positions, spans = [], [], []
    for cue in walk.cues:
        offset = cue['record_offset']
        record = codec.decode(original[offset:offset + cue['record_size']])
        records.append({'frame': cue['frame_index'], 'fields': record})
        positions.append([cue['frame_index'], offset])
        spans.extend((offset + at, data) for at, data in codec.encode(record))
    expected = {'schema_version': 1, 'format': codec.FORMAT, 'entry': stream['entry'],
        'stream_sha256': stream['original_sha256'], 'positions': positions,
        'ranges': [[at, at + len(data)] for at, data in spans],
        'fields_sha256': sha256(b''.join(data for _, data in spans))}
    return expected, {'format': codec.FORMAT, 'commands': records}


def input_files(expected, records):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'commands.json': (json.dumps(records, indent=2) + '\n').encode()}


def input_error(directory, expected, reason):
    return InputError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
        f'./conker mp3-assets recover-cues --entry {expected["entry"]} to back up and restore reviewed commands.')


def input_hashes(directory, expected):
    try:
        return asset_inputs.manifest_hashes(directory, expected,
            ('manifest.json', 'commands.json'), 'MP3 L-command fields')
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error


def packed_fields(directory, expected):
    before = input_hashes(directory, expected)
    try:
        source = json.loads((directory / 'commands.json').read_bytes())
        if (type(source) is not dict or set(source) != {'format', 'commands'}
                or source['format'] != codec.FORMAT or type(source['commands']) is not list
                or len(source['commands']) != len(expected['positions'])):
            raise ValueError('invalid MP3 command source')
        spans = []
        for record, (frame, offset) in zip(source['commands'], expected['positions']):
            if (type(record) is not dict or set(record) != {'frame', 'fields'}
                    or type(record['frame']) is not int or record['frame'] != frame):
                raise ValueError('MP3 command frame placement changed')
            spans.extend((offset + at, data) for at, data in codec.encode(record['fields']))
        if ([[at, at + len(data)] for at, data in spans] != expected['ranges']
                or sha256(b''.join(data for _, data in spans)) != expected['fields_sha256']):
            raise ValueError('MP3 commands no longer reproduce reviewed fields')
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('MP3 cue inputs changed during packing')
    return spans, before


def initialize(root, original, stream):
    reviewed = reviewed_stream(original, stream)
    if reviewed is not None:
        expected, records = reviewed
        directory = root / input_directory(stream['entry'])
        if not directory.exists():
            texture_build.publish_inputs(directory, input_files(expected, records))


def recover_inputs(index, root=ROOT):
    input_directory(index)
    try:
        from scripts import mp3_spectral_build
    except ModuleNotFoundError:
        import mp3_spectral_build
    _, selected = mp3_spectral_build.reviewed_streams(root)
    stream, original = next(pair for pair in selected if pair[0]['entry'] == index)
    expected, records = reviewed_stream(original, stream)
    backup = asset_inputs.recover_directory(root / input_directory(index),
        root / 'build/assets/mp3-cues/recovery/us', f'{index:04d}-', input_files(expected, records))
    return {'entry': index, 'backup_directory': backup}


def main(argv=None):
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('list-entries', 'recover'))
    parser.add_argument('--entry', type=int)
    args = parser.parse_args(argv)
    if args.command == 'recover' and args.entry is None: parser.error('recover requires --entry')
    if args.command != 'recover' and args.entry is not None: parser.error('--entry is only valid for recover')
    try:
        if args.command == 'list-entries': print(' '.join(f'{index:04d}' for index in ENTRIES))
        else: print(json.dumps(recover_inputs(args.entry), indent=2))
    except (OSError, ValueError) as error:
        parser.exit(2, f'error: {error}\n')


if __name__ == '__main__':
    main()
