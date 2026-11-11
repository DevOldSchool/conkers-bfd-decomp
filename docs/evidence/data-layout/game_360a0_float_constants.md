# US game_360A0 descriptor constants

`func_15008BF0` fills an effect descriptor from its owner's radius and angles. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_360A0/func_15008BF0.s` address six consecutive words at `0x80095B40..0x80095B57`
(first pair at `15008BF8`/`15008BFC`, last at `15008C78`/`15008C7C`). No other reference assembly function
touches them. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
`0x80082B20`) holds these big-endian words, and each round trips as the literal used in the C source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x80095B40` | `3F360B61` | `0.7111111f` (used for both angle conversions) |
| `0x80095B44` | `3E48B43A` | `0.19600001f` |
| `0x80095B48` | `3B0F67A2` | `0.0021881838f` |
| `0x80095B4C` | `41A0CCCD` | `20.1f` |
| `0x80095B50` | `3ECCCCCD` | `0.4f` |
| `0x80095B54` | `3F1B645B` | `0.60700005f` |

With `extern f32 D_80095B40..D_80095B54` the closest body scores CURRENT 516 (the extern loads are scheduled
differently); as literals the function is `CURRENT (0)`.

The generated `game_360A0.o` has 0x20 bytes of `.rodata`: the six constants in load order and 8 zero alignment
bytes, with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x80095B40` with a
0x20 extent assertion and a 0x18 payload; `config/data/us.json` records the owner. The informational alignment
bytes cover `0x80095B58..0x80095B5F`, which are zero in ROM. `game_36680.c` declares `u8` arrays at
`D_80095B48`/`D_80095B4C`/`D_80095B50` for indexed byte reads; those references resolve by address and are
unaffected by this mapping. No reference assembly, compiler flag or verifier change is involved.
