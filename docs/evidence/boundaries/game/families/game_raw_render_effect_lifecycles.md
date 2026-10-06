# US rendering state and effect lifecycles

Evidence type: `structural_analysis`

These four working source groups contain 64 raw entries and 19,088 bytes.
Original filenames and exact historical compilation-unit ownership remain
unknown. Offset-derived names describe navigation; no matched C is claimed.

The navigation input is local `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`,
with combined-image base `0x2D4B0`. Three ranges refine its broader ASM
intervals; body and callback evidence below supports those internal cuts.

| Source under `src/game/` | US range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_C2350.c` | `0x94EA0:0x96970` | 16 | 6,864 | 12 (12) | 0 (0) |
| `game_1844C0.c` | `0x157010:0x1580B0` | 16 | 4,256 | 8 (6) | 3 (3) |
| `game_1DF510.c` | `0x1B2060:0x1B2950` | 9 | 2,288 | 9 (6) | 0 (0) |
| `game_204660.c` | `0x1D71B0:0x1D87E0` | 23 | 5,680 | 19 (11) | 0 (0) |

## Rendering state: `game_C2350.c`

This narrows upstream `0x948C0:0x96970`, excluding the initial vertex
expansion and matrix routines. Opening `15094EA0` builds the workspace at
`800D2CA8`, which `1509563C` subsequently uses for point transformation.
`15094F40` initializes the display list and clears `800D2CA0`; paired
wrappers `15094F70/15094FE8` prepare `800D2C90` through `15095060`
then call `150950D4`, which allocates and uses `800D2CA0`.

The later rendering chain connects `15095760/150958B0` to `1509563C`
and `15095A90/15095B08`. `15095B08` writes seven shared float slots
`800D2C70:800D2C88`, consumed by `15095D34`. Final `15096934`
clears `800D2DAB`, which that renderer reads at `0x95E18`.
`1509629C` also calls the earlier `15094F70` at `0x966D4`.
These specific producer/consumer relationships tie the two rendering paths
and their setup/reset routines together.

The new start follows a returned matrix routine and an anonymous eight-byte
return stub at `0x94E98`; that stub remains outside this group, with no new
symbol or source claim. The final reset routine returns and has three padding
words before the existing end. Debug preserves twelve correlated entries,
including opening `0x94920` and late renderer `0x95D40`.

## Descriptor and matrix lifecycle: `game_1844C0.c`

This narrows upstream `0x156190:0x1580B0`. Constructor `15157010`
chooses object types `0x36/0x4C/0x5B`, reserves a `0x120`-byte base,
copies the descriptor, initializes matrices at `+0x7C/+0xBC`, and owns
resources starting at `+0xFC`. `15157898` wraps the constructor.
Cleanup pair `15157248/1515728C` shares `151571C4`, which releases
the constructor's resources.

Update `151572D0` loads dispatch pointers from `8008AD90` and
`8008ADA0` at `0x157334/0x157370`, then calls them with `jalr`.
Drawing `15157420` similarly uses `8008ADBC` and `8008ADCC`
at `0x157464/0x157830`. Owned table slots select the group's
`15157AA8`, `15157860`, `15157918`, `15157DC8`, `15157F80`
and `15157FE8`; `15157DC8` wraps `15157DEC` with custom data at
`+0x120`. Shared engine descriptor records select update, drawing,
event wrapper `15157D88`, and the cleanup pair.

Final `15158078` passes the three-entry array at `800A6060` to
`15169260`. Its exact words are `0x36, 0x4C, 0x5B`, the same three
object types chosen by the opening constructor. This ties the final helper
to the family rather than relying on adjacency. The start follows the
previous family's cleanup return; the end follows this helper's return and
padding, before the separately reviewed `0x1580B0` descriptor family.

## Attached effect controller: `game_1DF510.c`

This narrows upstream `0x1B2060:0x1B30B0`. Opening `151B2060`
creates type `0x16` through `151491F4`, then copies a `0x20`-byte
descriptor to object `+0x28`. Callback `151B2100` validates the two
owners there, compares their generation bytes and updates the state at
`+0x35`. It calls state selector `151B22F4`, cleanup `151B222C`,
and creation paths `151B2348/151B2690`.

`151B222C` releases the three child slots at descriptor `+0x10`
and the fourth at `+0x1C`. Wrapper `151B220C` and cleanup pair
`151B229C/151B22C8` reuse that path. The constructor/callback and
child creation/cleanup thus form a connected lifecycle. Owned callback
slots are `8008A540`, `8008A6D0`, and `8008A7F8`.

The last creation path returns at `0x1B2948`, with its stack restoration
in the delay slot. The next routine at the new aligned end `0x1B2950`
uses a different layout (`+0x178/+0x17C`) and is left outside the core.
Debug preserves the nine-entry sequence from `0x1B55E0` through
`0x1B5ED0` (the same `0x8F0` extent). The remaining tail is unclaimed.

## Parent and particle lifecycle: `game_204660.c`

Opening `151D71B0` creates type `0x42` with an attached descriptor;
wrapper `151D74B0` reuses it. Main callback `151D7264` invokes
the table at `8008FCA0`, creates its child through `151D7830`,
and tears it down through `151D77C8`. Event `151D73A8` invokes
the neighboring `8008FCA4` table. The five owned words at
`8008FCA0:8008FCB4` select `151D75C4`, `151D7538`, `151D7724`,
`151D7770`, and `151D779C`. The update path itself dispatches the
last three through `8008FCA8` at `0x1D76F8/0x1D7700`.

Child creation `151D7830` supplies `15147A80` with update index
`0xD`, step/draw indices `0x10`, descriptor byte `0x19`, and copies
the parent pointer plus position into the child's `+0x98` custom area.
The generic constructor stores those indices at `+0x2F/+0x30/+0x31`;
its engine tables (`8008A200`, `8008A23C`, `8008A2A4`) select
this group's `151D792C`, `151D7A38`, and `151D80C4`.
The first two share `151D8718` to advance the `0x1C`-stride particle
records at `+0x94`. Late cleanup `151D8764` follows `+0x98` back
to the parent and clears its `+0x28` child slot; wrappers
`151D8780/151D87AC` reuse it. Earlier `151D77C8` clears the same
association from the parent side. This links both halves of the range.

Both upstream endpoints follow returns and padding. The following range
starts a byte-selector routine. Debug preserves nineteen correlated members;
beta correlations supplement the lifecycle evidence and do not prove an
original filename.

## Validation and limits

All 64 raw labels agree with the US index. Their ordered spans cover each
range exactly. Every instruction, delay slot and padding word equals the
owned US payload; no decoded conditional branch crosses either endpoint in
either direction. No data, rodata or BSS ownership is assigned.

The newly reviewed internal endpoints are recorded as raw ASM map splits
before supported registration. Full-overlay byte equality gates integration.

## Membership

### `src/game/game_C2350.c`

Range SHA-1: `12bd00a305c6bc6194b3d6f86b1b2705e16238fb`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_15094EA0` | `0xa0` |
| `func_15094F40` | `0x30` |
| `func_15094F70` | `0x78` |
| `func_15094FE8` | `0x78` |
| `func_15095060` | `0x74` |
| `func_150950D4` | `0x568` |
| `func_1509563C` | `0x124` |
| `func_15095760` | `0x150` |
| `func_150958B0` | `0x198` |
| `func_15095A48` | `0x48` |
| `func_15095A90` | `0x78` |
| `func_15095B08` | `0x204` |
| `func_15095D0C` | `0x28` |
| `func_15095D34` | `0x568` |
| `func_1509629C` | `0x698` |
| `func_15096934` | `0x3c` |

### `src/game/game_1844C0.c`

Range SHA-1: `f59e5b16aed982fd1865c74114817299df97046e`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_15157010` | `0x1b4` |
| `func_151571C4` | `0x84` |
| `func_15157248` | `0x44` |
| `func_1515728C` | `0x44` |
| `func_151572D0` | `0x150` |
| `func_15157420` | `0x440` |
| `func_15157860` | `0x38` |
| `func_15157898` | `0x80` |
| `func_15157918` | `0x190` |
| `func_15157AA8` | `0x2e0` |
| `func_15157D88` | `0x40` |
| `func_15157DC8` | `0x24` |
| `func_15157DEC` | `0x194` |
| `func_15157F80` | `0x68` |
| `func_15157FE8` | `0x90` |
| `func_15158078` | `0x38` |

### `src/game/game_1DF510.c`

Range SHA-1: `56375d1832f4d580068dea42da171e94116f5468`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_151B2060` | `0xa0` |
| `func_151B2100` | `0x10c` |
| `func_151B220C` | `0x20` |
| `func_151B222C` | `0x70` |
| `func_151B229C` | `0x2c` |
| `func_151B22C8` | `0x2c` |
| `func_151B22F4` | `0x54` |
| `func_151B2348` | `0x348` |
| `func_151B2690` | `0x2c0` |

### `src/game/game_204660.c`

Range SHA-1: `48e2be212770f0121bfac4d172c63f542a8dccd0`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_151D71B0` | `0xb4` |
| `func_151D7264` | `0x144` |
| `func_151D73A8` | `0x5c` |
| `func_151D7404` | `0x20` |
| `func_151D7424` | `0x2c` |
| `func_151D7450` | `0x2c` |
| `func_151D747C` | `0x34` |
| `func_151D74B0` | `0x88` |
| `func_151D7538` | `0x8c` |
| `func_151D75C4` | `0x160` |
| `func_151D7724` | `0x4c` |
| `func_151D7770` | `0x2c` |
| `func_151D779C` | `0x2c` |
| `func_151D77C8` | `0x68` |
| `func_151D7830` | `0xfc` |
| `func_151D792C` | `0x10c` |
| `func_151D7A38` | `0x298` |
| `func_151D7CD0` | `0x3f4` |
| `func_151D80C4` | `0x654` |
| `func_151D8718` | `0x4c` |
| `func_151D8764` | `0x1c` |
| `func_151D8780` | `0x2c` |
| `func_151D87AC` | `0x34` |

## Integration result

All four groups integrated on the first attempt. The complete 2,072,880-byte
US overlay is byte-identical, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Functions remain raw ASM.
