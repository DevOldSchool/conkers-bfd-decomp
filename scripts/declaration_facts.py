#!/usr/bin/env python3
"""Resolve m2c placeholder declarations from existing project evidence."""

from __future__ import annotations

import re
import candidate_syntax
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
OBJECT_PLACEHOLDER = re.compile(
    r"^\s*(?:extern\s+)?M2C_UNK\s+(?P<symbol>[A-Za-z_]\w*)\s*;.*$"
)
TYPE_TEXT = (
    r"(?:(?:const|volatile|signed|unsigned)\s+)*"
    r"(?:struct\s+[A-Za-z_]\w*|[A-Za-z_]\w*)(?:\s*\*)*"
)
FUNCTION_PLACEHOLDER = re.compile(
    rf"^\s*(?:extern\s+)?(?P<return>{TYPE_TEXT})(?:\s+|(?<=\*))"
    r"(?P<symbol>[A-Za-z_]\w*)\((?P<args>[^()]*)\)\s*;.*$"
)
FUNCTION_EVIDENCE = re.compile(
    rf"(?m)^\s*(?:extern\s+|static\s+)?(?P<return>{TYPE_TEXT})\s+"
    r"(?P<symbol>[A-Za-z_]\w*)\((?P<args>[^(){};]*)\)\s*(?:;|\{)"
)
OBJECT_EVIDENCE = re.compile(
    rf"(?m)^\s*(?P<storage>extern\s+|static\s+)?(?P<type>{TYPE_TEXT})(?:\s+|(?<=\*))"
    r"(?P<symbol>[A-Za-z_]\w*)\s*(?P<array>(?:\[[^\]\n]*\]\s*)*)(?:;|=)"
)
FUNCTION_POINTER_OBJECT_EVIDENCE = re.compile(
    rf"(?m)^\s*(?P<storage>extern\s+|static\s+)?"
    rf"(?P<return>{TYPE_TEXT})\s*\(\s*\*\s*"
    r"(?P<symbol>[A-Za-z_]\w*)\s*"
    r"(?P<array>(?:\[[^\]\n]*\]\s*)*)\)\s*"
    r"\((?P<args>[^()\n]*)\)\s*(?:;|=)"
)
PREPROCESSOR_IF_ZERO = re.compile(r"^\s*#\s*if\s+0(?:\s|$)")
PREPROCESSOR_IF = re.compile(r"^\s*#\s*if(?:def|ndef)?\b")
PREPROCESSOR_ENDIF = re.compile(r"^\s*#\s*endif\b")


class DeclarationError(ValueError):
    """Raised when a required declaration cannot be proven uniquely."""


@dataclass(frozen=True)
class Declaration:
    text: str
    symbol: str
    evidence: tuple[str, ...]


def split_arguments(arguments: str) -> list[str]:
    parts: list[str] = []
    start = 0
    depth = 0
    for index, character in enumerate(arguments):
        if character in "([{":
            depth += 1
        elif character in ")]}":
            depth -= 1
        elif character == "," and depth == 0:
            parts.append(arguments[start:index].strip())
            start = index + 1
    tail = arguments[start:].strip()
    if tail:
        parts.append(tail)
    return parts


def normalize_type(type_name: str) -> str:
    normalized = re.sub(r"\s+", " ", type_name.strip())
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    return normalized


def argument_type(argument: str) -> str | None:
    argument = argument.strip()
    if not argument or argument == "void":
        return argument
    if argument == "..." or "(" in argument or "[" in argument:
        return None
    match = re.match(r"^(?P<type>.+?)(?:\s+|\*\s*)(?P<name>[A-Za-z_]\w*)$", argument)
    if match is not None:
        candidate = match.group("type")
        if "*" in argument[match.start("type") + len(candidate) : match.start("name")]:
            candidate += " *"
        return normalize_type(candidate)
    return normalize_type(argument)


def argument_types(arguments: str) -> tuple[str, ...] | None:
    parts = split_arguments(arguments)
    if parts == ["void"] or not parts:
        return ()
    normalized = tuple(argument_type(part) for part in parts)
    if any(part is None for part in normalized):
        return None
    return tuple(part for part in normalized if part is not None)


def active_text(text: str) -> str:
    """Remove disabled preprocessor regions so preserved candidates are not evidence."""

    output: list[str] = []
    disabled_depth = 0
    conditional_depth = 0
    for line in text.splitlines(keepends=True):
        if PREPROCESSOR_IF_ZERO.match(line):
            disabled_depth += 1
            conditional_depth += 1
            continue
        if PREPROCESSOR_IF.match(line):
            conditional_depth += 1
            if disabled_depth:
                disabled_depth += 1
            elif not PREPROCESSOR_IF_ZERO.match(line):
                output.append(line)
            continue
        if PREPROCESSOR_ENDIF.match(line):
            if disabled_depth:
                disabled_depth -= 1
            conditional_depth = max(0, conditional_depth - 1)
            if not disabled_depth:
                output.append(line)
            continue
        if not disabled_depth:
            output.append(line)
    return "".join(output)


def evidence_files(root: Path = ROOT) -> list[Path]:
    files: list[Path] = []
    for directory, suffixes in ((root / "src", {".c", ".h"}), (root / "include", {".h"})):
        if directory.is_dir():
            files.extend(
                path
                for path in directory.rglob("*")
                if path.is_file() and path.suffix in suffixes
            )
    return sorted(set(files))


def function_declaration(
    symbol: str, expected_arguments: str, *, expected_return: str = "M2C_UNK",
    root: Path = ROOT, source: str = ""
) -> Declaration | None:
    expected = argument_types(expected_arguments)
    if expected is None:
        return None
    # Resolve unknown parameter types as well as unknown returns, but never
    # repair argument count here: omitted register arguments require fresh m2c
    # output generated with a complete prototype.
    from call_signatures import (
        signature_index, source_signatures, sdk_alias_signatures, sdk_alias_evidence,
    )
    origins: dict[str, str] = {}
    signature = signature_index(root, {symbol}, source=source, evidence=origins).get(symbol)
    if signature is None or len(signature.arguments) != len(expected):
        return None
    if (expected_return != "M2C_UNK"
            and normalize_type(signature.result) != normalize_type(expected_return)):
        return None
    if any(want != "M2C_UNK" and normalize_type(actual) != want
           for want, actual in zip(expected, signature.arguments)):
        return None
    if symbol in source_signatures(source, {symbol}):
        paths = ["active declaration in the allowed source"]
    elif symbol in sdk_alias_signatures(root, {symbol}):
        paths = [sdk_alias_evidence(symbol)]
    elif origins.get(symbol, '').startswith('matched US definition in '):
        paths = [origins[symbol]]
    else:
        paths = [str(path.relative_to(root)) for path in evidence_files(root)
                 if re.search(rf"\b{re.escape(symbol)}\s*\(", active_text(path.read_text(encoding="utf-8")))]
    return Declaration(
        signature.declaration(symbol),
        symbol,
        tuple(sorted(paths)),
    )


def object_declaration(symbol: str, *, root: Path = ROOT, source: str = "") -> Declaration | None:
    from call_signatures import c_type

    # The source may already use an object through a deliberate local view.
    # Reuse that exact declarator instead of importing another unit's type.
    local = re.sub(r"/\*.*?\*/|//[^\n]*", "", source, flags=re.S)
    local = active_text(local)
    depth = 0
    top_level = set()
    for token in candidate_syntax.tokens(local):
        if depth == 0:
            top_level.add(token.start)
        depth += (token.text == "{") - (token.text == "}")
    pointer_choices: set[str] = set()
    for match in FUNCTION_POINTER_OBJECT_EVIDENCE.finditer(local):
        if match.group("symbol") != symbol or match.start("symbol") not in top_level:
            continue
        array = re.sub(r"\s+", "", match.group("array"))
        arguments = argument_types(match.group("args"))
        result = normalize_type(match.group("return"))
        if ((match.group("storage") or "").strip() == "static"
                or not re.fullmatch(r"(?:\[(?:0x[0-9A-Fa-f]+|[0-9]+)?\])*", array)
                or arguments is None
                or c_type(result) is None
                or any(c_type(argument, parameter=True) is None for argument in arguments)):
            return None
        pointer_choices.add(
            f"extern {result} (*{symbol}{array})"
            f"({', '.join(arguments) if arguments else 'void'});"
        )
    if pointer_choices:
        if len(pointer_choices) != 1:
            return None
        return Declaration(next(iter(pointer_choices)), symbol,
                           ("active file-scope declaration in the allowed source",))
    choices: set[str] = set()
    for match in OBJECT_EVIDENCE.finditer(local):
        if match.group("symbol") != symbol or match.start("symbol") not in top_level:
            continue
        type_name = normalize_type(match.group("type"))
        array = re.sub(r"\s+", "", match.group("array"))
        if ((match.group("storage") or "").strip() == "static"
                or c_type(type_name) in (None, "void")
                or not re.fullmatch(r"(?:\[(?:0x[0-9A-Fa-f]+|[0-9]+)?\])*", array)):
            return None
        choices.add(f"extern {type_name} {symbol}{array};")
    if choices:
        if len(choices) != 1:
            return None
        return Declaration(next(iter(choices)), symbol,
                           ("active file-scope declaration in the allowed source",))

    types: dict[str, set[str]] = {}
    pointer_types: dict[str, set[str]] = {}
    for path in evidence_files(root):
        try:
            text = re.sub(r"/\*.*?\*/|//[^\n]*", "", path.read_text(encoding="utf-8"), flags=re.S)
            text = active_text(text)
        except (OSError, UnicodeDecodeError):
            continue
        depth = 0
        top_level = set()
        for token in candidate_syntax.tokens(text):
            if depth == 0:
                top_level.add(token.start)
            depth += (token.text == "{") - (token.text == "}")
        file_pointer_types: dict[str, set[str]] = {}
        for match in FUNCTION_POINTER_OBJECT_EVIDENCE.finditer(text):
            if match.group("symbol") != symbol or match.start("symbol") not in top_level:
                continue
            array = re.sub(r"\s+", "", match.group("array"))
            arguments = argument_types(match.group("args"))
            result = normalize_type(match.group("return"))
            if ((match.group("storage") or "").strip() == "static"
                    or not re.fullmatch(r"(?:\[(?:0x[0-9A-Fa-f]+|[0-9]+)?\])*", array)
                    or arguments is None
                    or c_type(result) is None
                    or any(c_type(argument, parameter=True) is None for argument in arguments)):
                return None
            declaration = (
                f"extern {result} (*{symbol}{array})"
                f"({', '.join(arguments) if arguments else 'void'});"
            )
            file_pointer_types.setdefault(declaration, set()).add(str(path.relative_to(root)))
        for declaration, paths in file_pointer_types.items():
            pointer_types.setdefault(declaration, set()).update(paths)
        for match in OBJECT_EVIDENCE.finditer(text):
            if match.group("symbol") != symbol or match.start("symbol") not in top_level:
                continue
            type_name = normalize_type(match.group("type"))
            # Only import self-contained external scalar/pointer declarations.
            # Arrays and source-local types need separate declarator evidence.
            if (match.group("storage") or "").strip() == "static" or match.group("array"):
                return None
            if c_type(type_name) in (None, "void"):
                return None
            if file_pointer_types:
                return None
            types.setdefault(type_name, set()).add(str(path.relative_to(root)))
    if pointer_types:
        if len(pointer_types) != 1 or types:
            return None
        declaration, paths = next(iter(pointer_types.items()))
        return Declaration(declaration, symbol, tuple(sorted(paths)))
    if len(types) != 1:
        return None
    type_name, paths = next(iter(types.items()))
    return Declaration(
        f"extern {type_name} {symbol};",
        symbol,
        tuple(sorted(paths)),
    )


def declaration_already_present(source: str, declaration: Declaration) -> bool:
    if "(*" in declaration.text:
        pointer = re.compile(
            rf"(?m)^\s*(?:extern\s+|static\s+)?{TYPE_TEXT}\s*\(\s*\*\s*"
            rf"{re.escape(declaration.symbol)}\s*(?:\[[^\]\n]*\]\s*)*\)\s*"
            r"\([^()\n]*\)\s*(?:;|\{{)"
        )
        return pointer.search(active_text(source)) is not None
    if "(" in declaration.text:
        pattern = re.compile(
            rf"(?m)^\s*(?:extern\s+|static\s+)?{TYPE_TEXT}(?:\s+|(?<=\*))"
            rf"{re.escape(declaration.symbol)}\([^;{{}}]*\)\s*(?:;|\{{)"
        )
    else:
        pattern = re.compile(
            rf"(?m)^\s*(?:extern\s+|static\s+)?{TYPE_TEXT}(?:\s+|(?<=\*))"
            rf"{re.escape(declaration.symbol)}\s*(?:\[[^\]\n]*\]\s*)*(?:;|=)"
        )
    return pattern.search(active_text(source)) is not None


def resolve_required_declarations(
    prefix: str, source: str, *, root: Path = ROOT
) -> tuple[list[str], list[str]]:
    """Return declarations safe to insert and human-readable evidence summaries."""

    declarations: list[Declaration] = []
    unresolved: list[str] = []
    tokens = candidate_syntax.tokens(prefix)
    if any(token.text in ("{", "}") for token in tokens):
        raise DeclarationError("unresolved composite declaration in m2c context; refusing partial fields")
    # Tokenize the complete prefix so standalone and multiline evidence
    # comments cannot become declarations. Keep real declaration lines intact:
    # trailing ABI markers must survive to prevent later return-type inference.
    code_lines = {prefix.count("\n", 0, token.start) for token in tokens}
    for number, line in enumerate(prefix.splitlines()):
        if number not in code_lines:
            continue
        stripped = line.strip()
        if not stripped or not stripped.endswith((";", "*/")):
            continue
        function = FUNCTION_PLACEHOLDER.match(stripped)
        if function is not None and "M2C_" in function.group("return") + function.group("args"):
            resolved = function_declaration(
                function.group("symbol"), function.group("args"),
                expected_return=function.group("return"), root=root, source=source
            )
            if resolved is None:
                unresolved.append(function.group("symbol"))
            else:
                declarations.append(resolved)
            continue
        obj = OBJECT_PLACEHOLDER.match(stripped)
        if obj is not None:
            resolved = object_declaration(obj.group("symbol"), root=root, source=source)
            if resolved is None:
                unresolved.append(obj.group("symbol"))
            else:
                declarations.append(resolved)
            continue
        if "M2C_" in stripped:
            unresolved.append(stripped)
            continue
        symbol_match = re.search(r"\b([A-Za-z_]\w*)\s*(?:\(|;)" , stripped)
        symbol = symbol_match.group(1) if symbol_match is not None else stripped
        declarations.append(Declaration(stripped, symbol, ("m2c concrete declaration",)))

    unique: dict[str, Declaration] = {declaration.text: declaration for declaration in declarations}
    insert = [
        declaration.text
        for declaration in unique.values()
        if not declaration_already_present(source, declaration)
    ]
    evidence = [
        f"{declaration.symbol}: {', '.join(declaration.evidence)}"
        for declaration in unique.values()
        if declaration.evidence
    ]
    if unresolved:
        names = ", ".join(sorted(set(unresolved)))
        raise DeclarationError(f"no unique project declaration evidence for: {names}")
    return insert, evidence


def file_scope_matches(pattern: re.Pattern, source: str):
    """Yield declarations at file scope, excluding comments and disabled C."""
    active = active_text(re.sub(r"/\*.*?\*/|//[^\n]*", "", source, flags=re.S))
    depth = 0
    top_level = set()
    for token in candidate_syntax.tokens(active):
        if depth == 0:
            top_level.add(token.start)
        depth += (token.text == "{") - (token.text == "}")
    for match in pattern.finditer(active):
        if match.start("symbol") in top_level:
            yield match


def later_function_declarations(definition: str, source: str, visible: str) -> tuple[list[str], list[str]]:
    """Repeat a proven later prototype before the candidate's first use."""

    tokens = candidate_syntax.tokens(definition)
    calls = {token.text for index, token in enumerate(tokens[:-1]) if tokens[index + 1].text == "("}
    declarations: dict[str, set[str]] = {}
    for match in file_scope_matches(FUNCTION_EVIDENCE, source):
        symbol = match.group("symbol")
        if symbol not in calls:
            continue
        parts = split_arguments(match.group("args"))
        variadic = len(parts) > 1 and parts[-1] == "..."
        arguments = argument_types(", ".join(parts[:-1]) if variadic else match.group("args"))
        if variadic and arguments:
            arguments += ("...",)
        if arguments is None:
            continue
        text = f"{normalize_type(match.group('return'))} {symbol}({', '.join(arguments) if arguments else 'void'});"
        declarations.setdefault(symbol, set()).add(text)
    needed: list[str] = []
    evidence: list[str] = []
    for symbol, choices in sorted(declarations.items()):
        if len(choices) != 1:
            raise DeclarationError(f"no unique project declaration evidence for: {symbol}")
        declaration = Declaration(next(iter(choices)), symbol, ())
        if not declaration_already_present(visible, declaration):
            needed.append(declaration.text)
            evidence.append(f"{symbol}: later active declaration in the allowed source")
    return needed, evidence


def later_object_declarations(definition: str, source: str, visible: str) -> tuple[list[str], list[str]]:
    """Repeat a unique active file-scope extern before its first use."""

    pattern = re.compile(
        rf"(?m)^[ \t]*extern\s+(?P<type>{TYPE_TEXT})(?:\s+|(?<=\*))"
        r"(?P<symbol>[A-Za-z_]\w*)(?P<array>(?:\[\s*\w*\s*\])*)\s*;"
    )

    def declarations(text: str) -> dict[str, set[str]]:
        active = active_text(text)
        depth = 0
        top_level = set()
        for token in candidate_syntax.tokens(active):
            if depth == 0:
                top_level.add(token.start)
            depth += (token.text == "{") - (token.text == "}")
        found: dict[str, set[str]] = {}
        for match in pattern.finditer(active):
            if active.index("extern", match.start(), match.end()) not in top_level:
                continue
            symbol = match.group("symbol")
            declaration = f"extern {normalize_type(match.group('type'))} {symbol}{match.group('array')};"
            found.setdefault(symbol, set()).add(declaration)
        return found

    used = {token.text for token in candidate_syntax.tokens(definition)}
    present = declarations(visible)
    needed, evidence = [], []
    for symbol, choices in sorted(declarations(source).items()):
        if symbol not in used:
            continue
        if len(choices) != 1:
            raise DeclarationError(f"no unique project declaration evidence for: {symbol}")
        if choices == present.get(symbol):
            continue
        needed.append(next(iter(choices)))
        evidence.append(f"{symbol}: later active file-scope extern in the allowed source")
    return needed, evidence


def object_evidence_index(root: Path = ROOT) -> dict[str, tuple[str, ...]]:
    """Index declaration spellings for invalidation only, never as type proof."""
    result: dict[str, set[str]] = {}
    for path in evidence_files(root):
        source = active_text(path.read_text(encoding="utf-8"))
        for pattern in (OBJECT_EVIDENCE, FUNCTION_POINTER_OBJECT_EVIDENCE):
            for match in file_scope_matches(pattern, source):
                if match.group("storage") and match.group("storage").strip() == "static":
                    continue
                result.setdefault(match.group("symbol"), set()).add(match.group(0).strip())
    return {symbol: tuple(sorted(values)) for symbol, values in result.items()}
