# Further US callback and shared-state groups

Evidence type: `structural_analysis`

Five existing raw ranges are reviewed as working source groups: 203 recovered
entries and 54,720 bytes. Their generic filenames preserve upstream combined
offsets. No original filename or exact historical translation-unit extent is
claimed, and every member remains raw ASM.

## Inputs and extent review

The owned US game payload has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The pinned local upstream
`mkst/conker@3adf229175c037c771f251f169f9dd80ca306924` contains both endpoints
of each range as raw splits in `conker/conker.us.yaml`. Subtracting its
combined-image game base `0x2D4B0` gives the current overlay offsets below.
Those old splits supply navigation, not sufficient boundary evidence by
themselves. The call relationships and runtime state below corroborate the
working groups independently.

| Source under `src/game/` | Upstream combined range | US overlay range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| `game_133190.c` | `0x133190:0x135490` | `0x105CE0:0x107FE0` | 37 | 8,960 | 32 (23) | 17 (14) |
| `game_179F30.c` | `0x179F30:0x17CAF0` | `0x14CA80:0x14F640` | 78 | 11,200 | 69 (34) | 56 (26) |
| `game_18A8F0.c` | `0x18A8F0:0x18D250` | `0x15D440:0x15FDA0` | 35 | 10,592 | 30 (24) | 26 (19) |
| `game_1AC2F0.c` | `0x1AC2F0:0x1AFC80` | `0x17EE40:0x1827D0` | 28 | 14,736 | 27 (27) | 24 (24) |
| `game_1ED0F0.c` | `0x1ED0F0:0x1EF500` | `0x1BFC40:0x1C2050` | 25 | 9,232 | 19 (11) | 18 (9) |

The ECTS correlations use the regenerated index with the
[correct loader-derived layout](ects_game_layout.md). Correlations remain
relocation-insensitive research evidence, not instruction matches.

## Observed relationships

### `game_133190.c`

The opening allocator/setup `15105CE0` and callback `1510608C` both call
`15106214` and `15106610`. The former dispatches a series of eight compact
helpers from `151064B4` through `151065EC`. Later constructors `151072BC`,
`15107700` and `15107C1C` return to the opening setup, connecting the early
helper cluster to the end of the range. There are 32 direct inter-function
call sites within the group.

`1510608C` indexes `80088C10` using the signed byte at object `+0x44`, loads
a callback at code offset `0x1060B8`, and calls it with `jalr` at `0x1060C8`.
The table selects the late members `15107924` and `15107E48`; adjacent
callback slots reference `15107604`, `151078E4` and final `15107F98`.
Other runtime descriptors select setup/update/cleanup routines at
`8008C1A8`, `8008C1B0`, `8008C1D0` and `8008C1D4`. These are concrete links
across the existing extent, rather than unrelated adjacent function matches.

### `game_179F30.c`

The opening selector `1514CA80` uses the object's type byte at `+0x4` and a
187-entry jump table to choose attachment/handler information. Its caller
`1514D15C` derives an index from the owner relative to `800CC2D0`, using a
`0x32C` stride, and dispatches through `8008AA70` at `0x14D264` and
`0x14D2A4`. The raw data contains 63 pointers to members across this group's
callback tables, including the final `1514F5CC` at `8008AB40`.

Many handlers call the shared late helper `1514EC1C`, which calls
`1514EBA4` and inserts an allocated node into the owner's `+0x2F4` chain,
using node links at `+0x14` and `+0x18`. Other repeated families share
`1514DCAC`, `1514E89C` and `1514F194`. This includes 48 direct
inter-function call sites. The dispatch tables, common linked layout and
shared helpers tie the many small callback bodies to the larger routines.

### `game_18A8F0.c`

The range starts with allocation/zeroing helpers and then operates on shared
state at `800DCD10`, `800DCD20`, `800DCD78` and `800DCD94:800DCDA0`.
`1515D914` calls `1515E278`, `1515E43C` and `1515EC78`; the middle routines
share `1515EB84`. The setup `1515D6D0` calls the later sequence helper
`1515EF74`, which repeatedly uses `1515F008`, `1515F040` and `1515F0AC`.

The late callbacks `1515F338`, `1515F5C4` and `1515F850` all read the byte
state at `800DCD20`, use the neighboring floating-point state, and call the
early helper `1515D4D4`. Runtime slots `8008B0C0:8008B0C8` select those
three routines; nearby slots also select the short tail handlers and final
`1515FC60`. The 21 direct inter-function calls and ten callback pointers
support the full working range while leaving its original source name open.

### `game_1AC2F0.c`

The opening member compares and updates indexed state at `800DDDAC`,
`800DDDB0`, `800DDDC0` and `800DDE28`. The same neighboring state recurs
throughout the range, especially `800DDDC8`, `800DDDD8` and `800DDDE8`.
Early routines share `1517EF00` and `1517F08C`. The large middle dispatcher
`15180580` repeatedly calls `1517F9F4` and `1517FB9C`, while the later
`15181EE0` also uses `1517F9F4`.

The final callback `15182768`, selected by runtime slot `8008A67C`, unpacks
byte arguments and calls the early `1517F08C`. The preceding `15182748` is
selected at `8008A5CC`. All 27 debug correlations and all 24 ECTS
correlations in this range are strong; these corroborate the shared-state
ordering, without supplying a semantic filename or proving all finer bounds.

### `game_1ED0F0.c`

The opening `151BFC40` prepares a descriptor with mode-dependent dimensions.
The three following constructors share helpers `151C0418`, `151C04F8`,
`151C05A4` and `151C05F0`, with further reuse of `151C0360` and `151C0644`.
The later dispatcher `151C1180` selects those constructors and repeatedly
calls `151C1654`. The large update `151C0698` calls the late helpers
`151C1798`, `151C1860` and `151C196C`; the latter uses `151C1D5C`.

Runtime slots `800898D8`, `800899B4`, `800899D8` and `800899FC` select its
dispatcher and cleanup/update callbacks. A further slot at `80086C9C`
selects `151C1940`, which calls the earlier `151C02E4`. There are 35 direct
inter-function call sites. The final `151C1FB8` is a short related descriptor
emitter; its exact historical file ownership is weaker than the connected
core and remains part of the explicitly provisional upstream working extent.

## Raw checks and limits

Every word of all five generated raw spans was checked against the owned US
payload, including delay slots and padding. Their top-level labels agree
with the US function index, and their recorded spans cover each range exactly.
No decoded conditional branch crosses any proposed boundary in either
direction. The preceding functions return before padding, each final member
returns before padding, and the next groups start at fresh prologues.

Raw bytes, correlations and alignment alone do not prove original object
ownership. These are reviewed structural working groups supported by the
independent relationships above. There may be finer historical subdivisions.
No data, rodata or BSS ownership is assigned from the callback references.

The supported registration command creates ordered ASM-backed source skeletons
and canonical membership. Integration must compare the complete US game
overlay with the independently extracted ROM payload. No matching-C credit
is requested for this work.

## Membership

All five units integrate on the first complete-overlay attempt. The resulting
2,072,880-byte US game binary is byte-identical to the owned payload, with
SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The comparison map retains
raw assembly, all 203 new function records remain `raw_asm`, and the five
source units have `mixed` integration state.

### `src/game/game_133190.c`

Range SHA-1: `e93b147b6729656374a98ea56750de1fa41c7d82`. Spans below include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15105CE0` | `0x3ac` |
| `func_1510608C` | `0x154` |
| `func_151061E0` | `0xc` |
| `func_151061EC` | `0x28` |
| `func_15106214` | `0x2a0` |
| `func_151064B4` | `0x28` |
| `func_151064DC` | `0x34` |
| `func_15106510` | `0x30` |
| `func_15106540` | `0x18` |
| `func_15106558` | `0x2c` |
| `func_15106584` | `0x38` |
| `func_151065BC` | `0x30` |
| `func_151065EC` | `0x24` |
| `func_15106610` | `0x1a8` |
| `func_151067B8` | `0x6c0` |
| `func_15106E78` | `0x80` |
| `func_15106EF8` | `0x2c` |
| `func_15106F24` | `0x2c` |
| `func_15106F50` | `0x48` |
| `func_15106F98` | `0x160` |
| `func_151070F8` | `0x1c4` |
| `func_151072BC` | `0x348` |
| `func_15107604` | `0x18` |
| `func_1510761C` | `0x30` |
| `func_1510764C` | `0x2c` |
| `func_15107678` | `0x2c` |
| `func_151076A4` | `0x5c` |
| `func_15107700` | `0x1e4` |
| `func_151078E4` | `0x40` |
| `func_15107924` | `0xfc` |
| `func_15107A20` | `0xc0` |
| `func_15107AE0` | `0x98` |
| `func_15107B78` | `0xa4` |
| `func_15107C1C` | `0x22c` |
| `func_15107E48` | `0x10c` |
| `func_15107F54` | `0x44` |
| `func_15107F98` | `0x48` |

### `src/game/game_179F30.c`

Range SHA-1: `74a4b102000b9e73525a48d20be4d1664085632b`. Spans below include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1514CA80` | `0x6dc` |
| `func_1514D15C` | `0x1b4` |
| `func_1514D310` | `0xa0` |
| `func_1514D3B0` | `0x108` |
| `func_1514D4B8` | `0xac` |
| `func_1514D564` | `0xe8` |
| `func_1514D64C` | `0x320` |
| `func_1514D96C` | `0xc` |
| `func_1514D978` | `0x7c` |
| `func_1514D9F4` | `0x44` |
| `func_1514DA38` | `0x6c` |
| `func_1514DAA4` | `0x74` |
| `func_1514DB18` | `0x40` |
| `func_1514DB58` | `0xc` |
| `func_1514DB64` | `0x34` |
| `func_1514DB98` | `0x20` |
| `func_1514DBB8` | `0x80` |
| `func_1514DC38` | `0x24` |
| `func_1514DC5C` | `0x28` |
| `func_1514DC84` | `0x14` |
| `func_1514DC98` | `0x14` |
| `func_1514DCAC` | `0x48` |
| `func_1514DCF4` | `0x38` |
| `func_1514DD2C` | `0x20` |
| `func_1514DD4C` | `0x20` |
| `func_1514DD6C` | `0x20` |
| `func_1514DD8C` | `0x20` |
| `func_1514DDAC` | `0x20` |
| `func_1514DDCC` | `0x20` |
| `func_1514DDEC` | `0x20` |
| `func_1514DE0C` | `0x20` |
| `func_1514DE2C` | `0xc` |
| `func_1514DE38` | `0xc` |
| `func_1514DE44` | `0xc` |
| `func_1514DE50` | `0x38` |
| `func_1514DE88` | `0xc` |
| `func_1514DE94` | `0x13c` |
| `func_1514DFD0` | `0x3c` |
| `func_1514E00C` | `0x188` |
| `func_1514E194` | `0x188` |
| `func_1514E31C` | `0x1ec` |
| `func_1514E508` | `0xb0` |
| `func_1514E5B8` | `0xb0` |
| `func_1514E668` | `0xb0` |
| `func_1514E718` | `0xb0` |
| `func_1514E7C8` | `0x5c` |
| `func_1514E824` | `0xc` |
| `func_1514E830` | `0x20` |
| `func_1514E850` | `0x2c` |
| `func_1514E87C` | `0x20` |
| `func_1514E89C` | `0x84` |
| `func_1514E920` | `0xbc` |
| `func_1514E9DC` | `0x20` |
| `func_1514E9FC` | `0x20` |
| `func_1514EA1C` | `0x150` |
| `func_1514EB6C` | `0x20` |
| `func_1514EB8C` | `0x18` |
| `func_1514EBA4` | `0x78` |
| `func_1514EC1C` | `0xc4` |
| `func_1514ECE0` | `0x5c` |
| `func_1514ED3C` | `0x50` |
| `func_1514ED8C` | `0x64` |
| `func_1514EDF0` | `0x80` |
| `func_1514EE70` | `0x5c` |
| `func_1514EECC` | `0x244` |
| `func_1514F110` | `0x20` |
| `func_1514F130` | `0x64` |
| `func_1514F194` | `0x174` |
| `func_1514F308` | `0xc4` |
| `func_1514F3CC` | `0x80` |
| `func_1514F44C` | `0x5c` |
| `func_1514F4A8` | `0x30` |
| `func_1514F4D8` | `0x30` |
| `func_1514F508` | `0x30` |
| `func_1514F538` | `0x30` |
| `func_1514F568` | `0x28` |
| `func_1514F590` | `0x3c` |
| `func_1514F5CC` | `0x74` |

### `src/game/game_18A8F0.c`

Range SHA-1: `69c6db44376e58b0e86815c2333975177e5b1092`. Spans below include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1515D440` | `0x40` |
| `func_1515D480` | `0x54` |
| `func_1515D4D4` | `0x4c` |
| `func_1515D520` | `0x8c` |
| `func_1515D5AC` | `0x4c` |
| `func_1515D5F8` | `0xa4` |
| `func_1515D69C` | `0x2c` |
| `func_1515D6C8` | `0x8` |
| `func_1515D6D0` | `0x244` |
| `func_1515D914` | `0x964` |
| `func_1515E278` | `0x1c4` |
| `func_1515E43C` | `0x108` |
| `func_1515E544` | `0x344` |
| `func_1515E888` | `0x2fc` |
| `func_1515EB84` | `0xf4` |
| `func_1515EC78` | `0x2fc` |
| `func_1515EF74` | `0x94` |
| `func_1515F008` | `0x38` |
| `func_1515F040` | `0x6c` |
| `func_1515F0AC` | `0x60` |
| `func_1515F10C` | `0x64` |
| `func_1515F170` | `0x40` |
| `func_1515F1B0` | `0xac` |
| `func_1515F25C` | `0x14` |
| `func_1515F270` | `0x48` |
| `func_1515F2B8` | `0x30` |
| `func_1515F2E8` | `0x50` |
| `func_1515F338` | `0x28c` |
| `func_1515F5C4` | `0x28c` |
| `func_1515F850` | `0x320` |
| `func_1515FB70` | `0x24` |
| `func_1515FB94` | `0x30` |
| `func_1515FBC4` | `0x70` |
| `func_1515FC34` | `0x2c` |
| `func_1515FC60` | `0x140` |

### `src/game/game_1AC2F0.c`

Range SHA-1: `16c79931f203be341ef1be63fb1c935ed6ff3161`. Spans below include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1517EE40` | `0xc0` |
| `func_1517EF00` | `0xac` |
| `func_1517EFAC` | `0x30` |
| `func_1517EFDC` | `0xb0` |
| `func_1517F08C` | `0x314` |
| `func_1517F3A0` | `0x6c` |
| `func_1517F40C` | `0x3c` |
| `func_1517F448` | `0x40` |
| `func_1517F488` | `0x50` |
| `func_1517F4D8` | `0x8c` |
| `func_1517F564` | `0x1bc` |
| `func_1517F720` | `0x3c` |
| `func_1517F75C` | `0x58` |
| `func_1517F7B4` | `0x60` |
| `func_1517F814` | `0x1e0` |
| `func_1517F9F4` | `0x1a8` |
| `func_1517FB9C` | `0x9e4` |
| `func_15180580` | `0xf7c` |
| `func_151814FC` | `0x7cc` |
| `func_15181CC8` | `0x38` |
| `func_15181D00` | `0x70` |
| `func_15181D70` | `0x58` |
| `func_15181DC8` | `0x50` |
| `func_15181E18` | `0xc8` |
| `func_15181EE0` | `0x790` |
| `func_15182670` | `0xd8` |
| `func_15182748` | `0x20` |
| `func_15182768` | `0x68` |

### `src/game/game_1ED0F0.c`

Range SHA-1: `8e44bf77469dcca6d10eea033897fc12566c49b1`. Spans below include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_151BFC40` | `0x160` |
| `func_151BFDA0` | `0xe4` |
| `func_151BFE84` | `0x214` |
| `func_151C0098` | `0x24c` |
| `func_151C02E4` | `0x7c` |
| `func_151C0360` | `0xb8` |
| `func_151C0418` | `0xe0` |
| `func_151C04F8` | `0xac` |
| `func_151C05A4` | `0x4c` |
| `func_151C05F0` | `0x54` |
| `func_151C0644` | `0x54` |
| `func_151C0698` | `0xa74` |
| `func_151C110C` | `0x74` |
| `func_151C1180` | `0x3f0` |
| `func_151C1570` | `0x8c` |
| `func_151C15FC` | `0x2c` |
| `func_151C1628` | `0x2c` |
| `func_151C1654` | `0x144` |
| `func_151C1798` | `0x7c` |
| `func_151C1814` | `0x4c` |
| `func_151C1860` | `0xe0` |
| `func_151C1940` | `0x2c` |
| `func_151C196C` | `0x3f0` |
| `func_151C1D5C` | `0x25c` |
| `func_151C1FB8` | `0x98` |
