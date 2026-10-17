#!/usr/bin/env python3
"""Report recurring struct layouts across the game C sources (read-only).

Matched game C keeps private and partial structures in the owning source file,
so the same shape (a three-float vector, three words, a pointer plus a byte) is
defined again and again under different names. This parses every live
`struct`/`union` definition under src/game, src/done/game and include/, lays
each one out with the MIPS o32 rules that declaration_conflicts.py uses for
aggregate comparison, and clusters definitions whose layouts are identical.
Near matches (pad-only differences, one layout being a prefix of another) and
the matched functions whose parameters or locals name each copy are reported
as evidence for promoting a layout into a shared header. Field names are
compared across copies but never influence clustering. The report never
compiles, edits source or changes progress state.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
from dataclasses import dataclass, field
import json
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import declaration_conflicts as dc  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
SOURCE_DIRS = ("src/game", "src/done/game")
HEADER_DIR = "include"
# Shared headers are seeded first so source files resolve their typedefs; any
# other header under include/ follows in path order.
HEADER_ORDER = ("types.h", "game_command.h", "game_vec.h", "game_functions.h")
PAD_RE = re.compile(r"^_*pad", re.IGNORECASE)
LOCAL_QUALIFIERS = {"register", "const", "volatile", "static", "auto"}


@dataclass
class Member:
    name: str
    offset: int
    size: int
    type_text: str
    leaves: tuple
    pad: bool


@dataclass
class Definition:
    file: str
    line: int
    name: str
    kind: str
    names: tuple[str, ...]  # type spellings that declare a value of this definition
    nested: bool
    shared: bool
    members: list[Member] | None
    layout: tuple | None
    reason: str | None = None
    uses: set[tuple[str, str]] = field(default_factory=set)      # matched functions: parameters or locals
    mentions: set[tuple[str, str]] = field(default_factory=set)  # matched functions: any spelling, casts included


@dataclass
class Function:
    name: str
    line: int
    parameter_types: set[str]
    local_types: set[str]
    mentioned: set[str]


# ---------------------------------------------------------------- parsing
def is_pad(name: str | None) -> bool:
    return bool(name) and bool(PAD_RE.match(name))


def statements(tokens: list[tuple[str, int]]):
    """Yield ('decl', words, line, (), None) and ('fndef', header, line, knr, body).

    Mirrors declaration_conflicts.top_level_statements but keeps function
    bodies (flat tokens) so locals can be inspected.
    """
    stmt: list[tuple[str, int]] = []
    i, n = 0, len(tokens)
    while i < n:
        token, line = tokens[i]
        if token == "{":
            j = dc.matching_brace(tokens, i)
            words = [word for word, _ in stmt]
            body = [word for word, _ in tokens[i + 1:j]]
            if words and words[-1] == ")" and "=" not in words:
                yield "fndef", words, stmt[0][1], [], body
                stmt = []
            else:
                stmt.append((dc.Body(dc.collapse_braces(body)), line))
            i = j + 1
            continue
        if token == ";":
            words = [word for word, _ in stmt]
            header_end = dc.knr_header_end(words)
            if header_end is not None:
                params = [words[header_end:]]
                chunk: list[str] = []
                j = i + 1
                while j < n and tokens[j][0] not in ("{", "}"):
                    if tokens[j][0] == ";":
                        params.append(chunk)
                        chunk = []
                    else:
                        chunk.append(tokens[j][0])
                    j += 1
                if j < n and tokens[j][0] == "{" and not chunk:
                    end = dc.matching_brace(tokens, j)
                    yield "fndef", words[:header_end], stmt[0][1], params, [w for w, _ in tokens[j + 1:end]]
                    stmt = []
                    i = end + 1
                    continue
            if stmt:
                yield "decl", words, stmt[0][1], [], None
            stmt = []
        else:
            stmt.append((token, line))
        i += 1


def member_name(part: list[str]) -> str | None:
    name, _, _ = dc.parse_declarator(part, 0, dc.Context())
    return name


def layout_members(words: list[str], is_union: bool, ctx: dc.Context,
                   outer: str, sink: list[Definition], file: str, line: int, shared: bool
                   ) -> tuple[list[Member] | None, str | None]:
    """Lay out members exactly as declaration_conflicts.aggregate_layout does,
    keeping names and offsets; nested struct bodies are recorded in `sink`."""
    members: list[Member] = []
    offset, alignment = 0, 1
    for decl in dc.split_on(words, ";"):
        if not decl:
            continue
        if ":" in decl:
            return None, "bitfield"
        base, _, _, i = dc.parse_specifiers(decl, 0, ctx)
        declarators = dc.split_commas(decl[i:]) if i < len(decl) else [[]]
        nested_body = next(((k, decl[k]) for k in range(len(decl) - 1)
                            if decl[k] in ("struct", "union")
                            and (isinstance(decl[k + 1], dc.Body)
                                 or (k + 2 < len(decl) and isinstance(decl[k + 2], dc.Body)))), None)
        if nested_body is not None:
            k, tag_word = nested_body
            body = decl[k + 1] if isinstance(decl[k + 1], dc.Body) else decl[k + 2]
            first = member_name(declarators[0]) or "<anon>"
            record_definition(sink, file, line, f"{outer}.{first}", tag_word, (), True, shared, body, ctx)
        for part in declarators:
            name, wrap, _ = dc.parse_declarator(part, 0, ctx)
            t = wrap(base)
            layout = dc.type_layout(t)
            if layout is None:
                return None, f"unknown member type for `{name or '<anon>'}`"
            size, align, leaves = layout
            start = 0 if is_union else dc.align_up(offset, align)
            members.append(Member(name or "<anon>", start, size, dc.render(t),
                                  tuple((start + o, leaf) for o, leaf in leaves), is_pad(name)))
            offset = max(offset, size) if is_union else start + size
            alignment = max(alignment, align)
    return members, None


def record_definition(sink: list[Definition], file: str, line: int, name: str, kind: str,
                      names: tuple[str, ...], nested: bool, shared: bool, body: dc.Body,
                      ctx: dc.Context) -> Definition:
    is_union = kind == "union"
    members, reason = layout_members(body.tokens, is_union, ctx, name, sink, file, line, shared)
    layout = dc.aggregate_layout(body.tokens, is_union, ctx) if members is not None else None
    definition = Definition(file, line, name, kind, names, nested, shared, members, layout, reason)
    sink.append(definition)
    return definition


def definitions_in_statement(words: list[str], line: int, ctx: dc.Context, file: str,
                             shared: bool, sink: list[Definition]) -> None:
    """Record struct/union bodies in one top-level statement and register its typedefs."""
    for k, word in enumerate(words):
        if word not in ("struct", "union"):
            continue
        tag = words[k + 1] if k + 1 < len(words) and dc.is_ident(words[k + 1]) else None
        body_index = k + (2 if tag else 1)
        if body_index >= len(words) or not isinstance(words[body_index], dc.Body):
            continue
        declarators = [part for part in dc.split_commas(words[body_index + 1:]) if part]
        declared = [member_name(part[:part.index("=")] if "=" in part else part) for part in declarators]
        declared = [name for name in declared if name]
        names: list[str] = []
        if tag:
            names.append(f"{word} {tag}")
        if "typedef" in words[:k]:
            names.extend(declared)
            display = declared[0] if declared else (f"{word} {tag}" if tag else "<anon>")
        else:
            display = f"{word} {tag}" if tag else f"<anon> {declared[0]}" if declared else "<anon>"
        record_definition(sink, file, line, display, word, tuple(names), False, shared, words[body_index], ctx)
        break
    # Register typedefs and tags the way declaration_conflicts does so later
    # members and parameters resolve to the same layouts.
    base, storage, quals, i = dc.parse_specifiers(words, 0, ctx)
    if "typedef" not in storage:
        return
    for part in dc.split_commas(words[i:]):
        if "=" in part:
            part = part[:part.index("=")]
        name, wrap, _ = dc.parse_declarator(part, 0, ctx)
        if not name:
            continue
        t = wrap(base)
        if t[0] == "agg" and t[1] == "<anon>":
            t = ("agg", name, t[2])
        ctx.typedefs[name] = dc.with_quals(t, quals)


def identifier_uses(words: list[str]) -> set[str]:
    """Type spellings a token run can name: identifiers plus `struct Tag` pairs."""
    uses: set[str] = set()
    for k, word in enumerate(words):
        if dc.is_ident(word):
            uses.add(word)
        if word in ("struct", "union") and k + 1 < len(words) and dc.is_ident(words[k + 1]):
            uses.add(f"{word} {words[k + 1]}")
    return uses


def local_declaration_types(body: list[str]) -> set[str]:
    """Type spellings that start a declaration-shaped statement inside a body."""
    types: set[str] = set()
    stmt: list[str] = []
    for word in body + [";"]:
        if word in (";", "{", "}"):
            k = 0
            while k < len(stmt) and stmt[k] in LOCAL_QUALIFIERS:
                k += 1
            rest = stmt[k:]
            if len(rest) >= 2 and dc.is_ident(rest[0]) and (rest[1] == "*" or dc.is_ident(rest[1])):
                types.add(rest[0])
            if (len(rest) >= 3 and rest[0] in ("struct", "union") and dc.is_ident(rest[1])
                    and (rest[2] == "*" or dc.is_ident(rest[2]))):
                types.add(f"{rest[0]} {rest[1]}")
            stmt = []
        else:
            stmt.append(word)
    return types


def scan_function(header: list[str], line: int, knr: list[list[str]], body: list[str],
                  ctx: dc.Context) -> Function | None:
    base, _, _, i = dc.parse_specifiers(header, 0, ctx)
    name, _, _ = dc.parse_declarator(header, i, ctx)
    if not name:
        return None
    open_paren = next((p for p in range(1, len(header)) if header[p] == "(" and dc.is_ident(header[p - 1])), None)
    if open_paren is None:
        return None
    close = dc.matching_close(header, open_paren + 1, "(", ")")
    parameters = identifier_uses(header[open_paren + 1:close - 1])
    for words in knr:
        parameters |= identifier_uses(words)
    mentioned = identifier_uses(header + body) | parameters
    return Function(name, line, parameters, local_declaration_types(body), mentioned)


def scan_file(text: str, file: str, ctx: dc.Context, shared: bool
              ) -> tuple[list[Definition], list[Function], int]:
    """Definitions, functions and the number of struct bodies skipped inside `#if 0`."""
    live = dc.preprocess(text)
    skipped = (len(re.findall(r"\b(?:struct|union)\b(?:\s+\w+)?\s*\{", dc.strip_comments(text)))
               - len(re.findall(r"\b(?:struct|union)\b(?:\s+\w+)?\s*\{", "\n".join(live))))
    definitions: list[Definition] = []
    functions: list[Function] = []
    for kind, words, line, knr, body in statements(dc.tokenize(live)):
        if kind == "decl":
            definitions_in_statement(words, line, ctx, file, shared, definitions)
        else:
            function = scan_function(words, line, knr, body, ctx)
            if function:
                functions.append(function)
    return definitions, functions, max(skipped, 0)


# ---------------------------------------------------------------- clustering
def describe_leaf(leaf: tuple) -> str:
    kind = leaf[0]
    if kind == "i":
        return ("s" if leaf[2] else "u") + str(leaf[1] * 8)
    if kind == "f":
        return "f32" if leaf[1] == 4 else "f64"
    if kind == "ptr":
        return "ptr"
    element_leaves, element_size, count = leaf[1], leaf[2], leaf[3]
    if len(element_leaves) == 1 and element_leaves[0][0] == 0:
        element = describe_leaf(element_leaves[0][1])
    else:
        element = "{" + ", ".join(f"{describe_leaf(l)}@0x{o:X}" for o, l in element_leaves) + "}"
    return f"{element}[{count}]"


def shape_text(layout: tuple) -> str:
    return ", ".join(f"{describe_leaf(leaf)}@0x{offset:X}" for offset, leaf in layout[2])


def nonpad_leaves(definition: Definition) -> tuple:
    return tuple(sorted(leaf for member in definition.members if not member.pad for leaf in member.leaves))


def declarator_text(type_text: str, name: str) -> str:
    if type_text == "<anon>":
        return f"struct {{...}} {name}"
    if type_text.endswith("*"):
        return type_text + name
    if " [" in type_text:
        base, bounds = type_text.split(" [", 1)
        return f"{base} {name}[{bounds}"
    return f"{type_text} {name}"


def field_report(copies: list[Definition]) -> list[dict]:
    slots: dict[tuple[int, int], Counter] = defaultdict(Counter)
    pads: dict[tuple[int, int], int] = Counter()
    for definition in copies:
        for member in definition.members:
            key = (member.offset, member.size)
            if member.pad:
                pads[key] += 1
            else:
                slots[key][member.name] += 1
    report = []
    for (offset, size), names in sorted(slots.items()):
        present = sum(names.values())
        dominant, dominant_count = names.most_common(1)[0]
        if len(names) == 1 and present == len(copies):
            agreement = "unanimous"
        elif dominant_count * 2 > len(copies):
            agreement = "majority"
        else:
            agreement = "split"
        report.append({
            "offset": offset, "size": size, "names": dict(names.most_common()),
            "copies_with_member": present,
            "pad_in_other_copies": pads.get((offset, size), 0),
            "dominant": dominant, "dominant_count": dominant_count,
            "agreement": agreement,
        })
    return report


def canonical_members(copies: list[Definition], fields: list[dict]) -> Definition:
    """The copy whose non-pad member names are most common across the cluster."""
    frequency = {(f["offset"], f["size"]): f["names"] for f in fields}

    def score(definition: Definition) -> tuple[int, int]:
        return (sum(frequency.get((m.offset, m.size), {}).get(m.name, 0) for m in definition.members if not m.pad),
                -definition.line)
    return max(copies, key=score)


def build_clusters(definitions: list[Definition]) -> list[dict]:
    by_layout: dict[tuple, list[Definition]] = defaultdict(list)
    for definition in definitions:
        if definition.layout is not None:
            by_layout[definition.layout].append(definition)
    clusters: list[dict] = []
    for layout, copies in by_layout.items():
        copies.sort(key=lambda d: (not d.shared, d.file, d.line))
        fields = field_report(copies)
        representative = canonical_members(copies, fields)
        matched = set().union(*(d.uses for d in copies))
        mentioning = set().union(*(d.mentions for d in copies))
        clusters.append({
            "layout": layout,
            "nonpad": nonpad_leaves(representative),
            "copies": len(copies),
            "file_count": len({d.file for d in copies}),
            "shared_copies": sum(1 for d in copies if d.shared),
            "nested_copies": sum(1 for d in copies if d.nested),
            "kind": sorted({d.kind for d in copies}),
            "size": layout[0], "align": layout[1],
            "shape": shape_text(layout),
            "canonical": " ".join(declarator_text(m.type_text, m.name) + ";" for m in representative.members),
            "definitions": [{"file": d.file, "line": d.line, "name": d.name, "kind": d.kind,
                             "nested": d.nested, "shared": d.shared} for d in copies],
            "matched_functions": len(matched),
            "matched_function_names": sorted(f"{file}:{name}" for file, name in matched),
            "matched_functions_mentioning": len(mentioning),
            "fields": fields,
            "agreeing_fields": [f"{f['dominant']}@0x{f['offset']:X}" for f in fields if f["agreement"] == "unanimous"],
            "majority_fields": [{"offset": f["offset"], "name": f["dominant"], "count": f["dominant_count"],
                                 "others": {n: c for n, c in f["names"].items() if n != f["dominant"]}}
                                for f in fields if f["agreement"] == "majority"],
            "conflicting_fields": [{"offset": f["offset"], "names": f["names"],
                                    "copies_with_member": f["copies_with_member"]}
                                   for f in fields if f["agreement"] == "split"],
        })
    clusters.sort(key=lambda c: (-c["copies"], -c["matched_functions"], -c["file_count"], c["size"], c["shape"]))
    for index, cluster in enumerate(clusters, 1):
        cluster["id"] = index
    return clusters


def brief(cluster: dict) -> dict:
    example = cluster["definitions"][0]
    return {"cluster": cluster["id"], "copies": cluster["copies"], "size": cluster["size"],
            "example": example["name"], "file": example["file"]}


def near_matches(clusters: list[dict], reported: list[dict]) -> None:
    """Attach pad-only variants and prefix relations to each reported cluster.

    Comparisons use non-pad leaves only: two clusters are pad variants when
    those leaves coincide (sizes may differ by trailing pad), and A is a prefix
    of B when B's non-pad leaves begin with A's and extend past A's size. A
    layout with fewer than two non-pad leaves is never reported as a prefix.
    """
    by_nonpad: dict[tuple, list[dict]] = defaultdict(list)
    for cluster in clusters:
        by_nonpad[cluster["nonpad"]].append(cluster)
    for cluster in reported:
        leaves, size = cluster["nonpad"], cluster["size"]
        variants = [c for c in by_nonpad[leaves] if c["id"] != cluster["id"]]
        prefix_of: list[dict] = []
        extends: list[dict] = []
        for other in clusters:
            if other["id"] == cluster["id"]:
                continue
            o_leaves, o_size = other["nonpad"], other["size"]
            if (len(leaves) >= 2 and size < o_size and len(o_leaves) > len(leaves)
                    and o_leaves[:len(leaves)] == leaves and o_leaves[len(leaves)][0] >= size):
                prefix_of.append(other)
            elif (len(o_leaves) >= 2 and o_size < size and len(leaves) > len(o_leaves)
                    and leaves[:len(o_leaves)] == o_leaves and leaves[len(o_leaves)][0] >= o_size):
                extends.append(other)
        cluster["near_matches"] = {
            "pad_variants": [brief(c) for c in variants],
            "prefix_of": [brief(c) for c in prefix_of],
            "extends": [brief(c) for c in extends],
        }


# ---------------------------------------------------------------- analysis
def matched_functions(root: Path) -> dict[tuple[str, str], str]:
    """{(source file, C name or US symbol): inventory symbol} for US-matched functions."""
    matched: dict[tuple[str, str], str] = {}
    inventory = root / "progress/functions.json"
    if not inventory.exists():
        return matched
    for entry in json.loads(inventory.read_text())["functions"]:
        us = entry.get("regions", {}).get("us", {})
        if us.get("state") != "matched":
            continue
        for symbol in (entry.get("symbol"), us.get("symbol")):
            if symbol:
                matched[(entry["source"], symbol)] = entry["symbol"]
    return matched


def analyze(headers: dict[str, str], sources: dict[str, str], matched: dict[tuple[str, str], str],
            min_copies: int = 3) -> dict:
    """Cluster struct layouts across {relative path: text} headers and sources."""
    header_ctx = dc.Context()
    definitions: list[Definition] = []
    skipped = 0
    header_defs: list[Definition] = []
    for path in sorted(headers, key=lambda p: (HEADER_ORDER.index(Path(p).name)
                                               if Path(p).name in HEADER_ORDER else len(HEADER_ORDER), p)):
        defs, _, dead = scan_file(headers[path], path, header_ctx, shared=True)
        header_defs.extend(defs)
        skipped += dead
    definitions.extend(header_defs)
    shared_names: dict[str, list[Definition]] = defaultdict(list)
    for definition in header_defs:
        for name in definition.names:
            shared_names[name].append(definition)

    function_total = 0
    for path in sorted(sources):
        ctx = dc.Context(tags=header_ctx.tags)
        ctx.typedefs = dict(header_ctx.typedefs)
        defs, functions, dead = scan_file(sources[path], path, ctx, shared=False)
        skipped += dead
        function_total += len(functions)
        local_names: dict[str, list[Definition]] = defaultdict(list)
        for definition in defs:
            for name in definition.names:
                local_names[name].append(definition)
        for function in functions:
            key = (path, function.name)
            if key not in matched:
                continue
            declared = function.parameter_types | function.local_types
            for name in function.mentioned:
                owners = local_names.get(name) or ([] if name in local_names else shared_names.get(name, []))
                for owner in owners:
                    owner.mentions.add(key)
                    if name in declared:
                        owner.uses.add(key)
        definitions.extend(defs)

    clusters = build_clusters(definitions)
    reported = [c for c in clusters if c["copies"] >= min_copies]
    near_matches(clusters, reported)
    unknown = [{"file": d.file, "line": d.line, "name": d.name, "reason": d.reason}
               for d in definitions if d.layout is None]
    known = [d for d in definitions if d.layout is not None]
    families = {c["nonpad"] for c in clusters}
    summary = {
        "files_scanned": len(headers) + len(sources),
        "definitions": len(definitions),
        "definitions_in_disabled_blocks": skipped,
        "definitions_with_unknown_layout": len(unknown),
        "nested_definitions": sum(1 for d in definitions if d.nested),
        "shared_header_definitions": sum(1 for d in definitions if d.shared),
        "distinct_layouts": len(clusters),
        "distinct_layouts_ignoring_pads": len(families),
        "duplicate_definitions": sum(c["copies"] - 1 for c in clusters if c["copies"] > 1),
        "definitions_in_recurring_layouts": sum(c["copies"] for c in clusters if c["copies"] > 1),
        "clusters_at_or_above_min_copies": len(reported),
        "min_copies": min_copies,
        "pad_fields": sum(1 for d in known for m in d.members if m.pad),
        "functions_scanned": function_total,
        "matched_functions_in_inventory": len(set(matched.values())),
        "matched_functions_using_reported_clusters": len(set().union(
            *([set(c["matched_function_names"]) for c in reported] or [set()]))),
        "matched_functions_mentioning_reported_clusters": sum(c["matched_functions_mentioning"] for c in reported),
    }
    return {"summary": summary, "clusters": clusters, "unknown_layouts": unknown}


# ---------------------------------------------------------------- output
def names_text(items: list[dict], limit: int = 6) -> str:
    shown = ", ".join(f"`{b['example']}` (#{b['cluster']}, {b['copies']} copies, size 0x{b['size']:X})"
                      for b in items[:limit])
    more = f" +{len(items) - limit} more" if len(items) > limit else ""
    return shown + more


def render_markdown(report: dict, limit: int) -> str:
    summary = report["summary"]
    clusters = report["clusters"]
    reported = [c for c in clusters if c["copies"] >= summary["min_copies"]]
    lines = [
        "# Struct layout report\n",
        f"Generated from `{summary.get('revision', 'working tree')}` by `./conker struct-layouts`. "
        "Scans live struct and union definitions under `src/game`, `src/done/game` and `include/`: "
        "`#if 0` deferred candidates are skipped, nested anonymous bodies count as their own definitions, "
        "and layouts follow the MIPS o32 rules of the declaration conflict report (a definition whose "
        "member types are unknown or that uses bitfields has no layout and is listed separately).\n",
        "Definitions are clustered by identical layout (offset, width and type class of every scalar leaf); "
        "field names never affect clustering. Near matches compare non-pad leaves only: a pad variant "
        "differs only in `pad*` members (including trailing pads), and a prefix relation means a larger "
        "layout begins with this one. Matched-function counts cover functions whose parameters or locals "
        "spell a copy's type name in the owning file (header copies count in every file that does not "
        "shadow the name); the mentioning count also includes casts and `sizeof`, but members reached "
        "through other structs are never counted. "
        "Recurrence is evidence for a shared header, not proof that the copies mean the same thing.\n",
        "## Summary\n",
        f"- Files scanned: **{summary['files_scanned']}**",
        f"- Live definitions: **{summary['definitions']}** "
        f"({summary['nested_definitions']} nested, {summary['shared_header_definitions']} in shared headers, "
        f"{summary['definitions_in_disabled_blocks']} more skipped inside `#if 0`)",
        f"- Definitions with unknown layout: **{summary['definitions_with_unknown_layout']}**",
        f"- Distinct layouts: **{summary['distinct_layouts']}** "
        f"({summary['distinct_layouts_ignoring_pads']} ignoring pad members)",
        f"- Definitions duplicating a layout defined elsewhere: **{summary['duplicate_definitions']}** "
        f"({summary['definitions_in_recurring_layouts']} definitions share a layout with at least one other)",
        f"- Clusters with at least {summary['min_copies']} copies: **{summary['clusters_at_or_above_min_copies']}**",
        f"- Pad members: **{summary['pad_fields']}**",
        f"- Functions scanned: **{summary['functions_scanned']}**; matched functions declaring a parameter or "
        f"local of a reported cluster: **{summary['matched_functions_using_reported_clusters']}**\n",
        f"## Clusters with at least {summary['min_copies']} copies\n",
    ]
    if not reported:
        lines.append("None.\n")
    for cluster in reported[:limit]:
        lines.append(f"### #{cluster['id']}: {cluster['copies']} copies in {cluster['file_count']} files, "
                     f"{cluster['matched_functions']} matched functions "
                     f"({cluster['matched_functions_mentioning']} mentioning the type)\n")
        kinds = "/".join(cluster["kind"])
        lines.append(f"{kinds}, size 0x{cluster['size']:X}, align {cluster['align']}: `{cluster['shape']}`  ")
        lines.append(f"Canonical: `{cluster['canonical']}`\n")
        shown = ", ".join(f"`{d['name']}` ({d['file']}:{d['line']}{', shared' if d['shared'] else ''})"
                          for d in cluster["definitions"][:8])
        more = f" +{cluster['copies'] - 8} more" if cluster["copies"] > 8 else ""
        lines.append(f"Copies: {shown}{more}\n")
        agree = ", ".join(f"`{f}`" for f in cluster["agreeing_fields"]) or "none"
        majority = ", ".join(
            f"`{f['name']}@0x{f['offset']:X}` {f['count']}/{cluster['copies']}"
            + (f" (also {', '.join(list(f['others'])[:3])}{', …' if len(f['others']) > 3 else ''})" if f["others"] else "")
            for f in cluster["majority_fields"]) or "none"
        conflict = "; ".join(
            f"0x{f['offset']:X}: " + "/".join(f"{n}({c})" for n, c in list(f["names"].items())[:4])
            + (" …" if len(f["names"]) > 4 else "")
            + (f" [{f['copies_with_member']}/{cluster['copies']} copies]"
               if f["copies_with_member"] < cluster["copies"] else "")
            for f in cluster["conflicting_fields"]) or "none"
        lines.append(f"Fields unanimous: {agree}. Majority: {majority}. Split: {conflict}.\n")
        near = cluster["near_matches"]
        parts = []
        if near["pad_variants"]:
            parts.append(f"pad variants: {names_text(near['pad_variants'])}")
        if near["prefix_of"]:
            parts.append(f"prefix of {len(near['prefix_of'])} larger layouts: {names_text(near['prefix_of'])}")
        if near["extends"]:
            parts.append(f"extends: {names_text(near['extends'])}")
        lines.append(("Near matches: " + "; ".join(parts) if parts else "Near matches: none") + "\n")
    if len(reported) > limit:
        lines.append(f"_{len(reported) - limit} more in `struct-layouts.json`._\n")

    lines += ["## All recurring layouts\n",
              "| # | Copies | Files | Matched fns | Size | Shape | Example |",
              "| ---: | ---: | ---: | ---: | ---: | --- | --- |"]
    for cluster in clusters:
        if cluster["copies"] < 2:
            break
        example = cluster["definitions"][0]
        shape = cluster["shape"] if len(cluster["shape"]) <= 80 else cluster["shape"][:77] + "…"
        lines.append(f"| {cluster['id']} | {cluster['copies']} | {cluster['file_count']} | "
                     f"{cluster['matched_functions']} | 0x{cluster['size']:X} | `{shape}` | "
                     f"`{example['name']}` ({example['file']}) |")
    lines.append("")
    if report["unknown_layouts"]:
        lines += ["## Definitions without a computable layout\n",
                  "| Definition | Reason |", "| --- | --- |"]
        for item in report["unknown_layouts"][:limit]:
            lines.append(f"| `{item['name']}` ({item['file']}:{item['line']}) | {item['reason']} |")
        if len(report["unknown_layouts"]) > limit:
            lines.append(f"| … | {len(report['unknown_layouts']) - limit} more in `struct-layouts.json` |")
        lines.append("")
    return "\n".join(lines) + "\n"


def json_ready(report: dict) -> dict:
    """Drop the tuple keys that only clustering needs."""
    out = {"summary": report["summary"], "unknown_layouts": report["unknown_layouts"], "clusters": []}
    for cluster in report["clusters"]:
        out["clusters"].append({k: v for k, v in cluster.items() if k not in ("layout", "nonpad")})
    return out


def read_tree(root: Path) -> tuple[dict[str, str], dict[str, str]]:
    headers = {p.relative_to(root).as_posix(): p.read_text(errors="ignore")
               for p in sorted((root / HEADER_DIR).glob("*.h"))}
    sources = {p.relative_to(root).as_posix(): p.read_text(errors="ignore")
               for directory in SOURCE_DIRS for p in sorted((root / directory).rglob("*.c"))}
    return headers, sources


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--out", default="build/reports", help="report directory (default: build/reports)")
    parser.add_argument("--min-copies", type=int, default=3, help="copies a cluster needs to be detailed (default: 3)")
    parser.add_argument("--limit", type=int, default=40, help="clusters detailed in the Markdown report")
    parser.add_argument("--json", action="store_true", help="print the summary and top clusters as JSON")
    args = parser.parse_args()
    if args.min_copies < 2:
        parser.error("--min-copies must be at least 2")
    if args.limit < 1:
        parser.error("--limit must be positive")

    headers, sources = read_tree(ROOT)
    report = analyze(headers, sources, matched_functions(ROOT), args.min_copies)
    report["summary"]["revision"] = dc.git_revision(ROOT)
    out = ROOT / args.out
    out.mkdir(parents=True, exist_ok=True)
    (out / "struct-layouts.json").write_text(json.dumps(json_ready(report), indent=1) + "\n")
    (out / "struct-layouts.md").write_text(render_markdown(report, args.limit))

    summary = report["summary"]
    top = [c for c in report["clusters"] if c["copies"] >= args.min_copies][:10]
    if args.json:
        print(json.dumps({"summary": summary, "top_clusters": [
            {"id": c["id"], "copies": c["copies"], "files": c["file_count"], "matched_functions": c["matched_functions"],
             "matched_functions_mentioning": c["matched_functions_mentioning"],
             "size": c["size"], "shape": c["shape"], "canonical": c["canonical"]} for c in top]}, indent=1))
    else:
        print(f"Scanned {summary['files_scanned']} files: {summary['definitions']} live definitions, "
              f"{summary['distinct_layouts']} distinct layouts, {summary['duplicate_definitions']} duplicates, "
              f"{summary['clusters_at_or_above_min_copies']} clusters with >= {summary['min_copies']} copies.")
        for c in top:
            print(f"  #{c['id']:<4} {c['copies']:>3} copies {c['file_count']:>3} files "
                  f"{c['matched_functions']:>4} matched fns ({c['matched_functions_mentioning']:>3} mentioning)  "
                  f"size 0x{c['size']:<4X} {c['canonical']}")
        report_path = out / "struct-layouts.md"
        print(f"Report: {report_path.relative_to(ROOT) if report_path.is_relative_to(ROOT) else report_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
