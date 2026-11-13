# US game_1FBB80 rain emitter constants

`func_151CE6D0` accumulates a spawn budget and emits particles with random height and
scale. Its raw HI16/LO16 pairs in `asm/nonmatchings/game_1FBB80/func_151CE6D0.s`
(`151CE728`/`151CE72C`, `151CE730`/`151CE734`, `151CE738`/`151CE73C`,
`151CE818`/`151CE820`, `151CE830`/`151CE87C`, `151CE88C`/`151CE890`) address the six
words 0x800AAFF0..0x800AB007; no other reference function touches them. The
checksum-validated US game-data archive (ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20) holds
`45AFC000 45785000 2EDBE6FF C4A38000 43CC8000 3A83126F` there, exactly `5624.0f`,
`3973.0f`, `1.0e-10f`, `-1308.0f`, `409.0f` and `0.001f`. With `extern f32` symbols the
deferred body scored CURRENT 3460; as literals (with the packet and height locals in
the emitting block's scope) the function is `CURRENT (0)`.

The generated `game_1FBB80.o` has 0x20 bytes of `.rodata`: the six constants in ROM
order and 8 zero alignment bytes, with no data relocations. `config/game/us-rodata.ld`
maps it as an INFO section at 0x800AAFF0 with a 0x20 extent assertion and a 0x18
payload; `config/data/us.json` records the owner. The pool directly follows the
[game_1FA770](game_1fa770_float_constants.md) range ending at 0x800AAFEF. The
informational alignment bytes cover 0x800AB008..0x800AB00F (`40490FDB 38D1B717`), which
are not part of the owned payload. No reference assembly, compiler flag or verifier
change is involved.
