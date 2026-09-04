# US state, resource and emission helper groups

Evidence type: `structural_analysis`

Three working source families cover 23 raw entries and 17,472 bytes.
Their outer limits retain the older navigation intervals from local
`mkst/conker` at `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined-image base `0x2D4B0`). Local calls,
shared state and actual callback selectors add structural evidence. These
are working boundaries, with no original filename or historical file guarantee.

| Source under `src/game/` | US range | Entries | Bytes | Debug (strong) | ECTS (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_159940.c` | `0x12C490:0x12D380` | 6 | 3,824 | 4 (4) | 2 (2) |
| `game_11A680.c` | `0xED1D0:0xEEE00` | 8 | 7,216 | 4 (4) | 0 (0) |
| `game_111670.c` | `0xE41C0:0xE5AE0` | 9 | 6,432 | 9 (8) | 6 (5) |

## `game_159940.c`: resource-backed state and motion helpers

Opening `1512C490` calls nearby `1512D070`, `1512D2F8`, and the
final no-op hook `1512D368`. Both larger routines operate on the same
actor's motion and render state. The two remaining members have concrete
producer/consumer links: `1512D238` loads four resources into `800DC280`
and their record counts into `800DC290` using a `0x18`-byte record size.
The main routine reads the resource pointers, and `1512D2F8` reads the
count for the selected resource. `1512D2E4` sets that selection at actor
`+0x850` and starts state `+0x84D`; `1512D2F8` transitions the state,
advances timer `+0x84E`, and clears the state at the resource's count limit.
All six members therefore belong to the connected state/resource family.

## `game_11A680.c`: actor orientation and control family

Hub `150ED748` calls early angular-difference helper `150ED1D0`,
relative-direction wrapper `150ED234`, geometric trajectory helper
`150ED298`, and control clamp/output helper `150ED638`. The last clamps
its two inputs to -45..45 and submits them through `15062FC0`, choosing
an axis layout based on actor type `0x28`.

The otherwise uncalled helper `150ED578` writes actor bitfield `+0x2FC`,
which the hub resets, and uses the same actor `+0x124/+0x127` selection,
global mode `800BE616`, input pointer array `800BE728`, and associated
actor state at `+0x31C`. This is a specific shared control-state relationship,
not inclusion solely because of generic utility calls.

Late `150EEC84` and `150EEDA8` both establish actor state `+5 = 3`,
clear `+0xE4`, and set `+0x125 = 0xFF`. The former updates the same
associated actor and control records used by the hub. Owned callback slots
`8008608C`, `800860A8`, and `800860A0` reference the hub and these two
callbacks. This supports an actor control lifecycle, while the lack of ECTS
correlations leaves its cross-build boundary evidence weaker.

## `game_111670.c`: placement, emission and selected callbacks

Wrapper `150E4514` calls workspace setup `150E41C0` then placement
loop `150E42F8`, which calls emission core `150E4550`. Another geometry
placement path `150E4928` calls the same core. The core calls `150E4E04`,
which calls late `150E5558`. This direct call chain covers seven members.
The other two are tied through actual constructor selectors:

- `150E4550` puts selector `0xD` at descriptor `+0xA2` (stack `+0x102`,
  store `0xE48B4`), then passes the descriptor at stack `+0x60` to
  `15168800`. That constructor copies `0xA8` bytes into object `+0x10`.
  Update `15168870` reads object `+0xB2` at `0x1689D4`, loads table
  `8008C9C8` at `0x1689EC`, and calls it at `0x1689F8`. Slot `0xD`
  is `8008C9FC`, selecting `150E4CBC`, which updates this descriptor's
  size, fade and lifetime fields.
- `150E5558` sets descriptor `+0x63` to `3` (stack `+0x97`, store
  `0xE57B8`) and passes the descriptor at stack `+0x34` to `15132A4C`.
  That places the selector at object `+0x73`. Draw paths read it and
  invoke table `80089934` (`0x13399C:0x1339B0`, also `0x132FF8:0x13300C`).
  Entry `3`, `80089940`, is final `150E5810`, which adjusts effect
  position and motion before producing the drawing transform.

## Validation and limits

All 23 labels agree with the US function index; their ordered spans cover
all three ranges exactly. Every raw instruction, delay slot and padding word
matches the owned US payload. Both ends of each interval follow normal
return/delay-slot/padding boundaries, with no decoded conditional branch
crossing an endpoint in either direction. No data, rodata or BSS ownership
is assigned. The full US overlay byte-equality gate is required before
integration. These remain raw-ASM-backed sources, not C implementations.

## Membership

### `src/game/game_159940.c`

Range SHA-1: `6faccb8da8d4cd73f708bba8817940b5360fffc6`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_1512C490` | `0xbe0` |
| `func_1512D070` | `0x1c8` |
| `func_1512D238` | `0xac` |
| `func_1512D2E4` | `0x14` |
| `func_1512D2F8` | `0x70` |
| `func_1512D368` | `0x18` |

### `src/game/game_11A680.c`

Range SHA-1: `1aca1c0b828be3ecf5edf6b019d56909e98e5148`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_150ED1D0` | `0x64` |
| `func_150ED234` | `0x64` |
| `func_150ED298` | `0x2e0` |
| `func_150ED578` | `0xc0` |
| `func_150ED638` | `0x110` |
| `func_150ED748` | `0x153c` |
| `func_150EEC84` | `0x124` |
| `func_150EEDA8` | `0x58` |

### `src/game/game_111670.c`

Range SHA-1: `e7c453d960462410140e7b31c20bf2f9169a09af`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_150E41C0` | `0x138` |
| `func_150E42F8` | `0x21c` |
| `func_150E4514` | `0x3c` |
| `func_150E4550` | `0x3d8` |
| `func_150E4928` | `0x394` |
| `func_150E4CBC` | `0x148` |
| `func_150E4E04` | `0x754` |
| `func_150E5558` | `0x2b8` |
| `func_150E5810` | `0x2d0` |


## Integration result

The first complete US overlay gate passed for all three sources. All
2,072,880 bytes are identical to the original owned payload, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw ASM.
