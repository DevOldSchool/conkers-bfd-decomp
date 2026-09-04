# US buffered owner effect and stream callback triplet

Evidence type: `structural_analysis`

These narrower working families are drawn from the older local
`mkst/conker` navigation ranges at commit
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`.
The original filenames and exact historical compilation units remain unknown.

## Buffered owner effect: `0xCE150:0xCE740`

`150CE150` calls `1515FF74` with an 8-byte descriptor and `0x8F0` custom
bytes, then copies owner and buffered state to the result at `+0x18`.
The generic constructor copies that descriptor to object `+0xE`.
Its update selector is 1, draw selector 0, and event selector 2. The owned
US tables resolve these to all three local callbacks:

- Update table `8008B0D0`, index 1: `150CE200` at `8008B0D4`.
- Draw table `8008B0D8`, index 0: `150CE450` at `8008B0D8`.
- Event table `8008B0E4`, index 2: `150CE694` at `8008B0EC`.

The update works with the custom owner and buffer state. Draw copies buffered
records and consults the active display state; event handling compares or
transfers the stored owner identity and releases a matching object. The next
`150CE740` is a larger actor behavior and is deliberately excluded at its
aligned start. All four entries are accounted for by construction and dispatch.

## Stream triplet: `0x1AF270:0x1AF4D0`

`151AF270` creates a `1513418C` stream with emitter selector `0xA`:
stack byte `+0x47` relative to descriptor start `+0x1C`. The engine copies
it to object `+0x3B`, and table `80089A70` selects local `151AF338` at
owned slot `80089A98`. The callback forwards prepared position and emission
arguments to local `151AF388`, which creates output through `151D9014`.
The preceding `151AECA0` and following `151AF4D0` composite factories are
excluded; both narrower cuts are aligned complete-function boundaries.

## Mechanical review

Every raw word equals the owned US code image. Independent US beta-index CSV
membership and spans agree. The ranges are 16-byte aligned, without missing
or overlapping words or conditional branches crossing their boundaries.
Beta correlations supplement this US structural review. All seven entries
remain `raw_asm`; no matched-C claim is made.

### `src/game/game_FB600.c`

Range `0xce150:0xce740`; 4 entries, 1,520 bytes.
SHA-1: `337d1edc973c1fd39a96a93f44f8ea1cf103785d`.
debug: 2 correlations, 1 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_150CE150` | `0xb0` |
| `func_150CE200` | `0x250` |
| `func_150CE450` | `0x244` |
| `func_150CE694` | `0xac` |

### `src/game/game_1DC720.c`

Range `0x1af270:0x1af4d0`; 3 entries, 608 bytes.
SHA-1: `d816470df62470f9d304f1ad88ad07880406c3e1`.
debug: 3 correlations, 1 strong.
ects: 2 correlations, 1 strong.

| Entry | Raw span |
| --- | ---: |
| `func_151AF270` | `0xc8` |
| `func_151AF338` | `0x50` |
| `func_151AF388` | `0x148` |

## Integration result

Integrated on the first attempt. The complete US game overlay remains byte-identical: 2,072,880 bytes, SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All entries remain raw ASM; no C matches were added.
