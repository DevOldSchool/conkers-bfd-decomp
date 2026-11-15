# US game_1D2B10 region emitter float constants

`func_151A5660` accumulates a spawn budget for a region emitter and spawns particles inside the region's rotated
shape. Its raw HI16/LO16 pairs in `asm/nonmatchings/game_1D2B10/func_151A5660.s` address the six words
`0x800A8D80..0x800A8D97` in first-use order; no other reference function touches them. The checksum-validated US ROM
(SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3F360B61 41B4CCCD 415C9375
4267E042 422ADB23 42ED86A8` there, the single-precision values of `0.7111111f`, `22.6f`, `13.786f`, `57.969f`,
`42.714f` and `118.763f`. The raw function had no C candidate; with these literals (and its local region, emitter and
particle typedefs) it is `CURRENT (0)`.

The generated `game_1D2B10.o` has 0x20 bytes of `.rodata`: the 0x18-byte payload and 8 zero alignment bytes, with no
data relocations; no other member of the unit emits rodata. `config/game/us-rodata.ld` maps it as an INFO section at
`0x800A8D80` with a 0x20 extent assertion and a 0x18 payload; `config/data/us.json` records the owner. The range
lies in the free gap between the `game_1CE2F0` pool and the `game_1D3AB0` pool at `0x800A8DA0`; the alignment bytes
fall at `0x800A8D98..0x800A8D9F`, over words `game_1D3420` reads through extern symbols, and only the payload is
compared. No reference assembly, compiler flag or verifier change is involved.
