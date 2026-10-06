# US model face culling

The model exporter previously marked every glTF material as double-sided.
It now preserves proven back-face culling from each triangle's display-list
state. This corrects visible outside surfaces without removing source geometry.

## Consumer and state evidence

The local SDK's `gSPGeometryMode` macro in `lib/ultralib/include/PR/gbi.h`
encodes the complement of the clear mask in the low 24 bits of `D9`, followed
by the set mask. F3DEX2 uses `0x200` for front and `0x400` for back culling.
The pinned [CBFD handler](https://github.com/gonetz/GLideN64/blob/41c7ba273a6c9afb43c0574cf3cf5d139182d070/src/uCodes/F3DEX2CBFD.cpp#L106)
selects F3DEX2 geometry flags and its geometry-mode handler.

The parser tracks values and known bits separately. Clearing or setting one
culling bit does not establish the other bit. RDP other-mode changes preserve
RSP culling. Unresolved segment-8 calls invalidate culling knowledge, and an
independently callable display list starts with unknown inherited state.

Culling state is stored per source face, so existing material-run identities
and face order remain unchanged. A glTF run is partitioned at culling changes;
every primitive retains its source run and exact face span. The verifier rejects
gaps, overlaps, wrong run identities, incorrect index counts, lost runtime
material association and culling flags inconsistent with the retained evidence.
Posing, composition and zero-area filtering preserve face-state alignment.

## Scene-24 enclosure

Bank 04, entry 24, segment 2 contains twelve black, inward-facing triangles at
source faces 7–18. Their coordinates form an enclosure; every face normal points
toward its centre. At segment offsets `0x151C8` and `0x151D0`, the commands
`D9FAFDFF 00000000` and `D9FFFFFF 00000400` establish back-face culling before
those triangles.

The refreshed exterior preview rejects the outward sides and reveals interior
geometry and backdrop textures that were previously hidden. The enclosure
remains because it is source geometry. Its runtime scene relationship and the
complete appearance of the assembled scene are still unverified.

## Coverage and verification

| Source state | Source faces | Drawable preview faces |
| --- | ---: | ---: |
| Back-face culling | 148,124 | 147,904 |
| Culling disabled | 6,868 | 6,865 |
| Inherited or unresolved | 67,850 | 67,823 |

Ninety-five material runs require multiple glTF primitives. All 1,186 models,
222,842 source faces, 222,592 drawable faces, texture links, placement records
and composition geometry counts are preserved. No source draw in this corpus
establishes front-only or both-face culling; these modes remain explicitly
unsupported by the preview mapping.

All four model banks rebuild byte-identically, all 573 Python tests pass, and
Python compilation and scoped whitespace checks pass. The complete Blender
gates import 1,546 main glTFs and 1,469 captured-colour review glTFs. They verify
that every imported culling property matches its glTF evidence, including 7,636
back-culled materials in the main set and 7,626 in the review set.

Blender now imports 399,102 main polygons and 370,598 review polygons, two more
in each set. This is confined to bank 04, entry 12, segment 0. Source face pairs
309/317 and 310/318 use the same vertices in opposite orders under different
culling states. A minimal Blender reproduction imports only one polygon when
an opposite pair shares one primitive, but preserves both when partitioned.
Both glTF inputs contain two triangles. No source triangles were added.

Haybot and the captured Conker body with its cigar and helmet retain identical
rendered RGBA pixels. Static texture coverage remains 8,202 resolved runs and
1,218 missing runs; runtime material, inherited culling, scene assembly and
native raster parity remain separate frontiers.

Evidence, before images, source snapshots, the minimal opposite-face import
reproduction, full validation reports and regeneration scripts are under
`build/assets/models/reference/geometry-culling/`. See `enclosure-evidence.json`,
`opposite-face-pairs.json`, `opposite-face-import.json`, `survey.json` and
`audit.json` for machine-readable checks.
