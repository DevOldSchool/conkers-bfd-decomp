# Main C matching continuation

## Baseline and scope

This continuation starts from main commit
`2bf889bfc905e02359a3a9320832101a4b2ebfdd`, after the model-integration merge.
The baseline contains 2,633 accepted US C functions. The earlier game-matching
work's 38 functions / 14,244 bytes are already in that baseline and are not
counted again here. No source boundaries, compiler settings or shared headers
are changed.

Before new matching, the pinned toolchain smoke checks, an existing accepted
C function's independent CURRENT (0), RSP payload checks, complete US ROM
build, refreshed game-code/mapped-rodata comparison, progress and whitespace
checks passed.

## First batch: main stubs and scalar controls

Five functions match their entire independent registered US spans:

| Function | Source | Bytes | Source evidence |
| --- | --- | ---: | --- |
| `func_80011E88` | `init_EB00.c` | 12 | Void stub with one unused full-width argument home |
| `func_80011FA0` | `init_11FA0.c` | 16 | Full-width selector store |
| `func_80011FDC` | `init_11FA0.c` | 16 | Independent sibling selector store |
| `func_800085A4` | `init_8180.c` | 20 | Void stub with three full-width homes; existing `func_100085A4(s32, s32, s32)` game declaration corroborates the contract |
| `func_8000E75C` | `init_B1B0.c` | 20 | Arithmetic right shift and word-global update |

Every function matched on its first source form. `finish` confirmed CURRENT
(0), reviewed source-unit symbol layout, progress and whitespace. Owning units
remain in progress; a matched function is not a completed or integrated unit.

The clean five-function `verify-batch` returned `BATCH_COMPLETE`, including the
full US ROM build, 1,328 tests run with 12 skipped, metadata, progress and
whitespace. The new accepted total is **5 functions / 84 bytes**, and the US C
inventory is **2,638 functions**. No accepted IDs remain pending in this batch.

## Preserved candidates and negative findings

- `func_80003920`: the natural byte-global clear and an independently reviewed
  explicit-return form both score 60. The store is before `jr` instead of in
  its delay slot. The simpler candidate is preserved with original ASM active.
  Existing accepted main setters use the same compiler route successfully;
  this is not evidence for changing compilation settings.
- `func_8000390C`: the natural zero return reproduces the operations but scores
  100 over the full 20-byte registered span, which includes one trailing `nop`
  beyond the standalone candidate's 16-byte object. It is preserved inactive;
  no padding or reference change was introduced.
- `func_80007A24`: the existing SDK `__osPopThread` handwritten body explains
  the selected raw routine. It was left unchanged without a C trial or a new
  original-assembly acceptance claim.
- Independent reviews of earlier `func_150B17DC` (230) and `func_1506D2E8`
  (650) found their actual frames and stack homes already exact. Remaining
  allocation/scheduling differences do not justify repeating exhausted local
  forms. Both prior best candidates remain unchanged.

Detailed source snapshots, scores, hypotheses and command logs are retained in
the private task ledger. No permutation, artificial storage, volatile access,
narrow-formal inference, handwritten C-body assembly or weakened gate was used.

## Second batch: selector transitions and reset

`func_80011FB0` (44 bytes) and `func_80011FEC` (52 bytes) are newly accepted.
The conditional setter first scored 45 with seven register-only differences.
Naming the genuine previous selector value before testing it recovered the raw
value/address register roles and CURRENT (0). Its return type remains `void`;
no caller or declaration established a return-old contract. The reset's
right-associated assignment chain matched on its first source form, preserving
the raw reverse store order and address-register roles.

The owning unit's larger `func_80012020` (1,344 bytes) remains deferred. The
ready starter could not process its omitted jump-table input, so the candidate
was translated manually using the full raw body, bounded table/data context
and independently reviewed helper contracts. Two real two-float aggregates
preserve the initializer copies, while coherent two-element global arrays
represent the indexed output storage. The first source scored 591 with the
correct 0x70 frame, instruction count and branch structure.

Independent candidate-object `.mdebug` review identified source homes at
entry-SP offsets -4 (volume), -8 (selector), -16/-24 (aggregates), -28 (index)
and -32 (scale). Moving only the existing loop-index declaration above volume
predicted the exact live homes at SP+0x68, +0x5C and +0x54. That one revision
removed all 23 stack-related rows and improved the score to 495. The actual
scale spill stayed exact at +0x48, distinct from its abstract debug home +0x50.
No storage was added and this does not establish a universal declaration rule.

The remaining 18 rows are ten FP register/operand differences, six table or
array-alias operands, and two duplicate-byte-mask versus move instructions.
The helper parameters remain full-width: an extra byte mask is not qualifying
narrow-ABI evidence. Candidate table relative case starts agree with the raw
case-block positions, but this is not independent jump-table acceptance. The
best 495 source is preserved inactive; it contributes no accepted function or
byte count.

The clean related-family batch rechecked both earlier setters and accepted
the two new members: `BATCH_COMPLETE`, full US ROM match, 1,328 tests run with
12 skipped, metadata/progress/whitespace passed. The owning unit remains in
progress. This adds **2 functions / 96 bytes**, giving **7 / 180 bytes** since
the fresh baseline and **2,640** accepted US C functions. No batch IDs remain
pending at this checkpoint.
