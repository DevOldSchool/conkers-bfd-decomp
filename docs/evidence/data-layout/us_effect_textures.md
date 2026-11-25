# US effect texture roots, descriptors and frame lists

This reconstruction defines 1,316 bytes: the 70-entry pointer table at
`8008CA4C`, 63 distinct twelve-byte descriptors, and 280 bytes of frame words.
Five null slots and two repeated descriptor references retain their original
values. Twenty-one contiguous descriptor groups and fourteen frame groups
preserve shared storage and use explicit element pointers. Grouping does not
establish original compiler object boundaries. These INFO definitions verify
source reconstruction while the original archive supplies runtime data.

## Table extent and descriptor layout

The full 76-byte native `func_1502C3BC` reads an unsigned selector byte from
`800CC406 + actor * 0x32C`, retains values below 70, and substitutes eleven for
all larger values. Its caller `func_1502C408` carries the returned byte to the
four-byte indexed load from `8008CA4C` and passes the selected descriptor to
`func_15094F70`. The table extent therefore comes from an explicit native
predicate, independently of the neighbouring callback words.

A bounded interpreter executes the original selector instructions for every
byte value at three actor indices: 768 cases. The output domain is exactly
0..69. This demonstrates the selector rule, not gameplay activation of every
slot. Null entries remain null and are not treated as valid descriptor storage.

`func_15094F70` forwards its descriptor to `func_15095060`. The latter reads the
first word as either a resource identifier or a frame-list pointer using the
unsigned `0x10000000` threshold. It reads byte `+4`, halfwords `+6` and `+8`,
and bytes `+A` and `+B`; the upload consumer uses the dimensions, format and
texel size. The natural alignment byte `+5` is zero in all 63 records.
C89-compatible union initialization preserves the 45 scalar encodings and
18 actual frame pointers without inventing relocations for scalar resource IDs.

## Frame extents and shared storage

Original effect-type record 14 pairs updater `func_15168870` with renderer
`func_150A6860`. The updater reads object selector `+B0`, uses the pointer table,
reads descriptor byte `+4` and computes `(count << 8) - 1`. Its normal positive
wrap subtracts that boundary until the phase is within it. The renderer's
working pointer is object `+10`, so its selector `+A0` and phase `+88` are the
same object fields `+B0` and `+98`. It forwards the descriptor and phase through
`func_15094F70`; `func_15095060` uses `phase >> 8` to select a four-byte frame word.

The original positive counts are 1, 2, 5, 10 and 12. Their pointer/count spans
form fourteen frame groups totalling 280 bytes, with shared words retained
once. Other flags and negative phases are outside this bounded argument;
there is no universal safety or runtime activation claim. Original function
spans, instruction anchors, table pointers, descriptor values and frame spans
are recorded in the accompanying JSON. All proposed storage is unassigned in
the previous accepted inventory, and none overlaps the prior frame-list batch.

## Validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted work.
Thirty-six pinned-compiler source owners match 1,316 bytes and 83 symbolic
pointer fields against an independent full-ROM reference. The 252 compiler
tail bytes are excluded. All 833 prior GAME objects preserve their allocated
bytes, symbols and relocations; all 2,072,880 GAME code bytes are unchanged.
All 1,482 byte/pointer corruption cases were rejected, along with 1,316
independent ROM-byte mutations.

`./conker test` passed its 3,033-test suite with eight skips in 218.419 seconds.
`./conker build --assets` passed in 149 seconds wall time. Independent extraction
reproduces the entire 67,108,864-byte US ROM with SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The full report and acceptance audit passed with zero compilation errors:
63,327,043 / 65,120,512 matched data bytes, a gain of 1,316; 1,793,469 remain.
Complete data, code and function measures are unchanged. All 27,301 prior asset
input hashes and 11,836 asset object hashes are preserved. Report SHA-256:
`7ae43627a2d7873917258e7147c56bedd1e24b48c18ccc41f51b451dc5957f29`.
Source fingerprint:
`c3d0eb86df153607c084b67f15cf691609cd3509d720c47852c08843aff93554`.
Preparation took 378.2 seconds; report and validation took 24.8 seconds.

Temporary pilots and audit scripts are under
`build/us/data-completion/effect-textures-*`.
