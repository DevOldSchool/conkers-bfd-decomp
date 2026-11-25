# US spawn-record subset

Bank `0E` stores 69 compressed scene lists with 962 native 48-byte spawn
records. The supported subset reconstructs **14,519 stored bytes** across
68 lists and 938 records. Entry 14 remains excluded: one of its 24 records
has unexplained byte `12 = 50`. Its entire 374-byte compressed stream remains
backing, alongside 235 bytes of outer alignment. The outer directory already
has separate ownership.

## Native format

`150169A0` first copies a fixed record prefix into `D_800D20FC`, then loads
bank `0E` at depth two into the following space through `1502B8E0`. The returned
length is divided by 48. `150825C0` indexes this array by the same stride.
The constructor `15082A44` retains its first argument at actor offset `144`,
allowing later consumers to read the original spawn record.

The codec exposes 26 scalar fields covering 42 bytes. Names retain their
native offsets and widths where a higher-level interpretation is unnecessary.

| Offsets (hex) | Native storage |
| --- | --- |
| `00`, `2A`, `2C` | unsigned halfword |
| `06`, `08`, `0A`, `14` | signed halfword |
| `18` | 32-bit flags |
| `20`, `24` | single-precision float |
| `02`, `03`, `04`, `0C..11`, `13`, `1C`, `1D`, `28`, `29`, `2E`, `2F` | unsigned byte |

Most loads are in the constructor, through its saved record argument.
`150825C0` reads byte `02` after deriving `base + index * 48`.
The constructor passes the record as `a2` to `150839B8`, which reads unsigned
halfword `2C` at `150839DC`. `150623F4` reads unsigned halfword `2A` at
`15062434` through actor `144`. `150832AC`, called with the same actor by the
constructor, reads byte `2F` at `150832E0`. Both latter paths retain the record
pointer across a null check; their branch-likely delay slots cannot clobber it.
Eight complete native consumer spans are authenticated before reconstruction.

The five inter-field lanes `05`, `16..17` and `1E..1F` are constrained to zero.
**Byte `12` is also constrained to zero in this subset, but its meaning remains
unresolved.** It is not called padding or exposed as an opaque field. Any
nonzero unexplained storage rejects the record. Entire entry 14 is excluded.
The codec rejects extra/missing fields, invalid widths, nonfinite floats and
incorrect extents. Float encoding preserves signed zero. A fresh length prefix
and level-six raw DEFLATE reproduce each selected original stream.

## Build and ownership

Editable manifest and `spawns.json` live beneath
`build/assets/asset-directories/us/bank0E/spawn-records/`. The parent manifest,
directory and backing stay unchanged. The builder composes fresh selected
streams into the actual `asset_bank_0e.o`; other bytes remain preserved backing.
The report checks this whole linked object against the source reconstruction
and original ROM before comparing the disjoint selected stream ranges.

Edits, deletion, malformed input and source races fail without replacing user
files. Explicit `./conker asset-directories recover --part bank0E` backs up the
whole parent, including the child sources, before recovery. Make tracks both
new child files for edits and deletions.

## Validation

The independent research pilot checked every original scalar and reproduced
all 68 selected streams. All 24,388 single-field mutations changed encoding or
were rejected; all 5,628 mutations of constrained lanes were rejected.
The production source audit repeated these checks and rejected both endpoint
mutations in each of eight complete native consumers (16 mutations).
The actual linked-object pilot matched 14,519/14,519 bytes; independently
changing every claimed byte caused all 14,519 native comparisons to reject a
perfect match.

All 93 focused tests (two skips), 49 Make integration tests, and 2,992 full
Docker tests (eight skips) passed. `./conker build --assets` rebuilt the exact
67,108,864-byte US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, in 151 seconds. Progress and whitespace
checks passed. Tested base: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, with
these working-tree changes applied.

The full native report accepts **+14,519 matched and complete data bytes**:
63,223,787 / 65,120,512 matched, with 1,896,725 remaining. Bank `0E`'s
unreconstructed unit shrank from 15,128 to 609 bytes; all earlier unit measures
were preserved. All 27,253 earlier editable-source hashes and all earlier
linked asset-object hashes stayed identical. Two child source files were added.
Rebuilt CPU object/ELF container hashes are recorded without inferring their
cause: the fresh full-span code/data proofs are unchanged, and an independent
extraction of the current linked ELF reproduces the exact original ROM.

Report SHA-256:
`551b0e69768cc4e14518c88d10679a000804017d69add9161eed8b6f06dbf2aa`.
See [machine-readable evidence](us_spawn_records.json) for the field sites,
consumer checksums, source audit and accepted before/after measures.
