# US game_DBA60 spark burst float constants

`func_150AE790` spawns a randomized burst of particles from an attachment point
on its owner, then one final 0x38-byte descriptor through `func_15167D84`. Its
raw HI16/LO16 pairs in `asm/nonmatchings/game_DBA60/func_150AE790.s` address
five consecutive words at 0x8009F774..0x8009F787; no other reference function
touches them. The checksum-validated US game-data archive (ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20) holds
`41966666 40133333 4039999A 3DCCCCCD 3F333333` there, exactly `18.8f`, `2.3f`,
`2.9f`, `0.1f` and `0.7f` in load order. The other float operands (`0.5f`,
`2.5f`, `200.0f`, `600.0f`) are built with `lui`/`mtc1` and need no rodata.

With `extern f32` symbols IDO hoists the five addresses into saved registers
across the spawn loop (`$s5`-`$s8`, CURRENT 8670); with the literals each load
is a `lui $at`/`lwc1` pair inside the loop, as in the raw function, and the
function is CURRENT (0).

The generated `game_DBA60.o` has 0x20 bytes of `.rodata`: the five constants
and 12 zero alignment bytes, with no data relocations. `config/game/us-rodata.ld`
maps it as an INFO section at 0x8009F774 with a 0x20 extent assertion and a
0x14 payload; `config/data/us.json` records the owner. The informational
alignment bytes cover 0x8009F788..0x8009F793: 0x8009F788 and 0x8009F78C are
zero in the ROM, and 0x8009F790 (`00000006`) begins `D_8009F790[5]`, read by
game_DC6B0 through an extern; the game-data archive still supplies those words.
The preceding words 0x8009F764..0x8009F773 are not referenced by this unit.
The other raw member, `func_150AEB9C`, reads no rodata. No reference assembly,
compiler flag or verifier change is involved.
