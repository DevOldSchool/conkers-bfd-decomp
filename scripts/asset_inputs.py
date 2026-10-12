"""Shared source validation, recovery and publication for reconstructed assets."""
import hashlib
import json
from pathlib import Path
import shutil
import tempfile

try:
    from scripts import texture_build
except ModuleNotFoundError:
    import texture_build


def manifest_hashes(directory, expected, names, label):
    if json.loads((directory / 'manifest.json').read_text()) != expected:
        raise ValueError(f'{label} manifest differs from reviewed ROM contract')
    return {name: hashlib.sha256((directory / name).read_bytes()).hexdigest() for name in names}


def recover_directory(directory, backups, prefix, files):
    """Stage a complete replacement before backing up and replacing the old tree."""
    if directory.is_symlink() or (directory.exists() and not directory.is_dir()):
        raise ValueError(f'refusing recovery of a non-directory or symlink: {directory}')
    directory.parent.mkdir(parents=True, exist_ok=True)
    staging = Path(tempfile.mkdtemp(prefix='.restore-', dir=directory.parent))
    prepared = staging / 'inputs'
    backup = None
    try:
        groups = {}
        for name, data in files.items():
            path = Path(name)
            if path.is_absolute() or '..' in path.parts:
                raise ValueError('invalid recovery source path')
            groups.setdefault(path.parent, {})[path.name] = data
        for parent, contents in (groups or {Path('.'): {}}).items():
            texture_build.publish_inputs(prepared / parent, contents)
        if directory.exists():
            backups.mkdir(parents=True, exist_ok=True)
            backup = Path(tempfile.mkdtemp(prefix=prefix, dir=backups)) / 'inputs'
            directory.rename(backup)
        try:
            prepared.rename(directory)
        except Exception:
            if backup is not None and not directory.exists():
                backup.rename(directory)
            raise
    finally:
        shutil.rmtree(staging)
    return str(backup) if backup is not None else None


def check_batch_sources(candidates, input_hashes, label):
    """Validate all sources before publishing any candidate from a batch."""
    for expected, directory, _, hashes in candidates:
        if input_hashes(directory, expected) != hashes:
            raise ValueError(f'{label} inputs changed during batch packing')
