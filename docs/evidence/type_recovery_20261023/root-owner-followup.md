# D_800DBFF0 allocation-root follow-up (US, 2026-10-23)

Reusing the existing shared 0x9A0 owner in one more source reduces the current
measured deferred score sum by **47**, from **2,792,176 to 2,792,129**.
No candidate regresses and no new match is claimed. The PR total is **2,497**
against its original 2,794,626 baseline, with one earlier new C match.

## Baseline and complete measurement

Continuation base: `1b715cfc23fd1a648c5f72c556636728ec2cd591`.
The comparison point is [render-owner-final.tsv](render-owner-final.tsv),
SHA-256 `ba1cf07b425bdb1efe9d7807b3a7c586ceb3e5a0f83ccfaded410e2b3e9178b6`.
Scores use its measured `new` column; stored annotations are not measurements.
The [new full exact sweep](root-owner-followup-final.tsv) visits the identical
1,383 deferred rows: 1,334 scores, the same 49 compiler failures and the same
four pre-existing zeros. Only the candidate below changes. The scorer takes
141.4 seconds, excluding research, audit, clean validation and Git delivery.

| Scope | Candidates scored | Before -> after | Reduction | New matches |
| --- | ---: | ---: | ---: | ---: |
| `func_15005290`, `src/game/game_32740.c` | 1 | 2,519 -> 2,472 | 47 | 0 |
| Every candidate in the retained source | 3 | 3,189 -> 3,142 | 47 | 0 |
| Entire current baseline | 1,334 | 2,792,176 -> 2,792,129 | **47** | **0** |

## Shared owner and original evidence

The [earlier root recovery](root-owner.md) established
`extern struct108 *D_800DBFF0` in `include/game_view.h` from matched
`func_80011BB8` and original GAME allocation/readers. This follow-up adopts
that existing header in `src/game/game_32740.c`, removes its byte-pointer
copy and casts the existing integer-address allocator result to `struct108 *`.
The allocation loop computes its byte-compatible callee argument as
`(u8 *)&D_800DBFF0[index]` instead of adding a manually maintained byte offset.
The old offset local and updates remain; no statement or control flow is
reshaped. No new shared structure, field name, ABI or owner-member retype
is introduced.

Independent `reference/game/us/asm/5290.s` proves the ownership relation:
allocation count times 0x9A0 at 0x15005318..0x15005334, storage through
D_800DBFF0 at 0x15005354, use of the computed per-owner pointer for
`func_150054C4` at 0x15005410..0x1500541C, and stride advancement at
0x1500542C. Matched `func_80011BB8` independently iterates the same 0x9A0
owners (`reference/us/asm/EB00.s`). The allocator's existing integer-return
ABI remains intact; this change recovers the root pointee and indexing.

Paired pinned-IDO output shows different initialization scheduling and operand
order for the owner-address addition. The score improves despite the frame
growing **0x70 -> 0x78**, against reference 0x70. The candidate remains
nonzero. It has not been activated as canonical C or taken through `finish`.
The other candidates, `func_150054C4` and `func_15005818`, remain 485 and 185.
Before/after objects and disassembly are preserved in the ignored ledger.

## Examined and restored trials

Eleven previously untested source adoptions were measured in three bounded
cohorts. [Every comparison and decision](root-owner-followup-trials.tsv)
is retained. Ten source files were restored exactly to the continuation
commit before the full sweep and validation. No regressing source remains.

| Trial / source | Measurement and decision |
| --- | --- |
| `game_E7DE0.c`, `game_1A6360.c`, `game_1A89B0.c` | Proven float fields and indexed yaw; all candidates unchanged. Restore. |
| `game_F4D20.c` | `func_150C79BC` 983 -> 1,008 (+25); other candidate has the same baseline compile failure. Restore. |
| `game_FA360.c` | `func_150CD7F8` 1,565 -> 4,295 (+2,730); two others unchanged. Restore. First five-source cohort: 13 rows/12 scored, 14,974 -> 17,729. |
| `game_10D7B0.c`, `game_14C3F0.c`, `game_1A20A0.c` | Float position and owner-index adoption; all candidates unchanged. Restore. |
| `game_1944C0.c` | `func_15167310` 1,435 -> 2,215 (+780); nine others unchanged. Restore. Second four-source cohort: 20 scored, 27,763 -> 28,543. |
| `game_83300.c` actor-swap root | `func_15062800` 4,339 -> 4,329 (-10); source cohort 65,873 -> 65,863. Four baseline prototype failures prevent the every-candidate-compiles gate. Restore; no ten-point gain claimed. |
| `game_32740.c` allocation root | Retained 47-point improvement above. Third two-source cohort before restoring actor-swap source: 40 rows/36 scored, 69,062 -> 69,005. |
| Owner child at 0x3D4 | Initializer copies actor 0x31C into this member; actor-swap uses a child with a byte at 0x197. Existing shared owner instead calls it `struct127 *`, while actor 0x31C names `struct126 *` and local views differ. Leave unchanged pending a coordinated child/status audit. |
| Owner numeric fields at 0x2AC and 0x5D4 | Float readers and integer word views coexist. No speculative numeric conversion or whole-owner merge. |

The pending render-width trial from the preceding continuation was also
closed before root work: `func_1512B53C` remains 4,675 and the required
bounds adoption still changes `func_1512B1B8` 5,577 -> 5,652 (+75).
`game_157840.c` was restored exactly. This was a new width hypothesis, not
another bounds-only attempt; no gain is credited.

## Validation and limits

The sole retained source contains **zero matched C functions**; there is no
matched function in that file to nominate or recheck. Its three functions stay
under their original GLOBAL_ASM pragmas. A four-pair compiler audit covers the
canonical source and every individually activated candidate. All compile.
The canonical file and changed candidate have zero cfe warnings. The existing
warning 709 at `func_15123070(arg0)` in `func_15005818` is identical on both
sides after normalizing temporary source paths. The initial audit stopped on
that path-only comparison difference; the corrected comparison passes.
No candidate source repair or new warning is hidden.

`CONKER_JOBS=1 ./conker verify-batch func_15155780 func_150C99B4` uses two
existing matched users of the same shared root and reports **BATCH_COMPLETE**.
The clean integration covers retained assembly, linked data, layout, progress
and whitespace; 1,062 tests pass, six skipped. The batch log has zero cfe
warnings. The integrated GAME image is **2,072,880 bytes**, byte-identical to
the independently extracted reference, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
No pending batch IDs. [Machine-readable validation](root-owner-followup-validation.json).

No assembly, compiler flags, shared tooling, inventory or asset reconstruction
input changed. No permutation was run. This proves the US GAME image and
mapped data; no new asset-reconstruction claim is made. Runtime implementation
is only `src/game/game_32740.c`; the other tracked files are evidence.
The durable ignored ledger is
`build/us/manual-attempts/root-owner-followup-20261023/`.

## Next five leads

Weights are measured deferred scores, overlap and are not predicted gains.
The allocation candidate does not change these five symbol cohorts.
Do not repeat the recorded neutral or rejected forms without new evidence.

| Priority | Contract | Scored dependents | Score weight |
| ---: | --- | ---: | ---: |
| 1 | Remaining D_800BE628 render-owner users; honor bounds and ABI blockers | 22 | 58,600 |
| 2 | D_800DBEF4 0xA0 placed-object records and tagged views | 22 | 56,384 |
| 3 | func_15145128 vector/pointee contract | 13 | 45,265 |
| 4 | D_800B0DF0 level-header pointer views | 13 | 43,380 |
| 5 | D_800D2104 resource/script table entries | 12 | 36,026 |
