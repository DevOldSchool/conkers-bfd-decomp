# US path renderer and owner-linked endpoint lifecycle

Evidence type: `structural_analysis`

These working source families retain older navigation intervals from local
`mkst/conker` commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined base `0x2D4B0`). Constructor, callback and
field relationships support the groups. Original filenames and exact historical
compilation units remain unknown.

## Path renderer: `0xE1AB0:0xE3020`

Constructor `150E1AB0` allocates type `0xB`, size `0x100`, initializes start
and target vectors `+0x94/+0xB0`, motion parameters and owner `+0xDC`, and
builds two sets of four vertices using the selected `8008CA4C` resource.
Local `150E2DB4/150E2EA4` are parameter-building wrappers around it.

The owned type table at `8008B4A8`, stride `0x34`, selects local update
`150E1D14` and draw `150E28DC` in type `0xB` slots `8008B6E4/8008B6EC`.
Both consume the constructor's vectors and motion state; the update can invoke
the same constructor again. The draw uses the same selected resource and
per-view vertex fields `+0xC4/+0xC8/+0xCC`.

Type slots `8008B700/8008B704` point to local event `150E2FC0` and adapter
`150E2F90`. On event `0x2D`, the former transfers owner `+0xDC` and identity
byte `+0xDA`, both initialized by the constructor. The latter calls local
identity helper `150E2DA4`. Thus all eight entries have a concrete lifecycle
connection, including the short helper.

## Owner-linked endpoint renderer: `0xC5370:0xC5DC0`

Constructor `150C5370` allocates type `0x46`, base size `0xC8` plus custom
bytes. It copies `0x24` descriptor bytes to `+0x18`, calculates endpoint
separation into `+0xC0`, and sets active bit 0 in `+0x10`. The type row starts
at `8008C2E0`: its update/draw slots select `150C5568/150C56A4`, event
slot `8008C2FC` selects `150C5CC4`, and release slots `8008C308/8008C30C`
select `150C5470/150C54C0`.

Update `150C5568` checks the same active bit, optionally calls table
`80088760` by descriptor byte `+0x30`, and recomputes endpoint separation.
That table's first two entries select local `150C5B88/150C5BD4`, which resolve
an owner at custom `+0xC8` to endpoint `+0x24`, including model-node and
identity checks. Release dispatch uses mode byte `+0x38` and tables
`800887B8/800887C0`: local `150C5430/150C5450` handle the base case;
`150C5510/150C553C` release the custom owner relationship before calling
those base helpers. The event dispatcher uses the same mode byte and table
`800887C8`; its non-null second entry is local `150C5D0C`, which releases
or transfers that same custom owner on events 0 and `0x2D`.

The two remaining wrappers `150C5C74/150C5C9C` send commands 1/2 to
attachment kind `0x15` through `1514D3B0`. This is linked to this exact
renderer: external factory `1514D564` calls `150C5370` at `0x14D604`,
copies the owner state to `+0xC8`, and registers the result as kind `0x15`
through `1514EC1C` at `0x14D634`. The owned kind descriptor at `800A5F24`
and callback table `8008AB64` resolve to `1514E89C`, whose commands 1/2
set/clear the renderer's active bit at `+0x10`. This closes the wrapper link
without grouping unrelated adjacent functions.

## Validation

All twenty-three labels agree with the independent US index. Their spans total
8,128 bytes and match owned US instructions, delay slots and padding. Every
endpoint follows a complete return; no decoded conditional branch crosses a
boundary in either direction. No data, rodata or BSS ownership is assigned.
Full US overlay byte equality gates integration. All members remain raw ASM,
not matched C.

### `src/game/game_10EF60.c`

Range `0xe1ab0:0xe3020`; 8 entries, 5,488 bytes.
SHA-1: `e5fc04373bb24c3fcfb5a11ea7d86f2530c81a7f`.
debug: 6 correlations, 4 strong.
ects: 4 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150E1AB0` | `0x264` |
| `func_150E1D14` | `0xbc8` |
| `func_150E28DC` | `0x4c8` |
| `func_150E2DA4` | `0x10` |
| `func_150E2DB4` | `0xf0` |
| `func_150E2EA4` | `0xec` |
| `func_150E2F90` | `0x30` |
| `func_150E2FC0` | `0x60` |

### `src/game/game_F2820.c`

Range `0xc5370:0xc5dc0`; 15 entries, 2,640 bytes.
SHA-1: `151a97ec6aee0c5b5e33401c7a8773fab837e05a`.
debug: 13 correlations, 4 strong.
ects: 12 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C5370` | `0xc0` |
| `func_150C5430` | `0x20` |
| `func_150C5450` | `0x20` |
| `func_150C5470` | `0x50` |
| `func_150C54C0` | `0x50` |
| `func_150C5510` | `0x2c` |
| `func_150C553C` | `0x2c` |
| `func_150C5568` | `0x13c` |
| `func_150C56A4` | `0x4e4` |
| `func_150C5B88` | `0x4c` |
| `func_150C5BD4` | `0xa0` |
| `func_150C5C74` | `0x28` |
| `func_150C5C9C` | `0x28` |
| `func_150C5CC4` | `0x48` |
| `func_150C5D0C` | `0xb4` |

## Integration result

Integrated on the first build attempt. The complete US game overlay is
byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw ASM.
