# US game_DF2D0 particle float constants

`func_150B1F90` accumulates a spawn budget and, while it exceeds one, emits particles from a descriptor packet
and a 0x10-byte extension. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_DF2D0/func_150B1F90.s` address the eight words 0x8009F8E0..0x8009F8FF. The checksum-validated
US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3DA0F909 3D0DB8BB 3F7ABA06
3F821BFC 43CA8000 43FB8000 3E0A3D71 3E560419` there: the single-precision values of `0.0786f`, `0.0346f`,
`0.979401f`, `1.016479f`, `405.0f`, `503.0f`, `0.135f` and `0.209f`.

The `405.0f` and `503.0f` words come from the integer literals in `func_150ADA68() * 503 + 405`, which IDO converts
at compile time and keeps in rodata. The raw function loads the scale and speed constants once, before the spawn
loop, the literal-pool pattern; with extern symbols the candidate scored CURRENT 1136, and with the literals (and the
descriptor's `flags` word typed `u32`, which the raw `or` of the two random flip bits requires) the function is
`CURRENT (0)`. The descriptor type is local to this unit and used only by this function.

The generated `game_DF2D0.o` has exactly 0x20 bytes of `.rodata`, all payload, with no data relocations.
`config/game/us-rodata.ld` maps it as an INFO section at `0x8009F8E0` with a 0x20 extent assertion and a 0x20
payload; `config/data/us.json` records the owner. The preceding word 0x8009F8DC is not part of this unit's pool and
the following word 0x8009F900 (`3F5BE76D`, 0.859f) is read through an extern by the matched `game_DF930`, so the object has no
alignment tail over unowned words. No reference assembly, compiler flag or verifier change is involved.
