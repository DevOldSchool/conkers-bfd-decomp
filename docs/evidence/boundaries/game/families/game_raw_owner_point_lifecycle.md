# US owner-associated point-array lifecycle

Evidence type: `structural_analysis`

Working source `src/game/game_1D9F10.c` covers `0x1ACA60:0x1AE6B0`:
14 raw entries and 7,248 bytes. It narrows the older navigation interval
`0x1ABE40:0x1AF5C0` from local `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`
(combined-image base `0x2D4B0`). The two new endpoints are structural
hypotheses; no original filename or exact historical object ownership is claimed.

## Lifecycle evidence

Opening `151ACA60` allocates type `0x30`, with a `0x30`-byte base,
records its owner at `+0x1C`, owner identity at `+0x20/+0x24`, and scale
at `+0x28`. It calls `151ACB38` to classify the owner. Its callback
`151ACB60` follows owner `+0x31C` to the associated object at `+0x9C`,
then calls late helper `151AE3A8`; its event callback is `151ACB94`.
Owned engine slots `8008BE6C/8008BE84` select these two callbacks.

`151ACBD4` creates type `0x2F` or `0x4E`, with a `0x58`-byte base,
copies a `0x24`-byte descriptor to `+0x10`, allocates a `0x1E0`-byte
point array at `+0x38`, sets point count `+0x42` to twenty, and initializes
owner association `+0x44` and timer `+0x52`. Points have a `0x18`-byte
stride. Update `151AD174` and draw `151AD92C` use that exact point
array/count. The update reads the owner association and its `+0x31C`
state. Engine slots `8008BE38/8008BE3C` and `8008C484/8008C488`
select these callbacks for the two types.

Late `151AE06C` calls the opening classifier `151ACB38`, then attachment
helpers `151AE0E4/151AE264`. The lookup `151AE590`, called by
`151AE0E4`, scans lists for the two words at `800A9270`: exactly
`0x2F, 0x4E`. This joins the lookup to the constructor, beyond general
similarity of object fields. `151AE0E4` calls point interpolation helper
`151AE2BC`, examines the same point array/count, and establishes both
sides of the relationship: owner `+0x31C -> +0x9C` receives the point-array
object, and that object `+0x44` receives the owner. This is the pointer
consumed by the opening controller's callback.

`151AE3A8` uses the associated point array, scale and count to update
owner placement. Final callback `151AE640` clears or replaces the
association at `+0x44` on events `0` and `0x2D`; engine slots
`8008BE50/8008C49C` select it. Constructor, update, drawing, lookup,
attachment and association cleanup therefore form a connected lifecycle.

## Boundaries and validation

The new start follows `jr ra` at `0x1ACA58` and a nop delay slot.
The final callback returns at `0x1AE6A8` with its nop at `0x1AE6AC`.
Both endpoints are 16-byte aligned. The next routine is a separate effect
emitter calling an earlier constructor outside this core. Neither surrounding
raw interval is assigned to this source.

Every raw instruction, delay slot and padding word equals the owned US
payload; all 14 labels agree with the US function index, and their ordered
spans cover the range exactly. No decoded conditional branch crosses either
endpoint in either direction. The refreshed beta report has six debug
correlations (all strong) and five ECTS correlations (four strong). These
support correspondence but do not establish original compilation-unit limits.
No data, rodata or BSS ownership is assigned. All functions remain raw ASM.

## Membership

Range SHA-1: `375d4c22b43a0a94a57a70407a6c2eb834868b5f`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_151ACA60` | `0xd8` |
| `func_151ACB38` | `0x28` |
| `func_151ACB60` | `0x34` |
| `func_151ACB94` | `0x40` |
| `func_151ACBD4` | `0x5a0` |
| `func_151AD174` | `0x7b8` |
| `func_151AD92C` | `0x740` |
| `func_151AE06C` | `0x78` |
| `func_151AE0E4` | `0x180` |
| `func_151AE264` | `0x58` |
| `func_151AE2BC` | `0xec` |
| `func_151AE3A8` | `0x1e8` |
| `func_151AE590` | `0xb0` |
| `func_151AE640` | `0x70` |

## Integration result

The first full US overlay gate passed. All 2,072,880 bytes are identical to
the owned original payload (SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`).
The source is integrated with its raw ASM entries; no C match is claimed.
