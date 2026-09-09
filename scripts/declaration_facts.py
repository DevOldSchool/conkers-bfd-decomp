#!/usr/bin/env python3
"""Resolve m2c placeholder declarations from existing project evidence."""

from __future__ import annotations

import re
import candidate_syntax
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
FUNCTION_PLACEHOLDER = re.compile(
    r"^\s*M2C_UNK\s+(?P<symbol>[A-Za-z_]\w*)\((?P<args>[^()]*)\)\s*;.*$"
)
OBJECT_PLACEHOLDER = re.compile(
    r"^\s*M2C_UNK\s+(?P<symbol>[A-Za-z_]\w*)\s*;.*$"
)
TYPE_TEXT = (
    r"(?:(?:const|volatile|signed|unsigned)\s+)*"
    r"(?:struct\s+[A-Za-z_]\w*|[A-Za-z_]\w*)(?:\s*\*)*"
)
FUNCTION_EVIDENCE = re.compile(
    rf"(?m)^\s*(?:extern\s+|static\s+)?(?P<return>{TYPE_TEXT})\s+"
    r"(?P<symbol>[A-Za-z_]\w*)\((?P<args>[^(){};]*)\)\s*(?:;|\{)"
)
OBJECT_EVIDENCE = re.compile(
    rf"(?m)^\s*(?:extern\s+|static\s+)?(?P<type>{TYPE_TEXT})\s+"
    r"(?P<symbol>[A-Za-z_]\w*)\s*(?:;|=)"
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
    symbol: str, expected_arguments: str, *, root: Path = ROOT
) -> Declaration | None:
    expected = argument_types(expected_arguments)
    if expected is None:
        return None
    returns: dict[str, set[str]] = {}
    for path in evidence_files(root):
        try:
            text = active_text(path.read_text(encoding="utf-8"))
        except (OSError, UnicodeDecodeError):
            continue
        for match in FUNCTION_EVIDENCE.finditer(text):
            if match.group("symbol") != symbol:
                continue
            actual = argument_types(match.group("args"))
            if actual != expected:
                continue
            return_type = normalize_type(match.group("return"))
            returns.setdefault(return_type, set()).add(str(path.relative_to(root)))
    if len(returns) != 1:
        return None
    return_type, paths = next(iter(returns.items()))
    arguments = ", ".join(expected) if expected else "void"
    return Declaration(
        f"{return_type} {symbol}({arguments});",
        symbol,
        tuple(sorted(paths)),
    )


def object_declaration(symbol: str, *, root: Path = ROOT) -> Declaration | None:
    types: dict[str, set[str]] = {}
    for path in evidence_files(root):
        try:
            text = active_text(path.read_text(encoding="utf-8"))
        except (OSError, UnicodeDecodeError):
            continue
        for match in OBJECT_EVIDENCE.finditer(text):
            if match.group("symbol") != symbol:
                continue
            type_name = normalize_type(match.group("type"))
            types.setdefault(type_name, set()).add(str(path.relative_to(root)))
    if len(types) != 1:
        return None
    type_name, paths = next(iter(types.items()))
    return Declaration(
        f"extern {type_name} {symbol};",
        symbol,
        tuple(sorted(paths)),
    )


def declaration_already_present(source: str, declaration: Declaration) -> bool:
    if "(" in declaration.text:
        pattern = re.compile(
            rf"(?m)^\s*(?:extern\s+|static\s+)?{TYPE_TEXT}\s+"
            rf"{re.escape(declaration.symbol)}\([^;{{}}]*\)\s*(?:;|\{{)"
        )
    else:
        pattern = re.compile(
            rf"(?m)^\s*(?:extern\s+|static\s+)?{TYPE_TEXT}\s+"
            rf"{re.escape(declaration.symbol)}\s*(?:;|=)"
        )
    return pattern.search(active_text(source)) is not None


def resolve_required_declarations(
    prefix: str, source: str, *, root: Path = ROOT
) -> tuple[list[str], list[str]]:
    """Return declarations safe to insert and human-readable evidence summaries."""

    declarations: list[Declaration] = []
    unresolved: list[str] = []
    if any(token.text in ("{", "}") for token in candidate_syntax.tokens(prefix)):
        raise DeclarationError("unresolved composite declaration in m2c context; refusing partial fields")
    for line in prefix.splitlines():
        stripped = line.strip()
        if not stripped or not stripped.endswith((";", "*/")):
            continue
        function = FUNCTION_PLACEHOLDER.match(stripped)
        if function is not None:
            resolved = function_declaration(
                function.group("symbol"), function.group("args"), root=root
            )
            if resolved is None:
                unresolved.append(function.group("symbol"))
            else:
                declarations.append(resolved)
            continue
        obj = OBJECT_PLACEHOLDER.match(stripped)
        if obj is not None:
            resolved = object_declaration(obj.group("symbol"), root=root)
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


def later_function_declarations(definition: str, source: str, visible: str) -> tuple[list[str], list[str]]:
    """Repeat a proven later prototype before the candidate's first use."""

    tokens = candidate_syntax.tokens(definition)
    calls = {token.text for index, token in enumerate(tokens[:-1]) if tokens[index + 1].text == "("}
    declarations: dict[str, set[str]] = {}
    for match in FUNCTION_EVIDENCE.finditer(active_text(source)):
        symbol = match.group("symbol")
        if symbol not in calls:
            continue
        arguments = argument_types(match.group("args"))
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
