# Actor model-matrix buffer helpers

Names describe matrix operations without identifying models or mask purpose.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `1502C380` | `actor_matrix_buffer_reset_for_frame` | 60 |
| `1502DB20` | `model_get_adjusted_matrix_count` | 100 |
| `1502E474` | `actor_matrix_buffer_pack_fixed` | 80 |
| `15034728` | `actor_zero_masked_model_matrix_bases` | 192 |
| `150347E8` | `actor_pool_zero_masked_model_matrix_bases` | 120 |

The first three are in `src/game/game_58F80.c`; the last two are in
`src/done/game/game_61950.c`.

## Frame buffer and adjusted count

Reset selects `D_800C3E80[D_800BE9C0]`, copies it to allocation cursor
`D_800C3E88` and start pointer `D_800C3E8C`, and clears used-matrix count
`D_800C3E7A`. Original `1501905C` calls it at `150190D0`. This does not clear
conversion-state byte `D_800C3E90`; that write occurs separately at `1502BF0C`.

The count getter returns unsigned-halfword `D_800C4ED0[model]`, subtracting
four for IDs 3B, 75, 82, 88, 90, 96, 98, 9C, 9D, 9F, A0, B1, B2 and B4.
No identity or reason for these exceptions is assigned. Original loader
`1503CF20` derives the table entry from model-header size +0x14 divided by
16. Original `1502DB84` consumes the adjusted count for count*0x40 buffer
space, stores the buffer at actor+0x1D4, and accumulates the used count.
`15184150` also walks that count of 0x40-byte matrices and reads translation
floats +0x30/+0x34/+0x38. There is no model-index guard or nonnegative clamp.
The count definition's s32 argument and existing u8 caller declaration remain
unchanged.

## Masked float bases before fixed-point packing

With nonnull actor+0x1D4 and nonzero mask +0x9C, `15034728` walks indices
from min(adjusted count-1,31) down to zero. Each selected bit zeros the nine
float entries at matrix offsets 00/04/08, 10/14/18 and 20/24/28. Translation
and fourth-column values are untouched. Original `15034F30` temporarily
substitutes another matrix array, calls this helper at `15035674`, and
restores the original pointer at `15035680`. No visibility, animation or
bone-identity meaning is inferred from the mask.

The pool wrapper runs only when `D_800BEAC0` is zero. It traverses all 25
actor records in [800CC2D0,800D121C), stride 0x32C, invoking the helper for
records with nonzero state word +0 and mask +0x9C. The global gate's broader
meaning stays unnamed. The registered span retains all three trailing zero
words at `15034854`/`15034858`/`1503485C`.

Original frame routine `1501878C` calls this pool pass at `15018C64`, then
calls the packing wrapper at `15018C6C`. For a nonzero unsigned used count,
packing passes the selected frame buffer and count to `150A9984`; it then
sets `D_800C3E90` to one, including on the zero-count path. The original
callee multiplies twelve affine floats by 65536, uses `cvt.w.s`, and packs
integer/fraction halves in place with 0x40-byte stride, supplying a fixed
fourth column 0,0,0,1. This is destructive, not a general sixteen-float
conversion. There is no already-packed check, used-count reset or idempotence
promise.

## Evidence and acceptance

Original helper bodies are in `reference/game/us/asm/2BAD0.s` and `344A0.s`;
the conversion callee is in `A81A0.s`. The original count jump table at
`80096DF8` corroborates thirteen subtract-four destinations; ID 3B has a
direct branch. Registered spans total 552 bytes.
