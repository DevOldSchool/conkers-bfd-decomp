"""Evidence for retained handwritten US assembly, separate from C matches."""
from __future__ import annotations

import hashlib
import json
import re
from pathlib import Path

from candidate_tables import Object32
import linked_aliases
import rom_span


def validate_metadata(entry: dict) -> None:
    original = entry.get("original_asm")
    regions = entry["regions"]
    active = regions["us"]["state"] == "original_asm"
    if not active:
        if original is not None:
            raise ValueError("original assembly metadata requires original_asm state")
        return
    if entry.get("blocked") or entry.get("deferred") or entry.get("overlay") != "game":
        raise ValueError("verified original assembly must be a non-deferred US game span")
    if not isinstance(original, dict):
        raise ValueError("original assembly requires classification evidence")
    for key in ("reason", "reference", "recorded_revision"):
        if not isinstance(original.get(key), str) or not original[key].strip():
            raise ValueError(f"original assembly classification needs {key}")
    evidence = regions["us"].get("evidence", {})
    if not isinstance(evidence, dict):
        raise ValueError("original assembly evidence must be an object")
    if "current_differences" in evidence:
        raise ValueError("original assembly must not claim C CURRENT evidence")
    for key, length in (("rom_sha1", 40), ("span_sha256", 64), ("assembly_sha256", 64)):
        if not re.fullmatch(r"[0-9a-f]{" + str(length) + "}", str(evidence.get(key, ""))):
            raise ValueError(f"original assembly evidence needs {key}")
    if not evidence.get("verified_revision"):
        raise ValueError("original assembly evidence needs verified_revision")


def validate_source(root: Path, entry: dict) -> None:
    import project_state
    source = entry.get("source")
    if not isinstance(source, str) or not (root / source).is_file():
        raise ValueError("original assembly needs its assigned source")
    symbol = entry["regions"]["us"]["symbol"]
    if project_state.global_asm_pragma(source, symbol) not in (root / source).read_text():
        raise ValueError("original assembly must retain its canonical GLOBAL_ASM")
    if entry.get("original_asm"):
        reference = (root / entry["original_asm"]["reference"]).resolve()
        if not reference.is_relative_to(root.resolve()) or not reference.is_file():
            raise ValueError("original assembly requires an existing repository evidence document")
        assembly = root / project_state.nonmatching_asm_path(source, symbol)
        if assembly.is_file() and hashlib.sha256(assembly.read_bytes()).hexdigest() != entry["regions"]["us"]["evidence"]["assembly_sha256"]:
            raise ValueError("retained original assembly changed since verification")


def verify(root: Path, entry: dict) -> dict:
    import diff
    import project_state
    if entry.get("overlay") != "game":
        raise ValueError("original assembly verification currently supports US game spans")
    validate_source(root, entry)
    region = entry["regions"]["us"]
    symbol, start = region["symbol"], int(region["vram"], 16)
    size = diff.expected_function_size("us", symbol)
    assembly = root / project_state.nonmatching_asm_path(entry["source"], symbol)
    raw = diff.ensure_reference_function("us", symbol, game_reference=True)
    code, base, digest = rom_span.game_code(root)
    expected = rom_span.raw_span(raw.read_text(), start, size, code, base)
    # Check the words recorded in the retained source, then independently
    # assemble/link its actual directives too. Comments alone are not proof.
    rom_span.raw_span(assembly.read_text(), start, size, code, base)
    output = root / "build/us/original-asm" / symbol
    output.mkdir(parents=True, exist_ok=True)
    copy = output / "original.s"
    # GLOBAL_ASM snippets inherit these settings from the assembly processor;
    # they intentionally omit the standalone raw-reference prelude.
    copy.write_text('.set noat\n.set noreorder\n.set gp=64\n' + assembly.read_text())
    path = diff.reference_object("us", symbol, game_reference=True, assembly=copy)
    obj = Object32(path.read_bytes())
    symbols = {}
    for table in obj.symbols.values():
        for name, value, _, section in table:
            if name and section == 0:
                match = re.fullmatch(r"(?:D|func|jtbl)_([0-9A-Fa-f]{8})(?:_[A-Za-z0-9]+)?", name)
                if match is None or value:
                    raise ValueError(f"unsupported original assembly external symbol: {name}")
                symbols[name] = int(match[1], 16)
    payload = linked_aliases.linked_span(path, obj, symbol, start, size, symbols,
                                        output / "original", reference=True)
    if payload != expected:
        raise ValueError("assembled original span differs from the US ROM")
    (output / "span.bin").write_bytes(payload)
    return {"rom_sha1": digest, "span_sha256": hashlib.sha256(payload).hexdigest(),
            "assembly_sha256": hashlib.sha256(assembly.read_bytes()).hexdigest(),
            "verified_revision": "working-tree"}


def read_proof(root: Path, entry: dict, proof: Path) -> dict:
    """Revalidate a container proof against current host inputs before recording."""
    import diff
    import project_state
    data = json.loads(proof.read_text())
    if data.get("symbol") != entry["symbol"]:
        raise ValueError("original assembly proof belongs to a different work item")
    region = entry["regions"]["us"]
    symbol = region["symbol"]
    assembly = root / project_state.nonmatching_asm_path(entry["source"], symbol)
    code, base, digest = rom_span.game_code(root)
    payload = rom_span.raw_span(assembly.read_text(), int(region["vram"], 16),
                                diff.expected_function_size("us", symbol), code, base)
    if (root / "build/us/original-asm" / symbol / "span.bin").read_bytes() != payload:
        raise ValueError("assembled original proof is stale or differs from ROM")
    expected = {"rom_sha1": digest, "span_sha256": hashlib.sha256(payload).hexdigest(),
                "assembly_sha256": hashlib.sha256(assembly.read_bytes()).hexdigest(),
                "verified_revision": "working-tree"}
    if data.get("evidence") != expected:
        raise ValueError("original assembly proof does not match current inputs")
    return expected
