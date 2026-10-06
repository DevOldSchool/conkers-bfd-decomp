# US paired owner-effect stream families

Evidence type: `structural_analysis`

These two working families retain separate older navigation intervals
`0xC5DC0:0xC66F0` and `0xC66F0:0xC7020` from local `mkst/conker`
commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined base `0x2D4B0`). Original filenames and
exact historical compilation units remain unknown. All beta correlations are
weak; the following US ownership and callback links support the grouping.

## First family: owner slots `+0x58/+0x5C`

Owned action slots `8008B014/8008B018` select `150C5DC0/150C5F40`.
The common action dispatcher `15158D2C` indexes the `8008AFD0` table and
passes its same owner in `a0` at `0x158F58:0x158F64`. The two local actions
create children through `150C6460/150C5F94`, store them in owner slots
`+0x58/+0x5C`, or refresh a request byte in an existing child.

`150C6460` calls `1513C73C` with update 8 and cleanup 2, then copies
`0x20` custom bytes to `+0xB0`, including the owner. The underlying
`1513C350` stores those selectors at `+0x80/+0x81`. Dispatch tables
`80089C70/80089CA8` therefore select local `150C5E0C/150C5EFC` at
`80089C90/80089CB0`. The update consumes its custom request and timing;
cleanup clears the exact owner's `+0x58` child slot, clears the back-pointer,
and calls `1513F6C0`.

`150C5F94` creates the second child through `1513418C`, copies its owner
and request state to `+0x58`, and chooses emitter 4, condition 1, release 2.
The engine copies descriptor `0x30` bytes to `+0x10`; its `+0x3B/+0x3C/
+0x3D` selectors reach local `150C60D8/150C63EC/150C6410/150C6438`
through slots `80089A80/80089AA4/80089AB4/80089ADC`. The emitter
creates randomized particles; the condition consumes the refresh byte at
`+0x5C`; both release wrappers clear owner slot `+0x5C` before the generic
release. The release tables are based at `80089AAC/80089AD4`, and the
condition table at `80089AA0`.

## Second family: owner slots `+0x6C/+0x70`

Owned action slots `8008B01C/8008B020` similarly select
`150C66F0/150C6870`. They use their distinct owner slots `+0x6C/+0x70`
and call local factories `150C6D90/150C68C4`.

`150C6D90` selects update 9 and cleanup 3 through the same engine and
copies its own `0x20` custom bytes to `+0xB0`. Slots `80089C94/80089CB4`
select `150C673C/150C682C`; cleanup clears owner slot `+0x6C`.
`150C68C4` selects emitter 5, condition 2 and release 3. Corresponding slots
`80089A84/80089AA8/80089AB8/80089AE0` select
`150C6A08/150C6D1C/150C6D40/150C6D68`. Its condition consumes the
same child request field, while its release wrappers clear the second family's
owner slot `+0x70` (`owner + 0x58 + 0x18`). Distinct constants, model-anchor
inputs and owner slots keep the two ten-entry families separate.

## Validation

All twenty labels agree with the independent US index. Each range contains
2,352 bytes, total 4,704, matching owned US instructions, delay slots and
padding. Every endpoint follows a complete return; no decoded conditional
branch crosses a boundary in either direction. No data, rodata or BSS
ownership is assigned. Full US overlay byte equality gates integration.
All members remain raw ASM, not matched C.

### `src/game/game_F3270.c`

Range `0xc5dc0:0xc66f0`; 10 entries, 2,352 bytes.
SHA-1: `67880e635f97204ab3f0fcc429cc780f9aeffe4f`.
debug: 10 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C5DC0` | `0x4c` |
| `func_150C5E0C` | `0xf0` |
| `func_150C5EFC` | `0x44` |
| `func_150C5F40` | `0x54` |
| `func_150C5F94` | `0x144` |
| `func_150C60D8` | `0x314` |
| `func_150C63EC` | `0x24` |
| `func_150C6410` | `0x28` |
| `func_150C6438` | `0x28` |
| `func_150C6460` | `0x290` |

### `src/game/game_F3BA0.c`

Range `0xc66f0:0xc7020`; 10 entries, 2,352 bytes.
SHA-1: `c4dbb7b4b91caf36b7b5136d36a6f567842d0b17`.
debug: 10 correlations, 0 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C66F0` | `0x4c` |
| `func_150C673C` | `0xf0` |
| `func_150C682C` | `0x44` |
| `func_150C6870` | `0x54` |
| `func_150C68C4` | `0x144` |
| `func_150C6A08` | `0x314` |
| `func_150C6D1C` | `0x24` |
| `func_150C6D40` | `0x28` |
| `func_150C6D68` | `0x28` |
| `func_150C6D90` | `0x290` |

## Integration result

Both groups integrated on the first build attempt. The complete US game
overlay is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All twenty entries remain raw ASM.
