# US connected controller and state groups

Evidence type: `structural_analysis`

Four working source groups cover 82 existing raw entries and 80,064 bytes.
One extent is deliberately narrower than its upstream raw split: the state
core at `0xB6BC0:0xB7B40` excludes the following independent effect builders.
All source names remain offset-derived, and all functions remain raw ASM.

## Provenance and extents

The upstream navigation input is local
`mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`. Its combined offsets translate by subtracting
`0x2D4B0`. Both endpoints of the other three ranges occur in that map.
The owned US game payload has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

| Source under `src/game/` | US game range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_64120.c` | `0x36c70:0x3b7c0` | 19 | 19,280 | 6 (0) | 5 (0) |
| `game_90840.c` | `0x63390:0x6a5f0` | 19 | 29,280 | 8 (6) | 3 (2) |
| `game_E4070.c` | `0xb6bc0:0xb7b40` | 17 | 3,968 | 17 (15) | 17 (15) |
| `game_215960.c` | `0x1e84b0:0x1ef040` | 27 | 27,536 | 13 (11) | 6 (3) |

Beta correlations use the refreshed ECTS layout. Sparse or weak correlations
are not treated as boundary proof; the retail relationships below carry the
working-group evidence. None of these ranges has a recovered original file
name, and exact historical object ownership remains a hypothesis.

## Retail grouping evidence

### `game_64120.c`

The opening `15036C70` allocates and clears `0x48` bytes through
`10003C40/100226F0`, stores the buffer at object `+0x324`, and initializes
its float fields. `15036CE8`, `15038620` and `15039CC8` subsequently
read that same object field. This ties the opening allocation to the state
and numeric core rather than relying only on adjacency.

The repeated indexed state at `800C3FFA` occurs 56 times, alongside
`800C3FE8`, `800C3FD0` and `800C3FF0`. Early `15036CE8` dispatches to
`150379DC` and `15038620`; `15036F34` uses final `1503B708` and the
same central processor. The core shares `15037698/15038468`, while the
late wrapper `1503A7F0` calls both early `15036F34` and `1503A678`.
Final `1503B708` returns to `15037880` and `150380C0`. There are 25
inter-function call sites spanning the group.

Five runtime pointers in the ordered table at `80088584:800885A8` select
early and late callbacks, including `15036CE8`, `15036F34`, `1503A60C`,
`1503A678` and `1503A7F0`. This corroborates the shared buffer, indexed
state and bidirectional call relationships. The weak beta correlations add
no independent confidence to this boundary.

### `game_90840.c`

Opening `15063390` resolves a `0x32C`-byte object record from the byte at
`+0x222` and the pool at `800CC2D0`, then compares its X/Z positions with
the caller's object. Early wrappers `150639BC` and `15063A38` reuse it
and operate on state at `800CC284/800CC2B2/800CC2B4/800CC264`.

The large final controller `15065A5C` repeatedly calls the earlier helpers:
`15063404`, `150634E4`, `15063E84`, `15063A38`, `15063390`,
`150641D8`, `15063B64` and `15063C60`. The frequently used
`15063E84` tests object fields and its `+0x31C` custom state, returning
`0x3E7` on the rejected path. The controller and earlier helpers share
selected state at `800CC284/800CC2B0`, the object pool and `800D1580`.
There are 61 inter-function call sites across the complete extent.

The final controller returns at `0x6A5E4` with its stack restoration in the
delay slot and one preserved padding word. The next range begins a distinct
entry at `0x6A5F0`. The call distribution and shared custom state support a
controller/helper working unit; finer historical subdivisions remain possible.

### `game_E4070.c`

`150B6BC0` selects a state using byte `800D9890` and a ten-way jump
table. Its arms call the helpers through final `150B791C`. The helpers
share the active handle at `800D9898`, timer/state at `800D9894/800D98A4`
and workspace `800D98C0`. For example, `150B7484` releases the old
handle through `1516972C`, constructs a descriptor using `800918DC`,
creates its replacement through `15169968`, stores the new handle, and
advances `800D9890` to state 3. Later variants perform the same lifecycle
with nearby descriptors and different state transitions.

Wrappers `150B765C/150B768C` share `150B76BC`; the opening dispatcher
also reaches `150B77A8` and final `150B791C`. Eleven inter-function call
sites plus the jump-table arms connect the state core. Runtime descriptors
select its packed update callbacks at `8008CA30:8008CA44`, including
`150B6DFC`, `150B6E3C`, `150B709C`, `150B71A8` and `150B73F0`.

The original upstream raw interval continues to `0xB89E0`. At `0xB7B40`
the code changes to a separate large descriptor/effect builder, with different
helpers and constants and no calls linking it to the preceding state core.
The new endpoint follows the final core return and is aligned in all three
builds. The complete 17-entry core has identical relative function offsets
and a `0xF80` span in debug `0xB5D00:0xB6C80` and ECTS
`0xB0310:0xB1290`; both betas return immediately before the following
builder's distinct prologue. This independent body and cross-build evidence
supports a finer working boundary than the upstream raw split. It does not
claim an original linker symbol. The four trailing builders stay unmapped.

### `game_215960.c`

The opening `151E84B0` initializes state and calls `151ED1E0`, then
selects a callback through `8008FFF4` using byte `800E0B94`; the indirect
call is at `0x1E84FC`. The adjacent `151E8620` selects the drawing callback
through `8008FFC0`, with the load at `0x1E8640` and `jalr` at `0x1E8654`.
Owned table slots select eight later members, including `151EB06C`,
`151EB930`, `151EBB50`, `151EC1F0`, `151EC3E8` and `151ED09C`.

These callbacks repeatedly share early drawing helper `151E86E4` and
late helper `151ED430`; the latter reuses `151ED29C`. Central `151EC3E8`
connects the later setup/update/cleanup routines by calling `151EC648`,
`151EE184`, `151ED430` and `151EEBE8`. In total, 66 inter-function call
sites join early helpers, table-selected callbacks and the later state core.
State recurs at `800E0BD8`, `800E0C7C`, `8008FDC0/8008FDD4` and
`80090028/80090060`.

Final `151EEFF0` clears `800E9D00`, also used by `151EE184`; it returns
before the preserved zero padding through `0x1EF040`. Its exact historical
ownership is weaker than the dispatcher/core connection. The reviewed
extent retains that raw tail without assigning a filename or matching credit.
This is a game state/rendering group, not a stock library identity.

## Boundary and integration checks

Every raw instruction word, delay slot and padding word equals the owned US
payload. The 82 entries agree with the current US function index and cover
the four proposed spans exactly. No decoded conditional branch crosses an
endpoint in either direction, including the new internal `0xB7B40` split.
Preceding and final returns and the following entry prologues were inspected.
These checks supplement the relationships above; they do not by themselves
prove original source ownership. No data, rodata or BSS ownership is assigned.

The supported registration command creates ordered raw-ASM skeletons and
membership. Complete-overlay byte equality gates their integration, and the
comparison map remains raw assembly.

## Integration result

After recording the reviewed internal raw split at `0xB7B40`, all four
source units integrate on the first complete-overlay build attempt. The
2,072,880-byte US overlay remains byte-identical, with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 82 entries remain
`raw_asm`, and their source units have `mixed` integration state. The
comparison map remains raw assembly, including the excluded trailing builders.

## Membership

### `src/game/game_64120.c`

Range SHA-1: `25000cfe9062e17fce936d6519ef67da4b9532aa`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15036C70` | `0x78` |
| `func_15036CE8` | `0x24c` |
| `func_15036F34` | `0x764` |
| `func_15037698` | `0x1e8` |
| `func_15037880` | `0x15c` |
| `func_150379DC` | `0x6e4` |
| `func_150380C0` | `0x3a8` |
| `func_15038468` | `0x1b8` |
| `func_15038620` | `0x1434` |
| `func_15039A54` | `0x24` |
| `func_15039A78` | `0x250` |
| `func_15039CC8` | `0x208` |
| `func_15039ED0` | `0x1bc` |
| `func_1503A08C` | `0x580` |
| `func_1503A60C` | `0x6c` |
| `func_1503A678` | `0x178` |
| `func_1503A7F0` | `0x40` |
| `func_1503A830` | `0xed8` |
| `func_1503B708` | `0xb8` |

### `src/game/game_90840.c`

Range SHA-1: `6ea9280417cd3155388d9b1242e99d65258acd1e`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15063390` | `0x74` |
| `func_15063404` | `0xe0` |
| `func_150634E4` | `0x8c` |
| `func_15063570` | `0xb8` |
| `func_15063628` | `0x7c` |
| `func_150636A4` | `0x4c` |
| `func_150636F0` | `0x2cc` |
| `func_150639BC` | `0x7c` |
| `func_15063A38` | `0x12c` |
| `func_15063B64` | `0xfc` |
| `func_15063C60` | `0x224` |
| `func_15063E84` | `0x11c` |
| `func_15063FA0` | `0x238` |
| `func_150641D8` | `0xd4` |
| `func_150642AC` | `0x6f4` |
| `func_150649A0` | `0x74` |
| `func_15064A14` | `0x180` |
| `func_15064B94` | `0xec8` |
| `func_15065A5C` | `0x4b94` |

### `src/game/game_E4070.c`

Range SHA-1: `4709a82228540148be374bbd658be14adecc6681`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_150B6BC0` | `0xd0` |
| `func_150B6C90` | `0xa4` |
| `func_150B6D34` | `0x44` |
| `func_150B6D78` | `0x84` |
| `func_150B6DFC` | `0x40` |
| `func_150B6E3C` | `0x260` |
| `func_150B709C` | `0x10c` |
| `func_150B71A8` | `0x78` |
| `func_150B7220` | `0x1d0` |
| `func_150B73F0` | `0x94` |
| `func_150B7484` | `0xdc` |
| `func_150B7560` | `0xfc` |
| `func_150B765C` | `0x30` |
| `func_150B768C` | `0x30` |
| `func_150B76BC` | `0xec` |
| `func_150B77A8` | `0x174` |
| `func_150B791C` | `0x224` |

### `src/game/game_215960.c`

Range SHA-1: `9aeb6ad3f4ea0043e4dfe6819b9fec2947deb1d4`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_151E84B0` | `0x170` |
| `func_151E8620` | `0xc4` |
| `func_151E86E4` | `0x2bc` |
| `func_151E89A0` | `0xccc` |
| `func_151E966C` | `0x6ac` |
| `func_151E9D18` | `0x444` |
| `func_151EA15C` | `0xca0` |
| `func_151EADFC` | `0x270` |
| `func_151EB06C` | `0x8c4` |
| `func_151EB930` | `0x3c` |
| `func_151EB96C` | `0x1e4` |
| `func_151EBB50` | `0x628` |
| `func_151EC178` | `0x78` |
| `func_151EC1F0` | `0x1f8` |
| `func_151EC3E8` | `0x260` |
| `func_151EC648` | `0xa54` |
| `func_151ED09C` | `0x144` |
| `func_151ED1E0` | `0xbc` |
| `func_151ED29C` | `0x194` |
| `func_151ED430` | `0x4dc` |
| `func_151ED90C` | `0x24c` |
| `func_151EDB58` | `0x84` |
| `func_151EDBDC` | `0x370` |
| `func_151EDF4C` | `0x238` |
| `func_151EE184` | `0xa64` |
| `func_151EEBE8` | `0x408` |
| `func_151EEFF0` | `0x50` |
