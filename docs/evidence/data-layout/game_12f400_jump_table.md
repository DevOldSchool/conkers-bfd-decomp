# US switch table for game_12F400

`func_151026BC` switches on the object type byte for values `0x58` through
`0x80` through a 41-entry jump table. The raw HI16/LO16 address pair
identifies the table at `0x800A2298` in the separately loaded US game-data
archive.

The C switch reaches full registered CURRENT (0) when the default case is an
`if`/`else` on the inner byte compared with `0x3B`, which reproduces the raw
non-likely `bne` and the redundant branch after the taken arm; the earlier
fall-through form scored CURRENT (600). The generated
`build/us/src/game/game_12F400.o` has a 176-byte `.rodata` section with
forty-one `.text` word relocations, 164 payload bytes and twelve zero
alignment bytes. Relocated against the unit start `0x15102360`, the entries
take only the values `15102708` (types `0x58`, `0x5B`, `0x80`), `15102714`
(types `0x5A`, `0x5F`, `0x74`, `0x75`, `0x7A`) and `15102720` (default). These
164 bytes equal the checksum-validated US game-data archive at `0x800A2298`
(game-data base `0x80082B20`), read with `rom_game_data` from
`scripts/verify_game_rodata.py`.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A2298`
as informational data with `SUBALIGN(4)`, an exact 176-byte size assertion
and a 164-byte payload-size symbol, so the verifier compares only the
relocated payload and checks that the alignment bytes are zero. The payload
ends at `0x800A233C`; the twelve alignment bytes span the following unit
words, including `D_800A233C` (`3DA3D70A`) loaded by this function through an
extern, but are not compared against ROM. The section ends before the
`game_133190` pool at `0x800A2420`.

The unit's raw member `func_151022AC` loads literals `D_800A228C` through
`D_800A2294` directly before the table. Those words lie outside this
mapping's payload; matching that function in C with literals would place them
ahead of the table in this object's `.rodata`, trip the size assertion and
require the mapping to move. No padding is added and no verification rule is
changed.

Focused matching, source-unit integration and clean batch verification remain
separate required checks.

## func_151022AC literals (round-24)

`func_151022AC` is now matched in C with its three literals written in place:
`0x800A228C` = `46FFFE00` (32767.0f), `0x800A2290` = `3E4CCCCD` (0.2f) and
`0x800A2294` = `3ECCCCCD` (0.4f), read from the checksum-validated US ROM with
`rom_game_data`. With extern symbols the deferred body scored CURRENT 1982; as
literals it is `CURRENT (0)`. The words directly before them
(`D_800A2288` and earlier) are read by `game_12E540` and `game_12DAB0` members.

As predicted above, the literals now open the object's `.rodata` at offsets
0x0, 0x4 and 0x8, and the 41-word table follows at offset 0xC. The section is
0xB0 bytes, all payload, with no alignment tail. The mapping therefore moves
to `0x800A228C`; the size assertion stays 0xB0 and the payload-size symbol
grows from 0xA4 to 0xB0. The table still links at `0x800A2298`, and the
section now ends at `0x800A233C`, where the extern `D_800A233C` begins, so the
mapping no longer spans that word.
