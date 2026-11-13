# US game_10C170 particle constants

`func_150DF4B8` emits a burst of tinted particles with random scales. Its raw HI16/LO16
pairs in `asm/nonmatchings/game_10C170/func_150DF4B8.s` address the eleven words
0x800A0F28..0x800A0F53; no other reference function touches them. The checksum-validated
US game-data archive (ROM SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
0x80082B20) holds `41B4CCCD 415C9375 4267E042 422ADB23 42ED86A8 461C4000 3D3851EC 3F333333
4267E042 422ADB23 42ED86A8` there: exactly `22.6f`, `13.786f`, `57.969f`, `42.714f`,
`118.763f`, `10000.0f`, `0.045f`, `0.7f`, `57.969f`, `42.714f` and `118.763f` (IDO keeps
the repeated values as separate pool words). With `extern f32` symbols the deferred body
scored CURRENT 7325; as literals the function is `CURRENT (0)`.

The generated `game_10C170.o` has 0x2C payload bytes of `.rodata` (the eleven constants in
ROM order, no data relocations) padded to a 0x30 object extent. `config/game/us-rodata.ld`
maps it as an INFO section at 0x800A0F28 with a 0x30 extent assertion and a 0x2C payload;
`config/data/us.json` records the owner. The neighbouring words
0x800A0F20..0x800A0F27 are outside the owned payload, and 0x800A0F54 onward is zero. No reference assembly, compiler flag or verifier
change is involved.
