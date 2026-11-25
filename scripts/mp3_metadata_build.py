"""Editable text prefixes from reviewed US MP3 source tags."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
try:
    from scripts import mp3_metadata_codec as codec, mp3_assets, asset_inputs, texture_build
except ModuleNotFoundError:
    import mp3_metadata_codec as codec, mp3_assets, asset_inputs, texture_build

ROOT = Path(__file__).resolve().parent.parent


class InputError(ValueError):
    """Preserve the metadata-specific recovery action through parent builders."""


ENTRIES = (
    7, 18, 19, 20, 21, 28, 118, 119, 125, 126, 127, 128, 129, 131, 134, 135,
    136, 139, 140, 141, 142, 143, 144, 146, 148, 155, 156, 158, 160, 161, 162, 163,
    164, 165, 166, 168, 170, 171, 174, 175, 176, 177, 179, 180, 181, 182, 183, 184,
    185, 186, 187, 188, 189, 202, 204, 206, 208, 209, 210, 212, 213, 214, 215, 216,
    217, 218, 219, 220, 221, 222, 223, 225, 227, 228, 229, 230, 231, 232, 233, 235,
    236, 237, 238, 239, 240, 241, 243, 244, 245, 246, 247, 248, 249, 250, 251, 253,
    254, 255, 256, 257, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271,
    272, 273, 274, 275, 276, 277, 279, 280, 281, 282, 283, 284, 285, 286, 287, 290,
    291, 292, 294, 296, 297, 298, 299, 300, 301, 302, 303, 305, 306, 307, 308, 310,
    311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def input_directory(index):
    if type(index) is not int or index not in ENTRIES:
        raise ValueError('unsupported US metadata entry')
    return Path(f'build/assets/mp3-metadata/us/{index:04d}')


def relative_directory(index):
    input_directory(index)
    return Path(f'../../../mp3-metadata/us/{index:04d}')


def reviewed_tag(original, stream):
    index = stream['entry']
    if index not in ENTRIES:
        return None
    if sha256(original) != stream['original_sha256']:
        raise ValueError('metadata backing differs from the checked MP3 stream')
    walk = mp3_assets.parse_mp3_cue_stream(original)
    offset = walk.trailing_offset
    record = codec.decode(original[offset:offset + 128])
    spans = codec.encode(record)
    expected = {'schema_version': 1, 'format': codec.FORMAT, 'entry': index,
        'stream_sha256': stream['original_sha256'], 'tag_offset': offset,
        'ranges': [[offset + at, offset + at + len(data)] for at, data in spans],
        'fields_sha256': sha256(b''.join(data for _, data in spans))}
    return expected, record


def input_files(expected, record):
    return {'manifest.json': (json.dumps(expected, indent=2) + '\n').encode(),
            'tag.json': (json.dumps(record, indent=2) + '\n').encode()}


def input_hashes(directory, expected):
    try:
        return asset_inputs.manifest_hashes(directory, expected, ('manifest.json', 'tag.json'), 'MP3 source metadata')
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error


def input_error(directory, expected, reason):
    return InputError(f'{directory}: {reason}. Inputs were preserved; restore your files or run '
        f'./conker mp3-assets recover-metadata --entry {expected["entry"]} to back up and restore reviewed text.')


def packed_tag(directory, expected):
    before = input_hashes(directory, expected)
    try:
        record = json.loads((directory / 'tag.json').read_bytes())
        spans = [(expected['tag_offset'] + at, data) for at, data in codec.encode(record)]
        ranges = [[at, at + len(data)] for at, data in spans]
        if (ranges != expected['ranges']
                or sha256(b''.join(data for _, data in spans)) != expected['fields_sha256']):
            raise ValueError('tag text no longer reproduces reviewed fields')
    except (OSError, ValueError) as error:
        raise input_error(directory, expected, str(error)) from error
    if input_hashes(directory, expected) != before:
        raise ValueError('MP3 metadata inputs changed during packing')
    return spans, before


def initialize(root, original, stream):
    reviewed = reviewed_tag(original, stream)
    if reviewed is not None:
        expected, record = reviewed
        directory = root / input_directory(stream['entry'])
        if not directory.exists():
            texture_build.publish_inputs(directory, input_files(expected, record))


def recover_inputs(index, root=ROOT):
    input_directory(index)
    # This authenticates the same whole ROM, full consumers and layout used by
    # coefficient reconstruction before recovering any metadata source.
    try:
        from scripts import mp3_spectral_build
    except ModuleNotFoundError:
        import mp3_spectral_build
    _, selected = mp3_spectral_build.reviewed_streams(root)
    stream, original = next(pair for pair in selected if pair[0]['entry'] == index)
    expected, record = reviewed_tag(original, stream)
    backup = asset_inputs.recover_directory(root / input_directory(index),
        root / 'build/assets/mp3-metadata/recovery/us', f'{index:04d}-', input_files(expected, record))
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
