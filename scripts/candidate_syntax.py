"""Conservative C expression parsing for source-shape search.

This recognizes expression islands, not a translation unit. Unsupported syntax
is left untouched. Tokens retain source positions so rewrites preserve comments
and always exchange complete operands, including casts and parentheses.
"""

from __future__ import annotations

import re
from dataclasses import dataclass


TOKEN = re.compile(
    r"\s+|/\*.*?\*/|//[^\n]*|\#[^\n]*|"
    r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|'
    r"(?:0[xX][0-9a-fA-F]+|(?:\d+\.?\d*|\.\d+)(?:[eE][+-]?\d+)?)[uUlLfF]*|"
    r"[A-Za-z_]\w*|>>=|<<=|\+\+|--|->|&&|\|\||==|!=|<=|>=|<<|>>|"
    r"[+*/%&|^!-]=|.",
    re.DOTALL,
)
IDENTIFIER = re.compile(r"[A-Za-z_]\w*\Z")
TYPES = frozenset("void char short int long signed unsigned float double const volatile s8 u8 s16 u16 s32 u32 s64 u64 f32 f64".split())
PRECEDENCE = {
    "||": 1, "&&": 2, "|": 3, "^": 4, "&": 5,
    "==": 6, "!=": 6, "<": 7, ">": 7, "<=": 7, ">=": 7,
    "<<": 8, ">>": 8, "+": 9, "-": 9, "*": 10, "/": 10, "%": 10,
}


@dataclass(frozen=True)
class Token:
    text: str
    start: int
    end: int


@dataclass(frozen=True)
class Expression:
    start: int
    end: int
    kind: str
    children: tuple[Expression, ...] = ()


def tokens(source: str) -> list[Token]:
    return [
        Token(m.group(), m.start(), m.end()) for m in TOKEN.finditer(source)
        if not m.group().isspace() and not m.group().startswith(("/*", "//", "#"))
    ]


class UnsupportedExpression(ValueError):
    pass


class Parser:
    def __init__(self, items: list[Token], start: int):
        self.items = items
        self.index = start

    def peek(self) -> str:
        return self.items[self.index].text if self.index < len(self.items) else ""

    def take(self) -> Token:
        if self.index == len(self.items):
            raise UnsupportedExpression()
        item = self.items[self.index]
        self.index += 1
        return item

    def expect(self, value: str) -> Token:
        item = self.take()
        if item.text != value:
            raise UnsupportedExpression()
        return item

    def expression(self, minimum: int = 1) -> Expression:
        left = self.unary()
        while self.peek() in PRECEDENCE and PRECEDENCE[self.peek()] >= minimum:
            op = self.take().text
            right = self.expression(PRECEDENCE[op] + 1)
            left = Expression(left.start, right.end, op, (left, right))
        return left

    def unary(self) -> Expression:
        item = self.take()
        if item.text in ("+", "-", "!", "~", "*", "&", "++", "--", "sizeof"):
            child = self.unary()
            return Expression(item.start, child.end, "unary:" + item.text, (child,))
        if item.text == "(":
            # Recognize only explicit builtin/pointer casts. An unknown typedef
            # cast fails closed when the following token cannot end an expression.
            end = self.index
            while end < len(self.items) and self.items[end].text != ")":
                end += 1
            words = [t.text for t in self.items[self.index:end]]
            is_type = bool(words) and (
                all(w in TYPES or w == "*" for w in words)
                or (words[-1] == "*" and all(IDENTIFIER.fullmatch(w) or w == "*" for w in words))
            )
            if is_type:
                self.index = end
                self.expect(")")
                child = self.unary()
                node = Expression(item.start, child.end, "cast", (child,))
            else:
                child = self.expression()
                close = self.expect(")")
                node = Expression(item.start, close.end, "parentheses", (child,))
        elif IDENTIFIER.fullmatch(item.text) or item.text[0].isdigit() or item.text[0] in ".\"'":
            node = Expression(item.start, item.end, "atom")
        else:
            raise UnsupportedExpression()
        while self.peek() in ("(", "[", ".", "->", "++", "--"):
            op = self.take().text
            children = [node]
            if op == "(":
                if self.peek() != ")":
                    children.append(self.expression())
                    while self.peek() == ",":
                        self.take()
                        children.append(self.expression())
                end = self.expect(")").end
            elif op == "[":
                children.append(self.expression())
                end = self.expect("]").end
            elif op in (".", "->"):
                field = self.take()
                if not IDENTIFIER.fullmatch(field.text):
                    raise UnsupportedExpression()
                end = field.end
            else:
                end = self.items[self.index - 1].end
            node = Expression(node.start, end, "postfix:" + op, tuple(children))
        return node


def expression_roots(source: str) -> list[Expression]:
    items = tokens(source)
    roots: list[Expression] = []
    body = next((i for i, t in enumerate(items) if t.text == "{"), len(items))
    for index in range(body + 1, len(items)):
        item = items[index]
        start = index + 1
        if item.text in ("if", "while", "switch"):
            if start == len(items) or items[start].text != "(":
                continue
            start += 1
            endings = (")",)
        elif item.text in ("return", "=", "+=", "-=", "*=", "/=", "|=", "&=", "^="):
            endings = (";",)
        else:
            continue
        try:
            parser = Parser(items, start)
            root = parser.expression()
            if parser.peek() in endings:
                roots.append(root)
        except (UnsupportedExpression, RecursionError):
            continue
    return roots


def walk(node: Expression):
    yield node
    for child in node.children:
        yield from walk(child)


def simple_value(node: Expression) -> bool:
    # Keep calls, dereferences, member/index reads, increments and complex
    # arithmetic out of operand swapping. Their subexpressions can still be
    # visited independently; no evaluation is duplicated or removed.
    return node.kind == "atom" or (
        node.kind in ("parentheses", "cast", "unary:+", "unary:-", "unary:~")
        and all(simple_value(child) for child in node.children)
    )


def commutative_variants(source: str) -> list[str]:
    if any(t.text == "volatile" for t in tokens(source)):
        return []
    variants: list[str] = []
    seen: set[tuple[int, int]] = set()
    for root in expression_roots(source):
        for node in walk(root):
            if node.kind not in ("+", "*", "|", "&", "^") or (node.start, node.end) in seen:
                continue
            seen.add((node.start, node.end))
            left, right = node.children
            if not simple_value(left) or not simple_value(right):
                continue
            lhs, rhs = source[left.start:left.end], source[right.start:right.end]
            if lhs == rhs:
                continue
            # Both children are complete unary expressions. Exchanging them
            # keeps this binary node's precedence and associativity unchanged.
            replacement = rhs + source[left.end:right.start] + lhs
            variants.append(source[:node.start] + replacement + source[node.end:])
    return variants
