# US game_1F3780 trail float constants

`func_151C6A28` extends a trail segment past its second point
(`delta * 1.1f + first`) and passes two float parameters to its spawn call.
The raw code loads all three with `lui`/`lwc1` from `0x800AAC04..0x800AAC0C`,
IDO per-function literals rather than named globals.

| Address | Word | Literal | Use |
| --- | --- | --- | --- |
| `0x800AAC04` | `3F8CCCCD` | 1.1f | segment extension factor (x, y and z) |
| `0x800AAC08` | `42580001` | 54.000004f | spawn call argument |
| `0x800AAC0C` | `3C97B425` | 0.018518517f | spawn call argument |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) with
`rom_game_data` from `scripts/verify_game_rodata.py`. No other reference
function reads them. With the extern symbols `D_800AAC04`/`08`/`0C` the body
scored CURRENT 1009 (float register order); with the literals it is
`CURRENT (0)`.

The words before the pool (`0x800AABF8..0x800AAC00`) are read through extern
symbols by the still unmatched `func_151C62D0` of this unit, and the words
from `0x800AAC10` by later functions; neither range is owned by this mapping,
and the extent must grow when those functions use literals. The generated
`game_1F3780.o` has rodata `3f8ccccd 42580001 3c97b425` followed by 4 zero
alignment bytes, with no data relocations. `config/game/us-rodata.ld` maps the
object `.rodata` at `0x800AAC04` as informational data with `SUBALIGN(4)`, a
0x10-byte section-size assertion and a 12-byte payload-size symbol; the
verifier compares only the payload with the ROM.

The match also narrows the second and third parameters to `u8` (the raw
prologue reloads both with `lbu` from the argument homes); the prototype in
`game_981E0`, its only C caller, follows, and its call drops the manual
`& 0xFF`.
