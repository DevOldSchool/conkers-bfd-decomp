# US game_193130 degree-to-radian constant

`func_15165C80` swings a pair of vertex columns: it converts the current angle
from degrees to radians before the `func_150AD78C`/`func_150AD780` (sine and
cosine) calls. The raw code loads the factor with `lui`/`lwc1` from
`0x800A6C70`, an IDO per-function literal rather than a named global.

| Address | Word | Literal | Use |
| --- | --- | --- | --- |
| `0x800A6C70` | `3C8EFA35` | 0.017453292f | `current * 0.017453292f` in both calls |

The word was read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) with
`rom_game_data` from `scripts/verify_game_rodata.py`. `0x800A6C6C` and
`0x800A6C74..0x800A6C7F` are zero. No other reference function reads the word;
it was the extern `D_800A6C70` while the function was deferred (CURRENT 349).
Written as the literal in both call arguments, the product's spill slot sits
below the seven named locals and the function is `CURRENT (0)`.

The generated `game_193130.o` has rodata `3c8efa35` followed by 12 zero
alignment bytes, with no data relocations. `config/game/us-rodata.ld` maps the
object `.rodata` at `0x800A6C70` as informational data with `SUBALIGN(4)`, a
0x10-byte section-size assertion and a 4-byte payload-size symbol; the verifier
compares the payload with the ROM.

The match also narrows the last parameter to `u8` (the count is halved with a
logical shift of the masked argument home); the prototype in `game_1B0740`,
its only caller, follows, and `func_15183D28` compiles to an identical object.
