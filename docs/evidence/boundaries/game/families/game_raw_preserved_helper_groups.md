# US helper groups with preserved beta layouts

Evidence type: `structural_analysis`

Ten working source groups cover 38 existing raw entries and 12,640 bytes.
Their generic names retain the upstream combined-image offsets. The grouping
uses the retail relationships below alongside preserved function layout in
both betas; it does not recover historical filenames or linker symbols.
All members remain raw ASM.

## Extents and provenance

Both endpoints occur in the local upstream
`mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`; subtract its combined-image base `0x2D4B0` for
US overlay coordinates. The owned US game payload has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
The beta coordinates below use the corrected ECTS layout.

| Source under `src/game/` | US range | Entries | Bytes | Debug range | ECTS range |
| --- | --- | ---: | ---: | --- | --- |
| `game_6CCB0.c` | `0x3f800:0x3f9f0` | 3 | 496 | `0x3ed40:0x3ef30` | `0x3b120:0x3b310` |
| `game_770F0.c` | `0x49c40:0x4a2b0` | 4 | 1,648 | `0x4a7e0:0x4ae50` | `0x46cc0:0x47330` |
| `game_AE1D0.c` | `0x80d20:0x81690` | 4 | 2,416 | `0x805a0:0x80f10` | `0x7bd40:0x7c6b0` |
| `game_15AA10.c` | `0x12d560:0x12d6f0` | 4 | 400 | `0x132460:0x1325f0` | `0x11d4d0:0x11d660` |
| `game_1A0E60.c` | `0x1739b0:0x173d00` | 3 | 848 | `0x1777b0:0x177b00` | `0x1628f0:0x162c40` |
| `game_1A11B0.c` | `0x173d00:0x174690` | 3 | 2,448 | `0x177b00:0x178490` | `0x162c40:0x1635d0` |
| `game_1B74A0.c` | `0x189ff0:0x18a3c0` | 6 | 976 | `0x18d870:0x18dc40` | `0x1783d0:0x1787a0` |
| `game_1B7870.c` | `0x18a3c0:0x18aa10` | 3 | 1,616 | `0x18dc40:0x18e290` | `0x1787a0:0x178df0` |
| `game_1E5FF0.c` | `0x1b8b40:0x1b8db0` | 4 | 624 | `0x1bbfd0:0x1bc240` | `0x1a5ed0:0x1a6140` |
| `game_20A990.c` | `0x1dd4e0:0x1dd970` | 4 | 1,168 | `0x1dfa10:0x1dfea0` | `0x1c3390:0x1c3820` |

Every member has a strong correlation in both beta indexes. Within each
range, all correlated function offsets have a constant translation, so the
relative entry positions and total span are preserved across three builds.
This is structural corroboration, not an assertion of byte-identical beta
instructions. Aligned endpoints and preceding/final return sequences were
checked independently against the owned payloads.

## Retail relationships

### `game_6CCB0.c`

`1503F800` searches records from `800DBE48`, applying halfword X/Z bounds,
a radius test and a bit mask, then follows the relative next-record offset
at `+0x4`. `1503F904` converts object positions at `+0x14/+0x1C` to
halfwords and calls that search with the object's `+0x320` field. The tail
`1503F964` cycles 25 slots of the `0x32C`-byte object pool at `800CC2D0`,
using `800C67F0/800C67F1` and checking flag `0x800000` at `+0xF8`.

The two packed interior entries have the same non-16-byte-aligned offsets
in all three builds. The tail's original ownership is less certain than the
search/wrapper relationship, so the existing short extent is retained as a
generic search/selection working group rather than a named original file.

### `game_770F0.c`

Four related numeric routines operate on four-component rotations and
matrices. `15049C40` computes a four-component dot product and negates the
second vector when the dot product is negative. `15049CB8` converts a
matrix using diagonal offsets `0x0/0x14/0x28`, square roots and trace-based
selection. `15049EDC` interpolates four components with trigonometric
helpers. `1504A140` constructs matrix terms from products of four input
components. The packed layout is preserved in both betas.

This supports a quaternion helper family, without assigning an unverified
SDK version or a recovered source filename. The following range begins a
distinct entry after the final matrix routine's return and padding.

### `game_AE1D0.c`

`1508108C` tests an object's type byte at `+0x4` against halfword lists at
`8009BD30/8009BD34/8009BD38/8009BD3C`. Both `1508114C` and final
`15081574` call it, and the latter also calls opening `15080D20`.
The routines share indexed state at `800D1C90`, `8009CBCC`, `80086C60`
and the object pool. All four entries are connected by these calls and the
common type/state lookup. The next reviewed group starts at `0x81690`.

### `game_15AA10.c`

All four functions resolve a record through `800DC2B0`, using an object's
byte at `+0x23D` and a record stride of `0xB0`. `1512D560` uses the
record index at `+0xAC`; `1512D604` advances `+0xA8` with a bound of
`0x14`; `1512D66C` clears both indices; `1512D6B0` compares them and
returns a boolean. The common bounded-queue layout connects the complete
short range, including its final predicate.

### `game_1A0E60.c`

Both `15173C60` and final `15173C90` call the central processor
`151739B0`. That processor uses `800B0DF0/800B0E10/800B0E30/800B0E34`
and the current object at `800DBEF4`. The final wrapper also reads that
current-object root after calling `151149AC`. These calls connect all
three members; the last wrapper returns before the next aligned state group.

### `game_1A11B0.c`

`15173D00` manages selection/state using `1501A680/1501A490`.
`151742EC` calls `1501A764` and reuses the opening routine. All three
members reference `800DD348`, alongside the nearby state arrays
`800DD300/800DD310/800DD328`; final `151745F0` checks this root and
flags at `800DD3FC`. The shared state and wrapper/core relationship
corroborate the extent independently of the upstream raw split.

### `game_1B74A0.c`

The opening `15189FF0` allocates and copies a descriptor. `1518A094`
follows the owner at `+0x188`, compares its byte at `+0x3B` with saved
state at `+0x1D`, and dispatches through `8008D5A0`: the pointer load
is at `0x18A110`, and `jalr` is at `0x18A11C`. Three consecutive table
slots select `1518A214`, `1518A2E8` and `1518A324`. Each handler follows
the same owner link and checks bytes at `+0x68/+0x6A/+0x6F`.
Final `1518A360` handles event type `0x2D` and updates the saved byte
at `+0x1D`. Thus the indirect dispatch demonstrably joins the late
handlers to the earlier descriptor/state core. Runtime tables also select
`1518A094` at `80089CC0` and `1518A360` at `8008A058`.

### `game_1B7870.c`

`1518A3C0` constructs a descriptor using randomized selections from
`8008D5B0/8008D5B8`, allocation through `151580B0` and copied fields.
`1518A5F4` updates the resulting effect state through `15158AFC`;
`1518A914` prepares its rendering matrix using `150A8050/150A7790`.
Runtime descriptors select the latter two routines at `8008AE04` and
`8008AE10`. The constructor/update/render family and preserved packed
layout support this small working extent; the historical filename remains
unknown and data ownership is not assigned.

### `game_1E5FF0.c`

All four callbacks combine the timer at `800BE9A4`, trigonometric helper
`15047D60` and updater `15144B68`. They apply the same oscillation pattern
to different object layouts: `151B8B40` uses phase `+0x44`, amplitude
`+0x5C` and bases `+0x48/+0x4C`; `151B8BE0` uses phase `+0x58`,
amplitude `+0x64` and bases `+0x5C/+0x60`; `151B8C54` uses phase
`+0x130` and the embedded record at `+0x120`; final `151B8CFC` uses
phase `+0x118` and the record at `+0x110`. Runtime descriptors select
all four. The repeated operation and preserved layout support this family,
beyond merely sharing the global timer.

### `game_20A990.c`

The opening `151DD4E0` calls `151DD710` twice and `151DD65C` once.
These routines coordinate controller/storage operations through main-code
services at `10025750/10025794/100257C0/10023440`, using shared state
`800E0A30/800E0A31/800E0A34`. Final `151DD8C0` updates the related
flags/timer at `800E0A70/800E0A74` with the game's `800BE9E4/800BE748`.
This is a game wrapper group around external services, not a newly matched
library object. Exact service names are left unassigned here.

## Boundary checks and limits

All raw words, delay slots and padding equal the owned US payload. The
38 existing entries agree with the US index and exactly cover these spans.
No decoded conditional branch crosses an endpoint in either direction.
The neighboring/final routines return before padding, with distinct following
entries. Those checks supplement the call, layout and callback relationships;
they do not independently prove historical source-file boundaries.
No data, rodata or BSS ownership is assigned.

The four-entry `0x169C70:0x16A770` candidate also preserves both beta
layouts, but its runtime callback pointers alone do not yet establish enough
retail cohesion. It is left unregistered pending further review.

## Integration result

All ten units integrate on the first complete-overlay attempt. The resulting
2,072,880-byte game binary is byte-identical to the owned US payload, with
SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 38 entries remain
`raw_asm`, the ten source units have `mixed` integration state, and the
comparison map stays raw assembly.

## Membership

The supported registration command creates the ordered ASM-backed skeletons.
Complete US overlay equality gates integration; it never promotes these
entries to matched C.

### `src/game/game_6CCB0.c`

Range SHA-1: `cbc28756713183d8cf96ec9edca3a9c3405cd3fb`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1503F800` | `0x104` |
| `func_1503F904` | `0x60` |
| `func_1503F964` | `0x8c` |

### `src/game/game_770F0.c`

Range SHA-1: `403add89ad4cabf9df446d0a6266bb3b0b9a0654`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15049C40` | `0x78` |
| `func_15049CB8` | `0x224` |
| `func_15049EDC` | `0x264` |
| `func_1504A140` | `0x170` |

### `src/game/game_AE1D0.c`

Range SHA-1: `89f5a0dfe350222d426dceaac41ac725888ab928`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15080D20` | `0x36c` |
| `func_1508108C` | `0xc0` |
| `func_1508114C` | `0x428` |
| `func_15081574` | `0x11c` |

### `src/game/game_15AA10.c`

Range SHA-1: `463b818cf21e7fa61da75af61128cd204ca23cfe`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1512D560` | `0xa4` |
| `func_1512D604` | `0x68` |
| `func_1512D66C` | `0x44` |
| `func_1512D6B0` | `0x40` |

### `src/game/game_1A0E60.c`

Range SHA-1: `9fc9b29f5b94211619a4ff85eac2ca39ee3fb3f9`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_151739B0` | `0x2b0` |
| `func_15173C60` | `0x30` |
| `func_15173C90` | `0x70` |

### `src/game/game_1A11B0.c`

Range SHA-1: `47f810285ae00e6f222e2fdcdf702c9cbbb279a5`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15173D00` | `0x5ec` |
| `func_151742EC` | `0x304` |
| `func_151745F0` | `0xa0` |

### `src/game/game_1B74A0.c`

Range SHA-1: `fc3800dc1b48c622593290ea419fddcc5fd10044`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15189FF0` | `0xa4` |
| `func_1518A094` | `0x180` |
| `func_1518A214` | `0xd4` |
| `func_1518A2E8` | `0x3c` |
| `func_1518A324` | `0x3c` |
| `func_1518A360` | `0x60` |

### `src/game/game_1B7870.c`

Range SHA-1: `17a5da836c14ae6273d9dcc87d182919c4f4a7fa`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1518A3C0` | `0x234` |
| `func_1518A5F4` | `0x320` |
| `func_1518A914` | `0xfc` |

### `src/game/game_1E5FF0.c`

Range SHA-1: `9bfcdbf088d08b23bc8e8a8267fa396bc4e8d82f`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_151B8B40` | `0xa0` |
| `func_151B8BE0` | `0x74` |
| `func_151B8C54` | `0xa8` |
| `func_151B8CFC` | `0xb4` |

### `src/game/game_20A990.c`

Range SHA-1: `26d51d96e32a251344b348281b1e5f7dcbc5baf3`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_151DD4E0` | `0x17c` |
| `func_151DD65C` | `0xb4` |
| `func_151DD710` | `0x1b0` |
| `func_151DD8C0` | `0xb0` |
