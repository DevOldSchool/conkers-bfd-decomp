"""Content identity for a glTF and the local buffers/images it imports."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path
from urllib.parse import unquote, urlsplit


def preview_fingerprint(path: Path) -> dict:
    path = path.resolve()
    data = path.read_bytes()
    document = json.loads(data)
    dependencies = {}
    for item in document.get("buffers", []) + document.get("images", []):
        uri = item.get("uri")
        if uri is None or uri.startswith("data:"):
            continue
        parsed = urlsplit(uri)
        relative = Path(unquote(parsed.path))
        # Scene exports share textures through ../textures within their output.
        if parsed.scheme or parsed.netloc or parsed.query or parsed.fragment or relative.is_absolute():
            raise ValueError(f"nonlocal glTF dependency: {uri}")
        target = (path.parent / relative).resolve()
        if not target.is_relative_to(path.parent.parent):
            raise ValueError(f"glTF dependency escapes preview output: {uri}")
        dependencies[uri] = hashlib.sha256(target.read_bytes()).hexdigest()
    return {
        "gltf_sha256": hashlib.sha256(data).hexdigest(),
        "dependencies_sha256": dict(sorted(dependencies.items())),
    }
