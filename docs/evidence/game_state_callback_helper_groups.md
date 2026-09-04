# US state, callback and shared-helper source groups

Evidence type: `structural_analysis`

These five working source units use offset-derived navigation names from the
pinned upstream US C split map. They are educated structural boundary
hypotheses, not recovered original filenames or original object symbols.
The complete membership is kept as raw ASM; no upstream C implementation,
type, function name or completion status is imported.

## Inputs and reviewed ranges

The local upstream checkout is `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924`; its
[US split map](https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml)
provides independently recorded C group endpoints. Subtracting `0x2D4B0`
converts its combined offsets to game-overlay offsets.
The retail code image SHA-1 is
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
Cached `./conker beta-index` correlations use the hash-validated debug and
ECTS images recorded in `game_beta_sight.md`. Their fingerprints are
corroboration of related instruction sequences, never US matching evidence.

| Working source | Combined range | Game range | Members | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| `game_83300.c` | `0x83300:0x90840` | `0x55E50:0x63390` | 89 | 54,592 | 63 (50) | 53 (41) |
| `game_168A90.c` | `0x168A90:0x169510` | `0x13B5E0:0x13C060` | 13 | 2,688 | 11 (5) | 11 (5) |
| `game_16DC80.c` | `0x16DC80:0x16EE20` | `0x1407D0:0x141970` | 16 | 4,512 | 10 (8) | 7 (6) |
| `game_16EE20.c` | `0x16EE20:0x173D40` | `0x141970:0x146890` | 89 | 20,256 | 83 (78) | 72 (66) |
| `game_1944C0.c` | `0x1944C0:0x196DB0` | `0x167010:0x169900` | 42 | 10,480 | 24 (19) | 16 (12) |

## Evidence beyond alignment

### `game_83300.c`

This range has 167 direct intra-range JAL call sites. The central dispatcher
`func_15059140` invokes the opening three helpers and the later update groups
at `15056B08`, `1505B5F8` and `1505C7D8`. The latter update path reaches
`1505C1E4`, `1505B9C4` and the small state helper `1505C1A4`.
The later `15060F28` cleanup/reset path is called from several earlier and
later members, including the final `15063254` routine. This connectivity
spans the proposed range rather than merely a compact adjacent pair.
Repeated references to `D_800CC2D0`, `D_800C3E78`, `D_800D2104` and
`D_800D1550` establish shared runtime state. Numerous floating constant
references progress through the `80099438:80099694` area; this is a use
observation, not a claim to own that data region.

### `game_168A90.c`

The opening constructor allocates through `func_15167A68`, copies a
`0x3C`-byte descriptor, and initializes paired buffers and fields at object
`+0x4C`, `+0x50`, `+0x54`, `+0x58` and `+0x68`.
The following update/draw wrappers dispatch using signed byte fields at
`+0x11` and `+0x12` through tables `80089C18` and `80089C28`.
Independent reads of the retail initialized data confirm entries for
`1513BEB0`, `1513B968`, `1513BAD4`, `1513BBFC`, `1513B9A8` and `1513B9DC`
in `80089C20:80089C60`. Two additional callback records include the paired
wrappers `1513B798` and `1513B83C` at `8008C008/8008C010` and
`8008C5B8/8008C5C0`. The later `1513BAE8` directly invokes the opening
constructor. These are related construction, callback and buffer helpers;
the tables remain unmapped data.

### `game_16DC80.c`

The opening `151407D0` constructor and later wrappers share `D_800DC9F0`.
The large `151408A4` routine uses callback table `80089F90` and the math
helpers in the following group. Retail data confirms callback pointers to
members throughout the range: `151408A4` at `80089E20`, `151411E4` at
`80089F04`, `15141250` at `80089F38`, and `151416E8` at `80089F74`.
Repeated entries beginning at `80089F9C` select `151411A4`; its neighboring
wrapper `151411C4` calls the paired external routine `1513CAA0` while
`151411A4` calls `1513CA6C`. The final `15141928` wrapper calls `1514182C`.
This supports a related callback/helper grouping but does not prove that
all callbacks belonged to one historical file.

### `game_16EE20.c`

The range begins with a base wrapper `15141970` and two direct callers.
The initial setup path `15141A7C` calls `15141C0C`, `15141CC0` and
`15141E38`, sharing tables at `8008A084` and `8008A0B4` with `15141DA4`.
Later portions contain closely coupled numeric and transform helpers:
`151432BC`, `15143794`, `15143874` and `1514470C` repeatedly call
`151423D8`; `15144C8C` and `151454BC` call the small `15144B68` and
`15144B34` helpers. The late `15146078` routine calls `151450B4` and
`15145128`, while `1514654C` calls `15145EA4` near the closing boundary.
There are 42 direct intra-range call sites. Debug and ECTS correlations
cover most members, including long runs of nontrivial routines; identical
short wrappers are treated as weaker evidence. The several helper clusters
could represent finer historical subdivisions. None is invented here.

### `game_1944C0.c`

This group contains a coherent allocation/list/callback lifecycle. The
opening iteration routines and later removal paths repeatedly access
`D_800DCE50`, `D_800DD190`, `D_800DD198` and table `D_8008B4A8`.
`15167A68` allocates via `10003C6C` and links through `15168A4C`;
`15167AD8`, `15167D84`, `15168800` and `15168BE4` call that allocator.
`15168B10` combines unlink/relink helpers `15168A9C` and `15168A4C`.
Late cleanup routines `1516972C` and `1516979C` call the shared removal
helper `151696DC` and the neighboring finalizers `15169804`/`15169824`.
Retail data confirms 17 member pointers, including `15169824` at
`8008B4A8` and update callbacks `15167B44`, `15167E0C`, `15168870` and
`15168BAC`. Earlier newly mapped groups call these allocation and cleanup
entry points. These uses do not transfer ownership of the callback tables.

## Complete range checks and limits

Every raw instruction word in all five ranges was compared with the owned
retail image, checking contiguous offsets and corresponding runtime addresses.
All top-level function labels agree in order with the independent US function
index. No conditional branch crosses any proposed endpoint in either direction.
Each preceding range returns before padding; each proposed unit returns before
its final padding, and the next range starts with a fresh stack prologue.
No data labels or interior instructions are omitted from the proposed units.

The upstream C grouping, complete label recovery, runtime relationships and
cross-build order together support these working boundaries. Alignment and
byte-identical integration alone would not establish original ownership.
The numeric source names deliberately preserve the uncertainty about original
filenames. No initialized data, rodata or BSS allocation is assigned.

## Registration and validation

Register each range using `./conker register-source-unit --overlay game
--register-members` and this note as the evidence reference. Integrate the
reviewed units through `./conker progress integrate --profile us
--all-reviewed`; the complete US overlay comparison is the integration gate.
All new members remain `raw_asm`, irrespective of a successful full build.

The first integration attempt passes for all five units. The full 2,072,880-byte
US overlay remains byte-identical with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 170 Python tests pass;
generated progress and whitespace checks pass. The inventory now has 791
functions and 137 source units, including 135 reviewed boundaries.

## Raw range hashes and complete membership

### `game_83300.c`

Range SHA-1: `b01ad115578cdd2e88a04b839753b0138140d5bb`.

| US member | Function-index span |
| --- | ---: |
| `func_15055E50` | `0x300` |
| `func_15056150` | `0x108` |
| `func_15056258` | `0xA4` |
| `func_150562FC` | `0x640` |
| `func_1505693C` | `0xC4` |
| `func_15056A00` | `0x108` |
| `func_15056B08` | `0x1914` |
| `func_1505841C` | `0x1D4` |
| `func_150585F0` | `0x2A8` |
| `func_15058898` | `0x60C` |
| `func_15058EA4` | `0x80` |
| `func_15058F24` | `0x21C` |
| `func_15059140` | `0x284` |
| `func_150593C4` | `0x80` |
| `func_15059444` | `0x158` |
| `func_1505959C` | `0x260` |
| `func_150597FC` | `0x1CC` |
| `func_150599C8` | `0x18C` |
| `func_15059B54` | `0x130` |
| `func_15059C84` | `0x500` |
| `func_1505A184` | `0xCC` |
| `func_1505A250` | `0x158` |
| `func_1505A3A8` | `0x224` |
| `func_1505A5CC` | `0x64` |
| `func_1505A630` | `0xC8` |
| `func_1505A6F8` | `0x34` |
| `func_1505A72C` | `0x44` |
| `func_1505A770` | `0x23C` |
| `func_1505A9AC` | `0xC4C` |
| `func_1505B5F8` | `0x3CC` |
| `func_1505B9C4` | `0x77C` |
| `func_1505C140` | `0x64` |
| `func_1505C1A4` | `0x40` |
| `func_1505C1E4` | `0x5F4` |
| `func_1505C7D8` | `0x84C` |
| `func_1505D024` | `0x1A0` |
| `func_1505D1C4` | `0xF4` |
| `func_1505D2B8` | `0x94` |
| `func_1505D34C` | `0xBC` |
| `func_1505D408` | `0x1C8` |
| `func_1505D5D0` | `0x120` |
| `func_1505D6F0` | `0x3EC` |
| `func_1505DADC` | `0x2CC` |
| `func_1505DDA8` | `0x168` |
| `func_1505DF10` | `0xCC` |
| `func_1505DFDC` | `0x84` |
| `func_1505E060` | `0x64` |
| `func_1505E0C4` | `0x58C` |
| `func_1505E650` | `0x17C` |
| `func_1505E7CC` | `0xA8` |
| `func_1505E874` | `0x4C0` |
| `func_1505ED34` | `0x17C` |
| `func_1505EEB0` | `0x44` |
| `func_1505EEF4` | `0xDC` |
| `func_1505EFD0` | `0xDC` |
| `func_1505F0AC` | `0xDC` |
| `func_1505F188` | `0x110` |
| `func_1505F298` | `0x11C4` |
| `func_1506045C` | `0x31C` |
| `func_15060778` | `0x2B8` |
| `func_15060A30` | `0x6C` |
| `func_15060A9C` | `0x68` |
| `func_15060B04` | `0x6C` |
| `func_15060B70` | `0x34` |
| `func_15060BA4` | `0x3C` |
| `func_15060BE0` | `0x174` |
| `func_15060D54` | `0x1D4` |
| `func_15060F28` | `0x2C0` |
| `func_150611E8` | `0x3F4` |
| `func_150615DC` | `0x30` |
| `func_1506160C` | `0x1B0` |
| `func_150617BC` | `0x1B0` |
| `func_1506196C` | `0x3C` |
| `func_150619A8` | `0x1A4` |
| `func_15061B4C` | `0x8A8` |
| `func_150623F4` | `0x2F8` |
| `func_150626EC` | `0xE8` |
| `func_150627D4` | `0x2C` |
| `func_15062800` | `0x2C4` |
| `func_15062AC4` | `0x58` |
| `func_15062B1C` | `0x34` |
| `func_15062B50` | `0x34` |
| `func_15062B84` | `0x58` |
| `func_15062BDC` | `0x134` |
| `func_15062D10` | `0x114` |
| `func_15062E24` | `0x19C` |
| `func_15062FC0` | `0x1A8` |
| `func_15063168` | `0xEC` |
| `func_15063254` | `0x13C` |

### `game_168A90.c`

Range SHA-1: `c7c3c3b1bb9d366d9eeed0eebddf9993e0866ede`.

| US member | Function-index span |
| --- | ---: |
| `func_1513B5E0` | `0x1B8` |
| `func_1513B798` | `0xA4` |
| `func_1513B83C` | `0x12C` |
| `func_1513B968` | `0x40` |
| `func_1513B9A8` | `0x34` |
| `func_1513B9DC` | `0x34` |
| `func_1513BA10` | `0x34` |
| `func_1513BA44` | `0x34` |
| `func_1513BA78` | `0x5C` |
| `func_1513BAD4` | `0x14` |
| `func_1513BAE8` | `0x114` |
| `func_1513BBFC` | `0x2B4` |
| `func_1513BEB0` | `0x1B0` |

### `game_16DC80.c`

Range SHA-1: `d01d384dcb9d5ff6aa9ee4024f940d516ff86303`.

| US member | Function-index span |
| --- | ---: |
| `func_151407D0` | `0xD4` |
| `func_151408A4` | `0x900` |
| `func_151411A4` | `0x20` |
| `func_151411C4` | `0x20` |
| `func_151411E4` | `0x6C` |
| `func_15141250` | `0x6C` |
| `func_151412BC` | `0x180` |
| `func_1514143C` | `0x3C` |
| `func_15141478` | `0xEC` |
| `func_15141564` | `0x70` |
| `func_151415D4` | `0x114` |
| `func_151416E8` | `0xDC` |
| `func_151417C4` | `0x54` |
| `func_15141818` | `0x14` |
| `func_1514182C` | `0xFC` |
| `func_15141928` | `0x48` |

### `game_16EE20.c`

Range SHA-1: `c5d5f7897f6315482e98210130bce859f240d26b`.

| US member | Function-index span |
| --- | ---: |
| `func_15141970` | `0x20` |
| `func_15141990` | `0x20` |
| `func_151419B0` | `0x20` |
| `func_151419D0` | `0xAC` |
| `func_15141A7C` | `0x190` |
| `func_15141C0C` | `0xB4` |
| `func_15141CC0` | `0xE4` |
| `func_15141DA4` | `0x94` |
| `func_15141E38` | `0x140` |
| `func_15141F78` | `0x180` |
| `func_151420F8` | `0x88` |
| `func_15142180` | `0x140` |
| `func_151422C0` | `0x1C` |
| `func_151422DC` | `0x1C` |
| `func_151422F8` | `0x1C` |
| `func_15142314` | `0xC4` |
| `func_151423D8` | `0x6C` |
| `func_15142444` | `0xB0` |
| `func_151424F4` | `0x10C` |
| `func_15142600` | `0x238` |
| `func_15142838` | `0xDC` |
| `func_15142914` | `0xCC` |
| `func_151429E0` | `0x7C` |
| `func_15142A5C` | `0x24` |
| `func_15142A80` | `0x40` |
| `func_15142AC0` | `0x44` |
| `func_15142B04` | `0x40` |
| `func_15142B44` | `0x38` |
| `func_15142B7C` | `0x94` |
| `func_15142C10` | `0xE0` |
| `func_15142CF0` | `0x134` |
| `func_15142E24` | `0x198` |
| `func_15142FBC` | `0x88` |
| `func_15143044` | `0x28` |
| `func_1514306C` | `0xC8` |
| `func_15143134` | `0x188` |
| `func_151432BC` | `0x3F8` |
| `func_151436B4` | `0x88` |
| `func_1514373C` | `0x58` |
| `func_15143794` | `0xA0` |
| `func_15143834` | `0x40` |
| `func_15143874` | `0x64` |
| `func_151438D8` | `0x440` |
| `func_15143D18` | `0x90` |
| `func_15143DA8` | `0x60` |
| `func_15143E08` | `0x1C` |
| `func_15143E24` | `0x40` |
| `func_15143E64` | `0x30` |
| `func_15143E94` | `0x188` |
| `func_1514401C` | `0x188` |
| `func_151441A4` | `0x158` |
| `func_151442FC` | `0x1E0` |
| `func_151444DC` | `0x4C` |
| `func_15144528` | `0x70` |
| `func_15144598` | `0x94` |
| `func_1514462C` | `0xE0` |
| `func_1514470C` | `0x368` |
| `func_15144A74` | `0x34` |
| `func_15144AA8` | `0x8C` |
| `func_15144B34` | `0x34` |
| `func_15144B68` | `0x60` |
| `func_15144BC8` | `0x64` |
| `func_15144C2C` | `0x60` |
| `func_15144C8C` | `0x60` |
| `func_15144CEC` | `0x194` |
| `func_15144E80` | `0x234` |
| `func_151450B4` | `0x74` |
| `func_15145128` | `0xC8` |
| `func_151451F0` | `0xD4` |
| `func_151452C4` | `0x1F8` |
| `func_151454BC` | `0x8C` |
| `func_15145548` | `0xF4` |
| `func_1514563C` | `0x104` |
| `func_15145740` | `0x234` |
| `func_15145974` | `0x98` |
| `func_15145A0C` | `0x44` |
| `func_15145A50` | `0x88` |
| `func_15145AD8` | `0x1B8` |
| `func_15145C90` | `0x40` |
| `func_15145CD0` | `0xE4` |
| `func_15145DB4` | `0xF0` |
| `func_15145EA4` | `0x1D4` |
| `func_15146078` | `0x250` |
| `func_151462C8` | `0x1F0` |
| `func_151464B8` | `0x50` |
| `func_15146508` | `0x44` |
| `func_1514654C` | `0x1E0` |
| `func_1514672C` | `0x78` |
| `func_151467A4` | `0xEC` |

### `game_1944C0.c`

Range SHA-1: `dd8ec7a6aa63f3b27dae0f00906d38978cbee2d9`.

| US member | Function-index span |
| --- | ---: |
| `func_15167010` | `0x5C` |
| `func_1516706C` | `0x54` |
| `func_151670C0` | `0x128` |
| `func_151671E8` | `0x128` |
| `func_15167310` | `0x1E8` |
| `func_151674F8` | `0x570` |
| `func_15167A68` | `0x70` |
| `func_15167AD8` | `0x6C` |
| `func_15167B44` | `0x114` |
| `func_15167C58` | `0x12C` |
| `func_15167D84` | `0x88` |
| `func_15167E0C` | `0x30C` |
| `func_15168118` | `0x544` |
| `func_1516865C` | `0x1A4` |
| `func_15168800` | `0x70` |
| `func_15168870` | `0x1BC` |
| `func_15168A2C` | `0x20` |
| `func_15168A4C` | `0x50` |
| `func_15168A9C` | `0x74` |
| `func_15168B10` | `0x34` |
| `func_15168B44` | `0x68` |
| `func_15168BAC` | `0x38` |
| `func_15168BE4` | `0x68` |
| `func_15168C4C` | `0x1E8` |
| `func_15168E34` | `0x20` |
| `func_15168E54` | `0xB4` |
| `func_15168F08` | `0x7C` |
| `func_15168F84` | `0xBC` |
| `func_15169040` | `0x30` |
| `func_15169070` | `0x1F0` |
| `func_15169260` | `0x1EC` |
| `func_1516944C` | `0x1A4` |
| `func_151695F0` | `0x3C` |
| `func_1516962C` | `0x3C` |
| `func_15169668` | `0x24` |
| `func_1516968C` | `0x50` |
| `func_151696DC` | `0x50` |
| `func_1516972C` | `0x70` |
| `func_1516979C` | `0x68` |
| `func_15169804` | `0x20` |
| `func_15169824` | `0x2C` |
| `func_15169850` | `0xB0` |

