# US bank 0A native-format animations

The 29 entries in bank 0A contain 608 descriptor/frame-stream pairs. All
268,232 payload bytes are reconstructed from typed animation records, including
13,531 source frames. The outer 232-byte bank directory stays in raw backing
and receives no new credit. The machine-readable inventory and independent
checks are in [us_animation_bank_0a.json](us_animation_bank_0a.json).

## Format evidence and its limits

The entries use the same eight-byte paired-segment directory and packed
animation format already established for bank 02. Every entry has contiguous,
eight-byte-aligned segments, an even nonzero segment count, known size flags,
and a final marker on only its last segment. No segment leaves uncovered bytes.
The encoder derives directory offsets and size/final words from fresh descriptor
and channel output.

The full native readers func_1502AF04 (284 bytes), func_1502B110 (276 bytes),
func_150A81D0 (4,876 bytes) and func_1502D824 (764 bytes) are checksum-pinned.
They establish segment relocation, descriptor masks and optional words, joint
translation channels, packed root/rotation/scale channels and the duration/
keyframe interval rule. These are format consumers; a bank-0A runtime owner
has not been confirmed. Bounded immediate-argument callsite searches found no
bank-0A loader call. This does not prove the bank unused, and the reconstruction
does not assign its entries to scenes, actors or animation names.

Every selected descriptor supplies its own duration. No duration byte is 255,
so no unknown runtime replacement or bank-02 character routing assumption is
needed. Frame strides have no unexplained bytes, packed alignment bits are zero,
and descriptor/stream alignment is at most seven zero bytes. Any runtime-duration
source or opaque tail is rejected. This is exact format reconstruction, not a
claim that these entries are reached during gameplay.

## Editable sources and build integration

`./conker animation-bank build` initializes ignored sources under
`build/assets/animation-bank/us/bank0A/`: `manifest.json`, `backing.bin` and
`animations.json`. Subsequent builds read those saved sources, freshly encode
all 29 entries, verify each independent ROM hash and compose the actual
`asset_bank_0a.o` link input. The unchanged outer directory is copied only as
uncredited backing. Missing or edited inputs fail without being overwritten;
`./conker animation-bank recover --bank 0A` explicitly backs them up first.

The native report takes only the rebuilt payload ranges from that actual link
object. It compares them with fresh semantic output and independent ROM bytes,
checks source and linked-object hashes before/after preparation, and leaves the
outer directory in `assets/storage/bank0A/unreconstructed`.

## Independent verification

All 13,531 frames agree with the separate native pose decoder for joint
translations, roots, encoded rotations and scales. There are 1,415 successful
semantic endpoint mutations across the clips and eight rejected full-consumer
endpoint mutations. All prior editable-source hashes remain unchanged.
The complete 268,464-byte bank matches SHA-256
`aa2d4abe505b9307fb6f8725d89752055aca36861f4e101ea46ceb08d94939a6`.

Focused tests cover saved source preservation, explicit recovery, source races,
unknown runtime-duration rejection, valid channel edits, actual linked-object
credit and Make rebuilds after edits or deleted outputs/inputs. Full ROM, Docker
suite, native report, progress and whitespace acceptance are pending below.

## Accepted checkpoint

The full US asset build reproduced all 67,108,864 ROM bytes in 111 seconds.
All 2,599 Docker tests passed in 132.602 seconds, with eight existing skips.
Native objdiff, progress and whitespace checks passed. Matched Data is
62,476,001 / 65,120,512 (95.93905%), up 268,232 bytes; code and denominators
are unchanged. All 10,681 prior asset proofs and 26,052 unique input hashes
are unchanged. The report is local and has not been published.

Tested base commit: 094102644c4c2f5aefaa0fc4b609416918f66f58 plus uncommitted sources.
Source fingerprint: 4dd45225d0ff0b885be56295a218f6306b0a6c03242383a1e83abedc58fdaf39.
Report SHA-256: 3df3c91623c3dfbd8172c33aed85e02f6e669e6b67f5645ab34134421a7ad1f2.
