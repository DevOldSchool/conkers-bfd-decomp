# US native asset directories

Eighteen outer and inner asset directories regenerate **13,432 bytes** from
1,679 typed records. This is directory reconstruction only: unknown payloads,
alignment gaps and unused bank tails receive no new matching credit.

## Native contract

The indexed loader `func_1502AC88` uses eight-byte records containing a relative
offset and a packed size/flags word. The stored size occupies the low 28 bits;
the high four bits are retained as flags. `func_1502B5C8` starts at ROM
`0xAB1950` and traverses the requested bank/entry indices. The first relative
offset establishes the directory length. Empty slots remain explicit records.
Nonempty payload extents must be ordered, disjoint and after the directory.
See the [independent loader analysis](../assets/models/us_asset_inventory.md).

Both complete consumer spans are pinned: 636 bytes at `0x1502AC88` with SHA-1
`24f02469c9605e212ed65a4c75b216d50ef8577e`, and 244 bytes at `0x1502B5C8`
with SHA-1 `9c411ce6bf78e69583215fa8484bfd0f137edc72`. The owned US ROM is
checked against SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

## Selected directories

| Directory | Records | Rebuilt bytes |
| --- | ---: | ---: |
| Outer bank index | 30 | 240 |
| Bank 01 | 187 | 1,496 |
| Bank 02 | 187 | 1,496 |
| Bank 03 | 114 | 912 |
| Bank 04 | 69 | 552 |
| Bank 09 | 483 | 3,864 |
| Bank 07 | 1 | 8 |
| Bank 08 | 5 | 40 |
| Bank 0B | 69 | 552 |
| Bank 0D | 7 | 56 |
| Bank 0E | 69 | 552 |
| Bank 11 | 187 | 1,496 |
| Bank 12 | 187 | 1,496 |
| Bank 15 | 69 | 552 |
| Bank 18 | 1 | 8 |
| Bank 1A | 5 | 40 |
| Bank 1B | 4 | 32 |
| Bank 1C | 5 | 40 |

These directories occupy canonical raw linker objects. Directories within other
reconstructed families remain with their existing builders and are outside this
batch. The model directory objects contain only the header; the other selected
bank objects retain backing for their unproved payloads.

## Editable inputs and proof

`./conker asset-directories build` creates `directory.json`, a checked manifest
and explicit `backing.bin` under `build/assets/asset-directories/us/<key>/`.
The encoder accepts only named integer fields with native width checks; there
is no raw-byte override. Make links the generated canonical asset objects.
Native objdiff checks the entire actual linked object and credits only its
freshly encoded directory prefix. Preserved backing is never a credited source.

Changed or missing source files fail without being overwritten. Explicit
`./conker asset-directories recover --part <key>` backs up the current folder
before restoring reviewed inputs. Builds recheck source hashes before publishing
the group. Receipts bind sources, encoder dependencies, ranges and output bytes.

An independent ROM reader checked all **5,037 fields**. All **1,679 flag
mutations** changed exactly the selected high-bit field; all four full-consumer
endpoint mutations were rejected. Seven focused tests cover strict native
widths, empty slots, invalid extents, source preservation, explicit recovery,
source races and the boundary between credited directory bytes and backing.

## Accepted batch

`./conker build --assets` reproduced the complete 67,108,864-byte US ROM with
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a` in 201 seconds including
setup and Docker. All 2,893 Docker tests passed in 202.142 seconds (eight
existing skips). Native objdiff, progress and whitespace checks passed.

Matched Data increased by exactly 13,432 bytes to **63,045,344 / 65,120,512
(96.81335%)**. Complete Data increased by the same amount. Code measures and
both denominators are unchanged. All 26,064 prior source hashes are preserved;
only the corresponding raw-storage remainders shrink. The 240-byte raw bank
index unit is replaced completely, and 18 reconstructed directory units appear.

Tested base: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus uncommitted changes.
Source fingerprint:
`695398ad0ae87a5939bd89c5fecb260e63e2788aba143da61013eca26ad946f4`.
Report SHA-256:
`c7f3dc3e06383f503c7bc9476582cfc5dde8e576c5fc48016cc54b94faea9e21`.
