# US visibility Huffman codebook reconstruction

Follow-up: [visibility node sets](us_visibility_bitmaps.md) add 16 even entries
with independently derived geometry dimensions. This document retains the
original codebook batch and its validation.

Twenty bank-05 codebooks reconstruct **12,545 stored bytes** from editable
byte-symbol Huffman bitstrings. Each decoded entry has a derived four-byte
tree allocation, 256 big-endian codeword/bit-length pairs, and four bytes
of zero alignment. Absent symbols have zero codeword and length.

## Native evidence

The complete consumer spans and their SHA-1 hashes appear in the adjacent
[JSON evidence](us_visibility_reconstruction.json). func_150025FC loads
bank-05 entries scene * 2 and scene * 2 + 1. func_15018500 builds a
tree of six-byte nodes containing a signed symbol and two signed child
offsets, traversing each codeword most-significant bit first. The allocation
is six times the number of distinct prefixes, including the root.
func_150183D0 uses the resulting tree to locate visibility rows.
func_150A6760 decodes visibility bytes and applies their bits to BSP nodes.
The generic bank loader and decompressor spans are also pinned.

This work covers odd entries 5, 13, 15, 23, 25, 39, 47, 53, 55, 57, 59,
61, 73, 87, 89, 91, 97, 105, 111 and 121. The runtime row counts of the
paired bitstreams require further geometry evidence. Those bitstreams,
the bank index and padding remain raw and receive no reconstructed credit.

## Source and validation contract

scripts/visibility_codec.py validates 256 symbol slots, binary codes of
one through 32 bits, uniqueness, prefix freedom, native offset bounds,
allocation and alignment. scripts/visibility_build.py preserves sources
under build/assets/visibility/us: codebooks.json, the reviewed manifest
and whole-bank backing. Only freshly encoded codebook ranges are overlaid.
Level-6 raw DEFLATE with the native decoded-length prefix reproduces all
20 entries. The whole candidate bank must equal the independent ROM.

Run ./conker visibility-assets build. Malformed, edited or missing inputs
fail without overwriting them; ./conker visibility-assets recover backs
up the existing input folder before restoring reviewed sources.
Make tracks all required inputs and recovers a missing generated part.
Native report credit uses slices from the actual ROM linker object and
checks current source hashes before and after preparation.

The independent audit walks all **3,293 present symbol codes**, verifies
**3,293 symbol reassignment mutations**, rejects **12 consumer endpoint
mutations**, and confirms whole-bank equality and unchanged source hashes.
Focused tests additionally exercise invalid schemas and codes, allocation
and alignment errors, source preservation/recovery, source races, stale
linker objects and missing Make inputs.

## Accepted validation

The full US asset build reproduces all 67,108,864 ROM bytes, SHA-1
4cbadd3c4e0729dec46af64ad018050eada4f47a. The build wrapper took 100 seconds
(96.989 seconds in the build stage, including 85.784 seconds for compile,
link and verification). These are command timings, not workflow duration.
The full Docker suite passes 2,537 tests with eight skips in 122.612 seconds.
Native objdiff, progress and whitespace gates pass.

Matched Data is **60,683,092 / 65,120,512 (93.18584%)**, an increase of
12,545 bytes. Complete Data is 60,682,324 (93.184654%). Code and the
Data denominator are unchanged. The only previous unit measure to change
is the bank-05 unmatched remainder. All 10,624 prior asset proofs and
25,871 prior source-file hashes are unchanged. The native report has
11,639 units, 10,949 complete, and no compile errors.

Base commit: 094102644c4c2f5aefaa0fc4b609416918f66f58.
Validated source fingerprint:
518e1c9e3889271567de2479159207d60b03547d26c9e19f73119ffb48b2a1ce.
Report SHA-256:
33f0dc698b82e11e4f863e5664e1a445563d9bc50721abe268f6bf2fcf2f416b.
The independently audited snapshot is current. This result is local;
nothing has been published to decomp.dev.
