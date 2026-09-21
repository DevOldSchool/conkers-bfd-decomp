# US jump tables for the manual matching batch

The clean US integrated build after the manual batch kept every function at its
registered address, but three matched C switches referenced compiler-emitted
tables appended to the code payload. Their independent raw assembly references
identify the original game-data addresses below. Each corresponding source
object emits one `.rodata` section of the listed extent.

| Source object | Function | Raw table address | Object extent |
| --- | --- | --- | --- |
| `game_49BE0.o` | `func_1501C730` | `0x800969A0` | `0x20` |
| `game_CD860.o` | `func_150A03B0` | `0x8009F550` | `0x20` |
| `game_179F30.o` | `func_1514EA1C` | `0x800A5E20` | `0x30` |

`config/game/us-rodata.ld` links only those reviewed sections as external
informational data, with exact-extent assertions. The existing
`verify_game_rodata.py` gate compares their relocated table contents against
the checksum-validated US ROM's game-data region. The original data archive
provides the tables at runtime; this mapping does not change the matched C
instructions, raw assembly, or source-unit boundaries.

The three table payloads are respectively `0x1C`, `0x18`, and `0x28` bytes;
the remaining bytes in each object section are zero alignment padding. The
ROM verification checks only those payloads. The `game_CD860` address is
`0x8009F550`: its raw `lui`/`lw` pair uses the carried high half `0x800A`
for the negative low half `0xF550`.
