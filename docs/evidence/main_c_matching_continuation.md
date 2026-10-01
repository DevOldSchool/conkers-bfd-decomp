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
