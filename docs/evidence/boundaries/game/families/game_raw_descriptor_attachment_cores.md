# US descriptor and attachment lifecycle cores

Evidence type: `structural_analysis`

Two reviewed working source groups contain 26 raw entries and 9,632 bytes.
Both refine larger upstream ASM ranges at independently reviewed internal
endpoints. Original filenames and exact historical source ownership remain
unknown; the offset-derived names and functions remain raw ASM.

## Extents

The navigation input is local `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`,
whose combined-image base is `0x2D4B0`. It records the starts and broader
ends `0x1580B0:0x15AF90` and `0x19EF90:0x1A3390`. The narrower
ends below come from the independent body, callback and beta checks.
The owned US code SHA-1 is
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

| Source under `src/game/` | US range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_185560.c` | `0x1580b0:0x158bd0` | 12 | 2,848 | 10 (6) | 10 (7) |
| `game_1CC440.c` | `0x19ef90:0x1a0a10` | 14 | 6,784 | 5 (5) | 2 (0) |

## `game_185560.c`: descriptor lifecycle

Opening `151580B0` selects object type `0x37/0x55`, allocates through
`15167A68`, copies descriptor fields, and initializes related state.
`151581D8` wraps that constructor. Two engine descriptor records select
its lifecycle callbacks: update `15158224`, drawing `151582C8`, cleanup
wrappers `15158AA4/15158AD0`, and event handler `15158B3C`.
Their pointer slots occur at `8008BFD4:8008C004` and
`8008C5EC:8008C61C`.

The update dispatches through `8008AE00` with its pointer load at
`0x158284` and `jalr` at `0x158290`. The drawing path uses `8008AE0C`
with load at `0x158310` and `jalr` at `0x15831C`. These tables select
members `15158684/15158AFC` and `1515858C/15158920`, tying the
middle handlers to the early callbacks. The cleanup pair shares
`15158A20`. Final `15158B3C` handles event type `0x2D` by updating the
owner pointer at `+0x40` and its discriminator byte at `+0x44`.

At `0x158BD0`, a new constructor starts by selecting a different object
type, `0x2E`, allocating a different layout, and calling helpers outside the
reviewed core. The preceding event handler is 148 bytes in US, debug
`0x15CDFC:0x15CE90`, and ECTS `0x14844C:0x1484E0`; each ends in
its own return at a 16-byte-aligned boundary. This preserved tail and the
change in constructor/layout corroborate the narrower working end. The
remaining code through `0x15AF90` receives no mapping credit here.

## `game_1CC440.c`: attachment construction and cleanup

Opening `1519EF90` follows an owner record through `+0x0/+0x18`,
checks its attachment at `+0x1D4`, and derives a relative position.
Constructor `1519F1C8` uses that helper and initializes an attached effect;
`1519F3B8` and late `151A084C` reuse this constructor. The main callback
`1519F7F0` also uses the opening position helper and shared cleanup
`1519F48C`.

`1519F48C` follows custom state at `+0x98`, clears the corresponding
owner slots at `+0x58` for types 6/7, and updates object flags. The paired
cleanup `151A0928` clears the other slots in that same owner record,
selected by byte `+0x2C` and pointer `+0x28`. It is called from early
`1519F400`, late `151A084C` and final `151A09B4`; the final event
handler also releases the object through `1516972C`. This directly connects
setup, update and cleanup across the extent. Eleven owned-data pointer slots
select the group's callbacks.

The endpoint `0x1A0A10` follows the final handler's return. The next
routine starts a different object/position path using `800C35EA` and fields
`+0x180/+0x184`. Its strong debug counterpart begins at `0x1A3D40`
after a returned and padded predecessor. The connected owner-slot lifecycle
and that transition support the narrower working group; later unrelated
families through `0x1A3390` are left unmapped.

## Boundary checks and limits

Every raw instruction, delay slot and padding word equals the owned US
payload. The 26 existing labels agree with the US function index and their
spans cover the two ranges exactly. No decoded conditional branch crosses
either end in either direction. Neighboring/final returns and following
prologues were inspected, including the two new internal endpoints.
These are structural source-family hypotheses, not recovered linker symbols;
no data, rodata or BSS ownership is assigned.

Record the reviewed raw endpoints before supported source registration.
Ordered ASM-backed skeletons and membership are registered with `./conker`;
complete US overlay byte equality gates integration. No matched C is claimed.

## Membership

### `src/game/game_185560.c`

Range SHA-1: `b2e2dc5957be88a950d4dcf7b7f747df09a96516`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_151580B0` | `0x128` |
| `func_151581D8` | `0x4c` |
| `func_15158224` | `0xa4` |
| `func_151582C8` | `0x2c4` |
| `func_1515858C` | `0xf8` |
| `func_15158684` | `0x29c` |
| `func_15158920` | `0x100` |
| `func_15158A20` | `0x84` |
| `func_15158AA4` | `0x2c` |
| `func_15158AD0` | `0x2c` |
| `func_15158AFC` | `0x40` |
| `func_15158B3C` | `0x94` |

### `src/game/game_1CC440.c`

Range SHA-1: `276e999f19ac571682e363a896d0063f690d9e81`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1519EF90` | `0x178` |
| `func_1519F108` | `0x60` |
| `func_1519F168` | `0x60` |
| `func_1519F1C8` | `0x1f0` |
| `func_1519F3B8` | `0x48` |
| `func_1519F400` | `0x8c` |
| `func_1519F48C` | `0x64` |
| `func_1519F4F0` | `0x300` |
| `func_1519F7F0` | `0x67c` |
| `func_1519FE6C` | `0x9e0` |
| `func_151A084C` | `0xdc` |
| `func_151A0928` | `0x28` |
| `func_151A0950` | `0x64` |
| `func_151A09B4` | `0x5c` |

## Integration result

Both reviewed groups integrated through the supported US gate. The complete
2,072,880-byte overlay remains byte-identical, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Functions remain raw ASM.
