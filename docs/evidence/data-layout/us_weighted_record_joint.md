# US weighted-selection record

The 28-byte record at `800A2504` contains six `f32` weights and their `f32`
total. This reconstruction uses the existing declaration in `game_1368C0.c`:
`extern struct { f32 weights[6]; f32 total; } D_800A2504;`.

The native consumers and exact-rational selector witnesses are documented in
[weighted vectors](us_weighted_vectors.md). Both selectors load
the total at offset 24, then compare and subtract weights from offset zero.
Witnesses for indices zero through five establish reads of all six weights.
The five complete native instruction spans and instruction anchors were checked
again against the original ROM before this joint-owner experiment.

The former four-byte verification owner for `D_800A251C` is retired. The new
definition owns all 28 bytes, including that previously matched total, so the
net addition is 24 bytes. `D_800A251C` remains an interior address alias. This
avoids overlapping owners or shortening a 28-byte candidate symbol to claim
only 24 bytes. No comparison or padding gate is changed.

This is an INFO verification definition. Runtime storage still comes from the
original GAME archive. The compiler emits 32 bytes; four zero compiler-tail
bytes are excluded. Original source-object boundaries, runtime immutability,
PRNG-state reachability and gameplay activation are not asserted. The upward
rounding edge case described in the prefix evidence remains applicable.

## Validation

Tested base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted
work. The independent full-GAME reference and scratch native comparison match
28/28 bytes. All 28 scratch one-byte corruptions are rejected. The integrated
GAME build passes. All 1,937 unretired GAME objects preserve their allocated
bytes, symbols and relocations; the complete 2,072,880-byte GAME code image is
unchanged. The actual linked record matches 28/28 bytes, and all 28 native-byte
and 28 independent ROM-byte corruptions are rejected.

The regression suite passes 3,038 tests with eight skips. The asset build passes,
and independent extraction from the linked ELF reproduces the entire original
67,108,864-byte ROM. Progress and whitespace checks pass. The final report audit preserves all
27,323 prior asset source hashes and 11,847 asset object hashes, as well as every
other report unit's measures. The old unmatched 24-byte range and separate
four-byte total are replaced by exactly one 28-byte matching owner.

The accepted report credits 63,341,905 / 65,120,512 data bytes, leaving 1,778,607.
Complete-data and code/function measures are unchanged. Report SHA-256:
`c08583d4628b3be8d205ee8203da11ef6727a0e0d800f47c65cba875cadf7d02`.
