# US particle lifecycle and emitter helpers

Evidence type: `structural_analysis`

Two reviewed working groups contain 20 raw entries and 10,992 bytes.
Original filenames and historical source ownership remain unknown. The
functions retain raw ASM and their existing symbols.

Navigation comes from local `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`,
with combined-image base `0x2D4B0`. Its `0xD8B10:0xDAE70` interval
is retained. The final four helpers are independently separated from its
larger `0x149550:0x14CA80` interval.

| Source under `src/game/` | US range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_105FC0.c` | `0xD8B10:0xDAE70` | 16 | 9,056 | 12 (6) | 9 (3) |
| `game_1797A0.c` | `0x14C2F0:0x14CA80` | 4 | 1,936 | 4 (4) | 4 (4) |

## `game_105FC0.c`: owner-following particle lifecycle

Opening helpers `150D8B10/150D8B3C` derive the owner's raised position
and related direction. Constructor `150D8B88` and step `150D8FAC`
both use them. The constructor calls `15147A80` with update index `0xE`,
step index `1`, draw index `0x11`, and a `0x50`-byte custom descriptor.
The engine tables at `8008A200`, `8008A23C`, and `8008A2A4` select
members `150D8E4C`, `150D8FAC`, and `150D9C7C` for those indices.
Update and step share motion helper `150D8D84`; step also calls
detachment helper `150D8E1C`.

Another engine-selected callback, `150D942C` at slot `8008A298`,
calls final emitter `150DA67C` at `0xD96F0`. Cleanup pair
`150DA4B4/150DA4E0` shares `150DA484`, which releases the sound
handle from custom data `+0x30` via object `+0x98`. Event sender
`150DA5EC` sends event `0x44`, handled by `150DA50C` using that
same custom record. Owned slots at `8008A2F8/A348/A398` select
these cleanup/event callbacks.

The less obvious `150DA628` callback is tied to the final emitter by
the descriptor itself. At `0xDA748` the emitter sets `0x24`, stores it
at stack `+0x1B2` at `0xDA7AC`, and passes the descriptor starting at
stack `+0x150` to `15130280` at `0xDA9DC`. That constructor copies
it to object `+0x10`, placing this byte at object `+0x72`. The generic
update reads that byte at `0x130A0C` and dispatches through `80089760`
at `0x130A2C/0x130A38`. Entry `0x24` is slot `800897F0`, whose
owned value is `150DA628`. The emitter also copies sixteen custom
bytes to the child at `+0xA8`; this callback consumes precisely that area
through `15131828/15131958`. This establishes the callback relationship
without relying on adjacency.

Both outer endpoints follow returned routines and padding. The final emitter
returns before the existing aligned end. Beta mappings corroborate twelve
debug and nine ECTS members, but do not establish an original source name.

## `game_1797A0.c`: four emission-loop variants

The four routines `1514C2F0`, `1514C470`, `1514C678`, and
`1514C858` implement related emission loops. Each indexes the same
constructor table `8008AA00`, then invokes the selected pointer while
varying positions, direction or random offsets. The table loads occur at
`0x14C3A0`, `0x14C59C`, `0x14C794`, and `0x14C9A4`; corresponding
`jalr` instructions are `0x14C3F4`, `0x14C5FC`, `0x14C7EC`, and
`0x14CA08`. Shared trigonometric helper `151423D8` and random helper
`150ADA20` support the differing placement paths. The selected constructors
are external to the group; no ownership of their table or code is inferred.

The preceding routine only changes object flags, lifetime and scale and
returns at `0x14C2E8`; the new start is aligned at `0x14C2F0`.
The final emitter returns at `0x14CA6C`, followed by padding. All four
entries strongly correlate in sequence to debug `0x150A90:0x151220`
and ECTS `0x13D260:0x13D9F0`, preserving the exact `0x790` extent.
Both beta extents also end after the final returned routine and padding.

## Validation and limits

The twenty raw labels agree with the US index. Ordered spans cover both
ranges exactly. Every instruction, delay slot and padding word matches the
owned US payload; no decoded conditional branch crosses either endpoint
in either direction. No data, rodata or BSS ownership is assigned.

These are structural source-family hypotheses, not recovered linker symbols.
Supported registration records the newly reviewed raw start before full
US overlay byte equality gates integration.

## Membership

### `src/game/game_105FC0.c`

Range SHA-1: `0b759dea7235aba674ed2aaa86028a9f052fe68e`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_150D8B10` | `0x2c` |
| `func_150D8B3C` | `0x4c` |
| `func_150D8B88` | `0x1fc` |
| `func_150D8D84` | `0x98` |
| `func_150D8E1C` | `0x30` |
| `func_150D8E4C` | `0x160` |
| `func_150D8FAC` | `0x480` |
| `func_150D942C` | `0x850` |
| `func_150D9C7C` | `0x808` |
| `func_150DA484` | `0x30` |
| `func_150DA4B4` | `0x2c` |
| `func_150DA4E0` | `0x2c` |
| `func_150DA50C` | `0xe0` |
| `func_150DA5EC` | `0x3c` |
| `func_150DA628` | `0x54` |
| `func_150DA67C` | `0x7f4` |

### `src/game/game_1797A0.c`

Range SHA-1: `f562e9dca5a9ac091224aaa0446810df20c728c2`. Spans include padding.

| Entry | Raw span |
| --- | ---: |
| `func_1514C2F0` | `0x180` |
| `func_1514C470` | `0x208` |
| `func_1514C678` | `0x1e0` |
| `func_1514C858` | `0x228` |

## Integration result

Both groups integrated on the first attempt. The complete 2,072,880-byte
US overlay is byte-identical, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Functions remain raw ASM.
