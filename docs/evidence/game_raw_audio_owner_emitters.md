# US audio-linked and owner emitter families

Evidence type: `structural_analysis`

These three working source groups use older local `mkst/conker` navigation
intervals at commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`, as context. The first is narrowed to exclude the
preceding composite factory. Original filenames and exact historical
compilation units remain unknown. Generic filenames add `0x2D4B0` to the
raw US start offset.

## Owner emission: `0xB0A60:0xB10F0`

`150B0C34` wraps local constructor `150B0C58`. That constructor allocates
an emitter through `15149130`, selecting update `0x58` and event `0x43`,
and copies 12 custom bytes (owner pointer, owner identity, and timing) to
object `+0x28`. The engine stores these selectors at `+0x11/+0x13`.
Owned table slots `8008A648` (`8008A4E8 + 0x58*4`) and `8008A9E4`
(`8008A8D8 + 0x43*4`) select local `150B0D20/150B0CE0`.
The update calls the first member `150B0A60` to derive its emission
parameters. The event callback passes the exact owner/identity fields
`+0x28/+0x2C` to `15169850`. All five entries connect through this
constructor, update, and event path. The unrelated preceding `150B06B0`
composite factory is excluded at aligned `0xB0A60`.

## Audio-linked element system: `0xB3DD0:0xB53D0`

`150B3F5C` constructs an element system through `15147A80`, requesting
`0x58` custom bytes, `0x24` bytes per element, primary update 7, secondary
update 7 and draw 7. Descriptor `+0x10` is set to 9. The engine copies
that field to object `+0x20`, which selects its event and cleanup handlers.
Owned tables select the following local callbacks:

| Role | Slot | Target |
| --- | --- | --- |
| Primary update | `8008A21C` | `150B40E8` |
| Secondary update | `8008A258` | `150B4294` |
| Draw | `8008A2C0` | `150B4710` |
| Cleanup | `8008A314` / `8008A364` | `150B3E74` / `150B3EE8` |
| Event | `8008A3B4` | `150B538C` |

The secondary update directly calls local element-spawning helper
`150B5088`; the event callback handles command 5 by calling `150B5060`.
The first member `150B3DD0` broadcasts exactly that command through
`15147D64`, then sends its related emitter notifications. The constructor
starts audio ID `0x221`; both cleanup wrappers call `1000FC18` with that
same ID and object position before delegating to the generic release path.
All ten entries are tied by the system's callbacks, element management,
command, and audio lifetime.

## Counted owner emitter: `0xB53D0:0xB58F0`

`150B53D0` allocates through `15149130` with update `0x24`, event/cleanup
`0x23`, and 16 custom bytes at object `+0x28`. Owned slot `8008A578`
selects update `150B54A8`; event slot `8008A964` selects `150B5840`.
The latter compares or transfers the custom owner pointer and identity.
Cleanup slots `8008A714/8008A83C` select `150B57E8/150B5814`; both call
local `150B57C4` before generic release. Construction increments counter
6 through `151D2AB0`, and that helper decrements the same counter through
`151D2B4C`. This accounts for the complete six-entry family.

## Mechanical review

Raw words equal the owned US code image. The independent US beta-index CSV
confirms every member and span. All cuts are 16-byte aligned; no missing or
overlapping words or conditional branches cross the boundaries. Debug
correlations provide additional support, with no ECTS correspondence in
these ranges. All members remain `raw_asm`, with no matched-C claim.

### `src/game/game_DDF10.c`

Range `0xb0a60:0xb10f0`; 5 entries, 1,680 bytes.
SHA-1: `88da31f6c7ee671f84d02dfd0f7db3382be20ac9`.
debug: 4 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150B0A60` | `0x1d4` |
| `func_150B0C34` | `0x24` |
| `func_150B0C58` | `0x88` |
| `func_150B0CE0` | `0x40` |
| `func_150B0D20` | `0x3d0` |

### `src/game/game_E1280.c`

Range `0xb3dd0:0xb53d0`; 10 entries, 5,632 bytes.
SHA-1: `e33a809b8db1f9e7ebb6148bbde1163264092dbf`.
debug: 6 correlations, 4 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150B3DD0` | `0xa4` |
| `func_150B3E74` | `0x74` |
| `func_150B3EE8` | `0x74` |
| `func_150B3F5C` | `0x18c` |
| `func_150B40E8` | `0x1ac` |
| `func_150B4294` | `0x47c` |
| `func_150B4710` | `0x950` |
| `func_150B5060` | `0x28` |
| `func_150B5088` | `0x304` |
| `func_150B538C` | `0x44` |

### `src/game/game_E2880.c`

Range `0xb53d0:0xb58f0`; 6 entries, 1,312 bytes.
SHA-1: `b243e7696aa59e6c8f5f4c0ad6630f748d72ca59`.
debug: 6 correlations, 3 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150B53D0` | `0xd8` |
| `func_150B54A8` | `0x31c` |
| `func_150B57C4` | `0x24` |
| `func_150B57E8` | `0x2c` |
| `func_150B5814` | `0x2c` |
| `func_150B5840` | `0xb0` |

## Integration result

All three groups integrated on the first attempt. The complete US game
overlay is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All 21 entries remain
raw ASM; this validates layout preservation.
