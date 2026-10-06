# US resource parser, actor state and dispatch groups

Evidence kind: `structural_analysis`. These are working source families, with generic offset filenames. Original filenames and historical compilation units remain unknown. Every member remains raw ASM.

## Resource-record parser: `0x15920:0x15E80`

`15015920` loads the resource extent selected from `80082F80`, walks variable-length records and calls local `15015A38` for each record (`0x159BC`). The parser resolves the selected output array through `80085994` and writes record-derived data. The caller advances using the record's big-endian length at bytes 4 through 7. The preceding independent reset of `800CBD4C` at `0x15910` is excluded.

## Actor render pair: `0x36570:0x36C70`

`150368C4` selects the actor in `800CC2D0`, examines the attached object's type, obtains the relevant actor resource and calls local `15036570` at `0x36A9C`. Both operate on the selected actor and the same `800C3FC0/800C3FC4` rendering state. The caller returns an advanced display-list pointer; the helper builds the associated render data. The range contains only these two connected entries.

## Input-driven display state: `0x3F9F0:0x40350`

`1503FB08` resets `80084488/8C/90/94` and the float `800C6850`. `1503FB40` reads and updates those same fields while rendering the active display and directly calls local input helper `1503F9F0` at `0x3FCE8`. That helper turns controller bytes from `800BE728` into signed step outputs, using a repeat counter at `80084484`. The reset, input helper and stateful display entry form one family.

## Actor command state: `0x80200:0x80500`

`15080200` resets `800D1928/2C/30`. `15080228` reads command packets, selects an actor from `800CC2D0`, and calls local `15080430`. The latter interprets the mode and writes `800D1928` while changing actor state. `15080348` reads that same mode and `800D192C`, uses timing state, and updates actor fields `+0x1FF/+0x134/+0x135`. All four entries connect through the command-to-mode-to-update lifecycle.

## Guarded spatial query: `0xA34B0:0xA3A70`

`150A34B0` checks object bytes `+0x14/+0x15`, then forwards the original query arguments to local `150A3504` at `0xA34E4`. The latter computes spatial values from the object's coordinates and caller vectors. No other entries intervene between wrapper and implementation.

## Per-actor interpolation state: `0x12D6F0:0x12DD50`

All three entries index 104-byte records at `800DC2C0` with actor byte `+0x23D`. `1512D748` expands a selected ten-byte descriptor from `800895D0` into float state, derives interpolation rates and clears its phase/timer fields. `1512D980` advances and consumes that record, calling local `1512D6F0` when resetting. The reset clears the output vector and rate state and sets phase `+0x50` to five. Shared record indexing, initialization and consumption identify the family.

## Actor action dispatcher pair: `0x12E8E0:0x130230`

`1512E8E0` evaluates the current actor action and calls local `1512FE00` at `0x12EA28`, passing the same actor and selected action argument. `1512FE00` dispatches through the owned jump table `800A376C` and sets the actor's action using the same external action helper `15123934`; cases update actor flags and action parameters. These are the only two entries in the interval.

## Actor callback selection: `0x192800:0x192920`

`15192800` calls local `151928B0` at `0x192814`. The helper accepts specific actor type bytes at `+4`, returning a selector through its second argument. The caller uses that selector plus the actor state to resolve a callback from `8008F860` and invoke it. Both members participate in this type-to-callback dispatch.

## Resource render-data setup core: `0x127B0:0x12F90`

`150127B0` allocates and initializes the resource's render data, directly calling local `15012C84` twice and `15012ED8`. The former processes 16-byte records through shared `800BE510/800BE528`; the latter walks eight-byte display commands and fills colour/index state at `800BE530/550/564`. All three are connected by this initialization call graph. The unrelated reset at `0x12F90`, which clears `800DF7D0` and following state, is excluded.

## Validation

Endpoints are 16-byte aligned and indexed function starts. Raw words match the owned US image, and entry spans exactly cover each interval. Whole-image conditional-branch scanning finds no crossing edges. Independent CSV membership and beta correlations follow; correlations support entry identity, not historical compilation-unit proof.

### `src/game/game_42DD0.c`

Range `0x15920:0x15e80`; 2 entries, 1,376 bytes.
SHA-1: `0cd554e72c254c7c7bee9a15fb17782a965fce9b`.
debug: 2 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15015920` | `0x118` |
| `func_15015A38` | `0x448` |

### `src/game/game_63A20.c`

Range `0x36570:0x36c70`; 2 entries, 1,792 bytes.
SHA-1: `322a13ca39d9cd30f0c3d4e417b01939ce9f54fe`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15036570` | `0x354` |
| `func_150368C4` | `0x3ac` |

### `src/game/game_6CEA0.c`

Range `0x3f9f0:0x40350`; 3 entries, 2,400 bytes.
SHA-1: `77a1292da5204bc9dff3a58683e19bf7af7d9e49`.
debug: 2 correlations, 2 strong.
ects: 3 correlations, 3 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1503F9F0` | `0x118` |
| `func_1503FB08` | `0x38` |
| `func_1503FB40` | `0x810` |

### `src/game/game_AD6B0.c`

Range `0x80200:0x80500`; 4 entries, 768 bytes.
SHA-1: `69ded035b4f70344bf3d5769cf1875fa3dbb1026`.
debug: 2 correlations, 2 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15080200` | `0x28` |
| `func_15080228` | `0x120` |
| `func_15080348` | `0xe8` |
| `func_15080430` | `0xd0` |

### `src/game/game_D0960.c`

Range `0xa34b0:0xa3a70`; 2 entries, 1,472 bytes.
SHA-1: `42661d34ef6f334a9112b348d5d198bffcdd570a`.
debug: 1 correlations, 1 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150A34B0` | `0x54` |
| `func_150A3504` | `0x56c` |

### `src/game/game_15ABA0.c`

Range `0x12d6f0:0x12dd50`; 3 entries, 1,632 bytes.
SHA-1: `f5d2cea1d84e9913e0b1ab745452f7c0fe62235a`.
debug: 3 correlations, 3 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1512D6F0` | `0x58` |
| `func_1512D748` | `0x238` |
| `func_1512D980` | `0x3d0` |

### `src/game/game_15BD90.c`

Range `0x12e8e0:0x130230`; 2 entries, 6,480 bytes.
SHA-1: `60c9df67cf32523efb1676c743dbac1a254afa65`.
debug: 0 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1512E8E0` | `0x1520` |
| `func_1512FE00` | `0x430` |

### `src/game/game_1BFCB0.c`

Range `0x192800:0x192920`; 2 entries, 288 bytes.
SHA-1: `8df6c4e44205b7aedf27f4b0d5a781c812c61dfd`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15192800` | `0xb0` |
| `func_151928B0` | `0x70` |

### `src/game/game_3FC60.c`

Range `0x127b0:0x12f90`; 3 entries, 2,016 bytes.
SHA-1: `18d807cc80220e5daa23f479c6bcc968c4953468`.
debug: 3 correlations, 3 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150127B0` | `0x4d4` |
| `func_15012C84` | `0x254` |
| `func_15012ED8` | `0xb8` |

## Integration result

All nine reviewed units integrated as raw ASM wrappers. The complete 2,072,880-byte US game overlay is byte-identical (SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`). No C match is claimed.
