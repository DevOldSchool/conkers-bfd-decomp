# US owner effect with particle and audio lifecycle

Evidence type: `structural_analysis`

The working source group `0xD3360:0xD5440` retains an older navigation
interval from local `mkst/conker` commit
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`
(combined base `0x2D4B0`). The original filename and exact historical
compilation unit remain unknown. Constructor, resource ownership, callbacks
and cleanup connect all twelve entries.

## Structural evidence

Constructor `150D3360` resolves an owner resource through `1503195C`,
uses local anchor helper `150D4AE0`, and calls `15147A80` with `0x20`
custom bytes, secondary update `0xD`, and draw `0xD`. It copies `0x1C`
owner/state bytes into the custom area addressed by object `+0x98` and owns
two child objects at custom `+0xC/+0x10`.

The common effect engine stores secondary update at `+0x30` and draw at
`+0x31`. Owned slots `8008A270/8008A2D8` therefore select local
`150D3A68/150D4300`. Its descriptor also selects supplemental step 1 via
object byte `+0x24`: the engine's third update table is `8008A284`, read at
`0x14788C` and called at `0x147898`; slot `8008A288` selects local
`150D3FD4`. These callbacks operate on the same `+0x98` owner state,
`+0x94` working array, and `+0x2C/+0x2D` progression bytes.

Descriptor cleanup/event selector `0xF` is copied to object `+0x20`.
Owned event slot `8008A3CC` selects `150D49C0`; the two release tables
select `150D4BD4/150D4C00` at `8008A32C/8008A37C`. Both release
wrappers call local `150D4C2C`, which releases the same two custom child
pointers before generic effect cleanup. Update `150D3A68` also calls the
local anchor helper and particle spawner `150D4D58`.

The second child created by `150D3360` passes step selector `0x27` through
`151407D0` and `1513D524` into the particle engine. Its step table
`80089D60 + 0x27 * 4 = 80089DFC` selects local `150D4CC4`, which
consumes the extra custom fields at `+0x170/+0x174`; the constructor
explicitly copies those eight bytes at `0xD3A44:0xD3A50`.

The constructor passes local `150D5124` to `1000FA64`, with the custom
state pointer and sound IDs `0x5B3/0x5B4/0x5BC`. For example, its address
is constructed at `0xD34BC/0xD34C0` and passed in the stack argument at
`0xD3520`. Cleanup `150D4C2C` passes exactly that callback, state pointer
and those IDs to `1000FD38`. The callback consumes the same owner/state
and adjusts audio parameters. This explicit installation/removal pair connects
the final function independently of adjacency or shared global constants.

## Validation

All twelve labels agree with the independent US index. Their spans total
8,416 bytes and match owned US instructions, delay slots and padding. Both
endpoints follow complete returns; no decoded conditional branch crosses
either boundary in either direction. No data, rodata or BSS ownership is
assigned. Full US overlay byte equality gates integration. All entries remain
raw ASM, not matched C.

### `src/game/game_100810.c`

Range `0xd3360:0xd5440`; 12 entries, 8,416 bytes.
SHA-1: `28bdfa4f483cd4992b7364bd1a74a74439a38ac4`.
debug: 6 correlations, 3 strong.
ects: 4 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150D3360` | `0x708` |
| `func_150D3A68` | `0x56c` |
| `func_150D3FD4` | `0x32c` |
| `func_150D4300` | `0x6c0` |
| `func_150D49C0` | `0x120` |
| `func_150D4AE0` | `0xf4` |
| `func_150D4BD4` | `0x2c` |
| `func_150D4C00` | `0x2c` |
| `func_150D4C2C` | `0x98` |
| `func_150D4CC4` | `0x94` |
| `func_150D4D58` | `0x3cc` |
| `func_150D5124` | `0x31c` |

## Integration result

Registered and integrated all reviewed members as raw ASM. The complete US
game overlay is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Integration passed on its
first attempt. This verifies layout preservation, not original filenames.
