# US game_1199D0 emitter constants

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

`func_150EC520` advances a spawner accumulator by `(9.04e-08f + random * 9.87e-08f) * rate * frame time` and, while
it exceeds one, samples a point from the emitter shape with `func_151432BC` and spawns a sprite. Its raw HI16/LO16
pairs (`150EC56C`/`150EC570` and `150EC574`/`150EC578`) address `0x800A1570` and `0x800A1574`, which hold `33C221ED`
and `33D3F4E6` in the same ROM: the single-precision values of `9.04e-08f` and `9.87e-08f`. With extern symbols the
candidate scored CURRENT 262; with the literals, and the `func_151432BC` prototype corrected to its definition in
`game_16EE20.c` (`void *` shape and five pointer arguments, as `game_131F30.c` and `game_1FBB80.c` already declare
it), the function is `CURRENT (0)`. It precedes `func_150EC6B0` in the unit, so its two words come first.

The generated `game_1199D0.o` has 0x20 bytes of `.rodata`: the eight constants in load order with no alignment
bytes and no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A1570` with a 0x20
extent assertion and a 0x20 payload; `config/data/us.json` records the owner. The following words from
`0x800A1590` belong to game_11A680 externs and lie outside the mapping. No reference assembly, compiler flag or
verifier change is involved.
