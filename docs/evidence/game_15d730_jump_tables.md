# US switch tables for game_15D730

The raw dispatches in `func_1513137C` and `func_15131514` identify adjacent
tables at `0x800A3800` and `0x800A3820`. They cover selectors 1 through 8
and 0 through 8 respectively. All 17 relocated target words were independently
compared against the checksum-validated US ROM. The candidate table gate also
verified both complete raw instruction spans and their dispatch bounds.

The compiler emits 0x44 payload bytes and 12 existing zero alignment bytes in
an 0x50-byte `.rodata` section. The linker maps that existing section at
`0x800A3800` with `INFO`, `SUBALIGN(4)`, an exact 0x50 size assertion and a
0x44 payload-size symbol. The existing verifier compares every payload byte
with the ROM and separately verifies all alignment bytes are zero. No padding
is added and no verifier, compiler option or instruction is changed.

Without this mapping the integrated binary differs only at the four table
address instruction words and grows by the object's 80 rodata bytes. The
unchanged game-data archive supplies the tables at runtime. Existing reviewed
mappings, including game_11F780 and game_16EE20, are unaffected.

Clean batch verification remains required after applying this mapping.
