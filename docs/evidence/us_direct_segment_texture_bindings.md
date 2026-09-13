# US direct pixel-segment bindings

Bank-09 entries 186, 153, 141 and 147 have complete stored-geometry texture
coverage through reviewed runtime pixel and palette bindings. The exporter retains all texture
alternatives and displays explicit inspection presets. Seven resolved material
runs cover 25 faces; geometry, UVs and existing texture decoders are unchanged.

All inputs come from normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Captures and save states are not
extraction inputs.

## Four-digit timer: entry 186

Initializer `15093878` passes literal 186 to `1518C900` and saves the returned
primary display-list pointer at `800D2448`. The loader selects bank 09, parses
its list through `1510CE60` and relocates model-relative vertices through
`15168E54` / `15168E34`. The existing direct-model byte-reconstruction gate
checks that loader and relocation contract.

Renderer `150938BC` reads the signed timer word at `800D2450`. For a
nonnegative value, it divides by 30 to obtain seconds and then binds four
images, from segment 4 down to segment 1:

| Segment | Digit | ROM flat asset |
| ---: | --- | --- |
| 4 | Seconds units | `4525 + (seconds % 10)` |
| 3 | Seconds tens | `4525 + ((seconds % 60) / 10)` |
| 2 | Minutes units | `4525 + ((seconds / 60) % 10)` |
| 1 | Minutes tens | `4525 + ((seconds / 600) % 10)` |

Divisions in this table truncate. The loop discards higher minute digits.
Negative or non-integer inspection inputs are rejected. The default preset
uses zero ticks and displays **00:00**; this is not an inferred initial or
current gameplay time. All ten glyphs, flats 4525–4534, remain in the material
evidence and must decode successfully.

Each flat is a 256-byte, 16 x 32 IA4 image. The model's own commands establish
its combiner, lookup mode, texture load and tile layout. No ordinary-object
segment-8 consensus is applied to this direct renderer.

After installing the four pixel segments, `150A7D00` writes a translation
matrix into the separately allocated matrix buffer. It does not modify the
display list or digit bindings. The renderer loads that matrix and submits
the stored model pointer at `15093B24`. The caller `1508FD38` invokes it only
on the enabled timer branch; visibility and screen projection remain outside
the standalone inspection preset.

`scripts/model_timer_texture_bindings.py` checks seven complete function spans
and 21 literal, loop, binding and submission instructions. The timer formula
is tested at second/minute transitions and at the four-digit wrap boundary.

## Animated attachment: entry 153

Action 26's header at `80086D8C` selects the single sixteen-byte record at
`8009D2F0`: `99120f02000016000000000000000000`. This means model 153,
updater 15 and kind 2, with animation selector 22. The action header, complete
record, updater word at `800841FC` and two texture words at `800902FC` are
checked exactly.

The shared attachment constructor `15030AF4` initializes the texture fields
`+0x18/+0x1A` and counters `+0x38/+0x3C` to zero. Model 153 takes the no-op
initializer arm in `15031A50`. Its descriptor `+0x17 = 22` routes `1502FFD8`
through `1503F62C`, which loads the same bank-09 model through `1502FE10` and
allocates separate animation state and matrix buffers.

Updater `150337E4`, selected by dispatch index 15, adds the frame delta to
counter `+0x38`. At 16 it clears that counter and toggles `+0x3C` with XOR 1.
It stores `800902FC[+0x3C]` into texture field `+0x18`. The two entries are
flats 1545 and 1546, both 4,096-byte, 32 x 32 RGBA32 images. The preset uses
the constructor's zero counters and update delta 1, selecting flat 1545.
Both frames are retained; the standalone glTF preserves the stored neutral
joint hierarchy rather than claiming native attachment animation playback.

`150311C4` loads the selected flat through `1510D0EC` and binds segment 6
immediately before submission. The additional animated renderer `15035D6C`
changes segments 3 and 8, then submits the same descriptor's model lists.
It preserves segment 6. Its opacity and part-visibility branches remain
separate appearance state. Five additional whole-function pins supplement
the shared attachment consumer proof.

The inspection label **Unused military laptop — first screen frame** is based
on the supplied unused-content reference, checked against the ROM keyboard
(flat 1543), screen surround (1544) and message texture (1545). The latter reads
“LOOK SAD PEOPLE GET A LIFE NOW”. The matching attachment record is also
identified tentatively as an unused army laptop in the
[mkst/conker research notes](https://github.com/mkst/conker/wiki/Research).
The gallery uses camera rotation `[180, 0, 0]` in Blender world axes so the
screen and keyboard face the viewer upright. Only the camera and lights rotate;
the GLB retains the stored attachment orientation. `model-assets inspect`
caches this presentation thumbnail by source dependencies, camera settings,
renderer code and Blender binary, separately from regression/native evidence.
Parent identity,
a recovered source name and absence from every runtime path remain unproven.

The supplied walkie-talkie reference also identifies bank-09 entry 150: its
restoration code selects model `0x96`, matching decimal 150, and its green body
and long antenna match the exported geometry. Its gallery label is
**Walkie-talkie**. This is reference-based semantic naming, not new evidence for
extraction, runtime reachability or native appearance. Both exports remain
ROM-only. Naming comparison evidence is retained locally under
`build/assets/models/reference/asset-name-corrections-20260913/` and
`build/assets/models/reference/laptop-identification-20260913/`.

## Indexed animated attachments: entries 141 and 147

The same kind-2 loader and renderer preserve the inline-palette segment-6
binding for two updater-5 attachments. Each preset guards the complete action
header and record, updater dispatch, texture table and indirect branch targets.
The updater `15031FC8` is pinned for its full 4,592 bytes.

Entry 141 uses action 172: header `8008721C`, record `8009D060`, model 141,
updater 5, kind 2 and animation selector 7. Initializer `15031A50` uses slot 11
at `80096F6C` to enter `15031BA8`. It calls `150859AC(0, 6)`, which reads the
signed progress word at `800D2148` through jump slot `8009D9B8 -> 15085A9C`.
This is a progress read, not random selection. Values below 100 select flat
7181 from `80090228`; other values select 7182 from `8009022C`.
Both are 2,080-byte CI4 payloads: 64 x 64 pixels followed by a 32-byte palette.

The explicit entry-141 preset uses progress zero, parent type zero, parent
state `+0x84 = 0`, non-null attachment animation `+0x48` and a null parent
animation pointer `+0x2D0`. The updater skips the parent-type jump table, then
uses model slot `80097240 -> 15032578`. State zero takes the animation-zero
branch, preserving the initializer's texture. The rendered label **Gold pocket
watch — stored parts** describes the visible model; the stored neutral joints
do not claim assembled gameplay placement.

Entry 147 uses action 70: header `80086EEC`, record `8009D140`, model 147,
updater 5, kind 2 and animation selector 16. Its initializer is a no-op. The
explicit parent-type-90 preset uses slot `800970E8 -> 150320B4`. A zero parent
field `+0x2E8` stores flat 3791 from `800902D0` into descriptor `+0x18`; a
nonzero field selects flat 3792 from `800902D4`. Both are 1,536-byte CI8
payloads: 64 x 16 pixels followed by a 512-byte palette. Parent state zero uses
slot `8009716C -> 15032150` and the animation-5 branch. The inspection label
**Black weapon attachment** is descriptive; its owner and exact weapon name
remain unproven.

On both reviewed paths, `1503F5B8` receives the separate attachment animation
allocation. A null parent animation pointer skips the later parent-animation
copy path. Neither path changes descriptor palette offset `+0x1A = 0` or the
selected texture. The renderer's fifth argument is zero. All retained texture
alternatives pass the existing inline-palette decoder. These are explicit
inspection states; action records alone do not prove parent ownership or that
the selected complete state is reachable in gameplay.

## Shared decoder and validation

`rom_direct_binding_preview_texture` accepts only a proven runtime pixel
segment at offset zero, without a palette or external pointer. It maps each
retained flat asset through the existing direct-texture decoder, requires
the exact payload size and image layout, and checks the selected index against
the selected flat. Every alternative must decode before any is accepted.
Missing state, partial payloads and incompatible formats remain unresolved.

The manifest and glTF retain the full binding evidence. Batch validation
reloads the ROM context and rejects forged selectors. The direct-renderer
context is explicitly excluded from ordinary-object segment-8 fallback.

Fifteen focused tests pass across the timer, animated bindings and affected
attachment tests. Unchanged suites are reused. Independent checks cover all
four models' geometry and sixteen images: **17,408 pixels**, including IA4
intensity/alpha expansion, RGBA32 byte order, CI4/CI8 palette lookup, odd-row
word swaps and vertical orientation. Palette expansion uses the reversible
PNG convention `floor(channel5 * 255 / 31)`. Mutations in 24 distinct consumer
spans and sixteen action/data spans are rejected, together with four forged
exported selectors.

The local reproduction scripts, source snapshots, file-access audit and
packed-file checks are in
`build/assets/models/reference/timer-model-20260912/`. See the
[asset roadmap](../asset-roadmap.md) for current gallery and validation totals.

Attachment 80's paired texture and UV-origin update is proved separately in
[attachment UV updates](us_attachment_uv_updates.md). Four runtime-segment
blockers remain: bank 04 entry 59/segment 23, and bank 09 attachments 47, 165
and 185. Their inherited segment bindings still need consumer evidence.
