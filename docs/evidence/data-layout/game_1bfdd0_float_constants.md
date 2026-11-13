# US game_1BFDD0 emitter constants

`func_151929A4` spawns a side-flipping emitter burst. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_1BFDD0/func_151929A4.s` address the five words 0x800A8180..0x800A8193;
no other reference function touches them. The checksum-validated US game-data archive (ROM
SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20) holds
`4415C000 3A83126F 3F851EB8 3F733334 BFC20C4A` there: exactly `599.0f`, `0.001f`, `1.04f`,
`0.95000005f` (the shortest spelling of 0x3F733334; `0.95f` would be 0x3F733333) and
`-1.516f`. With `extern f32` symbols the deferred body scored CURRENT 550; as literals the
function is `CURRENT (0)`.

The matching call passes `&emitter` to `func_15130374` without an integer cast. That
callee's matched definition in `src/game/game_15D730.c` already converted its first
parameter with `(void *)arg0`, so its definition (and the same-file prototype and call in
`func_151303BC`) now take `void *arg0`; both functions stay `CURRENT (0)`, and the
`game_1BFDD0.c` prototype matches the definition.

The generated `game_1BFDD0.o` has 0x14 payload bytes of `.rodata` (the five constants in ROM
order, no data relocations) padded to a 0x20 object extent. `config/game/us-rodata.ld` maps
it as an INFO section at 0x800A8180, directly after the game_1BFCB0 extent, with a 0x20
extent assertion and a 0x14 payload; `config/data/us.json` records the owner. No reference
assembly, compiler flag or verifier change is involved.
