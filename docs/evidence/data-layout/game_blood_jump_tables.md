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
