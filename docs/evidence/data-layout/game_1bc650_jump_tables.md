# US game_1BC650 jump tables

## Initial two-table mapping

`func_1518FDC4` owns two adjacent switch tables in the original game-data archive. Its raw assembly refers to `jtbl_800A7B7C_game` and `jtbl_800A7D64_game`. The authoritative full registered US instruction comparison reached CURRENT (0) after the approved byte-flag declaration correction.

The generated `game_1BC650.o` rodata contains 122 entries at offset 0 and 23 entries at offset 0x1E8: 145 words, or 0x244 payload bytes. A read-only audit resolved all 145 R_MIPS_32 relocations relative to the matched function and compared every resulting target with the checksum-validated US ROM game-data archive. All targets agreed. ROM SHA1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The payload starts at 0x800A7B7C and ends at 0x800A7DC0. The next raw function, `func_1519003C`, references its own table beginning at 0x800A7DC0; that table is outside this mapping's owned payload. The generated section is 0x250 bytes because it ends with 12 zero alignment bytes. The existing payload-size convention verifies 0x244 bytes against ROM and independently requires the remaining 12 bytes to be zero. The section-size assertion detects unexpected additions.

The INFO output section retains linked bytes for verification without adding them to the code-only ROM payload. No compiler flags, reference assembly, or verification rules change. This audit establishes the payload and ownership; clean linked verify-batch must still return BATCH_COMPLETE before the match is reported as batch-verified.


## Adjacent table pair recovered on 2026-09-30

`func_1519003C` now independently reaches full-span `CURRENT (0)` for its
480-byte registered range. Its raw guarded switches own exactly 122 entries
at `0x800A7DC0` and 23 entries at `0x800A7FA8`. A direct switch on the existing
byte field removes the redundant selector temporary; no parameter width,
compiler setting, assembly or verifier change was used.

The newly compiled object appends those two tables immediately after the old
145-word payload, at section offsets `0x244` and `0x42C`. The combined payload
is therefore 290 words (`0x488` bytes), covering `0x800A7B7C–0x800A8004`.
The complete `.rodata` section is `0x490` bytes, with eight trailing zero bytes.
This replaces the historical `0x250` section / `0x244` payload extent above;
the mapping base is unchanged.

Two independent read-only audits resolved all 290 `R_MIPS_32` relocations
against the original registered function addresses and compared every word
with the checksum-validated US ROM game-data archive. Both agreed. The
integrator also reran the candidate-table verifier for both the old and new
functions. The combined resolved payload SHA-256 is
`d99e759be522e44ce58971b3d035bed7570794a9f2da3d03d99847c4811137af`.
All eight object-alignment bytes were independently verified zero.

The initial full build correctly rejected the larger section with the old
extent assertion. The subsequent change updates only the two exact extent
constants to these proven values; it does not remove or relax the assertion,
change the INFO mapping base, or infer ownership from alignment. The existing
function is included in the regression batch along with the new function.
Clean-batch acceptance is recorded with the continuation checkpoint evidence.
