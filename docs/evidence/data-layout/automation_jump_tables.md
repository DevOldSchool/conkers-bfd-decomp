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

## October 18 game_B4080 switch recovery

Activating `func_15089BC0` adds its eight-entry table before the two existing
`game_B4080` tables. The compiler packs all three into 0x200 bytes, but the
original first table ends at 0x8009DA44 and the next begins at 0x8009DA94.
Mapping the entire object at the old base would misplace every table.

The raw US dispatch subtracts 0xB7, checks the unsigned index against eight,
and loads `jtbl_8009DA24_game` at instruction addresses 0x15089BF8/0x15089C00.
The existing dispatches still load 0x8009DA94 at 0x1508E6E0/0x1508E6E8 and
0x8009DB90 at 0x1508E7A4/0x1508E7AC. These instructions are in the independently
extracted `reference/game/us/asm/86BD0.s`; the source unit begins at 0x15086BD0.

| Function | Object offset | Size | Runtime address | HI16 / LO16 object sites |
| --- | --- | --- | --- | --- |
| func_15089BC0 | 0x0 | 0x20 | 0x8009DA24 | 0x3028 / 0x3030 |
| func_1508E6D0 | 0x20 | 0xFC | 0x8009DA94 | 0x7B10 / 0x7B18 |
| func_1508E780 | 0x11C | 0xE4 | 0x8009DB90 | 0x7BD4 / 0x7BDC |

All 128 relocated target words were independently compared with the
checksum-validated US ROM using `rom_game_data` and `verify_bytes`. The first
table's targets for selectors 0xB7 through 0xBE are 0x15089C3C, 0x15089C18,
0x15089C0C, 0x15089C30, 0x15089C24, 0x15089C60, 0x15089C48 and 0x15089C54.
The missing case 0xBC correctly targets the default at 0x15089C60.

The three ROM payload SHA-256 hashes, in table order, are:

- `67901f9240420a2be5c486ce971ec6393f6cef83a794230f8b03501e6b8a07c8`
- `8d0056b89fa9c0d24d92f1a64381b3e186a77e04dac5fe0df745bd77560f6c5b`
- `09c699ce2d0a77a73b03de5be682f08e74b3e28d5454ec6168adce3c426daade`

The existing strict splitter now handles this object. It partitions the
original table relocations and rebinds the six reviewed instruction references;
`.text`, table words and instruction addends remain unchanged. Each section
has an exact linker extent assertion, and linked ROM verification covers all
512 bytes without a padding exemption. The original game-data archive remains
the runtime backing. No source or assembly changes are needed for this repair.

`config/data/us.json` records the source owner for each address/input-section
pair, replacing the former single `.rodata` owner. The checked data audit and
external-placement ownership tests enforce consistency with these mappings.

PR 147 review re-verification on 2026-10-18 used tested commit
`6d048a787aaf3e4c4b83376747b634deee51a1db`. This revision includes current main
`619190f8cb044d5ef7b1440c2f24c0e4b7c6efcc`, including PR 146's compiler/profile/CI
changes and PR 145's shared RNG declarations, plus the review fixes. The
split-object names now have one Makefile definition used by both the recipe
filter and dependency rule. The earlier pre-merge validation is superseded by
this run.

After the source edits, fresh `finish` checks for all ten functions reported
US `CURRENT (0)` over the full registered spans and passed source-unit layout,
progress and whitespace gates. The same ten-ID clean `verify-batch` ran on the
committed revision above with a clean tracked working tree:

```sh
./conker verify-batch func_151CD3CC func_150E1060 func_15089BC0 func_151C5588 func_150DB518 func_150F706C func_151470FC func_1515F850 func_151CF898 func_151B8400
```

The run ended in `AGENT_ACTION: BATCH_COMPLETE`. The entire 2,072,880-byte
integrated game-code payload and every linked external rodata payload matched
the checksum-validated US ROM. All 2,805 tests completed successfully (nine
skipped; 156.270 seconds), followed by valid metadata, progress and whitespace
checks. This evidence update changes documentation only after that tested
revision; it does not change source, compiler inputs or linker mappings.

The review also corrected the typed call in disabled `func_15114188`; enabling
it for `finish` compiled successfully and measured `CURRENT (1150)`, replacing
the historical recorded 700. The optional typed-parameter cleanup of disabled
`func_15157AA8` retained `CURRENT (65)` and its exact frame/local homes. Both
were restored transactionally to deferred candidates with canonical
`GLOBAL_ASM`; neither is included in the ten matching functions.
