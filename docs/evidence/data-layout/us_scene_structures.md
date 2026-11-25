# US scene directories and collision cylinders

This batch reconstructs **11,128 bytes** of bank `0C` through two independent
report units, preserving the existing scene fields, model parameters and volumes:

| Unit | Typed records | Newly reconstructed bytes |
| --- | --- | ---: |
| `assets/scenes/directories` | 66 directories, 849 entries | 8,704 |
| `assets/scenes/cylinders` | 24 lists, 56 groups, 188 cylinders | 2,424 |

## Directories and generated alignment

The existing native archive-loader spans `1502AC88`, `1502B5C8` and `1502B7F0`
establish eight-byte directory entries: a relative offset and a packed size/flag
word. The scene bank has a 552-byte outer directory and 65 nonempty scene
containers, each beginning with a 96-byte directory. These tables account for
6,792 bytes. The top flag bit is set on the final entry in every reviewed table, including
empty terminal entries in the inner tables. The native size mask excludes that
bit; these entries do not select compressed payloads.

Typed offsets and sizes derive minimum eight-byte alignment between outer
entries and at the bank end. Scene children use minimum sixteen-byte alignment,
with no trailing scene-container padding. All 273 gaps are generated zeros:
260 outer and 1,652 inner bytes. Any excessive gap, invalid extent, overlap,
nonzero alignment or unexplained container tail rejects reconstruction.

The source schema records the outer directory and indexed scene directories.
Parent-child extents are derived from those entries, not a separate list of raw
fill lengths. Each original index value is checked by independent native-width
reads; 2,547 scalar mutations change the output or fail validation. All 1,912
individual alignment-byte mutations fail the decoder's original-storage check.

## Native cylinder groups

`150163D0` requests bank `0C`, child 9 at path depth three into `D_800D18B0`.
It walks eight-byte records to a zero offset, then relocates each live relative
offset by the returned base. `15055E50` loads this table, selects an unsigned
16-bit group ID at offset 6, reads the unsigned count at offset 4, and obtains
the relocated cylinder pointer from offset 0. Its cylinder pointer advances ten
bytes per iteration without intervening calls.

| Cylinder offset | Native field | Load |
| --- | --- | --- |
| 0 | signed X center | `15055FD8` |
| 2 | signed Z center | `15055FDC` |
| 4 | signed bottom coordinate | `15055F90` |
| 6 | signed height, added to bottom | `15055FB4` |
| 8 | unsigned radius/mode halfword | `15055FE0` |

The low fifteen bits of the last field give the radius; the high bit selects
the interior collision path. The encoder derives table offsets and counts from
typed groups, then emits contiguous ten-byte records. It emits the consumed
four-byte zero-offset sentinel. The following four bytes per list remain
uncredited backing, including their current zero values: **96 bytes excluded**.
The production source audit checks every scalar against independent native reads
and verifies 1,184 scalar mutations change the output.

The full 304-byte loader and 768-byte collision routine are authenticated against
the US ROM and fresh independent disassembly. The existing C-matching block on
`15055E50` concerns possibly uninitialized nearest-point scratch values on some
runtime paths. This data reconstruction neither changes that function nor claims
a defined C implementation; it relies only on the established native storage reads.

## Preserved inputs and actual linked ownership

Two new source children live under `build/assets/scene-fields/us/`:

- `scene-directories/{manifest,directories}.json`
- `scene-cylinders/{manifest,cylinders}.json`

All old source files remain unchanged. Each child has an independently checked
manifest; edited, malformed, missing or concurrently changed inputs fail without
replacement. Explicit parent recovery backs up all children. Make tracks each
child file, including deletion. The common scene builder composes the freshly
encoded spans into the actual linked bank and rejects overlap with every existing
scene family. The report compares only the new owned ranges, after proving the
entire linked bank against both fresh sources and the independent ROM.

Focused tests include actual nested directory fixtures, terminal flags, signed
native widths, scalar bounds, derived counts/offsets, preserved sentinel bytes,
source edits/deletions/recovery/races, incremental Make behavior, disjoint owned
ranges and corruption of the actual linked object outside the credited ranges.
All 65 focused tests passed. The final Docker suite passed all 3,006 tests
(eight existing skips), including the incremental Make cases. Each of the 11,128
claimed bytes was independently mutated in native comparison objects; every
mutation rejected a perfect match. Ten native-consumer endpoint mutations also
failed their authenticated full-span checks.

The full US asset build reproduced all 67,108,864 original ROM bytes in 184
seconds including setup (155.003 seconds for compile/link/verification). An
independent extraction from the current linked ELF also matched ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The accepted native report adds exactly 11,128 matched and complete bytes:
**63,255,857 / 65,120,512 matched bytes (97.136609%)**, with 1,864,655 remaining.
Only the old scene-bank remainder changes, from 28,900 to 17,772 bytes. All
27,259 prior editable-source hashes and 11,829 prior asset-object hashes are
preserved; four source files and two report units were added. Code, function
counts and denominators are unchanged. Progress and whitespace checks passed.

Tested base: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus uncommitted changes.
Source fingerprint: `15e31286fe46f6911044d742de29ff4ec60830df8b1283ba2d399b2a601f3285`.
Report SHA-256: `252e35e2df1b3101194280ea06adca3ab02af41147aa4756f572ce4df3ce0428`.
