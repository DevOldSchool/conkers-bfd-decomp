# US game-overlay matrix utility variant

The complete `0x270`-byte range `0x1EFD00:0x1EFF70` is reproduced by the
SDK matrix algorithms compiled with the existing Rare `PR/gu.h` and IDO
graphics optimization level `-O3`. It is integrated as
`libultrare:mtxutil.o(.text)`, covering four functions. No function records
or source-unit skeletons occupied this range before the integration.

## Why the stock comparison differed

The pinned `lib/ultralib` revision
`e24c836796df4bf520ff8b11a5c9d2cea3a66cbd` defines `FIX32TOF(x)` as
`((float)(x) * (1.0f / (float)0x00010000))`. Its 2.0I ROM `mtxutil.o`
already has the correct section size, function order, and first three
functions, but its final routine uses multiplication by a reciprocal.

The already checked-in `lib/libultrare/include/PR/gu.h` defines the same
macro as `((float)(x) / (float)0x00010000)`, explicitly noting the original
expression in a comment. This is the header snapshot from GoldenEye revision
`c4356466796c697dfd298010b9bed261f9ed8c6a` already used by the Rare archive.
Conker's last matrix routine loads `65536.0f` and executes `div.s`, exactly
as this header requires. The different operation also changes scheduling.

The reconstructed source retains the pinned stock matrix algorithms,
replaces the private `guint.h` include with the existing Rare `PR/gu.h`,
and uses that header's declarations and conversion macros. No shared header
changes, instruction patches, inline assembly, or handwritten assembly are
needed. A member-specific `-O3` setting reproduces the stock 2.0I graphics
optimization level; the existing Rare members keep their accepted `-O1`
flags and checksums.

This establishes an exact Rare-header variant of the object. It does not
prove who edited the original source or identify the original archive name.

## Complete section and relocation proof

The authority is the owned US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` and extracted game-code SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The independently generated
raw assembly is `reference/game/us/asm/1EFD00.s`.

| Function | Object offset | Game address | Instruction bytes |
| --- | --- | --- | ---: |
| `guMtxF2L` | `0` | `0x151EFD00` | 256 |
| `guMtxIdentF` | `0x100` | `0x151EFE00` | 136 |
| `guMtxIdent` | `0x188` | `0x151EFE88` | 48 |
| `guMtxL2F` | `0x1B8` | `0x151EFEB8` | 180 |

The 620 instruction bytes are followed by one zero padding word. The
complete text template has exactly one occurrence in the entire game image,
at `0x1EFD00`, using the relocation masks in
`scripts/audit_library_boundaries.py`. All opcode and register bits remain
part of that comparison.

There are exactly two relocations, both `R_MIPS_26` calls from `guMtxIdent`:

| Object offset | Symbol | Resolved target | Retail instruction word |
| --- | --- | --- | --- |
| `0x194` | `guMtxIdentF` | `0x151EFE00` | `0x0D47BF80` |
| `0x1A0` | `guMtxF2L` | `0x151EFD00` | `0x0D47BF40` |

Resolving those two symbol relocations produces an exact byte comparison of
the entire `0x270`-byte section, with SHA-1
`e5fbfda1060bfe5c37451ddd812059e4f61cc52f`. The existing matrix aliases in
`config/game/us-sdk.ld` already point at those addresses; no new bindings
are needed. The object has no nonempty data, rodata, or BSS sections.
Its other allocated ELF section is `.reginfo` linker metadata, not a missing
runtime allocation. The adjacent complete objects are Rare `contreaddata.o`
and stock `sprintf.o`, independently fixing both ends of this range.

The finalized object's MD5 is `1a7b1770b504d6ae91fb48420e943ee6`.
`lib/libultrare/object-md5s.txt` labels it as a Conker reconstruction
checksum, distinct from the existing upstream accepted checksums. That
checksum protects the reviewed output; the independent retail comparison
above is the match evidence.

## Integration and validation

The canonical game map links the entire member from the existing Rare
archive. Its source resides in `lib/libultrare/src/libultrare/gu/mtxutil.c`
because the complete object is now reproduced exactly. The reference-map
generator continues to turn the library range into raw ASM.

The first C candidate matched the entire section. On 2026-09-02:

- `./conker libultrare` compiled the source and preserved all existing accepted
  object checksums. Archive staging also verified the new reconstruction checksum.
- `./conker game-build --refresh` produced the complete byte-identical game
  image with SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. The linked
  ELF `.game` section and its matrix subrange were independently hash-checked
  against the complete-image and matrix-section digests above.
- `./conker build --profile us` produced the original complete US ROM SHA-1
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- All 150 tests passed, including the exact matrix archive extent and updated
  byte totals. Generated progress, whitespace, and shell syntax checks passed.

Archive-backed text increases from 41,184 to 41,808 bytes; total matched code
increases from 45,444 to 46,068 bytes. The existing 433 function records and
131 source units are unchanged.
