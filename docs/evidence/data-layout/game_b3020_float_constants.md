# US game_B3020 range constants

`func_15085BE8` builds per-axis minimum/maximum bounds over the active waypoint set and
seeds them with sentinel values. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_B3020/func_15085BE8.s` address the three words
0x8009D9C0..0x8009D9CB; no other reference function touches them. The checksum-validated
US game-data archive (ROM SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
0x80082B20) holds `C61C4000 461C4000 47C35000` there, exactly `-10000.0f`, `10000.0f` and
`100000.0f`. With `extern f32` symbols the deferred body scored CURRENT 4345; as literals
the function is `CURRENT (0)`.

The generated `game_B3020.o` has 0xC payload bytes of `.rodata` (the three constants in
ROM order, no data relocations) padded to a 0x10 object extent. `config/game/us-rodata.ld`
maps it as an INFO section at 0x8009D9C0 with a 0x10 extent assertion and a 0xC payload;
`config/data/us.json` records the owner. The range lies between the game_B21B0 jump table
(ending at 0x8009D9BF) and 0x8009D9CC, which stays an extern read of the
matched `func_15085DF8`. No reference assembly, compiler flag or verifier change is
involved.
