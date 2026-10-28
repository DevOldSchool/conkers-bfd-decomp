# US switch table for game_E4070

`func_150B6BC0` dispatches the byte state `D_800D9890` values 1 through 10
through ten word-sized jump targets. The raw HI16/LO16 address pair
identifies the table at `0x8009FD00` in the separately loaded US game-data
archive.

The preserved C switch reaches full registered CURRENT (0). It was
previously deferred only because the table had no placement and full
integration exposed the unresolved private `.rodata` relocation. The
generated `build/us/src/game/game_E4070.o` has a 48-byte `.rodata` section
with ten `.text` word relocations, 40 payload bytes and eight zero alignment
bytes. Relocated against `func_150B6BC0` at `0x150B6BC0`, the payload is
`150B6BF8 150B6C08 150B6C80 150B6C18 150B6C28 150B6C38 150B6C48 150B6C58
150B6C68 150B6C78`; selector 3 shares the default return at `0x150B6C80`.
These 40 bytes equal the checksum-validated US game-data archive at
`0x8009FD00` (game-data base `0x80082B20`), read with `rom_game_data` from
`scripts/verify_game_rodata.py`.

The mapping in `config/game/us-rodata.ld` places this section at `0x8009FD00`
as informational data with `SUBALIGN(4)`, an exact 48-byte size assertion
and a 40-byte payload-size symbol, so the verifier compares only the
relocated payload and checks that the alignment bytes are zero. It ends at
`0x8009FD30`, after the `game_DE5A0` pool ending at `0x8009F8C0` and before
the `game_E8C10` pool at `0x8009FEE4`. The unit's remaining raw members do
not load rodata in this range. No padding is added and no verification rule
is changed.

Focused matching, source-unit integration and clean batch verification remain
separate required checks.
