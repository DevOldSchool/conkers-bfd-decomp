# US bounded animation clip reconstruction

Four bank-02 containers still contain an unexplained clip each. This batch
reconstructs their other 117 complete descriptor/frame pairs, covering
219,664 physical ROM bytes. It does not classify the four whole containers
as reconstructed. [Machine-readable evidence](us_partial_animation_clips.json)
records the exact physical ranges, native dependencies and independent audit.

| Actual linker object | Container entries | Rebuilt clips | Credited bytes | Object bytes |
| --- | --- | ---: | ---: | ---: |
| models/raw/00D3CBA0 | 82, 83 | 49 | 49,728 | 52,624 |
| models/raw/00E86CF8 | 124 | 42 | 40,296 | 44,392 |
| models/raw/00EEC120 | 146 | 26 | 129,640 | 171,216 |

The selected clips use the same typed descriptor/channel codec and native
pose checks as the [complete animation containers](us_single_pair_animations.md).
The selection excludes pair 0 of entry 82, pair 18 of entry 83, pair 36 of
entry 124 and pair 21 of entry 146. Their truncated descriptor, unexplained
frame fields or duration tails remain raw. Container directories and all
other backing bytes also remain uncredited: 48,568 bytes across these three
objects. No opaque fields or encoded-token recipes enter the semantic source.

## Character 146 runtime routing

Most clips use the descriptor/default duration. Entry 146 pairs 18, 19 and
20 require the runtime durations 533, 270 and 264. func_1503D660 resolves the
character through func_1503D5F0, loads bank 0F and passes its route table to
func_1503D484. func_1505E650 indexes eight-byte logical-animation records;
the first halfword selects an even descriptor segment. It passes the logical
index to func_1505E0C4, which stores it at actor + 0x84. For character 0x92
and descriptor duration 255, the latter reads an unsigned halfword from
0x800993F8 + logical_index * 2.

The three selected pairs map to logical indices 20, 21 and 22. The builder
checks the complete native functions, the five representative-group counts,
pointers and member arrays, and all three duration halfwords. It parses the
original route table, rejects absent/out-of-range routes, and requires every
alias for a clip to agree on duration. The unexplained tail of pair 21 stays
excluded even though its logical route and duration are known. Route and
runtime-table evidence receives no new Data credit.

## Sources, build and report bounds

Run ./conker animation-clips build. Each object has editable clips.json,
a checked manifest and backing.bin under build/assets/animation-clips/us.
The source lists only selected entry/pair IDs and typed channel records;
runtime duration comes from the independently reviewed manifest. Packing
freshly generates each descriptor and frame stream, checks each exact extent,
overlays only those ranges, then compares the complete object to the original
ROM. Missing, edited, invalid or concurrently changing sources fail without
replacement. Explicit recover --part ID backs up the complete old directory.

Make substitutes these three actual raw-path linker objects with generated
objects. Other raw parts keep their existing build path. The unchanged two
objects retain their timestamps when only one semantic source changes; missing
parts regenerate, while missing required input files fail. Native objdiff
rebuilds and reads the actual linker objects, checks every byte against current
semantic/backing inputs, and extracts only the freshly regenerated physical
ranges into bounded comparison units. The remaining storage stays in the
raw bank-02 denominator.

Five focused builder/report tests, all 27 report tests and all 35 Make tests
pass. The Make suite takes 41.241 seconds and exercises all nine required
source files. The independent audit decodes all 3,001 frames and checks 418
endpoint channel mutations. All 22 native code-span endpoint mutations and
20 runtime-table endpoint mutations fail their guards. The complete three
objects are exact and all 26,037 prior unique source hashes are unchanged.
Full acceptance passed: the 67,108,864-byte ROM retains SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`; all 2,571 tests pass (8 skips).
Native objdiff reports 61,958,067 / 65,120,512 matched Data bytes (95.14371%),
with unchanged Code measures, zero compile errors and a current snapshot.
All 10,676 prior asset proofs and 26,037 unique source hashes are unchanged.
Progress and whitespace gates pass. See the accompanying JSON for the
source fingerprint and report digest.
