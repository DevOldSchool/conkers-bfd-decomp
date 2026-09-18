# US jump tables exposed by the September 18 automation batch

The failed integrated image was 1,376 bytes longer than the checksum-validated
2,072,880-byte game-code payload. Twenty instruction words (ten HI/LO address
pairs) referenced the appended compiler `.rodata`. The dispatches in the raw
US code identify these original game-data addresses:

| Object | Function(s) | ROM data address | Payload / object bytes |
| --- | --- | --- | --- |
| game_433F0 | func_15015F40 | 0x800966C0 | 160 / 160 |
| game_58F80 | func_1502DB20 | 0x80096DF8 | 256 / 256 |
| game_AEB40 | func_150829D8 | 0x8009CC40 | 276 / 288 |
| game_B4080 | func_1508E6D0, func_1508E780 | 0x8009DA94, 0x8009DB90 | 480 / 480 combined |
| game_16EE20 | func_15141CC0 | 0x800A5430 | 64 |
| game_16EE20 | func_151442FC | 0x800A565C | 56; 8 trailing object-alignment bytes |
| game_1C1150 | func_15194320 | 0x800A8258 | 20 |
| game_1C1150 | func_15194394 | 0x800A826C | 20 |
| game_1C1150 | func_15194794 | 0x800A82BC | 20; 4 trailing object-alignment bytes |

The first four objects use ordinary external informational ELF sections in
`config/game/us-rodata.ld`. The twelve trailing bytes of `game_AEB40` are zero
object alignment, not the following ROM table: the existing explicit payload
size verifier checks the 276 payload bytes and requires zero alignment bytes.

The last two objects contain noncontiguous original tables. Their compiled
`.rodata` packs the currently recovered tables together. The integrated build
runs `scripts/split_game_rodata.py` on these two objects only, producing one
input section per table. This does not alter `.text`, jump-table words, or
relocation addends. It partitions the table's existing R_MIPS_32 relocations
and binds each reviewed HI16/LO16 pair to a linker-defined base equal to the
original runtime address minus the unchanged instruction addend. Unmodified
sections retain their file offsets, including MIPS ECOFF debug information.

The splitter checks exact extents, all table-pointer relocations, the reviewed
instruction-reference sites/addends, and zero trailing alignment. Unreviewed
references or changed extents stop the build. The linker asserts each output
extent; `verify_game_rodata.py` compares every linked table payload, including
relocated destinations, with the checksum-validated US ROM's decompressed game
data. Tables remain supplied at runtime by that original game-data archive.

ROM comparison also exposed wrong switch cases in `func_15194320` and
`func_15194394`: all five entries (selectors 0 through 4) target their spawn
blocks, at 0x15194358 and 0x151943CC respectively. The C previously sent cases
1 and 3 to the return block. Correcting those cases changes the generated table
entries while retaining matching dispatch instructions. Focused instruction
scores alone did not cover this data defect; linked ROM-data verification does.

Validation on 2026-09-18: both corrected switches passed `finish` with
`CURRENT (0)` and preserved source-unit layout. The clean `verify-batch` for
all 91 pending functions ended in `BATCH_COMPLETE`: the integrated code payload
matched exactly, all external table payloads matched US ROM data, 975 tests
completed successfully (six skipped), and metadata, progress, and whitespace
checks passed. Existing compiler warnings were not part of this repair.
