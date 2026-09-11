# ROM character position morphs

Indexed bank `0x13` stores 23 shape endpoints for two bank-01 character models.
`model-assets extract --bank 01` writes their decoded positions to
`character-morphs.json`. ROM-default glTF exports include the same endpoints as
Blender shape keys, alongside the existing rigid skeleton and animation Actions.
All default morph weights remain zero.

## Native mapping and layout

`func_1517AD00` selects an eight-byte record at `0x800A7230` using the model ID
returned by `func_150849A0`. Each selector holds a model byte, shape-count byte
and three big-endian vertex counts:

| Bank-13 entry | Bank-01 model | Shapes | Part vertex counts | First vertices |
| --- | --- | ---: | --- | --- |
| 0 | 0000 (Conker) | 16 | 337, 12, 12 | 496, 833, 901 |
| 1 | 0058 | 7 | 109, 25, 24 | 199, 308, 333 |

`func_1503CF20` exposes the model's first header pair as the vertex-boundary
table at `D_800C4020[model]`; its size divided by four becomes
`D_800C4310[model]`. The outer bank-13 record contains three part tables. Each
part table has one compressed child per shape. `func_1517AD00` loads the path
`[0x13, selector, part, shape]` at `0x1517B1F8` and `0x1517B274` for current
and previous endpoints.

Each decompressed leaf is an array of signed big-endian XYZ halfwords, followed
by zero padding to sixteen bytes. Complete table boundaries, flags, padding,
part ranges and shape counts are checked. Shape zero equals the original model
positions for all six part ranges. The 69 leaves reconstruct all 41,792 decoded
bytes exactly. The extractor verifies full native consumer spans and the exact
selector table against the validated US ROM.

At `0x1517B398..0x1517B45C`, the native loop reads two six-byte XYZ records,
calculates `previous + (current - previous) * fraction`, truncates each result
to an integer, and writes XYZ into the selected sixteen-byte vertex buffer.
It leaves the other vertex fields unchanged. `func_1502BD84` passes the actor's
shape and transition-duration bytes to this consumer; no expression names or
fixed timeline are inferred from these numeric endpoints.

## ROM expression presets

Bank `0x11` contains 258 ten-byte expression presets in 22 of its 186 default
bundles, including 90 presets for Conker and seven for model 0058.
`model-assets extract --bank 01` writes these to `character-expressions.json`.
All 2,580 expression bytes reconstruct exactly, including the reserved byte.
`model-assets verify --bank 01` checks the inventory and three full native
consumer hashes against the validated ROM.

`func_1507E908` selects the optional second segment using a ten-byte stride.
`func_1507E5C8` consumes the fields as follows:

| Byte offset | Native use |
| --- | --- |
| 0, 1 | Blink selectors plus ten, stored as bytes at actor `0x6C/0x6D` |
| 2 | Morph shape stored at actor `0x134` |
| 3 | Morph transition duration at `0x135`, when the shape changes and the caller supplies no override |
| 4 | Indirect animation selector passed to `func_1507EA44` |
| 5 | Preserved; this consumer does not read it |
| 6–7 | Big-endian raw animation-duration parameter |
| 8, 9 | Texture descriptor overrides at actor `0x68/0x69`; zero restores the corresponding default |

`func_1507EA44` resolves a nonzero animation selector through a separate byte
table before starting an action program. `func_1507E9F8` exposes the five bytes
at `0x8009D910` only for Conker: selectors 1–5 map to native actions
5, 6, 7, 10 and 11. `func_15083568` indexes eight-byte descriptors at
`0x80086CC4`, then dispatches consecutive sixteen-byte program records.
The five selected descriptors reference six records, including two operations
for action 11. Their 96 bytes and all descriptor bytes are preserved under
`animation_programs`; each preset retains its selector, duration and resolved
`native_action`. The records' dispatch kind is decoded, while operation
parameters remain raw. Both complete consumers are hash-checked.

These programs are not direct clip indices or an authored playback timeline.
Runtime expression triggers and caller duration
overrides remain unresolved. These presets are extracted ROM data, not clips
inferred from save states.

Independent comparison finds preset 67 active in Save-Game-10 and Save-Game-15:
shape 9, duration 22, blink codes 40/40 and descriptor indices 14/14 all agree
with ROM. Other sampled states retain initializer or later runtime values,
including duration 10 for a different preset whose stored duration is five.
This confirms why a selector alone is insufficient to reconstruct a full
runtime appearance. The comparison records both matches and differences in
`reference/expansion-20260910-two-hours/expression-state-comparison.json`.

## Export and comparison boundary

The exporter maps source vertex indices into each glTF primitive and supplies
POSITION deltas under `rom-shape-00`, `rom-shape-01`, and so on. Shape zero is
retained as the all-zero endpoint. glTF weights interpolate floating-point
positions; intermediate values do not reproduce native signed-halfword
truncation. The stored endpoints themselves are exact. UVs, colours, normals,
joints and existing animation channels keep their original data.

Morph keys are included only with `preview --bank 01 --rom-defaults`. Captured
pose exports retain their separate geometry contract. Neither the morph loader
nor ROM-default preview generation reads a save state or trace.

For independent comparison, nine existing save states contain Conker's neutral
or shape-9 endpoint. Both native vertex buffers in each state agree with all
361 positions across the three corresponding ROM parts: 6,498 compared XYZ
records, zero mismatches. RDRAM byte order and offset were checked using three
exact ROM data anchors per state. The local results are in
`reference/expansion-20260910-two-hours/morph-state-endpoint-comparison.json`.
Two bounded execution probes did not reach the interpolation breakpoint; they
are negative traces, not evidence of live intermediate interpolation.

The batch validator compares every exported morph corner against fresh ROM
data, checks provenance and neutral weights, and imports the files in Blender
to verify key names, counts and finite positions. A deliberate changed delta
is rejected by the test suite. Conker's rendered expressions are coherent.
Model 0058's winged-imp geometry becomes coherent after the independently
proven [primary draw-table selection](us_character_draw_tables.md); it also
exports all seven ROM shape endpoints.
