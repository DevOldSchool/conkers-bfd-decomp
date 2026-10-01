"""Dispatch guarded captured-appearance and ROM-consumer inspection presets."""
from __future__ import annotations

import argparse
import importlib
from pathlib import Path
import sys

PRESETS = {
    'scene60-captured-primary-opacity255': 'scripts.model_scene60_appearance',
    'haybot-captured-selector15': 'scripts.model_haybot_appearance',
    'library-bat155-captured-primary-opacity255': 'scripts.model_library_bat155_appearance',
    'shc-boat-captured-parent42': 'scripts.model_shc_boat_appearance',
    'haybot-rom-selector-variants': 'scripts.model_haybot_rom_variants',
}


def main(argv=None):
    arguments = list(sys.argv[1:] if argv is None else argv)
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--preset', required=True, choices=tuple(PRESETS))
    parser.add_argument('--rom', type=Path, help='authorized local US ROM')
    parser.add_argument('--textures', type=Path, help='local proven texture catalogs')
    parser.add_argument('--output', type=Path, required=True, help='new directory below build/')
    parser.add_argument('--verify', action='store_true', help='verify an existing export without overwriting it')
    args = parser.parse_args(arguments)
    try:
        module = importlib.import_module(PRESETS[args.preset])
        return module.main(arguments)
    except (OSError, ValueError) as error:
        parser.exit(1, f'appearance: {error}\n')


if __name__ == '__main__':
    raise SystemExit(main())
