# US game_135D00 billboard constants

`func_15109120` builds a camera-facing billboard matrix and its vertices. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_135D00/func_15109120.s` address four consecutive words at `0x800A2498..0x800A24A7`
(the `lwc1` halves at `151091A4`, `15109248`, `151092D0` and `151092E0`). No other reference function touches them.
The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds
these big-endian words, and each round trips as the literal used in the C source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A2498` | `3E20C49C` | `0.157f` |
| `0x800A249C` | `38D1B717` | `0.0001f` |
| `0x800A24A0` | `3E5A1CAD` | `0.21300001f` |
| `0x800A24A4` | `3EB74BC7` | `0.358f` |

With `extern f32 D_800A2498..D_800A24A4` the deferred body scored CURRENT 2838; as literals the function is
`CURRENT (0)`.

The generated `game_135D00.o` has exactly 0x10 bytes of `.rodata`, the four constants in load order with no
alignment bytes and no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A2498` with
a 0x10 extent assertion and a 0x10 payload; `config/data/us.json` records the owner. The preceding words
`0x800A2470..0x800A2494` (including the same `0.157f` value at `0x800A2490` and `0x800A2494`) stay extern reads of
other members of this unit and are not part of this mapping. No reference assembly, compiler flag or verifier change
is involved.
