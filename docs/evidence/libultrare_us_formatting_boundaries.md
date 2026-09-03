# US Rare formatting-library boundaries

This note records the reviewed main-executable boundaries and function identities
for Conker's Rare-modified formatting code. The sync-print object has since been
reconstructed exactly, and the complete main formatter is now reconstructed
too. The floating-point formatter now matches as a complete object as well. The original
identification evidence and earlier candidate history are retained below.

## Evidence

- Canonical US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Raw comparison map: `config/reference/us.yaml`, with the corresponding
  independently generated blocks under `reference/us/asm/`.
- GoldenEye identifies its `libultrare` directory as Rare-modified and places
  `xprintf.c` there, while keeping `xldtob.c` with the original libc sources.
- GoldenEye's Rare `_Printf` has the same distinctive positive-byte scan and
  pointer rollback used at Conker `0x800020D0`.
- GoldenEye and libreultra's sync-print implementations identify the discard
  callback followed by the `_Printf(callback, NULL, fmt, args)` wrapper at
  Conker `0x80002070` and `0x80002088`.
- Stock I/J/K/L object symbols and the corresponding source structure identify
  the private `_Ldunscale`, `_Genld`, and `_Putfld` helpers.

External source references:

- <https://github.com/n64decomp/007/blob/master/src/libultrare/readme.md>
- <https://github.com/n64decomp/007/blob/master/src/libultrare/libc/xprintf.c>
- <https://github.com/n64decomp/007/blob/master/src/libultra/libc/xldtob.c>
- <https://github.com/n64decomp/007/blob/master/src/rmon.c>
- <https://github.com/n64decomp/libreultra/blob/master/src/libc/syncprintf.c>

## Reviewed source units

| US ROM range | VRAM range | Size | Proposed source | Members |
|---|---|---:|---|---|
| `0x1550:0x2070` | `0x80001550:0x80002070` | `0xB20` | `src/libultrare/libc/xldtob.c` | `_Ldtob`, `_Ldunscale`, `_Genld` |
| `0x2070:0x20D0` | `0x80002070:0x800020D0` | `0x60` | `lib/libultrare/src/libultrare/libc/syncprintf.c` | `proutSyncPrintf`, `osSyncPrintf` |
| `0x20D0:0x2DB0` | `0x800020D0:0x80002DB0` | `0xCE0` | `src/libultrare/libc/xprintf.c` | `_Printf`, `_Putfld` |

`0x1550` begins immediately after the preceding startup function. `0x2070`
follows `_Genld` and its alignment word. `0x20D0` follows the sync-print wrapper.
`0x2DB0` follows `_Putfld` and two trailing alignment words and is already the
next raw-ASM map boundary. All three ranges use 16-byte IDO object boundaries.

## Function work items

| Work-item ID | US symbol | VRAM | Recovered extent | Size |
|---|---|---:|---|---:|
| `_Ldtob` | `func_80001550` | `0x80001550` | `0x1550:0x19F0` | `0x4A0` |
| `_Ldunscale` | `func_800019F0` | `0x800019F0` | `0x19F0:0x1AA8` | `0xB8` |
| `_Genld` | `func_80001AA8` | `0x80001AA8` | `0x1AA8:0x2070` | `0x5C8` |
| `proutSyncPrintf` | `func_80002070` | `0x80002070` | `0x2070:0x2088` | `0x18` |
| `osSyncPrintf` | `func_80002088` | `0x80002088` | `0x2088:0x20D0` | `0x48` |
| `_Printf` | `func_800020D0` | `0x800020D0` | `0x20D0:0x2718` | `0x648` |
| `_Putfld` | `func_80002718` | `0x80002718` | `0x2718:0x2DB0` | `0x698` |

The final recovered extent in each source unit includes any compiler-emitted
tail padding before the next reviewed object boundary. Focused matching still
stops at the function return.

The corresponding complete `xldtob` and `xprintf` initialized/read-only data
sections are now archive-backed at `0x2AAF0:0x2AB40` and
`0x2BF20:0x2C080`. Their separate build representation and exact checksums are
recorded in
[`libultra_us_data_object_bounds.md`](libultra_us_data_object_bounds.md).

## Exact sync-print reconstruction

The complete `0x2070:0x20D0` object now reproduces with IDO `-O2 -g3`,
under `lib/libultrare/src/libultrare/libc/syncprintf.c`. Its entries are
`proutSyncPrintf` at 0x00 (24 bytes) and `osSyncPrintf` at 0x18 (72 bytes).
The callback returns `(void *)1`. The wrapper clears an external halfword at
`0x80035500`, supplies the runtime callback alias `0x10002070`, and calls
the still-raw formatter at `0x800020D0` with the IDO stack varargs pointer.
All relocations and all 96 text bytes compare exactly; the full text occurs
once in the main executable. There are no nonempty data/rodata/BSS sections,
and the external debugger halfword does not claim an original BSS extent.
The normalized full-object MD5 is `97231c99cb43c199a338fe1cb3c7c74b`.
The raw comparison map remains unchanged. The canonical map links the archive
member; the two raw work items and skeleton are retired using the supported CLI.

## Remaining limits

For `xldtob` and `xprintf`, the text identities and boundaries remain structural
evidence, not byte-exact archive matches. GoldenEye supplies Rare source lineage,
but its compiled helper order and some instruction details differ. These text
units must remain raw assembly until their C implementations reach `CURRENT
(0)` and the complete US build remains byte-identical. Their exact data
sections do not imply that the text already matches.

## Continued library-only comparison, 2026-09-03

The earlier isolated formatting candidate was reviewed against this branch's
raw ROM assembly. A complete C-only reconstruction of `0x1550:0x2070` now emits
the correct 2,848-byte text extent and all three function boundaries. Four
bounded candidate compiles were performed. Moving the digit-generation pointer
increment into the `for` loop's increment expression reproduces Conker's branch
delay-slot scheduling. The final candidate differs in exactly two words:

| ROM offset | Candidate | Conker |
| --- | --- | --- |
| `0x1590` | `sdc1 $f2, 0x98($sp)` | `sdc1 $f2, 0xA0($sp)` |
| `0x1854` | `ldc1 $f10, 0x98($sp)` | `ldc1 $f10, 0xA0($sp)` |

Both accesses concern the same saved double-precision zero temporary. Other
declaration variants disturbed the frame or conversion sequence and were not
retained. The best whole-object candidate MD5 was
`741897706d7c911822e74e032e30e854`, compiled with the Rare snapshot's IDO
`-O2 -g3` settings and non-runtime `.mdebug` removed. All emitted text and
relocations were compared; there were no nonempty data/rodata/BSS/COMMON
sections in this candidate. Constants stayed external to the existing exact
data archive. This is still a non-exact object and is not mapped into either
ROM or library archive.

The best `_Ldtob` body is preserved under a disabled block in
`src/libultrare/libc/xldtob.c`; its original `GLOBAL_ASM` remains active.
`_Ldunscale` and `_Genld` were independently checked with `./conker finish` and
both report `CURRENT (0)`. Their C bodies replace only their own placeholders.
The recorded source-function extents add 1,664 matched bytes (184 and 1,480;
the latter includes four alignment bytes). No source unit is declared complete:
the canonical `0x1550:0x2070` mapping and its independent comparison remain raw
assembly. A full-ROM pass therefore does not claim that these two C helpers
are already linked into the main image.

The temporary research archive source/member was removed from the build list
after comparison. The accepted Rare archive and all earlier object checksums
were rebuilt and verified. The active library archive total stays at 139,008
CPU text bytes; overall matched CPU code rises to 144,932 bytes with these two
source-local helpers. The MP3/RSP work remains separate from formatter status.

`./conker verify-batch _Ldunscale _Genld` reports `BATCH_COMPLETE`: the complete
US ROM passes, all 164 tests pass, metadata and progress are valid, and
whitespace checks are clean. The US ROM SHA-1 remains
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The independently rebuilt library
overlay also retains SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

## Complete main formatter reconstruction

The subsequent whole-object pass resolves `_Printf` and `_Putfld`, including
all 52 generated switch-table entries, the flag/qualifier tables and both
padding strings. The complete `xprintf.o` owns 3,296 text bytes, 80 data bytes
and 256 rodata bytes. It replaces the two copied-data members and passes the
full US ROM checksum. See
[complete formatter evidence](libultrare_us_xprintf_reconstruction.md).

The untouched `src/libultrare/libc/xprintf.c` skeleton and its two raw work
items are retired through the supported CLI using this boundary record.
`xldtob.c` remains raw with two matched helpers and a preserved non-exact
`_Ldtob` candidate. Earlier formatter mismatch scores above are historical.

## Complete floating-point formatter reconstruction

The next library-only pass resolves the two remaining `_Ldtob` stack accesses
by retaining the observed unused word between floating temporaries and shorts.
The focused `./conker finish _Ldtob` check reports `CURRENT (0)` on the first
follow-up candidate. This reproduces the observed stack layout; it does not
claim the original unused variable's name or purpose. Together with the earlier
`_Ldunscale` and `_Genld` matches, all three entries are now exact.

The preserved complete C implementation is
`lib/libultrare/src/libultrare/libc/xldtob.c`, derived from the independent
Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514` with Conker's
reviewed formatting layout and control flow. It defines all nine decimal
powers and the `NaN`, `Inf` and `0` strings. The compiler emits the `1.0e8`
literal at rodata offset `0x58`. No target instruction body is copied or patched.
Two archive compiles established the exact constant-section representation.

| Entry | US ROM range | Code bytes |
| --- | --- | ---: |
| `_Ldtob` / `func_80001550` | `0x1550:0x19F0` | 1,184 |
| `_Ldunscale` / `func_800019F0` | `0x19F0:0x1AA8` | 184 |
| `_Genld` / `func_80001AA8` | `0x1AA8:0x206C` | 1,476 |
| Final object padding | `0x206C:0x2070` | 4 |

The complete 2,848-byte text section occurs uniquely at `0x1550:0x2070`.
All 21 text relocations resolve exactly: nine calls and six HI16/LO16 pairs.
The external calls bind `func_80022EC0` to the linked `memcpy` and
`func_80023060` to `ldiv`; internal calls retain the reviewed regional symbols.
The complete 96-byte rodata section occupies `0x2BF20:0x2BF80` and contains no
relocations. The compiler object has no initialized data, nonempty NOBITS
allocation or COMMON symbols. Its ELF `.reginfo` is metadata, not ROM payload.

- Compiler: IDO `-O2 -g3`, stripping only non-runtime `.mdebug`.
- Complete object MD5: `46e57720ef652c900db76749598e2065`.
- Resolved text SHA-1: `bc3165ea0adcf34b02285b1d513252d8bf4c66e8`.
- Complete rodata SHA-1: `2a0f4a3a817f33bbb80b1096284dc4fb87c4bfdf`.

The archive mapping replaces the earlier separate `xldtob_data` member. Its
actual input section remains `.rodata`, with `linker_section_order: .data`
retaining Conker's interleaved section position. The independent comparison
map remains raw assembly. Earlier nonzero formatter results in this note are
historical and do not describe this final complete object.

The complete US build reports `build/us/conker.us.z64: OK`, retaining all
67,108,864 bytes and SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
After that gate, `retire-library-units --preserved-source` removed the three
completed work items and duplicate `src/libultrare/libc/xldtob.c`, preserving
its byte-identical library copy. Exact archive CPU text is now 145,152 bytes;
overall matched CPU code is 149,412 bytes without double-counting the retired
source matches.

The follow-up shared-tool and integration gates pass: 169 Python tests, all
33 reconstructed-object audits (170 functions, 94,528 text bytes), current
progress output and clean whitespace. The independently rebuilt overlay
retains SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
