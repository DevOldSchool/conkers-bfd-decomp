#!/usr/bin/env python3
"""Prepare safe C candidates and generate semantics-preserving source variants."""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path

import declaration_facts
import candidate_syntax


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
KNOWN_INTRINSICS = {
    "sqrtf": ("f32 sqrtf(f32);", "#pragma intrinsic(sqrtf)"),
}
VOID_POINTER_DECLARATION = re.compile(
    r"\bvoid(?P<spacing>\s*\*\s*)(?P<name>[A-Za-z_]\w*)\b"
)
POINTER_DECLARATION = re.compile(
    r"\b(?P<type>void|[su](?:8|16|32|64)|f(?:32|64))(?P<spacing>\s*\*\s*)"
    r"(?P<name>[A-Za-z_]\w*)\b"
)
S32_DECLARATION = re.compile(r"\bs32\s+(?P<name>[A-Za-z_]\w*)\b")
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


def required_intrinsic_declarations(
    definition: str, existing_source: str
) -> tuple[tuple[str, ...], tuple[str, ...]]:
    """Return source-local IDO declarations needed by m2c intrinsic expressions."""

    declarations: list[str] = []
    evidence: list[str] = []
    declaration_text = existing_source
    for intrinsic, required in KNOWN_INTRINSICS.items():
        if not re.search(rf"\b{re.escape(intrinsic)}\s*\(", definition):
            continue
        prototype, pragma = required
        if not re.search(
            rf"\b(?:f32|float)\s+{re.escape(intrinsic)}\s*\(\s*"
            rf"(?:f32|float)(?:\s+[A-Za-z_]\w*)?\s*\)\s*;",
            declaration_text,
        ):
            declarations.append(prototype)
            declaration_text += "\n" + prototype
        if not re.search(
            rf"#\s*pragma\s+intrinsic\s*\(\s*{re.escape(intrinsic)}\s*\)",
            declaration_text,
        ):
            declarations.append(pragma)
            declaration_text += "\n" + pragma
        evidence.append(f"{intrinsic}: m2c intrinsic expression")
    return tuple(declarations), tuple(evidence)


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


def widen_store_only_parameters(definition: str, symbol: str, *, root: Path) -> tuple[str, list[str]]:
    """Keep inferred byte/halfword store arguments in their 32-bit ABI registers.

    Only direct stores of the parameter qualify. Arithmetic, return values,
    address use, and any existing project prototype leave the signature alone.
    """

    opening = definition.find("{")
    header, body = definition[:opening], definition[opening:]
    narrow = list(re.finditer(r"\b(?P<type>[su](?:8|16))\s+(?P<name>arg[0-3])\b", header))
    if not narrow:
        return definition, []
    items = candidate_syntax.tokens(body)
    store_uses: dict[str, set[int]] = {}
    for index, token in enumerate(items):
        if token.text != "*" or index == 0 or items[index - 1].text not in ("{", ";", "}", ")"):
            continue
        try:
            parser = candidate_syntax.Parser(items, index)
            lhs = parser.expression()
            if parser.peek() != "=" or lhs.kind != "unary:*":
                continue
            pointer = lhs.children[0]
            while pointer.kind == "parentheses":
                pointer = pointer.children[0]
            scalar = re.match(r"\(\s*(?P<type>[su](?:8|16))\s*\*\s*\)", body[pointer.start:])
            if pointer.kind != "cast" or scalar is None:
                continue
            parser.take()
            value = parser.take()
            if parser.peek() == ";":
                store_uses.setdefault(scalar.group("type")[1:], set()).add(value.start)
        except (candidate_syntax.UnsupportedExpression, RecursionError):
            continue
    eligible = []
    for parameter in narrow:
        uses = {t.start for i, t in enumerate(items) if t.text == parameter.group("name")
                and (i == 0 or items[i - 1].text not in (".", "->"))}
        if uses and uses <= store_uses.get(parameter.group("type")[1:], set()):
            eligible.append(parameter)
    if not eligible:
        return definition, []
    for path in declaration_facts.evidence_files(root):
        try:
            active = declaration_facts.active_text(path.read_text(encoding="utf-8"))
        except (OSError, UnicodeDecodeError):
            return definition, []
        if any(match.group("symbol") == symbol for match in declaration_facts.FUNCTION_EVIDENCE.finditer(active)):
            return definition, []
    evidence = []
    for parameter in reversed(eligible):
        start, end = parameter.span("type")
        header = header[:start] + "s32" + header[end:]
        evidence.append(f"{parameter.group('name')}: inferred narrow argument used only in same-width stores; kept as s32")
    return header + body, evidence


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


def repair_visible_address_uses(function: str, visible_source: str) -> tuple[str, list[str]]:
    """Repair address expressions only from unambiguous visible declarations."""
    from call_signatures import source_signatures

    objects: dict[str, set[str]] = {}
    for match in declaration_facts.file_scope_matches(declaration_facts.OBJECT_EVIDENCE, visible_source):
        objects.setdefault(match.group("symbol"), set()).add(
            declaration_facts.normalize_type(match.group("type")) + match.group("array")
        )
    clean = re.sub(r"/\*.*?\*/|//[^\n]*", "", function, flags=re.S)
    # A target-local declaration shadows any file-scope object evidence.
    local_types: dict[str, set[str]] = {}
    for match in re.finditer(
        rf"\b(?P<type>{declaration_facts.TYPE_TEXT})(?:\s+|(?<=\*))(?P<name>[A-Za-z_]\w*)\s*(?=[,;=)])", clean
    ):
        local_types.setdefault(match.group("name"), set()).add(
            declaration_facts.normalize_type(match.group("type"))
        )
    locals_ = set(local_types)
    void_globals = {name for name, types in objects.items() if types == {"void *"} and name not in locals_}
    integers = {name for name, types in local_types.items() if len(types) == 1 and types <= {"s32", "u32"}}

    def integer_expression(node: candidate_syntax.Expression) -> bool:
        if node.kind == "atom":
            value = function[node.start:node.end]
            return value in integers or re.fullmatch(r"(?:0x[\da-fA-F]+|\d+)[uUlL]*", value) is not None
        return node.kind in {"parentheses", "+", "-", "*", "<<", ">>", "&", "|", "^", "unary:-", "unary:+"} and all(
            integer_expression(child) for child in node.children
        )
    signatures = source_signatures(visible_source)
    roots = candidate_syntax.expression_roots(function)
    items = candidate_syntax.tokens(function)
    body = next((i for i, token in enumerate(items) if token.text == "{"), len(items))
    # expression_roots covers assignments/conditions; include standalone calls.
    for i in range(body + 1, len(items) - 1):
        if items[i].text in signatures and items[i + 1].text == "(":
            try:
                roots.append(candidate_syntax.Parser(items, i).unary())
            except (candidate_syntax.UnsupportedExpression, RecursionError):
                continue
    edits: dict[tuple[int, int], str] = {}
    actions: list[str] = []
    for root in roots:
        for node in candidate_syntax.walk(root):
            if node.kind in ("+", "-"):
                left = node.children[0]
                name = function[left.start:left.end]
                if left.kind == "atom" and name in void_globals and integer_expression(node.children[1]):
                    edits[left.start, left.end] = f"((u8 *){name})"
                    actions.append(f"cast visible void pointer {name} before byte arithmetic")
            if node.kind != "postfix:(" or node.children[0].kind != "atom":
                continue
            callee = function[node.children[0].start:node.children[0].end]
            choices = signatures.get(callee, set())
            if len(choices) != 1 or None in choices:
                continue
            signature = next(iter(choices))
            arguments = node.children[1:]
            if len(arguments) != len(signature.arguments):
                continue
            for argument, expected in zip(arguments, signature.arguments):
                if expected not in ("void *", "const void *"):
                    continue
                value = function[argument.start:argument.end]
                address = re.fullmatch(r"([A-Za-z_]\w*)\s*[+-]\s*(?:0x[\da-fA-F]+|\d+)", value)
                if address and address[1] in integers:
                    edits[argument.start, argument.end] = f"({expected})({value})"
                    actions.append(f"cast integer-backed address argument to {callee} using visible prototype")
    # All supported edits are disjoint atoms or simple integer expressions.
    for (start, end), replacement in sorted(edits.items(), reverse=True):
        function = function[:start] + replacement + function[end:]
    return function, actions


def repair_compile_diagnostics(
    function: str, messages: tuple[str, ...], *, visible_source: str = ""
) -> tuple[str, tuple[str, ...]]:
    """Apply bounded, semantics-neutral repairs proven by compiler diagnostics."""

    repaired = function
    actions: list[str] = []
    diagnostic_text = "\n".join(messages).lower()

    if "'null' undefined" in diagnostic_text and re.search(r"\bNULL\b", repaired):
        repaired = re.sub(r"\bNULL\b", "0", repaired)
        actions.append("replaced undefined NULL with integer null constant 0")

    pointer_arithmetic = any(
        marker in diagnostic_text
        for marker in (
            "illegal combination of pointer and integer",
            "unacceptable operand of '+'",
            "unacceptable operand of '-'",
            "bad operand type for += or -=",
        )
    )
    if not pointer_arithmetic:
        return repaired, tuple(actions)

    repaired, visible_actions = repair_visible_address_uses(repaired, visible_source)
    actions.extend(visible_actions)

    # A local end pointer can be inferred as s32 by m2c. Preserve the existing
    # pointer arithmetic (including its scale); fix only the destination type.
    pointer_types = {m.group("name"): m.group("type") for m in POINTER_DECLARATION.finditer(repaired)}
    for scalar in reversed(list(S32_DECLARATION.finditer(repaired))):
        if scalar.start() < repaired.find("{"):
            continue
        name = scalar.group("name")
        assignment = re.search(rf"(?m)^\s*{re.escape(name)}\s*=\s*(?P<base>\w+)\s*[+-]\s*(?:0x[\da-fA-F]+|\d+)\s*;", repaired)
        if assignment is None or assignment.group("base") not in pointer_types:
            continue
        base = assignment.group("base")
        if not re.search(rf"\b(?:{re.escape(base)}\s*!=\s*{re.escape(name)}|{re.escape(name)}\s*!=\s*{re.escape(base)})\b", repaired):
            continue
        pointer_type = pointer_types[base]
        repaired = repaired[:scalar.start()] + f"{pointer_type} *{name}" + repaired[scalar.end():]
        actions.append(f"typed end pointer {name} from {base}")

    declarations = list(VOID_POINTER_DECLARATION.finditer(repaired))
    arithmetic_names = {
        match.group("name")
        for match in declarations
        if re.search(
            rf"\b{re.escape(match.group('name'))}\b\s*(?:\+|-)", repaired
        )
        or re.search(
            rf"(?:\+|-)\s*\b{re.escape(match.group('name'))}\b", repaired
        )
    }
    if arithmetic_names:
        def promote_pointer(match: re.Match[str]) -> str:
            if match.group("name") not in arithmetic_names:
                return match.group(0)
            return f"u8{match.group('spacing')}{match.group('name')}"

        repaired = VOID_POINTER_DECLARATION.sub(promote_pointer, repaired)
        actions.append(
            "typed byte-address pointer arithmetic for "
            + ", ".join(sorted(arithmetic_names))
        )

    pointer_names = {
        match.group("name") for match in POINTER_DECLARATION.finditer(repaired)
    }
    scalar_address_names: set[str] = set()
    for scalar in S32_DECLARATION.finditer(repaired):
        name = scalar.group("name")
        if any(
            re.search(
                rf"(?m)^\s*{re.escape(pointer)}\s*=\s*"
                rf"{re.escape(name)}\s*(?:\+|-)",
                repaired,
            )
            for pointer in pointer_names
        ):
            scalar_address_names.add(name)
    if scalar_address_names:
        def promote_scalar_address(match: re.Match[str]) -> str:
            if match.group("name") not in scalar_address_names:
                return match.group(0)
            return f"u8 *{match.group('name')}"

        repaired = S32_DECLARATION.sub(promote_scalar_address, repaired)
        pointer_names.update(scalar_address_names)
        actions.append(
            "typed integer-backed address parameter as byte pointer for "
            + ", ".join(sorted(scalar_address_names))
        )

    if "dereferenced a non-pointer" in diagnostic_text:
        bare_global_dereference = re.compile(
            r"\*\(\s*(?P<base>D_[A-Za-z0-9_]+)\s*\+"
        )
        bare_bases = {
            match.group("base")
            for match in bare_global_dereference.finditer(repaired)
        }
        if bare_bases:
            repaired = bare_global_dereference.sub(
                lambda match: f"*(u8 *)({match.group('base')} +", repaired
            )
            actions.append(
                "cast integer-backed byte buffer dereference for "
                + ", ".join(sorted(bare_bases))
            )

    assignment = re.compile(
        r"(?m)^(?P<indent>\s*)(?P<name>[A-Za-z_]\w*)\s*=\s*"
        r"(?P<rhs>[^;\n]+)\s*;\s*$"
    )

    def cast_integer_address(match: re.Match[str]) -> str:
        rhs = match.group("rhs").strip()
        if (
            match.group("name") not in pointer_names
            or not re.search(r"(?:\+|-|<<)", rhs)
            or re.match(r"^\((?:void|u8)\s*\*\)", rhs)
        ):
            return match.group(0)
        actions.append(
            f"cast integer-backed address assigned to {match.group('name')}"
        )
        return (
            f"{match.group('indent')}{match.group('name')} = "
            f"(void *)({rhs});"
        )

    repaired = assignment.sub(cast_integer_address, repaired)
    return repaired, tuple(dict.fromkeys(actions))


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
    definition, prefix, inferred_evidence = lower_inferred_members(
        starter[match.start():].strip(), prefix, source
    )
    definition = sanitize_unused_parameters(
        sanitize_pointer_integer_assignments(
            sanitize_fields(definition)
        )
    )
    if not definition.endswith("}"):
        raise CandidateError("m2c emitted content after the function definition")
    placeholders = sorted(set(PLACEHOLDER.findall(definition)))
    if placeholders:
        raise CandidateError(
            "m2c body contains unresolved placeholder(s): " + ", ".join(placeholders)
        )
    definition, parameter_evidence = widen_store_only_parameters(definition, symbol, root=root)
    try:
        target = re.search(rf'(?m)^\s*#pragma GLOBAL_ASM\("[^"\n]*/{re.escape(symbol)}\.s"\)', source)
        visible = source[:target.start()] if target else source
        declarations, evidence = declaration_facts.resolve_required_declarations(
            prefix, visible, root=root
        )
        later, later_evidence = declaration_facts.later_function_declarations(
            definition, source, visible + "\n" + "\n".join(declarations)
        )
        declarations.extend(later)
        evidence.extend(later_evidence)
        later_objects, object_evidence = declaration_facts.later_object_declarations(
            definition, source, visible + "\n" + "\n".join(declarations)
        )
        declarations.extend(later_objects)
        evidence.extend(object_evidence)
        evidence.extend(inferred_evidence)
        evidence.extend(parameter_evidence)
    except declaration_facts.DeclarationError as error:
        raise CandidateError(str(error)) from error
    intrinsic_declarations, intrinsic_evidence = required_intrinsic_declarations(
        definition, "\n".join(declarations) + "\n" + source
    )
    declarations.extend(intrinsic_declarations)
    evidence.extend(intrinsic_evidence)
    return PreparedCandidate(
        definition + "\n",
        tuple(declarations),
        tuple(evidence),
    )


def lower_inferred_members(definition: str, prefix: str, source: str) -> tuple[str, str, list[str]]:
    """Lower new scalar fields to m2c's explicit byte offsets, keeping project types."""

    composite = re.compile(r"typedef\s+struct\s+(?P<name>\w+)\s*\{(?P<body>[^{}]*)\}\s*(?P=name)\s*;[^\n]*", re.DOTALL)
    active = declaration_facts.active_text(source)
    evidence: list[str] = []
    for match in list(composite.finditer(prefix)):
        name = match.group("name")
        known = re.search(rf"typedef\s+struct\s+{re.escape(name)}\s*\{{(?P<body>[^{{}}]*)\}}\s*{re.escape(name)}\s*;", active)
        if known is None:
            raise CandidateError(f"unresolved composite declaration: {name} lacks a canonical project type")
        bases = re.findall(rf"\bextern\s+{re.escape(name)}\s*\*\s*(\w+)\s*;", active)
        fields = re.finditer(r"/\*\s*(?P<offset>0x[\da-fA-F]+)\s*\*/\s*(?P<type>[su](?:8|16|32)|f(?:32|64))\s+(?P<field>\w+)\s*;[^\n]*?/\* inferred \*/", match.group("body"))
        for field in fields:
            member = field.group("field")
            if re.search(rf"\b{re.escape(member)}\s*(?:;|\[)", known.group("body")):
                continue
            scalar, offset = field.group("type"), field.group("offset")
            if int(offset, 16) % (int(scalar[1:]) // 8):
                raise CandidateError(f"unaligned inferred member: {name}.{member}")
            for base in bases:
                pattern = rf"\b{re.escape(base)}\s*->\s*{re.escape(member)}\b"
                definition, count = re.subn(pattern, f"*({scalar} *)((u8 *){base} + {offset})", definition)
                if count:
                    evidence.append(f"{name}.{member}: m2c scalar byte offset {offset}")
            if re.search(rf"(?:->|\.)\s*{re.escape(member)}\b", definition):
                raise CandidateError(f"unresolved inferred member base: {name}.{member}")
        prefix = prefix.replace(match.group(0), "", 1)
    return definition, prefix, evidence


def swap_commutative_expressions(function: str) -> list[str]:
    return candidate_syntax.commutative_variants(function)


def assignment_form_variants(function: str) -> list[str]:
    tokens = candidate_syntax.tokens(function)
    if any(t.text == "volatile" for t in tokens):
        return []
    active_positions = {t.start for t in tokens}
    variants: list[str] = []
    for match in ASSIGNMENT.finditer(function):
        if match.start("name") not in active_positions:
            continue
        replacement = (
            f"{match.group('indent')}{match.group('name')} "
            f"{match.group('op')}= {match.group('rhs')};"
        )
        variants.append(function[: match.start()] + replacement + function[match.end() :])
    for match in COMPOUND_ASSIGNMENT.finditer(function):
        if match.start("name") not in active_positions:
            continue
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
    queue = list(dict.fromkeys(seeds))
    queued = set(queue)
    index = 0
    while index < len(queue) and len(variants) < budget:
        candidate = queue[index]
        index += 1
        if candidate in seen:
            continue
        seen.add(candidate)
        variants.append(candidate)
        generated = assignment_form_variants(candidate)
        generated.extend(swap_commutative_expressions(candidate))
        for variant in generated:
            if variant not in queued:
                queued.add(variant)
                queue.append(variant)
    return variants
