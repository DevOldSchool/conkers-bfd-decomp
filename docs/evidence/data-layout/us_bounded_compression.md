# EOF-bounded compression and 16K token blocks

This follow-up reconstructs another **828,837 stored bytes** through fresh
compression: 12 native characters (105,553 bytes), 15 complete scene bundles
(686,344 bytes), and five sprite entries (36,940 bytes). The decoded formats
are already independently understood and typed. No original compressed bytes,
token sequences, Huffman tables or patch masks enter the encoder.

## Evidence for the encoder changes

A read-only DEFLATE parser following [RFC 1951](https://www.rfc-editor.org/rfc/rfc1951)
compared complete literal/match sequences. All five excluded sprites differ
only at their final match: the original encoder selects a match within the
remaining input, while stock gzip compares beyond EOF before truncating its
chosen length. Bounded comparisons reproduce all 50 compressed sprite entries.

Remaining large-model mismatches have identical complete decoded token
sequences but different block boundaries. The original full blocks contain
16,383 tokens; later heuristic boundaries occur at 4,096-token intervals.
A 16,384-token buffer reproduces those boundaries. The hash table remains
15 bits; the smaller-memory gzip presets would also change that table and
are not used. With both changes, level six reproduces all 27 reviewed model
candidates and the five sprites.

The standalone encoder derives its compression core from GNU gzip 1.2.4.
[Source provenance and licensing](../../../scripts/vendor/bounded_deflate/PROVENANCE.md)
record the official archive and checksum, retained copyright and GPL terms,
and exact local changes. The build needs no network download. A small driver
reads semantic asset bytes on stdin and emits raw DEFLATE on stdout.

The prototype passed 102 synthetic cases under address and undefined-behavior
sanitizers, including empty inputs, EOF boundaries, window boundaries and
250,000-byte payloads. Linux GCC and native macOS Clang reproduce all 32 new
ROM entries identically. The smaller driver also matched the full modified
gzip executable on 102 synthetic level-six/nine cases. Production accepts
only the reviewed level-six contract.

## Reconstruction and preservation

The new explicit encoder contract is rzip-bounded-deflate-v1, level six,
15-bit window/hash and 16,384-token buffers. scripts/rzip_bounded.py keys its
compiled cache by source hashes, compiler flags, OS and architecture; validates
the executable hash; atomically replaces completed outputs; and rejects a
source change during compilation. Independent zlib decoding must consume the
entire raw stream and reproduce exactly the input before the native length
prefix is added.

Bank-01 additions: 26, 33, 58, 83, 84, 93, 118, 146, 150, 151, 159 and 180.
Bank-04 additions: 2, 7, 12, 18, 19, 23, 29, 47, 50, 51, 52, 55, 57, 59 and 60.
Sprite additions: 4, 5, 19, 47 and 63.

Existing model manifests, encoder choices and editable records stay unchanged.
New entries use the established native character and model-bundle schemas.
The model partitions preserve raw index and gap bytes. Sprite source extension
backs up the previous directory and preserves all 368 prior files there;
every existing PNG and backing file also retains identical current contents.
Only the current sprite manifest changes to include the five added entries.
All 56 entries now rebuild from 212 pairs of editable color/intensity PNGs.

Make explicitly depends on every encoder source/header; source edits invalidate
packing, and missing sources fail. The report uses the actual ROM linker
objects and independently generated original targets. Unreconstructed bank
index and gaps retain their existing denominator and receive no credit.

## Validation

Focused tests cover EOF and block-boundary regression vectors, independent
decoding, executable corruption, cache invalidation, compilation races,
missing compilers, disjoint explicit encoder selections and Make prerequisites.
Five encoder tests, 37 model-build tests and 33 Make tests pass.
The [independent audit](us_bounded_compression.json) verifies 524 vertex
endpoint mutations, 12 joint mutations, 12 normal mutations, 11 procedural
index mutations and 116 sprite-pixel mutations. All 28 model consumer endpoint
mutations are rejected. Whole character, scene and sprite banks match the
original. All 25,874 prior source-file hashes remain preserved, with the
previous sprite manifest retained in its explicit recovery backup.
Full asset reconstruction passes in 109 seconds and reproduces all 67,108,864
ROM bytes, SHA-1 4cbadd3c4e0729dec46af64ad018050eada4f47a. The full Docker suite
passes 2,542 tests in 122.437 seconds, with eight skips. Native objdiff has no
compile errors; progress and whitespace checks pass. The current report has
61,511,929 matched Data bytes of 65,120,512 (94.4586%), a gain of 828,837.
Complete Data also rises by 828,837; Code and the denominator are unchanged.
All 10,624 unaffected prior asset proofs and 25,874 prior source hashes are
preserved. The 27 added model units and sprite unit account for the gain;
only the corresponding raw bank-00/01/04 units shrink.

Tested base commit: 094102644c4c2f5aefaa0fc4b609416918f66f58, with local changes.
Source fingerprint: 6637e932d2e3fcc7f884e6f8ebb0056f5eccb3bcab34b6b6bfbb772687ea3970.
Report SHA-256: 021bcfbebff0272a6e173026a2058132cd26156608addce9ae71dfad107abc7a.
