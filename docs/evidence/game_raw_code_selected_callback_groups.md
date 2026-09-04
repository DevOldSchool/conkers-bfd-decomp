# US code-selected callback groups

Evidence kind: `structural_analysis`. This review extends the owned data-pointer
search with exact function addresses constructed by US game code. Each code
selection is an ordinary MIPS `%hi/%lo` pair whose resulting pointer is stored,
compared, passed to a factory, or invoked with `jalr`. These are function-pointer
uses, not direct `jal` calls.

For every accepted range, the raw assembly index and independent US function
CSV agree on all entries and spans, both outer endpoints are 16-byte aligned,
and no conditional branch crosses an endpoint. Every member has an owned data
selection, an exact code construction, or a direct local relationship with a
selected member. Generic source names derive from retail-ROM offsets; all 33
functions remain raw assembly.

| Source | US range | Entries | Bytes | Range SHA-1 |
| --- | --- | ---: | ---: | --- |
| `src/game/game_10B380.c` | `0xDDED0:0xDE310` | 6 | 1,088 | `a94c960b83562efc2cee5e6a2ee23011a3f7b755` |
| `src/game/game_10B7D0.c` | `0xDE320:0xDE7C0` | 4 | 1,184 | `9d5d43c2c546a8feb0e8ae9f25ce701c75e43eb3` |
| `src/game/game_117D90.c` | `0xEA8E0:0xEAB10` | 3 | 560 | `ffd6367b976262f5af655d1350d318f87dba588f` |
| `src/game/game_142A70.c` | `0x1155C0:0x116110` | 6 | 2,896 | `5ee405ad5507a6bf50e2268b818019ed6775f301` |
| `src/game/game_1BA670.c` | `0x18D1C0:0x18E4A0` | 6 | 4,832 | `3215e9c81d0210c8ab11d2ba6f2b390f6ceb8c24` |
| `src/game/game_1CFE10.c` | `0x1A2960:0x1A3150` | 7 | 2,032 | `2e3f410e31a415777b8666df592567a2016c301b` |
| `src/game/game_20B050.c` | `0x1DDBA0:0x1DDC20` | 1 | 128 | `3f5d8433ddb21e6c44eda4a323537ffb03395191` |

## Exact code selections

- `func_150DDED0` is constructed at `0x11C184:0x11C18C` and invoked through
  `jalr $v0` at `0x11C1A8`. The other five members of its range have exact
  owned-data selections at `0x8008A4C8`, `0x8008A43C`, `0x8008A440`,
  `0x80089C84`, and `0x8008C9F8`.
- `func_150DE32C` is constructed at `0x10904:0x1090C` and stored to
  `0x800E0934`. Its three companions are selected at `0x8008CD30`,
  `0x80088DB0`, and `0x80088ED0`.
- `func_150EA904` is constructed at `0x10680:0x10688` and stored to
  `0x800E0940`. The two adjacent members are selected at `0x8008CD10` and
  `0x80088F60`.
- `func_15116058` is constructed at `0x464C:0x4654` and compared with the
  live function pointer at object offset `+0x38`. Four other members are
  selected at `0x80088DE0`, `0x80088DEC`, `0x80088CD0`, and `0x80088CCC`;
  selected `func_15115EDC` calls the remaining local helper
  `func_15115E0C`.
- `func_1518E298` is constructed at `0x18F740:0x18F748` for a factory call and
  at `0x1904E4:0x1904FC` for a second registration call. Data selects
  `func_1518D6E0` at `0x8008BB5C`; it calls local `func_1518E308`, while
  `func_1518D1C0` repeatedly calls closing `func_1518E3C4` and
  `func_1518E37C` calls `func_1518E308`.
- `func_151A2B84` and `func_151A2BD0` are constructed together at
  `0x1A2C7C:0x1A2C9C` and chosen by a runtime condition. Both are local to
  `func_151A2C24`, also called by `func_151A2A14` and `func_151A2AD4`.
  The opening and closing members are selected at `0x800897A4` and
  `0x8008F8E0`. All seven members correlate strongly with the debug beta; six
  also correlate strongly with ECTS.
- `func_151DDBA0` is constructed and stored as a live callback at
  `0x1DE4A4:0x1DE4B8`, `0x1E545C:0x1E5484`, and
  `0x1E5538:0x1E5554`. Its exact singleton span is independently indexed.

Beta correlations support identity where present but are not used as the
selection proof.
