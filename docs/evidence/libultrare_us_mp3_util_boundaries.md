# Conker US MP3 bit/Huffman utility boundaries

The complete overlay interval `0x1F8870:0x1F8CF0` is the Rare MP3 bit/Huffman
utility family. Following explicit approval to adapt the independent assembly,
it now links from `lib/libultrare/src/libultrare/mp3/util.S`. All five functions
and all 1,152 text bytes match. This is an assembly-library reconstruction;
its bytes receive archive credit, without new C-function match records.

## Structural comparison

Independent source: Perfect Dark revision
`169ed48bdcbfb3b568b028bd5bebb27680073514`, `src/lib/mp3/util.s`.
All five entries occur in the same order. The preceding stream object ends at
`0x1F8870`; the following independently reproduced transform starts at
`0x1F8CF0`. The final utility return and delay slot end exactly at that boundary.

| Conker runtime entry | Source identity | Conker bytes | Reference instructions | Conker instructions |
| --- | --- | ---: | ---: | ---: |
| `0x151F8870` | `mp3util000461c0` | 188 | 52 | 47 |
| `0x151F892C` | `mp3util00046290` | 52 | 13 | 13 |
| `0x151F8960` | `mp3util_get_bits` | 52 | 13 | 13 |
| `0x151F8994` | `mp3util000462f8` | 440 | 108 | 110 |
| `0x151F8B4C` | `mp3util000464a8` | 420 | 103 | 105 |

The 1,152-byte interval contains 288 instructions and no final padding.
The reference has 289 instructions before object alignment. A normalized
source-instruction comparison resolves equivalent pseudo-instruction spellings,
register aliases, immediates, local-label order and internal function names.
Exactly four differing instruction groups remain, all involving table access:

1. The first helper replaces the reference's three-instruction load of the
   length-table pointer with `addi $t2, $s5, 0x2200`.
2. It replaces the three-instruction load of the value-table pointer plus its
   index addition with `add $t2, $t3, $s5`.
3. The pair decoder loads the pointer at `0x800E0E20`, instead of taking the
   reference's static table address, and loads `$s5` from `0x800E0E24`.
4. The quad decoder makes the same two pointer loads.

The two 13-instruction bit readers agree completely. All other control flow,
Huffman traversal, sign handling, output stores and register save/restore
sequences agree after the stated symbolic normalization. Conker's playback
wrapper loads the combined lookup asset referenced at `0x800E0E24`; its second
table begins `0x2200` bytes into that allocation. The decoder separately sets
the pointer table used through `0x800E0E20`. These independently reconstructed
callers corroborate the utility's changed storage model.

## Ownership and matching limits

This is a Conker/Rare variant, not a stock libultra object. The internal helpers
use a handwritten register convention, including `$t0`, `$s0`, `$s1` and `$s5`;
they must not be given ordinary C-call signatures based only on entry labels.
The trapping integer `add`, `addi` and `sub` instructions also survive in the
original handwritten source.

The initial normalized comparison established identity and bounds before a
complete relocated-object match was available. That interval stayed raw while
the explicit assembly override was pending. The user then authorized the MP3
work, allowing exactly the four documented table-access changes to the
independent source. No target assembly file or ROM instruction body was used
as replacement source.

Workspace/table pointers remain external; these accesses do not establish
original BSS allocation or initialized-data ownership. The canonical map now
selects the archive member, and the independently generated comparison map
still selects raw ROM-derived assembly. No game C source unit or function
inventory entry is introduced for these assembly routines.

## Complete assembly-object reconstruction

The existing build preprocesses `util.S` with IDO and assembles it with GNU MIPS
binutils for VR4300/o32. Beyond the four source changes above, only provenance
comments, trailing-whitespace cleanup and ELF function type/size metadata were
added. Those additions emit no instructions or constants. The first assembled
candidate matches every instruction, and the complete 1,152-byte text template
occurs once in the game image. The five ELF function extents are 188, 52, 52,
440 and 420 bytes, with no final padding.

- Complete assembler-object MD5: `efc9a90b037447be21c91d61b61b1fe0`.
- Resolved full-text SHA-1: `58a30e95a62dac87c8260191c4ebcbbe75ba340b`.
- Relocations: five internal calls and four HI16/LO16 pairs, all resolved exactly.
- The two pointer slots remain `var8009c650 = 0x800E0E20` and
  `__conker_mp3_lookup_base = 0x800E0E24`.
- No nonempty `.data`, `.rodata`, BSS or COMMON allocation is emitted.
  `.reginfo` and `.MIPS.abiflags` are ELF metadata rather than ROM payload.

The old fixed-address definitions of `mp3util_get_bits`, `mp3util000462f8` and
`mp3util000464a8` are removed; the stream and decoder now call the archive's real
exports. The internal register-convention helpers remain assembly functions.

## Integration verification

The complete overlay passes `./conker game-build --profile us`: all 2,072,880
bytes retain SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The linked ELF
exports all five functions at the table's exact addresses and sizes as real
section-defined functions, rather than absolute-address substitutes.

`./conker build --profile us` also passes for the complete 67,108,864-byte ROM,
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. That main build preserves the
original compressed game asset; the independently rebuilt overlay is verified
separately by whole-payload equality, without claiming recompression.

All 170 Python tests pass, including the archive extent and independent raw
comparison mapping checks. All 34 active reconstruction objects compare
exactly: 175 functions and 95,680 text bytes. Progress output is current and
whitespace is clean. The utility adds 1,152 archive bytes, bringing total exact
CPU library text to 146,304 bytes (98,512 main and 47,792 overlay). Registered
function/source-unit counts do not change. The power candidate and original
workspace ownership remain unresolved; no ordinary game source was changed.
