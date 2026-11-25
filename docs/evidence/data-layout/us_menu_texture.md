# US menu tables and CPU texture descriptors

Six data definitions reconstruct 2,576 bytes. They are INFO verification
definitions: the original archive supplies runtime data, and source-unit
completion remains separate. Functions, shared headers and assembly are unchanged.

| Definition | Address | Bytes | Extent evidence |
| --- | --- | ---: | --- |
| Digit columns | `8009006C` | 4 | Native index masked to two bits |
| Primary menu resources | `800900BC` | 24 | Native selection-five producer |
| Secondary menu resources | `800900D8` | 32 | Native selection-four producer; eight words to the next object |
| Rotating menu resources | `800900FC` | 20 | Initialized modulo-five selector and seven-step draw loop |
| CPU texture descriptors | `80090B60` | 2,484 | Explicit selector 188, native stride twelve; 207 records to `80091514` |
| Additional fragment scales | `800A18CC` | 12 | Literal count three and indexed float consumer |

## Texture descriptors

`func_151D1C98` supplies descriptor address `80091430` and selector `0xBC`
(188) to `func_15142E24`. It stores that selector in argument slot `+0x18`,
sets frame zero and mode zero, and retains the direct descriptor address.
`func_15142E24` forwards the selector to `func_1514306C`. With mode zero,
that helper takes its default arm, computes the selector times twelve,
loads the word at `80090B60 + selector * 12`, and indexes its frame words.
This proves the record layout and reach through entry 188. Entries 189
through 206 follow with the same layout, each pointing at the next word of
`D_80090818`, and end at the independently consumed resource word at
`80091514`. The table is therefore declared with all 207 records; no native
selector for entries 189 through 206 is claimed.

The drawing path forwards the original descriptor pointer through
`func_15094FE8` to `func_15095060`. The latter reads the first word, compares
it with `0x10000000`, and either uses a scalar resource identifier or reads
an indexed word through the address. It also reads unsigned byte `+4`,
unsigned halfwords `+6` and `+8`, and unsigned bytes `+A` and `+B`.
The downstream renderer uses the halfwords as dimensions and the final
bytes as format and texel size. The byte at `+4` is retained as
`frameParameter`; this reconstruction does not assume that it bounds every
caller's frame index.

The source uses a four-byte union for the scalar/address word. Its initializers
retain genuine symbolic addresses; the two small stored values, 1844 and zero,
are scalar encodings under the native threshold test and generate no pointer
relocations. The union's first member is used for C89-compatible initialization;
no code in this data-only unit dereferences those initializers. There are 187
real pointer fields targeting 186 distinct addresses. External declarations
gave those destinations names without claiming storage or array lengths in this
batch. The subsequent [frame-storage reconstruction](us_cpu_texture_frames.md)
replaces those declarations with shared arrays and explicit element offsets;
all original pointer destinations are preserved.

Natural alignment between the byte at `+4` and halfword at `+6` emits one
padding byte. All 189 original padding bytes are checked zero. The resulting
record stride is twelve; the compiler's four final alignment bytes are excluded.
Complete registered spans for the producer, wrapper, selector, loader and
renderer are authenticated against the original ROM, including raw assembly
where available. The complete layout and instruction anchors are recorded in
the accompanying JSON.

## Menu selectors and scales

`func_151DE85C` writes mode zero and selection five through `D_8008FDD4`.
`func_151EC3E8` admits that mode and indexes `800900BC` using the selection
byte times four, establishing all six words. Separately,
`func_151EC648` explicitly writes four to `D_800900F8`, later loads that
byte, and indexes `800900D8`. That proves entries zero through four; three
further resource words follow before the next object and are included.

`func_151E5034` initializes menu byte `+0x41` to zero. On the selection-four
path, `func_151E0424` reads five from original count byte `8008FE9F`, applies
single-step input changes, and wraps the selector into 0..4. The rendering
path in `func_151EC648` requires selection four, subtracts four from the
selector, corrects a negative result by five, and draws seven successive
entries with wrap at five. Every initialized selector visits all five
entries of `800900FC`; arithmetic checks supplement the native instructions.
This is an initialized native-state proof, not a bound for arbitrary corrupted
menu state or a claim that all paths have been observed at runtime.

`func_151E89A0` masks the digit-column lookup index with three and reads a
byte from `8009006C`. The adjacent digit-row table remains unclaimed because
its incoming score bound has not been established here.

`func_150F1D10` passes `800A18CC` and literal count three to `func_1515080C`.
The latter retains the pointer, selects an ordinal within the supplied count,
indexes by four and loads a float scale. This establishes three float words,
matching the earlier three-selector list at `800A18C0`.

## Validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted work.
Independent pinned-compiler pilots match all 2,348 payload bytes and 187
symbolic pointers. Fifty-two compiler tail bytes are excluded. All 820 prior
GAME objects retain their allocated bytes, symbols and relocations; the full
2,072,880-byte GAME code image is unchanged. All 2,722 deliberately corrupted
byte/pointer candidates were rejected, as were 2,348 independent ROM-byte mutations.

`./conker test`: 3,033 tests passed, with eight skips (217.574 seconds).
`./conker build --assets`: passed (147 seconds wall time); the complete
67,108,864-byte US ROM matches SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The full report and acceptance audit passed with no compilation errors:
63,324,795 / 65,120,512 matched data bytes, a gain of 2,348; 1,795,717 remain.
Complete data, code and function measures are unchanged. All 27,301 prior asset
input hashes and 11,836 asset object hashes are preserved. Report SHA-256:
`b552433a2ad7e47594655d53529853957fc300389974a42ec52d94cc0b52403e`.
Source fingerprint:
`617d6edcfd0afd4a4d55ad143597fd12248964d80fbc3636b7fcaebb5d445b40`.
Preparation took 374.2 seconds; report and validation took 27.9 seconds.

Temporary native evidence and independent references are under
`build/us/data-completion/menu-scale-*`, `cpu-descriptor-*` and `menu-texture-*`.
Original object boundaries and runtime activation remain separate from this
stored-data reconstruction.
