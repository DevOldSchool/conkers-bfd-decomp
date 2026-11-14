# US game_14EE80 camera bounds constants

`func_151219D0` frames the camera around every active actor. It seeds the
running X and Z minima with `D_800A3420` and the maxima with `D_800A3424`,
per-function rodata literals reached through HI16/LO16 pairs.

| Address | Word | Value |
| --- | --- | --- |
| `0x800A3420` | `461C4000` | 10000.0f |
| `0x800A3424` | `C61C4000` | -10000.0f |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`). Writing the
seeds as literals reproduces the raw function (CURRENT 0). The other constants
in the function (0.5, 150, 300, 100 and 2) are built with `lui` and add no
rodata, so the generated `game_14EE80.o` has rodata
`461c4000c61c40000000000000000000`: eight payload bytes followed by eight zero
alignment bytes, with no data relocations. The ROM words at `0x800A3428` and
`0x800A342C` are also zero.

The preceding pool (`0x800A3400` to `0x800A341F`) belongs to `game_14D110`
(`func_15120158`). `D_800A3430` (`3C8EFA35`), read by the matched
`func_15121C00` in this source file, stays an external reference and is not
owned by this mapping; the zero words between the two show it starts a
separate 16-byte-aligned section rather than continuing this object's pool.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A3420`
as informational data with `SUBALIGN(4)`, an exact 16-byte size assertion and
an 8-byte payload-size symbol. The existing verifier compares every payload
byte with the ROM and checks that the alignment bytes are zero. Focused
matching, source-unit integration and clean batch verification remain separate
required checks.
