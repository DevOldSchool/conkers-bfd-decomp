"""Preserve timestamps when generated build contents are unchanged."""
from pathlib import Path


def write_if_changed(path: Path, payload: bytes) -> bool:
    if path.is_file() and path.read_bytes() == payload:
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + '.tmp')
    temporary.write_bytes(payload)
    temporary.replace(path)
    return True
