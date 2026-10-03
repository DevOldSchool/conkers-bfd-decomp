# Source-local actor model-byte names

Two existing unsigned-byte members receive the descriptive name `modelIndex`:

| Source-local view | Previous member | Offset / width | Identifier tokens |
| --- | --- | --- | ---: |
| `GameA28B0State` in `src/game/game_A28B0.c` | `pad4` | `+4` / one byte | 8 |
| `GameB21B0Object` in `src/game/game_B21B0.c` | `field_4` | `+4` / one byte | 2 |

The name means the mutable applied bank-01 model identity, including its `0xFF`
sentinel. It follows the [model identity](character_semantic_naming.md) and
[representation-selection](actor_representation_selection_semantics.md)
contracts. It is not an actor-slot index, immutable spawn identity, unique
behavior class, representation ordinal or override selector. The separate
derived animation-model byte at actor `+6` is unchanged. These are reviewed
descriptive names, not recovered original developer names.

Both types remain source-local partial views of size `0x320`, with alignment
four under the target MIPS ABI. The actor pool's stride is `0x32C`; these views
do not describe its final twelve bytes. No type or member is added. Member types, padding, headers, signatures,
numeric symbols, constants, executable operations and source boundaries remain
unchanged.

## Actor provenance and every member access

The original actor traversal `1504A730` forms the pool base `800CC2D0` at
`1504A7C0/1504A7E4`, stores the current slot in `800D154C` at `1504A8A0`, and
advances it by `0x32C` at `1504AC84` over 25 slots. A second traversal
`1504ADD0` independently stores the active actor at `1504AE58`. The A28B0
receivers are this current-actor global or `other`, explicitly derived from
the same pool in `150768DC`. The local current-actor save/restore paths retain
actor provenance; `15072208` returns only pool slots or null.

`150837D4` computes a pool slot, stores the supplied model at `15083820`,
and calls `15084D00` with that actor at `1508389C/150838A0`. The latter is the
only direct game-overlay caller of B21B0's model-byte consumer. Its returned
model-sharing representative is stored separately at actor `+6` at `150838B0`.
The same B21B0 view's two other typed consumers, `15085410` and `15085420`,
access only the inner pointer. Their proven callers obtain actor slots from
`1505EEF4`; their complete C bodies and signatures remain byte-identical.

| Function | Original instruction address | Member operation |
| --- | --- | --- |
| `15075548` | `15075604` | Read current model for comparison with `0x28` |
| `150768DC` | `150769B4`, `150769B8` | Compare current and other actor models |
| `150768DC` | `15076A0C` | Index model defaults in `D_800D1C90` |
| `15079790` | `150797BC`, `150797CC` | Store `0xFF` or `0x3A` directly |
| `1507BB28` | `1507BB38` | Index model-keyed route/script resources in `D_800D1588` |
| `15084D00` | `15084D04` | Read the actor model before searching model-sharing groups |

Those are all eight member accesses, plus the two declarations. The model
loader `1503CF20` uses bank 01; `1503D774` uses the same index for bank-11
defaults. The script-resource loader `1503D660` resolves bank-0F metadata.
The script-entry key bytes subsequently read in `1507BB28` are a separate
domain and are unchanged. Automatic selection and explicit application both
call `150837D4`; `1505F188` initializes the actor model to `0xFF`. These facts
establish mutability and sentinel behavior without asserting observed gameplay
execution, appearance or complete indirect-call reachability.

## Exclusions and source-equivalence proof

`GameB21B0PlayerRecord.field_4` remains an `s32` in a separate `0x1C`-byte
player record; both its declaration and use are unchanged.
`Func1506AC0CPacket.field_4` remains an unsigned byte in an eight-byte stack
packet. Original `1506AC2C/1506AC44` copies argument byte `+0x3B` to this packet,
not actor byte `+4`. Its entire source file is unchanged. No `field_70` name,
appearance label, shared declaration or ABI repair is part of this change.

Preparation at `f6134c662678e4e0e1b7b1afb9b306b8a0abf79d` verified exactly ten
identifier-token substitutions. Reversing those tokens reconstructs both
complete source files byte-for-byte; all other lossless lexical tokens,
including whitespace, comments and constants, are identical. Field order,
types, array extents and target-layout accounting are identical. All 29
disabled-candidate blocks across the two files retain their guards, recorded
scores, end markers and adjacent assembly pragmas. Only the authorized member
tokens inside three of those blocks change.

All 29 supporting complete registered spans were reauthenticated against
normalized US ROM SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, including
contiguous original assembly coverage, delay slots and terminal bytes. The
ROM is 67,108,864 bytes, with SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`.
This establishes source and ROM provenance, not a fresh compiler match.

## Required acceptance

Recheck existing matched users `func_15075548` and `func_15079790`, plus
unchanged typed consumers `func_15085410` and `func_15085420`. Require pinned
target size/offset proof, full-span US `CURRENT (0)`, unchanged reviewed
layouts, clean `BATCH_COMPLETE`, integrated game/data/rodata and full-ROM
equality, tests, progress and whitespace gates.

`func_150768DC` (`CURRENT (800)`), `func_1507BB28` (`CURRENT (325)`) and
`func_15084D00` (`CURRENT (1665)`) remain raw/deferred and must not enter a
matching or repair queue for this naming change. Preparation ran no compiler
or build, changed no tracked file, and adds no C match.

## Accepted target verification

Pinned US compilation of before/after type probes confirms four-byte pointers,
`0x320` partial-view sizes, four-byte alignment, one-byte model members at `+4`,
and nested pointers at `+0x31C`. The unrelated player-record view remains
`0x1C`, with its four-byte member at `+4`. Both probe value arrays agree exactly.
All four listed matched functions remain full-span US `CURRENT (0)` with source
layouts preserved. The combined five-function naming batch returned
`BATCH_COMPLETE`; integrated game/data/rodata checks, byte-exact full US ROM,
progress and whitespace passed. All 1,737 tests pass in both the host suite
(37 environment/tool skips) and ROM-enabled pinned suite (one optional validator
skip). Independent review authenticated every receiver, the 29 full spans and
the exact inverse. This adds two local member names and no C match.
