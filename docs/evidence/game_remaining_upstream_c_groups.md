# Further US game helper and callback C-group boundaries

Evidence type: `structural_analysis`

This batch reviews nineteen remaining C groups from the pinned upstream map:
263 recovered raw entries and 95,136 bytes. They receive generic offset-based
working filenames. These are educated source-group hypotheses; an original
linker map, original translation-unit symbols and original filenames have not
been recovered. All bodies remain raw assembly, with no upstream C imported.

## Inputs and range review

The local upstream input is `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924`, specifically its
[US map](https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml).
The combined offsets become game offsets after subtracting `0x2D4B0`.
The complete owned retail image SHA-1 is
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Callback references were read
from its initialized game data (base `80082B20`, SHA-1
`42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`). The beta correlations below
come from the existing hash-validated `./conker beta-index` cache and are
corroboration only; repeated tiny bodies often have weak fingerprints.

| Working source | Combined range | Game range | Raw entries | Bytes | Debug (strong) | ECTS (strong) |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| `game_30E90.c` | `0x30E90:0x32200` | `0x39E0:0x4D50` | 8 | 4,976 | 7 (6) | 0 (0) |
| `game_45B80.c` | `0x45B80:0x476D0` | `0x186D0:0x1A220` | 16 | 6,992 | 7 (6) | 0 (0) |
| `game_6E240.c` | `0x6E240:0x6E770` | `0x40D90:0x412C0` | 4 | 1,328 | 4 (3) | 4 (3) |
| `game_70200.c` | `0x70200:0x71240` | `0x42D50:0x43D90` | 16 | 4,160 | 13 (11) | 12 (10) |
| `game_71240.c` | `0x71240:0x71770` | `0x43D90:0x442C0` | 6 | 1,328 | 6 (6) | 6 (6) |
| `game_75FC0.c` | `0x75FC0:0x76710` | `0x48B10:0x49260` | 10 | 1,872 | 10 (7) | 10 (7) |
| `game_A9D90.c` | `0xA9D90:0xAB760` | `0x7C8E0:0x7E2B0` | 15 | 6,608 | 8 (1) | 8 (1) |
| `game_BC510.c` | `0xBC510:0xC1D70` | `0x8F060:0x948C0` | 18 | 22,624 | 11 (11) | 4 (0) |
| `game_C8950.c` | `0xC8950:0xC98F0` | `0x9B4A0:0x9C440` | 17 | 4,000 | 10 (9) | 6 (4) |
| `game_CB1C0.c` | `0xCB1C0:0xCB3D0` | `0x9DD10:0x9DF20` | 8 | 528 | 6 (2) | 1 (0) |
| `game_DBA60.c` | `0xDBA60:0xDC360` | `0xAE5B0:0xAEEB0` | 8 | 2,304 | 4 (2) | 0 (0) |
| `game_EF410.c` | `0xEF410:0xF15D0` | `0xC1F60:0xC4120` | 18 | 8,640 | 14 (10) | 8 (6) |
| `game_130CB0.c` | `0x130CB0:0x1312F0` | `0x103800:0x103E40` | 5 | 1,600 | 5 (4) | 5 (4) |
| `game_131F30.c` | `0x131F30:0x133190` | `0x104A80:0x105CE0` | 11 | 4,704 | 6 (4) | 3 (0) |
| `game_15B200.c` | `0x15B200:0x15B5F0` | `0x12DD50:0x12E140` | 2 | 1,008 | 2 (2) | 2 (2) |
| `game_1765E0.c` | `0x1765E0:0x176A00` | `0x149130:0x149550` | 12 | 1,056 | 10 (4) | 6 (4) |
| `game_1897A0.c` | `0x1897A0:0x18A8F0` | `0x15C2F0:0x15D440` | 8 | 4,432 | 7 (7) | 2 (0) |
| `game_1FFF60.c` | `0x1FFF60:0x200930` | `0x1D2AB0:0x1D3480` | 19 | 2,512 | 14 (9) | 13 (7) |
| `game_2062D0.c` | `0x2062D0:0x209B50` | `0x1D8E20:0x1DC6A0` | 62 | 14,464 | 59 (33) | 33 (11) |

## Observed grouping relationships

### `game_30E90.c`

The opening `150039E0` allocates and initializes shared state and directly calls the late helpers `15004BF0`, `15004AAC` and `15004CE0`. `150045C4` calls `15004A4C`. The routines repeatedly access `D_800DBEF0`, `D_800DBF00` and `D_800DBEF4`. The final helper scans a byte stream using explicit sentinel values. The unreferenced return sequence at `150045BC` remains in its preceding raw span.

### `game_45B80.c`

The entry `150186D0` performs setup and repeatedly calls `1501878C`; that dispatcher calls `1501905C`, `15019414`, `150198FC`, `15019E60`, `15019BB8`, `15019CC8`, `150195A0`, `15018F80`, `15019464` and `15019130`. `1501905C` calls the final `15019F20`. State references recur at `D_800BEAC0`, `D_800BE9C0`, `D_800BE628` and `D_800BE5E0`. The existing raw reference correctly labels the nontrivial opening setup routine even though the beta function index omits that separate entry; this batch preserves all sixteen raw labels.

### `game_6E240.c`

The two substantive middle routines at `15040D9C` and `15040FCC` share `D_8002AAE8`, `D_800BE9C0`, `D_800BE9C4`, `D_800BE620` and neighboring view state. Each is a complete standalone body without external calls. The range also retains the opening argument-store/return stub and closing counted busy loop. All four entries correlate with both beta images, three strongly. The weaker relationship of these two tiny edge helpers is retained as a limit of the upstream working C boundary; no semantic filename is assigned.

### `game_70200.c`

The opening reset `15042D50` calls `15043384`; the next pair `15042D94`/`15042E3C` both call `15042ECC`. The later group reuses `15043A20`, `15043AC8` and `15043B70`. Shared runtime state includes `800CBD64`, `800CBD72`, `800CBD74` and `800CBD80`. This is a connected state/helper group with long nontrivial debug and ECTS correlations.

### `game_71240.c`

Six related matrix/numeric helpers share a consistent operation family. The first two call `150A8050` and `150A7790`; `15043EC8` writes float matrix components, `15043F6C` calls `150A9B0C`, `15043FF0` converts packed halfwords with a floating scaling constant, and the final `150440A0` calls `10026530` three times. All six bodies strongly correlate with both beta versions. No exact SDK object identity is inferred from their use of math helpers; this remains a generic working source group.

### `game_75FC0.c`

Repeated table/constant references include `D_80085FD0`, `D_80085FE4`, `D_80099020` and `D_80099038`. `15048FC8` calls the earlier `15048C30`, and the closing `150491EC` calls adjacent `1504917C`. All ten functions correlate with both beta versions, seven strongly in each. These relationships corroborate the existing ten-function C grouping without an original filename claim.

### `game_A9D90.c`

The opening `1507C8FC` repeatedly calls `1507D4F8` and also calls `1507CD0C` and the closing `1507E1D0`. `1507CD64` calls the first `1507C8E0`; later `1507D754` repeatedly calls `1507CD64`. Shared state includes `800D18A8`, `800BE616`, `800BE9F0`, `8008FD8C` and `800CC2D0`. The three unreferenced return sequences at `1507DB34`, `1507DB3C` and `1507DB64` remain intact in existing raw spans rather than gaining speculative symbol identities.

### `game_BC510.c`

The setup `1508F060` clears state at `800D246D` and `800D247D`. The next dispatcher `1508F0A4` calls `1508F0D4`, `1508F9F4` and `1509093C`; later members reuse `15091534`, `1508F9C4`, `1508F7BC`, `150916B4` and the final large `15093B58`. There are twenty direct intra-range call sites and repeated references to `D_800D24C8`, `D_8008FDC0`, `D_800BE628` and `D_80082FA0`. Eleven complete functions strongly correlate with debug; the four ECTS candidates are weaker. This supports the substantial shared-state group, while allowing finer historical subdivisions.

### `game_C8950.c`

The opening `1509B4A0` calls both late helpers `1509C120` and `1509C3A0`, plus `1509B5AC`. The group repeatedly uses `D_800D2E4C`, `D_800D2F48` and `D_800D2F60`; the final `1509C414` reads the same root state. Multiple routines reuse `1509B704`, `1509B764`, `1509C228` and `1509BFB0`, giving seventeen intra-range calls across the group.

### `game_CB1C0.c`

This compact group contains related callback defaults and short active handlers. Retail tables contain eight pointers to its members, including `1509DD50` at `8008843C`, `1509DDC4` at `80088478`, `1509DEC4` at `800884B4`, and short defaults `1509DD30`/`1509DD40` at `800886AC`/`800886D8`. Several identical short bodies explain the weak beta correlations. The table context, full span and prior C map support the family; return-byte equality alone does not.

### `game_DBA60.c`

The callbacks share selected state at `D_800D2E4C`, `D_800886E0`, `D_800886E4` and `D_800BE9E4`. Retail tables select the opening `150AE5B0` at `80089678`, `150AEDD8` at `80089C80`, `150AED9C` at `8008A400`, and paired helpers `150AECCC`/`150AED4C` at `8008C9F0/8008C9F4`. There are seven pointers to members. No direct intra-range call relationship is invented; this is a callback-group hypothesis with limited beta corroboration.

### `game_EF410.c`

Twelve retail table pointers select members across this descriptor/helper range, including repeated `150C3994` at `80086060/80086064`, `150C3574` at `80086074`, and paired earlier routines `150C2558`/`150C2700` at `8008AA04/8008AA0C`. `150C3994` calls the closing `150C3D5C`, which calls `150C3D48`. Repeated state references include `D_800CC2D0`, `D_800D1580` and `D_800BE9A4`.

### `game_130CB0.c`

All five routines use the small shared state pair `D_800D9AB0`/`D_800D9AB4`, with repeated time-step reads at `D_800BE9E4`. The opening routine initializes through the first global, and the final `15103C14` is part of the same state family. All five correlate with both beta images, four strongly. Direct internal calls are absent, so the shared state and conserved order provide the grouping corroboration.

### `game_131F30.c`

Eight retail table pointers select this callback family, including `1510550C` at `80088C40`, adjacent callbacks `15104C44`/`151050B0` at `8008A5D8/8008A5DC`, `15105848` at `8008A994`, and `1510558C` at `8008FBE4`. `15105848` directly calls neighboring `151058B4`; the final `15105C24` traverses the shared allocation/list storage at `800DCE50`. The beta evidence is partial, and no original filename is asserted.

### `game_15B200.c`

The first routine reads signed halfword components at object `+0x70C`, `+0x70E` and `+0x710` and calls `150AD930`. The second uses the same large object, including float fields at `+0x874` and `+0x2BC`, and calls `150495B0` five times. Both complete bodies strongly correlate with both beta images. The recorded two-function C group is retained as a working large-object helper boundary.

### `game_1765E0.c`

The constructor `15149130` allocates through the reviewed lifecycle helper `15167A68`, while `151491F4` calls that constructor. The removal path `15149264` calls `1516972C`; paired wrappers `1514933C` and `15149368` call common helper `15149318` then `15169804`/`15169824`. The final wrappers call `15169260` and `15169850`. This forms a coherent construction/update/removal family. The upstream `game/done/` placement is discarded: all twelve members are registered raw, with no copied C or completion credit.

### `game_1897A0.c`

Retail tables select `1515C388`, `1515C534` and `1515C6F4` at `8008A220`, `8008A25C` and `8008A2C4`, plus `1515CF9C` and `1515D030` at `8008B084` and `8008B088`. The code itself uses table addresses `8008B080/8008B084`, alongside time-step and position state. Seven of the eight functions strongly correlate with the debug image. These descriptor/callback relationships corroborate the complete working range without importing a semantic source name.

### `game_1FFF60.c`

The group connects constructors, callback wrappers and late helpers: `151D2BA4` calls `151D3308`, `151D2DAC` calls `151D3354`, and paired wrappers `151D2DCC`/`151D2E14` call `151D2DAC`. Other members reuse `151D3130`. Nine retail table pointers include `151D2C40`, `151D2E5C`, `151D2DCC`, `151D3220` and the late `151D33B8` at `8008FC54`. Shared state includes `D_800E0950`, `D_800E0990` and `D_8008FC48`.

### `game_2062D0.c`

This larger callback group has 51 retail member pointers, including paired `151D93F4`/`151D9450` at `800897E4/800897E8`, `151DB97C` at `80089774`, and later `151DB068`/`151DB4CC` at `8008FD64/8008FD68`. `151D93F4` calls `151D9450` and `151D9534`; the latter calls reused helpers `151DAB58` and `151D9B8C`. Other members reuse `151D9FC0`. Shared state/constants recur at `D_800A5480`, `D_800AB330` and `D_8008FCD0`. Fifty-nine of 62 functions correlate with debug, 33 strongly, supporting conserved family order while leaving original finer subdivisions uncertain.

## Control flow, complete membership and limits

Every word in each proposed range was compared directly with the owned retail
image, verifying contiguous offsets and corresponding runtime addresses. The
regenerated raw spans cover all bytes exactly, with no omitted data labels.
No conditional branch crosses any proposed endpoint in either direction.
Every range closes after a returning routine and padding. Each preceding
range also terminates before the split: the special predecessor of
`game_45B80.c` ends with `jr $s4` at `0x186C0`, followed by its delay slot
and padding, while the other surveyed predecessors end with `jr $ra`.
That nonstandard predecessor is not imported as C in this batch.

The independent beta index omits the separate `150186D0` entry despite its
nontrivial prologue, startup calls and internal dispatcher loop; the canonical
raw reference includes it and all sixteen raw members are retained. Conversely,
the beta index proposes four unreferenced return-only entries in these groups:
`150045BC`, `1507DB34`, `1507DB3C` and `1507DB64`. Their exact words remain
in the prior raw spans and do not gain separate function-identity claims.
The membership spans below use the raw reference, including retained return
sequences and final padding, rather than silently dropping the discrepant bytes.

The older raw filenames `game_3BFD0` and `game_1765E0` explain why an initial
numeric-file lookup missed those ranges. The latter has twelve substantial
related members and is reviewed here. The isolated sixteen-byte `game_3BFD0`
was later assigned to its existing same-named source path after its exact C
match and adjacent reviewed endpoints supplied the missing integration evidence;
see `docs/evidence/game_reconciled_named_singleton_3bfd0.md`. This distinction
does not import upstream completion status.

Runtime relationships, conserved order and the prior explicit C grouping
support working boundaries together; neither padding alignment nor successful
integration alone establishes historical source ownership. The smallest and
most weakly corroborated groups retain that uncertainty explicitly above.
No data, rodata or BSS allocation is assigned. The two residual upstream
libultra-shaped math ranges are excluded from this game-source batch.

## Registration and integration

Use the supported `./conker register-source-unit --overlay game
--register-members` command with this note for each range, then require
`./conker progress integrate --profile us --all-reviewed` to pass the complete
US overlay comparison. Every new member remains `raw_asm`.

The first nineteen-group integration attempt passes. The complete
2,072,880-byte US overlay remains byte-identical with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 170 Python tests pass,
as do generated progress and whitespace checks. The named-split regression
expectation was updated for the newly integrated `game_1765E0` path and now
also checks that its comparison split stays raw. The inventory contains
1,913 functions and 173 source units, including 171 reviewed boundaries.

## Raw hashes and complete recovered membership

### `game_30E90.c`

Range SHA-1: `75daf57e350586e30bf7af7021f6092bfa12bbb5`.

| US member | Recovered raw span |
| --- | ---: |
| `func_150039E0` | `0xb94` |
| `func_15004574` | `0x50` |
| `func_150045C4` | `0x3e0` |
| `func_150049A4` | `0xa8` |
| `func_15004A4C` | `0x60` |
| `func_15004AAC` | `0x144` |
| `func_15004BF0` | `0xf0` |
| `func_15004CE0` | `0x70` |

### `game_45B80.c`

Range SHA-1: `1343050af8caedab4ab4c6ed0f623f3ce3784555`.

| US member | Recovered raw span |
| --- | ---: |
| `func_150186D0` | `0xbc` |
| `func_1501878C` | `0x670` |
| `func_15018DFC` | `0x8c` |
| `func_15018E88` | `0x80` |
| `func_15018F08` | `0x78` |
| `func_15018F80` | `0xdc` |
| `func_1501905C` | `0xd4` |
| `func_15019130` | `0x2e4` |
| `func_15019414` | `0x50` |
| `func_15019464` | `0x13c` |
| `func_150195A0` | `0x35c` |
| `func_150198FC` | `0x2bc` |
| `func_15019BB8` | `0x110` |
| `func_15019CC8` | `0x198` |
| `func_15019E60` | `0xc0` |
| `func_15019F20` | `0x300` |

### `game_6E240.c`

Range SHA-1: `b9f6374af6be12ad5e5d48ed199dda4216e719ab`.

| US member | Recovered raw span |
| --- | ---: |
| `func_15040D90` | `0xc` |
| `func_15040D9C` | `0x230` |
| `func_15040FCC` | `0x2d0` |
| `func_1504129C` | `0x24` |

### `game_70200.c`

Range SHA-1: `a62b68ba277e9d5cdf0f88e02e0dd93d6e5a8409`.

| US member | Recovered raw span |
| --- | ---: |
| `func_15042D50` | `0x28` |
| `func_15042D78` | `0x1c` |
| `func_15042D94` | `0xa8` |
| `func_15042E3C` | `0x90` |
| `func_15042ECC` | `0x3f0` |
| `func_150432BC` | `0x10` |
| `func_150432CC` | `0x30` |
| `func_150432FC` | `0x30` |
| `func_1504332C` | `0x58` |
| `func_15043384` | `0x67c` |
| `func_15043A00` | `0x20` |
| `func_15043A20` | `0xa8` |
| `func_15043AC8` | `0xa8` |
| `func_15043B70` | `0x48` |
| `func_15043BB8` | `0xec` |
| `func_15043CA4` | `0xec` |

### `game_71240.c`

Range SHA-1: `33c4272755657fe212db484fddf97166842240d2`.

| US member | Recovered raw span |
| --- | ---: |
| `func_15043D90` | `0xd8` |
| `func_15043E68` | `0x60` |
| `func_15043EC8` | `0xa4` |
| `func_15043F6C` | `0x84` |
| `func_15043FF0` | `0xb0` |
| `func_150440A0` | `0x220` |

### `game_75FC0.c`

Range SHA-1: `f40ebf55dbcd9afb9208634faf69717c9d483405`.

| US member | Recovered raw span |
| --- | ---: |
| `func_15048B10` | `0x120` |
| `func_15048C30` | `0x2f0` |
| `func_15048F20` | `0x38` |
| `func_15048F58` | `0x38` |
| `func_15048F90` | `0x38` |
| `func_15048FC8` | `0xe0` |
| `func_150490A8` | `0xa0` |
| `func_15049148` | `0x34` |
| `func_1504917C` | `0x70` |
| `func_150491EC` | `0x74` |

### `game_A9D90.c`

Range SHA-1: `eac933934eb73765535fc39951194337d6c5085d`.

| US member | Recovered raw span |
| --- | ---: |
| `func_1507C8E0` | `0x1c` |
| `func_1507C8FC` | `0x410` |
| `func_1507CD0C` | `0x58` |
| `func_1507CD64` | `0x3f4` |
| `func_1507D158` | `0x80` |
| `func_1507D1D8` | `0x320` |
| `func_1507D4F8` | `0x25c` |
| `func_1507D754` | `0x3f0` |
| `func_1507DB44` | `0x28` |
| `func_1507DB6C` | `0x2e0` |
| `func_1507DE4C` | `0xc4` |
| `func_1507DF10` | `0xd4` |
| `func_1507DFE4` | `0x130` |
| `func_1507E114` | `0xbc` |
| `func_1507E1D0` | `0xe0` |

### `game_BC510.c`

Range SHA-1: `d0905e238f19915f5833d8b8d8eb5b6b3cd7a414`.

| US member | Recovered raw span |
| --- | ---: |
| `func_1508F060` | `0x44` |
| `func_1508F0A4` | `0x30` |
| `func_1508F0D4` | `0x6e8` |
| `func_1508F7BC` | `0x208` |
| `func_1508F9C4` | `0x30` |
| `func_1508F9F4` | `0x344` |
| `func_1508FD38` | `0x3b8` |
| `func_150900F0` | `0x540` |
| `func_15090630` | `0x30c` |
| `func_1509093C` | `0x8b8` |
| `func_150911F4` | `0x340` |
| `func_15091534` | `0x180` |
| `func_150916B4` | `0x238` |
| `func_150918EC` | `0x1f2c` |
| `func_15093818` | `0x60` |
| `func_15093878` | `0x44` |
| `func_150938BC` | `0x29c` |
| `func_15093B58` | `0xd68` |

### `game_C8950.c`

Range SHA-1: `a02ebaddc8f611c4d832538ab07f2ea0b902f9d1`.

| US member | Recovered raw span |
| --- | ---: |
| `func_1509B4A0` | `0xd0` |
| `func_1509B570` | `0x3c` |
| `func_1509B5AC` | `0x158` |
| `func_1509B704` | `0x60` |
| `func_1509B764` | `0xac` |
| `func_1509B810` | `0xec` |
| `func_1509B8FC` | `0x54` |
| `func_1509B950` | `0xb4` |
| `func_1509BA04` | `0x19c` |
| `func_1509BBA0` | `0x2a0` |
| `func_1509BE40` | `0x170` |
| `func_1509BFB0` | `0x170` |
| `func_1509C120` | `0x108` |
| `func_1509C228` | `0x7c` |
| `func_1509C2A4` | `0xfc` |
| `func_1509C3A0` | `0x74` |
| `func_1509C414` | `0x2c` |

### `game_CB1C0.c`

Range SHA-1: `f90b02475457c79c3de83902d87627273799110a`.

| US member | Recovered raw span |
| --- | ---: |
| `func_1509DD10` | `0x10` |
| `func_1509DD20` | `0x10` |
| `func_1509DD30` | `0x10` |
| `func_1509DD40` | `0x10` |
| `func_1509DD50` | `0x74` |
| `func_1509DDC4` | `0x38` |
| `func_1509DDFC` | `0xc8` |
| `func_1509DEC4` | `0x5c` |

### `game_DBA60.c`

Range SHA-1: `b1ff87bf9bab54665d331b2592cc024cec760223`.

| US member | Recovered raw span |
| --- | ---: |
| `func_150AE5B0` | `0x1e0` |
| `func_150AE790` | `0x40c` |
| `func_150AEB9C` | `0x130` |
| `func_150AECCC` | `0x80` |
| `func_150AED4C` | `0x50` |
| `func_150AED9C` | `0x3c` |
| `func_150AEDD8` | `0x20` |
| `func_150AEDF8` | `0xb8` |

### `game_EF410.c`

Range SHA-1: `3a0d9023511a06cf4acf8ebee0075888c9d30dd5`.

| US member | Recovered raw span |
| --- | ---: |
| `func_150C1F60` | `0x330` |
| `func_150C2290` | `0x194` |
| `func_150C2424` | `0xf8` |
| `func_150C251C` | `0x3c` |
| `func_150C2558` | `0x1a8` |
| `func_150C2700` | `0x104` |
| `func_150C2804` | `0x94` |
| `func_150C2898` | `0x158` |
| `func_150C29F0` | `0x210` |
| `func_150C2C00` | `0x3cc` |
| `func_150C2FCC` | `0xc0` |
| `func_150C308C` | `0xd4` |
| `func_150C3160` | `0xd0` |
| `func_150C3230` | `0x344` |
| `func_150C3574` | `0x420` |
| `func_150C3994` | `0x3b4` |
| `func_150C3D48` | `0x14` |
| `func_150C3D5C` | `0x3c4` |

### `game_130CB0.c`

Range SHA-1: `45af8a2926fae6fcf733621a17bfc5afd984fe17`.

| US member | Recovered raw span |
| --- | ---: |
| `func_15103800` | `0x28` |
| `func_15103828` | `0xe8` |
| `func_15103910` | `0x190` |
| `func_15103AA0` | `0x174` |
| `func_15103C14` | `0x22c` |

### `game_131F30.c`

Range SHA-1: `e632c0876eb7941b762c27d24b848607e7f76f53`.

| US member | Recovered raw span |
| --- | ---: |
| `func_15104A80` | `0x1c4` |
| `func_15104C44` | `0x3b4` |
| `func_15104FF8` | `0xb8` |
| `func_151050B0` | `0x45c` |
| `func_1510550C` | `0x3c` |
| `func_15105548` | `0x44` |
| `func_1510558C` | `0x2bc` |
| `func_15105848` | `0x6c` |
| `func_151058B4` | `0x314` |
| `func_15105BC8` | `0x5c` |
| `func_15105C24` | `0xbc` |

### `game_15B200.c`

Range SHA-1: `e481cf64b606d7185dd0c24d6df045f64066706a`.

| US member | Recovered raw span |
| --- | ---: |
| `func_1512DD50` | `0x154` |
| `func_1512DEA4` | `0x29c` |

### `game_1765E0.c`

Range SHA-1: `9b29d0c99fbca9e3f6abc79facd11556396d5435`.

| US member | Recovered raw span |
| --- | ---: |
| `func_15149130` | `0xc4` |
| `func_151491F4` | `0x70` |
| `func_15149264` | `0xb4` |
| `func_15149318` | `0x24` |
| `func_1514933C` | `0x2c` |
| `func_15149368` | `0x2c` |
| `func_15149394` | `0x50` |
| `func_151493E4` | `0x50` |
| `func_15149434` | `0x5c` |
| `func_15149490` | `0x50` |
| `func_151494E0` | `0x34` |
| `func_15149514` | `0x3c` |

### `game_1897A0.c`

Range SHA-1: `2b21d8560114ac691a06315a3d0e630357cd661e`.

| US member | Recovered raw span |
| --- | ---: |
| `func_1515C2F0` | `0x98` |
| `func_1515C388` | `0x1ac` |
| `func_1515C534` | `0x1c0` |
| `func_1515C6F4` | `0x8a8` |
| `func_1515CF9C` | `0x94` |
| `func_1515D030` | `0x58` |
| `func_1515D088` | `0xa8` |
| `func_1515D130` | `0x310` |

### `game_1FFF60.c`

Range SHA-1: `8ef5ba65c67de3550c5212c82ee813a5c5af5c60`.

| US member | Recovered raw span |
| --- | ---: |
| `func_151D2AB0` | `0x9c` |
| `func_151D2B4C` | `0x58` |
| `func_151D2BA4` | `0x9c` |
| `func_151D2C40` | `0x16c` |
| `func_151D2DAC` | `0x20` |
| `func_151D2DCC` | `0x48` |
| `func_151D2E14` | `0x48` |
| `func_151D2E5C` | `0xa4` |
| `func_151D2F00` | `0x90` |
| `func_151D2F90` | `0x1a0` |
| `func_151D3130` | `0xc4` |
| `func_151D31F4` | `0x2c` |
| `func_151D3220` | `0x2c` |
| `func_151D324C` | `0xbc` |
| `func_151D3308` | `0x4c` |
| `func_151D3354` | `0x64` |
| `func_151D33B8` | `0x44` |
| `func_151D33FC` | `0x40` |
| `func_151D343C` | `0x44` |

### `game_2062D0.c`

Range SHA-1: `dff8092ba3e4492f9be6ffd829d15290565fe1aa`.

| US member | Recovered raw span |
| --- | ---: |
| `func_151D8E20` | `0x4c` |
| `func_151D8E6C` | `0x44` |
| `func_151D8EB0` | `0xc` |
| `func_151D8EBC` | `0xc` |
| `func_151D8EC8` | `0x34` |
| `func_151D8EFC` | `0x34` |
| `func_151D8F30` | `0x4c` |
| `func_151D8F7C` | `0x34` |
| `func_151D8FB0` | `0xc` |
| `func_151D8FBC` | `0xc` |
| `func_151D8FC8` | `0xc` |
| `func_151D8FD4` | `0xc` |
| `func_151D8FE0` | `0x34` |
| `func_151D9014` | `0x3e0` |
| `func_151D93F4` | `0x5c` |
| `func_151D9450` | `0xe4` |
| `func_151D9534` | `0x274` |
| `func_151D97A8` | `0x78` |
| `func_151D9820` | `0x58` |
| `func_151D9878` | `0x58` |
| `func_151D98D0` | `0x48` |
| `func_151D9918` | `0x48` |
| `func_151D9960` | `0x68` |
| `func_151D99C8` | `0x58` |
| `func_151D9A20` | `0x48` |
| `func_151D9A68` | `0x58` |
| `func_151D9AC0` | `0x1c` |
| `func_151D9ADC` | `0x58` |
| `func_151D9B34` | `0x58` |
| `func_151D9B8C` | `0x324` |
| `func_151D9EB0` | `0x110` |
| `func_151D9FC0` | `0xcc` |
| `func_151DA08C` | `0x2dc` |
| `func_151DA368` | `0x340` |
| `func_151DA6A8` | `0x50` |
| `func_151DA6F8` | `0x240` |
| `func_151DA938` | `0x150` |
| `func_151DAA88` | `0xd0` |
| `func_151DAB58` | `0x248` |
| `func_151DADA0` | `0x88` |
| `func_151DAE28` | `0x1dc` |
| `func_151DB004` | `0x64` |
| `func_151DB068` | `0x64` |
| `func_151DB0CC` | `0x90` |
| `func_151DB15C` | `0x90` |
| `func_151DB1EC` | `0x90` |
| `func_151DB27C` | `0x2c` |
| `func_151DB2A8` | `0x24` |
| `func_151DB2CC` | `0x64` |
| `func_151DB330` | `0xa8` |
| `func_151DB3D8` | `0x64` |
| `func_151DB43C` | `0x90` |
| `func_151DB4CC` | `0x104` |
| `func_151DB5D0` | `0x3ac` |
| `func_151DB97C` | `0x12c` |
| `func_151DBAA8` | `0x12c` |
| `func_151DBBD4` | `0xe8` |
| `func_151DBCBC` | `0x1c4` |
| `func_151DBE80` | `0x1b4` |
| `func_151DC034` | `0x22c` |
| `func_151DC260` | `0x224` |
| `func_151DC484` | `0x21c` |
