#!/usr/bin/env python3
"""Read-only declaration-change reminders and demand-only possible caller lookup."""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import json
from pathlib import Path
import re
import sys

import call_signatures
import candidate_syntax
import declaration_facts
from matching_context import source_bodies, source_calls

ROOT = Path(__file__).resolve().parent.parent
LIMITATIONS = ("Incomplete: direct C call spellings in unique registered matched US definitions only; "
               "indirect, macro-expanded, raw ASM and unregistered callers are not resolved. "
               "Spelling is a recheck lead, not proof of a linked call or complete impact coverage.")


def _headers(source: str) -> dict[str, list[tuple[str, ...]]]:
    source = call_signatures.without_abi_declarations(source)
    source = re.sub(r'/\*.*?\*/|//[^\n]*', '', source, flags=re.S)
    items = candidate_syntax.tokens(declaration_facts.active_text(source))
    found = defaultdict(list)
    start = depth = 0
    for i, token in enumerate(items):
        if depth == 0 and token.text in (';', '{'):
            words = tuple(item.text for item in items[start:i])
            if '(' in words and words[-1:] == (')',):
                opening = words.index('(')
                if opening and candidate_syntax.IDENTIFIER.fullmatch(words[opening - 1]):
                    found[words[opening - 1]].append(words)
            start = i + 1
        depth += (token.text == '{') - (token.text == '}')
        if token.text == '}' and depth == 0:
            start = i + 1
    return found


def changed_signatures(before_source: str, after_source: str) -> list[str]:
    """Warn on changed signatures, including changed unsupported/ambiguous headers.

    This compares declarations, not typedef definitions or expanded macros.
    Unsupported forms remain review leads; no ABI is inferred for them.
    """
    before = call_signatures.source_signatures(before_source)
    after = call_signatures.source_signatures(after_source)
    old_headers, new_headers = _headers(before_source), _headers(after_source)
    changed = []
    for symbol in sorted(before.keys() | after.keys()):
        old, new = before.get(symbol, set()), after.get(symbol, set())
        uncertain = len(old) != 1 or len(new) != 1 or None in old or None in new
        if old != new or (uncertain and old_headers.get(symbol) != new_headers.get(symbol)):
            changed.append(symbol)
    return changed


def _has_unhandled_zero_alternative(source: str) -> bool:
    """Flag alternatives active_text may omit after a literal #if 0."""
    source = re.sub(r'/\*.*?\*/|//[^\n]*', '', source, flags=re.S)
    stack = []
    for line in source.splitlines():
        if declaration_facts.PREPROCESSOR_IF.match(line):
            stack.append(bool(declaration_facts.PREPROCESSOR_IF_ZERO.match(line)))
        elif re.match(r'^\s*#\s*(?:else|elif)\b', line):
            if stack and stack[-1]:
                return True
        elif declaration_facts.PREPROCESSOR_ENDIF.match(line) and stack:
            stack.pop()
    return False


def classify_signature_changes(before_source: str, after_source: str) -> dict[str, list[str]]:
    """Separate contract changes from additions using only the two source snapshots.

    An addition referenced by existing local C is a review lead: an included header
    or macro may already declare it, so it is not proof of an implicit ABI change.
    """
    before = call_signatures.source_signatures(before_source)
    after = call_signatures.source_signatures(after_source)
    differences = set(changed_signatures(before_source, after_source))
    added = sorted(differences - before.keys())
    existing_calls = set()
    uncertain_callers = False
    if added:
        definitions = call_signatures.source_signatures(before_source, definitions_only=True)
        bodies = source_bodies(before_source, set(definitions), active_only=True)
        # Unknown preprocessor branches can contain duplicate definitions. Missing
        # bodies must not turn incomplete local coverage into a suppressed warning.
        uncertain_callers = (bool(definitions.keys() - bodies.keys())
                             or _has_unhandled_zero_alternative(before_source))
        for body in bodies.values():
            existing_calls.update(source_calls(body))
    return {
        'changed': sorted(differences & before.keys() & after.keys()),
        'removed': sorted(differences - after.keys()),
        'added': added,
        'added_with_existing_calls': sorted(set(added) & existing_calls),
        'added_with_uncertain_callers': sorted(set(added) - existing_calls) if uncertain_callers else [],
    }


def affected_callers(root: Path, symbols: list[str]) -> list[dict]:
    """Return possible matched direct callers; an empty result is not complete coverage."""
    wanted = set(symbols)
    if any(not candidate_syntax.IDENTIFIER.fullmatch(symbol) for symbol in wanted):
        raise ValueError('callee names must be C identifiers')
    if not wanted:
        return []
    entries = json.loads((root / 'progress/functions.json').read_text())['functions']
    owners = Counter(entry['symbol'] for entry in entries)
    sources = defaultdict(list)
    for entry in entries:
        region = entry.get('regions', {}).get('us', {})
        if (owners[entry['symbol']] == 1 and region.get('state') == 'matched'
                and region.get('evidence', {}).get('current_differences') == 0):
            sources[entry['source']].append(entry['symbol'])
    results = []
    for source in sorted(sources):
        path = root / source
        if not path.resolve().is_relative_to(root.resolve()):
            raise ValueError(f'source is outside repository: {source}')
        bodies = source_bodies(path.read_text(), set(sources[source]), active_only=True)
        for caller, body in sorted(bodies.items()):
            callees = sorted(source_calls(body) & wanted)
            if callees:
                results.append({'symbol': caller, 'source': source, 'callees': callees,
                                'basis': 'direct C call spelling', 'coverage': 'incomplete'})
    return results


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('symbols', nargs='+', help='callee names whose matched direct callers need rechecking')
    parser.add_argument('--root', type=Path, default=ROOT)
    args = parser.parse_args(argv)
    try:
        callers = affected_callers(args.root, args.symbols)
    except (OSError, ValueError, KeyError, TypeError) as error:
        print(f'error: caller lookup failed: {error}', file=sys.stderr)
        return 1
    print(json.dumps({'callees': sorted(set(args.symbols)), 'coverage': 'incomplete',
                      'limitations': LIMITATIONS, 'callers': callers}, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
