"""Captured Library155 primary material inspection."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
from scripts import model_scene60_appearance as scene

PRESET = 'library-bat155-captured-primary-opacity255'
CONTRACT_PATH = scene.ROOT / 'config/model-library-bat155-captured-appearance.json'
CONTRACT_SHA256 = 'c76d57ac2f0ab37e27aad6f98829d598c5c26d3fafc06f0dec18a8d596a6f2dd'


def contract():
    raw = CONTRACT_PATH.read_bytes()
    if hashlib.sha256(raw).hexdigest() != CONTRACT_SHA256:
        raise ValueError('captured library155 appearance contract changed')
    evidence = json.loads(raw)
    evidence['contract_sha256'] = CONTRACT_SHA256
    return evidence


def guard(evidence):
    if evidence != contract():
        raise ValueError('captured library155 evidence changed')
    if evidence['preset'] != PRESET or set(evidence['models']) != {'155'}:
        raise ValueError('captured library155 selection changed')
    scene.context_guard(155, evidence['models']['155'], evidence)


def build_files(rom, texture_root):
    evidence = contract()
    guard(evidence)
    return scene.build_files(rom, texture_root, evidence)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--preset', required=True, choices=[PRESET])
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--textures', type=Path, default=scene.ROOT / 'build/assets/textures')
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--verify', action='store_true')
    args = parser.parse_args(argv)
    output = args.output.resolve()
    if not output.is_relative_to((scene.ROOT / 'build').resolve()) or output == (scene.ROOT / 'build').resolve():
        raise ValueError('appearance output must be a child of build/')
    files, checked, manifest = build_files(args.rom, args.textures)
    if not args.verify:
        output.mkdir(parents=True, exist_ok=False)
        for name, data in files.items():
            path = output / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
    reports = scene.verify_files(output, files, checked, manifest)
    print(f'Verified captured Library155 inspection: 186 linked faces; source faces {[r["faces"] for r in reports.values()]}')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
