# Bounded target-selection comparison — 2026-09-30

## Result

This follow-up compares two evidence-led selections with two normal ready-queue
selections. The cohort was fixed before each target's first compilation, with
an initial candidate plus at most two manual revisions, and no replacements
based on mismatch scores. Both streams screened prior attempts and exact raw
instruction duplicates. Compiler settings and acceptance gates were unchanged.

The ready queue produced **one new batch-verified match (480 bytes)** and
completed its one-function source unit; the other three targets remained
candidates. The evidence arm produced no exact matches. This tiny, nonrandom sample
cannot establish that one selection policy is generally faster.

## Preselected cohort and outcomes

| Arm | Target | Bytes | Evidence before compilation | Scores |
| --- | --- | ---: | --- | --- |
| Evidence | `func_15140190` | 536 | Known `func_151D5D60` output contract and proven quad allocation/copy pattern | 2167, 2523, 1466 |
| Evidence | `func_1514EECC` | 580 | ROM-proven `func_15189FF0` descriptor-pointer contract and same-file matched setup callers | 5905, 5880, 10089 |
| Ready queue | `func_1504A400` | 480 | First normal ready selection after ownership and exhausted-duplicate exclusions | 0 |
| Ready queue | `func_1506E0EC` | 480 | Next normal ready selection under the same exclusions | 6264, 2783, 1570 |

All four had fresh target eligibility and no exact duplicate of a previously
attempted target in the checked material. No target was replaced after seeing
its scores. The known duplicate `func_151DAE28` was excluded before queue
selection, together with the evidence stream's two owned source files.
Evidence selection was authorized to use explicit-target `m2c`; normal queue
selection used `next --ready` once per selected item.

The two evidence targets were locked at 21:07:19 UTC. Both queue targets were
locked as they were selected, before their initial source edits. The intended
size band was 480–600 bytes; the evidence arm averaged 558 bytes, while the
queue arm averaged 480. Instruction count is not a difficulty adjustment.

## What happened

### Quad allocation and transformation: `func_15140190`

The known allocator contract and vertex/copy pattern supplied a concrete
starting point. The first source used real matrix and coordinate arrays,
vertex fields, and a full-width incoming selector with explicit signed
normalization at its use. Reusing the normalized incoming variable and changing
the byte-wrapped loop count worsened the result. Restoring the first shape and
writing each coordinate in physical x/y/z order improved it to 1466.

An eight-byte frame difference, selector normalization/lifetime and the final
loop schedule remain. No qualifying existing narrow target declaration was
found, so the parameter was not narrowed. The source remains disabled and the
original ASM remains active. This target shows that a useful helper contract
can still leave the hard compiler-allocation work unresolved.

### Descriptor setup: `func_1514EECC`

The existing descriptor-pointer contract avoided guessing the callee's ABI.
A source-local setup record and real three-word vector objects described the
raw fields. Unsigned descriptor byte fields and separate vector objects
improved 5905 to 5880. Replacing vector aggregate copies with individual
component copies worsened the result to 10089; the 5880 candidate was restored.

Frame size, vector placement and floating initializer scheduling remain. No
new match is claimed. The known call contract was insufficient to make this
larger constructor an easy target.

### Ready arithmetic helper: `func_1504A400`

The first candidate expressed the raw floating post-decrement/increment
loops directly. Its entire 480-byte span matched at `CURRENT (0)` on the first
attempt. The source unit contains one function and therefore required immediate
integration; it was finalized locally by the worker and independently by the
integrator. Completion of a source unit and a new function match are reported
separately.

### Ready transform/effect loop: `func_1506E0EC`

The first variant needed a `NULL` declaration correction before compiling;
that repair is logged separately from source hypotheses. Real pointer and
cached-coordinate lifetimes improved 6264 to 2783. Reordering actual local
objects improved it again to 1570. The transform/effect call block and save/
restore offsets improved, while frame and vertex homes still differ. It
remains disabled with original ASM active. No padding or permutation search
was used.

## Timing and validation

Sampling ran from 21:07:26 to 21:13:59 UTC: **6 minutes 33 seconds** across
both streams. This excludes earlier preflight, evidence preselection and worker
setup, and later handoff/acceptance/publication. The evidence arm's two target
cycles took 299 seconds; the queue arm took 390 seconds, including its mandatory
local integration. These overlapping intervals are not additive.

- Evidence arm: six successful compilations/diffs, 14.857 seconds total;
  context and defer commands bring its recorded command total to 24.241 seconds
- Queue arm: four compiled variants and one declaration-correction failure;
  five `finish` calls totaled 15.596 seconds. Selection, context, integration,
  defer and hygiene commands bring its recorded command total to 83.948 seconds
- Both arms: ten source hypotheses, eleven `finish` calls, 30.453 seconds of
  focused compile/diff/acceptance command time. Compiler-only time was not measured
- Queue worker's required local integration took 51.869 seconds; its initial
  copied build state required compilation. Handoff preparation took another
  101 seconds, separate from sampling
- The integrator independently reproduced `CURRENT (0)` in 6.555 seconds and
  repeated the required canonical integration in 48.473 seconds. Reproducing
  and deferring the worker's 1570 candidate took 2.160 and 2.865 seconds

The unmeasured wall time includes analysis, edits, inspections, communication,
reporting and tool orchestration. It must not be labelled pure model reasoning.
The 108.189 seconds of measured sampling commands across both streams may
overlap and cannot be subtracted as a serial trace. No token data was available.

The first canonical clean batch took 74.565 seconds and passed the complete
US game/rodata comparison, then failed one of 1,092 tests. The only failure
was a stale exact source-path expectation in
`test_mp3_libraries_preserve_their_raw_comparison`: it still expected
`game/game_778B0` after the mandatory integration moved the complete unit to
`game/done/game_778B0`. The range end and C segment kind were unchanged;
raw-reference checks still require the original ASM comparison. The batch
remained pending rather than being counted as accepted.

The approved one-line fixture correction changes only the exact expected
finalized path; the 0x4A400–0x4A5E0 span, C segment kind and every independent
raw-reference assertion remain intact. All 13 focused segment-map tests passed
in 0.467 seconds. The required clean batch was then rerun, rather than bypassed:

- `BATCH_COMPLETE` for `func_1504A400` at 21:19:55 UTC, taking 78.397 seconds
- Complete 2,072,880-byte US game-code image and all mapped external rodata
  and zero-alignment checks matched the owned ROM
- All 1,092 tests passed, with 12 skipped; metadata, generated progress and
  whitespace passed
- One newly accepted function (480 bytes) and one newly complete source unit;
  no pending accepted-match or regression batch remains
- The three disabled candidates add no matched bytes; no shared header,
  compiler flag, assembly body or linker-address mapping was altered

From the first recorded task timestamp (21:04:20 UTC) through batch acceptance
(21:19:55 UTC), the observation lasted 15 minutes 35 seconds, including setup,
selection, source work, handoff, the stale-fixture diagnosis and both batches.
One new accepted match over that interval is an observed 3.85 matches/hour.
It is only arithmetic for this one short run, excludes later publication, and
is **not a forecast or a statistically supported throughput estimate**. The
queue-versus-evidence result is 1 versus 0 accepted matches in two targets per
arm; shared integration costs are not assigned to separate causal rates.

## Interpretation

- Retain the normal small-function queue as a productive default. It found an
  exact result here without a special ABI investigation
- Use concrete call/type/sibling evidence to resolve a known obstacle, rather
  than treating a familiar helper as a general predictor of easy matching
- Keep duplicate and prior-attempt screening in both selection paths
- Keep bounded manual hypotheses and the existing validation gates; this
  trial provides no reason to relax them

The comparison is observational. It used two separate sessions, the same model
family without an intentional model change, unequal target complexity and
sizes, no randomization, no crossover and no token measurements. Reasoning
effort/session equivalence was not independently measured. Existing source
knowledge and context also differ. Evidence-arm preselection was not precisely
instrumented, so its sampling time must not be presented as the complete cost
of evidence-led selection. No causal speedup or exact completion ETA follows
from these four targets. Broader matching pauses after the verified checkpoint
for review of the findings.
