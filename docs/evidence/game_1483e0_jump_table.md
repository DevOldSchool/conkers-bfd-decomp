# US sound-event selector table

`func_1511DD98` in `game_1483E0.c` matches its complete 468-byte raw
instruction span and preserves the reviewed source-unit layout. It chooses
sound events from an unsigned halfword selector and the actor type. The
source cases were reconstructed manually from the checksum-validated owned
ROM because the generic starter did not have the switch table.

The first C candidate scored 440. Swapping the actual sound/volume local
declaration order and assigning the final cases' sound before volume produced
the exact instruction shape. The scheduled-boolean bound required the
separate correctness fix documented in `scheduled_boolean_switch_bounds.md`.
After that fix, authoritative `finish` passed `CURRENT (0)`, layout, candidate
table contents, progress and whitespace gates. No assembly or compiler
settings changed.

The raw guard admits 54 selectors, `0x39:0x6E`, from the table at
`0x800A3218`. The integrated `game_1483E0.o` emits one `.rodata` section:
216 bytes of relocated targets followed by eight zero alignment bytes, for
an exact object extent of `0xE0`. All 54 target relocations in that full-layout
object independently agree with the original ROM table; its targets range
from `0x1511DDF0` through `0x1511DF3C`.

Before mapping, the complete integrated image was 224 bytes too long and
only the raw HI16/LO16 table-address instructions at `0x1511DDDC` and
`0x1511DDE4` differed within the code payload. The reviewed informational
section in `config/game/us-rodata.ld` places only this object's table at its
original game-data address. Exact object and payload extents remain asserted.
The existing rodata verifier compares every relocated payload word with the
owned ROM and separately requires all eight object-alignment bytes to be
zero. It does not claim ownership of the following ROM data.

The source unit remains mixed. The clean batch ended in `BATCH_COMPLETE`: the
entire 2,072,880-byte US game-code image and all mapped external rodata are
byte-identical to the owned ROM. All 1,075 tests passed (12 skipped), with
progress and whitespace gates passing.
