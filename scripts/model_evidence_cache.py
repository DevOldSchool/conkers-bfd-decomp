"""Run-scoped content snapshots and conservative local Python dependencies.

The validation coordinator uses two independent snapshots, before and after
workers. Shared inputs are read once per snapshot; hashes never survive a run.
Worker fingerprinting remains independent in model_preview_evidence.
"""
from __future__ import annotations

import ast
import hashlib
import json
from pathlib import Path
from urllib.parse import unquote, urlsplit


class ContentSnapshot:
    def __init__(self):
        self.hashes = {}
        self.documents = {}
        self.resolved = {}
        self.bytes_read = 0
        self.read_count = 0

    def _read(self, path):
        data = path.read_bytes()
        self.read_count += 1
        self.bytes_read += len(data)
        actual = hashlib.sha256(data).hexdigest()
        if path in self.hashes and self.hashes[path] != actual:
            raise ValueError(f'input changed within content snapshot: {path}')
        self.hashes[path] = actual
        return data

    def digest(self, path):
        path = self.resolve(path)
        if path not in self.hashes:
            self._read(path)
        return self.hashes[path]

    def fingerprint(self, path):
        path = self.resolve(path)
        if path not in self.documents:
            # Keep parsed glTF only, not the large shared binary/image payloads.
            self.documents[path] = json.loads(self._read(path))
        document = self.documents[path]
        dependencies = {}
        for item in document.get('buffers', []) + document.get('images', []):
            uri = item.get('uri')
            if uri is None or uri.startswith('data:'):
                continue
            parsed = urlsplit(uri)
            relative = Path(unquote(parsed.path))
            if parsed.scheme or parsed.netloc or parsed.query or parsed.fragment or relative.is_absolute():
                raise ValueError(f'nonlocal glTF dependency: {uri}')
            target = self.resolve(path.parent / relative)
            if not target.is_relative_to(path.parent.parent):
                raise ValueError(f'glTF dependency escapes preview output: {uri}')
            dependencies[uri] = self.digest(target)
        return {'gltf_sha256': self.hashes[path],
                'dependencies_sha256': dict(sorted(dependencies.items()))}

    def resolve(self, path):
        path = Path(path)
        if path not in self.resolved:
            target = path.resolve()
            self.resolved[path] = target
            self.resolved[target] = target
        return self.resolved[path]

    def verify(self, current):
        """Hash every input again once, even inputs used only by cached stages."""
        changed = []
        for path, expected in self.hashes.items():
            try:
                actual = current.digest(path)
            except OSError:
                actual = None
            if actual != expected:
                changed.append(str(path))
        return changed


def python_dependencies(root, entries):
    """Include transitive imports, including lazy and direct-script fallbacks.

    A dynamic import cannot be resolved statically: conservatively include all
    scripts. Missing literal local imports are recorded so adding them changes
    the identity. This is an invalidation boundary, never an execution sandbox.
    """
    root = Path(root)
    pending = list(entries)
    found = {}
    while pending:
        relative = str(pending.pop())
        if relative in found:
            continue
        path = root / relative
        found[relative] = path if path.is_file() else None
        if not path.is_file() or path.suffix != '.py':
            continue
        try:
            tree = ast.parse(path.read_text(), filename=relative)
        except SyntaxError as error:
            raise ValueError(f'cannot identify Python dependencies: {relative}: {error.msg}') from error
        for node in ast.walk(tree):
            names = []
            if isinstance(node, ast.Import):
                names = [a.name for a in node.names]
            elif isinstance(node, ast.ImportFrom):
                module = node.module or ''
                if node.level:
                    module = '.'.join(Path(relative).with_suffix('').parts[:-node.level]) + ('.' + module if module else '')
                names = [module] + [module + '.' + a.name for a in node.names]
            elif isinstance(node, ast.Call) and (isinstance(node.func, ast.Name) and node.func.id == '__import__'
                    or isinstance(node.func, ast.Attribute) and node.func.attr == 'import_module'):
                pending.extend(str(p.relative_to(root)) for p in (root / 'scripts').glob('*.py'))
            for name in names:
                if name.startswith('scripts.'):
                    parts = name.split('.')
                    pending.append('/'.join(parts[:2]) + '.py')
                elif name and '.' not in name and (root / 'scripts' / (name + '.py')).is_file():
                    pending.append('scripts/' + name + '.py')
    return found


def source_identity(root, entries, digest):
    return {name: digest(path) if path else None
            for name, path in sorted(python_dependencies(root, entries).items())}
