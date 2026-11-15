# US game_623D0 surface float constants

The unit's rodata is a two-word literal pool at 0x80097D70..0x80097D77. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `469C4000 C61C4000` there, the
single-precision values of `20000.0f` and `-10000.0f`.

- `func_15035714` passes `20000.0f` as the last argument of `func_150A6360`. It matched with the extern
  `D_80097D70`; as a literal it keeps `CURRENT (0)` and supplies the first pool word.
- `func_15036148` scans the 25 actor slots and, for an actor of kind 0 or 1 whose `surface` height is set (not the
  `-10000.0f` sentinel), above its floor and below its position while it moves faster than `5.0f`, calls
  `func_15035808`. It loads the sentinel from 0x80097D74 once, before the loop. With the literal the function
  is `CURRENT (0)` (the extern candidate scored CURRENT 328). `5.0f`, `100.0f`, `150.0f` and `127.0f` are built with
  `lui`.

The generated `game_623D0.o` has 0x10 bytes of `.rodata`: the 0x8-byte payload in source order followed by 8 zero
alignment bytes, with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x80097D70`
with a 0x10 extent assertion and a 0x8 payload; `config/data/us.json` records the owner. The alignment bytes fall at
0x80097D78..0x80097D7F, which are zero in ROM and referenced by no function; only the payload is compared. The
preceding word `D_80097D60` belongs to `game_61D10` and the following word `D_80097D80` to `game_63A20`; both stay
extern reads. No reference assembly, compiler flag or verifier change is involved.
