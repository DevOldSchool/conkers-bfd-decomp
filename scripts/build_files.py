"""Preserve timestamps when generated build contents are unchanged."""
from pathlib import Path
from functools import lru_cache
import hashlib


def write_if_changed(path: Path, payload: bytes) -> bool:
    if path.is_file() and path.read_bytes() == payload:
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + '.tmp')
    temporary.write_bytes(payload)
    temporary.replace(path)
    return True


@lru_cache(maxsize=256)
def _sha256_at(path, signature):
    digest = hashlib.sha256(path.read_bytes()).hexdigest()
    if file_signature(path) != signature:
        raise ValueError(f'{path}: file changed while hashing')
    return digest


def file_signature(path):
    stat = path.stat()
    return (stat.st_dev, stat.st_ino, stat.st_size, stat.st_mtime_ns, stat.st_ctime_ns, stat.st_mode)


def cached_sha256(path):
    """Reuse a process-local digest only while the file identity is unchanged."""
    path = Path(path).resolve()
    return _sha256_at(path, file_signature(path))
