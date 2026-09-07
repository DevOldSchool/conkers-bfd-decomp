#!/usr/bin/env python3
"""Prepare safe C candidates and generate semantics-preserving source variants."""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path

import declaration_facts


DEFINITION = re.compile(
    r"^[A-Za-z_][^;\n{}]*\b(?P<symbol>[A-Za-z_][A-Za-z0-9_]*)\([^;\n]*\)\s*\{",
    re.MULTILINE,
)
M2C_FIELD_START = re.compile(r"\bM2C_FIELD\s*\(")
FIELD_TYPE = re.compile(
    r"^(?P<scalar>(?:s|u)(?:8|16|32)|f(?:32|64)|char|int|void)"
    r"(?P<pointers>(?:\s*\*){0,2})$"
)
FIELD_OFFSET = re.compile(r"^-?(?:0x[0-9A-Fa-f]+|\d+)$")
PLACEHOLDER = re.compile(r"\bM2C_[A-Za-z0-9_]+\b")
VOID_POINTER_DECLARATION = re.compile(
    r"(?m)^\s*void\s*\*\s*(?P<name>[A-Za-z_]\w*)\s*;\s*$"
)
POINTER_INTEGER_ASSIGNMENT = re.compile(
    r"(?m)^(?P<indent>\s*)(?P<name>[A-Za-z_]\w*)\s*=\s*"
    r"(?P<rhs>(?:"
    r"\*\(\s*[su]32\s*\*\s*\)\s*"
    r"\(\s*\(u8\s*\*\s*\)\s*[A-Za-z_]\w*\s*\+\s*"
    r"(?:0x[0-9A-Fa-f]+|\d+)\s*\)\s*\+\s*"
    r"(?:0x[0-9A-Fa-f]+|\d+)"
    r"|\(\s*[A-Za-z_]\w*\s*<<\s*\d+\s*\)\s*\+\s*[A-Za-z_]\w*"
    r"|[A-Za-z_]\w*\s*\+\s*\(\s*[A-Za-z_]\w*\s*<<\s*\d+\s*\)"
    r"))\s*;\s*$"
)
SIMPLE_OPERAND = r"(?:[A-Za-z_]\w*|(?:0x[0-9A-Fa-f]+|\d+)(?:[uUlL]+)?)"
COMMUTATIVE = re.compile(
    rf"(?P<left>{SIMPLE_OPERAND})\s*(?P<op>[|&^+*])\s*(?P<right>{SIMPLE_OPERAND})"
)
ASSIGNMENT = re.compile(
    rf"(?m)^(?P<indent>\s*)(?P<name>[A-Za-z_]\w*)\s*=\s*"
    rf"(?P=name)\s*(?P<op>[|&^+*])\s*(?P<rhs>{SIMPLE_OPERAND})\s*;\s*$"
)
COMPOUND_ASSIGNMENT = re.compile(
    rf"(?m)^(?P<indent>\s*)(?P<name>[A-Za-z_]\w*)\s*"
    rf"(?P<op>[|&^+*])=\s*(?P<rhs>{SIMPLE_OPERAND})\s*;\s*$"
)


class CandidateError(ValueError):
    """Raised when an m2c starter cannot be converted without guessing."""


@dataclass(frozen=True)
class PreparedCandidate:
    definition: str
    declarations: tuple[str, ...]
    evidence: tuple[str, ...]


def sanitize_fields(definition: str) -> str:
    """Replace aligned scalar M2C_FIELD uses with explicit byte-offset accesses."""

    def matching_parenthesis(opening: int) -> int | None:
        depth = 0
        for index in range(opening, len(definition)):
            if definition[index] == "(":
                depth += 1
            elif definition[index] == ")":
                depth -= 1
                if depth == 0:
                    return index
        return None

    def arguments(payload: str) -> list[str]:
        parts: list[str] = []
        start = 0
        depth = 0
        for index, character in enumerate(payload):
            if character == "(":
                depth += 1
            elif character == ")":
                depth -= 1
            elif character == "," and depth == 0:
                parts.append(payload[start:index].strip())
                start = index + 1
        parts.append(payload[start:].strip())
        return parts

    output: list[str] = []
    cursor = 0
    while match := M2C_FIELD_START.search(definition, cursor):
        output.append(definition[cursor : match.start()])
        opening = definition.find("(", match.start(), match.end())
        closing = matching_parenthesis(opening)
        if closing is None:
            output.append(definition[match.start() :])
            cursor = len(definition)
            break
        original = definition[match.start() : closing + 1]
        parts = arguments(definition[opening + 1 : closing])
        if len(parts) != 3:
            output.append(original)
            cursor = closing + 1
            continue
        base, type_text, offset = parts
        type_match = FIELD_TYPE.fullmatch(type_text)
        if not base or type_match is None or FIELD_OFFSET.fullmatch(offset) is None:
            output.append(original)
            cursor = closing + 1
            continue
        pointers = type_match.group("pointers")
        if pointers:
            cast_type = type_match.group("scalar") + pointers
        else:
            cast_type = type_match.group("scalar") + " *"
        output.append(f"*({cast_type})((u8 *){base} + {offset})")
        cursor = closing + 1
    output.append(definition[cursor:])
    return "".join(output)


def sanitize_unused_parameters(definition: str) -> str:
    """Give unused unknown register parameters a neutral 32-bit scalar type."""

    opening = definition.find("{")
    if opening < 0:
        return definition
    header = definition[:opening]
    body = definition[opening + 1 :]
    unknown = re.compile(r"\bM2C_UNK\s+(?P<name>arg[0-3])\b")

    def replace(match: re.Match[str]) -> str:
        name = match.group("name")
        if re.search(rf"\b{re.escape(name)}\b", body):
            return match.group(0)
        return f"s32 {name}"

    return unknown.sub(replace, header) + definition[opening:]


def sanitize_pointer_integer_assignments(definition: str) -> str:
    """Make m2c's integer-backed address assignments explicit for IDO."""

    pointer_names = {
        match.group("name") for match in VOID_POINTER_DECLARATION.finditer(definition)
    }

    def replace(match: re.Match[str]) -> str:
        if match.group("name") not in pointer_names:
            return match.group(0)
        return (
            f"{match.group('indent')}{match.group('name')} = "
            f"(void *)({match.group('rhs')});"
        )

    return POINTER_INTEGER_ASSIGNMENT.sub(replace, definition)


def prepare_starter(
    starter: str,
    symbol: str,
    source: str,
    *,
    root: Path = declaration_facts.ROOT,
) -> PreparedCandidate:
    definitions = list(DEFINITION.finditer(starter))
    if len(definitions) != 1 or definitions[0].group("symbol") != symbol:
        raise CandidateError(f"m2c did not emit exactly one {symbol} definition")
    match = definitions[0]
    prefix = starter[: match.start()]
    definition = sanitize_unused_parameters(
        sanitize_pointer_integer_assignments(
            sanitize_fields(starter[match.start() :].strip())
        )
    )
    if not definition.endswith("}"):
        raise CandidateError("m2c emitted content after the function definition")
    placeholders = sorted(set(PLACEHOLDER.findall(definition)))
    if placeholders:
        raise CandidateError(
            "m2c body contains unresolved placeholder(s): " + ", ".join(placeholders)
        )
    try:
        declarations, evidence = declaration_facts.resolve_required_declarations(
            prefix, source, root=root
        )
    except declaration_facts.DeclarationError as error:
        raise CandidateError(str(error)) from error
    return PreparedCandidate(
        definition + "\n",
        tuple(declarations),
        tuple(evidence),
    )


def swap_commutative_expressions(function: str) -> list[str]:
    variants: list[str] = []
    for match in COMMUTATIVE.finditer(function):
        if match.group("left") == match.group("right"):
            continue
        variants.append(
            function[: match.start()]
            + match.group("right")
            + f" {match.group('op')} "
            + match.group("left")
            + function[match.end() :]
        )
    return variants


def assignment_form_variants(function: str) -> list[str]:
    variants: list[str] = []
    for match in ASSIGNMENT.finditer(function):
        replacement = (
            f"{match.group('indent')}{match.group('name')} "
            f"{match.group('op')}= {match.group('rhs')};"
        )
        variants.append(function[: match.start()] + replacement + function[match.end() :])
    for match in COMPOUND_ASSIGNMENT.finditer(function):
        replacement = (
            f"{match.group('indent')}{match.group('name')} = {match.group('name')} "
            f"{match.group('op')} {match.group('rhs')};"
        )
        variants.append(function[: match.start()] + replacement + function[match.end() :])
    return variants


def rewrite_variants(seeds: list[str], budget: int) -> list[str]:
    """Expand candidates deterministically with bounded, local rewrite rules."""

    variants: list[str] = []
    seen: set[str] = set()
    queue = list(seeds)
    while queue and len(variants) < budget:
        candidate = queue.pop(0)
        if candidate in seen:
            continue
        seen.add(candidate)
        variants.append(candidate)
        generated = assignment_form_variants(candidate)
        generated.extend(swap_commutative_expressions(candidate))
        queue.extend(variant for variant in generated if variant not in seen)
    return variants
