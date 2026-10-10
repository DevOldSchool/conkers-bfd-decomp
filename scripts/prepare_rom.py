#!/usr/bin/env python3
"""Cache a ROM split by its configuration, toolchain and generated contents.

Code compilation remains Make's responsibility. Editable reconstruction inputs
are not part of this cache. A split never establishes asset reconstruction credit.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.metadata
import json
from pathlib import Path
import shutil
import subprocess

from build_files import write_if_changed
from profile_config import render_original_profile, render_profile
import yaml


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def signature(configuration: dict, rendered: str) -> str:
    options = configuration['options']
    paths = {Path(options['target_path']), Path('scripts/prepare_rom.py'),
             Path('scripts/profile_config.py'), Path('scripts/build_files.py'),
             Path('toolchain/tools.lock.json'), Path('toolchain/python-requirements.txt')}
    for key in ('symbol_addrs_path', 'reloc_addrs_path'):
        value = options.get(key, [])
        paths.update(map(Path, [value] if isinstance(value, str) else value))
    inputs = {str(path): digest(path) for path in sorted(paths)}
    inputs['rendered'] = rendered
    inputs['splat-version'] = importlib.metadata.version('splat64')
    return hashlib.sha256(json.dumps(inputs, sort_keys=True).encode()).hexdigest()


def assembly_paths(profile: str) -> list[Path]:
    return sorted(p for p in Path(f'asm/{profile}').rglob('*.s') if 'nonmatchings' not in p.parts)


def generated_paths(configuration: dict, materialized: Path, profile: str) -> list[Path]:
    paths = [materialized, Path(configuration['options']['ld_script_path'])]
    paths.extend(assembly_paths(profile))
    # The header source is generated once by Splat and then compiled by Make.
    paths.append(Path('src/header.c'))
    for segment in configuration['segments']:
        if not isinstance(segment, dict):
            continue
        if segment.get('type') == 'bin':
            name = segment.get('name') or f"{segment['start']:X}"
            paths.append(Path('assets') / (name + '.bin'))
        elif segment.get('type') == 'group':
            paths.extend(Path('assets') / (row[2] + '.bin') for row in segment['subsegments'])
    return sorted(set(paths))


def cache_valid(stamp: Path, expected: str, profile: str) -> bool:
    try:
        record = json.loads(stamp.read_text())
        if record['signature'] != expected:
            return False
        outputs = record['outputs']
        if not isinstance(outputs, dict) or not all(isinstance(p, str) and isinstance(v, str) for p, v in outputs.items()):
            return False
        current_assembly = {str(p) for p in assembly_paths(profile)}
        saved_assembly = {p for p in outputs if p.startswith(f'asm/{profile}/')}
        if current_assembly != saved_assembly:
            return False
        return bool(outputs) and all(digest(Path(path)) == value for path, value in outputs.items())
    except (OSError, ValueError, KeyError, TypeError):
        return False


def prepare(profile: str, *, assets: bool = False, refresh: bool = False) -> None:
    template = Path(f'config/profiles/{profile}.yaml')
    target = f'roms/baserom.{profile}.z64'
    renderer = render_profile if assets else render_original_profile
    rendered = renderer(template, target)
    configuration = yaml.safe_load(rendered)
    mode = 'rebuilt' if assets else 'original'
    materialized = Path(f'build/config/{profile}' + ('' if assets else '.original-assets') + '.yaml')
    stamp = Path(f'build/{profile}/.prepared-{mode}.json')
    expected = signature(configuration, rendered)
    if not refresh and cache_valid(stamp, expected, profile):
        print(f'ROM preparation: cached ({mode} assets)', flush=True)
        return
    # Invalidate before destructive work; an interrupted split is never reusable.
    stamp.unlink(missing_ok=True)
    shutil.rmtree(f'asm/{profile}', ignore_errors=True)
    write_if_changed(materialized, rendered.encode())
    subprocess.run(['splat', 'split', str(materialized)], check=True)
    outputs = {str(path): digest(path) for path in generated_paths(configuration, materialized, profile)}
    write_if_changed(stamp, (json.dumps(dict(signature=expected, outputs=outputs), sort_keys=True) + '\n').encode())
    print(f'ROM preparation: refreshed ({mode} assets)', flush=True)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('profile', choices=('us', 'eu'))
    parser.add_argument('--assets', action='store_true')
    parser.add_argument('--refresh', action='store_true')
    args = parser.parse_args()
    try:
        prepare(args.profile, assets=args.assets, refresh=args.refresh)
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        parser.exit(1, f'ROM preparation failed: {error}\n')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
