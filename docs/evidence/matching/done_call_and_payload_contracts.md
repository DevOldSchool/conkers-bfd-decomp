# Completed caller and payload contracts (US)

## Object argument to `func_15124B18`

Nine completed callers omitted the object argument and declared this helper
with `(void)` or an unspecified parameter list. Original `func_15124B18`
reads `lh ..., 0x1B4(a0)` at `0x15124B18`, then accesses other fields through
that same incoming pointer. The independent US reference is the function in
`reference/game/us/asm/122AE0.s`. Its incoming `a0` is required input.

Each corrected call now explicitly passes its existing `arg0`, through a
source-local `void func_15124B18(void *)` declaration. This preserves the
pointer already forwarded in the original machine code; it does not rely on
a caller-saved register happening to retain an undeclared argument.

| Caller | Completed source |
| --- | --- |
| `func_15005B10` | `game_32FC0.c` |
| `func_15005D60` | `game_33210.c` |
| `func_15005E30` | `game_332E0.c` |
| `func_15005EE0` | `game_33390.c` |
| `func_15005F20` | `game_333D0.c` |
| `func_15005F60` | `game_33410.c` |
| `func_15006140` | `game_334C0.c` |
| `func_15006170` | `game_33620.c` |
| `func_150CEF10` | `game_FC3C0.c` |

Sources are under `src/done/game/`. The existing call in `func_15006010`
already supplied its pointer; that function shares the updated declaration
and is included in the regression checks. The unchanged empty sibling
`func_15005DA0` is also included. The callee, other translation units and
shared headers are unchanged.

## Contiguous payload in `func_150106D0`

The reference `reference/game/us/asm/106D0.s` stores an object pointer at
`sp+0x38`, a float return value at `sp+0x3C`, an integer return value at
`sp+0x40`, and `0.0f` at `sp+0x44`. At `0x15010758` it passes `sp+0x38` as
the source of a `0x10`-byte copy to the newly allocated object at `+0x28`.
`config/game/us-sdk.ld` identifies the callee `func_10022EC0` as `memcpy`.

The previous C passed the address of a single pointer local and relied on
three independent volatile locals occupying the adjacent copied bytes.
`Game3DB80Payload` instead owns all four initialized fields in one object,
with o32 offsets `0`, `4`, `8`, `0xC` and total size `0x10`. The copy uses
`&payload` and `sizeof(payload)`, with the SDK-compatible
`void *(void *, const void *, u32)` declaration. No artificial padding or
volatile accesses are needed for the payload.

The other helper contracts in this function are unchanged. In particular,
this change does not settle the separate `func_1510F800` forwarding-contract
review or infer the original meanings of the three payload scalar fields.

## Validation scope

All twelve functions passed independent full-span US `CURRENT (0)`, source-unit
layout, progress and whitespace checks on the first attempt, without permutation.
The clean `verify-batch` returned `BATCH_COMPLETE`: the 2,072,880-byte integrated
US GAME image and mapped external data matched the reference; 1,978 tests ran
successfully with 41 skips, and metadata/progress/whitespace checks passed.
This is a recheck of existing matches, with no new match credit or source-unit
transition. No full-ROM or EU verification is claimed. Current task logs and
file hashes are kept under `build/us/manual-attempts/done-contract-cleanup/`.
