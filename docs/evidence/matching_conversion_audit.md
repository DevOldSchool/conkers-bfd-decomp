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

## Single independent-review trial (2026-10-01, outside the window)

The proposed three-local form was compiled once at 00:04 UTC. `finish` took
2.322 seconds and returned CURRENT(720), compared with the retained 271.
The specific storage prediction held: frame 0x70 became the exact 0x50, incoming
argument homes became exact, saved owner remained at SP+0x3C, and saved-register
slots were unchanged. No stack-only rows remained.

The full match prediction did not hold. The indexed second-loop form now
includes `index * 4` in its row-start calculation, adding two instructions;
raw initializes a real advancing cursor independently of index. The new
preheader and downstream temporary-register assignments account for the
worsening score (18 register rows, two operand rows, one opcode/alignment row,
four missing/extra rows). These categories are not proof of semantic defects.

The prior 271 source was restored byte-for-byte and deferred through the
supported tool, with progress and whitespace checks passing. Both forms and
full diffs are preserved. No match was claimed and no empty clean batch was run.
The result supports distinguishing expression-only storage from genuine
loop-carried cursor state, rather than indiscriminately deleting all locals.
Any follow-up needs a separately justified source form; no blind sequence of
local permutations was started.

### One isolated cursor follow-up

Independent inspection showed the first trial had also repaired the original
pair of reordered instructions and tail saved-pointer rotation. One additional
bounded form therefore retained the three-local body and restored only a real
block-local `s32 *cursor` in the second loop. Its row base was expressed as
`&D_800C3960[arg0 * 30]`; the cursor advances after each free-and-clear pair.

This returned CURRENT(132) in 2.192 seconds. The predicted extra index shift
and add disappeared; frame stayed at the exact 0x50. There are now no opcode/
control or missing/extra rows. The saved owner moved from the correct SP+0x3C
to SP+0x38, with 17 register rows and three operand rows remaining (one classified
as stack-only). It remains nonmatching. The improved 132 source is deferred;
older 271 and 720 forms are preserved as separate proof artifacts. No further
permutations were run, and no accepted function or byte count changed.

### Faithful byte-offset initializer

The typed-array cursor trial began before the reviewer's exact initializer
arrived. One explicitly approved correction then tested the proposed
`(s32 *)((u8 *)D_800C3960 + arg0 * 0x78)` with every other line unchanged.
This distinction matters: typed-array indexing had introduced a different
intermediate register for the final scaling operation.

The faithful form returned CURRENT(12) in 2.250 seconds. All 17 temporary-register
differences disappeared. Every instruction, ordering and control-flow shape
now agrees, with frame 0x50 exact. Only three accesses to the saved owner pointer
use SP+0x38 instead of SP+0x3C. This confirms the specific expression prediction;
it does not establish an accepted match. The improved 12 form is deferred and
all earlier forms are preserved. No padding or automated search was introduced.

### Direct owner access closes the focused difference

A further independent read of the candidate object's `.mdebug` showed four
abstract declared-word locations (`saved`, `index`, `count`, `cursor`). Those
are pre-optimization metadata, not final runtime locations. Together with the
observed three-local frame/spill behavior, they supported a specific prediction:
remove the redundant named owner address, retain the three real state variables,
and let the compiler retain the direct owner-table address across calls.

The exact reviewed body was applied without expression substitutions. It replaces
only the named `saved` declaration/assignment and its owner-table uses with
`D_800C3668[arg0]`; the real block-local byte-offset cursor remains. This returned
full-span CURRENT(0) for 508 bytes, with reviewed layout, progress and whitespace
passing. The 0x50 frame and SP+0x3C owner-address spill are now exact. Focused
finish took 7.690 seconds including successful match metadata gates.

The four compiled forms in this review sequence were 720, 132, 12 and 0. One was
an unintended typed-array variation of the proposed initializer; recording that
mistake matters for reproducibility. Summed finish command time was 14.454
seconds; read-only investigation, editing, coordination and durable checkpoints
were separate. This is one resolved case and does not establish a general
throughput improvement or justify dropping any acceptance gate.

The clean singleton batch then returned `BATCH_COMPLETE`: full 2,072,880-byte
US game code and all mapped external rodata matched, 1,092 tests passed with
12 skipped, and metadata/progress/whitespace passed. Batch wall time was
86.522 seconds, including 24.697 seconds for the Python tests. This adds one
accepted function / 508 bytes, bringing the task total to 24 / 10,292 bytes.
The source unit remains mixed; no boundary or shared declaration was changed.

## Next storage review: useful negative, no compile

A 271-second independent read-only review of `func_151AC61C` retained its best
209 form. Candidate `.mdebug` accounts for 44 bytes of declared source homes,
rounded to a 48-byte local region in frame 0x80. Raw has a 64-byte region in
frame 0x90 with the same 40 bytes of observed live vectors/RNG samples and
24 unaccessed bytes whose source identities are unknown. Vectors need +4-byte
home shifts while random samples need -4; saved registers already agree.

Matched helper/caller evidence supports genuine three-float vectors, and each
random sample must survive calls. Original debug symbols are unavailable.
Adding unused scalars or enlarging vectors would therefore invent storage.
No new body was proposed or compiled; this avoids replaying a superficially
similar cleanup fix on a different storage problem. Four FP load rows visibly
differ, two also in stack operands, so the classifier's two register-only rows
must not be read as only two differing FP instructions. Full offsets, object
hashes and cited proof are preserved in the private attempt archive.

## Follow-up scheduling review and independent implementation

The separate `func_15071B18` read-only review also recommended no compile.
Its three moved instructions cross independent operations. Matched siblings
that store their size fields earlier immediately reuse the involved FP
registers, a dependency absent here. Callee code confirms the pair are genuine
float base/spread parameters, so array/type reinterpretation is unsupported.
The original 390 source remains intact; full findings are in the attempt archive.

Meanwhile, direct owner-table access solved the related `func_1501E400` on its
first new source form (58 → 0), recovering both frame and pointer-spill homes.
Its 320 bytes passed the complete clean batch. A second related entry-address
probe on 1501E73C was unchanged at 70 and stopped.
These results support running concrete implementation leads alongside bounded
read-only diagnosis, rather than stopping both streams behind every review.

## Observed storage-led follow-up cohort

From the first new trial at approximately 00:04 UTC through clean acceptance
before 01:00 UTC on 2026-10-01, this selected deferred cohort produced eight
accepted functions / 1,932 bytes from 16 new scored forms on 12 compiled targets.
Two additional targets stopped after read-only negative reviews. Existing-score
diagnoses, deferral measurements and one type-cast repair recheck are excluded
from the 16 source hypotheses. All original acceptance gates remained in force.
The private machine-readable record is `storage-method-hour-20261001.json`
under the continuation proof directory.

Summed measured finish-command time was 81.042 seconds. Four clean batches
totalled 348.888 seconds, including 101.404 seconds of Python tests. Analysis,
review, source editing, coordination, baseline diagnoses, publication and backup
are not included in those command totals. They are not an exclusive wall-time
partition.

This is an observed improvement in delivered results within this cohort, not a
controlled estimate of a general speedup: targets were deliberately selected
from preserved near-misses and differed in size/difficulty from the prior hour.
The useful transferable finding is the distinction between actual state and
source-level names for derived addresses. Where the compiler recovers required
common expressions, redundant homes can be removed without changing operations.
Where it instead rematerializes addresses (1518F7C4), the same transformation
fails and the prior best must remain. Reconstructed source homes and dataflow,
not score alone or a universal locals-count rule, justified the successful tests.

A short explicit follow-up on 1501FC8C's remaining duplicate-zero behavior found
no matched local precedent or compiler proof for changing the float comparison
to an unsuffixed double zero. No additional source form was justified; the
improved 567 remains preserved.

## Reusing a storage hypothesis

Removing an address alias must preserve any actual value snapshot across calls.
In `func_15107924`, the three-coordinate copy survives a helper that can change
those coordinates; replacing the copy with fresh loads would erase the change
detection. The retained source in
[game_133190.c](../../src/game/game_133190.c) distinguishes that real snapshot
from recomputable addresses. Required fresh loads must likewise remain fresh.

A gap between aggregate homes can belong to another genuine local rather than
missing packet bytes. In `func_150D8B88`, placing the existing returned-object
declaration between the spawn descriptor and copied payload accounted for the
observed gap without adding storage or changing expressions. The retained
[game_105FC0.c](../../src/game/game_105FC0.c) shows that layout. This supports
one prediction from debug homes and raw accesses, not arbitrary declaration
permutations. Check the predicted home changes and the complete instruction
difference independently; recovering homes alone does not prove frame size,
scheduling or equality.
