# US resource descriptors, dependency lists and names

This reconstruction follows the independently reviewed [resource dependency
consumer family](../boundaries/game/families/game_raw_resource_dependency_core.md).
The complete `1509CA10..1509D180` code span is 1,904 bytes, SHA-1
`7f80b6659725e30b32eccb9ea7adcf84cb2ad5d9`, rechecked against the normalized US
ROM `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The consumers establish 204 records of 20 bytes at `80087430..80088420`:
nullable name pointer, packed ID, two unsigned halfwords, and two independent
pointers to halfword descriptor-index lists terminated by `FFFF`. The table
SHA-1 is `378e173d56925ab4b894d91f963d7eb2687a904e`. No new meaning is assigned
to the two raw halfword fields or to unrecognized packed-ID bits.

The table points to 116 distinct NUL-terminated ASCII task/scene labels and 179
distinct dependency lists. All non-terminator list indices are below 204.
Repeated pointers retain their exact shared destinations; unnamed descriptors
remain null. Existing function bodies, declarations and function inventories
are unchanged. The new source-local record type matches the existing consumer
layout in `src/game/game_C9EC0.c`.

## Storage and reconstruction ownership

These are new data-only reconstruction owners, not historical C-object or
function-source-unit boundary claims. The descriptor initializer uses symbolic
references to the separately defined names and lists. Names use C strings;
lists use typed `u16` values and explicit terminators. The compiler generates
minimal four-byte alignment between these declared objects.

| Source basename | Native range | Payload bytes | Input section |
| --- | --- | ---: | --- |
| `resource_descriptors.c` | `80087430..80088420` | 4,080 | `.data` |
| `resource_dependencies_0.c` | `8009E470..8009E5F0` | 384 | `.rodata` |
| `resource_dependencies_1.c` | `8009E5F4..8009E614` | 32 | `.rodata` |
| `resource_dependencies_2.c` | `8009E618..8009E834` | 540 | `.rodata` |
| `resource_names.c` | `8009E834..8009F0C4` | 2,192 | `.rodata` |

The list payloads contain 890 semantic bytes and 66 alignment bytes. Names
contain 2,018 semantic bytes, 173 internal alignment bytes and one final
word-alignment byte. The third list object emits another four bytes to reach
16-byte section alignment; those compiler-tail bytes are excluded from credit.

Two four-byte gaps, `8009E5F0..8009E5F4` and `8009E614..8009E618`, contain
`003E FFFF` but have no pointer from this descriptor table. Their ownership is
not established here; they remain unassigned. No arbitrary filler initializer
bridges either gap.

The GAME linker places each actual compiled section in its independently
addressed INFO section and verifies its linked payload against the US ROM.
The original GAME archive remains runtime backing, so this work can add
matched data but cannot add complete data. Accepted credit is 7,228 bytes.

## Independent reference typing

`config/relocs/game-data-us.txt` identifies exactly the two scalar words at
record offsets `+4` and `+8`, for all 204 records. Its coordinates belong to
the combined decoded GAME code+data reference buffer, where the table starts
at `0x1FEA40`; they are not physical-ROM offsets. Splat's supported `MIPS_NONE`
declaration retains each original numeric word rather than misclassifying
packed IDs as pointers. The three pointer fields remain symbolic. Only the
GAME data-reference configuration loads this file; standalone code and other
overlays do not. A regression test checks every declared offset and excludes
all pointer fields.

String symbols have exact unsigned-byte extents, including their terminator.
This lets the canonical disassembler distinguish trailing alignment from the
last string's symbol size. The C definitions remain ordinary string literals.
An isolated native pilot matched all five sections after these reference-type
corrections, without changing any candidate object or assembly bytes.

## Acceptance

Verified on working-tree changes based on
`38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`. The [machine evidence](us_resource_descriptors.json)
records source/object hashes, exact pointer verification and report preservation.

- GAME integration verifies all 2,072,880 code bytes and all five resource
  payloads against the US ROM. The source audit checks every defined symbol's
  extent and every one of the 524 symbolic pointer relocations. The complete
  consumer span is checked independently; both tested endpoint mutations fail.
- The reference audit confirms identical scalar bytes and pointer destinations
  between the independently disassembled references and the compiled C objects.
  Pointer-bearing fields retain all 524 relocations; 408 scalar words are
  explicitly classified as non-relocations.
- Focused host checks: 31 tests passed, two skipped. Full Docker suite:
  2,941 tests passed, eight skipped, 174.219 seconds.
- `./conker build --assets`: complete 67,108,864-byte US ROM is byte-identical,
  35 seconds including setup, SDK and Docker.
- Final native report: 283.7 seconds preparation, 23.9 seconds report/validation,
  zero compile errors. Progress and whitespace checks pass; snapshot is current.

Matched data rises from 63,115,860 to **63,123,088 / 65,120,512 bytes
(96.932724%)**. Complete data stays at 63,079,392. All 26,809 prior editable
asset-input hashes are preserved; code/function metrics and every other
existing unit's measures remain unchanged except the two repartitioned raw
storage ranges. Five new source owners account for exactly the documented
7,228 bytes. **1,997,424 bytes remain unmatched.**

Native report SHA-256:
`56ba48b7366c78936961f12b465920b4234d1bc894c9fb1a384b9d0fb6d3f00a`.
Input fingerprint:
`083e760cdc9680a8badc431d12d7b0c0139c4299f8ba6e08047906790c072ca1`.
