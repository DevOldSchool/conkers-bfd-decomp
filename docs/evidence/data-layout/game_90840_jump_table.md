# Pending actor action table

`func_150636F0` matches its full 716-byte US span. Raw address relocations identify the table at `0x800996D8`: 46 targets for actions 0x14–0x41. All 184 relocated bytes independently match the checksum-validated US ROM.

The compiler emits a 192-byte section with eight zero alignment bytes. The informational linker mapping consumes only `game_90840.o(.rodata)`, asserts this extent, and exposes the payload size to the existing ROM verifier. Before placement, the image grew by 192 bytes and only the table-address instructions differed. No compiler, assembly, shared types or verification rules changed.

The unit's `.rodata` is now split: `func_15064B94` appends a 0x98-byte literal pool at 0x800997E8. The table keeps object offset 0 and its runtime address; see the [literal sub-pool record](game_rodata_literal_sub_pools.md).
