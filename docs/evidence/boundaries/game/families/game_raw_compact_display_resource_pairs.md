# US compact display objects and resource pairs

Evidence kind: `structural_analysis`. These working source families retain generic offset filenames. Original filenames and historical compilation units remain unknown. All entries remain raw ASM.

## Type-3C display object: `0x1D26C0:0x1D2AB0`

`151D26C0` allocates type `0x3C`, size `0x18`, initializing halfword state at `+0xE/+0x10/+0x12/+0x14` and signed rate byte `+0x16`. Type-table update/draw slots `8008C0D8/8008C0E0` contain local `151D275C/151D2830`. The update advances the state using the rate; the draw consumes the same state. Local `151D2718` traverses the active chain at `800DD0E0`, finds matching identifiers at `+0x10` and sets the same rate byte to -2. These four entries implement creation, lookup/change, update and drawing for this state layout.

## Eight-byte custom particle: `0x1B6010:0x1B6320`

`151B6010` builds a descriptor at stack `+0x30`, selects update 6 in descriptor byte `+0x61` (`0x1B60F0`, `0x1B61B8`) and calls `15132A4C` with eight custom bytes. The underlying `1513264C` copies the descriptor to object `+0x10`, so the update selector becomes object `+0x71`; owned update slot `800898C8` points to local `151B6254`. The creator copies eight bytes to object `+0x170`, which that update advances and uses for the particle's motion/scale state.

## Type-5 child pair, selector 5: `0x174690:0x1749A0`

`15174690` creates a descriptor at stack `+0x40`, writes selector 5 to stack byte `+0x5F`, and calls `15167D84`. That constructor copies the descriptor to object `+0x10`, making the byte object `+0x2F`. The type-5 updater dispatches this byte through `8008C9C8`; owned slot `8008C9DC` is local `15174920`. The selected callback advances the child's height and halfword motion state.

## Type-5 child pair, selector 9: `0x18CA80:0x18CD20`

`1518CA80` builds a descriptor at stack `+0x30`, writes selector 9 to byte `+0x4F` and calls `15167D84`. The copied selector again becomes object `+0x2F`; owned slot `8008C9EC` points to local `1518CCA8`. This callback adjusts the child's motion state and reads the descriptor-derived mode at `+0x3B`. Both entries participate in the same child construction/update path.

## Actor render displacement: `0x34860:0x34F20`

`15034860` derives an actor animation displacement and stores its halfword result at `800C3EF0` (`0x349A0`). `15034EB4` reads exactly that result, scales it with actor `+0x14C` and adjusts translation `+0x34` in one or two actor matrices reached from `+0x1D4`. The producer/consumer state and adjacent two-entry layout support this working group.

## Allocated render records: `0x177410:0x177F90`

`15177410` allocates a 44-byte record and subordinate buffers, stores it in `800DD410` and manages the count byte `800DD418`. `15177A94` iterates that same array/count, reads the initialized record and buffers and builds their display data. Shared record fields include `+0x16/+0x20/+0x24/+0x28`. These are the only two entries in the range.

## Actor resource cache lifecycle: `0x17ABB0:0x17B500`

`1517AD00` selects a descriptor from the two-entry table at `800A7230`, obtains per-type counts from `800C4310`, and allocates/populates the associated cache at `800DD460`. `1517ABB0` traverses those same table/count/cache structures, frees the subordinate allocations, and clears the stored pointers. The matching allocation and teardown paths identify the two-entry family.

## Validation

Callback slots were read from the owned US data image. All endpoints are 16-byte aligned, indexed function starts. Raw words match the owned code image and entry spans cover each interval. Whole-image conditional-branch scanning finds no crossing edges. Independent CSV membership and beta correlations follow; these support entry identity without establishing historical filenames or compilation boundaries.

### `src/game/game_1FFB70.c`

Range `0x1d26c0:0x1d2ab0`; 4 entries, 1,008 bytes.
SHA-1: `1d4bf2dafcb408b8014b072ca8cf529b1fa5c699`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151D26C0` | `0x58` |
| `func_151D2718` | `0x44` |
| `func_151D275C` | `0xd4` |
| `func_151D2830` | `0x280` |

### `src/game/game_1E34C0.c`

Range `0x1b6010:0x1b6320`; 2 entries, 784 bytes.
SHA-1: `6ddc4c8090f75172a28ae420cad37ade768e2bae`.
debug: 2 correlations, 2 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151B6010` | `0x244` |
| `func_151B6254` | `0xcc` |

### `src/game/game_1A1B40.c`

Range `0x174690:0x1749a0`; 2 entries, 784 bytes.
SHA-1: `3d8d66ebd656694cb3eb26e519a41ab9ff7617fc`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15174690` | `0x290` |
| `func_15174920` | `0x80` |

### `src/game/game_1B9F30.c`

Range `0x18ca80:0x18cd20`; 2 entries, 672 bytes.
SHA-1: `6d2f502b0c5947f361e744558bc2cf287cf6352e`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1518CA80` | `0x228` |
| `func_1518CCA8` | `0x78` |

### `src/game/game_61D10.c`

Range `0x34860:0x34f20`; 2 entries, 1,728 bytes.
SHA-1: `645643bbbce5e0aa32c87971fe2f2af4985d47bf`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15034860` | `0x654` |
| `func_15034EB4` | `0x6c` |

### `src/game/game_1A48C0.c`

Range `0x177410:0x177f90`; 2 entries, 2,944 bytes.
SHA-1: `bc1a6c634e4c96360ed352fa9baf83a1dd8fb9cd`.
debug: 2 correlations, 2 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15177410` | `0x684` |
| `func_15177A94` | `0x4fc` |

### `src/game/game_1A8060.c`

Range `0x17abb0:0x17b500`; 2 entries, 2,384 bytes.
SHA-1: `e667aa151440ee626ea3bd2bbc8d31fbe65c9f5d`.
debug: 1 correlations, 0 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1517ABB0` | `0x150` |
| `func_1517AD00` | `0x800` |

## Integration result

All seven reviewed units integrated as raw ASM wrappers. The complete 2,072,880-byte US game overlay is byte-identical (SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`). No C match is claimed.
