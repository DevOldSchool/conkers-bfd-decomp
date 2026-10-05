# Viewport fade and tint helper semantics

These six existing matched functions in `src/game/game_1AC2F0.c` receive
source-local aliases. Original numeric linkage, signatures, operations and
registered spans remain unchanged. The primary evidence is original US
`reference/game/us/asm/17EE40.s`, including the still-unmatched callees.
Deferred C reconstructions are not used to establish semantics.

| Numeric symbol | Alias | Registered bytes |
| --- | --- | ---: |
| `func_1517EE40` | `viewport_fade_request` | 192 |
| `func_1517EFAC` | `viewport_fade_is_opaque` | 48 |
| `func_1517F3A0` | `viewport_fade_draw` | 108 |
| `func_1517F40C` | `viewport_fade_timer_finished` | 60 |
| `func_1517F448` | `viewport_fade_advance_timer` | 64 |
| `func_1517F4D8` | `viewport_tint_draw_if_active` | 140 |

## Fade state and timing

`1517EE40..1517EEFC` indexes per-viewport RGB bytes at `D_800DDDA0`,
signed mode bytes at `D_800DDDAC`, elapsed words at `D_800DDDB0`, duration
words at `D_800DDE28` and override bytes at `D_800DDDC0`. It accepts a
request only when the mode differs, elapsed is below duration, or override
is nonzero. An accepted request stores RGB and duration, clears elapsed and
override, and stores the mode. A repeated, already-complete request with the
same mode and no override does nothing, even if its RGB or duration differ.
The name therefore says request rather than promising an unconditional start.

Original `1517EF00..1517EFA8` establishes the fade interpretation. A nonzero
override byte is returned directly. Otherwise it computes signed
`elapsed * 255 / duration`, caps results above 255, and uses 255 for zero
duration. Mode zero returns `255 - result`; other modes return the result.
For ordinary nonnegative timing this gives decreasing or increasing opacity.
The original arithmetic, absence of a lower clamp, unchecked viewport index
and signed mode remain unchanged; no physical timing unit is inferred.

`1517EFAC..1517EFD8` returns whether that raw alpha result is exactly 255.
It neither compares the timer nor proves anything about the final composed
screen. `1517F40C..1517F444` instead tests signed elapsed >= duration.
`1517F448..1517F484` adds `D_800BE9E4` only when elapsed != duration;
it does not clamp and can advance again after overshoot if called directly.
Original `186D0.s`, `15018FD4..15018FF4`, calls the completion query first
and advances only when unfinished and `D_800BEAC0` is zero. This caller
guard is separate from the helper's own behavior.

## Drawing and the independent tint layer

`1517F3A0..1517F408` reads fade alpha through `1517EF00`, returns the input
display-list cursor for zero, and otherwise passes the viewport RGB and
alpha to `1517F08C`. That raw callee emits primitive RGBA (`0xFA`) and a
rectangle command (`0xF6`) using viewport bounds at offsets `0x24..0x30`
in the `D_800BE628` records of stride `0x180`. The command identities agree
with `G_SETPRIMCOLOR` and `G_FILLRECT` in `lib/ultralib/include/PR/gbi.h`.
It packs the low alpha byte; the fade wrapper skips exactly zero, not all
nonpositive values.

`1517F4D8..1517F560` draws a separate constant-color layer through the same
rectangle callee only when both the unsigned duration at `D_800DDE10` and
alpha byte at `D_800DDD9C` are nonzero. RGB comes from `D_800DDD90`.
Original setter `1517F488..1517F4D4` supplies these fields; original
`1517F75C..1517F7B0` decrements their per-viewport durations by the tick
increment and saturates at zero. This supports a timed tint without
assigning a particular damage, scene or weather meaning.

Original `186D0.s`, `15019C30..15019C44`, chains tint drawing and fade
drawing for the same viewport, passing each returned display-list cursor
onward. The original transition controller in `172C50.s` requests black
fades and polls the elapsed-time query, independently supporting the control
role without requiring names for its higher-level actions.

## Scope and validation

The six spans total 612 bytes. Full-span US CURRENT (0), source-unit layout,
clean batch verification, progress, whitespace, RSP, and byte-identical US
main and integrated game images gate the aliases. No new match or source
boundary is claimed. Unmatched alpha, rectangle, tint setter and timer
implementations retain numeric identities. The mixed all-viewport query
`1517EFDC`, which also reads a separate float effect, remains numeric until
that second condition is understood.
