# US slot, viewport and timed-controller groups

Evidence type: `structural_analysis`

Three working source groups preserve older navigation intervals from local
`mkst/conker` at `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined-image base `0x2D4B0`). Calls, state
producer/consumer relationships and callback selectors support these source
families. Original filenames and exact historical compilation-unit limits
remain unknown.

| Source under `src/game/` | US range | Entries | Bytes | Debug (strong) | ECTS (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_1A0100.c` | `0x172C50:0x172F70` | 5 | 800 | 2 (2) | 2 (2) |
| `game_1A0790.c` | `0x1732E0:0x1739B0` | 5 | 1,744 | 5 (4) | 5 (4) |
| `game_205C90.c` | `0x1D87E0:0x1D8E20` | 11 | 1,600 | 6 (3) | 6 (3) |

## Slot state

`15172C50` initializes the related slot arrays at `800DD2B0/800DD2C0`,
using -1 for empty handles and clearing the remaining per-slot state.
`15172CA8` releases the handles in the first array. `15172D80` reads
that array, calls the release helper, updates the companion state array,
and invokes actor-reset helper `15172D28`. Final `15172E7C` uses the
same arrays and reset helper when changing an actor's slot assignment.
The initializer, release, reset and both assignment paths form a connected
state lifecycle; no data ownership is transferred.

## Viewport command core

Opening `151732E0` and late wrapper `151738C4` read view configuration
through `800B0DF0` and call common core `151733E4`. The core writes
viewport dimensions and state at `800DD2E4:800DD2F4`, consults table
`8008CC70`, and calls final configuration helper `15173994`, which reads
configuration byte `+0x46`. The latter wrapper also consumes `800DD2E4`.

The intervening `151733D8` is a three-instruction identity hook (returns
its first argument). It has no internal call edge; it is retained as the
small hook within this ordered group, not used as semantic proof of the
boundary. All five routines correlate in both betas, with the four
substantive routines strong in each. This is a stronger continuity signal
than the identity hook alone could provide.

## Timed multi-slot controller

Constructor `151D8868` uses opening filter `151D87E0`, allocates type
`0x3F` with a `0x18`-byte base, copies eight descriptor bytes into `+0xE`,
and initializes per-slot state. Update `151D8A24` reads timer `+0x10`,
slot mask `+0x13`, and callback selector `+0x14` from that descriptor.
Its dispatch at `0x1D8A8C/0x1D8A94` uses `8008FCC0`; entry zero is
local `151D8BE0`, which calls transform helper `151D8C00` with custom
state at object `+0x18`.

Cleanup `151D8B24` loops over the same slot mask and clears the active
slots. Both wrappers `151D8B88/151D8BB4` call it before their respective
engine cleanup routines. Event `151D8D5C` releases the object for the
relevant events, including `0x58`. Owned engine slots `8008C174`,
`8008C190`, `8008C19C`, and `8008C1A0` reference update, event and
both cleanup wrappers.

The final two helpers strengthen the end boundary: `151D8DB4` passes the
single-word list at `800AB300` to the engine's type-list operation. Its
value is exactly `0x3F`, matching the constructor. `151D8DE8` invokes it
with event `0x58` after setting `800E0A00`.

## Validation and membership

The 21 entries total 4,144 bytes. All raw labels agree with the US function
index and their ordered spans cover the intervals exactly. Every instruction,
delay slot and padding word matches the owned US payload. Each endpoint
follows a return/delay slot and alignment padding; no decoded conditional
branch crosses one in either direction. No data, rodata or BSS ownership is
assigned. Complete US overlay byte equality gates integration. All entries
remain raw ASM; these mappings do not add matched C.

### `src/game/game_1A0100.c`

Range SHA-1: `c32630459f0a3d1cfb574a5860f4b6eb2ff22328`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_15172C50` | `0x58` |
| `func_15172CA8` | `0x80` |
| `func_15172D28` | `0x58` |
| `func_15172D80` | `0xfc` |
| `func_15172E7C` | `0xf4` |

### `src/game/game_1A0790.c`

Range SHA-1: `932775ccca76f04d9af9bfa3512ff98695e0fd2a`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_151732E0` | `0xf8` |
| `func_151733D8` | `0xc` |
| `func_151733E4` | `0x4e0` |
| `func_151738C4` | `0xd0` |
| `func_15173994` | `0x1c` |

### `src/game/game_205C90.c`

Range SHA-1: `ef3bc22b775b54ecc8ea0cf04f49357ebaf20998`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_151D87E0` | `0x88` |
| `func_151D8868` | `0x1bc` |
| `func_151D8A24` | `0x100` |
| `func_151D8B24` | `0x64` |
| `func_151D8B88` | `0x2c` |
| `func_151D8BB4` | `0x2c` |
| `func_151D8BE0` | `0x20` |
| `func_151D8C00` | `0x15c` |
| `func_151D8D5C` | `0x58` |
| `func_151D8DB4` | `0x34` |
| `func_151D8DE8` | `0x38` |


## Integration result

The first complete US overlay integration passed: all 2,072,880 bytes match
the owned payload, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
All three source groups are integrated as mixed C/ASM with their 21 entries
remaining raw ASM. No C implementation match is claimed.
