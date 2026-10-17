"""Receipts tying each rebuilt asset part to its inputs, encoder and output.

The asset build writes one receipt file per family under
``build/us/asset-receipts/``. The objdiff report may reuse a part's built output
instead of encoding it again only when it re-derives every receipt field from the
current checkout: the editable input hashes the encoder read, the encoder
module's own source hash (with its local imports) and the output's hash. Reuse
never skips the report's own comparison against the independently supplied ROM
bytes; it only replaces the encoding step with a hash check.
"""
from __future__ import annotations

import ast
from dataclasses import dataclass, field
from functools import lru_cache
import hashlib
import json
from pathlib import Path
import posixpath

SCHEMA = 1
DIRECTORY = Path('build/us/asset-receipts')
FRESH_ENCODE = 'fresh_encode'
REUSED_RECEIPT = 'reused_receipt'
CANDIDATE_SOURCES = (FRESH_ENCODE, REUSED_RECEIPT)


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


@lru_cache(maxsize=None)
def _local_imports(path: Path) -> list[str]:
    names = []
    try:
        tree = ast.parse(path.read_bytes(), filename=str(path))
    except SyntaxError:
        return names  # still hashed; it just cannot pull in further modules
    for node in ast.walk(tree):
        if isinstance(node, ast.Import):
            names.extend(alias.name for alias in node.names)
        elif isinstance(node, ast.ImportFrom) and node.module and not node.level:
            if node.module == 'scripts':
                names.extend(alias.name for alias in node.names)
            elif node.module.startswith('scripts.'):
                names.append(node.module.split('.', 1)[1])
            else:
                names.append(node.module)
    return [name.split('.', 1)[0] for name in names]


@lru_cache(maxsize=None)
def _encoder_modules(module: Path) -> tuple[Path, ...]:
    """Collect the encoder module and every script it imports, directly or not."""
    scripts = module.parent
    seen, queue = set(), [module]
    while queue:
        path = queue.pop()
        if path in seen:
            continue
        seen.add(path)
        for name in _local_imports(path):
            candidate = (scripts / (name + '.py')).resolve()
            if candidate.is_file() and candidate not in seen:
                queue.append(candidate)
    return tuple(sorted(seen))


def encoder_modules(root: Path, module: str) -> list[str]:
    """Repo-relative paths of the encoder module and its transitive local imports."""
    root = Path(root).resolve()
    return [path.relative_to(root).as_posix()
            for path in _encoder_modules((root / module).resolve())]


@lru_cache(maxsize=None)
def _file_sha256(path: Path) -> str:
    return sha256(path.read_bytes())


def encoder_fingerprint(root: Path, module: str, extra: tuple[str, ...] = ()) -> str:
    """Hash the encoder's source, its local imports and declared non-Python inputs.

    Both the asset build and the report derive this from the checkout, so a receipt
    written by one encoder revision never satisfies another. Files are read once
    per process; sources do not change while a build or report runs.
    """
    root = Path(root).resolve()
    digest = hashlib.sha256()
    for relative in sorted({*encoder_modules(root, module), *extra}):
        digest.update(relative.encode() + b'\0' + _file_sha256(root / relative).encode() + b'\0')
    return digest.hexdigest()


def source_root(root: Path, module: str) -> Path:
    """The checkout whose encoder would run: ``root`` when it holds the module, else this one.

    Builds and reports normally run from the checkout they write to. A caller
    (tests) that targets another root still fingerprints the encoder it imports.
    """
    root = Path(root).resolve()
    if (root / module).is_file():
        return root
    return Path(__file__).resolve().parent.parent


def receipt_path(root: Path, family: str) -> Path:
    if not family or family.startswith('/') or '..' in Path(family).parts:
        raise ValueError(f'invalid asset receipt family: {family!r}')
    return Path(root) / DIRECTORY / (family + '.json')


def part_record(*, output: Path | str, payload: bytes, source_inputs: dict[str, str],
                input_directory: Path | str, extent: dict, spans=None,
                matches_original: bool = True) -> dict:
    """Describe one reconstructed part: output, inputs and its ROM span proof.

    ``matches_original`` repeats the build's ROM comparison for the record only;
    the report compares a reused output against the ROM bytes itself.
    """
    if 'rom_ranges' in extent:
        proof = {'rom_ranges': extent['rom_ranges'], 'rom_start': extent['rom_start'],
                 'rom_end': extent['rom_end']}
    else:
        proof = {'rom_start': extent['rom_start'], 'rom_end': extent['rom_end']}
    record = {'output': Path(output).as_posix(), 'output_sha256': sha256(payload),
              'output_bytes': len(payload), 'input_directory': Path(input_directory).as_posix(),
              'source_inputs': dict(source_inputs), **proof, 'matches_original': bool(matches_original)}
    if spans is not None:
        record['spans'] = [[offset, len(data)] for offset, data in spans]
    return record


@dataclass
class Receipts:
    family: str
    path: str
    encoder_module: str
    encoder_extra: tuple[str, ...]
    encoder_sha256: str
    parts: dict[str, dict] = field(default_factory=dict)

    def get(self, name: str) -> dict | None:
        return self.parts.get(name)

    @property
    def header(self) -> dict:
        return {'family': self.family, 'path': self.path, 'encoder_module': self.encoder_module,
                'encoder_extra': list(self.encoder_extra), 'encoder_sha256': self.encoder_sha256}


def empty(family: str = '') -> Receipts:
    return Receipts(family, '', '', (), '')


def write(root: Path, family: str, module_file: Path | str, parts: dict[str, dict], *,
          extra: tuple[str, ...] = (), merge: bool = False) -> Path:
    """Record a family's verified parts; ``merge`` keeps other parts of the same encoder.

    ``module_file`` is the encoder's ``__file__``; its checkout, not ``root``, holds
    the encoder source, so builds into another root (tests) still fingerprint it.
    """
    root = Path(root)
    module_file = Path(module_file).resolve()
    source_root = module_file.parent.parent
    module = module_file.relative_to(source_root).as_posix()
    fingerprint = encoder_fingerprint(source_root, module, tuple(extra))
    merged = {}
    if merge:
        previous = load(root, family, module, extra=tuple(extra), fingerprint=fingerprint)
        merged.update(previous.parts)
    merged.update(parts)
    for name, part in merged.items():
        for key in ('output', 'output_sha256', 'source_inputs', 'rom_start', 'rom_end'):
            if key not in part:
                raise ValueError(f'asset receipt {family}/{name} lacks {key}')
    path = receipt_path(root, family)
    payload = {'schema': SCHEMA, 'family': family, 'encoder_module': module,
               'encoder_extra': sorted(extra), 'encoder_sha256': fingerprint,
               'parts': dict(sorted(merged.items()))}
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + '.tmp')
    temporary.write_text(json.dumps(payload, indent=2, sort_keys=True) + '\n')
    temporary.replace(path)
    return path


def load(root: Path, family: str, module: str, *, extra: tuple[str, ...] = (),
         fingerprint: str | None = None) -> Receipts:
    """Load a family's receipts only if the current encoder re-derives their fingerprint.

    Anything missing, malformed or written by another encoder revision yields no
    parts, so every such part is encoded afresh.
    """
    root = Path(root)
    path = receipt_path(root, family)
    try:
        document = json.loads(path.read_text())
    except (OSError, ValueError):
        return empty(family)
    if (not isinstance(document, dict) or document.get('schema') != SCHEMA
            or document.get('family') != family or document.get('encoder_module') != module
            or not isinstance(document.get('parts'), dict)
            or not isinstance(document.get('encoder_extra'), list)
            or sorted(document['encoder_extra']) != sorted(extra)
            or any(not isinstance(part, dict) for part in document['parts'].values())):
        return empty(family)
    if fingerprint is None:
        try:
            fingerprint = encoder_fingerprint(source_root(root, module), module, tuple(extra))
        except OSError:
            return empty(family)
    if document.get('encoder_sha256') != fingerprint:
        return empty(family)
    return Receipts(family, path.relative_to(root).as_posix(), module, tuple(sorted(extra)),
                    fingerprint, document['parts'])


@dataclass
class Reused:
    packed: bytes
    spans: list | None
    provenance: dict


def _find(receipts, name: str) -> tuple[Receipts | None, dict | None]:
    """Look a part up in one family's receipts or, in order, in several files of one family."""
    for group in (receipts,) if isinstance(receipts, Receipts) else tuple(receipts):
        part = group.get(name)
        if part is not None:
            return group, part
    return None, None


def _extent_matches(part: dict, extent: dict) -> bool:
    if part.get('rom_start') != extent.get('rom_start') or part.get('rom_end') != extent.get('rom_end'):
        return False
    return 'rom_ranges' not in extent or part.get('rom_ranges') == extent['rom_ranges']


def reusable(root: Path, receipts: Receipts, name: str, *, hashes: dict[str, str],
             extent: dict, fresh: bool = False, ranged: bool = False) -> Reused | None:
    """Return the built output when its receipt re-derives from the current checkout.

    Reuse needs the receipt's input hashes to equal the freshly read ones, its ROM
    span to equal the reviewed extent, and the output file to hash as recorded.
    ``fresh`` disables reuse so the caller encodes everything again.
    """
    receipts, part = _find(receipts, name) if not fresh else (None, None)
    if (part is None or part.get('source_inputs') != hashes or not _extent_matches(part, extent)
            or (ranged and not isinstance(part.get('spans'), list))):
        return None
    try:
        output = Path(root) / part['output']
        data = output.read_bytes()
    except (OSError, TypeError, KeyError):
        return None
    if sha256(data) != part.get('output_sha256') or len(data) != part.get('output_bytes', len(data)):
        return None
    spans = None
    if ranged:
        spans = []
        for row in part['spans']:
            if (not isinstance(row, list) or len(row) != 2 or any(type(v) is not int for v in row)
                    or row[0] < 0 or row[1] <= 0 or row[0] + row[1] > len(data)):
                return None
            spans.append((row[0], data[row[0]:row[0] + row[1]]))
    directory = Path(part.get('input_directory', ''))
    provenance = {'candidate_source': REUSED_RECEIPT,
                  'receipt': {**receipts.header, 'part': name, 'output': part['output'],
                              'output_sha256': part['output_sha256'],
                              'input_directory': directory.as_posix(),
                              # Repo-relative like the unit's own inputs; some encoders
                              # name inputs outside their directory with '..'.
                              'source_inputs': {posixpath.normpath((directory / p).as_posix()): h
                                                for p, h in part['source_inputs'].items()}}}
    return Reused(data, spans, provenance)


def fresh_provenance() -> dict:
    return {'candidate_source': FRESH_ENCODE}


def candidate(root: Path, receipts: Receipts, name: str, *, hashes: dict[str, str], extent: dict,
              encode, fresh: bool = False, ranged: bool = False):
    """Reuse a receipt-backed output or run ``encode``; returns ``(packed, [spans,] hashes, provenance)``."""
    reused = reusable(root, receipts, name, hashes=hashes, extent=extent, fresh=fresh, ranged=ranged)
    if reused is not None:
        if ranged:
            return reused.packed, reused.spans, hashes, reused.provenance
        return reused.packed, hashes, reused.provenance
    result = encode()
    return (*result, fresh_provenance())


def verify_reused(root: Path, unit: dict) -> None:
    """Refuse a reused candidate whose receipt no longer re-derives from the checkout.

    The report calls this after objdiff ran, so credit rests on inputs, encoder
    and output bytes that are all still present and unchanged.
    """
    receipt = unit.get('receipt')
    if unit.get('candidate_source') != REUSED_RECEIPT:
        return
    if not isinstance(receipt, dict):
        raise ValueError(f'{unit.get("key")}: reused candidate lacks its receipt')
    root = Path(root)
    expected = encoder_fingerprint(source_root(root, receipt['encoder_module']), receipt['encoder_module'],
                                   tuple(receipt.get('encoder_extra', ())))
    if receipt.get('encoder_sha256') != expected:
        raise ValueError(f'{unit.get("key")}: receipt encoder differs from the current checkout')
    if sha256((root / receipt['output']).read_bytes()) != receipt.get('output_sha256'):
        raise ValueError(f'{unit.get("key")}: receipt output differs from the built file')
    if receipt.get('output_sha256') != unit.get('payload_sha256'):
        raise ValueError(f'{unit.get("key")}: receipt output differs from the compared candidate')
    for path, digest in unit.get('source_inputs', {}).items():
        if sha256((root / path).read_bytes()) != digest:
            raise ValueError(f'{unit.get("key")}: receipt input changed: {path}')
