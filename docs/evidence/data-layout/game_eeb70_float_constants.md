# US game_EEB70 motion constants

`func_150C16C0` spawns a burst of particles with random speed and motion ranges. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_EEB70/func_150C16C0.s` address five consecutive words at `0x800A01F0..0x800A0203` (the `lwc1`
halves at `150C17A8`, `150C1880`, `150C1888`, `150C18A0` and `150C18B0`). No other reference function touches them.
The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds
these big-endian words, and each round trips as the literal used in the C source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A01F0` | `418B3333` | `17.4f` |
| `0x800A01F4` | `41A1999A` | `20.2f` |
| `0x800A01F8` | `41C5999A` | `24.7f` |
| `0x800A01FC` | `3E4CCCCD` | `0.2f` |
| `0x800A0200` | `3ECCCCCD` | `0.4f` |

With `extern f32 D_800A01F0..D_800A0200` the deferred body scored CURRENT 3154; as literals (and with the last
parameter declared `u8`) the function is `CURRENT (0)`.

The generated `game_EEB70.o` has 0x20 bytes of `.rodata`: the five constants in load order and 12 zero alignment
bytes, with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A01F0` with a 0x20
extent assertion and a 0x14 payload; `config/data/us.json` records the owner. The informational alignment bytes
`0x800A0204..0x800A020F` are zero in ROM and are not referenced. No reference assembly, compiler flag or verifier
change is involved.
