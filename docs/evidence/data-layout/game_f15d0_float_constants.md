# US game_F15D0 burst float constants

`func_150C44A4` emits sparks and a burst effect for active actors. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_F15D0/func_150C44A4.s` address the eleven words `0x800A03B8..0x800A03E3` in first-use order;
no other reference function touches them. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3EAAAAAB 3E041894 3DEF9DB3 3E051EB9
3E4CCCCD 3F19999A 40263540 409BD70B 3E841894 BF1BA5E4 3F333334` there, the single-precision values of
`0.33333334f`, `0.12900001f`, `0.117000006f`, `0.13000001f`, `0.2f`, `0.6f`, `2.5970001f`, `4.8700004f`,
`0.25800002f`, `-0.60800004f` and `0.70000005f`. The raw function had no C candidate; with these literals it is
`CURRENT (0)`. Its local `func_151D9014` prototype uses the byte and halfword parameters proven by the callee's raw
assembly (as in `game_17CAF0.c`); the probe scores 0 with it and with an all-`s32` form alike.

The generated `game_F15D0.o` has 0x30 bytes of `.rodata`: the 0x2C-byte payload and 4 zero alignment bytes, with no
data relocations; no other member of the unit emits rodata. `config/game/us-rodata.ld` maps it as an INFO section
at `0x800A03B8` with a 0x30 extent assertion and a 0x2C payload; `config/data/us.json` records the owner. The
preceding words through `0x800A03B7` stay extern reads of another member, and the alignment word `0x800A03E4` is not
part of the owned payload; the `game_F21D0` pool starts at `0x800A03F0`. No reference assembly, compiler flag or
verifier change is involved.
