# Bank-09 object texture state

Forty ROM meshes recover 73 material runs on 1,003 faces.
These are small objects, effect pieces and fragments, including a hanging bell.
This improves their textures; the decoded model inventory remains 1,487.

The evidence comes from normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, using the decompressed executable
and its data region. Capture files and emulator save states are not inputs.

The separate [callback texture-binding proof](us_object_callback_texture_bindings.md)
admits four additional models through callbacks whose checked payloads preserve
segment 8. Its counts and bindings are separate from the ordinary-object cohort
described here.

## Consumer and constructor evidence

The question was whether bank-09 runs calling segment 8 can use the existing
ROM render-state consensus decoder. A bank-wide default is unsafe:

- `func_151336A8` loads bank 9 using the four-byte model lookup table at
  `0x800A3880`, passes the primary list to `func_1510CE60`, and relocates
  model-relative vertices through `func_15168E54`.
- `func_1513264C` selects the lookup index from template halfword `+0x56`.
  It saves the loaded model wrapper at object `+0x8C` and copies the template
  to object `+0x10`. Template flags `+0x50` therefore become object flags
  `+0x60`. Allocation kinds 25 and 72 both dispatch to `func_15132B80`.
- That renderer binds segment 8 to `0x80083740` or `0x800838C0`, according
  to opacity. Its final display-list call follows object `+0x8C` through the
  loaded model to the primary list.
- If object flag bit 16 is set, an optional callback executes *after* the
  binding. The callbacks use `func_15133EEC`, whose destination segment comes
  from an object field. The lookup table alone cannot rule out replacement
  of segment 8. The exporter therefore admits only the reviewed constructor
  paths below, whose initial flags leave bit 16 clear or whose signed callback
  index is the renderer's disabled sentinel `-1`.

`scripts/model_bank09_materials.py` pins 45 complete function spans, the
233-entry lookup table, six selector arrays, two selection-mask tables, a
20-record descriptor table, two type-dispatch jump tables, type-selected
fragment pointer/count/selector arrays and the relevant
render-dispatch fields. It decodes
and checks each recorded literal and stack store, then maps the selector
through ROM data. The whole-function pins cover the reviewed intervening
control/data flow; the small literal/store check is not a general MIPS
interpreter. Changed pins or unsupported instructions fail closed.

| Constructor | Lookup selectors | Bank-09 entries | Initial flags |
| --- | --- | --- | --- |
| `150B2EB4` | 28 | 204 | `0x09E8` |
| `150BB760` | 1 | 191 | `0x29E9` |
| `1518B6B0` | 4 | 194 | `0x29E8` |
| `150E5558` | 7 | 198 | `0x29E9` |
| `150DECC0` | 196 or 197 | 199 or 200 | `0x29E9` |
| `150BB498` | 31 | 207 | `0x09E8` |
| `15109C20` | 35 or 36 | 211 or 212 | `0x29E8` |
| `151A6F00` | 27 | 229 | `0x21E9` |
| `15010A60` | 86 | 345 | `0x0D00` |
| `150F892C` | 134 | 393 | `0x39E8` |
| `151BA518` | 39, 40, 41, 43, 44 | 214, 215, 216, 218, 219 | `0x39E9` |
| `151B8DB0` | 34 | 210 | `0x0900` or `0x0D00` |
| `151BB61C` through `15151D6C` | 4, 4, 7, 8, 24, 25, 29, 30, 32 | 194, 194, 198, 197, 201, 202, 205, 206, 208 | `0x29E8` |
| `151BBA9C` through `15152190` | 45, 46, 42 | 220, 221, 217 | `0x29E8` or `0x1029E8` |
| `1513A6E0`, set mask bits | 122–125 | 388–391 | `0x101900` |
| `1513A6E0`, clear mask bits | 118–121 | 384–387 | `0x1039E9` |
| `1513B0F8`, set mask bits | 227, 229 | 248, 250 | `0x101900` |
| `1513B0F8`, clear mask bits | 228, 230 | 249, 251 | `0x1039E9` |
| `15138424` through `15138BC0` | 20 descriptor records | 12 distinct entries | `0x39E9` |

The [constructor-table evidence](us_model_constructor_tables.md) details the
descriptor dispatch, two-entry loops, shared intensity decoding and automated
cohort diagnosis.

For example, `0x150BB660` loads selector 31, `0x150BB678` stores it at
`sp+0x82`, and `0x150BB6C4` passes `sp+0x2C` as the template. The difference
is `0x56`. Its flags literal/store at `0x150BB4F0/0x150BB4F8` similarly
establish template `+0x50`. Submission at `0x150BB6D8` uses the ordinary
constructor wrapper. Selector 31 resolves to ROM entry 207.

`150B2EB4` submits the template at `sp+0x24` through `15132A4C` at
`0x150B316C`. The flags literal/store at `0x150B2F0C/0x150B2F14` writes
`0x09E8` to `sp+0x74`; the selector literal/store at
`0x150B30F0/0x150B310C` writes 28 to `sp+0x7A`. No intervening store changes
those fields or passes the template address elsewhere. The complete 724-byte
function pin is `0e124ee088467533e58d78a87edf2c8694142825`.
Selector 28 maps to entry 204, recovering its eight faces from flat asset 1424.
The geometry is labelled as a faceted gray shard, without asserting a native
name or its emission behavior. Six independent ROM mutations verify that
changes to the field setup, submission or intervening flow fail the pin check.

The alternate selectors in `150DECC0` and `15109C20` are branch alternatives.
`151BA518` reuses one template at `sp+0xDC` across five submissions, changing
selector `+0x56` while flags `+0x50` remain `0x39E9`. Some submissions execute
inside bounded random-choice loops. The conditional flags in `151B8DB0` and
`15152190` are checked on both branch outcomes, including the delay slots and
32-bit `LUI` contribution. Bit 20 may change; bit 16 remains clear.

The two array callers copy exact ROM words to stack buffers and pass their
address and count to the reviewed helpers. Those helpers select a word using
`RNG % count` and submit its low halfword as the lookup selector. The arrays are
`0x800AA718` (nine words, SHA-1 `7ff9cb28ca0cf99ba0f5959133159dcf140501c9`)
and `0x8008FBA0` (three words, SHA-1 `d88080eac98a7119b89ad930cb043e3c2fa96ac5`).
The complete caller pins cover the array copy and absence of an intervening
write to that buffer. Additional checks verify the source address, count,
stack destination, helper call and selector store. Duplicate selections and
models already covered by direct constructors keep their existing proof.

Constructor evidence describes an initial draw path. It does not
establish visibility, later flag mutations, world placement or a captured frame.
The array evidence likewise covers initial ROM values, not later mutations.

## Complementary fragment loops

`1513A6E0` iterates two four-word ROM arrays. Both loops use indices 0–3
and the bit `1 << index`; a shared mask is selected with `RNG % 6` from
`0x800A4278`, whose bytes are `04 0C 06 07 0D 00` (SHA-1
`e9a9be10f39f99e9842f3e0f6b20e38dd69b50d8`). This describes conditional
submissions, not eight simultaneous fragments or a reconstructed effect.

| Array | SHA-1 | Submission | Template | Selector store | Mask condition |
| --- | --- | --- | --- | --- | --- |
| `800A4280` | `2500c94c8e5b569e4ec666db87d4e8eded11a013` | `1513A89C` → `15132A4C` | `sp+144` | `1513A8A0` → `sp+19A` | Bit set |
| `800A4290` | `d7494ec63fa885c74203a90d19fc5959d480d5af` | `1513AB48` → `1513264C` | `sp+A4` | `1513AA70` → `sp+FA` | Bit clear |

The flags are decoded as full 32-bit `LUI/ORI/SW` expressions, preserving
bit 20 and rejecting callback bit 16. The first is established at
`1513A780/1513A784/1513A7EC`; the second at
`1513A974/1513A984/1513AA34`. The complete 1,240-byte caller is pinned to
`9d9cb54a938ddfbf76f6fbcb1c00fa5697256a8b`. Additional guards check array
addresses, word indexing, mask polarity, loads, selector stores, template
arguments, loop bounds and submission calls.

The second loop also requires actor `+1D4` to be nonnull and the low four
bits of actor `+74` to differ from 15. Between its selector store and submission,
`15143134` writes only the position vector at `sp+CC..D7`, and `15143794`
writes the direction vector at `sp+D8..E3`. Their bounded output helpers
`150A7960` and `15142314` are pinned too; these outputs cannot overlap flags
at `sp+F4` or selector at `sp+FA`. The pinned RNG and trigonometric helpers
receive no pointer to those fields. Subsequent motion/lifetime stores remain
outside the selector and flags. The first loop's one-byte post-allocation copy
writes to the returned object's `+170`, not to the shared template.

All eight initial ROM selectors produce a reviewed context. Their 18 missing
CI4 runs cover 334 faces and three unique 64 × 32 images. Independent pixel
checks cover all 6,144 texels, including odd-row word swapping and the trailing
RGBA5551 palettes. All eight geometry exports pass buffer/material validation;
60 ROM mutations and eight forged glTF contexts are rejected. Each separately
stored surface variant has a reviewed preview and a regression baseline.
Artifacts and the ROM-only file-open audit are under
`build/assets/models/reference/ci4-array-bindings-20260912/`.

## Texture and export gates

The existing decoder tries all eleven verified ROM segment-8 table variants
and requires identical texture bytes and interpretation under every variant.
Only missing texture lookups on the 114 models with reviewed ordinary-object
contexts are eligible; explicit
OtherMode, partial state, captured materials and unreviewed models retain their
existing handling. Consensus selects texture bytes only. It does not choose
blending, lighting or an effective render pass. Forty contexts recover
missing texture links; other contexts either already have complete texture
links, contain deliberately untextured runs, or remain blocked by payload checks. Entry 194 recovers RGBA32. Entry 345
retains five deliberately untextured faces.

The guarded context resolves 73 material runs on 1,003 faces across
40 models. Geometry, source palette bytes and explicit untextured runs remain
unchanged.

The preview manifest records the constructors, decoded selector/flag fields,
lookup addresses and hashes. glTF materials retain the corresponding ROM
texture-state evidence. Batch validation independently reloads this context
from the ROM, re-decodes the textures and checks exported PNG bytes. The same
checks reject forged provenance, changed pixels and capture/consensus mixing.

Local verification artifacts are under
`build/assets/models/reference/bank09-materials-20260910/` and
`build/assets/models/reference/expansion-20260910-one-hour/`. The actual exporter
also runs with a file-open audit rejecting save states, capture streams and
other model-output reads. Every newly selected gallery source and its buffer
and image dependencies reproduce byte for byte. Existing geometry buffers and
texture PNGs are preserved. New inspection cases have separate regression
baselines. See [the asset roadmap](../asset-roadmap.md) for current gallery
and validation totals; native appearance remains incomplete.


## Unresolved callback variants

Entries 304 and 305 are still outside this contract. Constructor `151C9198`
sets callback flag bit 16 and callback index 2. Its two eight-byte binding
records at object `+0x174` and `+0x17C` select pixel segments 4 and 6; callback
`15133FD8`, reached through table `0x800899A4`, invokes `15133EEC` to bind the
pixels and CI8 palettes to segments 4/5 and 6/7.

| Entry | Caller argument nonzero | Caller argument zero |
| --- | --- | --- |
| 304 | Descriptor 135/136: flat 2968/2969 | Descriptor 139/140: flat 2977/2978 |
| 305 | Descriptor 137/138: flat 2970/2971 | Descriptor 141/142: flat 2979/2980 |

The twelve-byte descriptors start at `0x80090B60`; their flat-index pointers,
CI8 format and 32 × 64 dimensions match the model draws. The constructor
copies twenty bytes of binding data to object `+0x170`. A caller comparison
at `0x151C7898` supplies the branch argument; it is not a fixed default.
Supporting these models requires explicit constructor variants and complete
renderer/callback guards. Table matches alone do not enable an export.

Bounded ROM-verified source blocks, descriptors and branch alternatives are
recorded in
`build/assets/models/reference/expansion-20260910-usage-budget/constructors/callback-304-305-frontier.json`.
This is a research frontier, not an enabled texture binding or native appearance
claim.
