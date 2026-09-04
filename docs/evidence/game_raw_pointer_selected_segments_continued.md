# Continued US pointer-selected raw segments

Evidence kind: `structural_analysis`. These fourteen complete raw-map segments
combine exact function pointers in the owned game-data image with preserved
beta order. Generic source names derive from retail-ROM offsets; every member
remains raw assembly.

The raw assembly index and the independent US function CSV agree on every
entry and span. All outer endpoints are 16-byte aligned and no conditional
branch crosses an endpoint. Beta correlations support function identity and
order only; the owned data selections and complete raw spans establish the
working boundaries.

| Source | US range | Entries | Bytes | Selected members | Debug strong/mapped | ECTS strong/mapped | Range SHA-1 |
| --- | --- | ---: | ---: | ---: | ---: | ---: | --- |
| `src/game/game_1BD940.c` | `0x190490:0x190550` | 3 | 192 | 2 | 0/2 | 1/2 | `cff4765ba71416d961d2f4cb3c80c13a2c017cda` |
| `src/game/game_10D080.c` | `0xDFBD0:0xDFDD0` | 3 | 512 | 1 | 3/3 | 3/3 | `53119d29389beff6f9c8538ddb19583848d7b7cb` |
| `src/game/game_97F90.c` | `0x6AAE0:0x6AD30` | 6 | 592 | 5 | 1/2 | 2/2 | `7e83f0df057161e797589e25ecc7fd9f059d72a7` |
| `src/game/game_12D7F0.c` | `0x100340:0x100600` | 2 | 704 | 1 | 2/2 | 2/2 | `855d5c4434c53af11fb5e8d0b7906c5bb8238957` |
| `src/game/game_105A40.c` | `0xD8590:0xD88E0` | 3 | 848 | 1 | 3/3 | 1/1 | `af4bee6d23810362c90900918fbb26276974ac65` |
| `src/game/game_1179B0.c` | `0xEA500:0xEA8E0` | 2 | 992 | 1 | 2/2 | 2/2 | `e043336877b222a823b3a6ad462ba3aedab78e7b` |
| `src/game/game_1CDEC0.c` | `0x1A0A10:0x1A0E40` | 3 | 1,072 | 2 | 3/3 | 0/1 | `3baf50a91de985f013f9fa4e2a46cedd3d917a6c` |
| `src/game/game_117490.c` | `0xE9FE0:0xEA490` | 3 | 1,200 | 2 | 1/3 | 1/3 | `dcdd9833cb950b4c6a980549299688713ee06c84` |
| `src/game/game_1BFDD0.c` | `0x192920:0x192DF0` | 3 | 1,232 | 2 | 2/3 | 2/3 | `1678737c636fde4ba289983ee8c69f08cd93f6ab` |
| `src/game/game_FE340.c` | `0xD0E90:0xD13A0` | 4 | 1,296 | 3 | 3/4 | 1/2 | `40dd0aa57e47346c60ae51eebc1c9caaa79dcca0` |
| `src/game/game_F21D0.c` | `0xC4D20:0xC5280` | 3 | 1,376 | 2 | 3/3 | 0/1 | `39b709570f9225fc450ff80ceffd5971a1f8d3de` |
| `src/game/game_1C0B10.c` | `0x193660:0x193CA0` | 4 | 1,600 | 2 | 4/4 | 3/3 | `aa4eac500baa153ee2776b8c3f8d2fe9cfcefada` |
| `src/game/game_130240.c` | `0x102D90:0x103430` | 3 | 1,696 | 2 | 2/2 | 0/0 | `8918419c52eae966406e59ceef753a115ee611c4` |
| `src/game/game_FC9E0.c` | `0xCF530:0xCFC60` | 7 | 1,840 | 4 | 7/7 | 3/3 | `46ec3d709b73049eda39552a8f1879adff6639dd` |

## Owned data selections

The following exact big-endian words occur in
`build/library-research/game.data.bin`, whose runtime base is `0x80082B20`.
Each value is the selected function's game-overlay runtime address.

| US range | Selected function -> owned word address |
| --- | --- |
| `0x190490:0x190550` | `func_15190490` -> `0x8008B344`; `func_151904BC` -> `0x8008FC60` |
| `0xDFBD0:0xDFDD0` | `func_150DFCA8` -> `0x80088EAC` |
| `0x6AAE0:0x6AD30` | `func_1506AAE0` -> `0x80086138`; `func_1506AB7C` -> `0x8008613C`; `func_1506ABC4` -> `0x80086148`; `func_1506AC0C` -> `0x80086140`; `func_1506AC58` -> `0x80086144` |
| `0x100340:0x100600` | `func_15100340` -> `0x8008CD2C` |
| `0xD8590:0xD88E0` | `func_150D88AC` -> `0x8008B200` |
| `0xEA500:0xEA8E0` | `func_150EA5CC` -> `0x80089A8C` |
| `0x1A0A10:0x1A0E40` | `func_151A0AF8` -> `0x8008A4EC`; `func_151A0C0C` -> `0x8008AA10` |
| `0xE9FE0:0xEA490` | `func_150EA10C` -> `0x80089B24`; `func_150EA11C` -> `0x80089B40` |
| `0x192920:0x192DF0` | `func_15192920` -> `0x8008F848`; `func_151929A4` -> `0x8008A538` |
| `0xD0E90:0xD13A0` | `func_150D0E90` -> `0x8008CD50`; `func_150D11B4` -> `0x80089B34`; `func_150D1204` -> `0x80089B54` |
| `0xC4D20:0xC5280` | `func_150C4D20` -> `0x80088E40`; `func_150C4E9C` -> `0x80088E4C` |
| `0x193660:0x193CA0` | `func_151938E4` -> `0x80089B28`; `func_151938FC` -> `0x80089B44` |
| `0x102D90:0x103430` | `func_15102D90` -> `0x80089D5C`; `func_15102EB8` -> `0x80089E74` |
| `0xCF530:0xCFC60` | `func_150CF530` -> `0x8008A5D4`; `func_150CF578` -> `0x8008CD54`; `func_150CF800` -> `0x8008ACF8`; `func_150CFBEC` -> `0x8008AD24` |
