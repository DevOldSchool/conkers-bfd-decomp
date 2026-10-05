# Actor resource controller helper semantics

Seven already-matched functions in `src/game/game_AD9B0.c` receive local
aliases with their numeric linker symbols preserved. Names describe the
request bytes, resources and controller established by original US
`reference/game/us/asm/80500.s`; they do not identify a character, dialogue,
cutscene, animation or particular resource content. The existing
[source-unit audit](game_raw_periodic_actor_resource_groups.md) establishes
the shared state and boundaries independently of these aliases.

| Numeric symbol | Alias | Registered bytes |
| --- | --- | ---: |
| `func_15080500` | `actor_resource_request` | 288 |
| `func_15080620` | `actor_resource_set_persistent_request` | 136 |
| `func_150806A8` | `actor_resource_clear_transient_requests` | 112 |
| `func_15080718` | `actor_resource_request_bit_location` | 32 |
| `func_15080738` | `actor_resource_request_flag_is_set` | 76 |
| `func_150807F4` | `actor_resource_controller_handle_event` | 52 |
| `func_15080C64` | `actor_resource_controller_poll_completion` | 144 |

## Request storage and bitsets

Original `15080500..1508061C` checks actor, actor word +0 and actor byte
+0x127 != 255. Requests 0x2B/0x2C save the original request and context in
`D_800D1940/D_800D199C`, then use 0x2A for the actor request. Other requests
whose `D_800BE580` bit is set save the original request in `D_800D1940` and
use 0x1A when the corresponding `D_800D2E60` bit is clear. These two bitsets
have different roles; the alias for `15080738` means only testing the former
set. It does not claim that a request is unlocked, completed or playable.

The resolved request is stored at actor->(+0x31C)+0x74 for selector zero,
or +0x75 for nonzero selector, only when that byte's high bit is clear.
The second path also stores `(context - D_800D3098) / 52` as a byte at
+0x7A. The global writes occur before the high-bit check and may therefore
occur even when the actor byte cannot be replaced. No allocation or load is
performed by this helper. The raw caller at `150A1BFC..150A1C14` in
`A09D0.s` passes an actor, record context, nonzero selector and request byte.

`15080620..150806A4` accesses those same nested fields via the actor table
with stride 0x32C. It stores zero for zero request; otherwise it ORs 0x80
before narrowing to a byte. The fourth argument remains unused.
`150806A8..15080714` clears only nonzero requests whose high bit is clear.
Thus persistent/transient describe this pair's preservation rule, not a
promise of indefinite persistence or a particular gameplay mode. The
existing lack of index/nested-pointer checks and byte narrowing are retained.

`15080718..15080734` writes `1 << (id & 7)` to the second output and
arithmetic `id >> 3` to the first; their order is retained. `15080738`
uses them to return 0/1 for the `D_800BE580` byte/mask test. Another original
caller, `55E50.s` at `1506055C..15060578`, also substitutes request 0x1A
when that bit is set under its own guards. No stronger category is needed.

## Event and completion lifecycle

Raw loader `15080828` consumes `D_800D1940`, stores the loaded resource at
`D_800D1944`, and establishes the list pointer/index/count at
`D_800D1998/D_800D1994/D_800D1995`. At `15080B70..15080BD4` it explicitly
passes `150807F4` as the callback to `1516A7B0` and stores the returned
controller at `D_800D1950`; it also sets active byte `D_800D1941` to one.
This direct callback reference requires no inferred callback-table mapping.

`150807F4..15080824` ignores its first two parameters and calls raw
`15080784` only for event 0x20. That raw helper consumes at most one
halfword list element, dispatches nonzero elements through `1001263C`, and
advances the byte index even for zero elements. The alias intentionally
stops at the event-adapter role without assigning a meaning to the list IDs.

`15080C64..15080CF0` returns without action unless active is nonzero and
controller byte +0x15 is zero. It then calls raw cleanup `15080BE8`, which
clears active, releases the controller and its owned buffers, and invokes
the existing final hook. The poller subsequently sets bit 0x10 in byte 8
of `D_800D2E60` except for numeric scene values 0x29/0x2E. If context
`D_800D199C` is nonnull it sets context byte +0x14 to one and clears the
global context pointer. These side effects remain part of the completion
poll, without inferred scene identities. Original `4A730.s` at `1504AD7C`
calls the poller in the actor update path.

`15080CF4..15080D1C`, including its trailing alignment words, returns only
whether active is zero. It remains numeric: its focused gate on the unchanged
pre-batch source reports CURRENT (100), missing the last zero word of the
44-byte registered span after unrelated assembly members are stripped.
Changing tooling or shortening that span is outside this naming batch.
The function does not inspect the controller or run cleanup.
Original `63390.s` at `15069784` starts the raw loader; its subsequent state
path at `150697B0` queries inactivity before proceeding. This supports the
lifecycle distinction between a passive query and the cleanup poller.

## Scope and validation

The seven renamed registered spans total 840 bytes. Only aliases and same-file
references change. Types, signatures, pointer assumptions, control flow,
operations and numeric linkage are unchanged. Full-span US CURRENT (0),
source-unit layout, clean batch, metadata/progress/whitespace, RSP and
byte-identical main/game images gate the batch. Loader, list consumer and
cleanup bodies remain unmatched assembly; no new match or boundary is added.
