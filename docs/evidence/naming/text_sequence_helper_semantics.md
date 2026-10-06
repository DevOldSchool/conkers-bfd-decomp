# Text sequences and special-glyph metadata

Sources: `game_FD1D0.c` and `game_6EA90.c`. Common allocators, render
callbacks and buffer updaters remain raw/deferred.

| Symbol | C name | Span |
| --- | --- | --- |
| `150415E0` | `text_get_special_glyph_metadata` | `0x1CC` |
| `150CFD5C` | `text_sequence_find_terminator` | `0x28` |
| `150CFD84` | `text_sequence_measure_segment_bytes` | `0x34` |
| `150D00C0` | `text_sequence_handle_event` | `0x74` |
| `150D0134` | `text_sequence_create_centered_crossfade` | `0x6C` |
| `150D02B4` | `text_sequence_create_typewriter` | `0x78` |
| `150D04C4` | `text_sequence_create_left_crossfade` | `0x70` |

## Byte-oriented sequence helpers

The full-sequence terminator is NUL. Its finder returns that byte's address,
including the input pointer for an empty sequence. Original caller `150CFDD0`
uses it in the maximum-segment-length scan.

The segment helper calls `150CFD20`, which stops at 0xBD or NUL. It stores the
stop address through its second argument and returns stop minus start, without
consuming the delimiter. This is a byte count, not glyph count or pixel width.
Original calls are `150CFDF0`, `150CFECC` and `150CFF58`. The existing s32
address/result interface is retained; no pointer-width, bounds or validation
change is introduced.

## Event routing

For event code 0x51, the handler compares payload byte zero with the object's
sequence key at +0x28 and delegates to `150CFE98` only on equality. That raw
helper tests the cursor byte for nonzero, advances one byte, measures the next
segment, switches the double-buffer page and marks the change. The established
scanner contract makes that nonzero stop byte 0xBD; it is not revalidated. Other event codes select
`D_800888B0[object byte +0x4D]` and invoke a non-null callback. No selector-bounds
check is added. The three constructors below use secondary selector zero,
whose original table entry is null.

Initialized-data slot `8008A9F4 = 8008A8D8 + 0x47*4` selects this event handler.
Original dispatcher `15149434` indexes by object +0x13; the constructor chain
`150CFF10 -> 15149130` supplies kind 0x47. These are registered callbacks,
not proof that a particular sequence or event is activated in gameplay.

## Three concrete presentation styles

All three wrappers call `150CFF10` with eight auxiliary-state bytes and primary
selectors 0, 1 and 2, forwarding the remaining creation arguments unchanged.
They initialize auxiliary state only if allocation succeeds. The two crossfade
wrappers copy one zero byte. The typewriter wrapper sets a float and halfword
to zero, then copies its eight-byte packet; padding is not explicitly cleared.
The sparse initialization, temporary layouts and silent failure behavior remain.

Original primary callback table `800888A0[0..2]` contains `150D01A0`,
`150D032C` and `150D0534`; `150D0034` selects these using object +0x4C.
Their full original bodies establish the styles:

- Centered crossfade: current/previous buffers use countdown 8 with alpha
  weight (count*31)&255 and its 255 complement. It queues at (146,190), flags 0x81,
  with RGB (206,196,97)
- Typewriter: a growing byte prefix follows literal `C:> `, then bytes 0x20,
  0xBB and NUL. It queues at (15,190), flags 0x80, with RGBA (0,255,0,150).
  Its original rate/accumulator and visible-byte counter remain unchanged
- Left crossfade: current/previous buffers use countdown 20 with alpha
  weight (count*12)&255 and its 255 complement. It queues at (20,20), flags 0x80,
  with RGB (255,255,255)

The alignment names are independently supported by `15043384`: after clearing
bit 0x80, flag value one subtracts half the scaled text width at
`150435B4..150435C8`; zero leaves X unadjusted. No subtitle, terminal, speaker,
chapter or character identity is inferred. Queued color/alpha values are not
claims about final rendered pixels.

Original constructor calls at `150279B0`, `150279F4` and `15027A6C` retrieve
text through `D_800C35E0` using a command string index and pass its low byte as
the sequence key. No wider key range or ownership relationship is inferred.

## Special-glyph layout metadata

`150415E0` accepts a signed selector and five output pointers. Within
0xA8..0xFF it writes base layout width, height, vertical adjustment, render flag
and scale. The outputs for explicitly handled selectors are:

| Selector | Width | Height | Vertical adjustment | Flag | Scale |
| --- | ---: | ---: | ---: | ---: | ---: |
| A8..A9 | 32 | 18 | 3.1 | 1 | 1.0 |
| AA..AD | 32 | 27 | 2.0 | 1 | 0.603 |
| AE | 16 | 17 | -1.6 | 1 | 1.0 |
| AF..B0 | 46 | 16 | 2.0 | 1 | 1.0 |
| B1 | 38 | 24 | 2.0 | 1 | 0.726 |
| B6..B9 | 16 | 12 | 2.0 | 0 | 1.0 |
| BA | 55 | 12 | 0.2 | 0 | 1.0 |
| Other in-range | 12 | 16 | 2.0 | 0 | 1.0 |

Outside that range it zeros only width, height and vertical adjustment, leaving
flag and scale untouched. There are no pointer checks. The alias changes no
parameter names, types, stores or partial-output behavior.

The two original direct calls are renderer `15041F4C` and measurement
`150429E0`. Both pass the low-byte result of `15042C40`, not a font-record
index. Measurement truncates the accumulated width plus width times scale;
its extent candidate is trunc(trunc(height * scale) - vertical adjustment) + 1.
The renderer
subtracts vertical adjustment from draw Y; flag zero emits a specific combiner
override, while nonzero skips it. No baseline, bitmap-size or named color-mode
meaning is inferred. Higher input bytes can map to ordinary font records, so
this helper's accepted range is not a character-encoding classification.

The complete 6,000-byte original glyph family and the switch/float payload at
`80098AB0..80098B0F` were checked against the US ROM. Existing format and caller
evidence is in [glyph rodata](../game_6ea90_glyph_rodata.md) and
[font atlas](../us_font_atlas.md). Raw renderer, measurement and lookup functions
remain unchanged and unmatched.

## Full-span evidence

All 1,008 registered target bytes agree with the checksum-validated US ROM.
The entire original `reference/game/us/asm/CFD20.s` family, callback tables,
timer dispatch, callers, glyph renderer and layout renderer were independently
checked. The pinned SDK's FA/RGBA packing supports the color roles; glyph code
packs those arguments at `15041888..150418BC`, and layout code forwards node
color bytes at `15043658..150436AC`.
