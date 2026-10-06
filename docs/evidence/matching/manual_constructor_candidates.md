# Bounded constructor candidates after cloud recovery (US)

This source-only pass prepared three typed candidates in their existing mixed
units. None matched. Each best candidate is preserved behind the supported
deferred marker with the original `GLOBAL_ASM` active. No source boundary,
shared header, compiler setting, raw assembly, or match gate was changed.
No padding to force stack size, new volatile accesses, or automated permutation
was used.

## `func_151A8B20`, `game_1D5FD0.c`

The working 0x58-byte payload reflects the copied 0x28-byte input, fields
initialized by the raw constructor, and later owner/position/node accesses.
Its initial candidate scored 840. Inlining the lifetime/timed conditional
expressions restored the original prefix and improved the score to 469.

Remaining differences are the 0xB0 rather than 0xA8 frame, associated stack
slots, and the branch scheduling of the node store followed by a flags load.
The first local-scalar shape is exhausted; this is not match evidence.

## `func_151B09BC`, `game_1DD500.c`

The 0x98-byte payload contains eleven three-word node records. An indexed loop
recovered the raw compiler's partial unrolling and 0xE0 frame, improving the
pointer-counted-loop candidate from 8989 to 1476. A nested conditional and
chained-zero probe scored 1680 and was discarded. Classification branches,
marker placement and initializer-store ordering remain different.

The independent raw `func_151491F4` calls the allocator `func_15149130` and
returns without modifying v0; this caller consumes that returned pointer.
The candidate expresses that observed pointer return in a source-local
prototype. The older wrapper's C declaration is void and was not changed by
this pass. No unset-register placeholder is used as a value.

## `func_151C8FCC`, `effects/effects_sight.c`

The raw call to `func_151407D0` has ten arguments: the parameter-block pointer,
100, the descriptor pointer, four zero words, one, and the last two input
arguments. Floating registers live during initialization are not extra
floating-point arguments. The typed candidate uses that pointer-first ABI.

The first descriptor/parameter-block candidate scored 1783. A physical-order
initializer probe scored 11109 and was discarded. Remaining differences include
the 0xF8 rather than 0xF0 frame, constant/FPR scheduling, and flag-expression
code. The physical-order pattern that helped other constructors does not
establish equivalence here.

## Validation

After deferral, the incremental complete US game-code image and all mapped
external rodata remained byte-identical to the owned ROM. The 1,068-test suite
passed (12 skipped), and generated-progress and whitespace checks passed.
There are no new focused matches or pending batch IDs in this candidate-only
pass; an empty match batch was not run.
