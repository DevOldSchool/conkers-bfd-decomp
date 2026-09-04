# Conker US Rare formatter reconstruction

The complete `xprintf.o` now reproduces both formatter functions and all three
ROM payload sections. It replaces the raw `0x20D0:0x2DB0` code range and the two
earlier copied-data archive members. This is library work only.

## Source and complete boundaries

Independent lineage is Perfect Dark revision
`169ed48bdcbfb3b568b028bd5bebb27680073514`, `src/lib/ultra/libc/xprintf.c`,
and the pinned SDK's `xstdio.h`/IDO varargs definitions. The existing reviewed
Rare candidate established Conker's positive-byte scan, pointer rollback and
field-width arithmetic. No ROM assembly body or prebuilt code was substituted.

| ROM interval | Section/function | Bytes |
| --- | --- | ---: |
| `0x20D0:0x2718` | `_Printf` | 1,608 |
| `0x2718:0x2DA8` | `_Putfld` | 1,680 |
| `0x2DA8:0x2DB0` | Final text alignment | 8 |
| `0x2AAF0:0x2AB40` | Complete `.data` | 80 |
| `0x2BF80:0x2C080` | Complete `.rodata` | 256 |

The full 3,296-byte text template occurs only at `0x20D0`. Both function
boundaries, all instructions and final alignment bytes compare exactly.
There is no BSS or COMMON allocation in this object.

`_Printf` uses a `0xE0`-byte frame. The earlier candidate had an otherwise
agreeing layout but reserved eight fewer bytes. The reconstruction explicitly
preserves those unused eight bytes below the formatting buffer; this records
an observed stack-layout requirement, not a recovered original variable name.
The scan byte remains `u8`, which also preserves the target's branch operand
order. Two layout/type candidates were compiled, followed by a compilation
using the final library names. All use IDO `-O2 -g3`; only non-runtime `.mdebug`
metadata is stripped.

## Data and relocation ownership

The source defines both 32-character padding strings, their terminators and
alignment, the qualifier string, flag characters and six flag masks. Its C
switch produces all 52 jump-table entries. These are complete compiler-emitted
sections, not text matched against separately copied target tables.

Compiler object MD5: `61e7376510f0cec3e80b1d60d7eda4f2`.
Resolved section SHA-1 values:

| Section | SHA-1 |
| --- | --- |
| `.text` | `a6833a7cdf118a8ee3b3754d1476d633ccb76019` |
| `.data` | `7cc265f8a697edc6a80c3e054442ab663d2008e7` |
| `.rodata` | `805865000aa86b0007c4c21d331f1b2c17e9aaad` |

All 73 relocations are reviewed: nine calls, six HI/LO pairs and 52 `R_MIPS_32`
code pointers in rodata. Main code links at `0x80000000` but executes through
`0x10000000`. The existing checked library preparer adjusts those 52 data
addends by `-0x70000000`; it changes no instructions or relocation records.
The unmodified compiler object retains the pinned MD5 above. The staged
object MD5 is `98fb6d6148c3ec36572ce9294d2f90ee`.

Splat's supported `linker_section_order: .data` places this object's actual
`.rodata` at its original position among the initialized data inputs. It does
not rename or split the compiler section. The generated linker script selects
the same `xprintf.o` for `.text`, `.data` and `.rodata`. The old
`xprintf_data.o` and `xprintf_rodata.o` build sources, archive selections and
checksum entries are removed, so the table has one owner.

The formatter calls existing `strchr`, `strlen`, `_Litob`, and the raw
floating formatter at `0x80001550`. Symbolic aliases preserve the existing raw
names for these standard-library calls and the two new exports. No game source
or shared runtime declarations change.

## Verification

The complete US ROM passes `./conker build --profile us`, retaining SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` across all 67,108,864 bytes. This
verifies the newly linked formatter, both complete data sections and the
generated table in their final locations. All 32 active reconstruction objects
pass the independent section/relocation audit.

The untouched raw formatter source unit and its two raw work items were
retired through `./conker retire-library-units` after this full-ROM gate. The remaining
floating formatter and power candidates keep their raw mappings. The MP3
bit/Huffman utility variant remains raw pending the separately documented
assembly-workflow approval.

`./conker game-build --profile us` also passes the complete 2,072,880-byte
overlay, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 164 Python
tests pass; progress output is current and whitespace checks are clean. The
new mapping checks cover the complete formatter and its explicit rodata link
order. The source inventory now contains 429 work items and 129 units.

Exact archive CPU text totals 142,304 bytes (95,664 main and 46,640 overlay).
Including independently matched source functions, matched CPU code totals
148,228 bytes. Reviewed boundary coverage is unchanged: the formatter already
had a reviewed raw boundary, which the archive now replaces. The main profile
links 144 unique library objects through 184 sections, including four RSP
payload members excluded from CPU progress.
