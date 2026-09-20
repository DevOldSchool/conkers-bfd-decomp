# External jump table for func_1503453C (US)

The raw US dispatch at `0x150345AC` bounds its selector to five unsigned
entries. Instructions at `0x150345B8` and `0x150345C0` address
`jtbl_80097D20_game` at `0x80097D20`. The table is in the separately loaded
game-data archive, not the executable game-code payload.

The checksum-validated US ROM's decompressed game data starts at
`0x80082B20` (`config/rzip_layouts.json`). At data offset `0x15200`, the five
table words all target `0x150345CC`, followed by twelve zero alignment bytes.
The next data begins at `0x80097D40`. The compiled `game_61950.c` object emits
the same 32-byte `.rodata` section when linked at the original runtime address.

`config/game/us-rodata.ld` consumes that object's `.rodata` before the
generated code linker script. Its informational ELF section binds the table
to `0x80097D20` and retains the linked bytes for verification, without placing
them in the code-only binary. A size assertion rejects changes to the reviewed
section extent. No instructions, relocations, or table entries are patched.

Every integrated game verification compares that complete linked section,
including relocated destinations and padding, against data decompressed from
the checksum-validated owned ROM. The original data archive remains its runtime
supplier. The code payload must independently remain byte-identical. This is
verified reuse of an existing data range, not a claim that the game-data archive
has been rebuilt from C or that the whole source unit is complete.

## Recovered preceding floating constant

The completed source also emits the floating constant loaded by
`func_150344A0` from `0x80097D1C`: bits `0x40690453` (`3.640889f`).
The combined object section is 32 bytes starting at `0x80097D1C`: that float,
the five relocated words targeting `0x150345CC`, and eight zero padding bytes.
All 32 bytes were compared with checksum-validated US ROM game data after
resolving the object's five `R_MIPS_32` text relocations. The remaining four
zero bytes before `0x80097D40` remain supplied by the original data archive.

The linker entry now starts at `0x80097D1C` with `SUBALIGN(4)` to preserve
this original address despite the object's stronger default section alignment.
The wildcard object path supports finalization into `src/game/done/`; the
32-byte size assertion and integrated ROM comparison remain in effect.
