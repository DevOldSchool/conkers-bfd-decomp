# US isolated selector and call families

Evidence kind: `structural_analysis`. These twelve complete raw-map segments
contain an exact function pointer in owned game data or a direct local call
linking their members. Generic source names derive from retail-ROM offsets;
every member remains raw assembly.

The raw assembly index and independent US function CSV agree on every member
and span. All outer endpoints are 16-byte aligned and no conditional branch
crosses an endpoint.

| Source | US range | Entries | Bytes | Exact evidence | Range SHA-1 |
| --- | --- | ---: | ---: | --- | --- |
| `src/game/game_1F1F60.c` | `0x1C4AB0:0x1C5280` | 2 | 2,000 | `func_151C4AB0` at `0x80089F84` | `b86958f19b3e817cceea18d8617843a9950d00e0` |
| `src/game/game_1E6260.c` | `0x1B8DB0:0x1B9310` | 2 | 1,376 | `func_151B9214` at `0x800898D4` | `3ee9d8fd4929bfcba530a3fc6d201010898c56c7` |
| `src/game/game_1BDB90.c` | `0x1906E0:0x190770` | 2 | 144 | `func_151906E0` at `0x8008D688` | `55e30666d2f63ea121ec4cb4d5de57d84b990648` |
| `src/game/game_1B8F40.c` | `0x18BA90:0x18BD60` | 3 | 720 | `func_1518BA90` calls `func_1518BCD0` | `911ed9ec548a6d3707df777154253b7d4b3ea76f` |
| `src/game/game_1A5440.c` | `0x177F90:0x178750` | 2 | 1,984 | `func_15178268` at `0x8008C9E0` | `3b5b2c8769f5994c58dd0097be2b1be8395de4e4` |
| `src/game/game_186080.c` | `0x158BD0:0x158D00` | 2 | 304 | `func_15158CD4` at `0x8008BE28` | `44b49681d391ff50da76e56165405d5974130bef` |
| `src/game/game_128790.c` | `0xFB2E0:0xFB4C0` | 2 | 480 | `func_150FB2E0` at `0x8008AD00` | `5af06a5c0836ac38267abc1de9201df8c90d7a4a` |
| `src/game/game_120860.c` | `0xF33B0:0xF34A0` | 2 | 240 | `func_150F33B0` at `0x80089080` | `f09438f23d248df3449677818698316c6a318f67` |
| `src/game/game_119370.c` | `0xEBEC0:0xEC4B0` | 3 | 1,520 | `func_150EC45C` at `0x8008FBDC` | `349b34a26484e2abd9ca2a13e4a234b7403d8f6c` |
| `src/game/game_109220.c` | `0xDBD70:0xDCEA0` | 2 | 4,400 | `func_150DC558` at `0x8008A210` | `dbd76584be08c739bbcfd22fe6d6cb1640d52cbe` |
| `src/game/game_803A0.c` | `0x52EF0:0x53430` | 4 | 1,344 | `func_15052EF0` at `0x80086050` | `04f37a9a4f419daebec89ce971cd85d7b5404c1e` |
| `src/game/game_6C960.c` | `0x3F4B0:0x3F800` | 4 | 848 | `func_1503F62C` calls `func_1503F5B8` | `8a68368e2b7b079a2fb131169429f22cc67432a3` |

The pointer addresses refer to exact words in
`build/library-research/game.data.bin`, whose runtime base is `0x80082B20`.
The separate `0x1DD140:0x1DD3A0` call-connected range was later assigned to
the Rare `libultrare/io/conteepread` source boundary rather than game
source.
