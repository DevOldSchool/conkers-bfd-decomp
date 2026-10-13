"""Preserve local editable debugger inputs, including before make clean.

This module uses only the standard library; migration never reads a ROM or
imports reconstruction tooling and never overwrites an existing editable file.
"""
from pathlib import Path
import shutil

DIRECTORY = Path('.conker/debugger-assets/us')
LEGACY_DIRECTORY = Path('build/us/debugger-assets')
INPUTS = ('glyphs.pgm', 'strings.json')


def migrate(root: Path) -> bool:
    directory = root / DIRECTORY
    present = [(directory / name).exists() for name in INPUTS]
    if all(present):
        return True
    if any(present):
        raise ValueError('partial editable debugger inputs; restore the missing file (no automatic re-extraction)')
    legacy = root / LEGACY_DIRECTORY
    old = [(legacy / name).exists() for name in INPUTS]
    if any(old):
        if not all(old):
            raise ValueError('partial legacy debugger inputs; restore both files before migration')
        directory.mkdir(parents=True, exist_ok=True)
        for name in INPUTS:
            with (directory / name).open('xb') as destination:
                with (legacy / name).open('rb') as source:
                    shutil.copyfileobj(source, destination)
        return True
    return False


if __name__ == '__main__':
    migrate(Path.cwd())
