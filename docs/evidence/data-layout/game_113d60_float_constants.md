# US game_113D60 emitter constants

`func_150E6B84` emits a burst of particles along two sine paths and wraps their phases. Its raw HI16/LO16
pairs in `asm/nonmatchings/game_113D60/func_150E6B84.s` address two consecutive words at
`0x800A1304..0x800A130B` (`150E6C10`/`150E6C14` and `150E6DC0`/`150E6DC4`). No other reference function
touches them. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
`0x80082B20`) holds these big-endian words, and each round trips as the literal used in the C source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A1304` | `3DCCCCCD` | `0.1f` (speed factor) |
| `0x800A1308` | `40C90FDB` | `6.2831855f` (phase period, 2 pi) |

With `extern f32 D_800A1304/D_800A1308` the deferred body scored CURRENT 1907; as literals the function is
`CURRENT (0)`.

The generated `game_113D60.o` has 0x10 bytes of `.rodata`: the two constants in load order and 8 zero
alignment bytes, with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at
`0x800A1304` with a 0x10 extent assertion and a 0x8 payload; `config/data/us.json` records the owner. This
pool sits inside a run of the unit's ROM constants: `0x800A12F8..0x800A1300` below and `0x800A130C` onward
(`3F102F57 3DB851EC ...`) are still read through externs by other members of this unit. The informational
alignment bytes `0x800A130C..0x800A1313` overlap two of those words; only the 0x8 payload is owned and
compared, and the extern references resolve by address. Converting those members' constants to literals
would need this pool to move or split. No reference assembly, compiler flag or verifier change is involved.
