# ROM textures for placed objects

The ordinary object renderer supplies enough ROM-backed state to recover another
22 indexed material runs on 521 faces across 17 models in banks 03 and 04.
Every selected model then has a linked texture for every drawable material run.
This proves image selection and decoding for the reviewed draw path; runtime
colour, lighting, visibility, rewritten display lists and raster parity remain
separate questions.

Evidence uses normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. No save-state or reference-model data
is used by this decoder. Generated evidence is under
`build/assets/models/reference/prop-materials-20260910/`.

## Placement-to-renderer path

`func_150039E0` creates 0xA0-byte records rooted at `D_800DBEF4`. For bank-03
placements it loads `[03, record+0x10]` at `0x15003E00..0x15003E1C` and installs
the primary model list at runtime record `+0x1C` at `0x15003E94..0x15003E9C`.
Repeated models reuse that field from an earlier record. Bank-04 dispatch kinds
one and two select an indexed scene descriptor at `0x15004080..0x15004094`, then
install its primary list at `0x15004130..0x15004150`. Other dispatch kinds and
missing scene segments are excluded from this proof.

`func_151135C4` reads the same `D_800DBEF4` array, multiplies the selected index
by 0xA0 and passes that record to `func_151137D4` at `0x15113700..0x15113730`.
That renderer selects segment 8 from `0x80083D40` or `0x80083EC0` according to
effective opacity at `0x15113A00..0x15113A58`. Its direct branch emits the list
from record `+0x1C` at `0x15113BE4..0x15113BF0`.

The alternative branch, selected by runtime record `+0x70 & 2`, calls
`func_150A50C0` to rewrite the list. A model needs at least one resolved placement
whose initial flags select the direct path. Bank-03 flags come from byte nine
of the twelve-byte per-model table at `0x800A26C0`; these override placement
flags at `0x15003F10..0x15003F24`. Bank-04 flags come from placement byte `+0x3C`.
Both clear bit three during loading. The manifest retains each supporting
placement's scene, record index, hash and flag source. It does not claim that
the object is visible, or that these initial flags never change.

## State changes between setup and drawing

The calls after segment-8 setup were reviewed explicitly:

- `func_1510CDB8` emits primitive and environment colours, without rebinding
  segment 8. These colours remain runtime inputs.
- `func_1510D8C0` can emit object-specific segment bindings. Its registrations
  come through `func_1510D874`, whose three direct callers are
  `0x150C5210`, `0x150DE69C` and `0x1511A6C8`.
  The first and last register segments four/five. The middle caller loops
  twice, registering four/five and six/seven. None replaces segment eight.
- `func_150CF5E8` emits tile bounds for scrolling, without rebinding segment 8.
  The decoder still requires explicit proven image dimensions and load spans
  in each accepted model material.

Ten complete function spans are checked against ROM-derived SHA-1 values in
`scripts/model_object_materials.py`. The normalized code scan also checks the
exact direct jump/call sites of `func_1510D874` and rejects a pointer to it in
the aligned game-data words. This is a bounded static producer audit, not a
claim that arbitrary computed code references have been exhaustively resolved.

## Texture-only consensus

The exporter applies the existing strict texture decoder to all eleven verified
ROM segment-8 table variants. It accepts a result only when every variant
produces identical texture bytes and status. Thus it does not need to select
one of the object's opacity branches. The selected OtherMode is not propagated
into glTF blending, and neither runtime colours nor lighting are invented.

Explicit or partially known OtherMode state is not replaced. Existing captured
materials are not changed. A material lacking a supported placement context
stays unresolved. Per-material `romTextureStateConsensus` metadata links the
texture agreement to its object renderer context; the preview manifest carries
the complete ROM consumer and placement evidence.

The recovered models are bank 03 entries 3, 58, 91 and 95, and bank 04 pairs
12/29, 19/17, 20/9, 28/13, 35/14 and 54/6 through 54/13. Bank-03 entry 3 already
has a captured material in the main comparison corpus, so that copy is
preserved. Its inspection source is the unobserved ROM-derived record in the
other existing corpus. Both source choices are checked against independent
ROM-only exports with capture and previous-output reads forbidden.

## Verification

Regenerate each existing corpus with its original runtime-material argument,
then run the supported validation and publication commands:

```sh
./conker model-assets validate
./conker model-assets inspect
```

The validation pipeline reconstructs the object context, texture bytes and
material evidence from the ROM, checks them against both manifests, and
rejects mixed captured/consensus records. Tests cover the placement/default
flag distinction, rewritten and missing dispatches, consumer changes, additional
direct callers, data pointers, missing context, conflicting texture-state
variants, altered image bytes and forged provenance.

Independent exports of all 17 selected models have byte-identical glTF, buffer
and image dependencies (90 file comparisons) while refusing capture or prior
model-output reads. Existing geometry buffers are unchanged. Regression
references remain separate from current previews; first references for the new
models do not establish native appearance parity.

Final validation passes all four ROM bank gates, all 4,002 configured glTF and
Blender file checks, six submitted-rig cases and one submitted-composition case.
Of 89 regression renders, 82 pass and the seven earlier differences remain
flagged; all 17 new references pass. All 716 Python tests and whitespace checks
pass. The 65 packaged inspection GLBs also pass separate Khronos and actual
Blender import checks, including embedded image bytes. The previous 48 GLBs
and thumbnails are unchanged. No model or code changes were committed here.
