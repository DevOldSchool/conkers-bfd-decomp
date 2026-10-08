#!/usr/bin/env python3
"""Report cross-file declaration conflicts in compiled C (read-only).

Every source file carries its own externs and prototypes, so one symbol can be
declared differently in different translation units. This parses top-level
declarations and definitions under src/, skips `#if 0` deferred candidates and
`static` symbols, resolves typedefs, computes MIPS o32 struct layouts where the
file defines them, and classifies each disagreement by the weakest erasure that
reconciles it. Risk flags are a heuristic review shortlist, not verified
defects. It never compiles, edits source or changes progress state.
"""
from __future__ import annotations

import argparse
import ast
from collections import Counter, defaultdict
import json
import operator
from pathlib import Path
import re
import subprocess
from typing import Callable, Iterator

ROOT = Path(__file__).resolve().parent.parent

QUALS = {"const", "volatile"}
STORAGE = {"extern", "static", "register", "auto", "inline", "typedef"}
BUILTIN = {"void", "char", "short", "int", "long", "float", "double", "signed", "unsigned"}
TAGS = {"struct", "union", "enum"}
KEYWORDS = QUALS | STORAGE | BUILTIN | TAGS

# Mirrors include/types.h; plain IDO `char` is unsigned.
BASE_TYPEDEFS = {
    "s8": ("i", 1, True), "u8": ("i", 1, False), "s16": ("i", 2, True), "u16": ("i", 2, False),
    "s32": ("i", 4, True), "u32": ("i", 4, False), "s64": ("i", 8, True), "u64": ("i", 8, False),
    "f32": ("f", 4, None), "f64": ("f", 8, None),
}

LEVELS = ["qualifier", "aggregate-name", "aggregate-unverified", "pointee", "signedness",
          "byte-placeholder", "incompatible"]
QUALIFIER, AGG_NAME, AGG_UNVERIFIED, POINTEE, SIGNEDNESS, PLACEHOLDER, INCOMPATIBLE = range(len(LEVELS))
LEVEL_DESC = {
    "qualifier": "differ only in const/volatile, array bounds or typedef spelling of the same type",
    "aggregate-name": "different struct names whose computed layouts are identical",
    "aggregate-unverified": "different structs whose layouts differ or could not be computed; compatibility unknown",
    "pointee": "pointers to different types (void * vs u8 * vs Struct *)",
    "signedness": "same width, different signedness",
    "byte-placeholder": "declared as a byte/byte array in some files and a real type elsewhere",
    "incompatible": "different width, kind, pointer-vs-value, array-vs-pointer, arity or return type",
}
RISK_REASONS = {
    "return location differs", "argument location differs",
    "float vs integer argument in the same register",
    "argument count differs", "variadic vs fixed", "access size differs",
    "array vs pointer", "float vs integer", "array element width differs",
    "array element float vs integer",
}

Type = tuple
TOKEN_RE = re.compile(r"\.\.\.|[A-Za-z_]\w*|0[xX][0-9A-Fa-f]+[uUlL]*|\d+\.?\d*[fFuUlL]*|<<|>>|\S")
IDENT_RE = re.compile(r"[A-Za-z_]\w*$")


class Body(str):
    """A collapsed `{...}` token that keeps the tokens it replaced."""

    def __new__(cls, tokens: list[str]) -> "Body":
        body = super().__new__(cls, "{...}")
        body.tokens = tokens
        return body


# ---------------------------------------------------------------- preprocessing
def strip_comments(text: str) -> str:
    """Blank comments while preserving line numbers and string literals."""
    out: list[str] = []
    i, n = 0, len(text)
    while i < n:
        if text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append(re.sub(r"[^\n]", " ", text[i:j]))
            i = j
        elif text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
        elif text[i] in "\"'":
            quote, j = text[i], i + 1
            while j < n and text[j] != quote:
                j += 2 if text[j] == "\\" else 1
            out.append(text[i:j + 1])
            i = j + 1
        else:
            out.append(text[i])
            i += 1
    return "".join(out)


def preprocess(text: str) -> list[str]:
    """Return live US lines: directives (including continuations) and disabled
    conditionals blanked, object-like macros applied, line numbers preserved."""
    lines = strip_comments(text).split("\n")
    defines: dict[str, str] = {}
    stack: list[list[bool]] = []  # [branch active, any branch taken]
    out: list[str] = []
    index = 0
    while index < len(lines):
        line = lines[index]
        active = all(branch for branch, _ in stack)
        directive = re.match(r"\s*#\s*(\w+)\s*(.*)", line)
        if not directive:
            if not active:
                out.append("")
            elif defines:
                out.append(re.sub(r"\b\w+\b", lambda m: defines.get(m.group(0), m.group(0)), line))
            else:
                out.append(line)
            index += 1
            continue
        name, rest = directive.group(1), directive.group(2)
        out.append("")
        while rest.rstrip().endswith("\\") and index + 1 < len(lines):
            index += 1
            rest = rest.rstrip()[:-1] + " " + lines[index]
            out.append("")
        index += 1
        rest = rest.strip()
        if name in ("if", "ifdef", "ifndef"):
            if name == "if" and rest == "0":
                cond = False
            elif name == "ifndef":
                cond = rest not in defines
            else:
                cond = "PROFILE_EU" not in rest
            stack.append([cond, cond])
        elif name == "elif" and stack:
            cond = not stack[-1][1] and "PROFILE_EU" not in rest
            stack[-1] = [cond, stack[-1][1] or cond]
        elif name == "else" and stack:
            stack[-1] = [not stack[-1][1], True]
        elif name == "endif" and stack:
            stack.pop()
        elif name == "define" and active:
            macro = re.match(r"(\w+)(?!\()\s+(.*)", rest)
            if macro:
                defines[macro.group(1)] = macro.group(2)
    return out


def tokenize(lines: list[str]) -> list[tuple[str, int]]:
    return [(m.group(0), number) for number, line in enumerate(lines, 1) for m in TOKEN_RE.finditer(line)]


def collapse_braces(words: list[str]) -> list[str]:
    """Replace each outermost {...} group with a Body token holding its contents."""
    out: list[str] = []
    i = 0
    while i < len(words):
        if words[i] == "{":
            depth, j = 0, i
            while j < len(words):
                depth += {"{": 1, "}": -1}.get(words[j], 0)
                if depth == 0:
                    break
                j += 1
            out.append(Body(collapse_braces(words[i + 1:j])))
            i = j + 1
        else:
            out.append(words[i])
            i += 1
    return out


def knr_header_end(words: list[str]) -> int | None:
    """Index just past `name(a, b, ...)` when words continue with a K&R parameter
    declaration (`f(a, b) s32 a`); None for ordinary declarations."""
    for p in range(1, len(words)):
        if words[p] != "(" or not is_ident(words[p - 1]):
            continue
        q = matching_close(words, p + 1, "(", ")")
        names = words[p + 1:q - 1]
        identifiers = names[0::2]
        if (not identifiers or any(sep != "," for sep in names[1::2])
                or any(not is_ident(n) or n in BASE_TYPEDEFS for n in identifiers)):
            return None
        if q < len(words) and (IDENT_RE.match(words[q]) or words[q] in KEYWORDS):
            return q
        return None
    return None


def matching_brace(tokens: list[tuple[str, int]], i: int) -> int:
    depth = 0
    while i < len(tokens):
        depth += {"{": 1, "}": -1}.get(tokens[i][0], 0)
        if depth == 0:
            return i
        i += 1
    return i


def top_level_statements(tokens: list[tuple[str, int]]) -> Iterator[tuple[str, list[str], int, list[list[str]]]]:
    """Yield ('decl' | 'fndef', words, line, knr_parameter_declarations).
    Brace groups become Body tokens; K&R parameter declarations stay with their definition."""
    stmt: list[tuple[str, int]] = []
    i, n = 0, len(tokens)
    while i < n:
        token, line = tokens[i]
        if token == "{":
            j = matching_brace(tokens, i)
            words = [word for word, _ in stmt]
            if words and words[-1] == ")" and "=" not in words:
                yield "fndef", words, stmt[0][1], []
                stmt = []
            else:
                stmt.append((Body(collapse_braces([word for word, _ in tokens[i + 1:j]])), line))
            i = j + 1
            continue
        if token == ";":
            words = [word for word, _ in stmt]
            header_end = knr_header_end(words)
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
                    yield "fndef", words[:header_end], stmt[0][1], params
                    stmt = []
                    i = matching_brace(tokens, j) + 1
                    continue
            if stmt:
                yield "decl", words, stmt[0][1], []
            stmt = []
        else:
            stmt.append((token, line))
        i += 1


# ---------------------------------------------------------------- type model
# Types are tuples:
#   ("void",)  ("i", width, signed)  ("f", width, None)
#   ("agg", name, layout | None)     layout = (size, align, leaves)
#   ("named", typedef name, type)    ("q", type, quals)
#   ("ptr", type, quals)  ("arr", type, bound text)  ("fn", ret, params | None, variadic)
class Context:
    def __init__(self, tags: dict[str, tuple | None] | None = None):
        self.typedefs: dict[str, Type] = {}
        self.tags: dict[str, tuple | None] = dict(tags or {})


def builtin_type(words: list[str]) -> Type:
    names = set(words)
    if "void" in names:
        return ("void",)
    if "float" in names:
        return ("f", 4, None)
    if "double" in names:
        return ("f", 8, None)
    unsigned = "unsigned" in names
    if "char" in names:
        return ("i", 1, "signed" in names)
    if "short" in names:
        return ("i", 2, not unsigned)
    if words.count("long") >= 2:
        return ("i", 8, not unsigned)
    return ("i", 4, not unsigned)


def resolve_typedef(name: str, ctx: Context) -> Type:
    if name in BASE_TYPEDEFS:
        return BASE_TYPEDEFS[name]
    if name in ctx.typedefs:
        return ("named", name, ctx.typedefs[name])
    return ("agg", name, None)  # unknown name: opaque type with no known layout


def is_ident(word: str) -> bool:
    return bool(IDENT_RE.match(word)) and word not in KEYWORDS


def parse_specifiers(words: list[str], i: int, ctx: Context) -> tuple[Type, set[str], set[str], int]:
    storage: set[str] = set()
    quals: set[str] = set()
    builtins: list[str] = []
    base: Type | None = None
    while i < len(words):
        word = words[i]
        if word in STORAGE:
            storage.add(word)
            i += 1
        elif word in QUALS:
            quals.add(word)
            i += 1
        elif word in BUILTIN and base is None:
            builtins.append(word)
            i += 1
        elif word in TAGS and base is None and not builtins:
            tag = words[i + 1] if i + 1 < len(words) and is_ident(words[i + 1]) else None
            i += 2 if tag else 1
            body = words[i] if i < len(words) and isinstance(words[i], Body) else None
            if body is not None:
                i += 1
            if word == "enum":
                base = ("i", 4, True)
                continue
            key = f"{word} {tag}" if tag else None
            if body is not None:
                layout = aggregate_layout(body.tokens, word == "union", ctx)
                if key:
                    ctx.tags[key] = layout
            else:
                layout = ctx.tags.get(key) if key else None
            base = ("agg", tag or "<anon>", layout)
        elif IDENT_RE.match(word) and base is None and not builtins:
            base = resolve_typedef(word, ctx)
            i += 1
        else:
            break
    if builtins:
        base = builtin_type(builtins)
    return base or ("i", 4, True), storage, quals, i


def with_quals(t: Type, quals: set[str]) -> Type:
    return ("q", t, frozenset(quals)) if quals else t


def split_on(words: list[str], separator: str) -> list[list[str]]:
    parts: list[list[str]] = [[]]
    depth = 0
    for word in words:
        if word in ("(", "["):
            depth += 1
        elif word in (")", "]"):
            depth -= 1
        if word == separator and depth == 0:
            parts.append([])
        else:
            parts[-1].append(word)
    return parts


def split_commas(words: list[str]) -> list[list[str]]:
    return split_on(words, ",")


def parse_params(words: list[str], ctx: Context) -> tuple[tuple | None, bool]:
    if not words:
        return None, False  # unprototyped ()
    if words == ["void"]:
        return (), False
    params: list[Type] = []
    variadic = False
    for part in split_commas(words):
        if part == ["..."]:
            variadic = True
            continue
        base, _, quals, i = parse_specifiers(part, 0, ctx)
        _, wrap, _ = parse_declarator(part, i, ctx)
        t = wrap(base)
        if t[0] == "arr":
            t = ("ptr", t[1], frozenset())
        elif t[0] == "fn":
            t = ("ptr", t, frozenset())
        params.append(with_quals(t, quals))
    return tuple(params), variadic


def matching_close(words: list[str], i: int, open_: str, close: str) -> int:
    depth = 1
    while i < len(words) and depth:
        depth += {open_: 1, close: -1}.get(words[i], 0)
        i += 1
    return i


def parse_declarator(words: list[str], i: int, ctx: Context) -> tuple[str | None, Callable[[Type], Type], int]:
    """Parse a (possibly abstract) declarator; return name, base-type wrapper and next index."""
    pointers: list[frozenset] = []
    while i < len(words) and words[i] == "*":
        i += 1
        quals: set[str] = set()
        while i < len(words) and words[i] in QUALS:
            quals.add(words[i])
            i += 1
        pointers.append(frozenset(quals))
    name: str | None = None
    inner: Callable[[Type], Type] = lambda t: t
    if i + 1 < len(words) and words[i] == "(" and words[i + 1] in ("*", "("):
        name, inner, i = parse_declarator(words, i + 1, ctx)
        if i < len(words) and words[i] == ")":
            i += 1
    elif i < len(words) and is_ident(words[i]) and words[i] not in ctx.typedefs and words[i] not in BASE_TYPEDEFS:
        name = words[i]
        i += 1
    suffixes: list[tuple] = []
    while i < len(words) and words[i] in ("[", "("):
        if words[i] == "[":
            j = matching_close(words, i + 1, "[", "]")
            suffixes.append(("arr", " ".join(words[i + 1:j - 1])))
        else:
            j = matching_close(words, i + 1, "(", ")")
            suffixes.append(("fn",) + parse_params(words[i + 1:j - 1], ctx))
        i = j

    def wrap(t: Type) -> Type:
        for quals in pointers:
            t = ("ptr", t, quals)
        for suffix in reversed(suffixes):
            t = ("arr", t, suffix[1]) if suffix[0] == "arr" else ("fn", t, suffix[1], suffix[2])
        return inner(t)

    return name, wrap, i


# ---------------------------------------------------------------- layouts (MIPS o32 / IDO)
BOUND_OPS = {
    ast.Add: operator.add, ast.Sub: operator.sub, ast.Mult: operator.mul, ast.FloorDiv: operator.floordiv,
    ast.Mod: operator.mod, ast.LShift: operator.lshift, ast.RShift: operator.rshift,
    ast.BitOr: operator.or_, ast.BitAnd: operator.and_, ast.BitXor: operator.xor,
}


def eval_bound(text: str) -> int | None:
    """Evaluate a constant array bound made only of integer literals and arithmetic."""
    expr = re.sub(r"\b(0[xX][0-9A-Fa-f]+|\d+)[uUlL]+\b", r"\1", text).replace("/", "//")
    try:
        tree = ast.parse(expr, mode="eval")
    except SyntaxError:
        return None

    def value(node: ast.AST) -> int:
        if isinstance(node, ast.Constant) and type(node.value) is int:
            return node.value
        if isinstance(node, ast.UnaryOp) and isinstance(node.op, ast.USub):
            return -value(node.operand)
        if isinstance(node, ast.BinOp) and type(node.op) in BOUND_OPS:
            left, right = value(node.left), value(node.right)
            if isinstance(node.op, (ast.LShift, ast.RShift)) and not 0 <= right < 64:
                raise ValueError("unsupported shift")
            return BOUND_OPS[type(node.op)](left, right)
        raise ValueError("unsupported array bound")

    try:
        result = value(tree.body)
    except (ValueError, ZeroDivisionError):
        return None
    return result if 0 <= result < 1 << 32 else None


def align_up(value: int, alignment: int) -> int:
    return (value + alignment - 1) // alignment * alignment


def type_layout(t: Type) -> tuple | None:
    """(size, align, leaves) where leaves are (offset, kind) pairs, or None if unknown."""
    t = strip(t)
    kind = t[0]
    if kind == "i":
        return (t[1], t[1], ((0, ("i", t[1], t[2])),))
    if kind == "f":
        return (t[1], t[1], ((0, ("f", t[1])),))
    if kind == "ptr":
        return (4, 4, ((0, ("ptr",)),))
    if kind == "agg":
        return t[2]
    if kind == "arr":
        count = eval_bound(t[2])
        element = type_layout(t[1])
        if count is None or element is None:
            return None
        return (element[0] * count, element[1], ((0, ("arr", element[2], element[0], count)),))
    return None


def aggregate_layout(words: list[str], is_union: bool, ctx: Context) -> tuple | None:
    """Lay out struct/union members; unknown member types or bitfields make it unknown."""
    members: list[tuple] = []
    for decl in split_on(words, ";"):
        if not decl:
            continue
        if ":" in decl:
            return None
        base, _, quals, i = parse_specifiers(decl, 0, ctx)
        declarators = split_commas(decl[i:]) if i < len(decl) else [[]]
        for part in declarators:
            _, wrap, _ = parse_declarator(part, 0, ctx)
            layout = type_layout(wrap(base))
            if layout is None:
                return None
            members.append(layout)
    offset, alignment, leaves = 0, 1, []
    for size, align, member_leaves in members:
        start = 0 if is_union else align_up(offset, align)
        leaves.extend((start + o, leaf) for o, leaf in member_leaves)
        offset = max(offset, size) if is_union else start + size
        alignment = max(alignment, align)
    return (align_up(offset, alignment), alignment, tuple(sorted(leaves)))


# ---------------------------------------------------------------- comparison
def strip(t: Type) -> Type:
    """Drop qualifiers and typedef names: comparisons use resolved types."""
    while t[0] in ("named", "q"):
        t = t[2] if t[0] == "named" else t[1]
    return t


def type_key(t: Type) -> tuple:
    """Hashable resolved type (typedefs expanded, qualifiers and layouts kept)."""
    kind = t[0]
    if kind == "named":
        return type_key(t[2])
    if kind == "q":
        return ("q", tuple(sorted(t[2])), type_key(t[1]))
    if kind == "ptr":
        return ("ptr", type_key(t[1]), tuple(sorted(t[2])))
    if kind == "arr":
        return ("arr", type_key(t[1]), t[2])
    if kind == "fn":
        params = None if t[2] is None else tuple(type_key(p) for p in t[2])
        return ("fn", type_key(t[1]), params, t[3])
    return t


def agg_equal(a: Type, b: Type, level: int) -> bool:
    if level >= AGG_UNVERIFIED:
        return True
    same_name = a[1] == b[1] and a[1] != "<anon>"
    if same_name and (a[2] is None or b[2] is None or a[2] == b[2]):
        return True
    return level >= AGG_NAME and a[2] is not None and a[2] == b[2]


def equal_at(a: Type, b: Type, level: int) -> bool:
    """Whether a and b agree once information up to LEVELS[level] is erased."""
    a, b = strip(a), strip(b)
    if a[0] == b[0] == "ptr":
        return level >= POINTEE or equal_at(a[1], b[1], level)
    if a[0] != b[0]:
        return False
    kind = a[0]
    if kind == "i":
        return a[1] == b[1] and (a[2] == b[2] or level >= SIGNEDNESS)
    if kind == "f":
        return a[1] == b[1]
    if kind == "agg":
        return agg_equal(a, b, level)
    if kind == "arr":
        return equal_at(a[1], b[1], level)
    if kind == "fn":
        if not equal_at(a[1], b[1], level):
            return False
        if a[2] is None or b[2] is None:
            return True  # unprototyped: return type only
        return (len(a[2]) == len(b[2]) and a[3] == b[3]
                and all(equal_at(pa, pb, level) for pa, pb in zip(a[2], b[2])))
    return True


def is_byte_placeholder(t: Type) -> bool:
    t = strip(t)
    if t[0] == "arr":
        t = strip(t[1])
    return t[0] == "i" and t[1] == 1


def pair_level(a: Type, b: Type) -> int:
    for level in range(PLACEHOLDER):
        if equal_at(a, b, level):
            return level
    return PLACEHOLDER if is_byte_placeholder(a) or is_byte_placeholder(b) else INCOMPATIBLE


def slot_class(t: Type) -> str:
    """How MIPS o32 carries a value: f32, f64, i64, agg, void or a 32-bit word."""
    t = strip(t)
    if t[0] == "f":
        return "f32" if t[1] == 4 else "f64"
    if t[0] == "i" and t[1] == 8:
        return "i64"
    if t[0] in ("agg", "void"):
        return t[0]
    return "word"


def size_of(t: Type) -> int | None:
    t = strip(t)
    if t[0] in ("i", "f"):
        return t[1]
    if t[0] in ("ptr", "fn"):
        return 4
    if t[0] == "agg" and t[2] is not None:
        return t[2][0]
    return None


def element_type(t: Type) -> Type:
    t = strip(t)
    while t[0] == "arr":
        t = strip(t[1])
    return t


def aggregate_reasons(a: Type, b: Type) -> set[str]:
    """Describe unverified struct pairs found at matching positions of a and b."""
    a, b = strip(a), strip(b)
    if a[0] == b[0] == "agg":
        if agg_equal(a, b, AGG_NAME):
            return set()
        if a[2] is None or b[2] is None:
            return {"struct layout unknown"}
        return {"struct size differs" if a[2][0] != b[2][0] else "struct layout differs"}
    if a[0] != b[0]:
        return set()
    if a[0] in ("ptr", "arr"):
        return aggregate_reasons(a[1], b[1])
    if a[0] == "fn":
        reasons = aggregate_reasons(a[1], b[1])
        if a[2] is not None and b[2] is not None:
            for pa, pb in zip(a[2], b[2]):
                reasons |= aggregate_reasons(pa, pb)
        return reasons
    return set()


def object_reasons(a: Type, b: Type, level: int) -> set[str]:
    a, b = strip(a), strip(b)
    if (a[0] == "arr") != (b[0] == "arr"):
        array, other = (a, b) if a[0] == "arr" else (b, a)
        # A pointer spelling loads an address from the array's storage; a scalar
        # spelling of the same storage only differs in how the first element is named.
        if other[0] == "ptr":
            return {"array vs pointer"}
        reasons = {"array vs scalar object"}
        element = element_type(array)
        se, so = size_of(element), size_of(other)
        if se and so and se != so and not is_byte_placeholder(element) and not is_byte_placeholder(other):
            reasons.add("array element width differs")
        return reasons
    if a[0] == b[0] == "arr":
        ea, eb = element_type(a), element_type(b)
        sa, sb = size_of(ea), size_of(eb)
        if sa and sb and sa != sb:
            return {"array element width differs"}
        if {slot_class(ea), slot_class(eb)} & {"f32", "f64"} and slot_class(ea) != slot_class(eb):
            return {"array element float vs integer"}
        if level == PLACEHOLDER:
            return {"byte placeholder (address-only use expected)"}
        return {"pointer vs integer or other same-size difference"}
    if level == PLACEHOLDER:
        return {"byte placeholder (address-only use expected)"}
    sa, sb = size_of(a), size_of(b)
    if sa and sb and sa != sb:
        return {"access size differs"}
    if slot_class(a) != slot_class(b) and "agg" not in (slot_class(a), slot_class(b)):
        return {"float vs integer"}
    return {"pointer vs integer or other same-size difference"}


def value_shape(t: Type) -> tuple[int, int] | None:
    """(size, alignment) of a passed value, or None when a struct layout is unknown."""
    t = strip(t)
    if t[0] in ("i", "f"):
        return t[1], 8 if t[1] == 8 else 4
    if t[0] in ("ptr", "fn"):
        return 4, 4
    if t[0] == "agg" and t[2] is not None:
        return align_up(t[2][0], 4), max(4, t[2][1])
    return None


def o32_return_location(t: Type) -> str | None:
    t = strip(t)
    if t[0] == "void":
        return None
    if t[0] == "f":
        return "$f0" if t[1] == 4 else "$f0:$f1"
    if t[0] == "i" and t[1] == 8:
        return "$v0:$v1"
    if t[0] == "agg":
        return "memory via hidden $a0"
    return "$v0"


def o32_argument_locations(fn: Type) -> list[tuple[str, str, int] | None]:
    """Assign each parameter a MIPS o32 location: (location, 'float' | 'int', size).

    Arguments occupy consecutive word slots ($a0-$a3, then the stack); 8-byte
    values align to an even slot. Only leading floating-point arguments (the
    first, or the first two) use $f12/$f14; a float after any integer argument
    travels in a general register. A struct return passes a hidden pointer in
    $a0. Entries after a struct of unknown size are None.
    """
    hidden_result = strip(fn[1])[0] == "agg"
    offset: int | None = 4 if hidden_result else 0
    float_registers_open = not hidden_result
    locations: list[tuple[str, str, int] | None] = []
    for index, param in enumerate(fn[2] or ()):
        shape = value_shape(param)
        if shape is None or offset is None:
            offset = None
            locations.append(None)
            continue
        size, alignment = shape
        offset = align_up(offset, alignment)
        is_float = strip(param)[0] == "f"
        if float_registers_open and is_float and index < 2:
            location = f"$f{12 + 2 * index}"
        else:
            float_registers_open = False
            words = [offset + 4 * n for n in range(align_up(size, 4) // 4)]
            location = ":".join(f"$a{w // 4}" if w < 16 else f"sp+0x{w:X}" for w in words)
        locations.append((location, "float" if is_float else "int", size))
        offset += align_up(size, 4)
    return locations


def function_reasons(a: Type, b: Type) -> set[str]:
    reasons: set[str] = set()
    ra, rb = o32_return_location(a[1]), o32_return_location(b[1])
    if ra != rb:
        reasons.add("void vs value return" if None in (ra, rb) else "return location differs")
    elif not equal_at(a[1], b[1], SIGNEDNESS):
        reasons.add("return type differs (same register)")
    if a[2] is not None and b[2] is not None:
        if a[3] != b[3]:
            reasons.add("variadic vs fixed")
        elif len(a[2]) != len(b[2]):
            reasons.add("argument count differs")
        for la, lb, pa, pb in zip(o32_argument_locations(a), o32_argument_locations(b), a[2], b[2]):
            if la is None or lb is None:
                reasons.add("argument location unknown (struct passed by value)")
                break
            if la[0] != lb[0]:
                reasons.add("argument location differs")
            elif la[1] != lb[1]:
                reasons.add("float vs integer argument in the same register")
            elif la[2] != lb[2] or not equal_at(pa, pb, SIGNEDNESS):
                reasons.add("argument type differs (same register)")
    return reasons


def pair_reasons(a: Type, b: Type, level: int) -> set[str]:
    if level == AGG_UNVERIFIED:
        return aggregate_reasons(a, b)
    if level < PLACEHOLDER:
        return set()
    sa, sb = strip(a), strip(b)
    if sa[0] == sb[0] == "fn":
        return function_reasons(sa, sb)
    return object_reasons(a, b, level)


# ---------------------------------------------------------------- rendering
def render(t: Type, resolve: bool = False) -> str:
    kind = t[0]
    if kind == "q":
        return " ".join(sorted(t[2])) + " " + render(t[1], resolve)
    if kind == "named":
        return render(t[2], resolve) if resolve else t[1]
    if kind == "void":
        return "void"
    if kind == "i":
        return ("s" if t[2] else "u") + str(t[1] * 8)
    if kind == "f":
        return "f32" if t[1] == 4 else "f64"
    if kind == "agg":
        if resolve and t[2] is not None:
            return f"{t[1]} /*size 0x{t[2][0]:X}*/"
        return t[1]
    if kind == "ptr" and t[1][0] not in ("fn", "arr"):
        inner = render(t[1], resolve)
        star = "*" if inner.endswith("*") else " *"
        return inner + star + (" " + " ".join(sorted(t[2])) if t[2] else "")
    return render_wrapped(t, resolve)


def render_wrapped(t: Type, resolve: bool) -> str:
    decl = ""
    while t[0] in ("arr", "fn", "ptr"):
        if t[0] == "arr":
            decl = f"{decl}[{t[2]}]"
        elif t[0] == "fn":
            params = "" if t[2] is None else ", ".join(
                [render(p, resolve) for p in t[2]] + (["..."] if t[3] else [])) or "void"
            decl = f"{decl}({params})"
        else:
            decl = f"(*{decl})" if t[1][0] in ("arr", "fn") else f"*{decl}"
        t = t[1]
    return f"{render(t, resolve)} {decl}".strip()


# ---------------------------------------------------------------- scanning
def default_promotion(t: Type) -> Type:
    """Type a caller passes for an unprototyped (K&R) parameter of type t."""
    resolved = strip(t)
    if resolved[0] == "i" and resolved[1] < 4:
        return ("i", 4, True)
    if resolved[0] == "f" and resolved[1] == 4:
        return ("f", 8, None)
    if resolved[0] == "arr":
        return ("ptr", resolved[1], frozenset())
    if resolved[0] == "fn":
        return ("ptr", resolved, frozenset())
    return t


def knr_function_type(header: list[str], t: Type, declarations: list[list[str]], ctx: Context) -> Type:
    """Rebuild a K&R definition's parameters from its declaration list.

    K&R definitions provide no prototype, so callers apply default argument
    promotions; the promoted types are the calling contract compared with
    prototypes elsewhere. Undeclared parameters default to int.
    """
    open_paren = next(p for p in range(1, len(header)) if header[p] == "(" and is_ident(header[p - 1]))
    names = header[open_paren + 1:len(header) - 1][0::2]
    declared: dict[str, Type] = {}
    for words in declarations:
        base, _, quals, i = parse_specifiers(words, 0, ctx)
        for part in split_commas(words[i:]):
            name, wrap, _ = parse_declarator(part, 0, ctx)
            if name:
                declared[name] = default_promotion(with_quals(wrap(base), quals))
    params = tuple(declared.get(name, ("i", 4, True)) for name in names)
    return ("fn", t[1], params, False) if t[0] == "fn" else t


def scan_pass(tokens: list[tuple[str, int]], ctx: Context) -> list[dict]:
    decls: list[dict] = []
    for kind, words, line, knr_params in top_level_statements(tokens):
        base, storage, quals, i = parse_specifiers(words, 0, ctx)
        if kind == "fndef":
            name, wrap, _ = parse_declarator(words, i, ctx)
            if name and "static" not in storage:
                t = wrap(base)
                if knr_params:
                    t = knr_function_type(words, t, knr_params, ctx)
                decls.append({"name": name, "type": t, "line": line, "definition": True})
            continue
        for part in split_commas(words[i:]):
            initialized = "=" in part
            if initialized:
                part = part[:part.index("=")]
            name, wrap, _ = parse_declarator(part, 0, ctx)
            if not name:
                continue
            t = wrap(base)
            if "typedef" in storage:
                if t[0] == "agg" and t[1] == "<anon>":
                    t = ("agg", name, t[2])  # anonymous struct takes its typedef name
                ctx.typedefs[name] = with_quals(t, quals)
            elif "static" in storage:
                continue
            elif t[0] == "fn":
                decls.append({"name": name, "type": t, "line": line, "definition": False})
            else:
                defines = initialized or "extern" not in storage
                decls.append({"name": name, "type": with_quals(t, quals), "line": line, "definition": defines})
    return decls


def scan_source(text: str) -> list[dict]:
    """Return externally visible declarations and definitions in one source file.
    A first pass collects struct layouts so earlier forward references resolve."""
    tokens = tokenize(preprocess(text))
    first = Context()
    scan_pass(tokens, first)
    return scan_pass(tokens, Context(tags=first.tags))


def us_states(root: Path) -> dict[str, str]:
    states: dict[str, str] = {}
    for entry in json.loads((root / "progress/functions.json").read_text())["functions"]:
        us = entry.get("regions", {}).get("us", {})
        states[entry["symbol"]] = us.get("state")
        if us.get("symbol"):
            states[us["symbol"]] = us.get("state")
    return states


def describe_variant(key: tuple, variant: dict) -> dict:
    spellings = Counter(render(site["type"]) for site in variant["sites"])
    spelling = spellings.most_common(1)[0][0]
    resolved = render(variant["type"], resolve=True)
    entry = {
        "type": spelling,
        "count": len(variant["sites"]),
        "sites": [f"{s['file']}:{s['line']}" for s in variant["sites"]],
    }
    if resolved != spelling:
        entry["resolved"] = resolved
    if len(spellings) > 1:
        entry["spellings"] = dict(spellings.most_common())
    return entry


def analyze(sources: dict[str, str], states: dict[str, str] | None = None) -> dict:
    """Classify conflicts across {relative path: source text}."""
    states = states or {}
    by_name: dict[str, list[dict]] = defaultdict(list)
    for path, text in sorted(sources.items()):
        for decl in scan_source(text):
            decl["file"] = path
            by_name[decl["name"]].append(decl)

    conflicts: list[dict] = []
    for name, decls in by_name.items():
        variants: dict[tuple, dict] = {}
        for decl in decls:
            variants.setdefault(type_key(decl["type"]), {"type": decl["type"], "sites": []})["sites"].append(decl)
        if len(variants) < 2:
            continue
        keys = list(variants)
        worst = 0
        reasons: set[str] = set()
        for x, key_a in enumerate(keys):
            for key_b in keys[x + 1:]:
                ta, tb = variants[key_a]["type"], variants[key_b]["type"]
                level = pair_level(ta, tb)
                worst = max(worst, level)
                reasons |= pair_reasons(ta, tb, level)
        definitions = [decl for decl in decls if decl["definition"]]
        definition_key = type_key(definitions[0]["type"]) if definitions else None
        disagree = []
        if definitions:
            for key in keys:
                if key != definition_key:
                    level = pair_level(variants[key]["type"], definitions[0]["type"])
                    if level >= POINTEE:
                        disagree.append({"type": render(variants[key]["type"]), "severity": LEVELS[level],
                                         "sites": len(variants[key]["sites"])})
        described = sorted((describe_variant(key, v) for key, v in variants.items()),
                           key=lambda v: (-v["count"], v["type"], v.get("resolved", "")))
        conflicts.append({
            "name": name,
            "kind": "function" if strip(decls[0]["type"])[0] == "fn" else "object",
            "severity": LEVELS[worst],
            "severity_rank": worst,
            "abi_risk": bool(reasons & RISK_REASONS),
            "reasons": sorted(reasons),
            "match_state": states.get(name),
            "declaration_count": len(decls),
            "file_count": len({decl["file"] for decl in decls}),
            "variant_count": len(variants),
            "definition": f"{definitions[0]['file']}:{definitions[0]['line']}" if definitions else None,
            "definition_type": render(definitions[0]["type"]) if definitions else None,
            "disagree_with_definition": disagree,
            "variants": described,
        })
    conflicts.sort(key=lambda c: (-c["severity_rank"], not c["abi_risk"], -c["variant_count"],
                                  -c["declaration_count"], c["name"]))
    summary = {
        "files_scanned": len(sources),
        "symbols_declared": len(by_name),
        "symbols_in_multiple_files": sum(1 for decls in by_name.values() if len({d["file"] for d in decls}) > 1),
        "conflicting_symbols": len(conflicts),
        "by_severity": dict(Counter(c["severity"] for c in conflicts)),
        "by_kind_and_severity": dict(Counter(f"{c['kind']}/{c['severity']}" for c in conflicts)),
        "risk_shortlist_symbols": sum(1 for c in conflicts if c["abi_risk"]),
        "reasons": dict(Counter(r for c in conflicts for r in c["reasons"]).most_common()),
        "defined_in_c_with_disagreeing_decls": sum(1 for c in conflicts if c["disagree_with_definition"]),
    }
    return {"summary": summary, "conflicts": conflicts}


# ---------------------------------------------------------------- output
def variant_text(variant: dict) -> str:
    text = f"`{variant['type']}`"
    if "resolved" in variant:
        text += f" → `{variant['resolved']}`"
    return text


def render_markdown(report: dict, limit: int) -> str:
    summary, conflicts = report["summary"], report["conflicts"]
    lines = [
        "# Declaration conflict report\n",
        f"Generated from `{summary.get('revision', 'working tree')}` by `./conker declaration-conflicts`. "
        "Scans live (compiled) C under `src/`: `#if 0` deferred candidates and macro bodies are excluded, "
        "`static` symbols are ignored, typedefs are resolved before comparison, and only externally visible "
        "symbols declared in more than one way are listed.\n",
        "This is an investigation aid. The risk shortlist is a heuristic for review, not a verified or "
        "exhaustive count of defects: whether a disagreement matters depends on how each site uses the symbol "
        "(for example, byte placeholders that only take an address).\n",
        "## Summary\n",
        f"- Files scanned: **{summary['files_scanned']}**",
        f"- Distinct externally visible symbols: **{summary['symbols_declared']}** "
        f"({summary['symbols_in_multiple_files']} appear in more than one file)",
        f"- Symbols with conflicting declarations: **{summary['conflicting_symbols']}**",
        f"- Heuristic risk shortlist: **{summary['risk_shortlist_symbols']}** symbols",
        f"- Symbols with a C definition that other files declare with a different shape "
        f"(pointee or worse): **{summary['defined_in_c_with_disagreeing_decls']}**\n",
        "| Severity | Meaning | Functions | Objects |",
        "| --- | --- | ---: | ---: |",
    ]
    by_kind = summary["by_kind_and_severity"]
    for level in reversed(LEVELS):
        lines.append(f"| {level} | {LEVEL_DESC[level]} | {by_kind.get('function/' + level, 0)} | "
                     f"{by_kind.get('object/' + level, 0)} |")
    lines += [
        "",
        "Severity is the worst pairwise disagreement between a symbol's variants. Unprototyped `()` "
        "declarations are compared on return type only. Struct layouts follow MIPS o32 alignment and are "
        "known only when the declaring file defines every member type; otherwise compatibility is reported "
        "as unknown. Argument and return locations follow MIPS o32: only leading floating-point arguments use "
        "$f12/$f14, so a float after an integer argument shares a general register with an integer spelling "
        "and is reported as a value-meaning disagreement rather than a location change. "
        "Shortlisted reasons are marked below; other incompatible pairs share a 32-bit register "
        "on MIPS o32 (for example `void *` vs `s32`).\n",
        "| Reason | Symbols |",
        "| --- | ---: |",
    ]
    for reason, count in summary["reasons"].items():
        lines.append(f"| {reason}{' (shortlist)' if reason in RISK_REASONS else ''} | {count} |")
    lines.append("")

    def section(title: str, items: list[dict]) -> None:
        lines.append(f"## {title}\n")
        if not items:
            lines.append("None.\n")
            return
        for c in items[:limit]:
            where = f"defined at `{c['definition']}`" if c["definition"] else "no C definition (GLOBAL_ASM or data)"
            why = f" Reasons: {'; '.join(c['reasons'])}." if c["reasons"] else ""
            lines.append(f"### `{c['name']}`: {c['severity']}, {c['variant_count']} variants in {c['file_count']} files\n")
            lines.append(f"{c['kind'].capitalize()}, US state `{c['match_state']}`, {where}.{why}\n")
            lines.append("| Count | Declared type | Example sites |")
            lines.append("| ---: | --- | --- |")
            for variant in c["variants"][:12]:
                sites = ", ".join(f"`{site}`" for site in variant["sites"][:3])
                more = f" +{len(variant['sites']) - 3}" if len(variant["sites"]) > 3 else ""
                lines.append(f"| {variant['count']} | {variant_text(variant)} | {sites}{more} |")
            if len(c["variants"]) > 12:
                lines.append(f"| … | {len(c['variants']) - 12} more variants | |")
            lines.append("")
        if len(items) > limit:
            lines.append(f"_{len(items) - limit} more in `declaration-conflicts.json`._\n")

    risky = [c for c in conflicts if c["abi_risk"]]
    section("Risk shortlist: symbols defined in C", [c for c in risky if c["disagree_with_definition"]])
    section("Risk shortlist: symbols without a disagreeing C definition",
            [c for c in risky if not c["disagree_with_definition"]])
    section("Byte placeholders vs real types", [c for c in conflicts if c["severity"] == "byte-placeholder"])

    lines += ["## All conflicting symbols\n",
              "| Symbol | Kind | Severity | Shortlist | Variants | Files | US state |",
              "| --- | --- | --- | --- | ---: | ---: | --- |"]
    for c in conflicts:
        lines.append(f"| `{c['name']}` | {c['kind']} | {c['severity']} | {'yes' if c['abi_risk'] else ''} | "
                     f"{c['variant_count']} | {c['file_count']} | {c['match_state'] or ''} |")
    return "\n".join(lines) + "\n"


def git_revision(root: Path) -> str:
    result = subprocess.run(["git", "rev-parse", "--short", "HEAD"], cwd=root, capture_output=True, text=True)
    revision = result.stdout.strip() or "unknown"
    dirty = subprocess.run(["git", "status", "--porcelain", "--", "src"], cwd=root, capture_output=True, text=True)
    return revision + ("+dirty" if dirty.stdout.strip() else "")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--out", default="build/reports", help="report directory (default: build/reports)")
    parser.add_argument("--limit", type=int, default=40, help="symbols shown per Markdown detail section")
    parser.add_argument("--json", action="store_true", help="print the summary as JSON")
    args = parser.parse_args()
    if args.limit < 1:
        parser.error("--limit must be positive")

    sources = {path.relative_to(ROOT).as_posix(): path.read_text(errors="ignore")
               for path in sorted((ROOT / "src").rglob("*.c"))}
    report = analyze(sources, us_states(ROOT))
    report["summary"]["revision"] = git_revision(ROOT)

    out = ROOT / args.out
    out.mkdir(parents=True, exist_ok=True)
    (out / "declaration-conflicts.json").write_text(json.dumps(report, indent=1) + "\n")
    (out / "declaration-conflicts.md").write_text(render_markdown(report, args.limit))

    summary = report["summary"]
    if args.json:
        print(json.dumps(summary, indent=1))
    else:
        print(f"Scanned {summary['files_scanned']} files: {summary['conflicting_symbols']} conflicting symbols, "
              f"{summary['risk_shortlist_symbols']} on the heuristic risk shortlist, "
              f"{summary['defined_in_c_with_disagreeing_decls']} disagreeing with a C definition.")
        for level in reversed(LEVELS):
            print(f"  {level:21} {summary['by_severity'].get(level, 0)}")
        report_path = out / "declaration-conflicts.md"
        print(f"Report: {report_path.relative_to(ROOT) if report_path.is_relative_to(ROOT) else report_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
