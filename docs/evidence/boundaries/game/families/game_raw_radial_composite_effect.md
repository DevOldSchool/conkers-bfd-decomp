# US radial renderer and composite particle effect

Evidence type: `structural_analysis`

This working source family narrows older navigation interval
`0xC8350:0xCB0E0` to `0xC88D0:0xCB0E0`, excluding the preceding resource
helpers and actor callback. The older interval comes from local `mkst/conker`
commit `3adf229175c037c771f251f169f9dd80ca306924`,
`conker/conker.us.yaml` (combined base `0x2D4B0`). Original filenames and
exact historical compilation units remain unknown.

## Structural evidence

Constructor `150C88D0` allocates type `0x31`, copies `0x30` descriptor bytes
to `+0x10`, initializes radial geometry and stores the per-segment work pointer
at `+0x360`. Type row `8008BE9C` in the common `0x34`-stride dispatch table
selects local update `150C8A68` and draw `150C8DB8` at `8008BE9C/8008BEA4`.
Both consume its descriptor, geometry and evolving radius fields.

The update indexes owned table `80088858` by descriptor byte `+0x3C`,
selecting local particle callbacks `150C99B4/150C9DC4`, and indexes
`80088864` by `+0x3D`, selecting local actor interaction callback `150C9BDC`.
The former indirect call is at `0xC8CDC`; the latter is at `0xC8D28`.
`150C9DC4` creates a particle through `15132A4C` with descriptor update 7;
the engine copies that byte to `+0x71`, so table slot `800898CC` selects
local `150CA07C` for that particle's motion.

Composite factory `150CA150` calls local `150C88D0` at `0xCA4F0` and
local burst helper `150CA930` at `0xCA878`. Its additional `1513C5B0`
children use update `0xC`, passed through `1513C350` to `+0x80`;
`80089C70 + 0xC * 4 = 80089CA0` selects local `150CA9D0`.

The composite factory and burst helper also call `1514C678` with selectors
`0x14/0x13` respectively in stack argument `+0x1C`. That engine reads the
selector at `0x14C724`, indexes `8008AA00`, and invokes it at `0x14C7EC`.
Owned slots `8008AA50/8008AA4C` therefore select local
`150CADD0/150CAA04`. These are the two subordinate particle emission
callbacks, not unrelated functions inferred from adjacency.

`150CAA04` passes descriptor update 9 to `15130374`; the generic particle
engine dispatches byte `+0x72` through `80089760`, selecting local
`150CAC28` at `80089784`. `150CADD0` passes descriptor update 4 to
`15132A4C`, selecting local `150CB008` at `800898C0`. Together these
constructor and selector paths connect all fourteen entries, including the
last particle update.

## Validation

All fourteen labels agree with the independent US index. Their spans total
10,256 bytes and match owned US instructions, delay slots and padding. Both
endpoints follow complete returns; no decoded conditional branch crosses
either boundary in either direction. No data, rodata or BSS ownership is
assigned. Full US overlay byte equality gates integration. All entries remain
raw ASM, not matched C.

### `src/game/game_F5D80.c`

Range `0xc88d0:0xcb0e0`; 14 entries, 10,256 bytes.
SHA-1: `2bc77471fb434e43581e46fd18ace39a0343b42b`.
debug: 10 correlations, 7 strong.
ects: 8 correlations, 5 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150C88D0` | `0x198` |
| `func_150C8A68` | `0x350` |
| `func_150C8DB8` | `0xbfc` |
| `func_150C99B4` | `0x228` |
| `func_150C9BDC` | `0x1e8` |
| `func_150C9DC4` | `0x2b8` |
| `func_150CA07C` | `0xd4` |
| `func_150CA150` | `0x7e0` |
| `func_150CA930` | `0xa0` |
| `func_150CA9D0` | `0x34` |
| `func_150CAA04` | `0x224` |
| `func_150CAC28` | `0x1a8` |
| `func_150CADD0` | `0x238` |
| `func_150CB008` | `0xd8` |

## Integration result

Registered and integrated all reviewed members as raw ASM. The complete US
game overlay is byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. Integration passed on its
first attempt. This verifies layout preservation, not original filenames.
