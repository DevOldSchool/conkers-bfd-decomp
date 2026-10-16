from __future__ import annotations

import json
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
import declaration_conflicts as dc
import struct_layouts as sl

FIXTURES = ROOT / 'tests' / 'fixtures' / 'struct_layouts'
# Synthetic fixtures; these are not copied project or ROM sources.


def fixture_report(min_copies: int = 2) -> dict:
    headers = {'types.h': (FIXTURES / 'types.h').read_text()}
    sources = {name: (FIXTURES / name).read_text() for name in ('alpha.c', 'beta.c')}
    matched = sl.matched_functions(FIXTURES)
    return sl.analyze(headers, sources, matched, min_copies)


def cluster_named(report: dict, name: str) -> dict:
    return next(c for c in report['clusters'] if any(d['name'] == name for d in c['definitions']))


class ScanTests(unittest.TestCase):
    def test_members_follow_declaration_conflicts_layout(self):
        text = 'typedef struct Thing { u8 kind; u8 pad1[3]; f32 value; s16 pair[2]; } Thing;\n'
        definitions, functions, skipped = sl.scan_file(text, 'thing.c', dc.Context(), shared=False)
        self.assertEqual(1, len(definitions))
        definition = definitions[0]
        self.assertEqual(('Thing', 'struct', ('struct Thing', 'Thing'), 0), (definition.name, definition.kind, definition.names, skipped))
        self.assertEqual([('kind', 0, 1, False), ('pad1', 1, 3, True), ('value', 4, 4, False), ('pair', 8, 4, False)],
                         [(m.name, m.offset, m.size, m.pad) for m in definition.members])
        # The clustering key is exactly the declaration-conflicts aggregate layout.
        body = dc.collapse_braces([word for word, _ in dc.tokenize(dc.preprocess(text))])
        expected = dc.aggregate_layout(next(w for w in body if isinstance(w, dc.Body)).tokens, False, dc.Context())
        self.assertEqual(expected, definition.layout)
        self.assertEqual((12, 4), definition.layout[:2])
        self.assertEqual('u8@0x0, u8[3]@0x1, f32@0x4, s16[2]@0x8', sl.shape_text(definition.layout))

    def test_nested_bodies_bitfields_and_disabled_blocks(self):
        definitions, _, skipped = sl.scan_file((FIXTURES / 'alpha.c').read_text(), 'alpha.c', dc.Context(), shared=False)
        names = [(d.name, d.nested, d.layout is not None) for d in definitions]
        self.assertEqual([('AlphaVec3', False, True), ('AlphaOwner.velocity', True, True),
                          ('AlphaOwner', False, True), ('AlphaBits', False, False)], names)
        self.assertEqual('bitfield', definitions[-1].reason)
        self.assertEqual(1, skipped)

    def test_functions_record_parameter_local_and_mention_types(self):
        _, functions, _ = sl.scan_file((FIXTURES / 'alpha.c').read_text(), 'alpha.c', dc.Context(), shared=False)
        by_name = {f.name: f for f in functions}
        self.assertEqual({'func_alpha_use', 'func_alpha_cast', 'func_alpha_shared', 'func_alpha_unmatched'}, set(by_name))
        self.assertIn('AlphaVec3', by_name['func_alpha_use'].parameter_types)
        self.assertIn('AlphaOwner', by_name['func_alpha_use'].local_types)
        self.assertNotIn('AlphaVec3', by_name['func_alpha_cast'].parameter_types | by_name['func_alpha_cast'].local_types)
        self.assertIn('AlphaVec3', by_name['func_alpha_cast'].mentioned)
        self.assertIn('SharedVec3', by_name['func_alpha_shared'].parameter_types)  # K&R declaration list

    def test_unknown_member_type_has_no_layout(self):
        definitions, _, _ = sl.scan_file('typedef struct { Mystery m; s32 a; } Holder;\n', 'h.c', dc.Context(), shared=False)
        self.assertIsNone(definitions[0].layout)
        self.assertEqual('unknown member type for `m`', definitions[0].reason)


class ClusterTests(unittest.TestCase):
    def test_identical_layouts_cluster_regardless_of_names(self):
        report = fixture_report()
        vec3 = cluster_named(report, 'AlphaVec3')
        self.assertEqual(['AlphaOwner.velocity', 'AlphaVec3', 'BetaVector', 'SharedVec3'],
                         sorted(d['name'] for d in vec3['definitions']))
        self.assertEqual((4, 3, 1, 1), (vec3['copies'], vec3['file_count'], vec3['shared_copies'], vec3['nested_copies']))
        self.assertEqual('f32@0x0, f32@0x4, f32@0x8', vec3['shape'])
        self.assertEqual('f32 x; f32 y; f32 z;', vec3['canonical'])
        self.assertEqual(['y@0x4', 'z@0x8'], vec3['agreeing_fields'])
        self.assertEqual([{'offset': 0, 'name': 'x', 'count': 3, 'others': {'posX': 1}}], vec3['majority_fields'])
        self.assertEqual([], vec3['conflicting_fields'])
        self.assertEqual(1, report['clusters'].index(vec3) + 1)

    def test_matched_function_counts_use_parameters_and_locals_only(self):
        report = fixture_report()
        vec3 = cluster_named(report, 'AlphaVec3')
        # func_alpha_use (parameter), func_alpha_shared (header copy, K&R) and
        # func_beta_local (local); the cast-only and unmatched functions are not uses.
        self.assertEqual(['alpha.c:func_alpha_shared', 'alpha.c:func_alpha_use', 'beta.c:func_beta_local'],
                         vec3['matched_function_names'])
        self.assertEqual(4, vec3['matched_functions_mentioning'])
        route = cluster_named(report, 'BetaRoute')
        self.assertEqual(['beta.c:func_beta_local'], route['matched_function_names'])  # `struct BetaRoute route;`

    def test_pad_variants_and_prefix_relations(self):
        report = fixture_report()
        vec3 = cluster_named(report, 'AlphaVec3')
        near = vec3['near_matches']
        self.assertEqual(['BetaPoint'], [b['example'] for b in near['pad_variants']])
        self.assertEqual(['BetaRoute'], [b['example'] for b in near['prefix_of']])
        self.assertEqual([], near['extends'])
        command = cluster_named(report, 'SharedCommand')
        self.assertEqual(['SharedCommand', 'GammaCommand'], [d['name'] for d in command['definitions']])
        self.assertEqual(['BetaCommand'], [b['example'] for b in command['near_matches']['pad_variants']])
        self.assertEqual(['opcode@0x0'], command['agreeing_fields'])
        self.assertEqual([{'offset': 4, 'names': {'word1': 1, 'data': 1}, 'copies_with_member': 2}],
                         command['conflicting_fields'])  # 1 of 2 is not a majority
        self.assertEqual([], command['near_matches']['prefix_of'])
        # Clusters below --min-copies get no near-match scan.
        self.assertNotIn('near_matches', cluster_named(report, 'BetaPair'))

    def test_summary_counts(self):
        summary = fixture_report()['summary']
        self.assertEqual(3, summary['files_scanned'])
        self.assertEqual(12, summary['definitions'])
        self.assertEqual(1, summary['definitions_in_disabled_blocks'])
        self.assertEqual(1, summary['definitions_with_unknown_layout'])
        self.assertEqual(1, summary['nested_definitions'])
        self.assertEqual(2, summary['shared_header_definitions'])
        self.assertEqual(7, summary['distinct_layouts'])
        self.assertEqual(5, summary['distinct_layouts_ignoring_pads'])
        self.assertEqual(4, summary['duplicate_definitions'])
        self.assertEqual(2, summary['clusters_at_or_above_min_copies'])
        self.assertEqual(6, summary['pad_fields'])
        self.assertEqual(3, summary['matched_functions_using_reported_clusters'])
        self.assertEqual(4, summary['matched_functions_in_inventory'])

    def test_min_copies_limits_detailed_clusters(self):
        report = fixture_report(min_copies=4)
        self.assertEqual(1, report['summary']['clusters_at_or_above_min_copies'])
        self.assertNotIn('near_matches', cluster_named(report, 'SharedCommand'))


class RenderTests(unittest.TestCase):
    def test_markdown_and_json_render(self):
        report = fixture_report()
        markdown = sl.render_markdown(report, limit=1)
        self.assertIn('### #1: 4 copies in 3 files, 3 matched functions (4 mentioning the type)', markdown)
        self.assertIn('Canonical: `f32 x; f32 y; f32 z;`', markdown)
        self.assertIn('Fields unanimous: `y@0x4`, `z@0x8`. Majority: `x@0x0` 3/4 (also posX). Split: none.', markdown)
        self.assertIn('pad variants: `BetaPoint`', markdown)
        self.assertIn('_1 more in `struct-layouts.json`._', markdown)
        self.assertIn('| `AlphaBits` (alpha.c:', markdown)
        encoded = json.dumps(sl.json_ready(report))
        self.assertIn('"matched_function_names"', encoded)
        self.assertNotIn('"nonpad"', encoded)


if __name__ == '__main__':
    unittest.main()
