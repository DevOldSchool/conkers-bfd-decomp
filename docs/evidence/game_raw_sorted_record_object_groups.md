# US sorted-record rendering and paired-object lifecycle groups

Evidence type: `structural_analysis`

These working source families retain navigation intervals from local `mkst/conker`
commit `3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`
(combined-image base `0x2D4B0`). Calls, shared records, and actual callback
selectors support ownership. Original filenames and exact historical compilation
unit limits remain unknown; offset names preserve that distinction.

## Sorted-record rendering: `0x17B500:0x17E080`

The four opening callbacks `1517B500`, `1517B6E8`, `1517B7A8`, and
`1517B7F8` transform the same packed position records. They are selected by
main renderer `1517BBAC`: the record selector is translated through `8008CF00`,
scaled by 12, and loaded from `8008CEBC` at `0x17C6DC`, followed by the
call at `0x17C6E8`. Owned slots 1, 2, 3 and 5 (`8008CEC8`, `8008CED4`,
`8008CEE0`, `8008CEF8`) are precisely those four local callbacks.

`1517B89C` recursively sorts the `0xE`-byte records in `800DDD18`, comparing
position component 0 or 4 according to `8008CEB4`. Renderer `1517BBAC`
sets that sort mode and invokes it. Resource cleanup `1517CFC4` uses the same
`800DDA90` and `800DD478` resources populated by setup `1517DE5C`; setup
also calls the main renderer. The renderer and later command path `1517D7B0`
share output state `800DDD20`, `800DDD58`, and `800DDD10`.

`1517D578` appends up to three `0x10`-byte records to `800DDD28`, counted
by `8008CEB0`; `1517D5FC` wraps it using actor position. `1517D690` consumes
that exact queue, calling `1517D074`, and is itself called by `1517D7B0`.
The final setter `1517E05C` writes the position triplet `800DD470:800DD474`,
which the main renderer reads at `0x17C4E8` onward and then clears. This
specific producer/consumer relationship supports the end boundary.

## Paired-object lifecycle: `0x108850:0x109410`

Constructor `15108850` creates two related objects through `1513B5E0`, copying
`0x24` bytes of custom state to object `+0x50` (a variable offset) plus `+0xF8`.
Its first descriptor (`sp+0xC0`) sets update selector 0 and draw selector 1;
the second (`sp+0x4C`) sets update selector 1 and draw selector 4. Engine
`1513B5E0` copies descriptors to object `+0x10`. Update dispatch reads `+0x11`
at `0x13B7E0`, loads `80089C18` at `0x13B7F8` and calls at `0x13B804`:
slots 0/1 are local `15108AB4/15108C38`. Draw dispatch reads `+0x12` at
`0x13B88C`, loads `80089C28` at `0x13B8AC` and calls at `0x13B8BC`:
slots 1/4 are local `15108D24/15109120`.

Both updates call local helpers `15108B80/15108BC0` and consume the custom
state initialized by the constructor. Its associated object uses `1516037C`
with selector 8 at descriptor `+1` (`0x108974`). That constructor copies six
bytes to object `+0xE`; update engine `15160400` reads `+0xF` and invokes
`8008B0F0` at `0x16045C/0x160468`. Slot 8 (`8008B110`) is local `15108E10`,
which follows the associated object pointer copied to custom state `+0x18`.

Helpers `15108FFC/151090DC` send events `0x1D/0x1E` to the two type lists
at `80088C50/80088C58`. Both owned lists contain exactly `0x38,0x54`,
the types selected by constructor `1513B5E0`. Local event handler `15109064`
is called directly by engine `1513BA78` at `0x13BAAC` for subtype 1; it
updates the same variable-offset custom state. This joins all 11 entries.

## Validation

The 25 entries cover 14,144 bytes. Every raw label agrees with the independent
US function index. Ordered spans, instruction words, delay slots and padding
match the owned US payload. No decoded conditional branch crosses any endpoint
in either direction; each boundary follows a complete return/delay-slot sequence
and alignment padding. Beta correlation supports continuity, not historical
filenames. No data, rodata or BSS ownership is assigned. Complete US overlay
byte equality gates integration; all entries remain raw ASM.

### `src/game/game_1A89B0.c`

Range `0x17b500:0x17e080`; 14 entries, 11,136 bytes.
SHA-1: `d62c0ff407416b83bd07dee2f76609cfa299dcce`.
debug: 14 correlations, 14 strong.
ects: 11 correlations, 10 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1517B500` | `0x1e8` |
| `func_1517B6E8` | `0xc0` |
| `func_1517B7A8` | `0x50` |
| `func_1517B7F8` | `0xa4` |
| `func_1517B89C` | `0x310` |
| `func_1517BBAC` | `0x1418` |
| `func_1517CFC4` | `0xb0` |
| `func_1517D074` | `0x504` |
| `func_1517D578` | `0x84` |
| `func_1517D5FC` | `0x94` |
| `func_1517D690` | `0x120` |
| `func_1517D7B0` | `0x6ac` |
| `func_1517DE5C` | `0x200` |
| `func_1517E05C` | `0x24` |

### `src/game/game_135D00.c`

Range `0x108850:0x109410`; 11 entries, 3,008 bytes.
SHA-1: `2319fd2b4990322551c87a3f1af501f9e2bc63b2`.
debug: 10 correlations, 10 strong.
ects: 9 correlations, 9 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15108850` | `0x264` |
| `func_15108AB4` | `0xcc` |
| `func_15108B80` | `0x40` |
| `func_15108BC0` | `0x78` |
| `func_15108C38` | `0xec` |
| `func_15108D24` | `0xec` |
| `func_15108E10` | `0x1ec` |
| `func_15108FFC` | `0x68` |
| `func_15109064` | `0x78` |
| `func_151090DC` | `0x44` |
| `func_15109120` | `0x2f0` |

## Integration result

The first full US overlay gate passed: all 2,072,880 bytes are identical,
SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Both groups are
integrated as mixed C/ASM; their 25 entries remain raw ASM.
