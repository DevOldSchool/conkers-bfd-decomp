# US model placements and additional scene parameters

The reconstruction adds **20,942 bytes** through the native 68-byte placement
format shared by bank `0B` and bank `0C`, child 2:

| Owner | Records | Newly reconstructed bytes |
| --- | ---: | ---: |
| 54 compressed bank-0B lists | 727 | 11,233 stored stream bytes |
| Bank-0C child-2 parameters | 511 | 9,709 field bytes |

## Native fields and pointer ownership

`150039E0` requests bank `0B` with path depth two at `15003A50..15003A60`,
then divides the returned size by 68. It also requests bank `0C`, child 2,
with path depth three at `15003A98..15003AAC`. The loop begins with the first
bank's base in `s7`; when it reaches the scene-child records, `15003B80..15003B94`
adjusts the base for the cumulative index. At `15003BA4`, `t0` is the selected
record pointer. The offset advances by 68 at `15004218`.

The [previous scene-model fields](us_scene_model_controls.md) establish 39 bytes
per record: signed position/rotation vectors, float scales, kind/index,
update handler, script selector, state and transform flags. Nine additional
native scalar loads establish another 19 bytes:

| Offset (hex) | Storage | Load | Runtime destination |
| --- | --- | --- | --- |
| `18` | 32-bit value | `15003C4C` | word `3C` |
| `38` | 32-bit value | `15003D08` | word `40` |
| `2C`, `2D` | unsigned bytes | `15004178`, `15004180` | bytes `4C`, `4D` |
| `2E`, `30` | unsigned halfwords | `15004160`, `15004168` | halfwords `50`, `52` |
| `32` | unsigned byte | `15004170` | byte `4F` |
| `3E` | unsigned halfword | `15004154` | halfword `6C` |
| `40` | unsigned halfword | `15004188` | halfword `90` |

Before these loads, the only call on the kind-zero resource-loading path saves
`t0` at `15003E14` and restores it at `15003E20`. The kind-one/two paths retain
it directly. The source labels preserve native offset and width without guessing
callback-specific meanings. The schema is shared; kind-zero static scene models
override some runtime parameters from fixed defaults. No claim is made that each
stored field is read on every path or that every original record is instantiated.

The complete 2,964-byte `150039E0` span and the complete archive-loader spans
`1502B7F0` and `1502AC88` are authenticated before reconstruction.

## Full compressed lists and bounded scene slices

Bank-0B sources combine the previously proved fields with the nine parameters.
Ten remaining lanes (`1C..1F`, `35..37`, `3D`, `42..43`) are constrained to zero;
any nonzero unexplained storage rejects the record. These lanes are not exposed
as raw values or assigned a speculative gameplay meaning. Decoded record arrays
have minimum trailing 16-byte alignment, checked in all 54 original streams.
The native loader's division by 68 excludes that tail from the record count.
Fresh length prefixes and level-six raw DEFLATE reproduce the stored streams.
The 175 bytes between outer entries remain uncredited backing.

For uncompressed bank-0C records, only the nine newly proved fields are encoded.
The ten unexplained bytes per record remain backing. Previously owned fields and
trigger volumes retain their source files, values and ownership ranges.

## Editable inputs and build verification

Each parent gains a separate `model-placements/` child with a checked manifest
and editable `placements.json`:

- `build/assets/asset-directories/us/bank0B/`
- `build/assets/scene-fields/us/`

Parent files are preserved. Both builders compose the new encoded data into the
actual linked bank objects. Each report unit compares only its disjoint owned
ranges after checking the entire linked bank against freshly reconstructed
sources and the independent ROM. Make tracks child edits and deletions.
Malformed, changed, missing or concurrently modified inputs fail without
replacement. Explicit parent recovery backs up the complete directory, including
the new child, before recreating reviewed sources.

## Validation

All 3,000 Docker tests passed (eight skips), including all 50 Make tests.
The 103 focused tests passed (two host skips). Independent source checks covered
22,047 scalar mutations, 7,270 unexplained-lane mutations, 356 alignment-byte
mutations and six native-consumer endpoint mutations. All 20,942 individual
native byte mutations rejected a perfect match.

The full US asset build reproduced all 67,108,864 ROM bytes in 197 seconds
including setup; compile, link and verification took 170.597 seconds. An
independent extraction from the current linked ELF also matched ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The accepted report adds exactly 20,942 matched and complete data bytes:
**63,244,729 / 65,120,512 matched bytes (97.119520%)**, with 1,875,783 remaining.
The 27,255 previous editable source hashes and all 11,829 prior asset-object
hashes are preserved; four new source files were added. Code, function counts
and denominators are unchanged. Only the bank-0B and bank-0C remainder units
shrink, by 11,233 and 9,709 bytes respectively. Native-report, progress and
whitespace gates passed.

Tested base: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus uncommitted changes.
Source fingerprint: `e59a3ac6b79920839b24b49624dd172c48b381133e552304aa3cecd375acddaa`.
Report SHA-256: `9ee925e22bb7912f50f68829936495b0e917b0c7ba3d924ca120c77aacf2bef5`.
