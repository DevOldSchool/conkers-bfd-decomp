#!/usr/bin/env python3
"""Run a bounded, semantics-preserving source-shape search for one C candidate."""

from __future__ import annotations

import argparse
import itertools
import hashlib
import json
import os
import re
import secrets
import shlex
import shutil
import signal
import subprocess
import sys
import time
from pathlib import Path

import compile_c
import candidate_rewrites
import candidate_syntax
import candidate_tables
import candidate_lifetimes
import diff
import m2c_context
import project_state


ROOT = Path(__file__).resolve().parent.parent
# The toolchain image clones decomp-permuter at the revision pinned in
# toolchain/tools.lock.json. Tests point this at a fake permuter.
PERMUTER_ROOT = Path(os.environ.get("CONKER_DECOMP_PERMUTER", "/opt/tools/decomp-permuter"))
# The permuter draws every randomization seed from Python's global random
# module, so seeding it once in-process makes a single-threaded run reproducible.
PERMUTER_SHIM = (
    "import random, runpy, sys\n"
    "seed, root = int(sys.argv[1]), sys.argv[2]\n"
    "random.seed(seed)\n"
    "sys.argv = [root + '/permuter.py'] + sys.argv[3:]\n"
    "sys.path.insert(0, root)\n"
    "runpy.run_path(sys.argv[0], run_name='__main__')\n"
)
PERMUTER_SEARCH_FLAGS = ("--stop-on-zero", "--better-only", "--stack-diffs", "-j", "1")
PERMUTER_OUTPUT = re.compile(r"^output-(?P<score>\d+)-(?P<counter>\d+)$")
REUSABLE_STOP_REASONS = ("plateau", "variants_exhausted", "stack_shape_no_improvement",
                         "time_limit", "permuter_exit")


def candidate_function_span(content: str, identifier: str, regional_symbol: str) -> tuple[int, int]:
    """Locate a candidate defined directly or through a profile symbol alias."""

    return project_state.work_item_function_span(
        content, identifier, regional_symbol
    )
DECLARATION = re.compile(
    r"^(?P<indent>[ \t]+)(?P<type>(?:(?:const|signed|unsigned)\s+)*"
    r"(?:struct\s+[A-Za-z_]\w*|[A-Za-z_]\w*)(?:[ \t]*\*)*)"
    r"(?:(?<=\*)[ \t]*|[ \t]+)(?P<name>[A-Za-z_]\w*)[ \t]*;[ \t]*$",
    re.MULTILINE,
)


class PermuteError(ValueError):
    """Raised when a candidate cannot be searched safely."""


def work_item(identifier: str, profile: str) -> tuple[dict, str]:
    inventory = json.loads(
        (ROOT / "progress" / "functions.json").read_text(encoding="utf-8")
    )
    entry = next(
        (function for function in inventory["functions"] if function["symbol"] == identifier),
        None,
    )
    if entry is None:
        raise PermuteError(f"unknown work-item ID: {identifier}")
    region = entry.get("regions", {}).get(profile)
    if region is None:
        raise PermuteError(f"{identifier} is not registered for {profile}")
    source = entry.get("source")
    if not isinstance(source, str) or not source:
        raise PermuteError(f"{identifier} has no assigned source")
    return entry, region["symbol"]


def active_candidate_content(entry: dict, identifier: str) -> tuple[Path, str]:
    source = ROOT / entry["source"]
    content = source.read_text(encoding="utf-8")
    if entry.get("deferred"):
        content = diff.activate_deferred_candidate(content, source, identifier)
    elif project_state.global_asm_pragma(entry["source"], identifier) in content:
        raise PermuteError(
            f"{identifier} has no active or preserved C candidate to permute"
        )
    return source, content


def declaration_variants(function: str, budget: int) -> list[str]:
    """Vary declaration order and first-assignment scope without changing behavior."""

    # Only the initial, top-level declaration block is eligible. Nested block
    # declarations and expression statements must never become type evidence.
    opening = function.find("{")
    declarations = []
    cursor = opening + 1
    for declaration in DECLARATION.finditer(function, cursor):
        if function[cursor:declaration.start()].strip():
            break
        if declaration.group("type") in ("return", "goto", "volatile"):
            break
        declarations.append(declaration)
        cursor = declaration.end()
    if not declarations:
        return [function]
    start = declarations[0].start()
    end = declarations[-1].end()
    between = function[start:end]
    if any(
        part.strip()
        for part in DECLARATION.sub("", between).splitlines()
    ):
        return [function]

    declaration_lines = [match.group(0) for match in declarations]
    variants: list[str] = []
    seen: set[str] = set()

    def retain(candidate: str) -> None:
        if candidate not in seen and len(variants) < budget:
            seen.add(candidate)
            variants.append(candidate)

    def lifetimes(base: str):
        if re.search(r"\bgoto\b|(?m:^[ \t]*[A-Za-z_]\w*\s*:)", base):
            return
        for declaration in declarations:
            name = declaration.group("name")
            type_name = declaration.group("type")
            indent = declaration.group("indent")
            declaration_pattern = re.compile(
                rf"^{re.escape(declaration.group(0))}\n?",
                re.MULTILINE,
            )
            without_declaration, removed = declaration_pattern.subn("", base, count=1)
            if removed != 1:
                continue
            assignment = re.compile(
                rf"^(?P<indent>[ \t]+){re.escape(name)}[ \t]*=[ \t]*(?P<expr>[^;\n]+);[ \t]*$",
                re.MULTILINE,
            )
            match = assignment.search(without_declaration)
            if match is None:
                continue
            prefix = without_declaration[: match.start()]
            prefix_tokens = candidate_syntax.tokens(prefix)
            if not prefix_tokens or prefix_tokens[-1].text not in ("{", ";", "}"):
                # An unbraced if/else/loop body must not acquire a scope that
                # swallows the rest of the function.
                continue
            preceding = candidate_syntax.tokens(prefix + match.group("expr"))
            if any(
                token.text == name and (index == 0 or preceding[index - 1].text not in (".", "->"))
                for index, token in enumerate(preceding)
            ):
                continue
            brace_depth = 0
            for token in prefix_tokens:
                brace_depth += (token.text == "{") - (token.text == "}")
            if brace_depth != 1:
                continue
            initialized = (
                f"{match.group('indent')}{{\n"
                f"{match.group('indent')}    {type_name} {name} = "
                f"{match.group('expr')};"
            )
            closing = without_declaration.rfind("}")
            if closing < match.end():
                continue
            yield (
                without_declaration[: match.start()]
                + initialized
                + without_declaration[match.end() : closing]
                + f"{match.group('indent')}}}\n"
                + without_declaration[closing:]
            )
    retain(function)
    # Interleave declaration order and first-assignment scope variants.
    orders = (
        function[:start] + "\n".join(order) + function[end:]
        for order in itertools.permutations(declaration_lines)
    )
    families = [iter(candidate_lifetimes.lifetime_variants(function, declarations)),
                iter(lifetimes(function)), iter(orders)]
    while families and len(variants) < budget:
        remaining = []
        for family in families:
            try:
                retain(next(family))
                remaining.append(family)
            except StopIteration:
                pass
        families = remaining
    return variants


def stack_source_variants(function: str, budget: int) -> list[str]:
    opening = function.find("{")
    declarations = []
    cursor = opening + 1
    for declaration in DECLARATION.finditer(function, cursor):
        if function[cursor:declaration.start()].strip():
            break
        declarations.append(declaration)
        cursor = declaration.end()
    return list(itertools.islice(itertools.chain(
        [function], candidate_lifetimes.stack_variants(function, declarations)), budget))


def source_variants(function: str, budget: int) -> list[str]:
    """Combine lifetime permutations with bounded expression-form rewrites."""

    declaration_budget = max(1, (budget + 1) // 2)
    seeds = declaration_variants(function, declaration_budget)
    return candidate_rewrites.rewrite_variants(seeds, budget)


def score_candidate(
    profile: str,
    symbol: str,
    source_content: str,
    directory: Path,
    reference: Path,
    expected_size: int,
) -> int:
    candidate_source = directory / "candidate.c"
    candidate_object = directory / "candidate.o"
    candidate_source.write_text(
        diff.GLOBAL_ASM_LINE.sub("", source_content), encoding="utf-8"
    )
    compile_c.run_compile(profile, candidate_source, candidate_object,
        cwd=ROOT,
        check=True,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    # scripts/ is mounted read-only in the container; a writable bytecode cache
    # roughly halves the per-candidate scorer start-up time.
    environment = dict(os.environ)
    environment.setdefault("PYTHONPYCACHEPREFIX", str(ROOT / "build" / "pycache"))
    try:
        result = subprocess.run(
            diff.asm_diff_command(
                candidate_object,
                reference,
                symbol,
                expected_size,
                require_match=True,
            ),
            cwd=directory,
            check=False,
            capture_output=True,
            text=True,
            env=environment,
        )
    except OSError as error:
        raise PermuteError(f"could not launch asm-differ: {error}") from error
    failure = None
    if result.returncode:
        failure = f"asm-differ exited {result.returncode}"
    else:
        try:
            return diff.current_difference_count(result.stdout)
        except ValueError as error:
            failure = str(error)
    log = directory / "scoring-failure.log"
    log.write_text(f"{failure}\n{result.stdout}{result.stderr}", encoding="utf-8")
    raise PermuteError(f"{failure}; details: {log}")


def search_fingerprint(profile: str, content: str, reference: Path, expected_size: int,
                       budget: int, exhaustive: bool, stack_shapes: bool = False,
                       randomized: tuple[int, int] | None = None) -> str:
    """Invalidate negative search results when any supported search input changes."""
    digest = hashlib.sha256()
    settings: list = [profile, content, expected_size, budget, exhaustive, stack_shapes]
    if randomized is not None:
        settings.append(["randomized", *randomized])
    digest.update(json.dumps(settings).encode())
    digest.update(reference.read_bytes())
    paths = [ROOT / "Makefile"]
    for directory in ("scripts", "include", "toolchain", "config"):
        paths.extend(path for path in (ROOT / directory).rglob("*")
                     if path.is_file() and "__pycache__" not in path.parts)
    for path in sorted(paths):
        digest.update(str(path.relative_to(ROOT)).encode())
        digest.update(path.read_bytes() if path.is_file() else b"<missing>")
    return digest.hexdigest()


def verify_exact_tables(entry: dict, symbol: str, candidate: Path, reference_assembly: Path,
                        expected_size: int) -> None:
    """Reject an instruction-exact candidate whose jump tables differ (game/debugger US)."""
    table_options = ({"overlay": "debugger", "expected_start": int(entry["regions"]["us"]["vram"], 16)}
                     if entry.get("overlay") == "debugger" else {})
    candidate_tables.verify_candidate(candidate, symbol, reference_assembly, expected_size,
                                      **table_options)


def permuter_command(seed: int, *arguments: str) -> list[str]:
    """Run the pinned decomp-permuter with Python's global RNG seeded first."""
    return ["python3", "-c", PERMUTER_SHIM, str(seed), str(PERMUTER_ROOT), *arguments]


def permuter_revision() -> str | None:
    try:
        lock = json.loads((ROOT / "toolchain" / "tools.lock.json").read_text(encoding="utf-8"))
        return lock["tools"]["decomp-permuter"]["revision"]
    except (OSError, ValueError, KeyError, TypeError):
        return None


def ido_preprocess(profile: str, focused: Path) -> str:
    """Expand a focused source with the pinned IDO preprocessor and build flags."""
    command = [str(compile_c.IDO_CC),
               *(flag for flag in compile_c.compiler_flags(profile) if flag != "-c"),
               "-E", str(focused.relative_to(ROOT))]
    result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, check=False)
    if result.returncode:
        raise PermuteError(f"IDO preprocessing of the permuter base failed: {result.stderr.strip()}")
    return result.stdout


def preprocess_for_permuter(profile: str, focused: Path) -> str:
    """Produce the self-contained, marker-free translation unit pycparser can parse."""
    lines = [line for line in ido_preprocess(profile, focused).splitlines()
             if not m2c_context.LINE_MARKER.fullmatch(line)]
    return "\n".join(lines) + "\n"


def clear_permuter_outputs(work: Path) -> None:
    """Remove only files this module generates below the randomized directory."""
    if not work.is_dir():
        return
    for entry in work.iterdir():
        if entry.is_dir() and PERMUTER_OUTPUT.match(entry.name):
            shutil.rmtree(entry)
        elif entry.name in ("focused.c", "base.c", "target.o", "compile.sh", "function.txt",
                            "settings.toml", "debug_source.c", "debug_compiled_object.o",
                            "permuter-base.log", "permuter.log"):
            entry.unlink()


def prepare_permuter_directory(profile: str, symbol: str, active_content: str,
                               reference: Path, directory: Path) -> Path:
    """Build the base.c/target.o/compile.sh directory decomp-permuter expects."""
    work = directory / "randomized"
    clear_permuter_outputs(work)
    work.mkdir(parents=True, exist_ok=True)
    focused = work / "focused.c"
    focused.write_text(diff.GLOBAL_ASM_LINE.sub("", active_content), encoding="utf-8")
    (work / "base.c").write_text(preprocess_for_permuter(profile, focused), encoding="utf-8")
    # Other definitions become prototypes so each permuter compile is one function.
    stripped = subprocess.run(["python3", str(PERMUTER_ROOT / "strip_other_fns.py"), "base.c", symbol],
                              cwd=work, capture_output=True, text=True, check=False)
    if stripped.returncode:
        raise PermuteError(f"decomp-permuter strip_other_fns failed: {stripped.stderr.strip()}")
    shutil.copyfile(reference, work / "target.o")
    flags = " ".join(shlex.quote(flag) for flag in compile_c.compiler_flags(profile))
    compile_script = work / "compile.sh"
    compile_script.write_text(
        "#!/bin/bash\n"
        "# Generated by scripts/permute.py: the pinned IDO flags of compile_c.compiler_flags.\n"
        "set -euo pipefail\n"
        f"cd {shlex.quote(str(ROOT))}\n"
        f'exec {shlex.quote(str(compile_c.IDO_CC))} {flags} "$@"\n',
        encoding="utf-8",
    )
    compile_script.chmod(0o755)
    (work / "function.txt").write_text(symbol + "\n", encoding="utf-8")
    (work / "settings.toml").write_text(
        f'func_name = "{symbol}"\ncompiler_type = "ido"\n', encoding="utf-8"
    )
    return work


def permuter_base(work: Path, seed: int) -> tuple[int, str]:
    """Score the base with the permuter's own metric and keep its regenerated source."""
    log = work / "permuter-base.log"
    try:
        result = subprocess.run(permuter_command(seed, str(work), "--debug", "--stack-diffs"),
                                cwd=work, capture_output=True, text=True, check=False,
                                stdin=subprocess.DEVNULL)
    except OSError as error:
        raise PermuteError(f"could not launch decomp-permuter: {error}") from error
    log.write_text(result.stdout + result.stderr, encoding="utf-8")
    score = re.search(r"base score = (\d+)", result.stdout)
    regenerated = work / "debug_source.c"
    if result.returncode or score is None or not regenerated.is_file():
        raise PermuteError(f"decomp-permuter could not score the base candidate; details: {log}")
    return int(score.group(1)), regenerated.read_text(encoding="utf-8")


def run_permuter_search(work: Path, seed: int, seconds: int) -> tuple[bool, int]:
    """Run the randomized search for at most `seconds`; return (timed_out, exit status)."""
    log = work / "permuter.log"
    with log.open("w", encoding="utf-8") as handle:
        try:
            process = subprocess.Popen(permuter_command(seed, str(work), *PERMUTER_SEARCH_FLAGS),
                                       cwd=work, stdout=handle, stderr=subprocess.STDOUT,
                                       stdin=subprocess.DEVNULL)
        except OSError as error:
            raise PermuteError(f"could not launch decomp-permuter: {error}") from error
        try:
            return False, process.wait(timeout=seconds)
        except subprocess.TimeoutExpired:
            # The permuter treats SIGINT as its normal "stop now" request.
            process.send_signal(signal.SIGINT)
            try:
                process.wait(timeout=30)
            except subprocess.TimeoutExpired:
                process.kill()
                process.wait()
            return True, process.returncode


def permuter_iterations(work: Path) -> int | None:
    """Best-effort iteration count from the permuter's status line."""
    try:
        text = (work / "permuter.log").read_text(encoding="utf-8", errors="replace")
    except OSError:
        return None
    counts = re.findall(r"iteration (\d+)", text)
    return int(counts[-1]) if counts else None


def permuter_outputs(work: Path) -> list[tuple[int, int, Path]]:
    """Improved candidates the permuter wrote, best permuter score first."""
    outputs = []
    for entry in work.iterdir():
        match = PERMUTER_OUTPUT.match(entry.name)
        source = entry / "source.c"
        if match and source.is_file():
            outputs.append((int(match.group("score")), int(match.group("counter")), source))
    return sorted(outputs)


def split_permuter_source(text: str, identifier: str, symbol: str) -> tuple[str, str]:
    """Separate the target definition from the rest of a regenerated source."""
    start, end = project_state.work_item_function_span(text, identifier, symbol)
    return text[start:end].rstrip("\n"), text[:start] + text[end:]


def restyle_permuter_function(function: str) -> str:
    """Widen pycparser's two-space indentation to the project's four spaces."""
    lines = function.splitlines()
    indents = [len(line) - len(line.lstrip(" ")) for line in lines if line.strip()]
    if any(indent % 2 for indent in indents) or min((i for i in indents if i), default=0) != 2:
        return function
    return "\n".join(" " * (2 * (len(line) - len(line.lstrip(" ")))) + line.lstrip(" ")
                     for line in lines)


def randomized_search(args: argparse.Namespace, entry: dict, symbol: str, active_content: str,
                      span: tuple[int, int], original_function: str, reference_assembly: Path,
                      reference: Path, expected_size: int, directory: Path, best_path: Path,
                      seed: int) -> tuple[dict, int | None, bool]:
    """Drive decomp-permuter, rescoring every reported improvement with the project scorer.

    Returns the report summary, the best project score and whether it is exact.
    """
    function_start, function_end = span
    started = time.monotonic()
    summary: dict = {
        "strategy": "randomized", "seconds": args.seconds, "seed": seed,
        "seed_given": args.seed is not None, "permuter_revision": permuter_revision(),
        "permuter_base_score": None, "permuter_outputs": 0, "permuter_iterations": None,
        "permuter_elapsed_seconds": None, "permuter_exit": None,
        "baseline_score": None, "compiled": 0, "invalid": 0, "rejected_context": 0,
        "improvements": 0, "best_score": None, "stop_reason": "permuter_exit",
    }
    best_score: int | None = None
    exact = False

    def splice(function: str) -> str:
        return active_content[:function_start] + function + "\n" + active_content[function_end:]

    def finish(stop_reason: str, failure: str | None = None) -> tuple[dict, int | None, bool]:
        summary["best_score"] = best_score
        summary["stop_reason"] = stop_reason
        summary["elapsed_seconds"] = time.monotonic() - started
        if failure is not None:
            summary["error"] = failure
        return summary, best_score, exact

    try:
        best_score = score_candidate(args.profile, symbol, splice(original_function), directory,
                                     reference, expected_size)
    except subprocess.CalledProcessError:
        return finish("tooling_failure", "the current candidate does not compile")
    except (PermuteError, OSError) as error:
        return finish("tooling_failure", str(error))
    summary["compiled"] = 1
    summary["baseline_score"] = best_score
    best_path.write_text(original_function + "\n", encoding="utf-8")
    print(f"{args.identifier}: baseline CURRENT ({best_score}) before the randomized search")
    if best_score == 0:
        try:
            if args.profile == "us" and entry.get("overlay") in {"game", "debugger"}:
                verify_exact_tables(entry, symbol, directory / "candidate.o", reference_assembly,
                                    expected_size)
        except (ValueError, OSError) as error:
            best_score = None
            best_path.unlink(missing_ok=True)
            return finish("table_gate_failure", f"candidate table gate: {error}")
        exact = True
        return finish("exact")

    try:
        work = prepare_permuter_directory(args.profile, symbol, active_content, reference, directory)
        permuter_started = time.monotonic()
        summary["permuter_base_score"], regenerated_base = permuter_base(work, seed)
        _, base_context = split_permuter_source(regenerated_base, args.identifier, symbol)
        timed_out, status = run_permuter_search(work, seed, args.seconds)
    except subprocess.CalledProcessError as error:
        return finish("tooling_failure", f"{error}")
    except (PermuteError, OSError, project_state.ProjectStateError) as error:
        return finish("tooling_failure", str(error))
    summary["permuter_elapsed_seconds"] = time.monotonic() - permuter_started
    summary["permuter_exit"] = status
    summary["permuter_iterations"] = permuter_iterations(work)
    outputs = permuter_outputs(work)
    summary["permuter_outputs"] = len(outputs)
    print(f"{args.identifier}: decomp-permuter base score {summary['permuter_base_score']}, "
          f"{len(outputs)} improved output(s) in {summary['permuter_elapsed_seconds']:.1f} s"
          + (f", {summary['permuter_iterations']} iterations" if summary["permuter_iterations"] else ""))

    stop_reason = "time_limit" if timed_out else "permuter_exit"
    for permuter_score, counter, source in outputs:
        label = source.parent.name
        try:
            function, context = split_permuter_source(source.read_text(encoding="utf-8"),
                                                      args.identifier, symbol)
        except (OSError, project_state.ProjectStateError):
            summary["rejected_context"] += 1
            continue
        if context != base_context:
            # Permutation may change only the target function.
            summary["rejected_context"] += 1
            print(f"{args.identifier}: rejected {label}; it changes text outside {symbol}")
            continue
        function = restyle_permuter_function(function)
        try:
            score = score_candidate(args.profile, symbol, splice(function), directory, reference,
                                    expected_size)
        except subprocess.CalledProcessError:
            summary["invalid"] += 1
            continue
        except (PermuteError, OSError) as error:
            return finish("tooling_failure", str(error))
        summary["compiled"] += 1
        if score == 0 and args.profile == "us" and entry.get("overlay") in {"game", "debugger"}:
            try:
                verify_exact_tables(entry, symbol, directory / "candidate.o", reference_assembly,
                                    expected_size)
            except (ValueError, OSError) as error:
                return finish("table_gate_failure", f"candidate table gate: {error}")
        if best_score is None or score < best_score:
            best_score = score
            best_path.write_text(function + "\n", encoding="utf-8")
            summary["improvements"] += 1
            print(f"{args.identifier}: improved CURRENT ({score}) from {label} "
                  f"(permuter score {permuter_score})")
        if score == 0:
            exact = True
            return finish("exact")
    return finish(stop_reason)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("profile", choices=("us", "eu"))
    parser.add_argument("identifier")
    parser.add_argument("--budget", type=int, default=32)
    parser.add_argument("--exhaustive", action="store_true",
                        help="use the full variant budget instead of stopping after 32 attempts without improvement")
    parser.add_argument("--stack-shapes", action="store_true",
                        help="probe storage shapes; stop at the first non-improvement")
    parser.add_argument("--randomized", action="store_true",
                        help="drive the pinned decomp-permuter instead of the deterministic variants; "
                             "every improvement it reports is rescored with the project scorer")
    parser.add_argument("--seconds", type=int, default=60,
                        help="wall-clock bound for the randomized search (default 60)")
    parser.add_argument("--seed", type=int,
                        help="reproducible randomized search; omitted seeds are drawn and recorded")
    args = parser.parse_args()
    if args.budget < 1 or args.budget > 5000:
        parser.error("--budget must be between 1 and 5000")
    if args.randomized and (args.exhaustive or args.stack_shapes):
        parser.error("--randomized cannot be combined with --exhaustive or --stack-shapes")
    if args.seconds < 1 or args.seconds > 3600:
        parser.error("--seconds must be between 1 and 3600")
    if args.seed is not None and not 0 <= args.seed < 2 ** 63:
        parser.error("--seed must be a non-negative 63-bit integer")
    if not args.randomized and (args.seed is not None or args.seconds != 60):
        parser.error("--seconds and --seed require --randomized")

    try:
        entry, symbol = work_item(args.identifier, args.profile)
        source, active_content = active_candidate_content(entry, args.identifier)
        function_start, function_end = candidate_function_span(
            active_content, args.identifier, symbol
        )
        original_function = active_content[function_start:function_end].rstrip("\n")
        if args.randomized:
            variants = []
        else:
            variants = (stack_source_variants(original_function, min(args.budget, 8))
                        if args.stack_shapes else source_variants(original_function, args.budget))
        seed = args.seed if args.seed is not None else secrets.randbelow(2 ** 32)
        reference_assembly = diff.ensure_reference_function(
            args.profile,
            symbol,
            game_reference=entry.get("overlay", "main") == "game",
        )
        reference = diff.reference_object(
            args.profile,
            symbol,
            game_reference=entry.get("overlay", "main") == "game",
            assembly=reference_assembly,
        )
        expected_size = diff.expected_function_size(args.profile, symbol)
        directory = ROOT / "build" / args.profile / "permute" / args.identifier
        directory.mkdir(parents=True, exist_ok=True)
        best_path = directory / "best.c"
        report = directory / "search-report.json"
        fingerprint = search_fingerprint(args.profile, active_content, reference, expected_size,
                                         args.budget, args.exhaustive, args.stack_shapes,
                                         randomized=(args.seconds, seed) if args.randomized else None)
        if report.is_file():
            saved = json.loads(report.read_text())
            if (saved.get("fingerprint") == fingerprint
                    and saved.get("stop_reason") in REUSABLE_STOP_REASONS
                    and isinstance(saved.get("best_score"), int) and saved["best_score"] > 0
                    and best_path.is_file()
                    and saved.get("best_sha256") == hashlib.sha256(best_path.read_bytes()).hexdigest()):
                print(f"{args.identifier}: unchanged search skipped; best CURRENT ({saved['best_score']}) "
                      f"saved to {best_path.relative_to(ROOT)}; change source or search settings to retry")
                return 1
        best_path.unlink(missing_ok=True)
        report.unlink(missing_ok=True)
        (directory / "scoring-failure.log").unlink(missing_ok=True)
        diff.write_settings(args.profile, source, directory=directory)

        if args.randomized:
            summary, best_score, exact = randomized_search(
                args, entry, symbol, active_content, (function_start, function_end),
                original_function, reference_assembly, reference, expected_size, directory,
                best_path, seed,
            )
            summary["fingerprint"] = fingerprint
            summary["best_sha256"] = (hashlib.sha256(best_path.read_bytes()).hexdigest()
                                      if best_path.is_file() else None)
            temporary = report.with_suffix(".json.tmp")
            temporary.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
            temporary.replace(report)
            if "error" in summary:
                print(f"error: {summary['error']}", file=sys.stderr)
                return 2
            if exact:
                print(f"{args.identifier}: exact randomized permutation saved to "
                      f"{best_path.relative_to(ROOT)}; host application and "
                      "authoritative finish required")
                return 0
            print(f"{args.identifier}: no exact match in {summary['permuter_outputs']} permuter "
                  f"output(s) ({summary['stop_reason']}, seed {seed}); best CURRENT ({best_score}) "
                  f"saved to {best_path.relative_to(ROOT)}"
                  + (f"; {summary['invalid']} invalid output(s) skipped" if summary["invalid"] else "")
                  + (f"; {summary['rejected_context']} output(s) rejected for changing other text"
                     if summary["rejected_context"] else ""))
            return 1

        best_score: int | None = None
        best_function = original_function
        exact_function: str | None = None
        started = time.monotonic()
        attempted = 0
        skipped = 0
        last_improvement = 0
        improvements = 0
        stop_reason = "variants_exhausted"
        failure: str | None = None
        for variant in variants:
            if not args.exhaustive and attempted + skipped >= max(32, last_improvement + 32):
                stop_reason = "plateau"
                break
            candidate_content = (
                active_content[:function_start]
                + variant
                + "\n"
                + active_content[function_end:]
            )
            try:
                score = score_candidate(
                    args.profile,
                    symbol,
                    candidate_content,
                    directory,
                    reference,
                    expected_size,
                )
            except subprocess.CalledProcessError:
                # Only candidate compilation uses check=True. Scorer failures
                # are tooling errors and must terminate the search instead.
                skipped += 1
                continue
            except (PermuteError, OSError) as error:
                failure = str(error)
                stop_reason = "tooling_failure"
                break
            attempted += 1
            if score == 0 and args.profile == "us" and entry.get("overlay") in {"game", "debugger"}:
                try:
                    verify_exact_tables(entry, symbol, directory / "candidate.o", reference_assembly,
                                        expected_size)
                except (ValueError, OSError) as error:
                    failure = f"candidate table gate: {error}"
                    stop_reason = "table_gate_failure"
                    break
            if best_score is None:
                best_score = score
                best_function = variant
                best_path.write_text(best_function + "\n", encoding="utf-8")
                print(f"{args.identifier}: baseline CURRENT ({score}) at variant {attempted}")
            elif args.stack_shapes and score >= best_score:
                stop_reason = "stack_shape_no_improvement"
                break
            elif score < best_score:
                best_score = score
                best_function = variant
                best_path.write_text(best_function + "\n", encoding="utf-8")
                last_improvement = attempted + skipped
                improvements += 1
                print(f"{args.identifier}: improved CURRENT ({score}) at variant {attempted}")
            if score == 0:
                exact_function = variant
                stop_reason = "exact"
                break

        summary = {
            "fingerprint": fingerprint,
            "best_sha256": hashlib.sha256(best_path.read_bytes()).hexdigest() if best_path.is_file() else None,
            "budget": args.budget, "exhaustive": args.exhaustive,
            "strategy": "stack_shapes" if args.stack_shapes else "general",
            "generated": len(variants), "compiled": attempted, "invalid": skipped,
            "improvements": improvements, "best_score": best_score,
            "stop_reason": stop_reason, "elapsed_seconds": time.monotonic() - started,
        }
        if failure is not None:
            summary["error"] = failure
        temporary = report.with_suffix(".json.tmp")
        temporary.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
        temporary.replace(report)
        if failure is not None:
            print(f"error: {failure}", file=sys.stderr)
            return 2
        if exact_function is None:
            if best_score is None:
                print(
                    f"{args.identifier}: no scored candidates; "
                    f"{skipped} invalid variant(s) skipped; no best candidate saved"
                )
                return 1
            print(
                f"{args.identifier}: no exact match in {attempted} variant(s); "
                f"best CURRENT ({best_score}) saved to {best_path.relative_to(ROOT)}"
                + (f"; {skipped} invalid variant(s) skipped" if skipped else "")
                + ("; plateau reached (use --exhaustive for the full budget)" if stop_reason == "plateau" else "")
            )
            return 1

        print(
            f"{args.identifier}: exact variant {attempted} saved to "
            f"{best_path.relative_to(ROOT)}; host application and "
            "authoritative finish required"
        )
        return 0
    except (
        PermuteError,
        ValueError,
        OSError,
        subprocess.CalledProcessError,
        project_state.ProjectStateError,
    ) as error:
        print(f"error: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
