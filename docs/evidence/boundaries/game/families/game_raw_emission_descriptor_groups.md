# US emission utilities and a descriptor lifecycle

Evidence type: `structural_analysis`

Two working source groups contain 41 raw entries and 24,896 bytes.
They refine the navigation interval `0x14F640:0x155780` from local
`mkst/conker` at `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined-image base `0x2D4B0`). The new
internal boundary is `0x154C90`. Original filenames and exact historical
compilation-unit ownership remain unknown; these are source-family hypotheses.

| Source under `src/game/` | US range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_17CAF0.c` | `0x14F640:0x154C90` | 35 | 22,096 | 27 (24) | 13 (13) |
| `game_182140.c` | `0x154C90:0x155780` | 6 | 2,800 | 3 (1) | 4 (2) |

## `game_17CAF0.c`: emission descriptors and placement utilities

This is a broader utility-family hypothesis, with less certainty about the
original file boundary than the adjacent six-entry lifecycle. Its members
construct effect descriptors, derive placement/direction, select random
counts and offsets, invoke existing effect constructors, and supply small
callbacks for those effects. The grouping does not imply that the different
effect constructors they call belong to this source.

Opening `1514F640` builds a placement record containing a direction,
basis and scale. Early wrapper `1514FEFC` and late `15153C84` both
use it before calling their respective emission cores `1514FF44` and
`15153CCC`. Both cores call shared placement helper `1514F6E8`
and random-vector helper `1514F808`. `1514FB98/1514FBFC` similarly
wrap `1514F8F8`. These relationships extend across much of the interval.

The intervening families follow the same descriptor-emission pattern with
different target constructors: `15150178` uses `151D9014`,
`15150400/1515080C` use `1513264C`, `15151670/15151A38` use
`15147DA0`, `15151D6C/15152190` use `15132A4C`, and `15152520`
uses `15157898`. Later `15152F70`, `15153298`, `15153634`, and
`151539B4` derive trigonometric placement and invoke other constructors.
They retain their distinct APIs and descriptors; no semantic renaming is made.

`15152874` also has an actual dispatch through `8008AC60` selecting
nearby `15152ABC`. The last two small callbacks have direct descriptor
evidence, beyond their table pointers:

- `151541B8` sets descriptor byte `+0x61` to `0xF` at `0x1544A4`,
  passes the descriptor at stack `+0x40` to `15132A4C`, and copies
  `0x18` custom bytes to the child at `+0x170`. The constructor places
  this selector at object `+0x71`. Engine update `151321D0` reads it
  at `0x132244` and invokes table `800898B0` at `0x132258/0x132264`.
  Entry `0xF` is `800898EC`, selecting `1515452C`, which consumes
  that custom area.
- `15154884` uses the same path with selector `0x12`, stored at
  `0x1549FC`, and `0x14` custom bytes. Slot `800898F8` selects
  final helper `15154A88`, which reads `+0x170` and uses its phase at
  `+0x17C` to update the effect.

The final callback returns at `0x154C88` with a nop delay slot. The next
routine is a different descriptor's central update rather than another
placement/emission utility. The original outer start follows return/padding.
Numerous ordered strong beta correlations support continuity, without
proving that every utility originally occupied one compilation unit.

## `game_182140.c`: two-type descriptor lifecycle

Constructor `1515548C` optionally calls overlap/filter helper `151555AC`,
chooses object type `0x57/0x5D`, allocates a `0x70`-byte base plus custom
space, copies `0x58` descriptor bytes into object `+0x10`, and stores a
dispatch selector at `+0x68`.

Opening update `15154C90` advances the timer at `+0x22`, uses the
low nibble of `+0x68` to dispatch through `8008ACC8`, adjusts the
descriptor's fade fields, and releases expired objects. Drawing
`15154D80` reads the same descriptor layout. Event `15155564`
dispatches via `8008AD04` using descriptor byte `+0x2A`.
Owned engine descriptor slots `8008C654/C65C/C670` and
`8008C78C/C794/C7A8` select update, drawing and event callbacks.

Final `1515572C` passes the two-word array at `800A6038` to
`15169260`. Its exact values are `0x5D, 0x57`, matching the
constructor's two types. The end follows its return and three padding words.
Thus the constructor, filter, callbacks and final type-list helper form a
connected lifecycle distinct from the earlier utilities.

## Validation and limits

All 41 raw labels agree with the US function index and their ordered spans
cover both ranges exactly. Every instruction, delay slot and padding word
equals the owned US payload. No decoded conditional branch crosses either
endpoint in either direction. No data, rodata or BSS ownership is assigned.

The internal endpoint is recorded as a raw ASM split before supported source
registration. Complete US overlay byte equality gates integration. All entries
remain raw ASM; beta correlations and a byte-identical build do not establish
original source filenames.

## Membership

### `src/game/game_17CAF0.c`

Range SHA-1: `8c8ca66994597fc942f195caebd09c04dc8d4a06`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_1514F640` | `0xa8` |
| `func_1514F6E8` | `0x120` |
| `func_1514F808` | `0xf0` |
| `func_1514F8F8` | `0x2a0` |
| `func_1514FB98` | `0x64` |
| `func_1514FBFC` | `0xec` |
| `func_1514FCE8` | `0x214` |
| `func_1514FEFC` | `0x48` |
| `func_1514FF44` | `0x234` |
| `func_15150178` | `0x288` |
| `func_15150400` | `0x40c` |
| `func_1515080C` | `0x510` |
| `func_15150D1C` | `0x274` |
| `func_15150F90` | `0x26c` |
| `func_151511FC` | `0x474` |
| `func_15151670` | `0x3c8` |
| `func_15151A38` | `0x334` |
| `func_15151D6C` | `0x424` |
| `func_15152190` | `0x390` |
| `func_15152520` | `0x354` |
| `func_15152874` | `0x248` |
| `func_15152ABC` | `0x7c` |
| `func_15152B38` | `0x438` |
| `func_15152F70` | `0x328` |
| `func_15153298` | `0x39c` |
| `func_15153634` | `0x380` |
| `func_151539B4` | `0x2d0` |
| `func_15153C84` | `0x48` |
| `func_15153CCC` | `0x24c` |
| `func_15153F18` | `0x2a0` |
| `func_151541B8` | `0x374` |
| `func_1515452C` | `0x158` |
| `func_15154684` | `0x200` |
| `func_15154884` | `0x204` |
| `func_15154A88` | `0x208` |

### `src/game/game_182140.c`

Range SHA-1: `e986f130381bfe03915806b4242e0a663c954cab`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_15154C90` | `0xf0` |
| `func_15154D80` | `0x70c` |
| `func_1515548C` | `0xd8` |
| `func_15155564` | `0x48` |
| `func_151555AC` | `0x180` |
| `func_1515572C` | `0x54` |

## Integration result

The first complete US game-overlay integration passed: all 2,072,880 bytes
are identical to the owned original payload (SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`). Both sources are integrated
as raw-ASM-backed mixed units; no C implementation credit is claimed.
