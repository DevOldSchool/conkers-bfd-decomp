# US clipping, resource and effect families

Evidence type: `structural_analysis`

Three working source groups contain 63 raw entries and 23,568 bytes.
They are structurally reviewed raw ASM groups, with unknown original
filenames and no claim of recovered historical linker boundaries.

Local `mkst/conker` at `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml`, supplies navigation intervals (combined-image
base `0x2D4B0`). Its `0x184150:0x187EC0` interval is independently
refined at `0x1875E0`; `0x1321D0:0x134070` is retained after reviewing
its dispatch and resource lifecycle.

| Source under `src/game/` | US range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_1B1600.c` | `0x184150:0x1875E0` | 28 | 13,456 | 20 (6) | 21 (6) |
| `game_1B4A90.c` | `0x1875E0:0x187EC0` | 4 | 2,272 | 2 (2) | 2 (2) |
| `game_15F680.c` | `0x1321D0:0x134070` | 31 | 7,840 | 16 (9) | 6 (3) |

## `game_1B1600.c`: clipping and rendering workspace

Main path `15186794` calls `15184DF0`, `15184368`, `1518652C`,
`151873E4`, `15184FA4` and `15185F24`. The early workspace producers
set the projection/clipping values at `800D3688/800D368C`; the middle
helpers and late renderer consume those same values. Opening `15184150`
is called by `15184DF0`.

`15185F24` calls clipping worker `15185DD4` four times. That worker
walks `0x14`-byte records and loads two indexed function tables from
`8008D498` and `8008D4C0` at `0x185E28/0x185E2C`, invoking their
intersection and predicate functions with `jalr`. Their twenty pointer
slots cover all eighteen small routines `15185454:15185DD4`;
two intersection routines occur twice. For example, `15185454`
interpolates position and three halfword attributes at a clipping plane,
while paired `15185554` tests that plane. This provides actual indirect
call evidence for the otherwise disconnected middle helpers.

Late `151872B0` sets `800DE01C/20/24`, `800DE030/34/38/3C`,
and `800DE040/41`, directly consumed by `15186794`, `15184368`
and `1518652C`. Final `151873E4` initializes `800DF0E8:F4` and
`800D3690`, also used by the main workspace path. It returns at
`0x1875D8` with stack restoration in the delay slot. The following
constructor has a different allocation/lifetime and is mapped separately.

## `game_1B4A90.c`: allocated effect records

Constructor `151875E0` allocates object type `6` with `0xB0` bytes,
then allocates a `0x780`-byte block into object `+0xA4`. It initializes
the timer pair at `+0xA8/+0xAA`, position at `+0x90:0x98`, and
the block's `0xA0`-stride effect records.

Update `15187978` advances that timer, updates the same records, and
frees `+0xA4` before releasing the object when the timer expires.
Draw callback `15187A98` uses the record block and calls matrix helper
`15187D6C` at `0x187BE0`. Owned engine slots `8008B5E0/B5E8`
select the update/draw pair. Both callbacks have consecutive strong debug
and ECTS counterparts. This ties all four entries into one lifecycle.
The final helper returns before two padding words and the existing
`0x187EC0` endpoint.

## `game_15F680.c`: resource-backed descriptor lifecycle

Constructor `1513264C` chooses object type `0x19/0x48`, reserves a
`0x170`-byte base, and manages the count, reference table and resource
slots at `800DC63C`, `800DC468`, and `800DC460/464`. It calls
resource initializer `151336A8`; cleanup `15132444` reverses those
references and calls `151325C8` to release per-view resources.
`15132A4C` wraps construction, while `15132570/1513259C` wrap cleanup.

Opening update `151321D0` invokes tables at `80089988`, `800898B0`,
`80089914`, and `8008997C`. Cleanup callbacks `151323AC/151323F8`
invoke `800899B0/800899D4`, which select the cleanup wrappers.
Callback `15132A88` uses `8008998C`; drawing `15132B80` uses
`800899A4`. Secondary update `15132DDC` dispatches through
`80089934/80089970/80089974`; event callback `15133588` uses
`800899F8`. These are actual pointer loads followed by `jalr`, rather
than unused constants resembling function addresses.

The owned tables select the later update, motion, event and draw helpers.
Direct calls additionally connect `15133894` to `151337C0`, the
paired motion routines `15133C58/15133D20` to `15133B98`, and
the three draw wrappers `15133E84/15133EB8/15133FD8` to
`15133EEC`. Near-final `15133E3C` passes the two-word list at
`800A3860` (`0x19, 0x48`) to `15169260`, matching the constructor's
two object types. Paired engine descriptor records select the opening
update, drawing and cleanup callbacks.

The existing outer endpoints follow separate returned routines and padding.
The final drawing wrapper is linked directly to its shared helper. The next
range starts a distinct byte-index lookup routine at `0x134070`.

## Validation and limits

All 63 existing raw labels agree with the US index. Their ordered spans
cover the reviewed ranges exactly; every instruction, delay slot and padding
word equals the owned US payload. No decoded conditional branch crosses
any endpoint in either direction. The new internal endpoint follows a full
return and precedes an independently described constructor.

No data, rodata or BSS ownership is assigned. Beta correlations supplement
the structural review and do not recover original filenames. Supported raw
source registration and complete US overlay byte equality gate integration.

## Membership

### `src/game/game_1B1600.c`

Range SHA-1: `f1bd5ded829502c6791fe6cb3dde95722cc8e62a`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_15184150` | `0x218` |
| `func_15184368` | `0xa88` |
| `func_15184DF0` | `0x1b4` |
| `func_15184FA4` | `0x4b0` |
| `func_15185454` | `0x100` |
| `func_15185554` | `0x28` |
| `func_1518557C` | `0x100` |
| `func_1518567C` | `0x2c` |
| `func_151856A8` | `0x108` |
| `func_151857B0` | `0x2c` |
| `func_151857DC` | `0xf8` |
| `func_151858D4` | `0x28` |
| `func_151858FC` | `0x100` |
| `func_151859FC` | `0x2c` |
| `func_15185A28` | `0x100` |
| `func_15185B28` | `0x2c` |
| `func_15185B54` | `0xf0` |
| `func_15185C44` | `0x28` |
| `func_15185C6C` | `0xf0` |
| `func_15185D5C` | `0x28` |
| `func_15185D84` | `0x28` |
| `func_15185DAC` | `0x28` |
| `func_15185DD4` | `0x150` |
| `func_15185F24` | `0x608` |
| `func_1518652C` | `0x268` |
| `func_15186794` | `0xb1c` |
| `func_151872B0` | `0x134` |
| `func_151873E4` | `0x1fc` |

### `src/game/game_1B4A90.c`

Range SHA-1: `0c14a006e76d0fb9ea2736719bfbbbad29322de2`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_151875E0` | `0x398` |
| `func_15187978` | `0x120` |
| `func_15187A98` | `0x2d4` |
| `func_15187D6C` | `0x154` |

### `src/game/game_15F680.c`

Range SHA-1: `c6e69d921485c7ad610299a4a259105a00b28298`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_151321D0` | `0x1dc` |
| `func_151323AC` | `0x4c` |
| `func_151323F8` | `0x4c` |
| `func_15132444` | `0x12c` |
| `func_15132570` | `0x2c` |
| `func_1513259C` | `0x2c` |
| `func_151325C8` | `0x84` |
| `func_1513264C` | `0x400` |
| `func_15132A4C` | `0x3c` |
| `func_15132A88` | `0xf8` |
| `func_15132B80` | `0x25c` |
| `func_15132DDC` | `0x500` |
| `func_151332DC` | `0x234` |
| `func_15133510` | `0x78` |
| `func_15133588` | `0x120` |
| `func_151336A8` | `0xb8` |
| `func_15133760` | `0x60` |
| `func_151337C0` | `0xd4` |
| `func_15133894` | `0x140` |
| `func_151339D4` | `0x7c` |
| `func_15133A50` | `0x44` |
| `func_15133A94` | `0x104` |
| `func_15133B98` | `0xc0` |
| `func_15133C58` | `0xc8` |
| `func_15133D20` | `0xc8` |
| `func_15133DE8` | `0x54` |
| `func_15133E3C` | `0x48` |
| `func_15133E84` | `0x34` |
| `func_15133EB8` | `0x34` |
| `func_15133EEC` | `0xec` |
| `func_15133FD8` | `0x98` |

## Integration result

All three groups integrated on the first attempt. The complete 2,072,880-byte
US overlay is byte-identical, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Functions remain raw ASM.
