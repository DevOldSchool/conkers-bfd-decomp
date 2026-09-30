# US game_1BC650 jump tables

`func_1518FDC4` owns two adjacent switch tables in the original game-data archive. Its raw assembly refers to `jtbl_800A7B7C_game` and `jtbl_800A7D64_game`. The authoritative full registered US instruction comparison reached CURRENT (0) after the approved byte-flag declaration correction.

The generated `game_1BC650.o` rodata contains 122 entries at offset 0 and 23 entries at offset 0x1E8: 145 words, or 0x244 payload bytes. A read-only audit resolved all 145 R_MIPS_32 relocations relative to the matched function and compared every resulting target with the checksum-validated US ROM game-data archive. All targets agreed. ROM SHA1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The payload starts at 0x800A7B7C and ends at 0x800A7DC0. The next raw function, `func_1519003C`, references its own table beginning at 0x800A7DC0; that table is outside this mapping's owned payload. The generated section is 0x250 bytes because it ends with 12 zero alignment bytes. The existing payload-size convention verifies 0x244 bytes against ROM and independently requires the remaining 12 bytes to be zero. The section-size assertion detects unexpected additions.

The INFO output section retains linked bytes for verification without adding them to the code-only ROM payload. No compiler flags, reference assembly, or verification rules change. This audit establishes the payload and ownership; clean linked verify-batch must still return BATCH_COMPLETE before the match is reported as batch-verified.
