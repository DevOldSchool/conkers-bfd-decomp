# US effect dispatch and resource lifecycle engine

Evidence type: `structural_analysis`

The working source group `0x147740:0x147DA0` retains the older navigation
interval from local `mkst/conker` commit
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`
(combined base `0x2D4B0`). Structural evidence supports this common engine
family; original filenames and exact historical compilation units are unknown.

Constructor `15147A80` chooses type `0x22` or `0x4D` from descriptor flag
`0x40`, allocates base `0xA0` plus custom storage, and copies the opening
`0x1C` descriptor bytes to object `+0x10`. It stores update/step/draw selectors
at `+0x2F/+0x30/+0x31`, custom pointers at `+0x98/+0x94`, initializes
resource state `+0x84`, and allocates per-view buffers at `+0x3C` plus `+0x4C`.

Owned type rows `8008BB90/8008C44C` both select local update `15147740`,
draw `15147C4C`, event `15147D1C`, and cleanup dispatchers
`151479E0/15147A30`. The update checks lifetime and selectors before
dispatching through `8008A200/8008A23C`; draw uses `8008A2A4`.
Event and cleanup select by copied descriptor field `+0x20` through
`8008A390/8008A2F0/8008A340`.

Cleanup table slot zero is local `151478F4/15147928`, also used by several
other entries in those tables. Both call local resource cleanup `151478D0`
on `+0x84`, then buffer cleanup `1514795C`, before generic object release.
The buffer cleanup walks the same per-view `+0x3C` pointers using
`80082FA0`, and separately frees `+0x4C`, matching constructor allocation.

Final helper `15147D64` broadcasts events to owned list
`800A5760 = [0x4D,0x22]`, exactly the two constructor types. Thus all eleven
entries form the constructor, dispatch, resource cleanup and event API.

All eleven raw labels agree with the independent US function index. Their
1,632-byte span matches owned US instructions, delay slots and padding. Both
endpoints follow complete returns, and no decoded conditional branch crosses
either endpoint in either direction. No data, rodata or BSS ownership is
assigned. Full US overlay byte equality gates integration; all members remain
raw ASM, not matched C.

### `src/game/game_174BF0.c`

Range `0x147740:0x147da0`; 11 entries, 1,632 bytes.
SHA-1: `190d5e870f8cf5943ad6fdd26db0d75da552763d`.
debug: 2 correlations, 2 strong.
ects: 1 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15147740` | `0x190` |
| `func_151478D0` | `0x24` |
| `func_151478F4` | `0x34` |
| `func_15147928` | `0x34` |
| `func_1514795C` | `0x84` |
| `func_151479E0` | `0x50` |
| `func_15147A30` | `0x50` |
| `func_15147A80` | `0x1cc` |
| `func_15147C4C` | `0xd0` |
| `func_15147D1C` | `0x48` |
| `func_15147D64` | `0x3c` |

## Integration result

The first full US overlay gate passed: 2,072,880 identical bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. This group is integrated
as mixed C/ASM, with all 11 entries remaining raw ASM.
