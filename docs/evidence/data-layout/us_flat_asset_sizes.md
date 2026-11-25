# US flat-resource stored-length table

The native flat-asset loader reads **7,762 unsigned 16-bit stored lengths** at
`0x80091D20..0x800959C4` (15,524 bytes). `1510D0EC` checks the resource index
against `0x1E52`, loads the selected halfword, handles zero-length slots, and
uses that length for the compressed read. `1510D374` sums preceding halfwords
to locate the requested stream from ROM `0x1A37E0`.

Full-span US consumer hashes:

| Start | Bytes | SHA-1 |
| --- | ---: | --- |
| `1510D0EC` | 648 | `47b67aab9ed8a4eb1706ced5424981ff21373aba` |
| `1510D374` | 144 | `b56e9f67e46ac44069b229680a76dde3e42baba0` |

An independent traversal of the flat archive used DEFLATE stream termination,
without reading the length table, to recover all 7,760 physical stream extents.
Inserting the two explicit empty runtime slots, 1767 and 1768, reproduces every
halfword and all 9,494,881 archive bytes. The table's SHA-256 is
`51b40c4080feea4e04b7e4921bce202c67a5d1c27f04ee92086255b6b38d6454`.
The normalized US ROM SHA-1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

## Reconstruction ownership and placement

`src/game/data/flat_asset_sizes.c` is a new data-only reconstruction owner.
It is not a claim that the original game had a C translation unit with that
name or boundary. It contains one typed `const u16[7762]` initializer, with no
function implementations, pointer initializers or copied compressed payloads.
Existing functions retain their active bodies. Their extern declarations now
state the actual array type; disabled candidates preserve byte addressing and
pointer assignment with the corresponding const-qualified expressions.

The canonical GAME linker consumes the actual compiled `.rodata` in a separate
INFO section at `0x80091D20`. Its emitted 16-byte-aligned envelope is 15,536
bytes; only the 15,524-byte payload is owned. The final twelve compiler padding
bytes must be zero, and the following original GAME data remains unassigned.
The source is included explicitly in GAME integration as a data-only input,
without adding or modifying function/source-unit registration.

`config/data/us.json` records the reconstruction source owner. The existing
boundary audit, linked GAME rodata verification, full GAME code comparison and
native report enforce the placement independently. The reference symbol has
an explicit halfword type and payload extent; scalar lengths cannot become
pointer relocations or neighboring symbols.

The original GAME data archive still supplies runtime storage. This work can
add matched data credit, but does not claim complete data or a reconstructed
GAME archive.

## Acceptance

Verified on working-tree changes based on
`38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`. The [machine evidence](us_flat_asset_sizes.json)
records the source, compiled object, report and input fingerprints.

- `./conker game-build`: all 2,072,880 GAME code bytes and the 15,524-byte
  table payload match the US ROM; twelve excluded compiler-padding bytes are zero.
- `./conker test`: 2,940 tests passed, eight skipped, 175.573 seconds. The
  initial run exposed a missing alternate raw/done source path in the ownership
  manifest; the manifest was corrected before this successful full rerun.
- `./conker build --assets`: the complete 67,108,864-byte US ROM is identical,
  140 seconds including setup, SDK and Docker.
- `./conker objdiff report`: zero compile errors, 282.5 seconds preparation
  and 24.8 seconds report/validation. All 26,809 previous editable asset-input
  hashes are preserved; the snapshot is current. Progress and whitespace pass.

Matched data rises from 63,100,336 to **63,115,860 / 65,120,512 bytes
(96.92163%)**. Complete data remains 63,079,392. The previous unassigned
`80091A20` span splits into a 768-byte prefix, this 15,524-byte source owner,
and a 108-byte unassigned suffix at `800959C4`. No other existing unit's
measures change; code and function metrics are unchanged.

Both affected C-only objects preserve their complete `.text` payloads (896
bytes for `game_305D0.c`, 352 for `game_139FC0.c`), function extents, and every
relocation site, kind and destination. Four references in the latter object
now describe `D_80091D20` as 15,524 bytes instead of the old one-byte extern;
this expected declaration metadata change does not alter instructions or
relocation destinations. The independent consumer check also rejects all four
tested endpoint mutations.

Native report SHA-256:
`cbf40d301f92e7f6ba908dd57e0329fbdc719035d60a297a175646114b0fe2ff`.
Input fingerprint:
`865712f7c8fa39f5c84c4370902fdb5902e317f3eab205ca6befc15727f60ba1`.
