"""Conservative local lifetime changes for straight-line C function bodies."""

from __future__ import annotations

import re

import candidate_syntax


LOCAL_TYPE = re.compile(r"(?:[su]32|(?:void|[su](?:8|16|32|64))\s*\*)\Z")
CONTROL = frozenset(("if", "else", "for", "while", "do", "switch", "goto", "case", "volatile", "asm", "__asm__"))


def replace_spans(source: str, edits: list[tuple[int, int, str]]) -> str:
    for start, end, replacement in sorted(edits, reverse=True):
        source = source[:start] + replacement + source[end:]
    return source


def lifetime_variants(function: str, declarations: list[re.Match[str]]):
    """Tighten scopes, split later writes, and reuse disjoint scalar locals.

    No control-flow, nested declarations, escaped local addresses, or unknown
    typedef qualifiers are accepted. Renaming uses tokens, never member names,
    comments, or strings. These rules change storage lifetimes, not evaluation.
    """

    if not declarations:
        return
    items = candidate_syntax.tokens(function)
    if any(t.text in CONTROL or t.text == ":" for t in items):
        return
    if sum(t.text == "{" for t in items) != 1 or sum(t.text == "}" for t in items) != 1:
        return
    # Preprocessor conditionals cannot be proven straight-line from tokens.
    if re.search(r"(?m)^\s*#", function):
        return
    declaration_end = declarations[-1].end()
    locals_with_uses = []
    occupied = {t.text for t in items}
    for declaration in declarations:
        name, type_name = declaration.group("name", "type")
        if not LOCAL_TYPE.fullmatch(type_name.strip()):
            continue
        uses = [i for i, token in enumerate(items)
                if token.start >= declaration_end and token.text == name
                and items[i - 1].text not in (".", "->")]
        def address_escapes(index: int) -> bool:
            previous = index - 1
            while previous >= 0 and items[previous].text == "(":
                previous -= 1
            return previous >= 0 and items[previous].text == "&"

        if len(uses) < 2 or any(address_escapes(i) for i in uses):
            continue
        first = uses[0]
        if items[first - 1].text not in (";", "{") or items[first + 1].text != "=":
            continue
        first_end = next((t.end for t in items[first + 2:] if t.text == ";"), None)
        if first_end is None or any(items[i].start < first_end for i in uses[1:]):
            continue
        locals_with_uses.append((declaration, uses))
        indent = declaration.group("indent")
        first_start = items[first].start
        last_end = next((t.end for t in items[uses[-1] + 1:] if t.text == ";"), None)
        if last_end is None:
            continue
        yield replace_spans(function, [
            (declaration.start(), declaration.end(), ""),
            (first_start, first_start, "{\n" + declaration.group(0) + "\n" + indent),
            (last_end, last_end, "\n" + indent + "}"),
        ])
        # A second definition can use a fresh local while its RHS still reads
        # the old value. All following uses then refer to the new definition.
        for index in uses[1:]:
            if items[index - 1].text != ";" or items[index + 1].text != "=":
                continue
            end = next((t.end for t in items[index + 2:] if t.text == ";"), None)
            if end is None:
                continue
            suffix = 0
            fresh = f"{name}_split{suffix}"
            while fresh in occupied:
                suffix += 1
                fresh = f"{name}_split{suffix}"
            edits = [(declaration_end, declaration_end, f"\n{indent}{type_name} {fresh};"),
                     (items[index].start, items[index].end, fresh)]
            edits.extend((items[i].start, items[i].end, fresh) for i in uses if items[i].start >= end)
            yield replace_spans(function, edits)
    for first_decl, first_uses in locals_with_uses:
        for second_decl, second_uses in locals_with_uses:
            if first_uses[-1] >= second_uses[0] or first_decl.group("type") != second_decl.group("type"):
                continue
            # Disjoint token ranges are disjoint live ranges only in the
            # straight-line, address-unescaped bodies accepted above.
            name = first_decl.group("name")
            edits = [(second_decl.start(), second_decl.end(), "")]
            edits.extend((items[i].start, items[i].end, name) for i in second_uses)
            yield replace_spans(function, edits)
