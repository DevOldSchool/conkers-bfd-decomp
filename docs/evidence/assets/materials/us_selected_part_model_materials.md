# US renderer-selected part material correlation

The normal and offscreen head lists in bank-01 entry 130 contain the same
triangle pattern and use palette-global matrix slot 12. Active-character and
matrix evidence alone therefore cannot distinguish source run 46 / cluster 56
/ first face 602 from run 69 / cluster 97 / first face 1,395. The old material
extractor left some of these observations ambiguous, although character
composition already resolved the renderer's selected part sequence.

`selected_part_material_candidates` now reuses that validated sequence. The
character-draw loader checks the current ROM topology, part-table pointers,
paired renderer call, and captured commands. Each ordered cluster must match
exactly one refreshed candidate by model SHA-1, cluster index, first face,
triangle count and material-run index. The sequence must cover the complete
renderer command range. Duplicate return or runtime-cluster identities fail.
Existing captured-vertex byte checks still constrain the accepted face span.

Accepted draw evidence records the command SHA-256, return event, source cluster
and part-selection event indices. No material state, texture pixel or lighting
value is inferred from the selected model's appearance.

## Positive capture and regenerated results

The source is
`build/assets/models/us/runtime-traces/character-draws-part-selections/save-game-26.jsonl`,
SHA-256 `50409577b2fe4719dbdef9222258d8efcca8eabe010c368d61967165f8818718`.
All eight renderer returns resolve: entry 130 has two 38-cluster offscreen
calls and two 68-cluster normal calls; entries 94 and 67 each have two calls
with 36 and four clusters respectively. Every ordered cluster has one exact
current ROM correlation.

Regenerating the original complete trace sets gives:

| Catalog | Material records | Variants | Draw observations |
| --- | ---: | ---: | ---: |
| Aggregate graphics tasks | 603 | 1,944 | 15,236 |
| Character renderer calls | 236 | 1,112 | 15,052 |
| Submitted vertex-colour capture | 63 | 63 | 373 |

The character catalog gains 32 records, 69 variants and 1,820 observations.
The new records cover 515 source faces in entries 4 and 130, with bounded
observations for every face. No old record or variant is removed. Old material
state, image data and lighting values are preserved; existing evidence changes
only where correlation becomes more specific. The aggregate and submitted
vertex-colour catalogs remain byte-identical to their prior versions.

There are 2,071 accepted selected-part cluster correlations and 14,306 accepted
draw observations carrying the new evidence. Twenty-two composed glTF records
change their material assignments while source faces, drawable faces and
cluster counts remain fixed. Entry 130's normal Save-Game-26 compositions now
use runtime materials for all 68 runs, with 61 textured runs / 646 textured
faces; the offscreen compositions resolve all 38 runs.

The regenerated `previews/entry-0130-save-game-26-posed.png` visibly shows the
captured face through the visor. The neutral aggregate preview remains a
topology review and does not contain every captured facial input. Neither
image establishes native lighting or raster parity. Explicit static visor
blending is covered separately in
[static raster-state evidence](us_static_model_raster_state.md).

## Reproduction and checks

Ignored evidence is under
`build/assets/models/reference/selected-part-materials/`: source and output
snapshots, the catalog regeneration recipe, `catalog-comparison.json`,
`preservation-check.json`, `composition-comparison.json`, rendered images and
`audit.json`. The recipe verifies the original trace and activity hashes before
calling `./conker model-assets materials`; preview and composition regeneration
uses the supported `./conker model-assets` commands.

Regression coverage proves ambiguous same-matrix sibling selection and rejects
incomplete sequence coverage, a changed source span and a changed ROM hash.
With the subsequent static raster-state fix, all 580 Python tests pass,
changed scripts compile, all four model banks rebuild byte-identically, and
current per-file Blender evidence covers 1,546 main and 1,469 captured-colour
review glTFs. Unchanged files retain validation only when their complete input
fingerprint matches; changed glTFs are imported again.
