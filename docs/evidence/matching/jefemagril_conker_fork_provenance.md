# Provenance: authored C from jefemagril/conker fork

## Summary

Independently authored matching C from the contributor's local
`conker` checkout / remote fork (`jefemagril/conker`), and **not** present as
finished C on upstream `mkst/conker` (`origin/master`), is reused in this
repository under the contribution exception in [LEGAL.md](../../../LEGAL.md).

## Rights

- Author: jefemagril (local contributor)
- Permission: the author confirms these functions were authored by them and
permits inclusion under this project's MIT license.
- Upstream `mkst/conker` has no repository license file; only functions that
are finished in the fork/local tree and **not** finished upstream are in
scope for this reuse.



## Port results

Inventory-mapped unmatched targets at start: **92** (83 game + 9 init aliases).

Successfully finished with US `CURRENT (0)` (**32**):

- `func_150027F8`
- `func_15004AAC`
- `func_150104F0`
- `func_15012370`
- `func_15016588`
- `func_150492CC`
- `func_15060BE0`
- `func_150717E0`
- `func_1507A3E8`
- `func_1508EF80`
- `func_150C251C`
- `func_150C3160`
- `func_1513532C`
- `func_151353A8`
- `func_151355B8`
- `func_151368A8`
- `func_15138BC0`
- `func_1514143C`
- `func_151415D4`
- `func_1514462C`
- `func_15144B68`
- `func_151464B8`
- `func_1514672C`
- `func_1515CF9C`
- `func_151638E0`
- `func_15167D84`
- `func_151927C0`
- `func_151D343C`
- `func_151DADA0`
- `func_80001420` (`func_bootstrap_clear_region`)
- `func_800043B4`
- `func_8000FE88`



### Not yet ported

- **~54** remaining inventory-mapped symbols with C bodies still need per-function work:
  - compile adaptation against local TU types / call contracts (many)
  - near-miss deferred C in many TUs (e.g. init sound helpers at `CURRENT (18–775)`)
  - source-unit layout recovery when an earlier matched member shifts later offsets
  (several hit `CURRENT (0)` but fail unit layout — restored to `GLOBAL_ASM`)
  - port script now prefers `#if 0 CONKER_DEFERRED_CANDIDATE` bodies over raw fork C when present
- **6** authored-list entries were declaration-only false positives (no C body in fork)
- **213** libultra-only authored functions remain on the library track (not game/main work items)

Supporting shared layouts from those ports live in `include/types.h` (promoted
from the contributor fork’s `structs.h` where cross-source use required it).