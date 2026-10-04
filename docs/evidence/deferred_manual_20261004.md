# Deferred matching: 2026-10-04

Latest five candidates; US, manual ASM-to-C. Shared dependency changes: no.

| Function | Source under src/game/ | Best valid full-span CURRENT | Revisions |
| --- | --- | --- | --- |
| 15047700 | game_71820.c | 15907 → 12607; matrix ABI/FP lifetimes | 2 |
| 151CBC60 | effects/effects_sight.c | 2885 → 1330; cached conversion scale | 2 |
| 150A81A0 | game_D5650.c | 2015; corrected 64-byte copy stride | 1 |
| 150ADA68 | game_DAE50.c | 5000; unsigned RNG shifts | 1 |
| 150ADACC | game_DAE50.c | 1520; widen seed before addition | 1 |

15 candidate finish calls. Invalid: A81A0=2020, ADA68=4605, ADACC=1100.
Best valid candidates deferred; canonical ASM retained; no new match credit.
Local matrix/getter declarations repaired; no shared header/compiler changes.
CBC60 frame/stack exact; payload-base folding and FP allocation remain.
Three handwritten 64-bit functions hit IDO o32 lowering barriers.
Seven affected callers passed CURRENT0/layout/progress/whitespace.
47B80 focused100 lacks one final nop: committed and edited focused objects
have identical text/relocations (text SHA256 424dfb4ae1f78d6988fb9ddfcd3331ff8eed30a777be928dd7af1edf236e257d).
Focused stripping removes raw neighbors and changes final alignment; no padding added.
Mixed object supplies all 128 bytes at the correct offset, including both padding nops.
Clean verify-batch: BATCH_COMPLETE; US GAME/mapped rodata equal ROM.
1,823 tests passed, 37 skipped; repository whitespace passed.

Speed leads: flag canonical ABI conflicts before starters, retain resumed-body context,
and triage handwritten 64-bit ISA before matching. CBC60 scale reuse helped;
these workflow changes remain unimplemented and unbenchmarked.
Pending [1500E738 mapping proof/proposal](game_3ba70_jump_table.md); linker unchanged.
1515942C shared contract and 150A6360 full-span/FPU blockers remain.
Commit identity: DevOldSchool-AI-Agent. No personal memory used.
