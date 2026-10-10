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
    if entry.get("blocked") or entry.get("deferred") or entry.get("overlay") not in {"game", "main", "debugger"}:
        raise ValueError("verified original assembly must be a non-deferred US main, game or debugger span")
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


def validate_source(root: Path, entry: dict, *, allow_stale_hash: bool = False) -> None:
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
        if not allow_stale_hash and assembly.is_file() and hashlib.sha256(assembly.read_bytes()).hexdigest() != entry["regions"]["us"]["evidence"]["assembly_sha256"]:
            raise ValueError("retained original assembly changed since verification")


def declared_symbols(root: Path, game_reference: bool) -> dict[str, int]:
    """Named addresses from the reviewed US symbol file used by the raw split."""
    path = root / "config/symbols/us.txt"
    if game_reference or not path.is_file():
        return {}
    pattern = r"^([A-Za-z_.$][\w.$]*)\s*=\s*(0x[0-9A-Fa-f]+);"
    return {name: int(address, 16) for name, address in re.findall(pattern, path.read_text(), re.M)}


def reference_image(root: Path, entry: dict) -> tuple[bytes, int, str]:
    return rom_span.code_image(root, entry.get("overlay", "main"))


def verify(root: Path, entry: dict, *, refresh: bool = False) -> dict:
    import diff
    import project_state
    code, base, digest = reference_image(root, entry)
    game_reference = entry["overlay"] == "game"
    if refresh:
        validate_source(root, entry, allow_stale_hash=True)
    else:
        validate_source(root, entry)
    region = entry["regions"]["us"]
    symbol, start = region["symbol"], int(region["vram"], 16)
    size = diff.expected_function_size("us", symbol)
    assembly = root / project_state.nonmatching_asm_path(entry["source"], symbol)
    assembly_data = assembly.read_bytes()
    assembly_text = assembly_data.decode("utf-8")
    raw = diff.ensure_reference_function("us", symbol, game_reference=game_reference)
    expected = rom_span.raw_span(raw.read_text(), start, size, code, base)
    # Check the words recorded in the retained source, then independently
    # assemble/link its actual directives too. Comments alone are not proof.
    rom_span.raw_span(assembly_text, start, size, code, base)
    output = root / "build/us/original-asm" / symbol
    output.mkdir(parents=True, exist_ok=True)
    copy = output / "original.s"
    # GLOBAL_ASM snippets inherit these settings from the assembly processor;
    # they intentionally omit the standalone raw-reference prelude.
    copy.write_bytes(b'.set noat\n.set noreorder\n.set gp=64\n' + assembly_data)
    path = diff.reference_object("us", symbol, game_reference=game_reference, assembly=copy)
    obj = Object32(path.read_bytes())
    symbols = {}
    declared = declared_symbols(root, game_reference)
    for table in obj.symbols.values():
        for name, value, _, section in table:
            if name and section == 0:
                match = re.fullmatch(r"(?:D|func|jtbl)_([0-9A-Fa-f]{8})(?:_[A-Za-z0-9]+)?", name)
                if match is None and not game_reference:
                    # Raw main also uses unpadded D_ names for literal constants
                    # (for example D_63FFFF); keep function identities strict.
                    match = re.fullmatch(r"D_([0-9A-Fa-f]{1,7})", name)
                # Main handwritten spans may branch into a neighbouring retained
                # span. Resolve only the disassembler's exact CPU-address label
                # form; the actual linked branch still must equal the ROM word.
                local = re.fullmatch(r"\.L([0-9A-Fa-f]{8})", name) if not game_reference else None
                if local and not base <= int(local[1], 16) < base + len(code):
                    raise ValueError(f"original assembly local target is outside {entry['overlay']} CPU text: {name}")
                if match is None and local is None and name in declared and not value:
                    # Canonical SDK names replace D_ labels in the raw split.
                    symbols[name] = declared[name]
                    continue
                if (match is None and local is None) or value:
                    raise ValueError(f"unsupported original assembly external symbol: {name}")
                symbols[name] = int((match or local)[1], 16)
    payload = linked_aliases.linked_span(path, obj, symbol, start, size, symbols,
                                        output / "original", reference=True)
    if payload != expected:
        raise ValueError("assembled original span differs from the US ROM")
    (output / "span.bin").write_bytes(payload)
    evidence = {"rom_sha1": digest, "span_sha256": hashlib.sha256(payload).hexdigest(),
                "assembly_sha256": hashlib.sha256(assembly_data).hexdigest(),
                "verified_revision": "working-tree"}
    if refresh:
        require_unchanged_span(entry, evidence)
    return evidence


def require_unchanged_span(entry: dict, evidence: dict) -> None:
    """A text refresh cannot change the classified ROM image or instruction span."""
    validate_metadata(entry)
    if entry["regions"]["us"]["state"] != "original_asm":
        raise ValueError("refresh requires an already classified original assembly span")
    old = entry["regions"]["us"]["evidence"]
    if any(evidence.get(key) != old[key] for key in ("rom_sha1", "span_sha256")):
        raise ValueError("original assembly refresh changed the recorded ROM or span hash")


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
    code, base, digest = reference_image(root, entry)
    assembly_data = assembly.read_bytes()
    payload = rom_span.raw_span(assembly_data.decode("utf-8"), int(region["vram"], 16),
                                diff.expected_function_size("us", symbol), code, base)
    if (root / "build/us/original-asm" / symbol / "span.bin").read_bytes() != payload:
        raise ValueError("assembled original proof is stale or differs from ROM")
    expected = {"rom_sha1": digest, "span_sha256": hashlib.sha256(payload).hexdigest(),
                "assembly_sha256": hashlib.sha256(assembly_data).hexdigest(),
                "verified_revision": "working-tree"}
    if data.get("evidence") != expected:
        raise ValueError("original assembly proof does not match current inputs")
    return expected
