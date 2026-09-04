# US dispatch, position and effect-helper groups

Evidence type: `structural_analysis`

Seven working source groups cover 94 existing raw entries and 29,520 bytes.
They include three newly reviewed internal raw boundaries: `0x9EFF0`,
`0x9F800` and `0xFF840`. Original source filenames and precise historical
object ownership remain unknown; all code stays raw ASM.

## Extents and provenance

The local upstream `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`,
provides the outer navigation endpoints (combined base `0x2D4B0`). The
narrowed dispatch core sits inside its `0x9E900:0x9F850` raw span. Two
separate effect families divide its `0xFED30:0x100180` span at `0xFF840`.
The other four ranges retain upstream endpoints with independent retail
relationships recorded below. The US payload SHA-1 is
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

| Source under `src/game/` | US range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_CC4A0.c` | `0x9eff0:0x9f800` | 13 | 2,064 | 13 (12) | 0 (0) |
| `game_12C1E0.c` | `0xfed30:0xff840` | 9 | 2,832 | 3 (2) | 3 (2) |
| `game_12CCF0.c` | `0xff840:0x100180` | 7 | 2,368 | 3 (2) | 0 (0) |
| `game_13BB20.c` | `0x10e670:0x10fea0` | 14 | 6,192 | 9 (8) | 8 (7) |
| `game_173D40.c` | `0x146890:0x147740` | 13 | 3,760 | 13 (10) | 7 (3) |
| `game_191C30.c` | `0x164780:0x165c80` | 9 | 5,376 | 6 (4) | 6 (4) |
| `game_1C1150.c` | `0x193ca0:0x1957b0` | 29 | 6,928 | 16 (13) | 3 (0) |

Beta counts use the corrected ECTS extraction. They are supporting navigation
evidence and do not prove source bounds, byte equality or code absence.

## Retail group relationships

### `game_CC4A0.c`

`1509EFF0` dispatches on the record word at `+0x4`, with an override from
`800D3840`, to helpers through `1509F6E8`. It reuses `1509F6B0` on
several paths. `1509F284` selects control operations through `1509F660`
and final `1509F77C`. Several helpers resolve an object through `1505EEF4`,
convert its X/Y/Z positions to integers, and pass them to main-executable
services; the final helper calls `1000F91C` with that converted position.
There are eleven direct inter-function call sites.

The first two callbacks in the original broad range instead use view/object
services and are left outside this group. The final two small wrappers also
stay outside. Both new endpoints follow completed returns. The reviewed
13-entry core combines the dispatchers with their service-parameter helpers;
it does not assign a stock library identity to the game wrappers.

### `game_12C1E0.c`

The two constructors `150FED30` and `150FF084` follow the same sequence:
resolve state with `150FF288`, prepare values through `150FF2AC`, build
through `150FF2D4`, and use `150FF474` for the related effect. Shared
`150FF2D4` also calls final `150FF6E0`. The latter and callback
`150FEFD0` use the same parameter family rooted at `800A2050` and
updater `1514654C`. Nine direct inter-function calls tie the constructors,
helpers and late callback core together.

The final helper returns at `0xFF838` with its stack restoration in the
delay slot. At aligned `0xFF840`, a separate constructor begins and uses
a different set of helpers and descriptors. This body/call transition supports
a narrower working boundary than the original combined raw span.

### `game_12CCF0.c`

Opening `150FF840` calls `150FFCC8`, final `150FFD84`, repeated helper
`150FFB6C`, and `150FFC3C`. It shares parameters `800A2130` and
`80088BB0` with callback `150FFBDC`. `150FFB6C` resolves object-pool
positions; final `150FFD84` constructs a descriptor via `15130280`.
Six direct inter-function calls connect this second family, which uses
`800A2130` and nearby parameters instead of the preceding family's
`800A2050` set. It returns before padding at the existing `0x100180`
endpoint. The separation is a structural working hypothesis, not a recovered
linker boundary.

### `game_13BB20.c`

Three early wrappers `1510E7A4/1510E82C/1510E8BC` call the main
processor `1510E950`. That processor reuses opening numeric helper
`1510E670` and lookup `1510F800`; `1510F648` and `1510F8D8` also
reuse the lookup. These routines share workspace `800D3300`, roots
`800DBE3C/800DBE54/800DBE60`, and state `800D37E0/800D3830`.

The early `1510F720` and final pair `1510FD20/1510FE30` traverse the
same root `800DBE48`; late controller `1510FC34` calls both tail helpers.
Thus the tail has a concrete shared-root relationship with the preceding
lookup family. Eleven direct inter-function calls support the range. Finer
historical subdivisions remain possible, particularly between the numeric
processor and the short list-management tail. The following range starts the
separately reviewed selected-view setup family.

### `game_173D40.c`

Opening helper `15146890` resolves a position through an object's `+0x1D4`
record, selecting attachment modes `0x13/0x17` from the requested mode.
Eight later routines call this helper directly, including the final
`151475D8`; wrappers `15146BB8/15146BD8` share `15146BF8`, which
also calls the opening helper. The callers use the resulting position with
related effect construction services. Eleven runtime descriptor slots select
the group's callbacks. The final three variants share the same position and
construction pattern with different parameter/dispatch tables.

Ten direct inter-function calls and repeated attachment/position handling
support the working extent. The isolated builder `151470FC` has weaker
historical ownership evidence than the connected helper core; it retains its
existing packed raw placement without a filename or matched-code claim.

### `game_191C30.c`

Constructor `15164780` allocates and initializes an object. `15164F0C`
uses `15165628` repeatedly to construct related variants, and that helper
calls the opening constructor. Callback `1516489C` updates the shared
24-byte-per-entry state at `800DCDE0`; `15164EE4` clears the same state.

The update dispatches through `8008B390` using signed object byte `+0x11`,
with a load at `0x164904` and `jalr` at `0x164910`. This table selects
late `151658DC`; the neighboring callback table selects `15165B80`, which
calls final `15165BB0`. The final helper reads the object's selector byte
at `+0x16`, obtains a position via `15144B34`, and evaluates the relative
position. Constructor reuse, shared state and actual table dispatch connect
the late callbacks to the early core. There are eleven direct call sites.

### `game_1C1150.c`

The early wrappers `151942B0/151942E8` both call `15193CA0`.
`15194B94` reuses the earlier wrapper, `15194B1C` and `151949F4`;
`15194EA8` reuses `15194BF0`. Middle `15194D80/15194DA4` share
`15194FF4`, and `15194DC8` calls the latter wrapper. These interleaved
callback/helper relationships account for thirteen direct calls.

Twenty-one owned-data slots in `8008669C:80086728` select the callback
family, including the final `15195738`. The engine's descriptor construction
at `0x5E39C:0x5E3B4` reads a halfword index, loads the corresponding
pointer from the table rooted at `8008630C`, and stores that callback into
the descriptor. This establishes these words as callback entries rather than
incidental pointer-like data. The shared callback contract and local helper
reuse support a bounded command/effect working group. The global table
spans many source groups; table membership alone is not treated as proof of
this particular historical file boundary.

## Boundary checks and gate

Every raw instruction word, delay slot and padding word equals the owned US
payload. The 94 existing entries agree with the US index and cover the
reviewed spans exactly. No decoded conditional branch crosses any endpoint
in either direction, including the three new internal splits. Preceding and
final return sequences and following function prologues were inspected.
These checks supplement the relationships above; they do not independently
prove original object ownership. No data, rodata or BSS is assigned.

Reviewed raw boundaries precede supported registration. Ordered ASM-backed
skeletons and inventories are created through `./conker`, and complete US
overlay equality gates integration. No C implementation is claimed.

## Integration result

All seven source units integrate on the first complete-overlay attempt. The
2,072,880-byte US overlay remains byte-identical, with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 94 entries remain
`raw_asm`, their units have `mixed` integration state, and the comparison
map remains raw assembly. The excluded ends of the dispatch range remain
unmapped.

## Membership

### `src/game/game_CC4A0.c`

Range SHA-1: `f465f01ee562494e3ba6365a813595c41b0ea130`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1509EFF0` | `0x258` |
| `func_1509F248` | `0x3c` |
| `func_1509F284` | `0xb8` |
| `func_1509F33C` | `0x18` |
| `func_1509F354` | `0x128` |
| `func_1509F47C` | `0x6c` |
| `func_1509F4E8` | `0xc0` |
| `func_1509F5A8` | `0x4c` |
| `func_1509F5F4` | `0x6c` |
| `func_1509F660` | `0x50` |
| `func_1509F6B0` | `0x38` |
| `func_1509F6E8` | `0x94` |
| `func_1509F77C` | `0x84` |

### `src/game/game_12C1E0.c`

Range SHA-1: `469da826685b2d418eb3498ed2eb335b7d7a8296`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_150FED30` | `0x2a0` |
| `func_150FEFD0` | `0xb4` |
| `func_150FF084` | `0x204` |
| `func_150FF288` | `0x24` |
| `func_150FF2AC` | `0x28` |
| `func_150FF2D4` | `0x1a0` |
| `func_150FF474` | `0x240` |
| `func_150FF6B4` | `0x2c` |
| `func_150FF6E0` | `0x160` |

### `src/game/game_12CCF0.c`

Range SHA-1: `29cc4f14e59052a5a9fba2d76f6cecac7e156715`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_150FF840` | `0x32c` |
| `func_150FFB6C` | `0x70` |
| `func_150FFBDC` | `0x60` |
| `func_150FFC3C` | `0x8c` |
| `func_150FFCC8` | `0x64` |
| `func_150FFD2C` | `0x58` |
| `func_150FFD84` | `0x3fc` |

### `src/game/game_13BB20.c`

Range SHA-1: `6b02123d2472d34ad17442c6ca279559a75ff509`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1510E670` | `0x134` |
| `func_1510E7A4` | `0x88` |
| `func_1510E82C` | `0x90` |
| `func_1510E8BC` | `0x94` |
| `func_1510E950` | `0xcf8` |
| `func_1510F648` | `0xd8` |
| `func_1510F720` | `0xe0` |
| `func_1510F800` | `0x20` |
| `func_1510F820` | `0xac` |
| `func_1510F8CC` | `0xc` |
| `func_1510F8D8` | `0x35c` |
| `func_1510FC34` | `0xec` |
| `func_1510FD20` | `0x110` |
| `func_1510FE30` | `0x70` |

### `src/game/game_173D40.c`

Range SHA-1: `397c633becad957be8ac3d7b5c750b97e084b55f`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15146890` | `0xe0` |
| `func_15146970` | `0x128` |
| `func_15146A98` | `0x120` |
| `func_15146BB8` | `0x20` |
| `func_15146BD8` | `0x20` |
| `func_15146BF8` | `0x168` |
| `func_15146D60` | `0x124` |
| `func_15146E84` | `0x1bc` |
| `func_15147040` | `0xbc` |
| `func_151470FC` | `0x21c` |
| `func_15147318` | `0x160` |
| `func_15147478` | `0x160` |
| `func_151475D8` | `0x168` |

### `src/game/game_191C30.c`

Range SHA-1: `99da568f4d956ca375d6ed854dce628706b6d3a0`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15164780` | `0x108` |
| `func_15164888` | `0x14` |
| `func_1516489C` | `0x648` |
| `func_15164EE4` | `0x28` |
| `func_15164F0C` | `0x71c` |
| `func_15165628` | `0x2b4` |
| `func_151658DC` | `0x2a4` |
| `func_15165B80` | `0x30` |
| `func_15165BB0` | `0xd0` |

### `src/game/game_1C1150.c`

Range SHA-1: `acf5247bc1b8a09f466422f05f1a086fbcac3069`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15193CA0` | `0x610` |
| `func_151942B0` | `0x38` |
| `func_151942E8` | `0x38` |
| `func_15194320` | `0x74` |
| `func_15194394` | `0x74` |
| `func_15194408` | `0x180` |
| `func_15194588` | `0x44` |
| `func_151945CC` | `0x1c8` |
| `func_15194794` | `0x7c` |
| `func_15194810` | `0x1d0` |
| `func_151949E0` | `0x14` |
| `func_151949F4` | `0x74` |
| `func_15194A68` | `0x4c` |
| `func_15194AB4` | `0x68` |
| `func_15194B1C` | `0x78` |
| `func_15194B94` | `0x5c` |
| `func_15194BF0` | `0x190` |
| `func_15194D80` | `0x24` |
| `func_15194DA4` | `0x24` |
| `func_15194DC8` | `0x8c` |
| `func_15194E54` | `0x54` |
| `func_15194EA8` | `0xa0` |
| `func_15194F48` | `0xac` |
| `func_15194FF4` | `0x1ec` |
| `func_151951E0` | `0x348` |
| `func_15195528` | `0x128` |
| `func_15195650` | `0x48` |
| `func_15195698` | `0xa0` |
| `func_15195738` | `0x78` |
