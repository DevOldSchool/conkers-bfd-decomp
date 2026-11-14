# US game_135780 timer constants

`func_15108658` updates an effect's timer state. The raw function loads two
per-function rodata literals through HI16/LO16 pairs:

| Address | Word | Literal | Use |
| --- | --- | --- | --- |
| `0x800A2460` | `3FC95811` | 1.5730001f | fade margin at both ends of the 11-unit countdown (loaded once, compared twice) |
| `0x800A2464` | `3D50E561` | 0.051000003f | chance of starting the countdown |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`); the HI16/LO16
pairs are at raw `0x151086F8`/`0x151086FC` and `0x151087BC`/`0x151087C0`.
The function's other constants (11 and 0) are built with `lui` or `mtc1` and
add no rodata. The generated `game_135780.o` has rodata
`3fc958113d50e5610000000000000000`: eight payload bytes followed by eight zero
alignment bytes, with no data relocations. The ROM words at `0x800A2468` and
`0x800A246C` are also zero. With extern symbols the deferred body scored
CURRENT 1491; as literals the function is `CURRENT (0)`.

The words `0x800A2450..0x800A245F` are read by the raw `func_151082D0` of this
unit through externs (`D_800A2450`, `D_800A2454`, `D_800A2458`, `D_800A245C`)
and are not owned by this mapping. When that function is matched with
literals, its words precede this pool in the object, so this mapping must move
to `0x800A2450` and its extent assertion must grow.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A2460`
as informational data with `SUBALIGN(4)`, an exact 16-byte size assertion and
an 8-byte payload-size symbol. The existing verifier compares every payload
byte with the ROM and checks that the alignment bytes are zero. Focused
matching, source-unit integration and clean batch verification remain separate
required checks.
