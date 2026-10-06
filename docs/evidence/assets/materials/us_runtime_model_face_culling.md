# US captured model face culling

The exporter now resolves inherited back-face culling on another 3,826 source
faces across 21 models. This includes all 338 Tediz faces, all 811 Conker body
faces, and captured attachment surfaces. Source geometry is unchanged.

## Captured command evidence

`mupen_trace.py` replays `D9` geometry-mode commands from the existing,
hash-checked command buffers and nested display lists. Values and known bits
are tracked separately. A captured call's ancestry must prove that its callee
was expanded; unresolved calls invalidate inherited knowledge. RDP other-mode
commands preserve RSP geometry state, and returning from an expanded list
retains that list's state in its caller.

The pinned [CBFD implementation](https://github.com/gonetz/GLideN64/blob/41c7ba273a6c9afb43c0574cf3cf5d139182d070/src/uCodes/F3DEX2CBFD.cpp#L106)
uses the F3DEX2 geometry flags and handlers. It also supports conditional list
culling and depth branches. The existing flattener does not execute those
conditions, so the culling replay declines the entire affected stream when
either opcode occurs. None occurs in the 1,318 decoded opcode tables from the
46 unique source traces used by the three current material catalogs.

Each draw receives separate culling evidence with its source face range.
Recorded material state, variant hashes, texture PNG identities, translations
and lighting evidence remain exactly unchanged. The catalogs retain their
603/1,944, 204/1,043 and 63/63 material/variant counts.

## Correlation boundaries

Culling is applied only to the observed source face range, after mapping
composition and filtered faces back to their source indices. Every bounded
observation of a face must agree. Missing legacy evidence leaves the ROM state
in place; conflicting or unknown observations cannot resolve inherited state.

Equivalent material aliases do not establish which source list supplied its
geometry state. All 59 aggregate records containing these aliases are excluded
from culling application. Of the remaining correlated faces, eight disagree
with explicit ROM state: four in bank 04 entry 28 segment 0, and four in entry
57 segment 0. The exporter retains their ROM state and records
`runtimeConflictFaceCount`; command-pattern correlation does not establish a
runtime rewrite. These disagreements remain an investigation frontier.

The aggregate catalog has eligible bounded evidence on 12,010 source faces
across 68 models. Most already have the same explicit ROM state. The newly
resolved inherited faces are:

| Bank | Models | Source faces |
| --- | ---: | ---: |
| 01 | 10 | 3,203 |
| 03 | 1 | 2 |
| 04 | 4 | 329 |
| 09 | 6 | 292 |

## Export and visual verification

The main standalone exports now contain 151,723 drawable back-culled faces,
6,865 with culling disabled and 64,004 with unresolved inherited state. Their
source counts are 151,950, 6,868 and 64,024 respectively. Every source run ID and
ordered face span remains intact. All 1,186 models, 222,842 source faces,
222,592 drawable faces, texture links, placements and composition counts are
preserved. Texture coverage remains 8,202 resolved runs and 1,218 missing runs.

Both preview collections and the character compositions were regenerated.
Blender re-imported 189 changed main glTFs and eight changed captured-colour
glTFs; prior validation was retained only for identical file fingerprints.
The complete current inventories cover 1,546 main files and 1,469 review files,
including imported material culling checks. Polygon totals remain 399,102 and
370,598 respectively. All 577 Python tests pass, all four model banks rebuild
byte-identically, and Python compilation and scoped whitespace checks pass.

The refreshed front Tediz image changes by three pixels; its three-quarter
image changes by one. Haybot remains pixel-identical. Culling changes 5,931
pixels in the standalone helmet, 3,092 in the posed Conker composition and
2,775 in entry 130. These changes reject back-facing surfaces, including
overlapping strap surfaces. The geometry and texture bytes are unchanged.
Conker's bind-pose and geometry diagnostics were also refreshed. The older
isolated attachment PNG is retained as a historical comparison, rather than
claimed to match the current culling-aware composition.

The native gameplay screenshot has a different camera and scene, so this is
not a pixel-parity claim. Aggregate facial/render-target inputs, unobserved
material state, scene association and complete native appearance remain open.
The user-supplied cutscene Conker model remains excluded as a gameplay reference.

Reproduction, source snapshots, before images and machine-readable checks are
under `build/assets/models/reference/runtime-face-culling/`. See
`regenerate_materials.py`, `regenerate.py`, `validate_changed.py`, the three
render scripts, `audit_catalogs.py`, `survey.py`, `catalog-audit.json`,
`conditional-opcodes.json`, `image-comparison.json` and `audit.json`.
