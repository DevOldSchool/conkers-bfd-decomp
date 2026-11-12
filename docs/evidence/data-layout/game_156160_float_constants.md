# US game_156160 camera follow constants

`func_15129934` moves a follow camera toward its target, eases each axis and probes the floor below it. Its raw
HI16/LO16 pairs in `asm/nonmatchings/game_156160/func_15129934.s` address three consecutive words at
`0x800A3614..0x800A361F` (`15129A1C`/`15129A20`, `15129B7C`/`15129B80`, `15129BC0`/`15129BC4`). No other
reference function touches them. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds these big-endian words, and each round trips as the literal used in the C source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A3614` | `3F99999A` | `1.2f` (vertical follow scale) |
| `0x800A3618` | `C61C4000` | `-10000.0f` (floor probe depth argument) |
| `0x800A361C` | `C61C4000` | `-10000.0f` (no-floor sentinel compare; IDO emits a separate word per use) |

With `extern f32 D_800A3614/18/1C` the deferred body scored CURRENT 2152; as literals the function is
`CURRENT (0)`.

The generated `game_156160.o` has 0x10 bytes of `.rodata`: the three constants in load order and 4 zero alignment
bytes, with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A3614` with a 0x10
extent assertion and a 0xC payload; `config/data/us.json` records the owner. The preceding word `0x800A3610`
(`0.011111111`) stays an extern read of this unit's `func_151298C0`, and the informational alignment
word `0x800A3620` is an extern of game_1570E0; neither is part of the owned payload. No reference assembly,
compiler flag or verifier change is involved.
