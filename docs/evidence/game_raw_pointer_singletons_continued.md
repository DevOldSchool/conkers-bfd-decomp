# Additional US pointer-selected singleton working units

Evidence kind: `structural_analysis`. These minimal working units isolate game-overlay functions selected by owned-ROM callback pointers. Each range is exactly one independently indexed raw function. Generic names derive from the raw ROM offsets; historical filenames and original compilation-unit boundaries remain unknown. All entries remain raw assembly.

The parent raw groups have exact agreement with the independent function CSV and no review errors or escaping branches at their outer endpoints. The singleton bounds use the indexed function start and raw span, and both endpoints are 16-byte aligned. Neighboring unselected functions receive no source-boundary credit.

| Source | US range | Bytes | Function | Owned selections | Parent raw group |
| --- | --- | ---: | --- | --- | --- |
| `src/game/game_7FA40.c` | `0x52590:0x52760` | 464 | `func_15052590` | `0x8008601C` -> `func_15052590`<br>`0x80086058` -> `func_15052590` | `game_77BE0` |
| `src/game/game_EBD00.c` | `0xbe850:0xbe9b0` | 352 | `func_150BE850` | `0x800896B8` -> `func_150BE850` | `game_EBD00` |
| `src/game/game_F4890.c` | `0xc73e0:0xc7670` | 656 | `func_150C73E0` | `0x800841E0` -> `func_150C73E0` | `game_F4890` |
| `src/game/game_F4C20.c` | `0xc7770:0xc7870` | 256 | `func_150C7770` | `0x80089674` -> `func_150C7770` | `game_F4C20` |
| `src/game/game_F5BE0.c` | `0xc8730:0xc88d0` | 416 | `func_150C8730` | `0x800841E8` -> `func_150C8730` | `game_F5BE0` |
| `src/game/game_FDBE0.c` | `0xd0730:0xd08c0` | 400 | `func_150D0730` | `0x8008CD3C` -> `func_150D0730` | `game_FDBE0` |
| `src/game/game_FF900.c` | `0xd2450:0xd26f0` | 672 | `func_150D2450` | `0x8008A59C` -> `func_150D2450` | `game_FF900` |
| `src/game/game_10E090.c` | `0xe0be0:0xe0d90` | 432 | `func_150E0BE0` | `0x8008607C` -> `func_150E0BE0` | `game_10DD20` |
| `src/game/game_10ED10.c` | `0xe1860:0xe1ab0` | 592 | `func_150E1860` | `0x800896FC` -> `func_150E1860` | `game_10ED10` |
| `src/game/game_118670.c` | `0xeb1c0:0xeb430` | 624 | `func_150EB1C0` | `0x80089680` -> `func_150EB1C0` | `game_118670` |
| `src/game/game_11F5A0.c` | `0xf20f0:0xf2230` | 320 | `func_150F20F0` | `0x8008CD68` -> `func_150F20F0` | `game_11C2B0` |
| `src/game/game_1218A0.c` | `0xf43f0:0xf4570` | 384 | `func_150F43F0` | `0x800896D0` -> `func_150F43F0` | `game_11FF10` |
| `src/game/game_126F60.c` | `0xf9ab0:0xf9bb0` | 256 | `func_150F9AB0` | `0x800891DC` -> `func_150F9AB0` | `game_126F60` |
| `src/game/game_1308E0.c` | `0x103430:0x103690` | 608 | `func_15103430` | `0x800896AC` -> `func_15103430` | `game_1308E0` |
| `src/game/game_135490.c` | `0x107fe0:0x108120` | 320 | `func_15107FE0` | `0x800896D4` -> `func_15107FE0` | `game_135490` |
| `src/game/game_1D0600.c` | `0x1a3150:0x1a3390` | 576 | `func_151A3150` | `0x8008F8E4` -> `func_151A3150` | `game_1CDEC0` |
| `src/game/game_1D3800.c` | `0x1a6350:0x1a6600` | 688 | `func_151A6350` | `0x80089E9C` -> `func_151A6350` | `game_1D2B10` |
| `src/game/game_1E9820.c` | `0x1bc370:0x1bc580` | 528 | `func_151BC370` | `0x80089B0C` -> `func_151BC370` | `game_1E73B0` |
| `src/game/game_1F1CD0.c` | `0x1c4820:0x1c4ab0` | 656 | `func_151C4820` | `0x8008A594` -> `func_151C4820` | `game_1EF500` |
| `src/game/game_1FC5D0.c` | `0x1cf120:0x1cf380` | 608 | `func_151CF120` | `0x8008A290` -> `func_151CF120` | `game_1FA770` |

## Validation

### `src/game/game_7FA40.c`

Range `0x52590:0x52760`; one entry, 464 bytes.
Entry: `func_15052590`; raw span `0x1d0`.
SHA-1: `e33da4f308f9a0d965904e40e4be489de46de79d`.
Reference assembly: `reference/game/us/asm/4A730.s`.

### `src/game/game_EBD00.c`

Range `0xbe850:0xbe9b0`; one entry, 352 bytes.
Entry: `func_150BE850`; raw span `0x160`.
SHA-1: `fac8c67bb8d557debe000282eac221b4ff3a2a62`.
Reference assembly: `reference/game/us/asm/BE850.s`.

### `src/game/game_F4890.c`

Range `0xc73e0:0xc7670`; one entry, 656 bytes.
Entry: `func_150C73E0`; raw span `0x290`.
SHA-1: `6ff172638a9e7149152c4ec044f4d4619bf4d5e5`.
Reference assembly: `reference/game/us/asm/C73E0.s`.

### `src/game/game_F4C20.c`

Range `0xc7770:0xc7870`; one entry, 256 bytes.
Entry: `func_150C7770`; raw span `0x100`.
SHA-1: `eef3dd411cb3a9f3f016d7306e2b18d407c0cb58`.
Reference assembly: `reference/game/us/asm/C7770.s`.

### `src/game/game_F5BE0.c`

Range `0xc8730:0xc88d0`; one entry, 416 bytes.
Entry: `func_150C8730`; raw span `0x1a0`.
SHA-1: `f19ac38457365c039c032f468e5d18b0211a8932`.
Reference assembly: `reference/game/us/asm/C8350.s`.

### `src/game/game_FDBE0.c`

Range `0xd0730:0xd08c0`; one entry, 400 bytes.
Entry: `func_150D0730`; raw span `0x190`.
SHA-1: `9653d8b2a9e23138a6e843685e4f1e82a6b31928`.
Reference assembly: `reference/game/us/asm/D0730.s`.

### `src/game/game_FF900.c`

Range `0xd2450:0xd26f0`; one entry, 672 bytes.
Entry: `func_150D2450`; raw span `0x2a0`.
SHA-1: `c513d2b2996fce94846b0dfab9399ffc7707fc3c`.
Reference assembly: `reference/game/us/asm/D2450.s`.

### `src/game/game_10E090.c`

Range `0xe0be0:0xe0d90`; one entry, 432 bytes.
Entry: `func_150E0BE0`; raw span `0x1b0`.
SHA-1: `d9f32ac37681dca8eaae686b615a73b697470021`.
Reference assembly: `reference/game/us/asm/E0870.s`.

### `src/game/game_10ED10.c`

Range `0xe1860:0xe1ab0`; one entry, 592 bytes.
Entry: `func_150E1860`; raw span `0x250`.
SHA-1: `00cc43b6fb40baab43daf4bda136e0478275a618`.
Reference assembly: `reference/game/us/asm/E1860.s`.

### `src/game/game_118670.c`

Range `0xeb1c0:0xeb430`; one entry, 624 bytes.
Entry: `func_150EB1C0`; raw span `0x270`.
SHA-1: `706e0dca785d335844d425c0ece9f487374505ce`.
Reference assembly: `reference/game/us/asm/EB1C0.s`.

### `src/game/game_11F5A0.c`

Range `0xf20f0:0xf2230`; one entry, 320 bytes.
Entry: `func_150F20F0`; raw span `0x140`.
SHA-1: `75b8be3f31319991dd311f8eaa3f7152d4de2039`.
Reference assembly: `reference/game/us/asm/EEE00.s`.

### `src/game/game_1218A0.c`

Range `0xf43f0:0xf4570`; one entry, 384 bytes.
Entry: `func_150F43F0`; raw span `0x180`.
SHA-1: `94f5a5322ca64c20309702117a4a533af37b6811`.
Reference assembly: `reference/game/us/asm/F2A60.s`.

### `src/game/game_126F60.c`

Range `0xf9ab0:0xf9bb0`; one entry, 256 bytes.
Entry: `func_150F9AB0`; raw span `0x100`.
SHA-1: `dc3d71f6ad5d4f26d814d5bbc24ed56f9c937f32`.
Reference assembly: `reference/game/us/asm/F9AB0.s`.

### `src/game/game_1308E0.c`

Range `0x103430:0x103690`; one entry, 608 bytes.
Entry: `func_15103430`; raw span `0x260`.
SHA-1: `9d7e8a1658d7bbd41eb3acefd59be95388a91aff`.
Reference assembly: `reference/game/us/asm/103430.s`.

### `src/game/game_135490.c`

Range `0x107fe0:0x108120`; one entry, 320 bytes.
Entry: `func_15107FE0`; raw span `0x140`.
SHA-1: `942fbb3bde87133879f91c0b34802df2fc6c97e6`.
Reference assembly: `reference/game/us/asm/107FE0.s`.

### `src/game/game_1D0600.c`

Range `0x1a3150:0x1a3390`; one entry, 576 bytes.
Entry: `func_151A3150`; raw span `0x240`.
SHA-1: `7c96427196369092d78d70b31e88d90e2583ce6e`.
Reference assembly: `reference/game/us/asm/19EF90.s`.

### `src/game/game_1D3800.c`

Range `0x1a6350:0x1a6600`; one entry, 688 bytes.
Entry: `func_151A6350`; raw span `0x2b0`.
SHA-1: `28350c6d2e047d159d4334b7a3aac8764d2a6c1f`.
Reference assembly: `reference/game/us/asm/1A5660.s`.

### `src/game/game_1E9820.c`

Range `0x1bc370:0x1bc580`; one entry, 528 bytes.
Entry: `func_151BC370`; raw span `0x210`.
SHA-1: `bb19d64c37d7ee1142bb8a12a16361101e91abc0`.
Reference assembly: `reference/game/us/asm/1B9F00.s`.

### `src/game/game_1F1CD0.c`

Range `0x1c4820:0x1c4ab0`; one entry, 656 bytes.
Entry: `func_151C4820`; raw span `0x290`.
SHA-1: `578314a472d23d039a83df9a7f4d2a0dd5379c03`.
Reference assembly: `reference/game/us/asm/1C2050.s`.

### `src/game/game_1FC5D0.c`

Range `0x1cf120:0x1cf380`; one entry, 608 bytes.
Entry: `func_151CF120`; raw span `0x260`.
SHA-1: `5d56e2ad4de51b976965d9636273b9961841e967`.
Reference assembly: `reference/game/us/asm/1CD2C0.s`.

## Integration result

Validated with `./conker progress integrate --profile us --all-reviewed`. The command extracted 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and reported `conker.game.us.integrated.bin: OK`; the complete US game overlay was byte-identical.
