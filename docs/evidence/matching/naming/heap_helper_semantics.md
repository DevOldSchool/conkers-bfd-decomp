# Heap allocation and tag-lifecycle helpers

Source: `src/main/init_3C40.c`. The original s32 ABI is retained; allocator,
free and tag-setter siblings remain numeric and unmatched.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `80003C40` | `heap_alloc_from_start` | 44 |
| `80004250` | `heap_process_deferred_frees` | 184 |
| `80004308` | `heap_free_tags_1_to_4` | 172 |
| `8000440C` | `heap_refresh_largest_free_block` | 100 |

## Allocation direction

The four-argument wrapper calls raw `80003C6C` with zero as argument four,
forwarding its own fourth argument as argument five. Zero selects the
free-list head `D_800380B8`, follows `nextFree` and allocates from the first
fitting block's low-address aligned edge. This is first-fit, not best-fit.
The arguments retain their existing ABI: size, tag, alignment selector and
failure mode all remain s32, as does the returned address.

Original alignment tables at `asm/us/data/2AB40.data.s` support selector
values 0..4 for 4, 8, 16, 64 and 8192-byte alignment. The selector is unchecked.
Failure mode zero invokes the failure handler on exhaustion; nonzero permits
returning zero. Exactly one also rejects when the cached largest-free size is
below 0x7800. The alias does not add validation or change failure behavior.

## Deferred release and explicit tag set

`80004250` masks interrupts, walks the block chain, frees tag 2, decrements
tags 3/4 and leaves others alone, then restores the prior interrupt mask.
Original `151D5E30` marks non-null pointers in four resource slots with tag 3;
main `80009CBC` marks a released audio buffer with tag 4. These producers
establish deferred release, without a promise of a fixed number of frames. Game `15019158` calls this pass.
The existing traversal reads the current block's next field after freeing;
no safety rewrite or new traversal guarantee is introduced.

`80004308` saves the chain head before calling `85042D50`, then frees blocks
whose tags are 1, 2, 3 or 4 under the preserved interrupt-mask sequence.
It does not release every nonzero tag: 0xFF survives. Original game caller
`15007B5C` precedes later initialization, but the numeric-tag name does not
claim a complete scene reset. The callback and snapshot order are unchanged.

## Largest-free cache

`8000440C` follows the free list, uses signed strict-greater comparisons and
stores the selected block and maximum size in `D_800380B0` and `D_8002AC30`.
Equal-size ties retain the first selected block. The allocator refreshes this
cache when consuming the previously cached largest block. This helper does
not itself mask interrupts.

If no positively sized block is encountered, its local selected pointer is
uninitialized. Original code allocates eight stack bytes, writes the selected
pointer slot only on an improvement and unconditionally loads it for the final
pointer store. The empty/no-positive-size result is not specified as NULL;
this behavior is preserved, not repaired. The three terminal NOPs remain in the registered span.

## Evidence and acceptance

Original `reference/us/asm/3C40.s`, allocator/free callees, runtime-alias
callers and alignment data support the roles. Existing unit boundaries are in
[allocator/transfer/controller
evidence](../../boundaries/main/main_allocator_transfer_controller_boundaries.md). Registered
spans total 500 bytes.
