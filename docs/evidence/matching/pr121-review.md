# PR121 review: deferred scope and local dispositions

Published head: `555402fd3932816ba0c03540964e0cd395e7dfae`; verified tree: `e430c4b8047383a494db470700b18af0a9628371`.
Original batch base: `a0e1bd680a6c1f9b2dac1809197d35fb5256569b`.
This document describes a later local review revision; it does not relabel that
published tree or assert that its CI covered subsequent edits.

The published commit changes **72 function inventory entries**: ten new C
matches, one already-matched member relocated with its completed source unit,
and **61 deferred entries**. Among those deferred entries, **34 function bodies
across 32 files** changed; the other 27 bodies are unchanged. Deferred candidates
remain inside `#if 0`, with original assembly active. Their score changes are
not additional matches and do not establish C correctness or integration.

The complete machine-readable audit, old/new reasons, source-body hashes and
recovered run receipts are in [pr121-review.json](pr121-review.json).
The inventory comparison is `git diff a0e1bd680a6c1f9b2dac1809197d35fb5256569b
555402fd3932816ba0c03540964e0cd395e7dfae -- progress/functions.json src`.

## Nine review dispositions

1. Fresh canonical `finish` measured **151A931C=530, 150CFE3C=130,
   150F4CFC=310**. Their base/published bodies have identical SHA256 hashes;
   only wrapper scores and metadata changed. Historical 830/235/410 prose
   was stale, not a new source improvement. Supported resume/finish/defer
   transactions now reconcile reasons and measured scores. The old reason
   and score remain preserved in the audit; their original discrepancy is not
   attributed to an unproved compiler change.
2. Both follow-ups have final `budget_complete` receipts at 6,000 iterations.
   Seed 202610151913 (1511F990) made 5,276 compiler calls, 5,223 successful;
   no accepted improvement beyond 20. Seed 202610151912 (1515C534) made 936
   calls, 726 successful, and its log reports an internal permuter assertion:
   `Anonymous declarations cannot happen in functions`. This is not a clean
   exhaustive-search claim. No accepted improvement beyond 30; no worker is
   running. Transient job claims are replaced with these bounded results.
3. Retain correctness repairs. **1502D54C** measures 530; its base expression
   probes at 135 but adds a potentially overflowing signed index product to
   the address of a scalar global as if it were an array. No object-bound or
   index-range proof authorizes restoring it. The current numerical unsigned
   address operation follows the 32-bit target model. The pre-existing
   volatile output access still requires a semantic contract before acceptance.
   **15055D48** measures 620. Its base form now probes at 440; 340 is only the
   historical stored score. Subtracting pointers to distinct/scalar objects
   and signed `1 << index` lack sufficient bounds proofs. The retained unsigned
   difference and `index & 31U` encode the MIPS variable-shift low-five-bit rule.
   Neither regression is hidden or counted as a match.
4. Full deferred scope is listed below. For **15178EFC**, raw instructions
   `0x15178F50..0x15178F78` reload D_800DD440 only after the non-null callback
   and null store. The C global is nonvolatile. On the null path, no function
   call or memory write occurs before the extra reload, so the previously read
   value cannot change in the C abstract execution. On the non-null path the
   reload remains after both call and store, preserving possible alias effects.
   Moving it back inside the if with the same pointer-typed store probes at 75;
   retaining the semantically redundant null-path reload measures 30. No
   asynchronous/volatile behavior is assumed for this ordinary global.
   **Scope recommendation:** retain the already-published, explicitly audited
   deferred history for this review, and keep future candidate search changes
   in separate work. Blindly reverting the broad candidate work would restore
   known arithmetic/aliasing hazards. No published history is rewritten and
   all original/probed candidates are preserved locally. Narrowing the existing
   PR can be a separate maintainer decision with a bounded follow-up patch.
5. The literal evidence now names the actual publication commit and verified
   tree, separates historical acceptance from this revision, and provides
   repository commands instead of an inaccessible local-package dependency.
6. Existing INFO placements are unchanged. Their 16-byte ELF envelopes include
   4-byte payloads and 12 zero object-alignment bytes; only the payloads are
   owned/compared to ROM. Neighboring constants are not owned or overwritten.
   See [the literal evidence](../data-layout/game_second_batch_literals.md)
   for precise future-pool constraints and required approval before expansion.
7. Removed the only source occurrences of the unused `extern f32 D_800A352C`
   and `extern f32 D_800A6520` declarations. Canonical finish remains zero for
   151254F4 (160 bytes) and 1515F040 (108 bytes).
8. Applied one `u8 *entry` assigned at the start of each **1507C22C** iteration.
   Unsigned address stepping, memory accesses, short-circuiting and call order
   remain unchanged. Probe and canonical finish both retain 60; still deferred.
9. The `(u8)arg1` alternative in **1514AD9C** probes at 214; the retained
   `((u8 *)&arg1)[3]` measures 14. On this 32-bit big-endian target, byte 3 is
   the low byte of the signed argument representation. `u8` is unsigned char,
   so inspecting that byte is permitted character aliasing. Taking its address
   causes the compiler to use the real argument home and recover the raw byte
   load (`lbu $t1, 0x7F($sp)` at raw 0x1514AF34); a value cast changes register/stack scheduling. This is target-specific,
   not portable C across endian/width models, and remains a nonzero candidate.

## Complete deferred audit

Base/published numbers below are **stored historical scores**. Review numbers
are fresh canonical measurements where the review explicitly revisited an item.
A dash means it was not remeasured in this review. The read-only command
`CONKER_JOBS=1 ./conker probe <function>` measures any retained deferred body
without activating it or altering inventory. A probe is not acceptance.

| Function | Source | Base | Published | Review | Body/scope change |
| --- | --- | ---: | ---: | ---: | --- |
| `func_15135480` | `src/game/effects/blood.c` | 20 | 20 | — | Function body unchanged; deferred reason/score history updated. |
| `func_15010538` | `src/game/game_3D9A0.c` | 135 | 120 | — | Function body unchanged; deferred reason/score history updated. |
| `func_151C94D4` | `src/game/effects/effects_sight.c` | 20 | 20 | — | Function body unchanged; deferred reason/score history updated. |
| `func_1505A3A8` | `src/game/game_83300.c` | 20 | 20 | — | Function body unchanged; deferred reason/score history updated. |
| `func_150039BC` | `src/game/game_305D0.c` | 10 | 10 | — | Unsigned numerical +8 replaces potentially overflowing signed address addition. |
| `func_15075400` | `src/game/game_A28B0.c` | 60 | 60 | — | Unsigned numerical cursor increment replaces unproved signed product/pointer extent. |
| `func_1509B4A0` | `src/game/game_C8950.c` | 10 | 10 | — | Function body unchanged; deferred reason/score history updated. |
| `func_1515C534` | `src/game/game_1897A0.c` | 50 | 30 | 30 | Unsigned countdown; product local scoped to the branch that consumes it. |
| `func_151DC034` | `src/game/game_2062D0.c` | 125 | 125 | — | Function body unchanged; deferred reason/score history updated. |
| `func_1514D15C` | `src/game/game_179F30.c` | 150 | 150 | — | Function body unchanged; deferred reason/score history updated. |
| `func_1515E43C` | `src/game/game_18A8F0.c` | 280 | 140 | — | Names consumed second-color and first-alpha snapshots without moving intervening writes. |
| `func_1501E73C` | `src/game/game_49D30.c` | 70 | 50 | — | Names the actual u16 entry-kind read; count reload paths retained. |
| `func_1502D54C` | `src/game/game_58F80.c` | 135 | 530 | 530 | Unsigned numerical actor address; retains a known score regression for correctness (item 3). |
| `func_15083E0C` | `src/game/game_AEB40.c` | 30 | 10 | — | Byte-buffer pointer/cursor types and inline byte lookup replace integer storage. |
| `func_15081574` | `src/game/game_AE1D0.c` | 555 | 555 | — | Function body unchanged; deferred reason/score history updated. |
| `func_150CFE3C` | `src/game/game_FD1D0.c` | 235 | 130 | 130 | Function body unchanged; deferred reason/score history updated. |
| `func_150CFE98` | `src/game/game_FD1D0.c` | 10 | 10 | — | Function body unchanged; deferred reason/score history updated. |
| `func_15183BA4` | `src/game/game_1B0740.c` | 305 | 305 | — | Function body unchanged; deferred reason/score history updated. |
| `func_151580B0` | `src/game/game_185560.c` | 20 | 20 | — | Unsigned +0xF8 address arithmetic before target-width signed conversion. |
| `func_151D7724` | `src/game/game_204660.c` | 635 | 635 | — | Function body unchanged; deferred reason/score history updated. |
| `func_151D7830` | `src/game/game_204660.c` | 10 | 10 | — | Function body unchanged; deferred reason/score history updated. |
| `func_15132A88` | `src/game/game_15F680.c` | 165 | 40 | — | Names attachment flag; corrects helper call to its one pointer argument. |
| `func_150E4CBC` | `src/game/game_111670.c` | 175 | 135 | — | Unsigned wrap for products/timers, with consumed factor reuse. |
| `func_15178EFC` | `src/game/game_1A6360.c` | 75 | 30 | 30 | Pointer-typed null store and unconditional nonvolatile reload; see item 4 proof. |
| `func_1517B6E8` | `src/game/game_1A89B0.c` | 40 | 30 | — | Removes initial scale snapshot and reads the source directly before any write. |
| `func_15108B80` | `src/game/game_135D00.c` | 60 | 60 | — | Unsigned timer subtraction before signed-result interpretation. |
| `func_15108D24` | `src/game/game_135D00.c` | 50 | 50 | — | Uses an actual 16-float matrix and element13 instead of separate work.saved storage. |
| `func_151A4D88` | `src/game/game_1D0840.c` | 30 | 30 | — | Compares pointer-valued identities through pointer-typed accesses. |
| `func_1519203C` | `src/game/game_1BF090.c` | 210 | 210 | — | Signed low-half conversion replaces alias-violating s16 access to an s32 local. |
| `func_15155FD4` | `src/game/game_182C30.c` | 50 | 50 | — | Numerical unsigned traversal replaces stepping beyond a scalar global declaration. |
| `func_1509CCF4` | `src/game/game_C9EC0.c` | 35 | 10 | — | Numerical table/byte addresses; removes a transient byte-pointer local. |
| `func_150C673C` | `src/game/game_F3BA0.c` | 12 | 12 | — | Function body unchanged; deferred reason/score history updated. |
| `func_150F4CFC` | `src/game/game_121A20.c` | 410 | 310 | 310 | Function body unchanged; deferred reason/score history updated. |
| `func_15166118` | `src/game/game_193430.c` | 200 | 200 | — | Function body unchanged; deferred reason/score history updated. |
| `func_1511F990` | `src/game/game_14CE30.c` | 370 | 20 | 20 | Earlier added initialization and consumed mode snapshot; no loop/call changes. |
| `func_1511ED84` | `src/game/game_14BC30.c` | 155 | 155 | — | Function body unchanged; deferred reason/score history updated. |
| `func_151AAA4C` | `src/game/game_1D6E80.c` | 20 | 20 | — | Unsigned product/addition preserves wrapping timer arithmetic. |
| `func_151087FC` | `src/game/game_135780.c` | 120 | 120 | — | Function body unchanged; deferred reason/score history updated. |
| `func_151152A8` | `src/game/game_142560.c` | 170 | 170 | — | Unsigned difference/product wrapping; float-conversion domain still needs future review. |
| `func_151162D4` | `src/game/game_1435C0.c` | 155 | 25 | — | Consumed narrowed-height reuse and unsigned phase update; float domain remains deferred. |
| `func_1518EF54` | `src/game/game_1BBFC0.c` | 20 | 20 | — | Function body unchanged; deferred reason/score history updated. |
| `func_151A77C0` | `src/game/game_1D4AC0.c` | 120 | 120 | — | Unsigned timestep product before intended low-half conversion. |
| `func_151A787C` | `src/game/game_1D4AC0.c` | 105 | 105 | — | Unsigned timestep product before existing low-half storage. |
| `func_150E0D90` | `src/game/game_10E240.c` | 110 | 10 | — | Uses direct stage-global condition; subsequent post-call stage reload retained. |
| `func_150E0BE0` | `src/game/game_10E090.c` | 205 | 45 | — | Narrows the updated counter to s16 under the recorded 0..354 range. |
| `func_150EA490` | `src/game/game_117940.c` | 20 | 20 | — | Numerical phase address and unsigned phase-step product. |
| `func_151A9060` | `src/game/game_1D6510.c` | 55 | 55 | — | Function body unchanged; deferred reason/score history updated. |
| `func_151A931C` | `src/game/game_1D6570.c` | 830 | 530 | 530 | Function body unchanged; deferred reason/score history updated. |
| `func_150EEE00` | `src/game/game_11C2B0.c` | 35 | 35 | — | Typed descriptor members replace byte-array punning; numerical transform address. |
| `func_15116D7C` | `src/game/game_143DE0.c` | 285 | 285 | — | Function body unchanged; deferred reason/score history updated. |
| `func_1514AD9C` | `src/game/game_177B50.c` | 14 | 14 | 14 | Target-endian unsigned-character argument-byte read; see item 9. |
| `func_1507C22C` | `src/game/game_A9260.c` | 100 | 60 | 60 | Unsigned numerical traversal; this review names one entry pointer per iteration. |
| `func_150F0BEC` | `src/game/game_11D830.c` | 135 | 130 | — | Correct no-argument RNG calls; unsigned-character packet byte write. |
| `func_15055D48` | `src/game/game_80B80.c` | 340 | 620 | 620 | Numerical difference plus unsigned masked shift; score regression retained (item 3). |
| `func_1504C9E4` | `src/game/game_77BE0.c` | 450 | 175 | — | Direct byte read and compound updates replace a temporary snapshot. |
| `func_1512C068` | `src/game/game_157840.c` | 20 | 20 | — | Function body unchanged; deferred reason/score history updated. |
| `func_150FDB0C` | `src/game/game_12A460.c` | 30 | 30 | — | Function body unchanged; deferred reason/score history updated. |
| `func_150DB2D8` | `src/game/game_108320.c` | 10 | 10 | — | Function body unchanged; deferred reason/score history updated. |
| `func_15122170` | `src/game/game_14F580.c` | 285 | 80 | — | Integer zero converted into f32 store replaces 0.0f spelling; no type change. |
| `func_1510D720` | `src/game/game_13ABD0.c` | 30 | 30 | — | Function body unchanged; deferred reason/score history updated. |
| `func_150AD8B0` | `src/game/game_DAD60.c` | 490 | 490 | — | Function body unchanged; deferred reason/score history updated. |

## Review acceptance

Local review acceptance passed on 2026-10-16 against published head
`555402fd3932816ba0c03540964e0cd395e7dfae` plus this uncommitted review revision.
All ten accepted function bodies are unchanged. Clean ten-function verify-batch
returned **BATCH_COMPLETE**, with **2,696 tests and eight skips** (184.140 seconds).
The data ownership audit, full-span/layout/integration, progress and whitespace
gates passed. Original-assets and reconstructed-assets full US ROM builds passed;
independent comparisons confirmed GAME (2,072,880 bytes, SHA1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`) and both complete US ROMs
(67,108,864 bytes, SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`) equal their
independent references. Direct ELF inspection found flags 0 (non-ALLOC), size16,
the exact four-byte payload and twelve zero bytes for both literal sections.

Source/configuration/tooling/inventory validation-manifest SHA256:
`3f2b3a5b4c2f2d5b0dd6e326eebdaca5fc3daed9f1351fafb4b265c5b888c248`. Those files remained unchanged through all gates;
only the evidence documentation was finalized afterward. This fingerprint
identifies the local review snapshot, not a new commit or the historical tree.
The reproducible gate commands are in the linked literal evidence document.
No shared header, linker placement, compiler setting, reference or acceptance
criterion changed. No commit, push or PR edit was performed in this review pass.
