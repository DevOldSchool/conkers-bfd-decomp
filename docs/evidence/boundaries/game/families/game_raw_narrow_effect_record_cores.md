# US narrow effect and record cores

Evidence kind: `structural_analysis`. These smaller working families split existing raw navigation ranges. Original filenames and exact historical object boundaries are unknown; alignment alone is not the membership evidence.

## Timed effect pair: `0xDB9E0:0xDBD70`

`150DB9E0` configures an effect through `15152F70` and creates a timer/update object through `151491F4` at `0xDBB34`, lifetime `0x1E`, update selector zero. The wrapper forwards that selector to `15149130`; update slot `8008A4E8` in the owned ROM targets local `150DBC60`. This callback issues the continuation effect through the same `15152F70` interface and consumes the timer's owner selector. The next entry `150DBD70` starts a separate descriptor-based element constructor and is excluded.

## Ten-record animation core: `0xC8350:0xC8730`

`150C8350` updates ten 10-byte records through `800BE4E0`, adjusts signed rate/current/target fields at `+2/+4/+6/+8`, and reflects the current value into the range `0:0x500`. `150C84F4` is its direct callback wrapper. `150C851C` chooses new target rates at record `+8`; `150C8600` reads the same ten records, uses current `+4` and type `+0` to select resources from `80088810`, and emits ten segment commands. The four routines share the exact record storage, stride and fields. The unrelated actor-oriented callback at `0xC8730` is excluded.

## Owner emitter triplet: `0xBA4C0:0xBA930`

`150BA4C0` creates a timer with update `0x52`, event `0x3F`, and 12 custom bytes containing owner identity and accumulated time (`0xBA508:0xBA548`). Owned update/event slots `8008A630/8008A9D4` resolve to local `150BA55C/150BA8F0`. The update consumes the copied owner/time state and emits child effects. The event wrapper passes object `+0x28/+0x2C` to the owner-event helper `15149514`. The next ground-position helper at `0xBA930` begins a separate family and is excluded.

## Validation

Every endpoint is 16-byte aligned and is an indexed function boundary. All raw words agree with the owned US image, entry spans cover each interval exactly, and a whole-image conditional-branch scan finds no crossing edges. Independent CSV membership and beta correlations follow. These maps retain generated ASM and claim no C matches.

### `src/game/game_108E90.c`

Range `0xdb9e0:0xdbd70`; 2 entries, 912 bytes.
SHA-1: `eb2cecb43dc00ed0513b3183fd3b4778d4359060`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150DB9E0` | `0x280` |
| `func_150DBC60` | `0x110` |

### `src/game/game_F5800.c`

Range `0xc8350:0xc8730`; 4 entries, 992 bytes.
SHA-1: `09d31de87db6d7dc61b49553d50a084e97e00e82`.
debug: 2 correlations, 2 strong.
ects: 2 correlations, 2 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C8350` | `0x1a4` |
| `func_150C84F4` | `0x28` |
| `func_150C851C` | `0xe4` |
| `func_150C8600` | `0x130` |

### `src/game/game_E7970.c`

Range `0xba4c0:0xba930`; 3 entries, 1,136 bytes.
SHA-1: `23d7e52631a2d6b4ce5d7ebbf913f8d00a8d41fb`.
debug: 3 correlations, 2 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150BA4C0` | `0x9c` |
| `func_150BA55C` | `0x394` |
| `func_150BA8F0` | `0x40` |

## Integration result

Passed the first integration attempt. The complete US game overlay remains byte-identical: 2,072,880 bytes; SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
