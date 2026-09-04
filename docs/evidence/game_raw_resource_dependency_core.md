# US resource descriptor and dependency core

Evidence type: `structural_analysis`

This working source family narrows older navigation interval
`0x9CA10:0x9DD10` to `0x9CA10:0x9D180`. The older interval comes from local
`mkst/conker` commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined base `0x2D4B0`). The following effect-command
handlers are excluded. Original filenames and historical compilation units
remain unknown.

## Structural evidence

The first four accessors select fields `+0/+8/+0xA/+4` of the same
`0x14`-byte descriptor table at `80087430`. `1509CA98` searches `0xCC`
entries by their masked `+4` value, and `1509CB68` counts non-null `+0`
entries across that exact table (`80087430:80088420`).

Recursive query `1509CBD4` reads each descriptor's `+0xC` halfword dependency
list (`8008743C`, stride `0x14`), terminated by `0xFFFF`, and checks each
resource bit in the buffer addressed by `800D2E4C`. Local `1509CCB4` passes
that same list and its own function pointer to `1509CE64`, whose indirect
call recursively visits dependencies and writes state 3 into `800D2E70`
and the corresponding availability bit. `1509CC94` is a direct wrapper.

`1509CCF4` traverses the other dependency list at descriptor `+0x10`
(`80087440`), updates the same state and bitset, and calls `1509CCB4`.
`1509CDDC` repeatedly runs that traversal across all `0xCC` descriptors until
no new state is added. These are concrete links between the descriptor
accessors and dependency operations.

The final three functions own a related loaded table at `800D2FB0`:
`1509CF28` loads and relocates it; `1509D054` frees and clears it;
`1509D08C` queries its halfword resource lists and checks every referenced
resource against the same `800D2E4C` availability bitset. That shared query
contract connects this loader lifecycle to the dependency core. The next
entry `1509D180` instead begins the effect-command switch and is excluded.

## Validation

All fifteen labels agree with the independent US index. Their spans total
1,904 bytes and match owned US instructions, delay slots and padding. Both
boundaries follow complete returns; no decoded conditional branch crosses
either boundary in either direction. No data, rodata or BSS ownership is
assigned. Full US overlay byte equality gates integration. All members remain
raw ASM, not matched C.

### `src/game/game_C9EC0.c`

Range `0x9ca10:0x9d180`; 15 entries, 1,904 bytes.
SHA-1: `7f80b6659725e30b32eccb9ea7adcf84cb2ad5d9`.
debug: 10 correlations, 5 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_1509CA10` | `0x20` |
| `func_1509CA30` | `0x20` |
| `func_1509CA50` | `0x28` |
| `func_1509CA78` | `0x20` |
| `func_1509CA98` | `0xd0` |
| `func_1509CB68` | `0x6c` |
| `func_1509CBD4` | `0xc0` |
| `func_1509CC94` | `0x20` |
| `func_1509CCB4` | `0x40` |
| `func_1509CCF4` | `0xe8` |
| `func_1509CDDC` | `0x88` |
| `func_1509CE64` | `0xc4` |
| `func_1509CF28` | `0x12c` |
| `func_1509D054` | `0x38` |
| `func_1509D08C` | `0xf4` |

## Integration result

Integrated on the first build attempt. The complete US game overlay is
byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw ASM.
