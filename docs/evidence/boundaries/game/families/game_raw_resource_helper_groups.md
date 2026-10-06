# US resource, object-state and helper groups

Evidence type: `structural_analysis`

Four further existing raw ranges form reviewed working source groups, covering
69 recovered entries and 18,432 bytes. Generic names refer to upstream
combined-image offsets. Original filenames and exact historical object
ownership are not recovered; the code stays raw ASM.

## Extents and provenance

The local upstream `mkst/conker@3adf229175c037c771f251f169f9dd80ca306924`
records the following raw endpoints in `conker/conker.us.yaml`. Their
translation subtracts `0x2D4B0`. The independent raw reference and owned US
game payload supply instruction, call and runtime-table checks. The payload
SHA-1 is `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

| Source under `src/game/` | Combined range | US game range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| `game_6A3D0.c` | `0x6A3D0:0x6B280` | `0x3CF20:0x3DDD0` | 15 | 3,760 | 9 (9) | 7 (7) |
| `game_AB760.c` | `0xAB760:0xAC030` | `0x7E2B0:0x7EB80` | 15 | 2,256 | 13 (11) | 13 (11) |
| `game_AC030.c` | `0xAC030:0xAD6B0` | `0x7EB80:0x80200` | 16 | 5,760 | 13 (12) | 11 (11) |
| `game_1CA420.c` | `0x1CA420:0x1CBE20` | `0x19CF70:0x19E970` | 23 | 6,656 | 19 (14) | 11 (6) |

Beta counts use the current index, including the corrected ECTS image layout.
They corroborate ordering; they do not establish instruction equality or
historical file bounds.

## Group relationships

### `game_6A3D0.c`

The opening resource routine `1503CF20` checks an index against `0xBB`, uses
the indexed root table at `800D19A0`, and calls helpers throughout the range:
`1503D438`, `1503D368`, `1503DC3C`, `1503D984`, `1503D804`, `1503D774`,
`1503D660` and the final `1503DD1C`. The small `1503D438` helper rebases a
nonzero pointer only when its `0x0F000000` mask is clear. `1503D660` shares
the preceding pointer/layout helpers, and `1503DA9C` calls back to the
opening routine. There are twenty direct inter-function call sites.

The repeated roots and resource arrays at `800C5338`, `800C5628`,
`800C5A90` and `800C4488` support the connected group. The final helper
iterates `0xC`-byte records and is directly used by the opening routine.
There is no reliance on incidental data words looking like callback pointers.

### `game_AB760.c`

These routines share the object's compact state bytes around `+0x6A:+0x72`
and the table at `800D1C90`. `1507E500` and `1507E7E4` both call
`1507E968`, `1507E908`, `1507E9F8` and `1507E5C8`; that helper calls
`1507EA44`. `1507E73C` calls the opening `1507E2B0` and late `1507EABC`.
The final pair calls `1507EB4C` then `1507EABC`, connecting both ends to
the same update chain. Eighteen direct call sites support this compact
working unit, with thirteen ordered correlations in each beta.

### `game_AC030.c`

The opening `1507EB80` appends a byte to a bounded buffer only while the
new count is below `0x28`. The adjacent `1507EBB8` resolves a table-backed
entry. Both are repeatedly used by `1507EFD0`, which constructs a local
byte sequence from the object selected by shared root `800D154C` and flags
at `800D18C0`. The main callback `1507F640`, selected at `80086310`, calls
that constructor and shared helpers `1507F54C` and `1507F454`.

Late `1507FEA0` uses `1507FF94` and `1507FC2C`; the middle constructor also
uses `1507FF94` and final `1507FFD8`. Ten references to `800D154C`, recurring
state at `800D18C0/800D18C4`, and 26 inter-function call sites support the
full range. The preceding compact object-state unit ends with its completed
state-update wrapper; this range begins with the distinct byte-buffer helper.

### `game_1CA420.c`

The first routine `1519CF70` constructs a type-6 descriptor. The adjacent
`1519CFA0` resets object flags and updates bits in its custom data at `+0x98`.
`1519D454` and `1519E1F4` reuse that reset, while setup `1519D030` and the
update share `1519E304`. The later `1519E3BC` and `1519E464` return to the
early setup; `1519E65C` and `1519E688` each call the opening constructor
twice. Seventeen direct inter-function call sites link these clusters.

Runtime descriptors contain sixteen pointers to the group's callbacks.
The final cleanup pair `1519E924`/`1519E948`, selected at
`8008A698/8008A7C0`, both clear shared root `800E0920` before calling their
respective generic teardown helpers. Earlier routines also use this root.
The shared custom layout, setup/update/reset relationships and descriptor
callbacks corroborate the working extent without supplying a source filename.

## Boundary checks and integration

Every generated raw instruction word equals the owned US payload; member
spans cover each proposed range exactly, and top-level entries agree with the
US function index. No decoded conditional branch crosses these endpoints in
either direction. The neighboring and final routines return before padding;
each following range starts at a distinct function entry. These checks are
combined with the relationships above, rather than treating padding as proof
of a source boundary.

No data, rodata or BSS is assigned. The supported registration command creates
ordered raw-ASM skeletons and membership. Complete-overlay byte equality is
the integration gate; it does not promote the raw functions to matched C.

## Membership

All four units integrate on the first complete-overlay attempt. The resulting
2,072,880-byte game binary has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, exactly matching the owned US
payload. The comparison map stays raw assembly, all 69 new functions remain
`raw_asm`, and the four source units have `mixed` integration state.

### `src/game/game_6A3D0.c`

Range SHA-1: `b609c8f462b7ab04da343500aa286e286bce5503`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1503CF20` | `0x448` |
| `func_1503D368` | `0xd0` |
| `func_1503D438` | `0x24` |
| `func_1503D45C` | `0x28` |
| `func_1503D484` | `0x8c` |
| `func_1503D510` | `0xe0` |
| `func_1503D5F0` | `0x70` |
| `func_1503D660` | `0x114` |
| `func_1503D774` | `0x90` |
| `func_1503D804` | `0x180` |
| `func_1503D984` | `0xb8` |
| `func_1503DA3C` | `0x60` |
| `func_1503DA9C` | `0x1a0` |
| `func_1503DC3C` | `0xe0` |
| `func_1503DD1C` | `0xb4` |

### `src/game/game_AB760.c`

Range SHA-1: `13e4841ff33e7424574966bdd59976252d5faa26`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1507E2B0` | `0x110` |
| `func_1507E3C0` | `0x140` |
| `func_1507E500` | `0xc8` |
| `func_1507E5C8` | `0xf0` |
| `func_1507E6B8` | `0x84` |
| `func_1507E73C` | `0xa8` |
| `func_1507E7E4` | `0x124` |
| `func_1507E908` | `0x60` |
| `func_1507E968` | `0x80` |
| `func_1507E9E8` | `0x10` |
| `func_1507E9F8` | `0x4c` |
| `func_1507EA44` | `0x78` |
| `func_1507EABC` | `0x70` |
| `func_1507EB2C` | `0x20` |
| `func_1507EB4C` | `0x34` |

### `src/game/game_AC030.c`

Range SHA-1: `2f4f60c7c3016f23cb51d347d4596522937c27eb`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1507EB80` | `0x38` |
| `func_1507EBB8` | `0x80` |
| `func_1507EC38` | `0x220` |
| `func_1507EE58` | `0x60` |
| `func_1507EEB8` | `0x3c` |
| `func_1507EEF4` | `0xac` |
| `func_1507EFA0` | `0x30` |
| `func_1507EFD0` | `0x484` |
| `func_1507F454` | `0x6c` |
| `func_1507F4C0` | `0x8c` |
| `func_1507F54C` | `0xf4` |
| `func_1507F640` | `0x5ec` |
| `func_1507FC2C` | `0x274` |
| `func_1507FEA0` | `0xf4` |
| `func_1507FF94` | `0x44` |
| `func_1507FFD8` | `0x228` |

### `src/game/game_1CA420.c`

Range SHA-1: `88502f6d944d6f57d6c04d5af690b24fb155fb0b`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1519CF70` | `0x30` |
| `func_1519CFA0` | `0x30` |
| `func_1519CFD0` | `0x30` |
| `func_1519D000` | `0x30` |
| `func_1519D030` | `0x210` |
| `func_1519D240` | `0x214` |
| `func_1519D454` | `0x5a0` |
| `func_1519D9F4` | `0x800` |
| `func_1519E1F4` | `0x110` |
| `func_1519E304` | `0xb8` |
| `func_1519E3BC` | `0xa8` |
| `func_1519E464` | `0x10c` |
| `func_1519E570` | `0xac` |
| `func_1519E61C` | `0x40` |
| `func_1519E65C` | `0x2c` |
| `func_1519E688` | `0x34` |
| `func_1519E6BC` | `0x98` |
| `func_1519E754` | `0xc4` |
| `func_1519E818` | `0xb4` |
| `func_1519E8CC` | `0x2c` |
| `func_1519E8F8` | `0x2c` |
| `func_1519E924` | `0x24` |
| `func_1519E948` | `0x28` |
