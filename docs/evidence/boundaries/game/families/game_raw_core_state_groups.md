# US core state, dispatch and geometry working groups

Evidence type: `structural_analysis`

Six reviewed source groups cover 220 existing raw entries and 120,352 bytes.
All remain ASM-backed skeletons. Their generic names preserve upstream
combined offsets; the grouping is a structural working hypothesis, not a
claim to have recovered original filenames or linker object symbols.

## Provenance and extents

The owned US game payload has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Both endpoints of every range
are existing raw splits in the local upstream
`mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`. Subtracting its combined-image base `0x2D4B0`
gives the active overlay coordinates. These upstream splits are navigation
evidence; the independent retail relationships below justify the working
groups. A raw split alone receives no new mapping credit.

| Source under `src/game/` | Combined range | US game range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| `game_49D30.c` | `0x49D30:0x50D20` | `0x1C880:0x23870` | 57 | 28,656 | 40 (35) | 34 (30) |
| `game_50D80.c` | `0x50D80:0x57FA0` | `0x238D0:0x2AAF0` | 11 | 29,216 | 7 (6) | 4 (3) |
| `game_58F80.c` | `0x58F80:0x5D2C0` | `0x2BAD0:0x2FE10` | 38 | 17,216 | 20 (14) | 17 (11) |
| `game_5D2C0.c` | `0x5D2C0:0x61490` | `0x2FE10:0x33FE0` | 40 | 16,848 | 22 (20) | 20 (19) |
| `game_71820.c` | `0x71820:0x750B0` | `0x44370:0x47C00` | 43 | 14,480 | 32 (17) | 37 (16) |
| `game_AEB40.c` | `0xAEB40:0xB21B0` | `0x81690:0x84D00` | 31 | 13,936 | 22 (20) | 17 (14) |

The beta counts use the refreshed index and corrected ECTS layout. They
preserve useful relative order but cannot establish equality of instructions,
data ownership, or exact original object boundaries.

## Independent retail grouping evidence

### `game_49D30.c`

This substantial state group repeatedly uses the indexed roots and flags at
`800C35B0`, `800C35C8`, `800C35F0`, `800C3638`, `800C363A`, `800C3868`
and `800C3958`. The opening `1501C880` initializes selected state and calls
`1501CC3C`. The early controller `1501D348` calls helpers throughout the
extent, including `15020388`, `15020EC4`, `15022528`, `15022754`,
`15022848` and `15022BA4`. `1501E81C` also calls the late `150233E4` and
`150235DC`.

The final `1502378C` traverses `0x32C`-byte object records and calls
`15022998`, `150229E4` and `1502178C`. This ties the tail to the same
controller/helper set. There are 68 direct inter-function call sites within
the range. The existing extent is supported by these links across the group
and repeated indexed state, not merely its size or proximity to neighboring
state code. Finer historical subdivisions remain possible.

### `game_50D80.c`

Three large processors `1502460C`, `150265CC` and `15029BB8` repeatedly
call the shared early helper `15023BB0`. That helper uses selected indices
to resolve tables at `800C3688` and `800C35D8`; all three processors also
work with the selected object/state at `800C3958`. The final dispatcher
`1502A8A0` selects those processors and is itself reached from the early
`15024130`. There are 58 direct inter-function call sites, with substantial
forward and backward reuse inside the range.

The existing eight-byte opening return `150238D0` is preserved as an existing
raw entry. It is not independently named, newly discovered from a byte
pattern, or used as evidence of this boundary. Its original file ownership is
weaker than the connected processor core. The working extent retains it
without changing any instruction or claiming a matched implementation.

### `game_58F80.c`

The opening `1502BAD0` traverses the object pool rooted at `800CC2D0` and
calls `1502C408` and `1502C974`. The next controller `1502BD84` reaches
`1502DF38`, `1502C608`, `1502E4C4`, `1502EEF4`, `1502F264`, `1502EAFC`
and the late `1502FBE8`; `1502BEE4` also reaches `1502F3C8` and
`1502F948`. The large middle `1502CCFC` uses `1502F01C`, `1502F9FC`
and final `1502FD70`.

The pool base appears 26 times alongside recurring state at `800C3E88`,
`800C4ED0`, `800C3E7A` and `800D121C`. The final helper updates a bounded
byte value and is directly used by the middle routines. These 32
inter-function call sites and shared pool/state access support the extent.

### `game_5D2C0.c`

The early helper `15030158` updates the linked root `800C3EE0`, using node
links at `+0x54` and `+0x58`, and calls the later `15031C14`. Several early
controllers reuse it. `15030468` indexes the callback table at `800841C0`
using the node byte at `+0x7`, loads a function pointer at `0x3058C`, and
executes `jalr` at `0x30598`.

The owned data contains seventeen pointers to late members of this same
range, including `15031E2C`, `150331B8`, `150334B8`, `150339C8` and final
`15033F70`. Late `150335C8` also calls early `15030D54`. There are 23
direct inter-function call sites plus the demonstrated indirect dispatcher.
The callback table connects the late predicates/handlers to the earlier
linked-state core. The table's existence does not assign its data section to
this source unit.

### `game_71820.c`

The opening `15044370` clears state at `800CBD9C`. Setup `15044380` calls
`15044660`. The later `15044964` walks linked records and dispatches
through `80085E80` using a record type byte, with the load at `0x44A98`
and `jalr` at `0x44AA0`. Seven table slots contain this range's small
handlers from `15044B78` through `15044E88`.

The central numeric family repeatedly uses the integer workspace at
`800D3300` and roots at `800DBE3C`, `800DBEF4`, `800D37E0` and
`800D3830`. `150461D0`/`15046460` share `15045714` and feed the later
wrappers `150466F8`/`1504697C`; still later wrappers reuse those routines.
The tail contains two geometry/matrix builders with wrappers:
`15047688` calls `15047390`, and final `15047B80` calls `15047700` before
converting the matrix through `150A7790`.

There are 29 direct inter-function call sites. The tail builders' exact
historical file ownership is less certain than the shared-workspace core;
the existing extent is retained as a generic working group, without a
stock SDK identity or a semantic filename claim. The following `0x47C00`
math-library range is outside this registration.

### `game_AEB40.c`

The opening geometry/object routine `15081690` calls `15081C20`, which
uses object positions at `+0x14/+0x18/+0x1C`, signed height at `+0xD6`
and related numeric fields. The later selected-state routine `150825C0`
uses the indexed root at `800D20FC` and calls `15082A44`; the latter
dispatches to helpers throughout the remainder of the range, including
`150832AC`, `15083384`, `15083568`, `150837D4`, `150838EC`,
`150839B8`, `15084488`, `150849A0`, `15084C30` and final `15084CB0`.

The final helper searches halfword entries and returns the selected index.
Shared state recurs at `800D20FC`, `800D210C`, `800D2100`, `800D1F80`
and `800D2040`, alongside the object pool. There are 24 direct
inter-function call sites. The connected dispatch/helper group and common
state corroborate the working extent without proving an original file name.

## Raw review and gate

Each raw word, including delay slots and padding, equals the owned US game
payload. The 220 existing top-level entries agree with the current US function
index and cover the six spans exactly. No decoded conditional branch crosses
any of these boundaries in either direction. The preceding and final
routines return before padding, and the following ranges start at distinct
function entries. Existing return-only members are retained as raw reference
entries; none is newly named or credited as matched C.

These checks supplement the relationships above; padding and successful
reassembly are not proof of original object ownership. No data, rodata or BSS
ownership is assigned. The supported registration command must create the
ordered skeletons and membership, and the complete US overlay must remain
byte-identical before integration is accepted.

## Integration result

The first integration attempt failed to link because `replace_map_range`
did not recognize the following `lib` boundary at `0x47C00`, inserting a
zero-length ASM entry there. The transaction restored project state. The
integration parser now recognizes library entries both at an extent's end
and when rejecting an extent that crosses an existing library. Two focused
regressions cover these cases.

After that tooling correction, all six units integrate on the second attempt.
The complete 2,072,880-byte US overlay is byte-identical, with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The comparison map remains
raw assembly, all 220 entries remain `raw_asm`, and the six units have
`mixed` integration state. No function implementation changed.

## Membership

### `src/game/game_49D30.c`

Range SHA-1: `d08bab20367541a28758424b50556719a6de0064`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1501C880` | `0x3bc` |
| `func_1501CC3C` | `0x184` |
| `func_1501CDC0` | `0x94` |
| `func_1501CE54` | `0x1a4` |
| `func_1501CFF8` | `0x4c` |
| `func_1501D044` | `0x190` |
| `func_1501D1D4` | `0x84` |
| `func_1501D258` | `0x6c` |
| `func_1501D2C4` | `0x84` |
| `func_1501D348` | `0x764` |
| `func_1501DAAC` | `0x36c` |
| `func_1501DE18` | `0xec` |
| `func_1501DF04` | `0x158` |
| `func_1501E05C` | `0x158` |
| `func_1501E1B4` | `0x144` |
| `func_1501E2F8` | `0x108` |
| `func_1501E400` | `0x140` |
| `func_1501E540` | `0x1fc` |
| `func_1501E73C` | `0xe0` |
| `func_1501E81C` | `0x1fc` |
| `func_1501EA18` | `0x220` |
| `func_1501EC38` | `0xaf4` |
| `func_1501F72C` | `0x560` |
| `func_1501FC8C` | `0x1dc` |
| `func_1501FE68` | `0x180` |
| `func_1501FFE8` | `0x3a0` |
| `func_15020388` | `0x4f0` |
| `func_15020878` | `0x64c` |
| `func_15020EC4` | `0x8c8` |
| `func_1502178C` | `0x62c` |
| `func_15021DB8` | `0x26c` |
| `func_15022024` | `0x16c` |
| `func_15022190` | `0x58` |
| `func_150221E8` | `0x4c` |
| `func_15022234` | `0x14` |
| `func_15022248` | `0x14` |
| `func_1502225C` | `0x84` |
| `func_150222E0` | `0xb8` |
| `func_15022398` | `0x190` |
| `func_15022528` | `0x118` |
| `func_15022640` | `0x7c` |
| `func_150226BC` | `0x98` |
| `func_15022754` | `0x68` |
| `func_150227BC` | `0x8c` |
| `func_15022848` | `0x9c` |
| `func_150228E4` | `0xb4` |
| `func_15022998` | `0x4c` |
| `func_150229E4` | `0x124` |
| `func_15022B08` | `0x9c` |
| `func_15022BA4` | `0x6c0` |
| `func_15023264` | `0x158` |
| `func_150233BC` | `0x28` |
| `func_150233E4` | `0x5c` |
| `func_15023440` | `0x64` |
| `func_150234A4` | `0x138` |
| `func_150235DC` | `0x1b0` |
| `func_1502378C` | `0xe4` |

### `src/game/game_50D80.c`

Range SHA-1: `4d4f3f6f086ab9c5ff4db7e45d4cbff567d13811`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_150238D0` | `0x8` |
| `func_150238D8` | `0x2d8` |
| `func_15023BB0` | `0x230` |
| `func_15023DE0` | `0x350` |
| `func_15024130` | `0x84` |
| `func_150241B4` | `0x144` |
| `func_150242F8` | `0x314` |
| `func_1502460C` | `0x1fc0` |
| `func_150265CC` | `0x35ec` |
| `func_15029BB8` | `0xce8` |
| `func_1502A8A0` | `0x250` |

### `src/game/game_58F80.c`

Range SHA-1: `a240e8037f728b1ddcf7f177c065b390641e5899`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1502BAD0` | `0x2b4` |
| `func_1502BD84` | `0x160` |
| `func_1502BEE4` | `0x2c0` |
| `func_1502C1A4` | `0x1dc` |
| `func_1502C380` | `0x3c` |
| `func_1502C3BC` | `0x4c` |
| `func_1502C408` | `0x200` |
| `func_1502C608` | `0xe0` |
| `func_1502C6E8` | `0x28c` |
| `func_1502C974` | `0x2c0` |
| `func_1502CC34` | `0xc8` |
| `func_1502CCFC` | `0x850` |
| `func_1502D54C` | `0xe4` |
| `func_1502D630` | `0x1f4` |
| `func_1502D824` | `0x2fc` |
| `func_1502DB20` | `0x64` |
| `func_1502DB84` | `0x3b4` |
| `func_1502DF38` | `0x53c` |
| `func_1502E474` | `0x50` |
| `func_1502E4C4` | `0x538` |
| `func_1502E9FC` | `0x10` |
| `func_1502EA0C` | `0x44` |
| `func_1502EA50` | `0x10` |
| `func_1502EA60` | `0x1c` |
| `func_1502EA7C` | `0x1c` |
| `func_1502EA98` | `0x64` |
| `func_1502EAFC` | `0x138` |
| `func_1502EC34` | `0x258` |
| `func_1502EE8C` | `0x68` |
| `func_1502EEF4` | `0x128` |
| `func_1502F01C` | `0x248` |
| `func_1502F264` | `0x164` |
| `func_1502F3C8` | `0xc8` |
| `func_1502F490` | `0x4b8` |
| `func_1502F948` | `0xb4` |
| `func_1502F9FC` | `0x1ec` |
| `func_1502FBE8` | `0x188` |
| `func_1502FD70` | `0xa0` |

### `src/game/game_5D2C0.c`

Range SHA-1: `f0f9cd335332e3bdef6357d749faf9c67632342b`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1502FE10` | `0x1c8` |
| `func_1502FFD8` | `0x180` |
| `func_15030158` | `0x198` |
| `func_150302F0` | `0x20` |
| `func_15030310` | `0xd4` |
| `func_150303E4` | `0x84` |
| `func_15030468` | `0x68c` |
| `func_15030AF4` | `0x260` |
| `func_15030D54` | `0xb4` |
| `func_15030E08` | `0x18c` |
| `func_15030F94` | `0xdc` |
| `func_15031070` | `0x154` |
| `func_150311C4` | `0x768` |
| `func_1503192C` | `0x30` |
| `func_1503195C` | `0x70` |
| `func_150319CC` | `0x84` |
| `func_15031A50` | `0x1c4` |
| `func_15031C14` | `0x218` |
| `func_15031E2C` | `0x50` |
| `func_15031E7C` | `0x14c` |
| `func_15031FC8` | `0x11f0` |
| `func_150331B8` | `0xc4` |
| `func_1503327C` | `0xac` |
| `func_15033328` | `0x80` |
| `func_150333A8` | `0x98` |
| `func_15033440` | `0x78` |
| `func_150334B8` | `0x110` |
| `func_150335C8` | `0x1c4` |
| `func_1503378C` | `0x58` |
| `func_150337E4` | `0x54` |
| `func_15033838` | `0x190` |
| `func_150339C8` | `0x110` |
| `func_15033AD8` | `0x104` |
| `func_15033BDC` | `0x224` |
| `func_15033E00` | `0x28` |
| `func_15033E28` | `0x5c` |
| `func_15033E84` | `0x40` |
| `func_15033EC4` | `0x48` |
| `func_15033F0C` | `0x64` |
| `func_15033F70` | `0x70` |

### `src/game/game_71820.c`

Range SHA-1: `906cc367eff35d49f0169873e0340222f02b669d`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15044370` | `0x10` |
| `func_15044380` | `0x1ac` |
| `func_1504452C` | `0x12c` |
| `func_15044658` | `0x8` |
| `func_15044660` | `0x270` |
| `func_150448D0` | `0x94` |
| `func_15044964` | `0xc4` |
| `func_15044A28` | `0x150` |
| `func_15044B78` | `0x16c` |
| `func_15044CE4` | `0x5c` |
| `func_15044D40` | `0x60` |
| `func_15044DA0` | `0x48` |
| `func_15044DE8` | `0x58` |
| `func_15044E40` | `0x48` |
| `func_15044E88` | `0x48` |
| `func_15044ED0` | `0x1fc` |
| `func_150450CC` | `0x240` |
| `func_1504530C` | `0x78` |
| `func_15045384` | `0x1c8` |
| `func_1504554C` | `0x1c8` |
| `func_15045714` | `0x6c` |
| `func_15045780` | `0x80` |
| `func_15045800` | `0x80` |
| `func_15045880` | `0x264` |
| `func_15045AE4` | `0x264` |
| `func_15045D48` | `0x244` |
| `func_15045F8C` | `0x244` |
| `func_150461D0` | `0x290` |
| `func_15046460` | `0x298` |
| `func_150466F8` | `0x284` |
| `func_1504697C` | `0x284` |
| `func_15046C00` | `0x80` |
| `func_15046C80` | `0x80` |
| `func_15046D00` | `0x284` |
| `func_15046F84` | `0x80` |
| `func_15047004` | `0xac` |
| `func_150470B0` | `0xac` |
| `func_1504715C` | `0x164` |
| `func_150472C0` | `0xd0` |
| `func_15047390` | `0x2f8` |
| `func_15047688` | `0x78` |
| `func_15047700` | `0x480` |
| `func_15047B80` | `0x80` |

### `src/game/game_AEB40.c`

Range SHA-1: `3ec7dc4b2bd4e24e063e7eb5cf364590232ae2f8`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15081690` | `0x590` |
| `func_15081C20` | `0x1ec` |
| `func_15081E0C` | `0x6c` |
| `func_15081E78` | `0x748` |
| `func_150825C0` | `0x39c` |
| `func_1508295C` | `0x7c` |
| `func_150829D8` | `0x6c` |
| `func_15082A44` | `0x868` |
| `func_150832AC` | `0xd8` |
| `func_15083384` | `0x1e4` |
| `func_15083568` | `0x164` |
| `func_150836CC` | `0x108` |
| `func_150837D4` | `0x118` |
| `func_150838EC` | `0xcc` |
| `func_150839B8` | `0x110` |
| `func_15083AC8` | `0x2d8` |
| `func_15083DA0` | `0x6c` |
| `func_15083E0C` | `0x84` |
| `func_15083E90` | `0x120` |
| `func_15083FB0` | `0x50` |
| `func_15084000` | `0x44` |
| `func_15084044` | `0x308` |
| `func_1508434C` | `0x60` |
| `func_150843AC` | `0xdc` |
| `func_15084488` | `0xd0` |
| `func_15084558` | `0x448` |
| `func_150849A0` | `0x2c` |
| `func_150849CC` | `0x4c` |
| `func_15084A18` | `0x218` |
| `func_15084C30` | `0x80` |
| `func_15084CB0` | `0x50` |
