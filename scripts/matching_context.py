#!/usr/bin/env python3
"""Bounded, read-only matching leads; never a substitute for raw evidence or finish."""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

import call_signatures
import candidate_syntax
import declaration_facts


ROOT = Path(__file__).resolve().parent.parent
INDEX = 'config/matching-mechanisms.json'
MAX_SOURCE_SIBLINGS = 64


def source_bodies(source: str, wanted: set[str], *, active_only: bool = False) -> dict[str, str]:
    """Read ordinary definitions once; comments, strings and declarations cannot match."""
    if active_only:
        source = declaration_facts.active_text(source)
    items = candidate_syntax.tokens(source)
    bodies: dict[str, list[str]] = {}
    for i, token in enumerate(items[:-1]):
        if token.text not in wanted or items[i + 1].text != '(':
            continue
        depth = 1
        j = i + 2
        while j < len(items) and depth:
            depth += (items[j].text == '(') - (items[j].text == ')')
            j += 1
        if depth or j == len(items) or items[j].text != '{':
            continue
        start = j
        depth = 1
        j += 1
        while j < len(items) and depth:
            depth += (items[j].text == '{') - (items[j].text == '}')
            j += 1
        if depth:
            return {}
        bodies.setdefault(token.text, []).append(source[items[start].start:items[j - 1].end])
    return {symbol: definitions[0] for symbol, definitions in bodies.items() if len(definitions) == 1}


def function_body(source: str, symbol: str, *, active_only: bool = False) -> str:
    return source_bodies(source, {symbol}, active_only=active_only).get(symbol, '')


def source_calls(body: str) -> set[str]:
    items = candidate_syntax.tokens(body)
    opening = next((i for i, token in enumerate(items) if token.text == '{'), len(items))
    ignored = {'if', 'for', 'while', 'switch', 'sizeof'}
    return {items[i].text for i in range(opening + 1, len(items) - 1)
            if candidate_syntax.IDENTIFIER.fullmatch(items[i].text)
            and items[i + 1].text == '(' and items[i].text not in ignored
            and items[i - 1].text not in {'.', '->'}}


def load_index(root: Path) -> list[dict]:
    data = json.loads((root / INDEX).read_text())
    if data.get('schema_version') != 1 or not isinstance(data.get('mechanisms'), list):
        raise ValueError('unsupported matching mechanism index')
    mechanisms = data['mechanisms']
    names = [item['name'] for item in mechanisms]
    if len(names) != len(set(names)):
        raise ValueError('duplicate matching mechanism name')
    return mechanisms


def address(entry: dict) -> int:
    try:
        return int(entry['regions']['us']['vram'], 0)
    except (KeyError, TypeError, ValueError):
        return 0


def matching_context(root: Path, symbol: str, *, mechanism: str | None = None,
                     limit: int = 3) -> dict:
    if not 1 <= limit <= 10:
        raise ValueError('limit must be between 1 and 10')
    mechanisms = load_index(root)
    if mechanism is not None and mechanism not in {item['name'] for item in mechanisms}:
        raise ValueError(f'unknown mechanism: {mechanism}')
    entries = json.loads((root / 'progress/functions.json').read_text())['functions']
    choices = [entry for entry in entries if symbol in {
        entry.get('symbol'), entry.get('regions', {}).get('us', {}).get('symbol')}]
    if len(choices) != 1 or 'us' not in choices[0].get('regions', {}):
        raise ValueError(f'expected one registered US function for {symbol}; found {len(choices)}')
    target = choices[0]
    source_path = target['source']
    path = root / source_path
    source = path.read_text() if path.is_file() else ''
    body = function_body(source, target['symbol'])
    raw_path = call_signatures.raw_callee_path(root, target['regions']['us']['symbol'])
    # Only this target's existing full-span raw extract is read. No extraction,
    # repository-wide assembly search, cached-report refresh, or build occurs.
    if raw_path is not None:
        callees = call_signatures.direct_callees(raw_path.read_text())
        call_basis = f'raw direct calls: {raw_path.relative_to(root)}'
    else:
        callees = source_calls(body)
        call_basis = 'source call spellings; raw reference unavailable or unvalidated'
    reason = target.get('deferred', {}).get('reason', '')
    scored = []
    for item in mechanisms:
        evidence = []
        if target['symbol'] in item.get('symbols', []):
            evidence.append('recorded example or counterexample')
        overlap = callees.intersection(item.get('callees', []))
        if overlap:
            evidence.append('callee ' + ', '.join(sorted(overlap)))
        if any(re.search(pattern, reason, re.I) for pattern in item.get('reason_patterns', [])):
            evidence.append('saved deferred reason; may be stale')
        if mechanism == item['name']:
            evidence.append('explicit mechanism selection')
        if evidence and (mechanism is None or mechanism == item['name']):
            scored.append((len(evidence), item['name'], {**item, 'selected_by': evidence}))
    selected = [item for _, _, item in sorted(scored, key=lambda row: (-row[0], row[1]))[:limit]]

    # Nearby means same registered source, ordered by US address distance. This
    # is intentionally a bounded local sample, not a complete caller impact audit.
    local = [entry for entry in entries if entry.get('source') == source_path
             and entry['symbol'] != target['symbol']]
    wanted = {entry.get('regions', {}).get('us', {}).get('symbol') for entry in local}
    matched = call_signatures.matched_definition_sources(root, wanted, 'us')
    local = [entry for entry in local if entry.get('regions', {}).get('us', {}).get('symbol') in matched]
    local.sort(key=lambda entry: (abs(address(entry) - address(target)), entry['symbol']))
    siblings = []
    bodies = source_bodies(source, {entry['symbol'] for entry in local[:MAX_SOURCE_SIBLINGS]},
                           active_only=True)
    for entry in local[:MAX_SOURCE_SIBLINGS]:
        sibling_body = bodies.get(entry['symbol'], '')
        if not sibling_body:
            continue
        shared = sorted(source_calls(sibling_body) & callees)
        siblings.append({'symbol': entry['symbol'], 'source': source_path,
                         'shared_callees': shared[:limit], 'shared_callee_count': len(shared),
                         'distance': abs(address(entry) - address(target))})
    family = [entry for entry in siblings if entry['shared_callees']][:limit]
    return {'symbol': target['symbol'], 'source': source_path, 'mechanisms': selected,
            'callees': sorted(callees)[:limit], 'callee_count': len(callees),
            'call_basis': call_basis, 'family': family, 'siblings': siblings[:limit],
            'sampled_matched_siblings': min(len(local), MAX_SOURCE_SIBLINGS),
            'total_matched_siblings': len(local)}


def render(context: dict) -> str:
    lines = [f"Matching context: {context['symbol']} ({context['source']})",
             'Leads are hypotheses, not ABI or match proof; inspect raw evidence and use finish.']
    for item in context['mechanisms']:
        lines += [f"- {item['name']} [{'; '.join(item['selected_by'])}]: {item['hypothesis']}",
                  f"  Raw/source clues: {item['clues']}",
                  f"  Success: {item['success']}",
                  f"  Counterexample: {item['counterexample']}",
                  '  Evidence: ' + ', '.join(item['evidence'])]
        if item.get('historical_chats'):
            lines.append('  Historical chats: ' + ', '.join(item['historical_chats']))
    if not context['mechanisms']:
        lines.append('No indexed mechanism selected; use --mechanism for a specific residual.')
    if context['callees']:
        suffix = ' (truncated)' if context['callee_count'] > len(context['callees']) else ''
        lines.append(f"Direct-callee leads ({context['call_basis']}): " + ', '.join(context['callees']) + suffix)
    if context['family']:
        lines.append('Same-source matched callers sharing a callee (source spellings; incomplete impact sample):')
        lines.extend(f"- {item['symbol']} -> {', '.join(item['shared_callees'])}"
                     + (' (truncated)' if item['shared_callee_count'] > len(item['shared_callees']) else '')
                     + f" ({item['source']})"
                     for item in context['family'])
    if context['siblings']:
        lines.append('Nearby inventory-matched definitions (same source; similarity and current match unverified):')
        lines.extend(f"- {item['symbol']} ({item['source']}, US address distance 0x{item['distance']:X})"
                     for item in context['siblings'])
    if context['sampled_matched_siblings'] < context['total_matched_siblings']:
        lines.append(f"Caller sample capped at {context['sampled_matched_siblings']} nearby definitions.")
    return '\n'.join(lines)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('symbol', help='registered work-item ID or unique US symbol')
    parser.add_argument('--mechanism', help='select contracts, real-state, or scope-lifetime')
    parser.add_argument('--limit', type=int, default=3, help='maximum entries per section (1-10; default 3)')
    args = parser.parse_args(argv)
    try:
        context = matching_context(ROOT, args.symbol, mechanism=args.mechanism, limit=args.limit)
    except (OSError, ValueError, KeyError, TypeError) as error:
        parser.exit(2, f'matching-context: {error}\n')
    print(render(context))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
