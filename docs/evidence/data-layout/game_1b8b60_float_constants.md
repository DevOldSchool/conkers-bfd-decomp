# US game_1B8B60 particle constants

`func_1518B6B0` initialises a particle with a fixed lift and drag and then spawns
copies with a random scale. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_1B8B60/func_1518B6B0.s` (`1518B708`/`1518B70C`,
`1518B710`/`1518B718`, `1518B7B8`/`1518B7BC`, `1518B7C0`/`1518B7C4`) address the four
words 0x800A7400..0x800A740F; no other reference function touches them. The
checksum-validated US game-data archive (ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20) holds
`3ECCCCCD BFA66666 3F333333 3E99999A` there, exactly `0.4f`, `-1.3f`, `0.7f` and
`0.3f`. With `extern f32` symbols the deferred body scored CURRENT 5061; as literals
the function is `CURRENT (0)`.

The generated `game_1B8B60.o` has 0x10 bytes of `.rodata`: the four constants in ROM
order with no alignment padding and no data relocations. `config/game/us-rodata.ld`
maps it as an INFO section at 0x800A7400 with a 0x10 extent assertion and a 0x10
payload; `config/data/us.json` records the owner. The range lies between the
game_1B81D0 extent (ending at 0x800A73FF) and the game_1B8F40 pool at 0x800A7410. No
reference assembly, compiler flag or verifier change is involved.
