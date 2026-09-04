# US quad rendering and actor-state effects

Evidence type: `structural_analysis`

These are working source-family boundaries, not recovered original filenames
or confirmed historical compilation units. The older navigation intervals are
from local `mkst/conker` commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`, combined base `0x2D4B0`. The quad family starts
after the older interval's separate initializer, at a reviewed complete return.

## Quad object family: `0x179FE0:0x17ABB0`

Constructor `15179FE0` allocates `0xB8` bytes with a caller-selected type and
initializes packed coordinate pairs at `+0x90:+0x9A`, motion `+0xA0:+0xA6`,
and appearance/lifetime fields through `+0xB3`. Constructor `1517A644`
allocates the same size with concrete type 9 and initializes the same layout;
wrapper `1517AA20` calls it. Updates `1517A1EC/1517A84C` consume those
coordinate/motion fields and release expired objects.

The owned engine table at `8008B4A8`, stride `0x34`, confirms the grouping:
types 8, `0xC` and `0x59` use update `1517A1EC`; type 9 uses `1517A84C`.
All four use renderer `1517A3A0` and draw setup `1517A958`. Table rows start
at `8008B648/8008B67C/8008B718/8008C6BC` respectively. The engine's
draw path calculates that stride at `0x16757C:0x167598`; setup is loaded
from row `+0x14` and called at `0x167784`.

The renderer consumes this packed layout, branches explicitly for types
`0xC/0x59`, and calls local helper `1517A9A8`. Setup `1517A958` resets
shared draw cache `800DD450` and invokes local identity hook `1517A394`
for those two types. Their row `+0x20` slots additionally reference final
adapter `1517AB7C`, which forwards its signed selector to `1510B7B4`.
This covers every member; the preceding initializer is not assigned here.

## Actor-state effect API: `0x15AF90:0x15BAE0`

External actor-state routine `151236D0` connects this otherwise split-looking
family. Its branches at `0x123824/0x123880/0x123890` call cleanup wrappers
`1515BA80/1515BAAC`; `0x1238EC/0x12390C` call creation wrappers
`1515BA54/1515BA1C`. The inactive branches at `0x123838/0x1238D0` and
`0x12391C` call empty hooks `1515BA48/1515BA10`. All receive the same
actor selector byte `+0x23D`, selected by state flags `+0x5F0` and `+0x2C`.
The two empty hooks therefore have concrete API ownership, not merely proximity.

Wrapper `1515BA1C` calls `1515AF90`. That constructor selects update `0xC`
in `151491F4` and copies `0x18` custom bytes to `+0x28`; owned update slot
`8008A518` is local `1515B21C`, which consumes the copied emission state.
Wrapper `1515BA54` calls `1515B674`. Its `1515548C` call selects update 2
and copies `0x18` custom bytes to `+0x70`. The engine stores update selector
at `+0x68` and dispatches its low nibble through `8008ACC8`
(`0x154CF0/0x154CFC`); slot 2 is local motion update `1515B994`.

The second constructor's descriptor is based at stack `+0x9C`, with event
selector 1 written at `+0xB6` (`0x15B6C8/0x15B6EC`). `1515548C`
copies the descriptor to object `+0x10`, placing that selector at `+0x2A`.
Engine event dispatcher `15155564` reads it and calls `8008AD04[index]`
at `0x155588/0x155594`; owned slot 1 is local `1515B62C`.
That event releases an object on event `0xB` when custom selector `+0x70`
matches the message. Both cleanup wrappers call `1515B5F4`, which sends
exactly event `0xB` through `1515572C` to type list `800A6038 = [0x5D,0x57]`.
Those are exactly the two types selected by `1515548C`.

## Validation

All 22 entries agree with the independent US index. Their spans total 5,920
bytes and match owned US instructions, delay slots and padding word for word.
All endpoints follow complete returns, and no decoded conditional branch
crosses a range boundary in either direction. No data, rodata or BSS ownership
is assigned. Full US overlay byte equality gates integration. All members
remain raw ASM, not matched C.

### `src/game/game_1A7490.c`

Range `0x179fe0:0x17abb0`; 10 entries, 3,024 bytes.
SHA-1: `695b7d3f515a5c4ee888aba10551844fcc18f751`.
debug: 7 correlations, 6 strong.
ects: 6 correlations, 4 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15179FE0` | `0x20c` |
| `func_1517A1EC` | `0x1a8` |
| `func_1517A394` | `0xc` |
| `func_1517A3A0` | `0x2a4` |
| `func_1517A644` | `0x208` |
| `func_1517A84C` | `0x10c` |
| `func_1517A958` | `0x50` |
| `func_1517A9A8` | `0x78` |
| `func_1517AA20` | `0x15c` |
| `func_1517AB7C` | `0x34` |

### `src/game/game_188440.c`

Range `0x15af90:0x15bae0`; 12 entries, 2,896 bytes.
SHA-1: `d1ae78a47d555eeb278ea8d7ba43688062319134`.
debug: 12 correlations, 7 strong.
ects: 9 correlations, 4 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1515AF90` | `0x28c` |
| `func_1515B21C` | `0x3d8` |
| `func_1515B5F4` | `0x38` |
| `func_1515B62C` | `0x48` |
| `func_1515B674` | `0x320` |
| `func_1515B994` | `0x7c` |
| `func_1515BA10` | `0xc` |
| `func_1515BA1C` | `0x2c` |
| `func_1515BA48` | `0xc` |
| `func_1515BA54` | `0x2c` |
| `func_1515BA80` | `0x2c` |
| `func_1515BAAC` | `0x34` |

## Integration result

The first full US overlay gate passed: 2,072,880 identical bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Both groups are integrated
as mixed C/ASM, with all 22 entries remaining raw ASM.
