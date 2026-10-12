"""Verify bank-17 ROM storage boundaries against loader-proven audio structures."""
from pathlib import Path
import struct
import sys

try:
    from scripts.profile_config import load_profile
    from scripts import audio_assets, mp3_assets, sound_bank_codec, adpcm_layout
except ModuleNotFoundError:
    from profile_config import load_profile
    import sound_bank_codec
    import adpcm_layout
    import audio_assets
    import mp3_assets

ROOT = Path(__file__).resolve().parent.parent


def bank_layout(profile: Path, *, configuration: dict | None = None) -> tuple[int, int, list[tuple[int, str]]]:
    segments = (load_profile(profile) if configuration is None else configuration)['segments']
    index = next((i for i, segment in enumerate(segments)
                  if isinstance(segment, dict) and segment.get('name') == 'asset_bank_17'), None)
    if index is None:
        raise ValueError(f'{profile}: missing required asset group: asset_bank_17')
    bank = segments[index]
    if bank['type'] != 'group' or bank['align'] != 1 or bank['subalign'] != 1:
        raise ValueError('audio bank must be a byte-aligned group')
    splits = []
    for entry in bank['subsegments']:
        if (len(entry) != 3 or entry[1] != 'bin' or not entry[2].startswith('audio/bank17/')
                or '..' in Path(entry[2]).parts):
            raise ValueError('invalid audio bank split entry')
        splits.append((entry[0], entry[2]))
    return bank['start'], segments[index + 1]['start'], splits


def proven_ranges(rom: bytes, family, mp3, *, sound_regions=None, adpcm_contract=None) -> list[tuple[int, int, str]]:
    start, end = family.bank_start, family.bank_end
    index_size = struct.unpack_from('>I', rom, start)[0]
    if index_size != 7 * 8:
        raise ValueError('audio bank index must contain seven records')
    ranges = [(start, start + index_size, 'index')]
    assets = family.assets + (mp3.offsets, mp3.lookup, mp3.huffman)
    names = ('sound_bank_control_rzip', 'external_sound_bank', 'wavetable_adpcm',
             'sequences', 'mp3_huffman_offsets', 'mp3_lookup', 'mp3_huffman')
    cursor = start + index_size
    for index, (asset, name) in enumerate(zip(assets, names, strict=True)):
        offset, flags = struct.unpack_from('>II', rom, start + index * 8)
        if (asset.entry_index != index or asset.rom_start != start + offset
                or asset.rom_end - asset.rom_start != (flags & 0x0FFFFFFF)
                or asset.type_flags != flags >> 24 or asset.rom_start < cursor
                or asset.rom_end > end):
            raise ValueError('audio asset disagrees with its bank index')
        if asset.rom_start > cursor:
            padding = rom[cursor:asset.rom_start]
            if any(padding) or len(padding) != (-cursor) % 8:
                raise ValueError('audio entry alignment padding is not proven')
            ranges.append((cursor, asset.rom_start, f'padding/{cursor - start:08X}'))
        if index == 1 and sound_regions is not None:
            ranges.extend((begin, finish, name.removeprefix('audio/bank17/'))
                          for begin, finish, name in sound_bank_codec.external_partition(asset, sound_regions))
        elif index == 2 and adpcm_contract is not None:
            ranges.extend((begin, finish, name.removeprefix('audio/bank17/'))
                          for begin, finish, name in adpcm_layout.partition(
                              asset, family.sound_graph.manifest['samples'], adpcm_contract))
        elif index == 3:
            if asset.compressed or rom[asset.rom_start:asset.rom_end] != asset.data:
                raise ValueError('sequence storage must be raw ROM bytes')
            if audio_assets.rebuild_compact_sequence_bank(family.sequences) != asset.data:
                raise ValueError('sequence descriptors and payloads do not reconstruct the entry')
            ranges.append((asset.rom_start, asset.rom_start + 4 + len(family.sequences) * 8,
                           'sequences/index'))
            for sequence in family.sequences:
                begin = asset.rom_start + sequence.offset
                finish = begin + len(sequence.data)
                ranges.append((begin, finish, f'sequences/{sequence.index:04d}'))
                if len(sequence.padding_after) != (-finish) % 4:
                    raise ValueError('sequence padding does not end at the next four-byte boundary')
                if sequence.padding_after:
                    ranges.append((finish, finish + len(sequence.padding_after),
                                   f'sequences/padding/{finish - asset.rom_start:08X}'))
        else:
            ranges.append((asset.rom_start, asset.rom_end, name))
        cursor = asset.rom_end
    cursor = start
    for begin, finish, _ in ranges:
        if begin != cursor or not begin < finish <= end:
            raise ValueError('audio ranges overlap or leave unaccounted bytes')
        cursor = finish
    if cursor != end:
        raise ValueError('audio ranges do not cover the entire bank')
    return [(begin, finish, 'audio/bank17/' + name) for begin, finish, name in ranges]


def verify(profile: Path = ROOT / 'config/profiles/us.yaml') -> tuple[bytes, list[tuple[int, int, str]]]:
    _, rom, _, family = audio_assets.load_profile_audio_assets('us', None)
    _, checked_rom, _, mp3 = mp3_assets.load_profile_mp3_assets('us', None)
    if checked_rom != rom:
        raise ValueError('audio ROM changed during boundary verification')
    start, end, splits = bank_layout(profile)
    sound_regions = None
    has_sound = any(name.startswith('audio/bank17/sound-bank/') for _, name in splits)
    has_samples = any(name.startswith('audio/bank17/samples/') for _, name in splits)
    if has_sound or has_samples:
        sound_bank_codec.verify_consumers(rom)
    if has_sound:
        sound_regions = sound_bank_codec.typed_regions(*(asset.data for asset in family.assets[:3]))
    adpcm_contract = None
    if has_samples:
        adpcm_contract = adpcm_layout.load_contract(ROOT)
    ranges = proven_ranges(rom, family, mp3, sound_regions=sound_regions, adpcm_contract=adpcm_contract)
    if (start != family.bank_start or end != family.bank_end
            or splits != [(begin, name) for begin, _, name in ranges]):
        raise ValueError('US YAML audio splits differ from loader-proven boundaries')
    return rom, ranges


if __name__ == '__main__':
    if sys.argv[1:] == ['list-bins']:
        print(' '.join('assets/' + name + '.bin' for _, name in bank_layout(ROOT / 'config/profiles/us.yaml')[2]))
    elif sys.argv[1:] == ['verify']:
        _, ranges = verify()
        print(f'Verified {len(ranges)} bank-17 YAML ranges ({sum(end - start for start, end, _ in ranges)} ROM bytes)')
    else:
        raise SystemExit('Use list-bins or verify')
