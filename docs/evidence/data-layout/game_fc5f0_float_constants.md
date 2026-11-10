# US game_FC5F0 particle spawn constants

`func_150CF140` spawns trail particles around its owner. Its raw HI16/LO16
pairs in `asm/nonmatchings/game_FC5F0/func_150CF140.s` address six words at
`0x800A0840..0x800A0857`, and no other reference function touches them. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds these big-endian words, and each one round
trips as the literal used in the C source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A0840` | `3D75C28F` | `0.06f` |
| `0x800A0844` | `3D902DE0` | `0.0704f` |
| `0x800A0848` | `BF4978D6` | `-0.78700006f` |
| `0x800A084C` | `3E926E98` | `0.286f` |
| `0x800A0850` | `401126EA` | `2.2680001f` |
| `0x800A0854` | `3FB8B43A` | `1.4430001f` |

`0x800A0858..0x800A085F` are zero, which matches IDO's 16-byte padding of the
unit's `.rodata`. `0.5f`, `1.0f`, `50.0f` and `48.0f` are `lui` immediates and
need no rodata.

The generated `game_FC5F0.o` has 0x20 bytes of `.rodata`: the six constants
in this order and 8 zero alignment bytes, with no data relocations.
`config/game/us-rodata.ld` maps it as an INFO section at `0x800A0840` with a
0x20 extent assertion and a 0x18 payload; `config/data/us.json` records the
owner. No reference assembly, compiler flag or verifier change is involved.
