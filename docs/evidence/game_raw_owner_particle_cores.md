# US emission and owner-following particle cores

Evidence type: `structural_analysis`

Two narrowed source hypotheses contain twelve raw entries and 4,528 bytes.
They refine older navigation intervals from local `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`
(combined-image base `0x2D4B0`). Original filenames and historical object
ownership remain unknown.

| Source under `src/game/` | US range | Entries | Bytes | Debug (strong) | ECTS (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_E2E00.c` | `0xB5950:0xB6110` | 6 | 1,984 | 6 (5) | 6 (5) |
| `game_103BE0.c` | `0xD6730:0xD7120` | 6 | 2,544 | 5 (3) | 5 (3) |

## Paired emission helpers

Opening `150B5950` validates its owner pointer at `+0x28` and identity
byte `+0x2C`, then calls `150B5A3C` and model-position helper `150B60E0`.
`150B5A3C` and adjacent variant `150B5C38` construct different emission
arguments but both call `15152B38`, `150B5E34`, and `150B6000`.
The latter two construct additional descriptors for `15130280` and
`151602C0`; the final position helper uses the owner's model at `+0x1D4`
and shared position data at `8009FC30`. Direct calls connect all six members.
The preceding command writer and following different callback remain outside.
Both new endpoints follow normal return/nop pairs and are 16-byte aligned.

## Owner-following particle lifecycle

Opening `150D6730` creates two particles through `15130280`. The first
copies a `0xC`-byte owner record to object `+0xA8`, including its owner pointer
and identity byte. Its descriptor at stack `+0xE4` selects update `0x1E`
(store `0xD684C`, descriptor `+0x62`) and event `8` (store `0xD6858`,
`+0x65`). The second copies `0x1C` custom bytes to the same base and sets
update `0x1F` and event `9` at `0xD6BF8/0xD6C04` in its descriptor at
stack `+0x64`.

The engine reads object `+0x72` and dispatches through `80089760` at
`0x130A24:0x130A38`. Slots `0x1E/0x1F`, `800897D8/800897DC`, select
`150D6CC4/150D6F0C`. Both validate the owner record at `+0xA8`, compare
its identity, and call local position helper `150D6C98`, also used by the
constructor. This helper copies owner position with a fixed vertical offset.

Engine event dispatch reads object `+0x75` at `0x131C50` and calls table
`80089878` at `0x131C60/0x131C6C`. Slots `8/9`, `80089898/8008989C`,
select `150D6E60/150D7068`. Both update the same owner pointer/identity
on event `0x2D`, and release the effect on an owner-removal event. Thus the
constructor, helper, both updates and both event callbacks are connected by
exact selectors and custom-record layout.

The new start follows the preceding emitter's return/nop at
`0xD6728/0xD672C`; the original outer end follows the final callback's
return/nop and three alignment words. Both endpoints are 16-byte aligned.

## Validation and membership

All twelve raw labels agree with the US function index, and their spans cover
the ranges exactly. Every instruction, delay slot and padding word equals the
owned US payload. No decoded conditional branch crosses either boundary in
either direction. No data, rodata or BSS ownership is assigned. Complete US
overlay equality gates integration. These remain raw ASM, without C match credit.

### `src/game/game_E2E00.c`

Range SHA-1: `46a5c20c7b56d1d296124fba79f1491de3085830`.

| Entry | Raw span |
| --- | ---: |
| `func_150B5950` | `0xec` |
| `func_150B5A3C` | `0x1fc` |
| `func_150B5C38` | `0x1fc` |
| `func_150B5E34` | `0x1cc` |
| `func_150B6000` | `0xe0` |
| `func_150B60E0` | `0x30` |

### `src/game/game_103BE0.c`

Range SHA-1: `dc9bb2c6b71306c94eb0a2e0ce80fa1c6def1425`.

| Entry | Raw span |
| --- | ---: |
| `func_150D6730` | `0x568` |
| `func_150D6C98` | `0x2c` |
| `func_150D6CC4` | `0x19c` |
| `func_150D6E60` | `0xac` |
| `func_150D6F0C` | `0x15c` |
| `func_150D7068` | `0xb8` |


## Integration result

Both cores passed their first complete US overlay gate. All 2,072,880 bytes
are identical to the owned original payload, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All twelve entries remain raw ASM.
