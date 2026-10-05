# Actor initialization and animation-sequence helpers

Five existing matched helpers use source-local aliases, preserving numeric
symbols, original types, operations and complete spans. Names describe actor
and animation mechanics, without character, model or scene identity claims.

| Symbol | C name | Source | Bytes |
| --- | --- | --- | ---: |
| `15004F00` | `actor_attachments_clear_list_head` | `game_323B0.c` | 16 |
| `150162B0` | `actor_pool_initialize` | `game_43760.c` | 192 |
| `1505841C` | `actor_update_animation_playback_rate` | `game_83300.c` | 468 |
| `1505D2B8` | `actor_apply_motion_preset_and_begin_animation_sequence` | `game_83300.c` | 148 |
| `1505E7CC` | `actor_find_animation_sequence_index` | `game_83300.c` | 168 |

## Pool and attachment root

Pool initialization clears 0x4F4C bytes at `D_800CC2D0`, exactly 25 records of
stride 0x32C, also corroborated by original allocator `1505ED34`. It zeros
`D_80086000`, `D_800CC2B0` and `D_800D18D0`, clears 0x18 bytes at `D_800CC298`,
sets `D_800CC2A2` to one, and maps `D_800D2138` values 2/3/4 directly to
`D_800CC26E`, otherwise zero. Ancillary globals retain neutral names. This
does not individually set actor model sentinels or free old allocations.
Original caller is `15007D74`; the three final NOPs remain in the span.

The attachment helper only zeros `D_800C3EE0`. Original constructor `15030AF4`
links descriptor +0x54/+0x58 and installs that head, while copying actor+0x3B
to descriptor+0. Existing attachment queries traverse it. Original caller
`15007DD8` invokes the reset. It does not traverse, detach, free or clear
individual descriptors; see [actor utility evidence](actor_utility_helper_semantics.md).

## Playback-rate update

The helper's calculated float is passed to `1505E650` at `15058550/1505856C`,
forwarded to `1505E0C4`, then stored at animation-state+0x10 at
`1505E38C/1505E5D0`. Original `1507BDB0` reads that field at `1507BE50`,
multiplies it by time delta and advances animation time +8. This establishes
playback rate independently of tentative source field names.

The calculation uses packed bytes +0x246/+0x249, motion magnitude +0x3C and
scale +0x14C, retaining all existing overrides. It also requests the animation
at actor+0x244, including when the requested rate is zero. An initial flags
byte +0x246 equal to 0xFF forces rate zero. After the call it re-reads that byte;
if it is 0xFF and the external signed control is nonnegative, it
sets time +8 to state[+0x18]*(32768-control)/32768 without a clamp or null guard.
The control is not assigned a stronger
“fade” meaning, nor is actor+0x1D0 called “pitch” based on existing labels.
Signed-byte-to-float forwarding, guards and unchecked divisions/pointers remain.
Original direct calls are `15056C50` and `15058318`.

## Keyed animation sequences

The lookup reads unsigned model byte +4, obtains `D_800D1588[model]`, then
uses table pointer root-8 and byte length root-4. It searches floor(length/24)
records for first-byte equality with the complete s32 key. Model 0xFF, missing
root/table, zero length and no match return zero; the first matching ordinal
can also be zero. Duplicate keys choose the first; non-byte keys are not
truncated. Model index and record payloads are not validated.

Original bank-0F loader `1503D660` relocates header+8 and stores header+0x10 as
this root. Callers store the ordinal at actor+0x106. Consumer `1505E874` uses
ordinal*24, reads stage selectors at record+0xA+4*stage and rate bytes at
+0xC+4*stage, and calls animation selector `1505E650`. These are up to three
animation stages with ancillary action/control fields, not frame descriptors.
The lookup does not return an animation route ID or play an animation.
See [animation/resource evidence](actor_animation_state_helper_semantics.md).

## Motion preset and pending sequence

The preset helper selects `D_8009A6D8 + u8_index*0x28`, copying preset floats
+0x18 to actor+0x20, +0x14 to actor+0x3C, and +0x1C to actor+0x24. Original
`1505A770` uses +0x24 to decrement +0x20 in time-scaled substeps, then
integrates +0x20 into vertical position +0x18; `15059C84/1505A184` consume
+0x3C as motion magnitude.

It sets actor+0x104 to 0xFE and +0x105 to zero, resolves the separate pending
selector actor[+0x10E]&0x7F into ordinal +0x106, consumes that selector by
writing +0x10E=0xFF, then calls `1505E874`. The preset index does not choose
the animation-sequence key. Original caller `15053488` supplies preset nine
after testing 0<actor[+0x10E]<0xF0. There is no preset-bound or lookup-success
check and no guaranteed successful playback: “begin” denotes state setup and
dispatch, while the consumer can return or clear sequence state. No specific
reaction is named.

## Evidence and acceptance

Original `162B0.s`, `4F00.s`, `7A70.s`, `2FE10.s`, `3CF20.s`, `53430.s`,
`55E50.s`, `6AD30.s` and `7BDB0.s` supply the entry/consumer evidence. All 992
registered bytes require full-span CURRENT (0), existing layout, clean batch,
tests, progress, whitespace, RSP and exact main/game images. Raw/deferred
consumers remain evidence only; no new C match or source-unit completion is
claimed. Existing source field names are preserved without promoting their
unconfirmed semantic labels.
