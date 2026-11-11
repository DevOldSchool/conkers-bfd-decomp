# US game_F21D0 wave constants

`func_150C4D20` advances a wave timer and scales the result. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_F21D0/func_150C4D20.s` address three consecutive words at
`0x800A03F0..0x800A03FB` (first pair at `150C4D80`/`150C4D84`). No other reference function touches them.
The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds these big-endian words, and each round trips as the literal used in the C source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A03F0` | `3C1374BC` | `0.009f` |
| `0x800A03F4` | `3DCCCCCD` | `0.1f` |
| `0x800A03F8` | `3F4CCCCD` | `0.8f` |

With `extern f32 D_800A03F0/F4/F8` the same body scores CURRENT 325 (the inline `360.0f` constant is scheduled
differently); as literals the function is `CURRENT (0)`.

The generated `game_F21D0.o` has 0x10 bytes of `.rodata`: the three constants in load order and 4 zero alignment
bytes, with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A03F0` with a 0x10
extent assertion and a 0xC payload; `config/data/us.json` records the owner. The informational alignment word covers
`0x800A03FC`, which is zero in ROM and is not referenced by any function. No reference assembly, compiler flag or
verifier change is involved.
