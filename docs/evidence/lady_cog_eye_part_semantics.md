# Lady Cog eye-part selection

`func_1507E3C0` has role `actor_update_lady_cog_eye_parts`; its excluded
`CURRENT (757)` candidate and raw fallback stay intact.

## Exact model gate and mask

The full registered US span is `0x1507E3C0..0x1507E500` (320 bytes), read from
normalized ROM SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`:

- SHA-1: `eb9bcf2cd630cf7c6dde5111e846ebb8934d575d`
- SHA-256: `22d8b389d5a312d7c34462b8ba052b10e9d18debaab74c454a9573b3b71d5b3c`

The `lbu` at `0x1507E3C4` reads actor `+0x04`. Comparisons at
`0x1507E3D0`, `0x1507E3DC` and `0x1507E3E4` admit exactly model indices
15 (`0x0F`), 70 (`0x46`) and 76 (`0x4C`); all other byte values return without
changing the actor. The [reviewed gallery identities](us_gallery_character_names.md)
identify these bank-01, segment-0 entries as red, blue and green Lady Cogs.

Two loop iterations read actor bytes `+0x6C` and `+0x6D`. The
[expression contracts](character_expression_semantics.md) establish them as
numeric eye-channel blink/expression codes. A code at least ten is reduced by
ten, then mapped from five to state zero, one to state one, and any other value
to state two. A code below two is incremented; codes two through nine remain
unchanged. The final selection distinguishes zero, one and all other states:

| Actor code | Selected primary part from `+0x6C` | Selected primary part from `+0x6D` |
| --- | ---: | ---: |
| 15 | 3 | 5 |
| 0 or 11 | 4 | 6 |
| All other unsigned-byte codes | 2 | 1 |

The routine first ORs actor `+0x94` with `0x7E`, then clears the two selected
part bits. Part zero and bits outside one through six are preserved.
`func_1502CCFC` reads this mask at `0x1502D214`; its bit test and branch at
`0x1502D21C..0x1502D224` skip a part when that bit is set. Thus clearing a bit
permits that part through this mask gate; other rendering gates still apply.
See [character draw tables](us_character_draw_tables.md).

## Why these are eye parts

Each of the three models has seven primary parts and no secondary parts.
Parts 2/3/4 use only joint matrix 5; parts 1/5/6 use only joint matrix 6.
Every alternative is an eight-face part using flat texture ID 2246. In primary
part zero, the corresponding matrix-5 and matrix-6 surfaces use the two dynamic
eye texture segments 6 and 7. The independent model identities are:

| Entry | Decoded bytes |
| --- | ---: |
| 15 | 8,152 |
| 70 | 8,152 |
| 76 | 8,168 |

The direct caller, `func_1502EEF4`, steps both eye codes and calls the routine
at `0x1502EFF0` with `D_800CC2D0 + actorIndex * 0x32C`. Its complete 296-byte
span has SHA-1 `2da422b7989f9b16b67dc448f60332131031e4f0`. The renderer's
complete 2,128-byte span has SHA-1 `2176c655198fed8b1867b28f059cb4765bced897`.

These links support paired eye-part selection. They do not establish left/right
orientation, open/half/closed labels, eyelid-versus-eyelash anatomy, playback
timing, or a scene-specific live actor. Earlier defaults notes calling these
models flowers are superseded by the reviewed gallery identities.

The original-word interpreter checked every byte-code pair on model 15 and
all 256 model IDs with 75 mask/code combinations each. This supports the gate
and part selection, not timing or a fresh C comparison. The terminal
`1507EB4C` padding discrepancy in the [expression audit](character_expression_semantics.md) must not be concealed by boundary or
comparator changes.
