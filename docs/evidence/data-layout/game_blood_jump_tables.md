# US switch tables for effects/blood

The raw dispatch in `func_15134070` uses two adjacent tables. Selectors
0x34 through 0xB4 index `jtbl_800A4350_game` (0x81 words), and selectors 0
through 0x16 index `jtbl_800A4554_game` (0x17 words). Values outside both
ranges take the shared default return of 0x63.

The compiler emits exactly 0x260 payload bytes for the two tables in
`blood.o`'s `.rodata`, with no alignment padding. The linker maps that section
at `0x800A4350` with `INFO`, `SUBALIGN(4)`, an exact 0x260 size assertion and a
0x260 payload-size symbol. The existing verifier compares every relocated
target word with the checksum-validated US ROM. No padding is added and no
verifier, compiler option or instruction is changed.

Without this mapping the integrated binary differs at the table address
instruction words in `func_15134070` and grows by the object's 0x260 rodata
bytes. The unchanged game-data archive supplies the tables at runtime.

Clean batch verification remains required after applying this mapping.

Update: the spray literal pool of `func_1513A48C` and `func_1513A5E0` follows
these tables in `blood.o`. The unit is now split into exact 0x204 and 0x5C table
sections at their unchanged addresses, plus a 0x20 pool at 0x800A4950. See
[literal sub-pools](game_rodata_literal_sub_pools.md).

Update (nov13): `func_15138C80` dispatches a hit kind 0 through 0x13 (`sltiu 0x14`) through `jtbl_800A4874_game`.
Its raw HI16/LO16 pair is `0x15138D20`/`0x15138D28` (object `.text` offsets 0x4CB0/0x4CB8). The 20 ROM words at
`0x800A4874..0x800A48C3` are `15138D6C 15138E68 15138DF8 15138D8C 15138E18 15138DAC 15138DAC 15138D6C 15138E38
15138E38 15138E80 15138E80 15138E68 15138E68 15138E80 15138DD0 15138D34 15138D54 15138E80 15138E80`. With the C
switch (cases 10, 11, 14, 18, 19 return; 1, 12, 13 share the default) the function is `CURRENT (0)`, and its 20
`R_MIPS_32` table entries in `blood.o` resolve to exactly those targets. The callee prototypes for
`func_15139D74`, `func_1513A6E0`, `func_1513ABB8`, `func_1513B0F8` and `func_1513A594` take the selector byte as
`u8`, and the definition's second parameter is `u8`; the `game_200930` caller prototype is
`(void *, u8, s32)`. The matched caller `func_151D4DAC` keeps identical instruction words and relocations.

`blood.o` now has 0x2D0 bytes of `.rodata`: the two `func_15134070` tables (0x204, 0x5C), this table (0x50) and
the spray pool (0x20). The splitter maps them as `.rodata.blood_0` (0x800A4350), `.rodata.blood_204` (0x800A4554),
`.rodata.blood_260` (0x800A4874, table, sites 0x4CB0/0x4CB8) and `.rodata.blood_2b0` (0x800A4950, pool), each with
an exact size assertion.
