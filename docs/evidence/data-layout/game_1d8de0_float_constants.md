# US game_1D8DE0 particle speed constants

`func_151AB9C8` gives each spawned particle a random speed: a random value scaled by
713.0, offset by 500.0 and scaled by 0.01. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_1D8DE0/func_151AB9C8.s` (`151ABB74`/`151ABB98` and
`151ABBB0`/`151ABBBC`) address 0x800A9018 and 0x800A901C; no other reference function
touches them. The checksum-validated US game-data archive (ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20) holds
`44324000 3C23D70A` there, exactly `713.0f` and `0.01f`. With `extern f32` symbols the
deferred body scored CURRENT 4390; as literals the function is `CURRENT (0)`.

The generated `game_1D8DE0.o` has 0x10 bytes of `.rodata`: the two constants in ROM
order and 8 zero alignment bytes, with no data relocations. `config/game/us-rodata.ld`
maps it as an INFO section at 0x800A9018 with a 0x10 extent assertion and a 0x8
payload; `config/data/us.json` records the owner. The preceding word 0x800A9014 (0.4)
stays an extern read of the matched `func_151AB930`, outside the owned payload. The informational
alignment bytes cover 0x800A9020..0x800A9027 and are not part of the owned payload. No
reference assembly, compiler flag or verifier change is involved.
