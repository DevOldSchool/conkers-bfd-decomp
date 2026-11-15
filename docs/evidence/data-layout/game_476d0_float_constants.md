# US game_476D0 view angle constants

`func_1501B0A0` converts two view scales to half-angles in radians and two
arctangent results back to full angles in degrees. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_476D0/func_1501B0A0.s` address three words at
`0x800968F4..0x800968FF` (`1501B0A4`/`1501B0A8`, `1501B18C`/`1501B190` and
`1501B1D8`/`1501B1DC`; unit text offsets 0xE84/0xE88, 0xF6C/0xF70 and
0xFB8/0xFBC). No other reference function touches them; `func_1501B22C` owns
the two words after them (below). The checksum-validated
US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
`0x80082B20`) holds these big-endian words, and each round trips as the literal
used in the C source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800968F4` | `3C0EFA35` | `0.008726646f` (pi / 360) |
| `0x800968F8` | `42E52EE0` | `114.59155f` (360 / pi) |
| `0x800968FC` | `42E52EE0` | `114.59155f` |
| `0x80096900` | `3C8EFA35` | `0.017453292f` (pi / 180) |
| `0x80096904` | `3C8EFA35` | `0.017453292f` |

`func_1501B0A0` uses each of its literals twice. The compiled object holds
`0.008726646f` once (both uses share the one load at 0xE84/0xE88) and
`114.59155f` twice (one load per use, with calls in between), which is the ROM
layout. With `extern f32 D_800968F4/F8/FC` the same body scores CURRENT 275:
the first load is scheduled after the prologue stores instead of directly after
`addiu sp`. As literals the function is `CURRENT (0)`.

`func_1501B22C` builds two view rotation rows from half the view angles. Its
raw HI16/LO16 pairs in `asm/nonmatchings/game_476D0/func_1501B22C.s` address
`0x80096900` and `0x80096904`, the two words directly after the three above;
no other reference function touches them. The source converts each half-angle
with `0.017453292f` once per `cos`/`sin` call (four uses); the compiler shares
the product within each pair, so the object holds the literal twice, one per
axis, in ROM order. With `extern f32 D_80096900/D_80096904` the body does not
match; as literals the function is `CURRENT (0)`.

The generated `game_476D0.o` has 0x20 bytes of `.rodata`: the five constants
in this order and 12 zero alignment bytes, with no data relocations.
`config/game/us-rodata.ld` maps it as an INFO section at `0x800968F4` with a
0x20 extent assertion and a 0x14 payload; `config/data/us.json` records the
owner. Only the 0x14 payload bytes are claimed. The informational alignment
extent runs on to `0x80096913`: the ROM words at `0x80096908..0x8009690F` are
zero, and `0x80096910` holds `3DCCCCCD` (`0.1f`), which belongs to the next
unit (`func_1501B320` in `game_487D0` loads it with the HI16/LO16 pair at
`1501B374`/`1501B378`); the game-data archive still supplies that word. The words below
the mapping (`0x800968E0..0x800968F3`) are read by other members through
externs and are not part of it. No reference assembly, compiler flag or verifier
change is involved.
