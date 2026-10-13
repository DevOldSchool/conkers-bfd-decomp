# US single-pair animation reconstruction

This extension adds 22 bank-02 animation containers, covering 30,712 uncompressed
bytes. The selected bank now has 141 complete containers, 2,561 clips and
3,782,968 stored bytes. The original 119 containers and their editable source
files remain byte-identical. The machine-readable audit is
[us_single_pair_animations.json](us_single_pair_animations.json).

## Native paired layout

The previous animation builder reused the bank-04 scene parser, whose minimum
is four segments. Bank-02 animation containers also have a valid two-segment
case: one descriptor followed by one frame stream. func_1505E0C4 requests two
records through func_1502AF04 or func_1502B110. The latter walks the bank/entry
indices and forwards the requested record count; the former reads eight-byte
records and relocates their payload-relative addresses. Neither imposes the
scene-specific minimum. Both full function spans are now pinned alongside the
existing animation loader, frame-count and channel-decoder proofs.

The dedicated animation parser requires an even, nonzero segment count, a
16-byte minimum table, contiguous eight-byte-aligned payloads, known size flags,
only the last segment's final flag, and complete coverage. The source contains
semantic descriptors and packed channel values. Offsets, counts and flags are
derived. This does not relax the bank-04 parser or admit opaque storage.

Nineteen added entries use descriptor/default durations: 7, 19, 26, 36, 38,
67, 77, 78, 79, 97, 99, 103, 106, 115, 131, 143, 167, 170 and 171. Together
they cover 5,800 bytes. A zero-stride clip with an empty stream has no stored
source frames; its typed descriptor remains reconstructed.

## Fixed runtime durations

Entries 183, 184 and 185 account for the other 24,912 bytes. Their descriptor
duration byte is 255. At 0x1505E484–0x1505E528, func_1505E0C4 checks that byte
and the actor's character entry; entries 0xB7, 0xB8 and 0xB9 read the float
at 0x8009953C. Its US representation is 44204000, exactly 641.0. The complete
1,420-byte consumer and the four-byte scalar are independently guarded.
No logical-route lookup changes this branch's duration.

These three sources explicitly record character_entry and runtime_duration
under the character-animation-fixed-duration format. Their manifests record
the same native evidence. Packing rejects a different character or duration,
even when it would produce identical bytes. Ordinary sources keep their
previous schema. The native frame rule yields 161, 161 and 321 stored frames,
respectively. Only up to seven zero alignment bytes may follow the frames.

## Exclusions and checks

Four entries remain unselected: 82 has a truncated rotation descriptor in pair
0; 83 has unexplained per-frame storage in pair 18; 124 has a 590-byte tail in
pair 36; and 146 has a 145-byte tail in pair 21 after its route-selected runtime
duration. Their valid sibling clips do not give those whole entries credit.

Eight codec tests and 39 model-builder tests pass. The tests cover one-pair
containers without changing the scene contract, table/flag/offset errors,
channel edits, duration/frame disagreement, scalar guards, input preservation
and the equal-byte/different-runtime-evidence case.

The independent audit decodes all 55,208 selected source frames with the native
pose decoder and compares joint translations, root positions, rotations and
scale channels. It checks 997 semantic endpoint mutations, 12 full-consumer
endpoint mutations and all four duration-scalar bytes. The complete bank
reassembles exactly, with SHA-256
1cefc77132fdf0815c0a3ed57f66fcdc9a8035f9fefa6b70ca28364b0b4f0bb7.
All 25,993 prior unique editable-source hashes are unchanged. Full ROM/native
report acceptance is recorded below.

## Accepted checkpoint

The complete 67,108,864-byte ROM remains identical, SHA-1
4cbadd3c4e0729dec46af64ad018050eada4f47a. The asset build took 113 seconds
including setup. All 2,565 tests pass in 125.661 seconds, with eight existing
skips. An initial stale Make-plan count assertion was updated from 119 to 141;
the complete rerun passed. Native objdiff, progress and whitespace checks pass.
Matched Data is 61,738,403 / 65,120,512 bytes (94.80638%), up 30,712 bytes.
Code measures and denominators are unchanged. All 10,654 preceding asset
proofs and 25,993 unique source hashes are preserved.

Tested base commit: 094102644c4c2f5aefaa0fc4b609416918f66f58 plus the
uncommitted reconstruction sources. Source fingerprint:
b587cc9dfb7934acaf387649423a84aade204ce17abb9af25ec9d38fc47eea97.
Report SHA-256:
eceab33d3a91783e0f5c0c28c605dd4b121aac1cc32be13be0cd6be0df2c6f1a.
