#!/usr/bin/env python3
"""Portable records of manual finish attempts; never an acceptance authority."""
from __future__ import annotations

import argparse
import hashlib
import json
import math
import os
from pathlib import Path, PurePosixPath
import re
import signal
import stat
import shutil
import subprocess
import sys
import time
import tempfile
import uuid
import zipfile

import project_state
import matching_callers

ROOT = Path(__file__).resolve().parent.parent
FILES = {"start.json", "result.json", "source.c", "function.c", "output.log",
         "mismatch.json", "mismatch.txt", "note.json"}
ASSESSMENTS = ("unreviewed", "valid", "invalid", "structural")
MAX_BUNDLE_BYTES = 100 * 1024 * 1024
RESULT_FIELDS = {"status", "return_code", "score", "elapsed_seconds", "ended_ns",
                 "target_changed", "source_after_sha256", "context_after_fingerprint", "acceptance",
                 "diagnostics"}


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def write_bytes_atomic(path: Path, data: bytes) -> None:
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(
                mode="wb", dir=path.parent, prefix=f".{path.name}.", delete=False) as stream:
            temporary = Path(stream.name)
            stream.write(data)
        temporary.replace(path)
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)


def write_json(path: Path, data: dict) -> None:
    write_bytes_atomic(path, (json.dumps(data, indent=2, sort_keys=True) + "\n").encode())


def safe_id(value: str) -> str:
    if not re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", value):
        raise ValueError("invalid work-item ID")
    return value


def history_dir(root: Path, identifier: str) -> Path:
    return root / "build/us/matching-attempts" / safe_id(identifier)


def no_symlinks(root: Path, path: Path) -> None:
    relative = path.relative_to(root)
    current = root
    for part in relative.parts:
        current /= part
        if current.is_symlink():
            raise ValueError(f"symlink in history path: {relative}")


def validate_record(start: dict, result: dict, note: dict, identifier: str, attempt: str) -> None:
    if any(not isinstance(value, dict) for value in (start, result, note)):
        raise ValueError("invalid record object")
    if (start.get("schema_version") != 1 or start.get("identifier") != identifier
            or start.get("attempt_id") != attempt or start.get("profile") != "us"
            or type(start.get("started_ns")) is not int):
        raise ValueError("invalid attempt identity")
    if not isinstance(start.get("source_path"), str):
        raise ValueError("invalid source path")
    for field in ("source_sha256", "context_fingerprint", "function_sha256"):
        if field == "function_sha256" and start.get(field) is None:
            continue
        if not isinstance(start.get(field), str) or not re.fullmatch(r"[0-9a-f]{64}", start[field]):
            raise ValueError("invalid attempt fingerprint")
    if set(result) - RESULT_FIELDS:
        raise ValueError("result cannot override attempt identity")
    if (result.get("score") is not None and
            (type(result["score"]) is not int or result["score"] < 0)):
        raise ValueError("invalid recorded score")
    elapsed = result.get("elapsed_seconds", 0)
    if type(elapsed) not in (float, int) or not math.isfinite(elapsed) or elapsed < 0:
        raise ValueError("invalid recorded duration")
    if not isinstance(result.get("status", "interrupted"), str):
        raise ValueError("invalid result status")
    if note.get("assessment", "unreviewed") not in ASSESSMENTS:
        raise ValueError("invalid candidate assessment")
    for key in ("hypothesis", "expected"):
        if key in note and (not isinstance(note[key], str) or len(note[key]) > 4000):
            raise ValueError("invalid hypothesis annotation")
    if "exhausted" in note and type(note["exhausted"]) is not bool:
        raise ValueError("invalid exhaustion annotation")


def work_item(root: Path, identifier: str) -> dict:
    safe_id(identifier)
    entries = json.loads((root / "progress/functions.json").read_text())["functions"]
    matches = [entry for entry in entries if entry["symbol"] == identifier]
    if len(matches) != 1 or "us" not in matches[0]["regions"]:
        raise ValueError(f"unknown US work-item: {identifier}")
    return matches[0]


def reference_files(root: Path, entry: dict) -> dict[str, str]:
    game = entry.get("overlay") == "game"
    raw = root / ("reference/game/us/asm" if game else "reference/us/asm")
    symbol = entry["regions"]["us"]["symbol"]
    pattern = re.compile(rf"^glabel\s+{re.escape(symbol)}\s*$", re.MULTILINE)
    index = root / "build/reference-index" / ("game-us.json" if game else "main-us.json")
    candidates = []
    if index.is_file() and raw.is_dir():
        try:
            cache = json.loads(index.read_text())
            if cache.get("schema_version") == 1 and cache.get("assembly_root_mtime_ns") == raw.stat().st_mtime_ns:
                candidates = [raw / name for name in cache["symbols"].get(symbol, [])]
        except (ValueError, KeyError, TypeError):
            pass
    if (len(candidates) != 1 or not candidates[0].is_file()
            or not candidates[0].resolve().is_relative_to(raw.resolve())
            or not pattern.search(candidates[0].read_text())):
        candidates = [path for path in raw.rglob("*.s") if pattern.search(path.read_text())]
    if len(candidates) != 1:
        return {}  # Missing/ambiguous raw input must never establish comparability.
    path = candidates[0]
    return {path.relative_to(root).as_posix(): sha(path.read_bytes())}


def snapshot(root: Path, entry: dict) -> tuple[dict, bytes, bytes | None]:
    source = (root / entry["source"]).resolve()
    if not source.is_relative_to(root.resolve()):
        raise ValueError("source is outside the checkout")
    data = source.read_bytes()
    function = None
    context = data
    try:
        text = data.decode("utf-8")
        begin, end = project_state.work_item_function_span(
            text, entry["symbol"], entry["regions"]["us"]["symbol"])
        function = text[begin:end].encode()
        context = (text[:begin] + "/* recorded target */\n" + text[end:]).encode()
    except (UnicodeError, project_state.ProjectStateError):
        pass  # Malformed/pragma-only sources still deserve an attempt record.
    inputs = {}
    paths = list((root / "include").rglob("*.h"))
    paths += list((root / "src").rglob("*.h"))
    paths += list((root / "lib/ultralib/include").rglob("*.h"))
    paths += [path for path in (root / "config").rglob("*") if path.is_file()]
    paths += list((root / "scripts").glob("*.py"))
    paths += [root / name for name in ("scripts/conker.sh", "Dockerfile", "Makefile",
                                      "toolchain/tools.lock.json", "progress/source_units.json")]
    for path in sorted(paths):
        if path.is_file():
            inputs[path.relative_to(root).as_posix()] = sha(path.read_bytes())
    references = reference_files(root, entry)
    identity = {"context_sha256": sha(context), "inputs": inputs,
                "reference_files": references, "region": entry["regions"]["us"],
                "overlay": entry.get("overlay", "main")}
    # Inventory state is not a compiler input and changes after successful finish.
    identity["region"] = {key: value for key, value in identity["region"].items()
                          if key in {"symbol", "vram", "size_bytes", "rom"}}
    return {"source_path": entry["source"], "source_sha256": sha(data),
            "function_sha256": sha(function) if function is not None else None,
            **identity, "context_fingerprint": sha(json.dumps(identity, sort_keys=True).encode())}, data, function


def records(root: Path, identifier: str) -> list[dict]:
    result = []
    for path in history_dir(root, identifier).glob("*/start.json"):
        if not re.fullmatch(r"[0-9a-f]{32}", path.parent.name):
            continue
        no_symlinks(root, path)
        start = json.loads(path.read_text())
        location = path.parent
        end = location / "result.json"
        note = location / "note.json"
        for file in (end, note):
            no_symlinks(root, file)
        outcome = {"status": "interrupted", "score": None}
        if end.exists():
            loaded = json.loads(end.read_text())
            if not isinstance(loaded, dict):
                raise ValueError("invalid record object")
            outcome.update(loaded)
        annotation = json.loads(note.read_text()) if note.exists() else {}
        validate_record(start, outcome, annotation, identifier, location.name)
        result.append({**start, **outcome, "note": annotation,
                       "directory": location})
    return sorted(result, key=lambda row: (row["started_ns"], row["attempt_id"]))


def summarize(root: Path, identifier: str, limit: int = 5, *, compact: bool = False,
              current_score: int | None = None) -> None:
    rows = records(root, identifier)
    if not rows:
        if not compact:
            print(f"{identifier}: no recorded finish attempts")
        return
    pairs = {(r["function_sha256"], r["context_fingerprint"]) for r in rows}
    elapsed = sum(r.get("elapsed_seconds", 0) for r in rows)
    print(f"matching-history: {identifier}: {len(rows)} finish calls, {len(pairs)} distinct inputs; "
          f"{elapsed:.1f}s command time (not workflow wall time)")
    try:
        current, _, _ = snapshot(root, work_item(root, identifier))
        fingerprint = current["context_fingerprint"]
    except (OSError, ValueError, KeyError):
        current = None
        fingerprint = None
    latest = rows[-1]
    target = ("unavailable" if not current or not latest.get("function_sha256") else
              "changed-during-finish" if latest.get("target_changed") else
              "current" if latest["function_sha256"] == current["function_sha256"] else "historical")
    context = ("incomplete" if not latest.get("reference_files") else
               "changed-during-finish" if latest.get("context_after_fingerprint")
               and latest["context_after_fingerprint"] != latest["context_fingerprint"] else
               "current" if latest["context_fingerprint"] == fingerprint else "historical")
    score = f" CURRENT ({latest['score']})" if type(latest.get("score")) is int else ""
    print(f"latest-recorded-finish: {latest['status']}{score}; target={target}; context={context}; "
          f"attempt={latest['attempt_id']}; historical evidence, not current verification or BATCH_COMPLETE")
    scored = [r for r in rows if type(r.get("score")) is int and r.get("target_changed") is False
              and r.get("function_sha256") and r.get("reference_files")
              and r.get("context_after_fingerprint") == r["context_fingerprint"]
              and r["context_fingerprint"] == fingerprint
              and r["note"].get("assessment") != "invalid"]
    best = min(scored, key=lambda row: row["score"]) if scored else None
    if best:
        print(f"lowest-observed: CURRENT ({best['score']}) [{best['note'].get('assessment', 'unreviewed')}] "
              f"{best['directory'].relative_to(root)}/function.c; not proof of validity or acceptance")
        if current_score is not None and best["score"] < current_score:
            print("history-warning: deferring a higher score; review the archived alternative and its "
                  "context before selecting a candidate (no automatic restoration)")
    for row in rows[-limit:]:
        note = row["note"]
        print(f"attempt: {row['attempt_id']} score={row.get('score')} status={row['status']} "
              f"assessment={note.get('assessment', 'unreviewed')}"
              + (" exhausted" if note.get("exhausted") else "")
              + (" context=incomplete" if not row.get("reference_files") else
                 " context=historical" if row["context_fingerprint"] != fingerprint else " context=current"))
        if note.get("hypothesis"):
            print(f"  hypothesis: {note['hypothesis']}")
        if note.get("expected"):
            print(f"  predicted-effect: {note['expected']}")
        if row.get("diagnostics"):
            print(f"  observed: {json.dumps(row['diagnostics'], sort_keys=True)}")
    exhausted = sum(bool(r["note"].get("exhausted")) for r in rows)
    if exhausted:
        print(f"exhausted-records: {exhausted}; a continuation or a lower score does not reset prior work")
    print("history-scope: historical evidence; compare input fingerprints before reuse; "
          "STOP_MATCHED is a per-function gate, not BATCH_COMPLETE")


def diagnostic_facts(path: Path) -> dict:
    import diff
    try:
        rows = diff.diagnostic_rows(path.read_text())
        facts = {**diff.classify_diff_rows(rows),
                 "stack_rows": sum(diff.is_stack_difference(row) for row in rows)}
        for side in ("base", "current"):
            frames = [text for row in rows if (text := diff.instruction_text(row, side))
                      and re.search(r"\baddiu\s+\$?sp,\s*\$?sp,\s*-", text)]
            if frames:
                facts[side + "_frame_instruction"] = frames[0]
        return facts
    except (ValueError, KeyError, TypeError):
        return {"unavailable": "saved evidence has no valid diagnostic rows"}


def prepare(root: Path, identifier: str) -> None:
    entry = work_item(root, identifier)
    directory = history_dir(root, identifier)
    no_symlinks(root, directory / "ready-source.c")
    directory.mkdir(parents=True, exist_ok=True)
    data = (root / entry["source"]).read_bytes()
    write_bytes_atomic(directory / "ready-source.c", data)
    write_json(directory / "ready.json", {"source_path": entry["source"],
               "source_sha256": sha(data), "started_ns": time.time_ns()})
    summarize(root, identifier, 3, compact=True)


def declaration_changes(root: Path, identifier: str, metadata: dict, source: bytes) -> dict[str, list[str]]:
    previous = records(root, identifier)
    baseline = previous[-1] if previous else None
    path = baseline["directory"] / "source.c" if baseline else None
    ready = history_dir(root, identifier) / "ready.json"
    if ready.exists():
        no_symlinks(root, ready)
        initial = json.loads(ready.read_text())
        if baseline is None or initial["started_ns"] > baseline["started_ns"]:
            baseline, path = initial, ready.with_name("ready-source.c")
    if baseline is None or baseline["source_path"] != metadata["source_path"]:
        return {"changed": [], "removed": [], "added": [], "added_with_existing_calls": [],
                "added_with_uncertain_callers": []}
    no_symlinks(root, path)
    data = path.read_bytes()
    if sha(data) != baseline["source_sha256"]:
        raise ValueError("declaration baseline checksum mismatch")
    return matching_callers.classify_signature_changes(data.decode(), source.decode())


def record(root: Path, identifier: str) -> int:
    entry = work_item(root, identifier)
    metadata, source, function = snapshot(root, entry)
    declarations = declaration_changes(root, identifier, metadata, source)
    changed = sorted(set(declarations["changed"] + declarations["removed"]))
    review = sorted(set(changed + declarations["added_with_existing_calls"]
                        + declarations["added_with_uncertain_callers"]))
    attempt = uuid.uuid4().hex
    directory = history_dir(root, identifier) / attempt
    no_symlinks(root, directory)
    directory.mkdir(parents=True, exist_ok=False)
    (directory / "source.c").write_bytes(source)
    if function is not None:
        (directory / "function.c").write_bytes(function)
    start = {"schema_version": 1, "identifier": identifier, "profile": "us",
             "attempt_id": attempt, "started_ns": time.time_ns(),
             "changed_declarations": changed, "declaration_review": declarations,
             "caller_review_symbols": review, **metadata}
    write_json(directory / "start.json", start)
    if changed:
        print("declaration-changes: " + ", ".join(changed), flush=True)
    if declarations["added"]:
        print("declaration-additions: " + ", ".join(declarations["added"]), flush=True)
    if declarations["added_with_existing_calls"]:
        print("existing-local-call-review: new declarations for "
              + ", ".join(declarations["added_with_existing_calls"])
              + "; check existing contracts, including headers and macros", flush=True)
    if declarations["added_with_uncertain_callers"]:
        print("uncertain-local-call-review: " + ", ".join(declarations["added_with_uncertain_callers"])
              + "; existing definition bodies are ambiguous or unavailable; inspect additions", flush=True)
    if review:
        print("caller-review: inspect affected contracts and recheck existing matches; "
              "./conker matching-callers " + " ".join(review), flush=True)
    evidence_dir = root / "build/us/diff" / entry["regions"]["us"]["symbol"]
    before = {name: (evidence_dir / name).stat().st_mtime_ns
              for name in ("mismatch.json", "mismatch.txt") if (evidence_dir / name).exists()}
    env = dict(os.environ, CONKER_MATCHING_RECORD_ACTIVE="1")
    began = time.monotonic()
    output = []
    status = None
    ended = None
    try:
        with (directory / "output.log").open("w") as log:
            child = subprocess.Popen([str(root / "conker"), "finish", identifier], cwd=root,
                                     env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                     text=True, errors="replace", start_new_session=True)
            try:
                for line in child.stdout:
                    output.append(line)
                    log.write(line)
                    log.flush()
                    print(line, end="", flush=True)
                status = child.wait()
                ended = time.monotonic()
            except BaseException:
                try:
                    os.killpg(child.pid, signal.SIGTERM)
                except ProcessLookupError:
                    pass
                try:
                    child.wait(timeout=5)
                except subprocess.TimeoutExpired:
                    try:
                        os.killpg(child.pid, signal.SIGKILL)
                    except ProcessLookupError:
                        pass
                    child.wait()
                raise
            finally:
                child.stdout.close()
    finally:
        ended = ended or time.monotonic()
        text = "".join(output)
        score_matches = re.findall(rf"^{re.escape(entry['regions']['us']['symbol'])}: CURRENT \((\d+)\)$",
                                  text, re.MULTILINE)
        actions = re.findall(r"^AGENT_ACTION: ([A-Z_]+)$", text, re.MULTILINE)
        target_changed = None
        try:
            after, _, _ = snapshot(root, entry)
            target_changed = after["function_sha256"] != metadata["function_sha256"]
        except (OSError, ValueError):
            after = {}
        result = {"status": actions[-1] if actions else "interrupted" if status is None else "unclassified",
                  "return_code": status, "score": int(score_matches[-1]) if score_matches else None,
                  "elapsed_seconds": ended - began, "ended_ns": time.time_ns(),
                  "target_changed": target_changed,
                  "context_after_fingerprint": after.get("context_fingerprint"),
                  "source_after_sha256": after.get("source_sha256"),
                  "acceptance": "not_recorded_by_history"}
        for name in ("mismatch.json", "mismatch.txt"):
            path = evidence_dir / name
            if (path.exists() and path.stat().st_mtime_ns != before.get(name)
                    and f"diff/{entry['regions']['us']['symbol']}/{name}" in text):
                (directory / name).write_bytes(path.read_bytes())
                if name == "mismatch.json":
                    result["diagnostics"] = diagnostic_facts(directory / name)
        write_json(directory / "result.json", result)
        print(f"attempt-record: {directory.relative_to(root)}", flush=True)
    return 128 - status if status < 0 else status


def annotate(root: Path, identifier: str, attempt: str, **note) -> None:
    row = next((row for row in records(root, identifier) if row["attempt_id"] == attempt), None)
    if row is None:
        raise ValueError("unknown attempt ID; use matching-history show")
    note = {key: value for key, value in note.items() if value is not None}
    validate_record(row, {}, {**row["note"], **note}, identifier, attempt)
    write_json(row["directory"] / "note.json", {**row["note"], **note, "updated_ns": time.time_ns()})


def export_bundle(root: Path, identifier: str, output: Path) -> None:
    rows = records(root, identifier)
    if not rows:
        raise ValueError("no recorded attempts to export")
    contents = {}
    for row in rows:
        for name in sorted(FILES):
            path = row["directory"] / name
            no_symlinks(root, path)
            if path.is_file():
                contents[f"{row['attempt_id']}/{name}"] = path.read_bytes()
    if sum(map(len, contents.values())) > MAX_BUNDLE_BYTES:
        raise ValueError("attempt bundle exceeds 100 MiB")
    manifest = {"schema_version": 1, "identifier": identifier,
                "files": {name: sha(data) for name, data in contents.items()}}
    # Exclusive creation prevents accidental replacement of an earlier handoff.
    with output.open("xb") as stream, zipfile.ZipFile(stream, "w", zipfile.ZIP_DEFLATED) as archive:
        archive.writestr("manifest.json", json.dumps(manifest, sort_keys=True))
        for name, data in contents.items():
            archive.writestr(name, data)
    print(f"Exported {len(rows)} historical attempts to {output}; no match state exported")


def import_bundle(root: Path, archive_path: Path) -> None:
    with zipfile.ZipFile(archive_path) as archive:
        members = archive.infolist()
        names = [member.filename for member in members]
        if (len(names) != len(set(names)) or len(names) > 20000
                or sum(member.file_size for member in members) > MAX_BUNDLE_BYTES
                or any(stat.S_ISLNK(member.external_attr >> 16) or member.is_dir() for member in members)):
            raise ValueError("duplicate archive members or oversized bundle")
        manifest = json.loads(archive.read("manifest.json"))
        if manifest.get("schema_version") != 1:
            raise ValueError("unsupported bundle schema")
        identifier = safe_id(manifest["identifier"])
        files = manifest["files"]
        if set(names) != set(files) | {"manifest.json"}:
            raise ValueError("bundle manifest does not match contents")
        contents = {}
        for name, checksum in files.items():
            parts = PurePosixPath(name).parts
            if (len(parts) != 2 or not re.fullmatch(r"[0-9a-f]{32}", parts[0])
                    or parts[1] not in FILES or name != "/".join(parts)):
                raise ValueError("unsafe bundle path")
            data = archive.read(name)
            if sha(data) != checksum:
                raise ValueError("bundle checksum mismatch")
            contents[name] = data
    attempts = {name.split("/")[0] for name in contents}
    for attempt in attempts:
        start = json.loads(contents[f"{attempt}/start.json"])
        outcome = json.loads(contents.get(f"{attempt}/result.json", b"{}"))
        note = json.loads(contents.get(f"{attempt}/note.json", b"{}"))
        validate_record(start, outcome, note, identifier, attempt)
        if sha(contents[f"{attempt}/source.c"]) != start.get("source_sha256"):
            raise ValueError("invalid attempt identity or source checksum")
        if start.get("function_sha256") is not None and sha(contents[f"{attempt}/function.c"]) != start["function_sha256"]:
            raise ValueError("invalid function checksum")
    destination = history_dir(root, identifier)
    no_symlinks(root, destination)
    if not destination.resolve().is_relative_to(root.resolve()):
        raise ValueError("history destination escapes checkout")
    for name, data in contents.items():
        path = destination / name
        no_symlinks(root, path)
        if not path.resolve().is_relative_to(destination.resolve()):
            raise ValueError("history path escapes destination")
        if path.exists() and path.read_bytes() != data:
            raise ValueError("existing attempt differs; import will not overwrite history")
    # An existing UUID must be identical in full, not a partial merge.
    for attempt in attempts:
        existing = destination / attempt
        if existing.exists() and {p.name for p in existing.iterdir()} != {
                name.split("/")[1] for name in contents if name.startswith(attempt + "/")}:
            raise ValueError("existing attempt has different files")
    staging = destination.parent / (".import-" + uuid.uuid4().hex)
    created = []
    try:
        for name, data in contents.items():
            path = staging / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
        destination.mkdir(parents=True, exist_ok=True)
        for attempt in attempts:
            target = destination / attempt
            if not target.exists():
                (staging / attempt).rename(target)
                created.append(target)
    except BaseException:
        for path in created:
            shutil.rmtree(path)
        raise
    finally:
        if staging.exists():
            shutil.rmtree(staging)
    print(f"Imported {len(attempts)} historical attempts for {identifier}; source and inventory unchanged")


def interrupted(signum, frame):
    raise KeyboardInterrupt


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    for command in ("show", "summary", "prepare", "record", "note", "export"):
        sub = commands.add_parser(command)
        sub.add_argument("identifier")
        if command in {"show", "summary"}:
            sub.add_argument("--limit", type=int, default=3 if command == "summary" else 5)
            sub.add_argument("--current-score", type=int)
        elif command == "note":
            sub.add_argument("attempt")
            sub.add_argument("--hypothesis")
            sub.add_argument("--expected")
            sub.add_argument("--assessment", choices=ASSESSMENTS)
            sub.add_argument("--exhausted", action="store_true", default=None)
        elif command == "export":
            sub.add_argument("output", type=Path)
    commands.add_parser("import").add_argument("archive", type=Path)
    args = parser.parse_args()
    try:
        if args.command in {"show", "summary"}:
            if not 1 <= args.limit <= 20:
                raise ValueError("limit must be between 1 and 20")
            summarize(ROOT, args.identifier, args.limit, compact=args.command == "summary",
                      current_score=args.current_score)
        elif args.command == "record":
            signal.signal(signal.SIGTERM, interrupted)
            return record(ROOT, args.identifier)
        elif args.command == "prepare":
            prepare(ROOT, args.identifier)
        elif args.command == "note":
            annotate(ROOT, args.identifier, args.attempt, hypothesis=args.hypothesis,
                     expected=args.expected, assessment=args.assessment, exhausted=args.exhausted)
        elif args.command == "export":
            export_bundle(ROOT, args.identifier, args.output)
        else:
            import_bundle(ROOT, args.archive)
        return 0
    except KeyboardInterrupt:
        print("matching-history: interrupted; candidate snapshot retained", file=sys.stderr)
        return 130
    except (OSError, ValueError, KeyError, TypeError, zipfile.BadZipFile) as error:
        print(f"error: matching history: {error}", file=sys.stderr)
        if args.command == "record":
            print("AGENT_ACTION: BLOCKED_TOOLING")
        return 3


if __name__ == "__main__":
    raise SystemExit(main())
