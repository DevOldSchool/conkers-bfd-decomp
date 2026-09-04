# Complete US pointer-selected raw segment at `0x11EF40`

Evidence kind: `structural_analysis`. This review covers the complete existing
raw-map segment between the reviewed neighboring boundaries at `0x11EF40` and
`0x11F980`. The generic source name derives from its retail-ROM offset and does
not claim a recovered historical filename. All seven functions remain raw
assembly.

Every member has an exact owned US game-data pointer selection. The independent
US function CSV and the raw reference agree on every entry and span, both outer
endpoints are 16-byte aligned, and no conditional branch crosses either outer
endpoint.

| Source | US range | Entries | Bytes |
| --- | --- | ---: | ---: |
| `src/game/game_14C3F0.c` | `0x11EF40:0x11F980` | 7 | 2,624 |

| Function | US span | Owned selection |
| --- | --- | --- |
| `func_1511EF40` | `0x11EF40:0x11F31C` | `0x80088FA8` -> `func_1511EF40` |
| `func_1511F31C` | `0x11F31C:0x11F3E8` | `0x80088F6C` -> `func_1511F31C` |
| `func_1511F3E8` | `0x11F3E8:0x11F4D0` | `0x80088F84` -> `func_1511F3E8` |
| `func_1511F4D0` | `0x11F4D0:0x11F768` | `0x80088F90` -> `func_1511F4D0` |
| `func_1511F768` | `0x11F768:0x11F788` | `0x80088FA0` -> `func_1511F768` |
| `func_1511F788` | `0x11F788:0x11F92C` | `0x80088F9C` -> `func_1511F788` |
| `func_1511F92C` | `0x11F92C:0x11F980` | `0x80089074` -> `func_1511F92C` |

The complete range SHA-1 is
`b574d80b98c003b28bf3baebc320b42d59d78e04`. The five-function middle
sequence from `func_1511F31C` through `func_1511F788` also has strong debug-beta
correlations; the first four of those functions have strong ECTS correlations.
Those correlations support entry identity but are not used as the boundary
proof.

The earlier callback-table review stopped at `0x11EF40` because the non-null
slot at `0x80088FA8` selected the following raw-map entry. This review follows
that lead across the complete next raw segment and accounts for every member,
including the final selection at `0x80089074`.

