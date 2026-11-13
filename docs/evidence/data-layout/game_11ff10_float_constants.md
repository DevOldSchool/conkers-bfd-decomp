# US game_11FF10 emitter constants

`func_150F2D14` scales an emitter with `0.148f` and `58.14f`. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_11FF10/func_150F2D14.s` address the words `0x800A1968` and `0x800A196C`;
no other reference function touches them. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3E178D50 42688F5C`
there, exactly those two literals, which reach `CURRENT (0)` in the C source.

The generated `game_11FF10.o` has 0x10 bytes of `.rodata`: the two constants and 8 zero alignment
bytes, with no data relocations. The words `0x800A1950..0x800A1967` stay extern reads (`D_800A1950`,
`D_800A195C`) and are not part of this mapping. `config/game/us-rodata.ld` maps the object as an INFO
section at `0x800A1968` with a 0x10 extent assertion and a 0x8 payload; `config/data/us.json` records
the owner. The informational alignment words `0x800A1970..0x800A1977` (`C5034000 00000000`) are not
owned. No reference assembly, compiler flag or verifier change is involved.
