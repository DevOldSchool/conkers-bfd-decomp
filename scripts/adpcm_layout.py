"""Reviewed complete ADPCM frame extents, preserving raw tails and ambiguous frames."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
CONTRACT = Path('config/adpcm_reconstruction.us.json')


def part_name(sample, first_frame):
    if (type(sample) is not int or not 0 <= sample <= 9999
            or type(first_frame) is not int or not 0 <= first_frame <= 0xFFFFFFFF):
        raise ValueError('invalid ADPCM part selector')
    return f'audio/bank17/samples/{sample:04d}/{first_frame:08X}'


def load_contract(root):
    return json.loads((root / CONTRACT).read_text())


def selected_runs(samples, contract):
    if (not isinstance(contract, dict)
            or set(contract) != {'format', 'rom_sha1', 'sample_count', 'ambiguous_frames'}
            or contract['format'] != 'conker-adpcm-frames-v1'
            or contract['rom_sha1'] != ROM_SHA1
            or type(contract['sample_count']) is not int
            or contract['sample_count'] != len(samples)
            or not isinstance(contract['ambiguous_frames'], list)):
        raise ValueError('invalid ADPCM frame selection contract')
    excluded = {}
    previous = -1
    for row in contract['ambiguous_frames']:
        if (not isinstance(row, dict) or set(row) != {'sample', 'frames'}
                or type(row['sample']) is not int or not previous < row['sample'] < len(samples)
                or not isinstance(row['frames'], list) or not row['frames']):
            raise ValueError('invalid ADPCM excluded sample')
        sample = row['sample']
        frames = row['frames']
        count = samples[sample]['runtime_payload_length'] // 9
        if (any(type(frame) is not int or not 0 <= frame < count for frame in frames)
                or frames != sorted(set(frames))):
            raise ValueError('invalid ADPCM excluded frame')
        excluded[sample] = frames
        previous = sample
    result = []
    for index, sample in enumerate(samples):
        length = sample['runtime_payload_length']
        if (sample['index'] != index or sample['kind'] != 'adpcm'
                or type(length) is not int or length <= 0 or length % 9
                or length != sample['stored_length'] - sample['stored_length'] % 9):
            raise ValueError('unsupported native ADPCM sample extent')
        cursor = 0
        runs = []
        for frame in excluded.get(index, []):
            if cursor < frame:
                runs.append((cursor, frame))
            cursor = frame + 1
        if cursor < length // 9:
            runs.append((cursor, length // 9))
        result.append(runs)
    return result


def partition(asset, samples, contract):
    """Return all sample storage, crediting only complete reviewed frame runs."""
    if isinstance(contract, dict) and contract.get('format') == 'conker-adpcm-complete-samples-v2':
        rows = complete_samples(asset, samples, contract)
        return [(row['rom_start'], row['rom_end'], part_name(row['sample'], 0)) for row in rows]
    if (asset.compressed or asset.rom_end - asset.rom_start != len(asset.data)):
        raise ValueError('ADPCM storage must be raw ROM bytes')
    rows = []
    previous_sample_end = 0
    for sample, runs in zip(samples, selected_runs(samples, contract), strict=True):
        base = int(sample['base'], 16)
        end = base + sample['stored_length']
        if base < previous_sample_end or end > len(asset.data):
            raise ValueError('native ADPCM sample storage overlaps or exceeds its entry')
        previous_sample_end = end
        for first, stop in runs:
            rows.append((asset.rom_start + base + first * 9,
                         asset.rom_start + base + stop * 9, part_name(sample['index'], first)))
    result = []
    cursor = asset.rom_start
    for start, end, name in rows:
        if start < cursor or not start < end <= asset.rom_end:
            raise ValueError('ADPCM frame regions overlap or exceed storage')
        if cursor < start:
            result.append((cursor, start, f'audio/bank17/samples/raw/{cursor - asset.rom_start:08X}'))
        result.append((start, end, name))
        cursor = end
    if cursor < asset.rom_end:
        result.append((cursor, asset.rom_end, f'audio/bank17/samples/raw/{cursor - asset.rom_start:08X}'))
    return result


def complete_samples(asset, graph_samples, contract):
    if (not isinstance(contract, dict)
            or set(contract) != {'format','rom_sha1','sample_count','float32_headroom_samples'}
            or contract['format'] != 'conker-adpcm-complete-samples-v2'
            or contract['rom_sha1'] != ROM_SHA1
            or type(contract['sample_count']) is not int
            or contract['sample_count'] != len(graph_samples)
            or not isinstance(contract['float32_headroom_samples'],list)):
        raise ValueError('invalid complete ADPCM sample contract')
    indices = contract['float32_headroom_samples']
    if (any(type(index) is not int or not 0 <= index < len(graph_samples) for index in indices)
            or indices != sorted(set(indices))):
        raise ValueError('invalid headroom PCM source selection')
    wide = set(indices)
    if asset.compressed or asset.rom_end - asset.rom_start != len(asset.data):
        raise ValueError('native ADPCM storage must be raw')
    cursor = 0
    rows = []
    for index, sample in enumerate(graph_samples):
        base = int(sample['base'],16)
        payload = sample['runtime_payload_length']
        stored = sample['stored_length']
        if (sample['index'] != index or sample['kind'] != 'adpcm'
                or type(payload) is not int or payload <= 0 or payload % 9
                or type(stored) is not int or stored != (payload + 1) & ~1
                or base != cursor or base % 8):
            raise ValueError('native ADPCM sample disagrees with complete storage layout')
        end = (base + stored + 7) & ~7
        if end > len(asset.data) or any(asset.data[base + payload:end]):
            raise ValueError('ADPCM alignment bytes are not bounded zero padding')
        rows.append({'sample':index, 'rom_start':asset.rom_start + base,
                     'rom_end':asset.rom_start + end, 'runtime_bytes':payload,
                     'zero_padding_bytes':end-base-payload,
                     'pcm_format':'float32-headroom' if index in wide else 'pcm16',
                     'stored_sha256':hashlib.sha256(asset.data[base:end]).hexdigest()})
        cursor = end
    if cursor != len(asset.data):
        raise ValueError('native samples do not cover the complete ADPCM storage entry')
    return rows
