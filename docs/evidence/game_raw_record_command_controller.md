# US record-backed actor command controller

Evidence type: `structural_analysis`

The working source group `0x96970:0x97910` retains an older navigation
interval from local `mkst/conker` commit
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`
(combined base `0x2D4B0`). Shared state and local calls support this family;
the original filename and exact historical compilation unit remain unknown.

## Structural evidence

Initializer `15096970` clears `0x6C` bytes at `800D2DC0` and resets active
word `800D2DB4`. Local `150969A0` scans the first byte of records with stride
`0x24` and reports whether an earlier record is active. It does not copy or
shift those records. Local `15096D08` walks exactly three records with that
stride, calling `15096A68` for an active record.

State routine `15096A68` selects the same record by index, updates its state
byte and timer, and owns the transition flag `800D2DB4` and saved scalar
`800D2DB8`. It writes a per-index motion scalar to `800D2E30` at
`0x96BE0:0x96C08`. Final helper `15097798` checks that same active word and
uses the corresponding `800D2E30` scalar to adjust actor position vectors
`+0x2A4` and `+0x2F8`. This connects the final helper to the state lifecycle.

Command handler `15096D78` initializes the indexed `800D2DC0` record from
command arguments, then calls both the earlier-record query and state routine
at `0x96F18/0x96F28`. Other cases set and clear the same transition flag.
Query handler `1509759C` reads the indexed record's state byte at
`0x97648:0x97664` and returns related actor measurements. Owned data points
to these handlers at `800884F4` and `800884B8`; the grouping rests on their
concrete state access and local calls, not those pointers alone.

## Validation

All seven labels agree with the independent US index. Their spans total
4,000 bytes and match owned US instructions, delay slots and padding. Both
endpoints follow complete returns; no decoded conditional branch crosses
either boundary in either direction. No data, rodata or BSS ownership is
assigned. Full US overlay byte equality gates integration. All members remain
raw ASM, not matched C.

### `src/game/game_C3E20.c`

Range `0x96970:0x97910`; 7 entries, 4,000 bytes.
SHA-1: `a0033fbc23f6993449809b1d04b34f3f8fb4d878`.
debug: 5 correlations, 4 strong.
ects: 0 correlations, 0 strong.

| Entry | Raw span |
| --- | ---: |
| `func_15096970` | `0x30` |
| `func_150969A0` | `0xc8` |
| `func_15096A68` | `0x2a0` |
| `func_15096D08` | `0x70` |
| `func_15096D78` | `0x824` |
| `func_1509759C` | `0x1fc` |
| `func_15097798` | `0x178` |

## Integration result

Integrated on the first build attempt. The complete US game overlay is
byte-identical: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw ASM.
