# Additional early US game-overlay source groups

Evidence type: `structural_analysis`

These are reviewed working boundaries with generic offset-derived names,
not recovered original filenames or exact C matches. Their grouping hypotheses
combine the pinned upstream C map with the independent retail observations
below. No upstream C body, type, semantic symbol or completion claim is copied.

The upstream input is the local `mkst/conker` checkout at
`3adf229175c037c771f251f169f9dd80ca306924`, specifically its
[US map](https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml).
Subtract `0x2D4B0` from combined offsets to obtain game offsets.
The owned retail game image has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Cross-build counts come from
the cached, hash-validated `./conker beta-index` report; weak or identical
short-function fingerprints do not independently identify a source file.

| Working source | Combined range | Game range | Functions | Bytes | Debug (strong) | ECTS (strong) |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| `game_305D0.c` | `0x305D0:0x30E90` | `0x3120:0x39E0` | 9 | 2,240 | 9 (8) | 0 (0) |
| `game_32740.c` | `0x32740:0x32F10` | `0x5290:0x5A60` | 3 | 2,000 | 0 (0) | 0 (0) |
| `game_33990.c` | `0x33990:0x34CE0` | `0x64E0:0x7830` | 18 | 4,944 | 14 (8) | 9 (3) |
| `game_34F20.c` | `0x34F20:0x357F0` | `0x7A70:0x8340` | 6 | 2,256 | 2 (1) | 1 (0) |
| `game_357F0.c` | `0x357F0:0x35CF0` | `0x8340:0x8840` | 1 | 1,280 | 1 (1) | 1 (1) |
| `game_36680.c` | `0x36680:0x39690` | `0x91D0:0xC1E0` | 82 | 12,304 | 82 (28) | 75 (22) |
| `game_39750.c` | `0x39750:0x3B920` | `0xC2A0:0xE470` | 7 | 8,656 | 7 (6) | 2 (2) |
| `game_3BA70.c` | `0x3BA70:0x3BFD0` | `0xE5C0:0xEB20` | 6 | 1,376 | 4 (2) | 2 (0) |
| `game_3DF10.c` | `0x3DF10:0x3E460` | `0x10A60:0x10FB0` | 1 | 1,360 | 1 (1) | 0 (0) |
| `game_40490.c` | `0x40490:0x42DC0` | `0x12FE0:0x15910` | 32 | 10,544 | 28 (25) | 22 (16) |
| `game_44C40.c` | `0x44C40:0x45880` | `0x17790:0x183D0` | 6 | 3,136 | 4 (4) | 1 (0) |
| `game_476D0.c` | `0x476D0:0x487D0` | `0x1A220:0x1B320` | 11 | 4,352 | 9 (9) | 0 (0) |
| `game_57FA0.c` | `0x57FA0:0x58F80` | `0x2AAF0:0x2BAD0` | 15 | 4,064 | 12 (10) | 12 (10) |

## Structural observations

### `game_305D0.c`

The central `150031EC` routine calls the first helper `15003120`, the interior `150034B4`, and the final `150039BC`. The first helper updates the state at `800B0E30/800B0E34`; the final helper installs a nullable pointer at `800DBE5C`, advancing it by eight bytes when present. All nine members correlate with the later debug image, eight strongly.

### `game_32740.c`

The opening `15005290` routine calls its adjacent helper `150054C4`; the group repeatedly uses `D_800BE2B0`. The opening routine allocates several blocks through `10003C40` and calls `1512ABF8` and `1512D238`. The closing `15005818` calls the reviewed camera-range routines `15124B18`, `15125330`, `1512523C` and `15123070`, plus other helpers. No cached beta fingerprint corroborates this group; the retained upstream C split and independently reviewed body relationships are the available evidence.

### `game_33990.c`

This state-reset and update group repeatedly uses `D_800BE358`, `D_800BE900`, `D_80082BB4` and `D_800BE3EC`. Both `15006590` and the late `150076BC` call the opening reset `150064E0`; `1500727C` calls `15007168`. The closing `15007778` writes repeated -1 sentinels at 0x10-byte intervals from `800BE3F8` and resets adjacent state.

### `game_34F20.c`

The opening two routines call the smaller helpers near the closing boundary: `15007A70` calls `15008230`, while `15007B3C` calls `150081E4`, `15008248` and `150082CC`. Repeated reads/writes use `D_800BE9F0`, `D_800BE9F4` and `D_800BE9ED`. This is connected setup/update state, without a recovered original source name.

### `game_357F0.c`

One complete 1,280-byte transform routine occupies the recorded upstream C range. It repeatedly calls the paired helpers `15047D60`/`15047C00`, `10024770` and `150ADA20`, and uses the adjacent constant references beginning at `80095B10`. The whole function has strong debug and ECTS correlations. No interior function or extra historical subdivision is asserted.

### `game_36680.c`

The opening dispatcher `150092DC` calls `15009334`, which calls `1500A94C` and `1500AB5C`. Six later members call the shared `1500AF08` helper; the last `1500BEC0` calls both `1500BE68` and `1500AD84`. The retail initialized-data table beginning at `80082C00` points to the consecutive compact members `150095D8`, `15009600`, `15009628`, `1500969C` and `150096C4`, with repeated slots selecting `15009628`. There are 95 aligned member pointers in the retail data. These corroborate a callback family; identical short callbacks account for many weak correlations and do not establish distinct original names.

### `game_39750.c`

The opening `1500C2A0` resets fields at `800DC460`, `800DC464`, `800DC468`, `800DC46A`, `800DC63A` and `800DC63C`. All six subsequent nontrivial routines appear consecutively in a real retail function-pointer table: `80082F28:80082F3C` holds `1500C2F0`, `1500C8D0`, `1500CE4C`, `1500D3AC`, `1500D8C8`, `1500DE88`. The final callback uses the earlier transform at `15008340`. This callback-table ordering adds independent grouping evidence despite the absence of direct intra-range calls.

### `game_3BA70.c`

The six routines share state at `800DCA20:800DCA2C`. Retail callback entries independently select `1500E8C0` at `80082D94`, `1500E890` at `80082DE4`, and the last `1500EAA0` at `80082E20`. The opening routine resets through the existing `15012470`, `15008A10` and `15012770` helpers; the closing callback emits through two calls to `15195AA8`.

### `game_3DF10.c`

The recorded single-function C group contains one complete 1,360-byte callback with a 0x1D0-byte stack frame. Retail table slot `80082DEC` contains its address `15010A60`. It builds descriptors using repeated `10024770`/`150ADA20` calls, copies them through `10022EC0`, and calls the reviewed constructor `1513B5E0`. Its entire body has a strong later-debug correlation.

### `game_40490.c`

This callback family begins with `15012FE0` clearing `800BE570/800BE574/800BE575`. Retail callback tables contain 31 pointers to members, spread across `80082E3C:80082F70`, including `1501396C`, `1501370C`, `150130B4`, `15015300` and `15015354`. Twenty-eight of the 32 members correlate with debug and 22 with ECTS. There are no direct intra-range calls: the pointer tables and cross-build ordering are the relevant family evidence, not invented call connectivity.

### `game_44C40.c`

The group has a reset entry at `15017790` and an internal chain `15017930` -> `15017B20` -> final helper `15017FA4`. Shared references include `D_800D3094`, `D_800D30B8` and `D_800D2E44`. The last helper repeatedly calls matrix/vector routines at `150A7DA0`, `150A7CB0`, `150A7A48`, `150A8050` and `150A7960`.

### `game_476D0.c`

The first `1501A220` invokes `1501A8C0` twice; that interior routine calls the late helpers `1501AE94`, `1501AF44` and `1501B0A0`. The same state vector is repeatedly accessed through `D_800BE620`, `D_800BE624`, `D_800BE628` and `D_800BE62C`. The final `1501B22C` uses the shared state and paired numeric routines `15047C00`/`15047D60`. Nine of the eleven functions strongly correlate with debug.

### `game_57FA0.c`

Fourteen intra-range call sites connect this resource-handling group: `1502AC88` calls `1502AB04`, `1502B110` calls `1502AF04` and `1502AC88`, and the late `1502B5C8` and final `1502B9B4` also reach `1502AC88`. The routines repeatedly reference state `D_800C3D68`/`D_800C3D60` and a ROM-address constant at `0xAB1950`. The opening return-only member remains generic; its bytes do not identify an SDK object. The substantive later members supply the family evidence.

## Complete-range review and limitations

Every raw assembly word in all thirteen ranges matches the owned retail image,
with contiguous offsets and correct runtime addresses. Top-level labels agree
in order with the separate US function index. No conditional branch enters or
leaves a range across its endpoints. The preceding functions return before
the split, and every proposed range ends after its final return and padding.
There are no omitted data labels or instructions inside a proposed group.

The retail pointer observations above are function-table entries in the
existing initialized game data; their ownership is not assigned to these C
units. Shared state and table relationships corroborate families but do not
prove one historical translation unit. The recorded upstream C endpoints
remain working structural hypotheses. Neither alignment nor a byte-identical
build alone supplies historical ownership evidence. Single-function groups
claim no smaller source subdivision. The generic names retain this uncertainty.

The overlay's first raw group is not promoted in this batch: isolated aligned
words equal to `0x15000000` elsewhere in data are not enough to establish
callback-table references to its first function. Groups with function-index
membership disagreements are handled separately.

## Registration and integration

Use `./conker register-source-unit --overlay game --register-members` with
this note for each range, followed by `./conker progress integrate --profile us
--all-reviewed`. The complete US overlay must remain byte-identical. Every
new inventory member remains `raw_asm` and every source begins as a generated
ordered GLOBAL_ASM skeleton.

The first integration attempt passes for all thirteen units. The full
2,072,880-byte US overlay remains byte-identical with SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 170 Python tests pass, as do
generated progress and whitespace checks. There are now 988 registered
functions and 150 source units, including 148 reviewed boundaries.

## Raw hashes and membership

### `game_305D0.c`

Range SHA-1: `3429310d5307bde6707c50d8f0da3b21068f58ce`.

| US member | Function-index span |
| --- | ---: |
| `func_15003120` | `0xCC` |
| `func_150031EC` | `0x2C8` |
| `func_150034B4` | `0xBC` |
| `func_15003570` | `0xF8` |
| `func_15003668` | `0x238` |
| `func_150038A0` | `0x6C` |
| `func_1500390C` | `0xA4` |
| `func_150039B0` | `0xC` |
| `func_150039BC` | `0x24` |

### `game_32740.c`

Range SHA-1: `a3036a6d23490e79494b23ffa7dc32a67526e927`.

| US member | Function-index span |
| --- | ---: |
| `func_15005290` | `0x234` |
| `func_150054C4` | `0x354` |
| `func_15005818` | `0x248` |

### `game_33990.c`

Range SHA-1: `def193de3b808fd5290c6d2c963b39b3c8b8b04f`.

| US member | Function-index span |
| --- | ---: |
| `func_150064E0` | `0xB0` |
| `func_15006590` | `0x65C` |
| `func_15006BEC` | `0x490` |
| `func_1500707C` | `0xEC` |
| `func_15007168` | `0x114` |
| `func_1500727C` | `0xE4` |
| `func_15007360` | `0xE0` |
| `func_15007440` | `0x118` |
| `func_15007558` | `0xEC` |
| `func_15007644` | `0x8` |
| `func_1500764C` | `0x1C` |
| `func_15007668` | `0x1C` |
| `func_15007684` | `0x1C` |
| `func_150076A0` | `0x1C` |
| `func_150076BC` | `0x5C` |
| `func_15007718` | `0x38` |
| `func_15007750` | `0x28` |
| `func_15007778` | `0xB8` |

### `game_34F20.c`

Range SHA-1: `e293f3cf913ca2e82822658863f888f04e90f32d`.

| US member | Function-index span |
| --- | ---: |
| `func_15007A70` | `0xCC` |
| `func_15007B3C` | `0x6A8` |
| `func_150081E4` | `0x4C` |
| `func_15008230` | `0x18` |
| `func_15008248` | `0x84` |
| `func_150082CC` | `0x74` |

### `game_357F0.c`

Range SHA-1: `c1e1c9c1675a679d22f7241d79d09ae5a8765884`.

| US member | Function-index span |
| --- | ---: |
| `func_15008340` | `0x500` |

### `game_36680.c`

Range SHA-1: `38ff52eb0f5af23015f2009e4a108d66c693c410`.

| US member | Function-index span |
| --- | ---: |
| `func_150091D0` | `0x10C` |
| `func_150092DC` | `0x58` |
| `func_15009334` | `0x2A4` |
| `func_150095D8` | `0x28` |
| `func_15009600` | `0x28` |
| `func_15009628` | `0x74` |
| `func_1500969C` | `0x28` |
| `func_150096C4` | `0x7C` |
| `func_15009740` | `0x28` |
| `func_15009768` | `0x3C` |
| `func_150097A4` | `0x28` |
| `func_150097CC` | `0x4C` |
| `func_15009818` | `0x2C` |
| `func_15009844` | `0x2C` |
| `func_15009870` | `0x24` |
| `func_15009894` | `0x3C` |
| `func_150098D0` | `0x28` |
| `func_150098F8` | `0x4C` |
| `func_15009944` | `0x4C` |
| `func_15009990` | `0xA8` |
| `func_15009A38` | `0x68` |
| `func_15009AA0` | `0x4C` |
| `func_15009AEC` | `0x4C` |
| `func_15009B38` | `0x4C` |
| `func_15009B84` | `0x4C` |
| `func_15009BD0` | `0xAC` |
| `func_15009C7C` | `0xAC` |
| `func_15009D28` | `0x44` |
| `func_15009D6C` | `0x44` |
| `func_15009DB0` | `0x4C` |
| `func_15009DFC` | `0x4C` |
| `func_15009E48` | `0x3C` |
| `func_15009E84` | `0x44` |
| `func_15009EC8` | `0x2C` |
| `func_15009EF4` | `0x3C` |
| `func_15009F30` | `0x44` |
| `func_15009F74` | `0xB4` |
| `func_1500A028` | `0x44` |
| `func_1500A06C` | `0x44` |
| `func_1500A0B0` | `0x4C` |
| `func_1500A0FC` | `0x4C` |
| `func_1500A148` | `0x4C` |
| `func_1500A194` | `0x4C` |
| `func_1500A1E0` | `0x3C` |
| `func_1500A21C` | `0x44` |
| `func_1500A260` | `0x4C` |
| `func_1500A2AC` | `0x48` |
| `func_1500A2F4` | `0x48` |
| `func_1500A33C` | `0x44` |
| `func_1500A380` | `0x44` |
| `func_1500A3C4` | `0x4C` |
| `func_1500A410` | `0x44` |
| `func_1500A454` | `0x3C` |
| `func_1500A490` | `0x44` |
| `func_1500A4D4` | `0x44` |
| `func_1500A518` | `0x44` |
| `func_1500A55C` | `0x4C` |
| `func_1500A5A8` | `0x4C` |
| `func_1500A5F4` | `0x4C` |
| `func_1500A640` | `0x4C` |
| `func_1500A68C` | `0x4C` |
| `func_1500A6D8` | `0xC4` |
| `func_1500A79C` | `0x4C` |
| `func_1500A7E8` | `0xE0` |
| `func_1500A8C8` | `0x3C` |
| `func_1500A904` | `0x48` |
| `func_1500A94C` | `0x44` |
| `func_1500A990` | `0x1CC` |
| `func_1500AB5C` | `0x44` |
| `func_1500ABA0` | `0x74` |
| `func_1500AC14` | `0x170` |
| `func_1500AD84` | `0x184` |
| `func_1500AF08` | `0x2EC` |
| `func_1500B1F4` | `0x1BC` |
| `func_1500B3B0` | `0x364` |
| `func_1500B714` | `0x1E0` |
| `func_1500B8F4` | `0x1C4` |
| `func_1500BAB8` | `0x1C4` |
| `func_1500BC7C` | `0x1C4` |
| `func_1500BE40` | `0x28` |
| `func_1500BE68` | `0x58` |
| `func_1500BEC0` | `0x320` |

### `game_39750.c`

Range SHA-1: `1f5655d30ee845310fd3a85db8cedb519812164f`.

| US member | Function-index span |
| --- | ---: |
| `func_1500C2A0` | `0x50` |
| `func_1500C2F0` | `0x5E0` |
| `func_1500C8D0` | `0x57C` |
| `func_1500CE4C` | `0x560` |
| `func_1500D3AC` | `0x51C` |
| `func_1500D8C8` | `0x5C0` |
| `func_1500DE88` | `0x5E8` |

### `game_3BA70.c`

Range SHA-1: `ed4e387445670870edaf6d9ebfccdb379ca4f097`.

| US member | Function-index span |
| --- | ---: |
| `func_1500E5C0` | `0x14C` |
| `func_1500E70C` | `0x2C` |
| `func_1500E738` | `0x158` |
| `func_1500E890` | `0x30` |
| `func_1500E8C0` | `0x1E0` |
| `func_1500EAA0` | `0x80` |

### `game_3DF10.c`

Range SHA-1: `4dd66da12b20985c586e17b952c2eb48682cc317`.

| US member | Function-index span |
| --- | ---: |
| `func_15010A60` | `0x550` |

### `game_40490.c`

Range SHA-1: `5b7e2ad497132cd67399de59670f6c33970515ef`.

| US member | Function-index span |
| --- | ---: |
| `func_15012FE0` | `0x20` |
| `func_15013000` | `0xB4` |
| `func_150130B4` | `0x658` |
| `func_1501370C` | `0x40` |
| `func_1501374C` | `0x2C` |
| `func_15013778` | `0x1F4` |
| `func_1501396C` | `0x40` |
| `func_150139AC` | `0x28C` |
| `func_15013C38` | `0x100` |
| `func_15013D38` | `0xB0` |
| `func_15013DE8` | `0x1B4` |
| `func_15013F9C` | `0x28` |
| `func_15013FC4` | `0x40` |
| `func_15014004` | `0x3C` |
| `func_15014040` | `0x3C` |
| `func_1501407C` | `0x18` |
| `func_15014094` | `0xB0` |
| `func_15014144` | `0xDC` |
| `func_15014220` | `0x8C` |
| `func_150142AC` | `0x40` |
| `func_150142EC` | `0x1CC` |
| `func_150144B8` | `0x294` |
| `func_1501474C` | `0x414` |
| `func_15014B60` | `0x40C` |
| `func_15014F6C` | `0x138` |
| `func_150150A4` | `0x60` |
| `func_15015104` | `0xD0` |
| `func_150151D4` | `0x12C` |
| `func_15015300` | `0x54` |
| `func_15015354` | `0x2F0` |
| `func_15015644` | `0xB0` |
| `func_150156F4` | `0x21C` |

### `game_44C40.c`

Range SHA-1: `ec58f63da844a34b36b3f5de928ccc54f5b2bf77`.

| US member | Function-index span |
| --- | ---: |
| `func_15017790` | `0x68` |
| `func_150177F8` | `0x70` |
| `func_15017868` | `0xC8` |
| `func_15017930` | `0x1F0` |
| `func_15017B20` | `0x484` |
| `func_15017FA4` | `0x42C` |

### `game_476D0.c`

Range SHA-1: `f203fb0d8f131f2cefb86f8d60e1f7203e845922`.

| US member | Function-index span |
| --- | ---: |
| `func_1501A220` | `0x17C` |
| `func_1501A39C` | `0xF4` |
| `func_1501A490` | `0x1F0` |
| `func_1501A680` | `0x4C` |
| `func_1501A6CC` | `0x98` |
| `func_1501A764` | `0x15C` |
| `func_1501A8C0` | `0x5D4` |
| `func_1501AE94` | `0xB0` |
| `func_1501AF44` | `0x15C` |
| `func_1501B0A0` | `0x18C` |
| `func_1501B22C` | `0xF4` |

### `game_57FA0.c`

Range SHA-1: `53014d795f1099ac5d85b8ee4bc3ddde6f7f9daa`.

| US member | Function-index span |
| --- | ---: |
| `func_1502AAF0` | `0x8` |
| `func_1502AAF8` | `0xC` |
| `func_1502AB04` | `0x184` |
| `func_1502AC88` | `0x27C` |
| `func_1502AF04` | `0x11C` |
| `func_1502B020` | `0xF0` |
| `func_1502B110` | `0x114` |
| `func_1502B224` | `0x12C` |
| `func_1502B350` | `0x158` |
| `func_1502B4A8` | `0x120` |
| `func_1502B5C8` | `0xF4` |
| `func_1502B6BC` | `0x134` |
| `func_1502B7F0` | `0xF0` |
| `func_1502B8E0` | `0xD4` |
| `func_1502B9B4` | `0x11C` |

