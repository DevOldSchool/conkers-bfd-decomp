# ECTS game layout from its ROM loader

The owned, normalized ECTS ROM has SHA-1
`06597dc935651f8995bfacc30fde6e621d44c3e1`. Its executable loader establishes
the raw game boundaries independently of the older upstream split map:

| Field | Correct value | Previous value |
| --- | --- | --- |
| Game code ROM start | `0x21A30` | `0x26040` |
| Game code ROM end / data start | `0x20FB20` | `0x20FB10` |
| Game code VRAM | `0x15000000` | unchanged |
| Game data VRAM | `0x80068F90` | `0x80068F80` |
| Game data ROM end | `0x23DA50` | unchanged |

## Independent instruction evidence

At normalized ROM `0x1214:0x124C`, the startup loader constructs:

- `t1 = 0x151EE0F0` (`3C09151F`, then `2529E0F0`);
- `t2 = 0x00021A30` (`3C0A0002`, then `254A1A30`);
- `t4 = 0x15000000` (`3C0C1500`, then `258C0000`);
- `a1 = 0x80068F90` (`3C058007`, then `24A58F90`);
- `t5 = 0x80096EC0` (`3C0D8009`, then `25AD6EC0`).

It calls `0x10003F94` with ROM source `t1 + t2 - t4 = 0x20FB20`,
destination `a1`, and length `t5 - a1 = 0x2DF30`. This gives data end
`0x23DA50` and code size `0x1EE0F0` (2,023,664 bytes).

The TLB page loader independently adds ROM base `0x21A30` to the faulting
game page offset at `0x467C:0x4684`: `3C080002`, `25081A30`, `01485021`.
An embedded pair at ROM `0xB7B0:0xB7B8` also contains `0x21A30, 0x23DA50`.
ROM `0x21A30` begins a normal function prologue, while the previous start
`0x26040` is an interior source group, 17,936 bytes later.

The previous data start cut off the final return's delay slot and classified
another return-only function as data. The correct boundary follows those
instructions and padding; the following data contains game callback pointers.

## Cross-check and effect on evidence

Before correction, 1,238 corresponding JAL sites in strongly correlated
US/ECTS functions all disagreed with their ECTS callee offsets by exactly
`0x4610`. This led to the loader review; it was not used alone to choose a
new layout. Previously only 23 of 2,908 distinct in-range game JAL targets
were recovered ECTS function entries. With the corrected slice, 2,756 of
2,937 are recovered entries. Remaining index omissions include ordinary
math/RNG routines; this statistic is not a claim of complete disassembly.

`./conker beta-index` automatically invalidates the ECTS cache because its
code hash changes, while reusing the unchanged US and debug indexes. The
corrected code SHA-1 is `b4f9b6d9e4f93b85fbecbf3e68fc416c7b1d3b4a`;
the 188,208-byte data SHA-1 is
`df1e5e1e03b607581c1b0da030df521400b3363a`.

Old ECTS code offsets within the retained slice move forward by `0x4610`.
Old ECTS data offsets move back by `0x10`, while their actual runtime
addresses stay the same because the data base increases by `0x10`.
The camera/rope/bee and sight evidence notes have been corrected accordingly.
The earlier assertion that the Trail anchor had no direct callers is
withdrawn: `0x151A2F2C` calls its corrected entry `0x151A2F44`.

This correction changes beta research coordinates, not the retail US ROM,
its source-unit extents, or any C matching status. Historical beta-correlation
counts in other boundary notes describe their recorded discovery snapshots;
fresh research must use the regenerated index rather than old ECTS labels.
