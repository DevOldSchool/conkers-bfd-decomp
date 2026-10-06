# US composite emitters and timed renderer

Evidence type: `structural_analysis`

These source-family hypotheses use call graphs, exact callback selections and
producer/consumer fields. Older navigation intervals are from local `mkst/conker`
commit `3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`
(combined offset base `0x2D4B0`). The internal return boundary `0x1A4FD0`
separates an actor effect family from a different type-`0x5A` timed renderer.
Original filenames and precise historical compilation-unit limits are unknown.

## Actor effect family: `0x1A3390:0x1A4FD0`

Opening `151A3390` constructs three related effects on the same owner through
`151A3504`, `151A4590` and `151A499C`. The first copies a `0x50`-byte
owner/model descriptor through object pointer `+0x98`, using `151A4E34` to
resolve model position. It supplies update/step/draw selector 6 to `15147A80`.
Owned slots `8008A218`, `8008A254`, and `8008A2BC` select local
`151A361C`, `151A37C0`, and `151A3BE4`. The engine's update/step dispatches
are at `0x1477B8/0x1477C4` and `0x147814/0x147820`; draw dispatch is
`0x147CEC/0x147CF8`. These callbacks consume the same descriptor fields.

Step `151A37C0` calls both position helper `151A4E34` and reset helper
`151A4E9C`. Event `151A4CE0` also calls the reset helper through `+0x98`.
The step's fallback creates a `0x30`-byte owner descriptor via `151491F4`
with update `0xA` and event 5, selecting `151A4ECC/151A4F7C` through
`8008A510/8008A8EC`. The former validates owner/identity and calls the
original constructor `151A3504`; the latter releases the associated object.

Root's `151A499C` creates an owner descriptor of size `0x20` with update 5
and event 1, selecting local `151A4A38/151A4D88` (`8008A4FC/8008A8DC`).
They use the same owner pointer and identity byte copied to object `+0x28`.
The separate `151A4590` constructs a particle emitter with descriptor byte
`+0x2B` equal to 1. Engine dispatch reads object `+0x3B` and uses
`80089A70`; slot 1 is local `151A4638`. Its child descriptor selects update
0 (`sp+0x9A`, descriptor base `sp+0x38`), hence `151A483C` at `80089760`.
Companion update variant `151A4900` occupies the adjacent slot and consumes
the same small custom record at `+0xA8`, including step/lifetime byte `+0x1A`.
This variant is grouped by the specific record layout and behavior; the shown
factory directly selects slot 0, not both variants.

## Timed renderer: `0x1A4FD0:0x1A5660`

Constructor `151A4FD0` allocates type `0x5A`, with base size `0x20`, and
initializes timer `+0x10`, draw selector `+0x14`, phase fields `+0x15:0x18`,
event selector `+0x19` and parameter `+0x1A`. Update `151A5070` advances
that timer/phase and releases the object. Draw dispatcher `151A5130` reads
`+0x14` and invokes `8008F900` at `0x1A5154/0x1A5158`; its first owned
entry is local renderer `151A5170`. Event dispatcher `151A55D4` reads
`+0x19` and dispatches through `8008F904` (first entry null).

Owned type descriptor slots `8008C6F0`, `8008C6F8`, and `8008C70C` select
update, draw dispatcher and event dispatcher. Final sender `151A561C` uses
the one-word list at `800A8D70`, whose owned value is exactly `0x5A`, joining
the final helper to the constructor and supporting this complete six-entry core.

## Configured particle lifecycle: `0x191BE0:0x1927C0`

Preset wrapper `151925C4` picks configuration records and calls opening
constructor `15191BE0`. That constructor creates a `0x68`-byte owner/custom
record at `+0x28` through `15149130`, with update and event indices `0x1D`.
Engine tables `8008A4E8` and `8008A8D8` select local `15191D54` and
`1519277C` at `8008A55C/8008A94C`; actual dispatches are at
`0x1492A8/0x1492B0` and `0x14946C/0x149478`. The event helper passes the
same owner/identity fields at `+0x28/+0x2C` to the engine event operation.

Update `15191D54` calls child constructor `1519203C`. This sets selector
`0xF` at stack `+0xB6` (`0x192188`) with descriptor base `+0x54`, hence
byte `+0x62`. The particle engine copies it to object `+0x72` and selects
slot `0xF` of `80089760`, local `1519257C` at `8008979C`. This callback
calls both local particle steps `15192308/15192358` (also slots `0xD/0xE`).
The child constructor copies a `0x28`-byte record to object `+0xA8`, consumed
by the two steps. Thus all eight entries have concrete lifecycle relationships.

## Validation

All 31 raw entries agree with the independent US function index. Their spans
cover 11,952 bytes exactly, and every instruction, delay slot and padding word
matches the owned US payload. No decoded conditional branch crosses these
endpoints in either direction. Endpoints follow complete return/delay-slot
sequences. No data, rodata or BSS ownership is assigned. Beta correlations
support continuity but do not establish original filenames. Full US overlay
byte equality gates integration; these mappings do not add matched C.

### `src/game/game_1D0840.c`

Range `0x1a3390:0x1a4fd0`; 17 entries, 7,232 bytes.
SHA-1: `6e2a0305b3df7cd59a42798cc0f8401e1d829bc2`.
debug: 9 correlations, 6 strong.
ects: 7 correlations, 5 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151A3390` | `0x174` |
| `func_151A3504` | `0x118` |
| `func_151A361C` | `0x1a4` |
| `func_151A37C0` | `0x424` |
| `func_151A3BE4` | `0x9ac` |
| `func_151A4590` | `0xa8` |
| `func_151A4638` | `0x204` |
| `func_151A483C` | `0xc4` |
| `func_151A4900` | `0x9c` |
| `func_151A499C` | `0x9c` |
| `func_151A4A38` | `0x2a8` |
| `func_151A4CE0` | `0xa8` |
| `func_151A4D88` | `0xac` |
| `func_151A4E34` | `0x68` |
| `func_151A4E9C` | `0x30` |
| `func_151A4ECC` | `0xb0` |
| `func_151A4F7C` | `0x54` |

### `src/game/game_1D2480.c`

Range `0x1a4fd0:0x1a5660`; 6 entries, 1,680 bytes.
SHA-1: `20b2722901025cc773ae53dbec3988616c2ebd14`.
debug: 4 correlations, 3 strong.
ects: 4 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151A4FD0` | `0xa0` |
| `func_151A5070` | `0xc0` |
| `func_151A5130` | `0x40` |
| `func_151A5170` | `0x464` |
| `func_151A55D4` | `0x48` |
| `func_151A561C` | `0x44` |

### `src/game/game_1BF090.c`

Range `0x191be0:0x1927c0`; 8 entries, 3,040 bytes.
SHA-1: `beba18ad8823a0fceb3e26ad6dc8fca220b26988`.
debug: 8 correlations, 7 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15191BE0` | `0x174` |
| `func_15191D54` | `0x2e8` |
| `func_1519203C` | `0x2cc` |
| `func_15192308` | `0x50` |
| `func_15192358` | `0x224` |
| `func_1519257C` | `0x48` |
| `func_151925C4` | `0x1b8` |
| `func_1519277C` | `0x44` |

## Integration result

The first full US overlay gate passed: 2,072,880 identical bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All three groups are
integrated as mixed C/ASM, with all 31 entries remaining raw ASM.
