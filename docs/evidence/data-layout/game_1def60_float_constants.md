# US game_1DEF60 billboard emitter float constants

`func_151B1B34` accumulates a spawn budget and emits 0x70-byte billboard
descriptors through `func_15130374`. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_1DEF60/func_151B1B34.s` address seven consecutive words at
0x800AA300..0x800AA31B; no other reference function touches them. The
checksum-validated US game-data archive (ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20) holds
`442E4000 3A83126F 3F8374BD 3F6C8B44 44BB2000 4478C000 3C23D70A` there:
`697.0f`, `0.001f`, `1.0270001f`, `0.924f`, `1497.0f`, `995.0f` and `0.01f` in
load order. `1.0270001f` is written that way because IDO rounds `1.027f` to
`3F8374BC`. The other float operands (`1.0f`, `342.0f`, `36.0f`, `104.0f`,
`199.0f`, `0.0f`) are built with `lui`/`mtc1` and need no rodata.

The generated `game_1DEF60.o` has 0x20 bytes of `.rodata`: the seven constants
and 4 zero alignment bytes, with no data relocations. 0x800AA31C is zero in the
ROM, and 0x800AA320 begins the next pool. `config/game/us-rodata.ld` maps it as
an INFO section at 0x800AA300 with a 0x20 extent assertion and a 0x1C payload;
`config/data/us.json` records the owner. The preceding word 0x800AA2FC belongs
to game_1DD500 ([record](game_1dd500_float_constant.md)), whose informational
alignment bytes overlap this pool's first 12 bytes.

The two `{19.0f, 0.0f, 25.0f}` vectors at 0x8008FAD0 and 0x8008FADC are game
`.data` and stay unit-local `extern Vec3f` declarations (as in game_1E73B0);
the other members, `func_151B1AB0` and `func_151B1FAC`, read no rodata. No
reference assembly, compiler flag or verifier change is involved.
