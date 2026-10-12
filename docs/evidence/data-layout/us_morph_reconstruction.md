# Complete US character morph bank reconstruction

Bank `0x13`, ROM `0x1300188..0x1304F00`, now reconstructs all **19,832 stored
bytes** from editable signed XYZ endpoints. This includes the outer two-entry
index, six nested part tables, 69 freshly compressed leaves and every alignment
byte. The original bank is an independent comparison target; no original
compressed bytes are used as encoder input.

## Native contract

The [existing morph consumer evidence](../assets/models/us_character_morph_targets.md)
establishes four complete native code spans and the two-record selector at
`0x800A7230`. The selector supplies model ID, shape count and three vertex
counts. Each model's native header supplies the corresponding starting vertex
indices. The existing independent decoder checks those ranges and proves
shape zero equals the original model geometry.

| Character | Shapes | Part vertex counts | First vertex indices |
| --- | ---: | --- | --- |
| 0 | 16 | 337, 12, 12 | 496, 833, 901 |
| 58 | 7 | 109, 25, 24 | 199, 308, 333 |

The editable source stores 6,882 XYZ positions, grouped by character, shape
and part. The encoder validates signed-halfword coordinates and the native
selector/boundary contract. Each leaf is padded with zeros to sixteen bytes
and freshly encoded with raw DEFLATE level 9 plus its native decoded-length
word. Eight-byte pair tables derive child offsets and lengths, compression
flags and the terminal-child flag. All inter-child and final alignment is
explicitly generated as zero bytes. Both original entry payloads (15,848 and
3,968 bytes) and the complete bank compare exactly.

## Build and independent checks

`./conker model-assets build-morphs` initializes editable `morphs.json` and a
manifest under `build/assets/morph-build/us/`. Subsequent builds regenerate
all compression and table structure from these inputs, recheck source hashes
and independently compare original ROM bytes. Missing, malformed or edited
inputs are preserved and fail the build. `./conker model-assets recover-morphs`
backs up the input directory before restoring reviewed endpoint records.

The existing ROM linker object `asset_bank_13.o` now comes from the reconstructed
part for `ASSETS=1`. Native objdiff compares that actual object with fresh
endpoint encoding and an independent ROM target. Whole-bank credit replaces
the same-sized unreconstructed storage region; decoded leaves add no duplicate
Data allocation.

[Machine-readable evidence](us_morph_reconstruction.json) records all 69 leaves
and 41,792 decoded bytes independently checked, 414 first/last XYZ component
mutations, and ten code/selector endpoint mutations. Tests also cover typed
field errors, source preservation and recovery, Make invalidation, and stale
report objects.

## Completed integration acceptance

The uncommitted worktree based on 094102644c4c2f5aefaa0fc4b609416918f66f58
passed the full asset build: all 67,108,864 ROM bytes equal the original US
SHA-1 4cbadd3c4e0729dec46af64ad018050eada4f47a. The Docker suite passed
2,501 tests with eight skips. Progress and whitespace checks passed.

The native report adds exactly 19,832 matched and complete Data bytes:
**37,098,874 / 65,120,512 matched (56.969566%)**, with 37,098,106 complete.
Code and the Data denominator remain unchanged. The complete morph unit replaces
its former raw-storage unit; all other unit measures and all 10,168 previous
reconstructed asset proofs are unchanged. All 24,140 prior editable-source
file hashes were preserved.

Input fingerprint:
8297b7e9cf27823f459358b607a4b5aea88752cc40a2282c2bb725c4862d7d2c.
Native report SHA-256:
4d7654966f8fc0deff5873e5bbf260787f440bc63fe8959d2948fc11ab1f9b6b.
This is local verified progress; nothing has been committed or published.
