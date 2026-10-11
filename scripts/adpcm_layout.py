"""Reviewed complete ADPCM samples and native zero alignment."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

ROM_SHA1 = '4cbadd3c4e0729dec46af64ad018050eada4f47a'
CONTRACT = Path('config/adpcm_reconstruction.us.json')


def part_name(sample, first_frame):
    if (type(sample) is not int or not 0 <= sample <= 9999
            or type(first_frame) is not int or first_frame != 0):
        raise ValueError('invalid ADPCM part selector')
    return f'audio/bank17/samples/{sample:04d}/{first_frame:08X}'


def load_contract(root):
    return json.loads((root / CONTRACT).read_text())


def partition(asset, samples, contract):
    rows = complete_samples(asset, samples, contract)
    return [(row['rom_start'], row['rom_end'], part_name(row['sample'], 0)) for row in rows]


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
