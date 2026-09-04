# US rendering-record pool, glyph pipeline, and emitter callback pair

Evidence type: `structural_analysis`

These are three independently reviewed working source families. Original
filenames and exact historical compilation units are unknown. Older local
`mkst/conker` navigation ranges at commit
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`,
provide surrounding ranges, not proof of these narrower boundaries. Filenames
retain combined-image offsets (raw US offset plus `0x2D4B0`).

## Rendering records: `0x34F20:0x36310`

`15034F20` resets the byte count at `800C3F00`. `150356C8` allocates
successive 12-byte records from `800C3F08`, rejecting count 15. The producer
`15035808` calls this allocator, local geometry helper `15034F30`, and
local spatial test `15035714`. Both render paths `15035D6C/15035FE8`
read that exact count and pool and produce display-list commands.
`15036148` scans 25 actors at stride `0x32C`, tests their vertical state,
and invokes the same producer at `0x362B4`. Thus all eight entries connect
through the pool or its producer helpers. Preceding `15034860/15034EB4`
use different state at `800C3EF0` and are excluded. The preceding function
returns before aligned `0x34F20`; the last function returns and pads to
existing `0x36310`.

## Glyph rendering and measurement: `0x415E0:0x42D50`

`15042C40` maps input bytes through `80085930`, uppercases ASCII lowercase
letters, and gives space its special index. `150415E0` supplies dimensions,
scale, and flags for special byte values in `0xA8:0x100`, using the jump
table at `80098AB0`. Both the display-list builder `150417AC` and the
string-measurement routine `150428D4` call these same two helpers.
The former handles glyph drawing and the latter accumulates dimensions
through a zero-terminated byte stream; both use the display scale globals
`800380A0/800380A4`. This four-entry grouping excludes the preceding
lookup/display helpers because their source-family relationship is unproven.
The first cut follows a complete return at aligned `0x415E0`; the final
lookup returns and pads to existing `0x42D50`.

## Emitter callback pair: `0xF6890:0xF6B00`

`150F6890` constructs a descriptor and calls `15134DAC`, writing selector
8 at stack `+0x4B` relative to descriptor start `+0x1C`. The constructor
copies `0x3C` bytes to object `+0x18` at `0x134DF4:0x134E04`, placing
that selector at object `+0x47`. The engine loads that byte at `0x135148`
and dispatches through `80089B38` at `0x135164:0x135178`. Owned US data
slot `80089B58` (index 8) contains local `150F695C`. That callback derives
emission parameters through `15137F30` and produces a child with `151D9014`.
These two entries are directly tied by constructor selection and runtime
dispatch. The preceding event callback returns before aligned `0xF6890`;
the emitter returns and pads to existing `0xF6B00`.

## Mechanical review

Each range's raw assembly words were compared with the owned US code image.
Every indexed entry and span was independently checked against the US beta
index CSV. There are no missing or overlapping words and no conditional
branches crossing a proposed boundary. Debug/ECTS correlations supplement
this US structural evidence; they do not establish filenames. Every member
remains `raw_asm`; no C instruction-match claim is made.

### `src/game/game_623D0.c`

Range `0x34f20:0x36310`; 8 entries, 5,104 bytes.
SHA-1: `520ffc08b2bc3a0d25a439e4230411b8ca6befc9`.
debug: 5 correlations, 3 strong.
ects: 4 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15034F20` | `0x10` |
| `func_15034F30` | `0x798` |
| `func_150356C8` | `0x4c` |
| `func_15035714` | `0xf4` |
| `func_15035808` | `0x564` |
| `func_15035D6C` | `0x27c` |
| `func_15035FE8` | `0x160` |
| `func_15036148` | `0x1c8` |

### `src/game/game_6EA90.c`

Range `0x415e0:0x42d50`; 4 entries, 6,000 bytes.
SHA-1: `25173bd0201b32d5eaf35cbe4101f646a3e96953`.
debug: 2 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150415E0` | `0x1cc` |
| `func_150417AC` | `0x1128` |
| `func_150428D4` | `0x36c` |
| `func_15042C40` | `0x110` |

### `src/game/game_123D40.c`

Range `0xf6890:0xf6b00`; 2 entries, 624 bytes.
SHA-1: `a1321ff5ef431aa2bfaabcb514f233499fad32d6`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150F6890` | `0xcc` |
| `func_150F695C` | `0x1a4` |

## Integration result

Registered and integrated all reviewed members as raw ASM. The complete US
game overlay is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Integration passed on its
first attempt. This verifies layout preservation, not original filenames.
