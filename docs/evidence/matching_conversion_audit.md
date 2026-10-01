# Manual matching conversion audit, 2026-09-30

## Result and scope

The 22:48–23:48 UTC window produced one newly batch-verified function,
`func_1504BC38` (500 bytes), from 59 scored source forms across 23 distinct
targets in two isolated streams. The integrator contributed 36 forms across
12 targets; the source worker contributed 23 across 11 targets. These are
observed results for this hour, not an estimated long-term rate. Two targets
were already in progress at the window's start. One additional compile-only
missing-declaration repair is excluded, as are import rechecks, deferrals and
existing-match regressions. Accepted task totals are 23 functions / 9,784 bytes.

The machine-readable local evidence is
`build/us/manual-attempts/queue-continuation-20260930/hour-audit-2248-2348.json`.
Its 59 records identify the original target, finish log, score, UTC timestamp
and timing method. Detailed source snapshots and full diffs are preserved in
the associated private attempt archive; no ROM content is published here.

## Time evidence

- Scored finish commands total 147.178 seconds. Twenty-seven have explicit
  timing; 32 use original log creation-to-last-write proxies.
- Two clean verification batches inside the window took approximately 80.406
  and 80.224 seconds, including builds. Their Python tests took 24.598 and
  24.717 seconds, respectively (49.315 seconds combined).
- The next batch began at 23:48:27 and is outside this measurement window.
- These are accumulated command times, not an exclusive wall-clock partition:
  parallel operations overlap. Selection, editing, analysis, coordination,
  import checks, publication and backup time were not fully instrumented.
- There was no workspace reset or toolchain rebuild during the hour. One
  publication retry occurred; publication is now working.

This evidence does not support treating the test suite or compiler latency as
the principal cause. Most proposed source forms failed to become exact code.

## What the attempts show

Short registered spans (roughly 492–508 bytes in this cohort) still contain
constructors, floating-point/vector calculations, command emitters and uncertain
call contracts. Size does not establish source difficulty. However, the cohort
alone does **not** prove the small-function queue is worse than another selector.
No comparable counterfactual cohort was run during this hour.

Both streams generally used the same technique: adapt an m2c starter, reconstruct
local types, adjust storage or expression shape, and stop after bounded revisions.
Parallelism therefore increased similar attempts without providing an independent
analysis of why a surviving shape differed. Some revisions combined local-order
and data-flow changes, weakening attribution. Three-variant limits are useful
bounds, but should not replace understanding the specific remaining mismatch.

At least seven targets needed substantial contract reconstruction: the leading
actor argument of 15107700's helper, display arguments for 151462C8, forwarding
through the 15116984 wrapper, the 15156190 allocation result, 151EC1F0's pointer
lookup result, 1509759C's one-argument lookup, and 151AC61C's callback slots.
This limits the value of treating the generated starter as nearly finished C.

Of 22 retained nonzero targets, diagnostic row categories include register rows
in 21, operand/constant rows in 22, opcode/control rows in 18, missing/extra rows
in 21 and stack rows in 15. Categories overlap and are alignment diagnostics,
not semantic defects: missing/extra rows may simply be moved instructions.
No target was purely register-only. For example, 1501E540's apparent missing
rows are two reordered instructions, not missing behavior.

The successful 1504BC38 sequence (975 → 365 → 0) replaced forced cached values
with direct field operations, then preserved one actual full-word timer value.
It recovered the raw data flow before full-span and clean-batch acceptance.
This supports source-storage/data-flow reconstruction as a productive technique,
without establishing that it generalizes to every remaining target.

## Rules and research

The integer-formal rule constrained 15107700, 151462C8, 1518F5D0 and 151D5B6C.
Their byte operations alone do not establish a narrow ABI. No qualifying narrow
counterfactual was compiled, so it is unknown whether changing the rule would
help. Existing variadic annotation also affects 1519F1C8's argument homes; no
proven replacement contract was found. No rule relaxation is justified here.

A 212-second read-only call-contract pass supplied a correct helper prototype
and useful negative evidence. The resulting 15107700 attempts compiled but
remained at best 3417. A separate 115-second storage review justified one
151D1138 aggregate-copy form: 1160 → 1022, with the correct frame but remaining
spills and prefix differences. Neither research pass added an accepted match.
They improved evidence, but research activity itself is not matching throughput.

## Immediate practical change

Pause another broad sweep and test one independently reviewed storage hypothesis
on the already-preserved integer cleanup function 1501E540. Its first two forms
had 15 then 11 top-level locals and frames 0x80 then 0x70; raw uses 0x50. Saved
registers and the saved owner slot already agree, with no additional runtime
spill traffic in the extra space. The register-keyword third form is unchanged.

The independent review proposes retaining only the actual saved owner, loop
index and count pointer, expressing eight named address/expression temporaries
as direct table accesses. This is supported by the raw load/call/reload order
and the prior accepted [quad storage cases](quad_vertex_storage_matching.md).
Prediction: the frame should contract toward 0x50. It is a falsifiable source
hypothesis, not a claim about IDO internals or a promised match. Run one form,
record frame and remaining instructions separately from the total score, and
stop if it fails. No padding, arbitrary permutations, compiler changes, ABI
changes or weaker verification are involved.

The pending trial is outside the audited hour. Its outcome must be recorded
separately. Fresh queue selection remains paused for review.
