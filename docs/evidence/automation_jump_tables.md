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

## September 28 manual switch recovery

`func_15141C0C` now contributes two additional tables to `game_16EE20.o`.
The integrated object contains exactly 0x290 bytes of table payload with no
trailing alignment bytes. The unchanged raw dispatches identify these mappings:

| Object offset | Size | Runtime address | HI16 / LO16 instruction sites |
| --- | --- | --- | --- |
| 0x0 | 0xB4 | 0x800A5218 | 0x2B8 / 0x2C0 |
| 0xB4 | 0x164 | 0x800A52CC | 0x2D8 / 0x2E0 |
| 0x218 | 0x40 | 0x800A5430 | 0x3B4 / 0x3BC |
| 0x258 | 0x38 | 0x800A565C | 0x29A0 / 0x29A8 |

The new tables cover selectors 0x79 through 0xA5 and 0 through 0x58.
All 164 relocated target words across all four tables were independently
compared with the checksum-validated US ROM using `rom_game_data` and
`verify_bytes` from `scripts/verify_game_rodata.py`. The existing two tables
retain their original runtime addresses; only their packed object offsets move.

The proposed split was checked against the actual integrated object: all
existing strict extent, relocation coverage, instruction addend and reference
checks pass, and `.text` remains byte-for-byte unchanged. The linker continues
to assert exact individual table sizes. No padding is added and no verifier
check is weakened. Full clean batch verification remains required after applying
the reviewed mapping.

## Additional table from func_151441A4

The restored unused parameter at index 7 is supported by caller `1513CD38`,
which writes its value at SP+0x1C and places the selector at SP+0x34.
The complete 344-byte function now passes authoritative US CURRENT (0).
Its raw unsigned bounds check admits selectors 0 through 4, and its dispatch
loads the five-entry table at `0x800A5648`.

The full-layout object now has 0x2A4 table payload bytes in a 0x2B0-byte
`.rodata` section, followed by 12 existing zero alignment bytes. The reviewed
splitter validates those bytes and preserves `.text` byte-for-byte. No padding
or relaxed checks are introduced. The updated mappings are:

| Object offset | Size | Runtime address | HI16 / LO16 instruction sites |
| --- | --- | --- | --- |
| 0x0 | 0xB4 | 0x800A5218 | 0x2B8 / 0x2C0 |
| 0xB4 | 0x164 | 0x800A52CC | 0x2D8 / 0x2E0 |
| 0x218 | 0x40 | 0x800A5430 | 0x3B4 / 0x3BC |
| 0x258 | 0x14 | 0x800A5648 | 0x284C / 0x2854 |
| 0x26C | 0x38 | 0x800A565C | 0x29A0 / 0x29A8 |

All 169 relocated target words across the five tables match the checksum-validated
US ROM. Existing runtime addresses are preserved; the final table's packed
object offset moves from 0x258 to 0x26C. The unchanged splitter checks enforce
complete relocation coverage, exact instruction addends and reviewed references.
Each linker section retains an exact size assertion. Clean batch verification
remains required after applying the mapping.
