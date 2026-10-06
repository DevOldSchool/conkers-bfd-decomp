# Palette RGB and computed graphics colors

Source: `game_16EE20.c`. The RGBA helpers compute components; neither emits a
command.

| Symbol | C name | Span |
| --- | --- | --- |
| `151429E0` | `color_pick_random_palette_rgb` | `0x7C` |
| `151441A4` | `gfx_compute_primitive_rgba_by_mode` | `0x158` |
| `151442FC` | `gfx_compute_environment_rgba_by_mode` | `0x1E0` |

## Four-choice RGB palette rows

The selector reads `D_8008A160 + paletteIndex*12 + (RNG & 3)*3` and copies
three ordered bytes to the output pointers. It adds no index, pointer or
uniform-randomness guarantee. Inspected rows 0..8 occupy 108 bytes at initialized
game-data offset 0x7640, SHA-1 `8f63065b8a6df9421b55e4a1083335ba3b5219ba`.
This inspected range is not a claim of bounds validation or a complete table extent.

RGB semantics follow the original consumer chain. `150B2570` supplies packet
+0x20/+0x21/+0x22 and +0x24/+0x25/+0x26 as outputs and separately sets their
alpha bytes. `15156190` copies these into object color bytes at +0x64..0x67,
+0x74..0x77 and +0x84..0x87. `151564F8` copies the corresponding three 16-byte
vertices, requests clearing geometry bits including G_LIGHTING, emits vertex
command 0x01003006, then draws a triangle. The pinned SDK's vertex layout and
F3DEX2 encoding establish color channels rather than normal components. No
palette-row character, effect or material identity is inferred.

## Primitive and environment consumers

Original caller `151582C8` calls `151441A4` at `151583A4`, then passes its
four outputs in RGBA order to `15142CF0` at `15158460`. It calls `151442FC`
at `15158408` and passes those outputs to `15142C10` at `1515842C`.
Caller `1515BBF0` independently repeats both relationships.

The original writers emit FA/G_SETPRIMCOLOR and FB/G_SETENVCOLOR respectively,
packing RGBA into bits 31..24, 23..16, 15..8 and 7..0. This establishes the
component helpers' roles without assigning meanings to their custom selectors.

## Numeric selector contracts

For notation only, A denotes args4..7, B args8..11, t arg12 and mode arg13.
The four outputs are s16 values in RGBA order. Primitive arg7 is an ignored
s32 and remains so; its width is not changed to match the other byte arguments.
Products below use the original right shift by eight, not division by 255:
255*255 becomes 254. Duplicate cases and sequential stores remain unchanged.

| Primitive mode | Output RGBA |
| --- | --- |
| 0 | (0,0,0,0) |
| 1 | (0,0,0,B.a) |
| 2 | B |
| 3, 4, default | (A.r*t>>8, A.g*t>>8, A.b*t>>8, 0) |

| Environment mode | Output RGBA |
| --- | --- |
| 0 | (0,0,0,0) |
| 1 | (t,t,t,0) |
| 2, 3 | A |
| 4, 5, default | (t,t,t,A.a*B.a>>8) |
| 6 | (A.r,A.g,A.b,B.a) |
| 7, 12 | (0,0,0,B.a) |
| 8 | (0,0,0,A.a) |
| 9 | (t,t,t,B.a) |
| 10 | B |
| 11 | (B.r,B.g,B.b,A.a) |
| 13 | (A.r,A.g,A.b,0) |

Original selector tables at `800A5648` (20 bytes) and `800A565C` (56 bytes)
confirm these paths. The selectors remain numeric; they are not promoted to
named RDP combiner/render modes or unproved material categories.

## Full-span evidence

All 948 registered bytes in `reference/game/us/asm/141970.s` agree with the
checksum-validated US game image. Supporting writers, particle consumers and
both RGBA callers were independently checked against their full original
spans. Bounded direct-call counts are 13/8/8 in table order, not exhaustive
indirect coverage. The inspected SDK gitlink and HEAD are
`87af1e4d8ed666f2ad407dc11c6e47736094f2f8`; `include/PR/gbi.h` has SHA-1
`759ed335ced92c9877fcf7f370d14a39b37796c0`. Nearby raw command emitters remain
outside this naming batch.
