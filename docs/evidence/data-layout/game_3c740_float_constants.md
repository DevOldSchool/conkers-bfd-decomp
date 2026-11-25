# US game_3C740 float constants

`func_1500F40C` spawns four emitters through `func_1500F290` and nine path descriptors through
`func_15189900`. Its non-`lui` float literals are emitted in use order (IDO emits one word per use,
so repeated path points appear twice): `-1692.0f`, `4054.0f`, `3890.0f`, `4380.0f`, `4218.0f`
for the emitters, then `2686.0f`, `2063.0f`, `0.24000002f`, `0.497f`, `0.31500003f`, `-1667.0f`,
`2810.0f`, `1637.0f`, the descriptor angle scale `40.743664f`, and the remaining path points
`-1667.0f`, `2810.0f`, `1637.0f`, `2667.0f`, `-1668.0f`, `1236.0f`, `2667.0f`, `-1668.0f`, `1236.0f`,
`2220.0f`, `-1676.0f`, `1025.0f`, `1894.0f`, `-1674.0f`, `1841.0f`, `-1677.0f`, `557.0f`, `1841.0f`,
`-1677.0f`, `557.0f`, `1594.0f`, `-1678.0f`, `455.0f`, `1594.0f`, `455.0f`, `-1678.0f`, `613.0f`,
`1253.0f`, `-1673.0f`, `1075.0f`, `-1682.0f`, `1075.0f`, `-1682.0f`, `687.0f`, `687.0f`, `-1676.0f`
and `931.0f`. Constants with zero low halfwords (`2.0f`, `6.0f`, `7.0f`, `10.0f`, `788.0f`,
`1400.0f`, `668.0f`, `572.0f`, `872.0f`, `-1680.0f`, `772.0f`) and the `0.0f` stores are built with
`lui`/`mtc1` and need no pool.

Its raw HI16/LO16 pairs in `asm/nonmatchings/game_3C740/func_1500F40C.s` address
0x80096250..0x80096318; no other reference function reads them. The checksum-validated US
game-data archive (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`,
read through `scripts/rom_span.py`) holds, from `0x80096250`:

```
C4D38000 457D6000 45732000 4588E000 4583D000 4527E000 4500F000 3E75C291
3EFE76C9 3EA147AF C4D06000 452FA000 44CCA000 4222F983 C4D06000 452FA000
44CCA000 4526B000 C4D08000 449A8000 4526B000 C4D08000 449A8000 450AC000
C4D18000 44802000 44ECC000 C4D14000 44E62000 C4D1A000 440B4000 44E62000
C4D1A000 440B4000 44C74000 C4D1C000 43E38000 44C74000 43E38000 C4D1C000
44194000 449CA000 C4D12000 44866000 C4D24000 44866000 C4D24000 442BC000
442BC000 C4D18000 4468C000
```

exactly those literals, which reach `CURRENT (0)` in the C source. The word at `0x8009631C` is
zero and the next unit's words start at `0x80096320`; the zero words at `0x80096248..0x8009624F`
are the preceding unit's alignment.

The other members, `func_1500F290` and `func_1500F378`, emit no `.rodata` (`110.0f` is built with
`lui`), so the generated `game_3C740.o` has a 0xD0-byte `.rodata`: the 0xCC payload and 4 zero
alignment bytes, with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section
at `0x80096250` with a 0xD0 extent assertion and a 0xCC payload symbol; `config/data/us.json`
records the owner. No assembly, compiler flag or verifier change is involved.
