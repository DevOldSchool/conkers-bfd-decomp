# US actor-state and descriptor-emitter groups

Evidence type: `structural_analysis`

These working families use older local `mkst/conker` navigation ranges
(commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`) as context. Original filenames and exact historical
compilation units remain unknown. The emitter range is narrowed from the
older `0xE68B0:0xE9890` interval.

## Actor-state group: `0x3B7C0:0x3CF20`

`1503B9BC` obtains actor state through `+0x31C`, then `+0x11C`.
It calls local `1503B7C0` when this state is absent, and the initializer
allocates and clears its `0x50` bytes and seeds state at `+0x44/+0x4C`.
The main routine then calls local `1503B95C` at `0x3BA44` and its final
geometry helper `1503CB98` at `0x3CB70`.

The otherwise isolated-looking classifier `1503B840` sets actor byte
`+0x2FB` bits 1 or 2 according to actor type and IDs from the tables
`8009877C:80098836`. `1503B95C` reads these exact bits from indexed
address `800CC5CB + actor_index * 0x32C`: `800CC5CB` equals the actor
array base `800CC2D0` plus `0x2FB`. It suppresses the state path according
to those bits and clears state byte `+0x4E` for bit 2. This concrete writer/
reader relationship connects the classifier to the rest of the five-member
family. The last helper returns and pads to the existing aligned end.

## Descriptor-driven emitter: `0xE68B0:0xE7290`

`150E68B0` derives position and emission parameters through three tables,
with signed descriptor selectors and `-1` as the absent value:

| Owned US table | Local callbacks | Dispatch instructions |
| --- | --- | --- |
| `80088A20` | `150E6E34`, `150E6ED8`, `150E6F18` | `0xE6988:0xE69AC` |
| `80088A2C` | `150E6FAC`, `150E70CC` | `0xE693C:0xE6960` |
| `80088A34` | `150E70EC`, `150E71E4` | `0xE6A20:0xE6A44` |

The constructor then calls `151491F4` with update selector `0xF` and
copies `0x44` custom bytes to object `+0x28`. That wrapper forwards the
update selector to `15149130`, which stores it at object `+0x11`.
The emitter engine's table `8008A4E8` therefore selects `150E6B84` at
owned slot `8008A524`. That update consumes the custom parameters and
spawns effects. This accounts for all nine entries through actual dispatch
paths, beyond their contiguous table addresses. The following `150E7290`
begins a separate composite factory and is excluded.

## Mechanical review

All raw instruction words equal the owned US code image. An independent
US beta-index CSV check confirms every member and span. Both ranges are
16-byte aligned, with no missing/overlapping words or conditional branches
crossing their boundaries. The emitter has nine strong debug correlations
and eight strong ECTS correlations; the actor group has only one weak debug
correlation, so its grouping rests on the US structural evidence above.
All members remain `raw_asm`; these mappings claim no matched C.

### `src/game/game_68C70.c`

Range `0x3b7c0:0x3cf20`; 5 entries, 5,984 bytes.
SHA-1: `98c05bf3066a13d83df5d67a4e979bae28a5004a`.
debug: 1 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1503B7C0` | `0x80` |
| `func_1503B840` | `0x11c` |
| `func_1503B95C` | `0x60` |
| `func_1503B9BC` | `0x11dc` |
| `func_1503CB98` | `0x388` |

### `src/game/game_113D60.c`

Range `0xe68b0:0xe7290`; 9 entries, 2,528 bytes.
SHA-1: `04bfcf676967959266bc38f2dde3381965c7276a`.
debug: 9 correlations, 9 strong.
ects: 9 correlations, 8 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150E68B0` | `0x2d4` |
| `func_150E6B84` | `0x2b0` |
| `func_150E6E34` | `0xa4` |
| `func_150E6ED8` | `0x40` |
| `func_150E6F18` | `0x94` |
| `func_150E6FAC` | `0x120` |
| `func_150E70CC` | `0x20` |
| `func_150E70EC` | `0xf8` |
| `func_150E71E4` | `0xac` |

## Integration result

Both groups integrated on the first attempt. The complete US game overlay
is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 14 entries remain
raw ASM; this validates layout preservation.
