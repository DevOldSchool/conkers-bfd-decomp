# Final US pointer-selected singleton working units

Evidence kind: `structural_analysis`. These minimal working units isolate game-overlay functions selected by owned-ROM callback pointers. Each range is exactly one independently indexed raw function. Generic names derive from the raw ROM offsets; historical filenames and original compilation-unit boundaries remain unknown. All entries remain raw assembly.

The parent raw groups have exact agreement with the independent function CSV and no review errors or escaping branches at their outer endpoints. The singleton bounds use the indexed function start and raw span, and both endpoints are 16-byte aligned. Neighboring unselected functions receive no source-boundary credit.

The `0xeb20:0xeb30` singleton was reviewed but withdrawn because the existing named raw split `game_3BFD0` must retain its identity in the comparison map.

| Source | US range | Bytes | Function | Owned selections | Parent raw group |
| --- | --- | ---: | --- | --- | --- |
| `src/game/game_2D4B0.c` | `0x0:0x90` | 144 | `func_15000000` | `0x8009AA98` -> `func_15000000`<br>`0x800A5E8C` -> `func_15000000`<br>`0x800A94DC` -> `func_15000000`<br>`0x800A981C` -> `func_15000000` | `game_2D4B0` |
| `src/game/game_50D20.c` | `0x23870:0x238d0` | 96 | `func_15023870` | `0x80084100` -> `func_15023870` | `game_50D20` |
| `src/game/game_E8BB0.c` | `0xbb700:0xbb760` | 96 | `func_150BB700` | `0x80089684` -> `func_150BB700` | `game_E8BB0` |
| `src/game/game_EC360.c` | `0xbeeb0:0xbef70` | 192 | `func_150BEEB0` | `0x800896DC` -> `func_150BEEB0` | `game_EBE60` |
| `src/game/game_F4800.c` | `0xc7350:0xc73e0` | 144 | `func_150C7350` | `0x80089698` -> `func_150C7350` | `game_F4800` |
| `src/game/game_FC410.c` | `0xcef60:0xcf040` | 224 | `func_150CEF60` | `0x8008CD1C` -> `func_150CEF60` | `game_FC410` |
| `src/game/game_FC530.c` | `0xcf080:0xcf0a0` | 32 | `func_150CF080` | `0x800896B0` -> `func_150CF080` | `game_FC410` |
| `src/game/game_FC550.c` | `0xcf0a0:0xcf140` | 160 | `func_150CF0A0` | `0x80088EDC` -> `func_150CF0A0` | `game_FC550` |
| `src/game/game_FD110.c` | `0xcfc60:0xcfd20` | 192 | `func_150CFC60` | `0x8008ACFC` -> `func_150CFC60` | `game_FC5F0` |
| `src/game/game_FDB00.c` | `0xd0650:0xd0730` | 224 | `func_150D0650` | `0x800896C8` -> `func_150D0650` | `game_FDB00` |
| `src/game/game_10CCD0.c` | `0xdf820:0xdf8c0` | 160 | `func_150DF820` | `0x80089694` -> `func_150DF820` | `game_10CCD0` |
| `src/game/game_117940.c` | `0xea490:0xea500` | 112 | `func_150EA490` | `0x80089B64` -> `func_150EA490` | `game_117490` |
| `src/game/game_123870.c` | `0xf63c0:0xf6400` | 64 | `func_150F63C0` | `0x8008A9A8` -> `func_150F63C0` | `game_1228D0` |
| `src/game/game_126ED0.c` | `0xf9a20:0xf9ab0` | 144 | `func_150F9A20` | `0x800896E0` -> `func_150F9A20` | `game_126ED0` |
| `src/game/game_129E80.c` | `0xfc9d0:0xfca00` | 48 | `func_150FC9D0` | `0x8008A844` -> `func_150FC9D0` | `game_128D70` |
| `src/game/game_12B1C0.c` | `0xfdd10:0xfdda0` | 144 | `func_150FDD10` | `0x8008CD48` -> `func_150FDD10` | `game_12B1C0` |
| `src/game/game_130200.c` | `0x102d50:0x102d90` | 64 | `func_15102D50` | `0x80089F6C` -> `func_15102D50` | `game_12FDD0` |
| `src/game/game_1319D0.c` | `0x104520:0x1045e0` | 192 | `func_15104520` | `0x8008969C` -> `func_15104520` | `game_1319D0` |
| `src/game/game_1792B0.c` | `0x14be00:0x14be20` | 32 | `func_1514BE00` | `0x80089DEC` -> `func_1514BE00` | `game_176A00` |
| `src/game/game_1B7480.c` | `0x189fd0:0x189ff0` | 32 | `func_15189FD0` | `0x8008A45C` -> `func_15189FD0` | `game_1B7480` |
| `src/game/game_1BD880.c` | `0x1903d0:0x190400` | 48 | `func_151903D0` | `0x8008B138` -> `func_151903D0` | `game_1BA1D0` |
| `src/game/game_1D6510.c` | `0x1a9060:0x1a90c0` | 96 | `func_151A9060` | `0x80082EDC` -> `func_151A9060` | `game_1D5FD0` |
| `src/game/game_1DBB60.c` | `0x1ae6b0:0x1ae7b0` | 256 | `func_151AE6B0` | `0x8008B028` -> `func_151AE6B0` | `game_1DBB60` |
| `src/game/game_1F3740.c` | `0x1c6290:0x1c62d0` | 64 | `func_151C6290` | `0x80086C98` -> `func_151C6290` | `game_1F2730` |

## Validation

### `src/game/game_2D4B0.c`

Range `0x0:0x90`; one entry, 144 bytes.
Entry: `func_15000000`; raw span `0x90`.
SHA-1: `517ade9081fb4cb31ea2fe61b9af269767b0c8f2`.
Reference assembly: `reference/game/us/asm/0.s`.

### `src/game/game_50D20.c`

Range `0x23870:0x238d0`; one entry, 96 bytes.
Entry: `func_15023870`; raw span `0x60`.
SHA-1: `a2e75fe1ce4d8da79bd3e9368ad912bb03c47148`.
Reference assembly: `reference/game/us/asm/23870.s`.

### `src/game/game_E8BB0.c`

Range `0xbb700:0xbb760`; one entry, 96 bytes.
Entry: `func_150BB700`; raw span `0x60`.
SHA-1: `6d2640ac730a91f1da69f5ef663af6e9aa2a0dcc`.
Reference assembly: `reference/game/us/asm/BB700.s`.

### `src/game/game_EC360.c`

Range `0xbeeb0:0xbef70`; one entry, 192 bytes.
Entry: `func_150BEEB0`; raw span `0xc0`.
SHA-1: `e5ea13f4a590d656d0bec98a30d559e15fd896ee`.
Reference assembly: `reference/game/us/asm/BE9B0.s`.

### `src/game/game_F4800.c`

Range `0xc7350:0xc73e0`; one entry, 144 bytes.
Entry: `func_150C7350`; raw span `0x90`.
SHA-1: `3a83ee8dda8ec66ca4156c86d60ee3088bee74b8`.
Reference assembly: `reference/game/us/asm/C7350.s`.

### `src/game/game_FC410.c`

Range `0xcef60:0xcf040`; one entry, 224 bytes.
Entry: `func_150CEF60`; raw span `0xe0`.
SHA-1: `c342ffb945cf2acefcd2c78cff129ef675a8cfeb`.
Reference assembly: `reference/game/us/asm/CEF60.s`.

### `src/game/game_FC530.c`

Range `0xcf080:0xcf0a0`; one entry, 32 bytes.
Entry: `func_150CF080`; raw span `0x20`.
SHA-1: `cec2fb06a79ba6e1b78e8dba44caa4f0a5445e85`.
Reference assembly: `reference/game/us/asm/CEF60.s`.

### `src/game/game_FC550.c`

Range `0xcf0a0:0xcf140`; one entry, 160 bytes.
Entry: `func_150CF0A0`; raw span `0xa0`.
SHA-1: `ecf11210bd26684715dbf318c786030b72bdfb67`.
Reference assembly: `reference/game/us/asm/CF0A0.s`.

### `src/game/game_FD110.c`

Range `0xcfc60:0xcfd20`; one entry, 192 bytes.
Entry: `func_150CFC60`; raw span `0xc0`.
SHA-1: `32e8f7326c076ee90b0989ef171d2a18e9285a98`.
Reference assembly: `reference/game/us/asm/CF140.s`.

### `src/game/game_FDB00.c`

Range `0xd0650:0xd0730`; one entry, 224 bytes.
Entry: `func_150D0650`; raw span `0xe0`.
SHA-1: `3bc3ba493e0bbd25ae79dd58c919cb33380defca`.
Reference assembly: `reference/game/us/asm/D0650.s`.

### `src/game/game_10CCD0.c`

Range `0xdf820:0xdf8c0`; one entry, 160 bytes.
Entry: `func_150DF820`; raw span `0xa0`.
SHA-1: `3aac6c721ae934803f0ee98ccc602104ce2ed8f9`.
Reference assembly: `reference/game/us/asm/DF820.s`.

### `src/game/game_117940.c`

Range `0xea490:0xea500`; one entry, 112 bytes.
Entry: `func_150EA490`; raw span `0x70`.
SHA-1: `4d1e228e046c9af367a61fc4741f9ad6aef56bf7`.
Reference assembly: `reference/game/us/asm/E9FE0.s`.

### `src/game/game_123870.c`

Range `0xf63c0:0xf6400`; one entry, 64 bytes.
Entry: `func_150F63C0`; raw span `0x40`.
SHA-1: `8d1af07f63992c9b43881d64013a5a7bd28f136e`.
Reference assembly: `reference/game/us/asm/F5420.s`.

### `src/game/game_126ED0.c`

Range `0xf9a20:0xf9ab0`; one entry, 144 bytes.
Entry: `func_150F9A20`; raw span `0x90`.
SHA-1: `65a16f94bea73b38951dc3e9b60875065ea94e10`.
Reference assembly: `reference/game/us/asm/F9A20.s`.

### `src/game/game_129E80.c`

Range `0xfc9d0:0xfca00`; one entry, 48 bytes.
Entry: `func_150FC9D0`; raw span `0x30`.
SHA-1: `cabf0174834a4400244dcf7999b8262192df8648`.
Reference assembly: `reference/game/us/asm/FB8C0.s`.

### `src/game/game_12B1C0.c`

Range `0xfdd10:0xfdda0`; one entry, 144 bytes.
Entry: `func_150FDD10`; raw span `0x90`.
SHA-1: `be88ee7ba847ffa7ff8fea8359b701274869f748`.
Reference assembly: `reference/game/us/asm/FDD10.s`.

### `src/game/game_130200.c`

Range `0x102d50:0x102d90`; one entry, 64 bytes.
Entry: `func_15102D50`; raw span `0x40`.
SHA-1: `f0c2fdd1d2fbecc61a5d79aa2b714f1e9ac2964c`.
Reference assembly: `reference/game/us/asm/102920.s`.

### `src/game/game_1319D0.c`

Range `0x104520:0x1045e0`; one entry, 192 bytes.
Entry: `func_15104520`; raw span `0xc0`.
SHA-1: `9053b01d25098f010520bfb8994a75850bc8e601`.
Reference assembly: `reference/game/us/asm/104520.s`.

### `src/game/game_1792B0.c`

Range `0x14be00:0x14be20`; one entry, 32 bytes.
Entry: `func_1514BE00`; raw span `0x20`.
SHA-1: `6ac64fe5ea21334de842688af73b8843687c5511`.
Reference assembly: `reference/game/us/asm/149550.s`.

### `src/game/game_1B7480.c`

Range `0x189fd0:0x189ff0`; one entry, 32 bytes.
Entry: `func_15189FD0`; raw span `0x20`.
SHA-1: `53a4494580c3c13db9dbbede1b0f354a158bfd63`.
Reference assembly: `reference/game/us/asm/189900.s`.

### `src/game/game_1BD880.c`

Range `0x1903d0:0x190400`; one entry, 48 bytes.
Entry: `func_151903D0`; raw span `0x30`.
SHA-1: `2ae344fd34b34bfd6f19d062678344c2e097688d`.
Reference assembly: `reference/game/us/asm/18CD20.s`.

### `src/game/game_1D6510.c`

Range `0x1a9060:0x1a90c0`; one entry, 96 bytes.
Entry: `func_151A9060`; raw span `0x60`.
SHA-1: `74e20772029889aed9cee201297e4bcb0b159eae`.
Reference assembly: `reference/game/us/asm/1A7950.s`.

### `src/game/game_1DBB60.c`

Range `0x1ae6b0:0x1ae7b0`; one entry, 256 bytes.
Entry: `func_151AE6B0`; raw span `0x100`.
SHA-1: `3b79c40df71dd78b7c783ff582e7309695cfb823`.
Reference assembly: `reference/game/us/asm/1ABE40.s`.

### `src/game/game_1F3740.c`

Range `0x1c6290:0x1c62d0`; one entry, 64 bytes.
Entry: `func_151C6290`; raw span `0x40`.
SHA-1: `cf7000faecdbcb1c85044932e1c690e99ed17c55`.
Reference assembly: `reference/game/us/asm/1C5280.s`.

## Integration result

Validated with `./conker progress integrate --profile us --all-reviewed`. The command extracted 2,072,880 bytes with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and reported `conker.game.us.integrated.bin: OK`; the complete US game overlay was byte-identical.
