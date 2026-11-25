# US floating-point data and bounded creation records

This batch reconstructs 224 bytes in two C owners: five rows of eight
creation choices at `8008CF00` (160 bytes) and the eight float pairs at
`80095C64` (64 bytes) that the selected choice reaches. Source grouping does not
infer original C-object boundaries or runtime immutability.

## Scene-selected pairs and creation choices

The ROM-backed scene source contains 65 child-`0A` lists, each with fifteen
four-byte resource choices. All 975 flags are zero and all sprite IDs differ
from the disabled sentinel. The editable sources exactly match these originals.
`1500ABA0` loads bank `0C`, the selected scene and child `0A` into the 60-byte
choice buffer. `1500BEC0` iterates its fifteen entries; `1500AD84` stores the
choice flags with bit seven removed into the byte used as creation-table row.
This original-source path therefore selects row zero.

The native selector masks triangle bits 20..22 to obtain one of eight columns.
At `8008CF00`, the first row contains signed `{ creator, count }` pairs:
`{0,1}`, `{0,2}`, `{4,0}`, `{0,4}`, `{4,1}`, `{0,6}`, `{4,2}`, `{0,8}`.
The callback address at `8008CEB8` maps creator zero to `1500B1F4`.
Variant seven passes count eight. That callback reads two floats at offsets
zero and four, advances the pointer by eight bytes, increments an index and
compares it with the preserved count. This proves eight float pairs at
`80095C64`, retaining the existing `f32[][2]` declaration.

All 7,800 scene/resource/variant combinations are checked. The proof assumes
successful allocation and normal ABI preservation; it does not claim that every
variant occurs during gameplay. The row index comes from the stored choice
flags, so `Game36680CreationChoice[][8]` holds every row up to the next object at
`8008CFA0`: five rows, 160 bytes. Rows one through four use the same signed
pair layout, each ending in a `{0,1}` entry (`{0,3}` follows it in row four).
Only row zero's consumption is traced. The eight float pairs at `80095C64` are
followed by unrelated byte data, so that table is complete at 64 bytes. Eight full native spans authenticate this loader/selector chain.

## Withdrawn scalars

The original batch also defined 104 owners of separately addressed `f32` and
`f64` scalar words. Each was a single function's literal-pool constant,
credited when that function matches, and was withdrawn under the project rule
against reconstructing literal pools as data.

## Build

Owners use INFO verification storage at their native addresses. Runtime data
continues to come from the original GAME archive. There are no pointer
relocations. Explicit `f32` and `s16` symbol annotations prevent pointer
inference. No existing function body, header, assembly or function/source-unit
inventory changes.
