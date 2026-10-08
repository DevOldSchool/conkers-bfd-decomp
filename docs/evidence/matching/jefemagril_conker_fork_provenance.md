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

Successfully finished with US `CURRENT (0)` in the first pass (**31**):

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
- `func_800043B4`
- `func_8000FE88`



### Completion pass (2026-10-07)

An earlier unverified transfer of fork bodies into active source was discarded and
every function was re-ported through `./conker finish`, then gated with three clean
`./conker verify-batch` runs (`BATCH_COMPLETE`). **47** further functions reached US
`CURRENT (0)`:

- `src/main/init_1420.c`: `func_80001420` (`func_bootstrap_clear_region`), using the
  fork body unchanged, including its unused zero-valued locals, at the author's
  request; verified by a fourth clean batch against the main ROM image
- `src/game/game_3B920.c`: `func_1500E470`
- `src/game/game_3DC30.c`: `func_15010880`
- `src/game/game_40490.c`: `func_15014F6C`
- `src/game/game_83300.c`: `func_150597FC`, `func_1505EEB0`
- `src/game/game_981E0.c`: `func_1506D6B4`, `func_1506DC10`, `func_15070C40`,
  `func_15073B38`, `func_150746F0`, `func_150747E4`, `func_15074A94`
- `src/game/game_A28B0.c`: `func_15076768`, `func_15079228`, `func_15079F6C`,
  `func_1507A428`, `func_1507A47C`
- `src/game/game_CB1C0.c`: `func_1509DDFC`
- `src/game/game_EF410.c`: `func_150C2424`, `func_150C2FCC`
- `src/game/game_131F30.c`: `func_15104FF8`
- `src/game/camera/camera_camera.c`: `func_15123070`, `func_15125490`,
  `func_15125628`, `func_15125A6C`, `func_15127EB8`
- `src/game/effects/blood.c`: `func_15134908`, `func_15134DAC`, `func_15137F30`
- `src/game/game_168A90.c`: `func_1513B798`
- `src/game/game_169510.c`: `func_1513F4E4`, `func_1513FFF4`
- `src/game/game_16EE20.c`: `func_15142314`, `func_151424F4`, `func_15142B7C`,
  `func_15142C10`, `func_15142CF0`, `func_15142FBC`, `func_151436B4`
- `src/game/effects/light.c`: `func_15160A58`, `func_15162510`
- `src/game/game_1944C0.c`: `func_15167010`, `func_15167B44`, `func_15168B44`,
  `func_151696DC`
- `src/game/game_2062D0.c`: `func_151D9450`

The fork bodies were kept statement-for-statement. Where a body missed here, the cause
was a declaration that differed from the fork's, and the fix was to give the body the
fork's contract in the owning source: unprototyped callees (`func_1505D024`,
`func_1000FD38`, `func_15060A9C`), narrower parameter or return types
(`func_1514C470`, `func_1000FA64`, `func_151D9450`, `func_1513FFF4`), array rather
than scalar globals taken by address at the use site (`D_800CC2D0`, `D_8008B4A8`,
`D_800DD198`), the function type of the `D_1000EF40` callback address, local
project names for SDK routines (`func_10022EC0`, `func_15047D60`, `func_15047C00`,
`func_150A7790`), and source-local copies of the display-list macros used by
`game_169510.c` and `game_16EE20.c`.

Not ported:

- `func_1508F060` (`src/game/game_BC510.c`): deferred at `CURRENT (20)`. The fork loop
  links to identical bytes, but the reference names `D_800D246D` / `D_800D247D` where
  the unrolled loop emits `D_800D2460+0xd` / `+0x1d`.
- `func_151254F4` (`camera_camera.c`): the fork working tree un-commented a body its
  own note marks non-matching, and the fork build differs from the ROM in exactly that
  function. The existing deferred candidate here is unchanged.
- Six authored-list rows are declaration-only in the fork (`func_10004074`,
  `func_150AAD98`, `func_15109064`, `func_1514C470`, `func_151669A0`,
  `func_151BA468`); there is no body to port.
- The 213 libultra rows and 23 SDK-named init rows need no port: six map by address to
  entries already matched here, and the rest lie in ranges this repository builds from
  its `lib/` archive sources.

Current match state is owned by `progress/functions.json`.

Supporting shared layouts from those ports live in `include/types.h` (promoted
from the contributor fork’s `structs.h` where cross-source use required it).
