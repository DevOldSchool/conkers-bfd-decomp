# US MP3 directory and alignment reconstruction

Bank `16` contributes **5,151 newly reconstructed bytes**: its 462 eight-byte
index records (3,696 bytes) and 368 minimal alignment spans (1,455 bytes).
Encoded stream payloads are outside this family; their existing spectral and
metadata proofs remain separate.

## Proven storage rules

The [native asset directory contract](us_asset_directory_reconstruction.md)
applies to this index: each record has a 32-bit relative offset, 28-bit stored
size and four flags. Both complete loader spans, `1502AC88` (636 bytes) and
`1502B5C8` (244 bytes), are checked against the same pinned US hashes.

The independently reviewed [MP3 bank partition](us_mp3_bank_build.md) contains
453 nonempty streams and nine explicit empty slots. Every stream begins at an
eight-byte ROM boundary. Each gap has exactly the 1..7 zero bytes needed to
reach that boundary; the last stream ends at the bank end. The new encoder
derives those lengths from the typed index and emits fresh zeros. It does not
copy the old padding files to generate the candidate.

The index source retains the explicit empty slots and terminal flag. It does
not resize streams, reinterpret MP3 frame bytes, or classify unknown audio
tails as padding. Overlaps, nonminimal gaps, unsupported compression flags,
unaccounted streams and unexpected final storage are rejected.

## Inputs and actual link objects

`./conker mp3-assets build-bank` and the full asset build initialize a separate
`layout/` child under `build/assets/mp3-bank/us/`, containing a checked manifest
and editable `index.json`. All 822 preexisting bank inputs are preserved and
still checked. In particular, edited streams retain the existing build
behavior; layout reconstruction does not silently restore them.

Existing invalid or missing child files fail without overwrite. Explicit
`./conker mp3-assets recover-layout` backs up only the layout child before
restoring it. Make tracks edits and deletions of both child files. The old
padding files remain checked provenance, while the output uses newly generated
alignment bytes.

The report compares the actual `audio/mp3/index.o` and 368
`audio/mp3/padding/<offset>.o` linker inputs with fresh semantic output and
independent ROM bytes. All 369 extents are disjoint from the stream units.
There is no synthetic combined candidate or credit for copied encoded audio.

## Validation

An independent reader checked all 1,386 index fields. Field mutations changed
only the selected record in 1,208 cases; the other 178 were rejected by extent
or width checks. All four loader endpoint mutations were rejected. Fresh
packing reproduced the complete 23,586,160-byte bank and preserved all 822
existing input hashes, adding exactly two source files.

Six focused tests cover sparse slots, flags, fresh alignment, invalid extents,
source edits and preservation, explicit recovery, source races and actual
linked-object comparisons. The existing 12 bank tests pass. A real Makefile
test verifies layout edits and missing files reach the bank builder.

The full Docker suite passed **2,933 tests** (eight skipped), followed by
`./conker build --assets`: all 67,108,864 US ROM bytes remain identical. The
native report has zero compile errors and confirms exactly 369 new units and
5,151 matched and complete data bytes. All 26,436 previously recorded source
hashes are unchanged. The 371 newly reported hashes comprise the two new child
files and 369 existing bank provenance files.

Data matching is **63,097,229 / 65,120,512 bytes (96.89302%)**, leaving
2,023,283 bytes unmatched. Complete data is 63,076,285 bytes. Code totals and
all existing unit measures are unchanged except for the MP3 unreconstructed
remainder, which falls from 369,813 to 364,662 bytes.

Tested base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, with local
uncommitted changes. The accepted report and source fingerprint are recorded
in [the machine-readable evidence](us_mp3_layout.json).
