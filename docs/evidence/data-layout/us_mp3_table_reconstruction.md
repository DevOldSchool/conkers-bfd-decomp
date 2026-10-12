# US MP3 decoder table reconstruction

The US bank-17 entries 4, 5 and 6 contain 59,552 bytes of decoder tables.
Their values are now generated from the independent Huffman seed definitions
already present in `lib/libultrare/src/libultrare/mp3/decoder.c`. The original
ROM tables are comparison targets only. This does not reconstruct or credit
any encoded MP3 stream in bank 16.

## Native records and layout

The 17 canonical C codebooks contain 1,410 literal `(x, y, width, code)` seed
rows after removing checked sentinel records. `var8005f670` selects a null
codebook followed by 33 tree instances, including repeated books. The encoder
validates symbol and code bounds, prefix freedom, complete branches, pointer
mapping and representable relative child edges. It visits each depth in seed
order and emits four-byte nodes `(zero-edge, one-edge, x, y)`. Edges are unsigned
node-relative offsets. Codes are consumed least-significant bit first, as
confirmed by the original Huffman helper in `util.S`.

The 36 big-endian offsets are derived from those generated tree sizes. The
fast table has two 8,704-byte halves: `(y << 4) | x` followed by consumed bit
length for every eight-bit input prefix. Codes longer than eight bits use a
zero-length fallback to the tree. The stored tree allocation ends with one
unlinked initialized empty node `(0, 0, 255, 255)`; its runtime purpose has not
been established. It is represented explicitly, not treated as zero padding.

| Entry | ROM range (exclusive end) | Bytes | Role |
| --- | --- | ---: | --- |
| 4 | `0x3F738D0..0x3F73960` | 144 | 36 tree offsets |
| 5 | `0x3F73960..0x3F77D60` | 17,408 | Fast symbols and bit lengths |
| 6 | `0x3F77D60..0x3F82170` | 42,000 | Relative Huffman nodes |

The full registered playback, decoder, frame-reader and utility code spans
are SHA-1 pinned in `scripts/mp3_table_codec.py`. They cover the original
external-table loads, prefix lookup and node traversal. Exact extents are
checked against the existing audio YAML and original ROM descriptors.

## Build and verification

`./conker mp3-assets build-tables` initializes editable `tables.json` and a
manifest under `build/assets/mp3-tables/us/`. Every subsequent build freshly
encodes those inputs, checks all three original payload hashes and compares
against independent ROM slices. Missing, malformed or changed inputs are
preserved and fail the build. `./conker mp3-assets recover-tables` backs up the
entire input directory before restoring reviewed seed records.

The asset Make rules link the reconstructed parts, rebuild on seed/codec
changes and reject missing sources even if old objects remain. Native objdiff
compares each actual linker object with both freshly encoded records and an
independent original-ROM target. Source and object hashes are rechecked; these
three spans replace equal-sized unreconstructed storage without changing the
Data denominator.

[Machine-readable evidence](us_mp3_table_reconstruction.json) records exact
hashes, independently traversed leaves and fast lookup prefixes, one valid
symbol-swap mutation per canonical book, and both endpoints of each of the
four consumer spans. Unit tests cover malformed seeds, source preservation,
transactional recovery, report object substitution and Make invalidation.

## Completed integration acceptance

The uncommitted worktree based on `094102644c4c2f5aefaa0fc4b609416918f66f58`
passed `./conker build --assets`: all 67,108,864 bytes equal the original US ROM
(SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`). The full Docker suite passed
2,493 tests with eight skips. Progress and whitespace gates passed.

The native report contains 11,184 units with no compile errors. Matched Data
increased by exactly 59,552 bytes to **37,079,042 / 65,120,512 (56.939106%)**.
Complete Data increased by the same amount to 37,078,274. Code measures and the
Data denominator did not change. All 10,165 prior reconstructed asset proofs
and 24,138 unique editable-source file hashes were preserved; only bank-17
unreconstructed storage shrank. The three new table units are complete.

The current input fingerprint is
`1b2f3abde46d68d311f55be71dff61a3cb599a03fa2a2415135c161d736f97b4`;
report SHA-256 is
`2c4ccba4679560c26e7c2ef2e1cc0785baba5892e22d930613b0fae1f809c449`.
This is a local verified result; nothing has been committed or published.
