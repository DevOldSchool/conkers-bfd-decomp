# US game_188440 smoke emitter constants

`func_1515B21C` emits smoke puffs with random size, wobble and spin. Its raw HI16/LO16
pairs in `asm/nonmatchings/game_188440/func_1515B21C.s` (`1515B338`/`1515B33C`,
`1515B340`/`1515B344`, `1515B3C0`/`1515B3C4`, `1515B3C8`/`1515B3CC`,
`1515B3D0`/`1515B3D4`, `1515B400`/`1515B404`, `1515B54C`/`1515B550`,
`1515B560`/`1515B564`) address the eight words 0x800A6438..0x800A6457; no other
reference function touches them. The checksum-validated US game-data archive (ROM
SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20) holds
`3F99999A 3F555555 3D75C28F 3D8F5C29 3E19999A 3DCCCCCD 447B4000 3A83126F` there,
exactly `1.2f`, `0.8333333f`, `0.06f`, `0.07f`, `0.15f`, `0.1f`, `1005.0f` and
`0.001f`. With `extern f32` symbols the deferred body scored CURRENT 5086; as
literals the function is `CURRENT (0)`.

The matching body passes the particle address to `func_151303BC` without an integer
cast. The file-local prototype now reads `void *func_151303BC(void *, u8, s32)`, and
the matched definition in `src/game/game_15D730.c` takes `void *arg0` (casting it to
`s32` for `func_15130374`); that definition stays `CURRENT (0)`.

`func_1515B674` spawns a burst of ten smoke particles. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_188440/func_1515B674.s` address the five words
0x800A6458..0x800A646B, which hold `44C56000 3C23D70A 3A83126F 43F48000 43968000`:
exactly `1579.0f`, `0.01f`, `0.001f`, `489.0f` and `301.0f`. Written as those
literals (and with `count = (func_150ADA20() % 1U) + 10`, the RAND_RANGE form already
used in `game_115F30.c` and `game_1F3780.c`, which keeps the reference's `divu` and
`count--` guard) the deferred body (CURRENT 5500) reaches `CURRENT (0)`.

The generated `game_188440.o` has 0x34 payload bytes of `.rodata`: the eight
`func_1515B21C` constants then the five `func_1515B674` constants in ROM order, with
no data relocations, padded to a 0x40 object extent. `config/game/us-rodata.ld` maps
it as an INFO section at 0x800A6438 with a 0x40 extent assertion and a 0x34 payload;
`config/data/us.json` records the owner. The word at 0x800A646C is zero in ROM; the
alignment tail beyond it is not part of the owned payload. The words
0x800A6420..0x800A6437 stay extern reads of the deferred `func_1515AF90`. No
reference assembly, compiler flag or verifier change is involved.
