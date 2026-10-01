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
the private task ledger. In the first batch, no permutation, artificial storage, volatile access,
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

## Third batch: sound-control records

Three functions are newly accepted in `init_EB00.c`:

- `func_80011E94` (36 bytes): full-width boolean test and two byte stores,
  including the observed early return; first source form matched.
- `func_800112BC` (84 bytes): typed four-byte queue record, full-width formals
  and real count snapshot. The initial 660 source reloaded the count after byte
  stores. Preserving the raw once-loaded count removed that alias-driven reload
  and recovered CURRENT (0).
- `func_8001147C` (84 bytes): the initial full-width formal plus normalized
  local scored 365. The pre-existing active runtime-alias declaration
  `s32 func_1001147C(u16)` in `src/game/game_13F9D0.c`, outside its deferred
  caller body, supplies the narrow contract; the caller passes a `u16` sound
  field. Using that declared contract reduced the score to 10. Reversing the
  source integer-equality operands recovered the sole remaining branch-register
  order and CURRENT (0). The formal was not narrowed from a store instruction.

The same group preserves the following nonmatches:

- `func_8000853C` and `func_80008570` retain 225 each. Exact SDK/library and raw
  caller evidence establish the get-state result, single player input and
  queue setter's actual pointer argument. The generated starters' incidental
  register arguments were rejected. The existing full-width wrapper contracts
  remain; the incoming argument-home differences are unresolved.
- `func_80010F30` retains 248 with verified seven-argument forwarding and a
  returned sound handle. Full-width existing contracts and explicit use-site
  casts were retained instead of unsupported formal narrowing.
- `func_8000EBC4` improved 320 to 125 when its real value snapshot was moved
  before the timer branch, matching raw load order. A named step snapshot was
  code-neutral and discarded. Fourteen register rows remain.
- `func_800038E0` improved 845 to 410 by expressing the observed hardware write
  through its direct MMIO address. Only the genuine hardware pointee is
  volatile; the RAM globals are not. This is a semantic MMIO qualification,
  not an allocation technique. Independent review found no evidence for a
  signedness or extra-volatility experiment to defeat the remaining constant
  reuse. The conditional whole-unit alignment lead for `func_8000390C` remains
  unaccepted until this genuine companion matches; no padding was added.

The clean batch included the three new functions plus existing `80011E88`
and `800085A4` regressions. It returned `BATCH_COMPLETE`: full US ROM match,
1,328 tests run with 12 skipped, and metadata/progress/whitespace passed.
This adds **3 functions / 204 bytes**, giving **10 / 384 bytes** since the
fresh baseline and **2,643** accepted US C functions. Source units remain in
progress or raw as recorded; no new unit completion is claimed. No accepted
IDs remain pending at this checkpoint.

## Fourth batch: scalar controls and guarded lookups

Five related members of `init_B1B0.c` are newly accepted:

| Function | Bytes | Source evidence and attempts |
| --- | ---: | --- |
| `func_8000E8C4` | 44 | Full-width bit test and word flag clear; first form matched |
| `func_8000E770` | 48 | Independently nullable word outputs followed by flags read, retaining alias-sensitive order; first form matched |
| `func_8000E0F8` | 60 | Guarded pointer lookup and aligned state word; 410 to 0 by normalizing the existing full-width formal before the call instead of only in its argument expression |
| `func_8000BBE8` | 64 | Initial-state callback with three unused argument homes and a proven three-word helper call; first form matched |
| `func_8000E8F0` | 68 | Forwarded full-width selector, guarded leading record word and unsigned-byte table read; first form matched |

The raw `func_8000B1B0` body consumes incoming a0, so the final wrapper explicitly
forwards its argument rather than adopting the starter's guessed no-argument
contract. The existing runtime-alias declaration supports its `s32` result.
The adjacent `8000E704` body establishes the three real arguments and boolean
return used by the callback. No formal narrowing or shared dependency change
was needed.

All five passed independent full-span CURRENT (0), reviewed symbol layout,
progress and whitespace. The clean batch also rechecked existing `8000E75C`:
`BATCH_COMPLETE`, full US ROM match, 1,328 tests run with 12 skipped, and
metadata/progress/whitespace passed. This adds **5 functions / 284 bytes**,
giving **15 / 668 bytes** since the fresh baseline and **2,648** accepted US
C functions. The source unit remains in progress and no accepted IDs remain
pending at this checkpoint.

## Fifth batch: shared record fields and updates

Five further `init_B1B0.c` members matched on their first source forms:

| Function | Bytes | Recovered behavior |
| --- | ---: | --- |
| `func_8000CBA8` | 72 | Independently guard two table records, store the input halfword and duration, retaining pointer-table reloads |
| `func_8000E134` | 72 | Preserve the signed upper-bound test, 16-byte table stride and two accepted masked modes |
| `func_8000E704` | 88 | Guard a shared-record lookup and forward its low index byte and two full-width parameters |
| `func_8000CD40` | 96 | Signed approach/clamp arithmetic, including the negative-result guard and conditional step read |
| `func_8000E40C` | 96 | Clamp before lookup, then update the proven word fields according to the record's signed leading word |

The source-local partial record now includes independently observed index/id,
owner and child pointers, word fields at 0x2C/0x30 and halfwords at 0x4E/0x50.
Unused gaps retain only the offsets established by the raw accesses. The
previous word-only zero test at 0x60 is now a pointer-null test on the same
field; its machine code was explicitly revalidated. No shared header changed.

Two related pointer loops remain inactive candidates. `func_8000B1B0` improved
1655 to 290 after an explicit sentinel exit avoided the compiler's loop
transformation; a base-pointer return cast was code-neutral. Its missing
initial input relocation and register allocation remain. `func_8000B294`
improved 1935 to 765 to 140: the sentinel exit removed unrolling, then direct
primary-record expressions removed a redundant retained address. Its complete
96-byte instruction/control shape is now exact, while pointer-register
allocation and address-initializer ordering differ. Independent review of the
retained object found only real cursor and child state; no further unsupported
source experiment was proposed. Neither candidate contributes a new match.

The clean batch checked all five new matches and all six earlier accepted
members of the modified source unit. `BATCH_COMPLETE` confirms the full US
ROM match, 1,328 tests run with 12 skipped, metadata, progress and whitespace.
This adds **5 functions / 424 bytes**, giving **20 / 1,092 bytes** since the
fresh baseline and **2,653** accepted US C functions. The unit remains in
progress and no accepted IDs remain pending at this checkpoint.
