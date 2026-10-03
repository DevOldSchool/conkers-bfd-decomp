# Entrypoint switch table

The raw US `func_15007830` span is `0x15007830:0x15007A20` (496 bytes).
Its dispatch loads five addresses from `0x80095A30` in the game-data archive.
The recovered C emits these targets in selector order:

| Selector | Target |
| --- | --- |
| 1 | `0x1500798C` |
| 2 | `0x15007994` |
| 3 | `0x150079C0` |
| 4 | `0x150079CC` |
| 5 | `0x1500798C` |

All five relocated words were independently compared with the checksum-validated
US ROM using `rom_game_data` and `verify_bytes` from
`scripts/verify_game_rodata.py`. The candidate contains a 32-byte `.rodata`
section: 20 payload bytes with five `R_MIPS_32` relocations into this function,
followed by 12 zero alignment bytes.

The mapping in `config/game/us-rodata.ld` places the table at `0x80095A30`
as informational data with `SUBALIGN(4)`, an exact 32-byte size assertion,
and a 20-byte payload-size symbol. Linked verification compares all five
resolved addresses with the original game-data archive and separately verifies
zero alignment. The original archive continues to supply the runtime bytes.

The function's ELF symbol covers 492 bytes; its final four zero alignment bytes
complete the registered 496-byte span. The candidate table verifier accepts
this final section alignment only when it is zero-filled, reaches the next
16-byte boundary, and contains no other symbol or relocation. The independent
full-span instruction comparison still includes all 496 bytes. Source layout,
linked-ROM verification, and clean batch verification remain required gates.
