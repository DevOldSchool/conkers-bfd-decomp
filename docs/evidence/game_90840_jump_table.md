# Pending actor action table

`func_150636F0` matches its full 716-byte US span. Raw address relocations identify the table at `0x800996D8`: 46 targets for actions 0x14–0x41. All 184 relocated bytes independently match the checksum-validated US ROM.

The compiler emits a 192-byte section with eight zero alignment bytes. The informational linker mapping consumes only `game_90840.o(.rodata)`, asserts this extent, and exposes the payload size to the existing ROM verifier. Before placement, the image grew by 192 bytes and only the table-address instructions differed. No compiler, assembly, shared types or verification rules changed.
