# Extended US pointer-selected raw segments

Evidence kind: `structural_analysis`. These twelve complete raw-map segments
combine exact function pointers in the owned game-data image with local calls
and preserved beta order. Generic source names derive from retail-ROM offsets;
every member remains raw assembly.

The raw assembly index and independent US function CSV agree on every entry and
span listed in the table. All outer endpoints are 16-byte aligned and no
conditional branch crosses an endpoint. Beta correlations support identity and
order only.

| Source | US range | Entries | Bytes | Selected | Local edges | Debug strong/mapped | ECTS strong/mapped | Range SHA-1 |
| --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| `src/game/game_1D2B10.c` | `0x1A5660:0x1A5F70` | 5 | 2,320 | 3 | 2 | 3/5 | 2/4 | `3b4df9ee049d575c4f0327aa092e5e7b00ca0aa9` |
| `src/game/game_1D6570.c` | `0x1A90C0:0x1A99D0` | 6 | 2,320 | 3 | 0 | 6/6 | 4/4 | `5bbb2ff2f3da6e69e5e6ed0bfafe62ddca40e250` |
| `src/game/game_11C2B0.c` | `0xEEE00:0xEF7B0` | 5 | 2,480 | 2 | 1 | 4/4 | 3/3 | `2365aa26fbbfe55c7248797c10b17cfa41f88ee2` |
| `src/game/game_176A00.c` | `0x149550:0x149FD0` | 7 | 2,688 | 6 | 0 | 7/7 | 4/5 | `8ad2a6278c73542e4af79308c833dcab2159f12a` |
| `src/game/game_143DE0.c` | `0x116930:0x1174A0` | 7 | 2,928 | 5 | 2 | 7/7 | 6/6 | `9846e225f5f185927af278e707c1385fb1eec066` |
| `src/game/game_104AE0.c` | `0xD7630:0xD82B0` | 4 | 3,200 | 2 | 0 | 3/3 | 0/0 | `6f9b0285bf5c89ea3d5b888e882d1fa724ae3ad9` |
| `src/game/game_FA360.c` | `0xCCEB0:0xCDBB0` | 5 | 3,328 | 3 | 0 | 5/5 | 2/3 | `922e7324fc9c890b825e883ccc7b763940eda20f` |
| `src/game/game_122B60.c` | `0xF56B0:0xF63C0` | 9 | 3,344 | 7 | 2 | 6/9 | 1/1 | `7a1cfdfcde78094adbf8e34d0369560352cbae6a` |
| `src/game/game_128D70.c` | `0xFB8C0:0xFC930` | 5 | 4,208 | 3 | 1 | 3/3 | 3/3 | `69a278b0ab0accf5981ae5a8830c90a8318f5cb8` |
| `src/game/game_114B80.c` | `0xE76D0:0xE88C0` | 9 | 4,592 | 3 | 0 | 9/9 | 4/6 | `be00c118d240ee21388f16def0e902846e096734` |
| `src/game/game_1368C0.c` | `0x109410:0x10A870` | 8 | 5,216 | 5 | 0 | 8/8 | 7/7 | `bdbe52e04099058ea49dca88f7f531a00350f74e` |
| `src/game/game_177B50.c` | `0x14A6A0:0x14BE00` | 11 | 5,984 | 5 | 1 | 8/11 | 6/9 | `52c355392325aad06387247673ae500fc2447ebe` |

## Owned data selections

The exact big-endian words below occur in
`build/library-research/game.data.bin`, whose runtime base is `0x80082B20`.

| US range | Selected function -> owned word address |
| --- | --- |
| `0x1A5660:0x1A5F70` | `func_151A5660` -> `0x8008A500`; `func_151A5CAC` -> `0x8008A6B0`; `func_151A5CEC` -> `0x8008A7D8` |
| `0x1A90C0:0x1A99D0` | `func_151A90C0` -> `0x8008F984` through `0x8008F998`; `func_151A91AC` -> `0x8008F970`; `func_151A9634` -> `0x8008F974` |
| `0xEEE00:0xEF7B0` | `func_150EF38C` -> `0x80089D2C`; `func_150EF784` -> `0x80086CA0` |
| `0x149550:0x149FD0` | `func_15149838` -> `0x80089D94`; `func_15149A94` -> `0x80089D98`; `func_15149BF4` -> `0x80089D9C`; `func_15149C58` -> `0x80089DA0`; `func_15149D18` -> `0x80089E44`; `func_15149EC4` -> `0x80089E14` |
| `0x116930:0x1174A0` | `func_15116930` -> `0x80088E98`; `func_15116984` -> `0x80088E94`; `func_151169B4` -> `0x80089008`; `func_15116D7C` -> `0x80089014`; `func_15116EA4` -> `0x80089020` |
| `0xD7630:0xD82B0` | `func_150D7630` -> `0x8008CD64`; `func_150D7928` -> `0x80086094` |
| `0xCCEB0:0xCDBB0` | `func_150CD17C` -> `0x80089D04`, `0x80089DD8`; `func_150CD59C` -> `0x80089E60`; `func_150CD7F8` -> `0x8008A544` |
| `0xF56B0:0xF63C0` | `func_150F56B0` -> `0x800841D0`; `func_150F5A54` -> `0x80084214`; `func_150F5C98` -> `0x8008A62C`; `func_150F6138` -> `0x8008A9D0`; `func_150F6178` -> `0x8008A638`; `func_150F6368` -> `0x8008A758`; `func_150F6394` -> `0x8008A880` |
| `0xFB8C0:0xFC930` | `func_150FC368` -> `0x8008FBE0`; `func_150FC614` -> `0x8008A584`; `func_150FC818` -> `0x8008A96C` |
| `0xE76D0:0xE88C0` | `func_150E7C9C` -> `0x8008A528`; `func_150E8470` -> `0x8008A588`; `func_150E8824` -> `0x800897C4` |
| `0x109410:0x10A870` | `func_151094FC` -> `0x8008A550`; `func_15109848` -> `0x80088C64`; `func_15109C20` -> `0x80088C68`; `func_15109FB8` -> `0x8008A554`; `func_1510A40C` -> `0x8008A558` |
| `0x14A6A0:0x14BE00` | `func_1514A6A0` -> `0x80089E2C`; `func_1514AF74` -> `0x80089DD0`; `func_1514B844` -> `0x8008A428`; `func_1514B87C` -> `0x80089D00`; `func_1514B8B0` -> `0x80089DD4` |

Local relationships independently connect members in four ranges:
`func_151A5CAC` and `func_151A5CEC` call `func_151A5D2C`;
`func_150EEE00` calls `func_150EEF80`; `func_15116984` calls
`func_151169B4`, which calls `func_15116BAC`; `func_150F6368` and
`func_150F6394` call `func_150F631C`; `func_150FC614` calls opening
`func_150FB8C0`; and `func_1514B364` calls `func_1514B034`.

## Reconciled candidate at `0xADAF0:0xAE5B0`

The owned data image selects `func_150AE35C` and `func_150AE36C`. The
independent function CSV records three entries while the raw assembly index
records four because the linear detector folds externally called alternate
entry `func_150AE280` into the preceding handwritten routine. The range was
later mapped with the entry evidence recorded in
`docs/evidence/game_raw_exception_entry_family.md`.
