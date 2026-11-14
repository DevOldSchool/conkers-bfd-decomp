# US game_1368C0 emitter constants

`func_1510A40C` scales two spawn speeds by `0.910801f` and `1.043206f` and guards a length with
`0.001f`. Its raw HI16/LO16 pairs in `asm/nonmatchings/game_1368C0/func_1510A40C.s` address the words
`0x800A268C`, `0x800A2690` and `0x800A2694`; no other reference function touches them. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
`0x80082B20`) holds `3F692A41 3F8587C6 3A83126F` there, exactly those three literals, which reach
`CURRENT (0)` in the C source.

The generated `game_1368C0.o` has 0x10 bytes of `.rodata`: the three constants and 4 zero alignment
bytes, with no data relocations; the other members of the unit read their constants
(`D_800A2668..D_800A2688`) through extern symbols. `config/game/us-rodata.ld` maps the object as an
INFO section at `0x800A268C` with a 0x10 extent assertion and a 0xC payload; `config/data/us.json`
records the owner. The informational alignment word `0x800A2698` is zero in ROM and not owned. No
reference assembly, compiler flag or verifier change is involved.
