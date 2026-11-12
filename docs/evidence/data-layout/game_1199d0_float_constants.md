# US game_1199D0 smoke emitter constants

`func_150EC6B0` advances an emitter counter and spawns smoke sprites with randomised speed. Its raw HI16/LO16
pairs in `asm/nonmatchings/game_1199D0/func_150EC6B0.s` address six consecutive words at
`0x800A1578..0x800A158F` (first pair at `150EC710`/`150EC714`, last at `150EC880`/`150EC884`). No other
reference function touches them. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds these big-endian words, and each round trips as the literal used in the C source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A1578` | `44D44000` | `1698.0f` |
| `0x800A157C` | `38D1B717` | `0.0001f` |
| `0x800A1580` | `3F7870B9` | `0.97047f` |
| `0x800A1584` | `3F82B114` | `1.021029f` |
| `0x800A1588` | `3DC8B43A` | `0.098000005f` |
| `0x800A158C` | `3E3020C5` | `0.172f` |

With `extern f32 D_800A1578..D_800A158C` the deferred body scored CURRENT 2136; as literals the function is
`CURRENT (0)`. The sibling `func_150AF328` in game_DC6B0 uses the same six values from its own pool at
`0x8009F7B8` ([record](game_dc6b0_float_constants.md)).

The generated `game_1199D0.o` has 0x20 bytes of `.rodata`: the six constants in load order and 8 zero alignment
bytes, with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A1578` with a
0x20 extent assertion and a 0x18 payload; `config/data/us.json` records the owner. The preceding words
`0x800A1570`/`0x800A1574` stay extern reads of this unit's `func_150EC520`, and the informational
alignment bytes `0x800A1590..0x800A1597` belong to game_11A680 externs; neither is part of the owned payload.
No reference assembly, compiler flag or verifier change is involved.
