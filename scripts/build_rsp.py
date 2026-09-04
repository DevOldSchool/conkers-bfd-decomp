#!/usr/bin/env python3
"""Assemble RSP sources, compare independent ROM bytes, then stage ELF members."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parent.parent
ARMIPS_REVISION_FILE = Path("/opt/armips/revision")


def verify_payload(payload: bytes, reference: bytes, expected_md5: str, name: str) -> None:
    if hashlib.md5(reference).hexdigest() != expected_md5:
        raise ValueError(f"{name}: independent ROM range checksum differs from reviewed evidence")
    if payload != reference:
        first = next((i for i, (a, b) in enumerate(zip(payload, reference)) if a != b),
                     min(len(payload), len(reference)))
        raise ValueError(f"{name}: payload mismatch at +0x{first:X}; "
                         f"produced 0x{len(payload):X}, expected 0x{len(reference):X} bytes")


def verify_ownership(size: int, spans: list[tuple[int, int]], name: str) -> None:
    end = 0
    for start, next_end in sorted(spans):
        if start != end or next_end <= start:
            raise ValueError(f'{name}: missing or overlapping payload ownership')
        end = next_end
    if end != size:
        raise ValueError(f'{name}: assembler output contains unowned bytes')


def main() -> int:
    config = json.loads((ROOT / 'config/rsp/us.json').read_text())
    lock = json.loads((ROOT / 'toolchain/tools.lock.json').read_text())
    revision = lock['tools']['armips']['revision']
    if ARMIPS_REVISION_FILE.read_text().strip() != revision:
        raise ValueError('RSP assembler revision does not match toolchain lock')
    rom = (ROOT / 'roms/baserom.us.z64').read_bytes()
    if hashlib.sha1(rom).hexdigest() != config['rom_sha1']:
        raise ValueError('US ROM SHA-1 does not match reviewed RSP reference')
    output = ROOT / 'build/rsp/us'
    output.mkdir(parents=True, exist_ok=True)
    archive = ROOT / 'build/us/lib/librsp.a'
    archive.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='.assemble-', dir=output) as tmp:
        staging = Path(tmp)
        for source in config['sources']:
            command = ['/opt/armips/armips', '-strequ', 'CODE_FILE', str(staging / source['code'])]
            if 'data' in source:
                command += ['-strequ', 'DATA_FILE', str(staging / source['data'])]
            command += ['-sym2', str(staging / (Path(source['path']).stem + '.sym')), source['path']]
            subprocess.run(command, cwd=ROOT, check=True)
        # Check original assembler files before writing member slices. A member
        # can share its filename with a source output; checking later could
        # hide an extra tail after that source output has been overwritten.
        for source in config['sources']:
            for key in ('code', 'data'):
                if key not in source:
                    continue
                filename = source[key]
                spans = sorted((p['offset'], p['offset'] + p['end'] - p['start'])
                               for p in config['payloads'] if p['file'] == filename)
                verify_ownership(len((staging / filename).read_bytes()), spans, filename)
        objects = []
        comparisons = []
        for item in config['payloads']:
            size = item['end'] - item['start']
            produced = (staging / item['file']).read_bytes()
            payload = produced[item['offset']:item['offset'] + size]
            verify_payload(payload, rom[item['start']:item['end']], item['md5'], item['name'])
            binary = staging / (item['name'] + '.bin')
            binary.write_bytes(payload)
            obj = staging / (item['name'] + '.o')
            flags = 'alloc,load,readonly,code,contents' if item['kind'] == 'code' else 'alloc,load,readonly,data,contents'
            subprocess.run(['mips-linux-gnu-objcopy', '-I', 'binary', '-O', 'elf32-tradbigmips', '-B', 'mips',
                            '--set-section-alignment', '.data=16', '--rename-section',
                            f".data={item['section']},{flags}", binary.name, obj.name], cwd=staging, check=True)
            objects.append(obj)
            comparisons.append({'name': item['name'], 'bytes': size, 'md5': item['md5'], 'kind': item['kind']})
            print(f"{item['name']}: 0x{size:X} bytes identical; MD5 {item['md5']}", flush=True)
        subprocess.run(['mips-linux-gnu-ar', 'crs', str(staging / 'librsp.a'),
                        *map(str, objects)], check=True)
        for path in staging.iterdir():
            if path.name != 'librsp.a':
                path.replace(output / path.name)
        (staging / 'librsp.a').replace(archive)
        (output / 'comparisons.json').write_text(json.dumps({'armips_revision': revision,
            'rom_sha1': config['rom_sha1'], 'payloads': comparisons}, indent=2) + '\n')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        raise SystemExit(str(error)) from error
