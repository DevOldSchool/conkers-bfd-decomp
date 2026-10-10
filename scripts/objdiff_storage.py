"""Account for bounded ROM asset storage without granting reconstruction credit."""
from __future__ import annotations

import hashlib
from pathlib import Path
import subprocess

from elf_sections import sections
import objdiff_targets
import rzip_archive

CATEGORIES = [('assets', 'Stored assets'), ('assets-flat', 'Flat assets'),
              ('assets-models', 'Model banks'), ('assets-animations', 'Animation bank'),
              ('assets-audio', 'Audio banks'), ('assets-other', 'Other asset storage')]


def regions(rom: bytes, layout: dict) -> list[dict]:
    """Derive disjoint storage extents from the checked ROM's archive table.

    Bank extents include their indices and gaps. Decoded resources inside them
    are not additional allocations. CPU archive backing is deliberately absent.
    """
    if hashlib.sha1(rom).hexdigest() not in layout['normalized_sha1']:
        raise ValueError('storage reference ROM checksum differs from reviewed layout')
    font_start, font_end = layout['font_start'], layout['font_storage_end']
    flat_start, flat_end, table = (layout[k] for k in
                                 ('flat_assets_start', 'flat_assets_end', 'asset_table'))
    if not 0 <= font_start < font_end <= flat_start < flat_end <= table < len(rom):
        raise ValueError('invalid or overlapping font/flat storage ranges')
    # Exact decoder consumption independently checks the flat stream endpoint.
    for _ in rzip_archive.iter_flat_rzip_entries(rom[flat_start:flat_end]):
        pass
    banks = rzip_archive.parse_asset_banks(rom, table)
    result = []

    def add(key, start, end, category):
        if start < end:
            result.append({'key': key, 'rom_start': start, 'rom_end': end,
                           'category': category})

    add('font', font_start, font_end, 'assets-other')
    add('flat', flat_start, flat_end, 'assets-flat')
    add('flat-alignment', flat_end, table, 'assets-other')
    cursor = table + len(banks) * 8
    add('bank-index', table, cursor, 'assets-other')
    for bank in banks:
        # The checked US table is contiguous; preserve any bounded interbank gap.
        add(f'before-bank{bank.index:02X}', cursor, bank.start, 'assets-other')
        rzip_archive.parse_asset_entries(rom, bank)
        category = ('assets-models' if bank.index in (1, 3, 4, 9) else
                    'assets-animations' if bank.index == 2 else
                    'assets-audio' if bank.index in (0x16, 0x17) else 'assets-other')
        add(f'bank{bank.index:02X}', bank.start, bank.end, category)
        cursor = bank.end
    return result


def partition(regions: list[dict], rebuilt: list[dict]) -> list[dict]:
    """Subtract proved candidate extents exactly once and retain every remainder."""
    ordered = sorted(regions, key=lambda r: r['rom_start'])
    previous = -1
    for region in ordered:
        start, end = region['rom_start'], region['rom_end']
        if start < 0 or start >= end or start < previous:
            raise ValueError('invalid or overlapping storage regions')
        previous = end
    selected = sorted(rebuilt, key=lambda u: u['rom_start'])
    previous = -1
    by_region = {r['key']: [] for r in ordered}
    if len(by_region) != len(ordered):
        raise ValueError('duplicate storage region keys')
    for unit in selected:
        start, end = unit['rom_start'], unit['rom_end']
        if start < previous or start >= end or unit['size'] != end - start:
            raise ValueError('invalid or overlapping rebuilt storage ranges')
        owners = [r for r in ordered if r['rom_start'] <= start < end <= r['rom_end']]
        if len(owners) != 1:
            raise ValueError('rebuilt storage must belong to exactly one bounded region')
        by_region[owners[0]['key']].append(unit)
        previous = end
    result = []
    for region in ordered:
        cursor, spans = region['rom_start'], []
        for unit in by_region[region['key']]:
            if cursor < unit['rom_start']:
                spans.append([cursor, unit['rom_start']])
            cursor = unit['rom_end']
        if cursor < region['rom_end']:
            spans.append([cursor, region['rom_end']])
        rebuilt_bytes = sum(u['size'] for u in by_region[region['key']])
        unmatched_bytes = sum(end - start for start, end in spans)
        if rebuilt_bytes + unmatched_bytes != region['rom_end'] - region['rom_start']:
            raise ValueError('storage partition does not cover its complete region')
        result.append({**region, 'unreconstructed_ranges': spans,
                       'rebuilt_bytes': rebuilt_bytes, 'unreconstructed_bytes': unmatched_bytes})
    return result


def prepare_remainder(rom: bytes, region: dict, output: Path) -> tuple[dict, dict]:
    """Wrap only an independent target; raw ROM backing is never a candidate.

    One target per region concatenates its uncredited spans in ROM order. The
    provenance retains each physical span; this does not imply contiguous bytes
    or an original object boundary.
    """
    key = 'storage/' + region['key']
    directory = output / key
    directory.mkdir(parents=True, exist_ok=True)
    spans = region['unreconstructed_ranges']
    payload = b''.join(rom[start:end] for start, end in spans)
    if not payload or len(payload) != region['unreconstructed_bytes']:
        raise ValueError('unreconstructed target extent differs from storage partition')
    (directory / 'unreconstructed.bin').write_bytes(payload)
    subprocess.run(['mips-linux-gnu-ld', '-r', '-b', 'binary', '-m', 'elf32btsmip',
                    '-o', 'target.o', 'unreconstructed.bin'], cwd=directory, check=True)
    target = directory / 'target.o'
    allocated = {name: data for name, (header, data) in sections(target.read_bytes(), 1).items()
                 if header[2] & 2 and header[5]}
    if allocated != {'.data': payload}:
        raise ValueError('stored-asset target differs from original ROM spans')
    unit = {'key': key, 'kind': 'unreconstructed_asset', 'section': '.data',
            'size': len(payload), 'rom_ranges': spans, 'storage_region': region['key'],
            'target_path': key + '/target.o', 'target_sha256': objdiff_targets.sha256(target),
            'payload_sha256': hashlib.sha256(payload).hexdigest(),
            'report_code_bytes': 0, 'report_data_bytes': len(payload), 'complete': False}
    item = {'name': 'assets/storage/' + region['key'] + '/unreconstructed',
            'target_path': unit['target_path'],
            'metadata': {'complete': False, 'progress_categories': ['data', 'assets', region['category']]}}
    return unit, item


def prepare(rom: bytes, layout: dict, rebuilt: list[dict], configs: list[dict], *,
            output: Path) -> tuple[list[dict], list[dict], dict]:
    plan = partition(regions(rom, layout), rebuilt)
    for unit, config in zip(rebuilt, configs, strict=True):
        owner = next(r for r in plan if r['rom_start'] <= unit['rom_start'] < unit['rom_end'] <= r['rom_end'])
        config['metadata']['progress_categories'] = ['data', 'assets', owner['category']]
    pairs = [prepare_remainder(rom, r, output) for r in plan if r['unreconstructed_bytes']]
    proof = {'rom_sha1': hashlib.sha1(rom).hexdigest(), 'regions': plan,
             'stored_asset_bytes': sum(r['rom_end'] - r['rom_start'] for r in plan),
             'rebuilt_asset_bytes': sum(r['rebuilt_bytes'] for r in plan),
             'unreconstructed_asset_bytes': sum(r['unreconstructed_bytes'] for r in plan)}
    return [u for u, _ in pairs], [c for _, c in pairs], proof
