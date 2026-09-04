# US owner child-chain and resource emitter families

Evidence type: `structural_analysis`

These working groups retain older local `mkst/conker` navigation intervals
(commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`). Original filenames and exact historical compilation
units remain unknown. US structural links, not the older cuts alone, support
the following membership.

## Owner child-chain: `0xC09B0:0xC1260`

`150C0AC0` allocates type `0x25` through `15167A68`, with base size
`0x48` plus caller-requested slot storage, and copies a `0x1C` descriptor
to object `+0x18`. Owned type-table row `8008BC2C` selects update
`150C0C38`, event `150C09B0`, and cleanup `150C09F0/150C0A1C`.
The event delegates owner-pointer and identity handling using `+0x20/+0x24`.
Both cleanup wrappers call local `150C0A48`, which walks linked 8-byte child
slots using the storage pointer `+0x40`, active head `+0x44`, and `-1`
sentinel, releasing each child.

The update creates particles through `15130280`, links them into those same
slots, and copies the parent pointer to each child's custom `+0xA8` at
`0xC105C:0xC108C`. Final member `150C1198` reads that exact parent pointer,
finds its own child slot, unlinks it from the parent's active chain, and
returns the slot to the free chain at `+0x46`. Owned data `80089800`
contains this callback. It is selected by the particle's zero-valued cleanup
selector: the constructor descriptor starts at stack `+0x80`, its byte at
`+0xE3` is zero, and the engine copies it to object `+0x73` before cleanup
dispatch. Thus all seven entries form one parent/child lifecycle.

## Resource emitter: `0xC4120:0xC4BF0`

`150C4120` creates an emitter with update `0x53`, event/cleanup `0x40`,
and `0x1C` custom bytes at object `+0x28`, including owner identity,
a child pointer, and flags. Its selectors resolve through owned US tables:

| Role | Slot | Local target |
| --- | --- | --- |
| Update | `8008A634` | `150C44A4` |
| Cleanup | `8008A788` / `8008A8B0` | `150C4B08` / `150C4B34` |
| Event | `8008A9D8` | `150C4B60` |

The constructor also creates a particle through `15130280`, stores it in
custom `+0xC` (object `+0x34`) at `0xC4484`, and supplies child custom
data. Both cleanup wrappers call local `150C4AD8`, which releases exactly
that `+0x34` child before generic emitter release. Event commands `0x55`
and `0x56` clear/set bit 2 in custom `+0x16`; other events delegate owner
handling through `15149514`. The update consumes the same custom resource
and owner state. All six entries are covered without extending into the
following routines.

## Mechanical review

Every raw word equals the owned US image; independent US beta-index CSV
membership and span checks agree. Both ranges have aligned complete-function
cuts, no missing/overlapping words, and no conditional branches crossing
boundaries. The first family has sparse debug/ECTS corroboration; the second
has none and rests entirely on the specific US callback and lifecycle links.
All members remain `raw_asm`; no matched-C claim is made.

### `src/game/game_EDE60.c`

Range `0xc09b0:0xc1260`; 7 entries, 2,224 bytes.
SHA-1: `31e19bee764e9da373c2c49b05c8e67d7b02d0b8`.
debug: 5 correlations, 1 strong.
ects: 3 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C09B0` | `0x40` |
| `func_150C09F0` | `0x2c` |
| `func_150C0A1C` | `0x2c` |
| `func_150C0A48` | `0x78` |
| `func_150C0AC0` | `0x178` |
| `func_150C0C38` | `0x560` |
| `func_150C1198` | `0xc8` |

### `src/game/game_F15D0.c`

Range `0xc4120:0xc4bf0`; 6 entries, 2,768 bytes.
SHA-1: `a0b9c8ea1fa455ff615244644bbae93c43578d9d`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C4120` | `0x384` |
| `func_150C44A4` | `0x634` |
| `func_150C4AD8` | `0x30` |
| `func_150C4B08` | `0x2c` |
| `func_150C4B34` | `0x2c` |
| `func_150C4B60` | `0x90` |

## Integration result

All reviewed members integrated on the first attempt. The complete US game
overlay is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw
ASM; this verifies layout preservation.
