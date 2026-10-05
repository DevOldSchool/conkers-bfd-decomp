# US callback switch table

func_1509C7C8 matches all308 registered instruction bytes and mixed-unit layout.
Before mapping, GAME differed in two table-address instructions and appended32 bytes.

The full game_C98F0.o has six R_MIPS_32 targets at rodata offset0:24 payload bytes,
then8 zero alignment bytes. Resolving them at source text base0x1509C440 reproduces
all six checksum-validated ROM words at0x8009E458. Following ROM bytes are nonzero.

Approved INFO placement consumes only this object's rodata, asserts extent0x20,
and verifies payload0x18 separately from alignment. Clean full linking reproduces
the complete2,072,880-byte GAME image and every external rodata payload.
Clean verify-batch: BATCH_COMPLETE; layout, progress, whitespace and tests passed.
