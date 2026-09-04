# US paired emission helpers

Evidence type: `structural_analysis`

Working source `src/game/game_1DBD40.c` covers `0x1AE890:0x1AECA0`,
three raw functions and 1,040 bytes. Both endpoints refine the older raw
navigation span `0x1ABE40:0x1AF5C0`, from local `mkst/conker` at
`3adf229175c037c771f251f169f9dd80ca306924`, `conker/conker.us.yaml`
(combined-image base `0x2D4B0`). This connected helper family is a working
structural boundary, without an original filename claim.

Opening `151AE890` takes a position and motion inputs, chooses an emission
variant using the shared random generator, and directly calls `151AE984`
or `151AEAB4`. Both helpers derive random motion, lifetime and appearance
arguments for their respective existing constructors `151D9014` and
`151DA6F8`. The first scales the supplied velocity; the second derives a
random direction using `151423D8`. Both receive the same position and
context byte selected by their common wrapper. These direct calls account
for all three members. No surrounding helper is included merely for using
the same general effect engine.

The start follows a return/nop at `0x1AE888/0x1AE88C`. The end follows
return/nop at `0x1AEC98/0x1AEC9C`. Both are 16-byte aligned. All raw
words equal the owned US code; the three labels agree with its function index,
their spans cover the interval exactly, and no decoded conditional branch
crosses either endpoint. All three have strong debug correlations; only one
has an ECTS correlation and it is not strong. No data/BSS ownership is assigned.
Complete US overlay equality gates integration; all entries remain raw ASM.

## Membership

Range SHA-1: `06c013a04133e21f99213ea63805a3b0aec825a4`.

| Entry | Raw span |
| --- | ---: |
| `func_151AE890` | `0xf4` |
| `func_151AE984` | `0x130` |
| `func_151AEAB4` | `0x1ec` |

## Integration result

The first full US overlay gate passed. All 2,072,880 bytes are identical to
the owned original payload (SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`).
The source is integrated with its raw ASM entries; no C match is claimed.
