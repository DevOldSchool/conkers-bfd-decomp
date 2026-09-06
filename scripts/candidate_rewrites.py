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
M2C_FIELD = re.compile(
    r"M2C_FIELD\(\s*(?P<base>[A-Za-z_]\w*)\s*,\s*"
    r"(?P<type>(?:s|u)(?:8|16|32)|f(?:32|64)|char|int)(?:\s*\*)?\s*,\s*"
    r"(?P<offset>(?:0x[0-9A-Fa-f]+|\d+))\s*\)"
)
PLACEHOLDER = re.compile(r"\bM2C_[A-Za-z0-9_]+\b")
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

    def replace(match: re.Match[str]) -> str:
        type_name = match.group("type")
        base = match.group("base")
        offset = match.group("offset")
        return f"*({type_name} *)((u8 *){base} + {offset})"

    return M2C_FIELD.sub(replace, definition)


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
        sanitize_fields(starter[match.start() :].strip())
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
