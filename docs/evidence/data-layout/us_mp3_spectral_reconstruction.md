# US MPEG-2 spectral reconstruction

The 453 streams in bank 16 contain 282,715 native MPEG-2 mono frames at
22,050 Hz. `scripts/mp3_spectral_codec.py` reconstructs 280,637 complete
physical frames, totaling **23,165,336 ROM bytes in 10,305 disjoint spans**.
The original encoded stream is not an input to this encoder. The later
[partial-frame extension](us_mp3_partial_frames.md) adds 36,479 bytes from
remaining typed frame fields; its acceptance is recorded separately.

## Native evidence and editable source

The existing four full-span playback, decoder, frame-reader and utility
consumer checks in `mp3_table_codec.py` gate every stream inventory. The
canonical `lib/libultrare/src/libultrare/mp3/decoder.c` supplies the reviewed
Huffman seed books, linbit counts, scalefactor partitions and long-block bands.
The table builder independently proves those books against the ROM's external
decoder tables before streams are interpreted.

`build/assets/mp3-spectral/us/NNNN/stream.json` contains explicit MPEG headers,
side information, scalefactors, signed quantized coefficient pairs and signed
count1 quads. Headers and side information regenerate their native bit fields;
Huffman codes, linbits and signs regenerate every granule's exact declared bit
length. Reservoir positions follow `main_data_begin`, frame size and side-info
length. All 282,715 granules round-trip exactly, including granules stored in
previous physical frames. No encoded hex or opaque byte fields are accepted.
The source manifest records the reviewed original boundaries and seed hash.

## Excluded storage

Conker inserts nine-byte `L:` cue records after copyright-marked frames. Their
six-byte payload remains opaque. Every stream also has an unresolved terminal
reservoir tail and trailing storage. These bytes receive **no reconstruction
credit**. The initial checkpoint selected only whole physical frames ending before the
last reconstructed granule endpoint. The partial-frame extension also selects
typed final headers and complete bytes before the final reservoir bit. Earlier unused reservoir bits are generated as
zero and independently checked against original bytes. Adjacent selected
frames merge into a span; cues leave explicit gaps.

The real ROM linker still needs a whole stream. `mp3_spectral_build.py` overlays
freshly encoded frames onto the existing preserved raw MP3 input only to retain
uncredited holes. It checks the complete stream against the independent ROM.
Changed or missing typed sources and raw backing fail without overwriting the
user's files. `./conker mp3-assets recover-spectral --entry N` backs up and
restores the typed directory; it never overwrites raw MP3 inputs.

## Build and native report

`./conker mp3-assets build-spectral` validates all streams. `ASSETS=1` links
actual `audio/mp3/streams/NNNN.o` objects built from these reconstructed parts.
Make tracks both semantic sources and existing raw backing, and rejects missing
inputs even when an old object exists.

The native report independently checks the actual whole-stream linker object
against current fresh encoding. It concatenates only proved physical slices
from that object into the candidate and the same slices from the original ROM
into the target. Explicit `rom_ranges` record their physical provenance;
`linked_rom_start/end` describe the larger actual object's extent. No cue, incomplete reservoir byte or unproved trailing byte enters a credited
candidate. Storage partitioning rejects overlap,
ambiguous envelopes, invalid bounds and inconsistent sizes. Each proved span
replaces the same raw-storage bytes, preserving the Data denominator.

Focused tests exercise coefficient signs and linbits, native field bounds,
reservoir overlap, source preservation/recovery, stale objects, Make
invalidation and disjoint storage accounting. Full integration results and
independent mutation evidence are recorded below.

[Machine-readable evidence](us_mp3_spectral_reconstruction.json) records each
stream's physical spans and preserved source hashes. All 453 streams passed
three independent in-memory mutations: global gain, a nonzero coefficient's
sign, and a scalefactor. Each of the **1,359 mutations** changed the freshly
encoded credited bytes; all on-disk source hashes remained unchanged. The full
strict codec survey also compared every granule and selected frame with the
independent original bitstream.

## Initial integration acceptance (historical)

The uncommitted worktree based on `094102644c4c2f5aefaa0fc4b609416918f66f58`
passed `./conker build --assets` in 100 seconds including setup and Docker. All
67,108,864 bytes equal the original US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The Docker suite passed 2,512 tests
with eight skips in 116.591 seconds. Progress and whitespace checks passed.

Native objdiff added 453 complete units and exactly **23,165,336 matched and
complete Data bytes**. Matched Data is now **60,264,210 / 65,120,512
(92.54259%)**; complete Data is 60,263,442. Code and the Data denominator remain
unchanged. Only bank-16 unreconstructed storage shrank. All 10,169 prior asset
proofs and all 24,142 unique prior editable-source hashes were preserved.
The 11,637-unit report has no compile errors and its source snapshot is current.

Input fingerprint:
`a91709be831c2e5ccf0ed22c89dce1a51c5d14a2a06b2deff8194bf4b4b561e5`.
Report SHA-256:
`c471ea9541836d626e4d5805641e89a1d5120ad6588e09014e328edbf7f90bf5`.
The independent final audit ran on the host because Docker cannot resolve the
managed worktree's external Git metadata. The full test and asset-build gates
ran in Docker. This is verified local progress; nothing is committed or published.
