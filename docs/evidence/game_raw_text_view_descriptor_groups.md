# US text buffers, view setup and descriptor dispatch

Evidence type: `structural_analysis`

Three reviewed working groups cover 58 existing raw entries and 20,224 bytes.
The text and view groups refine broader upstream raw spans instead of
assigning all adjacent code to the same source. Names remain offset-derived;
original filenames and precise historical object ownership are not recovered.
The functions remain raw ASM.

## Extents and provenance

The local upstream `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924` supplies raw navigation ranges
in `conker/conker.us.yaml`, with combined base `0x2D4B0`. It groups text
with earlier effects in `0xCF140:0xD0650`, and view setup with later object
state in `0x10FEA0:0x1150B0`. The narrower endpoints below are justified
by the retail bodies, calls and tables. The descriptor range uses the
existing upstream `0x130280:0x1321D0` extent.

The owned US payload has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.

| Source under `src/game/` | US range | Entries | Bytes | Debug correlations (strong) | ECTS correlations (strong) |
| --- | --- | ---: | ---: | ---: | ---: |
| `game_FD1D0.c` | `0xcfd20:0xd0650` | 15 | 2,352 | 15 (15) | 0 (0) |
| `game_13D350.c` | `0x10fea0:0x112520` | 12 | 9,856 | 8 (7) | 5 (4) |
| `game_15D730.c` | `0x130280:0x1321d0` | 31 | 8,016 | 28 (14) | 24 (12) |

The beta counts use the corrected ECTS layout. Missing correlations do not
prove code absence. Correlations alone do not supply source boundaries.

## Text-buffer family: `game_FD1D0.c`

The opening `150CFD20` scans bytes to delimiter `0xBD` or zero.
`150CFD5C` finds the terminating zero; `150CFD84` uses the delimiter
scanner to return the span and next pointer; `150CFDB8` repeatedly calls
it to find the maximum span. `150CFE98` advances the active string segment,
flips the buffer index, and calls shared copier `150CFE3C`.

Constructor `150CFF10` uses the scanners, allocation helper `15149130`
and the same copier. Later constructors `150D0134`, `150D02B4` and
`150D04C4` all reuse it. `150D0034` indexes `800888A0` by the signed
byte at object `+0x4C`, loads a function pointer at `0xD0074`, and executes
`jalr` at `0xD0078`. Three consecutive table entries select the late
callbacks `150D01A0`, `150D032C` and final `150D0534`. These callbacks
work with the same embedded text/buffer layout and drawing services.
There are twelve direct inter-function call sites plus this demonstrated
indirect dispatch, connecting all parts of the group.

At `0xCFD20`, the preceding oscillating effect callback has returned and the
code switches to the string-scanning helpers. This endpoint is aligned in
both US and debug. All fifteen functions preserve relative offsets and their
`0x930` total span in debug `0xCE890:0xCF1C0`, including the preceding
return and final padding. There is no sufficiently established ECTS mapping
for this group. The earlier effect code `0xCF140:0xCFD20` stays unmapped.

## View setup family: `game_13D350.c`

The opening `1510FEA0` sets selected-view state and calls `151106A8`,
`15110544` and `151108C4`. Helpers `151103C8` and `15110600` share
`15110544`, which uses the selected-view services `1501A680/1501A6CC`.
The group repeatedly uses `80082FA0/80082FA4`, the selected view arrays
at `800BE620/800BE624/800BE628`, and compact state at `800DBEA8`.

The setup/cleanup pair `1511172C/15111858` manages the resource rooted
at `800DBE80`, also read by `15110CFC`. Final drawing controller
`15111AF4` calls `15110544`, early matrix helper `151102CC`, and
`15110CFC`. Runtime slots at `800891D8`, `800891E4` and `800891E8`
select `151103C8`, `15110600` and `15111AF4`.

The proposed end `0x112520` immediately follows the final controller's
return. The next routine begins a distinct object/position operation, using
`800DBEC0/80089234` and the object pool, followed by a later family using
`800DBEF0/800DBEF4`. Its strong debug counterpart starts at `0x118CD0`
after a returned, padded predecessor. This body/state transition supports a
narrower view-setup working group; the rest through `0x1150B0` stays raw
and receives no new boundary credit.

## Descriptor family: `game_15D730.c`

`15130280` chooses object types `0x2B/0x52/0x47`, allocates via
`15167A68`, copies `0x70` descriptor bytes, and initializes additional
state. `15130374` and `151303BC` wrap this constructor. Final
`15131EE4` returns to it and fills extra fields at `+0xA8`, connecting the
far end of the group back to the same constructor/layout.

Core update `151303EC` dispatches through `80089760` at `0x130A38`
and through `80089800` at `0x130A78`. Drawing controller `15130A9C`
uses `80089804` at `0x130B34` and directly calls `1513137C` and
`1513164C`. These controllers are selected together by three runtime
descriptors at `8008BD64/8008BD6C`, `8008C314/8008C31C` and
`8008C550/8008C558`.

The late wrappers `1513177C/151317C8` read object flag `0x4000` at
`+0x68`, optionally use its type byte at `+0x75`, and dispatch through
`80089814/80089844` at `0x1317B0/0x1317FC`. Those tables repeatedly
select the group's `1513173C/1513175C` lifecycle callbacks. The same
layout controls `15131C2C`, which dispatches through `80089878`.
The helper `151319C4` dispatches through `80089874` to `15131B7C`.

There are sixteen direct inter-function call sites and 43 owned-data
pointers to members. The demonstrated table consumers, shared descriptor
layout and constructor reuse join the early core and late callback family.
The final wrapper returns at `0x1321C4` with preserved padding before the
next entry at `0x1321D0`. The complete working extent is supported without
assigning its associated data tables to a source data section.

## Boundary checks and gate

Raw words, delay slots and padding equal the owned US payload. Existing raw
entries and spans cover each reviewed interval exactly and agree with the
current US function index. No decoded conditional branch crosses either end
of any interval, including the two new internal boundaries. Neighboring and
final returns were inspected. Successful reassembly and padding alone are not
proof of original source ownership; the relationships above provide the
working evidence. No data, rodata or BSS ownership is assigned.

The canonical raw splits must be recorded before supported source-unit
registration. Ordered skeletons and membership are then registered through
`./conker`, and complete-overlay byte equality gates integration.

## Integration result

All three groups integrate on the first complete-overlay attempt. The
2,072,880-byte US game binary has SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5` and equals the owned payload.
All 58 entries remain `raw_asm`, the units have `mixed` integration state,
and the reference comparison stays raw assembly. The excluded portions of
the two broader upstream ranges remain unmapped.

## Membership

### `src/game/game_FD1D0.c`

Range SHA-1: `3e7b66ef72113bc6aa35a50b1236baa4c0e7336b`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_150CFD20` | `0x3c` |
| `func_150CFD5C` | `0x28` |
| `func_150CFD84` | `0x34` |
| `func_150CFDB8` | `0x84` |
| `func_150CFE3C` | `0x5c` |
| `func_150CFE98` | `0x78` |
| `func_150CFF10` | `0x124` |
| `func_150D0034` | `0x8c` |
| `func_150D00C0` | `0x74` |
| `func_150D0134` | `0x6c` |
| `func_150D01A0` | `0x114` |
| `func_150D02B4` | `0x78` |
| `func_150D032C` | `0x198` |
| `func_150D04C4` | `0x70` |
| `func_150D0534` | `0x11c` |

### `src/game/game_13D350.c`

Range SHA-1: `66b2132fdcf3cb6f50d7835318a3c2a51cc7fb6f`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_1510FEA0` | `0x42c` |
| `func_151102CC` | `0x94` |
| `func_15110360` | `0x68` |
| `func_151103C8` | `0x17c` |
| `func_15110544` | `0xbc` |
| `func_15110600` | `0xa8` |
| `func_151106A8` | `0x21c` |
| `func_151108C4` | `0x438` |
| `func_15110CFC` | `0xa30` |
| `func_1511172C` | `0x12c` |
| `func_15111858` | `0x29c` |
| `func_15111AF4` | `0xa2c` |

### `src/game/game_15D730.c`

Range SHA-1: `389fbad8b9a93b685c241e2de373db84a0ab67d2`. Spans include preserved padding.

| Entry | Raw span |
| --- | ---: |
| `func_15130280` | `0xf4` |
| `func_15130374` | `0x48` |
| `func_151303BC` | `0x30` |
| `func_151303EC` | `0x6b0` |
| `func_15130A9C` | `0x8e0` |
| `func_1513137C` | `0x198` |
| `func_15131514` | `0x138` |
| `func_1513164C` | `0x60` |
| `func_151316AC` | `0x30` |
| `func_151316DC` | `0x30` |
| `func_1513170C` | `0x30` |
| `func_1513173C` | `0x20` |
| `func_1513175C` | `0x20` |
| `func_1513177C` | `0x4c` |
| `func_151317C8` | `0x4c` |
| `func_15131814` | `0x14` |
| `func_15131828` | `0xc0` |
| `func_151318E8` | `0x30` |
| `func_15131918` | `0x40` |
| `func_15131958` | `0x4c` |
| `func_151319A4` | `0x20` |
| `func_151319C4` | `0x138` |
| `func_15131AFC` | `0x40` |
| `func_15131B3C` | `0x40` |
| `func_15131B7C` | `0xb0` |
| `func_15131C2C` | `0x58` |
| `func_15131C84` | `0xc8` |
| `func_15131D4C` | `0x50` |
| `func_15131D9C` | `0x50` |
| `func_15131DEC` | `0xf8` |
| `func_15131EE4` | `0x2ec` |
