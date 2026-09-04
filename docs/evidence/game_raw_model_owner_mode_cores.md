# US model, owner-emitter and actor-mode cores

Evidence type: `structural_analysis`

These are narrower working source families within older navigation intervals
from local `mkst/conker` commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined base `0x2D4B0`). Call relationships, object
fields and concrete selector values support the cuts. They do not establish
original filenames or exact historical compilation-unit limits.

## Model lifecycle: `0x1A7950:0x1A8B20`

Constructor `151A7950` allocates type `0x2D`, base `0x80` plus count times
`0x18` and requested custom storage. It copies a `0x50`-byte descriptor to
object `+0x10`, sets the model record pointer at `+0x64`, phase `+0x68`,
custom pointer `+0x60`, and model resource state at `+0x7C`.

Update `151A7A90` reads that phase/record array, calls recursive geometry
helper `151A8340`, and dispatches descriptor selectors `+0x2C/+0x2D` through
`8008F940/8008F948`. The concrete dispatch at `0x1A7AF8/0x1A7B04` selects
local `151A87F8` for index 1 (`8008F944`). Wrapper `151A8624` calls the
constructor, copies owner custom data through `+0x60`, and sets index 1 at
stack `+0x68` (`0x1A8764/0x1A876C`) in its descriptor based at `+0x4C`.
The resulting object field is exactly `+0x2C`.

Draw `151A7D6C` consumes the same model records and resource state. Cleanup
wrappers `151A8584/151A85D4` call common resource cleanup `151A8560` and
use descriptor selector `+0x5C`. Event dispatcher `151A8A20` uses that selector
with `8008F964` at `0x1A8A54/0x1A8A60`; owned slot 2 (`8008F96C`) is
local owner/identity event `151A8A78`, which follows custom pointer `+0x60`.
Owned type slots `8008BDCC/8008BDD4/8008BDF4/8008BDF8/8008BDE8` select
update, draw, both cleanup wrappers and event dispatcher. All eleven members
belong to this lifecycle; the following generic emitter constructor is excluded.

## Owner-emitter trio: `0x1AB930:0x1ABE00`

Constructor `151AB930` captures owner pointer, identity byte and actor type,
then calls `151491F4` with update `0xE`, event 9, and `0x1C` bytes of custom
state copied to object `+0x28`. The engine update/event tables select local
`151AB9C8/151ABD54` at owned slots `8008A520/8008A8FC`.
The update follows the copied owner record and emits through `151D9014`.
The event helper compares owner/identity, releases on event zero and updates
both fields on event `0x2D`. This gives a complete constructor/update/event
relationship without assigning the surrounding effects to the same source.

## Actor mode and key state: `0xF26A0:0xF2A60`

Opening `150F26A0` chooses actor mode using its associated `+0x3D0` record
and actor fields `+0x23E/+0x2C/+0x6C8`, updating flags and motion parameters.
The branches at `0xF26D4/0xF27D0` call local helper `150F2994` with state 1;
the inactive path calls it with state 0 at `0xF28BC`.

The helper applies that state through `1509BFB0` to keys `0x4016:0x4023`,
`0x405D`, `0x405F`, and conditionally `0x4063:0x4065`, based on
`800D2E4C`. The caller separately queries the same key family (including
`0x405F`) to update actor flags. Owned table slot `800896D8` references the
opening routine. This supports a small mode/key-state core; no beta correlation
was found for these two routines, and none is claimed.

## Validation

All 16 raw labels agree with the independent US function index. Spans total
6,752 bytes and match the owned US instructions, delay slots and padding word
for word. Each endpoint follows a complete return/delay-slot sequence and no
decoded conditional branch crosses it in either direction. No data, rodata or
BSS ownership is assigned. Complete US overlay byte equality gates integration.
All members remain raw ASM, not matched C.

### `src/game/game_1D4E00.c`

Range `0x1a7950:0x1a8b20`; 11 entries, 4,560 bytes.
SHA-1: `61b3d1384f62fd43b224ad92a1dc9c43c461f495`.
debug: 8 correlations, 4 strong.
ects: 4 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151A7950` | `0x140` |
| `func_151A7A90` | `0x2dc` |
| `func_151A7D6C` | `0x5d4` |
| `func_151A8340` | `0x220` |
| `func_151A8560` | `0x24` |
| `func_151A8584` | `0x50` |
| `func_151A85D4` | `0x50` |
| `func_151A8624` | `0x1d4` |
| `func_151A87F8` | `0x228` |
| `func_151A8A20` | `0x58` |
| `func_151A8A78` | `0xa8` |

### `src/game/game_1D8DE0.c`

Range `0x1ab930:0x1abe00`; 3 entries, 1,232 bytes.
SHA-1: `0656320fb431d6f40a862beca464b6b8e2e71d38`.
debug: 3 correlations, 2 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151AB930` | `0x98` |
| `func_151AB9C8` | `0x38c` |
| `func_151ABD54` | `0xac` |

### `src/game/game_11FB50.c`

Range `0xf26a0:0xf2a60`; 2 entries, 960 bytes.
SHA-1: `5215e42428b724902bd9cd2ab2cac90f62e73beb`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F26A0` | `0x2f4` |
| `func_150F2994` | `0xcc` |

## Integration result

The first full US overlay gate passed: 2,072,880 identical bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All three groups are
integrated as mixed C/ASM, with all 16 entries remaining raw ASM.
