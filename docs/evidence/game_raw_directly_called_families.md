# US directly called raw families

Evidence kind: `structural_analysis`. These twenty-four complete raw-map
segments contain functions reached by direct `jal` calls from outside their
range. In each multi-function segment every member has an external caller; the
remaining segments contain one externally called function. Generic source
names derive from retail-ROM offsets; every member remains raw assembly.

The raw assembly index and independent US function CSV agree on every member
and span. All outer endpoints are 16-byte aligned and no conditional branch
crosses an endpoint.

| Source | US range | Entries | Bytes | External call sites | Debug strong/mapped | ECTS strong/mapped | Range SHA-1 |
| --- | --- | ---: | ---: | ---: | ---: | ---: | --- |
| `src/game/game_13ABD0.c` | `0x10D720:0x10D970` | 5 | 592 | 7 | 2/4 | 1/2 | `057da994e56334a106cb431e17e82c761c7ab5bc` |
| `src/game/game_156160.c` | `0x128CB0:0x129C30` | 3 | 3,968 | 4 | 0/1 | 0/1 | `15c5e632e61bbb903a6cd225a5b824466aad3b8f` |
| `src/game/game_2D540.c` | `0x90:0x940` | 3 | 2,224 | 4 | 0/1 | 0/0 | `e369109dd50c58007ff3f88ff189575ec6cb3f41` |
| `src/game/game_12FDD0.c` | `0x102920:0x102D50` | 2 | 1,072 | 19 | 1/1 | 0/0 | `c9521b2f5c79cf7f4a5454d351ab42bc7cdcd71e` |
| `src/game/game_14F8F0.c` | `0x122440:0x122AE0` | 2 | 1,696 | 4 | 1/1 | 1/1 | `9f13a61853154dd1a266a7a25319b41cd3ab273f` |
| `src/game/game_D4C40.c` | `0xA7790:0xA7960` | 1 | 464 | 30 | 1/1 | 0/0 | `b8f2a7c3eb85814d9bfbdf6c445a0c03ec739fec` |
| `src/game/game_49BE0.c` | `0x1C730:0x1C860` | 1 | 304 | 16 | 0/0 | 0/0 | `63fc334c675bcdfbbee45c801e5894f396992962` |
| `src/game/game_D5070.c` | `0xA7BC0:0xA7C10` | 1 | 80 | 13 | 0/1 | 0/0 | `f004462f81ca7fb7e94b2d39fca8bedf41739728` |
| `src/game/game_FA240.c` | `0xCCD90:0xCCEB0` | 1 | 288 | 6 | 1/1 | 1/1 | `15c45195cdf9be268293777c5ffec03ea1ab7487` |
| `src/game/game_DAE10.c` | `0xAD960:0xAD9A0` | 1 | 64 | 6 | 1/1 | 0/0 | `378dc48efa20d69957e24ae73a767e51a6415510` |
| `src/game/game_15B5F0.c` | `0x12E140:0x12E4B0` | 1 | 880 | 5 | 0/0 | 0/0 | `3a2ede2c0ebb3a9911958a4312b56974ae3d76cb` |
| `src/game/game_DAD60.c` | `0xAD8B0:0xAD900` | 1 | 80 | 5 | 1/1 | 0/0 | `90b9ae76628e8ca1945d3bed97f6687b2ef47b12` |
| `src/game/game_155C90.c` | `0x1287E0:0x128CB0` | 1 | 1,232 | 4 | 0/0 | 0/0 | `7c24a126204c9c667fd367c21c324e8ac24811d0` |
| `src/game/game_1312F0.c` | `0x103E40:0x104170` | 1 | 816 | 3 | 0/0 | 0/0 | `7ab51dfbcf556b8e7e3459d039b2ae4db441ebbf` |
| `src/game/game_1EBD00.c` | `0x1BE850:0x1BEB20` | 1 | 720 | 3 | 0/0 | 0/0 | `3487ddac76345907caf55c5f37aac94d0300f812` |
| `src/game/game_138390.c` | `0x10AEE0:0x10B070` | 1 | 400 | 3 | 1/1 | 1/1 | `44461bcde34dba0d994e8ebabd2901203e52e47d` |
| `src/game/game_1D92B0.c` | `0x1ABE00:0x1ABE40` | 1 | 64 | 3 | 0/0 | 0/0 | `03bd1e138bbe0d20445deecd77e88d1a07c0f76e` |
| `src/game/game_EE710.c` | `0xC1260:0xC1660` | 1 | 1,024 | 2 | 1/1 | 0/0 | `b5ba15977e500bf93e6c3d9b25f8b1cda89d4e0a` |
| `src/game/game_1B8B60.c` | `0x18B6B0:0x18BA90` | 1 | 992 | 2 | 1/1 | 0/0 | `c5f569c368c612c17e3ca1edf58452b4fbf008df` |
| `src/game/game_10DD20.c` | `0xE0870:0xE0BE0` | 1 | 880 | 2 | 0/0 | 0/0 | `44624b01a6ff6c546921525f2aa3f2333e80c5a2` |
| `src/game/game_10EA20.c` | `0xE1570:0xE1800` | 1 | 656 | 2 | 0/0 | 0/0 | `e881110dfb8c23131d637ee2ec1a7fa39f1f375d` |
| `src/game/game_1228D0.c` | `0xF5420:0xF5590` | 1 | 368 | 2 | 1/1 | 1/1 | `8f2760075eaf54b1ab8bcb234ca470039d61eac6` |
| `src/game/game_1792D0.c` | `0x14BE20:0x14BF50` | 1 | 304 | 2 | 1/1 | 1/1 | `0539aa5c54dba743edcb62e769e40020e36d1a47` |
| `src/game/game_1238B0.c` | `0xF6400:0xF6420` | 1 | 32 | 2 | 1/1 | 0/0 | `c9a721780becdad6062d72d3d5c6d32ff67c2c8c` |

The multi-member ranges have complete call coverage: all five members in
`0x10D720:0x10D970`, all three in `0x90:0x940` and
`0x128CB0:0x129C30`, and both members in the remaining pairs. The singleton
groups are bounded by their exact indexed function spans and neighboring map
entries; repeated direct callers independently confirm each entry point.
