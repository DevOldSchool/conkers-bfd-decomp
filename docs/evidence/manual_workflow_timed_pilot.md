# Small manual matching workflow pilot — 2026-09-30

## Result

Three fresh targets, nine bounded manual C variants, and **zero new exact or
batch-verified matches**. One additional ready selection was screened out as
an exact raw duplicate of an exhausted candidate, without compiling it or
changing its inventory state. The two streams ran during
20:33:34–20:42:20 UTC, an 8-minute 46-second observation window. The observed
new-match rate in this sample was therefore zero per hour; it is not a useful
forecast of a long-run rate.

The practical finding is that focused compilation/diff checks were cheap in
this warm environment. All nine `finish` commands together took 24.511 seconds
(range 2.233–3.837 seconds). Measured selection, context, finish and defer
commands totaled 49.575 seconds across both streams. The rest of the wall
window includes source analysis and edits, inspection, communication,
orchestration and uninstrumented tool latency. This is **not** a measurement
of model reasoning time alone. Parallel commands may overlap, so the summed
command times should not be subtracted as if they were a serial trace.

## Scope and method

- US only; unchanged pinned compiler, settings and mandatory acceptance gates
- One canonical integrator and one isolated source-family worker
- Maximum initial candidate plus two targeted revisions per trial target
- No permutation, assembly edits, artificial padding, parameter narrowing
  without qualifying declarations, or extra attempts after the trial cap
- Ordinary ready-queue selection used the reviewed exact-source exclusions
  to avoid the worker's file; the actor worker used its explicitly assigned
  target and existing family evidence
- UTC timestamps and Bash built-in `time` measured commands; `/usr/bin/time`
  was absent. The initial timing-tool miss was recorded separately. The
  worker's 182-second wall interval includes about 14 seconds of adaptation
- Compiler/diff/harness time is combined; compiler time alone and tokens were
  not measured
- Earlier setup, ROM/toolchain recovery and warm-up functions are excluded
  from trial match counts

## Target observations

| Target | Selection/reuse | Registered bytes | Target wall | Scores | Best |
| --- | --- | ---: | ---: | --- | ---: |
| `func_1502D630` | Explicit actor family; existing actor type | 500 | 182 s | 1104, 2034, 1104 | 1104 |
| `func_15008BF0` | Normal ready queue; new typed descriptor | 480 | 202 s | 4956, 4956, 1909 | 1909 |
| `func_1500E8C0` | Normal ready queue; reuse preceding descriptor | 480 | 205 s | 2500, 2217, 1600 | 1600 |

Target wall spans run through their supported defer transaction. They include
model/tool interaction and bookkeeping, are not pure editing times, and must
not be summed as elapsed parallel runtime. All nine variants compiled without
a declaration correction. All three best candidates remain disabled with the
original ASM active.

The actor's reused 812-byte type immediately gave the correct frame, argument
and output homes, and pre-transform instruction prefix. Two float-lifetime
revisions did not improve it. That supports reusing established types as a
starting point, but does not demonstrate faster exact matching.

The first descriptor candidate retained an eight-byte frame/stack offset
mismatch. A combined output workspace was unchanged; a real cached scale and
reordered independent stores improved instruction selection. The second
already had the correct frame and reused the same 80-byte descriptor. Keeping
a floating subtraction dependent on a real field, rather than allowing a
literal expression to fold, and grouping zero-field stores improved it. Both
still differ in initialization scheduling and register allocation.

### Duplicate screening

The normal queue selected `func_151DAE28` (476 bytes). Its entire independent
raw instruction byte stream is identical to the already attempted
`func_151AC810`:

`c2c069b6daa71470e88cedcf4ab4617dd73692b7c5eeba7022ef36c664fdf42f`

Readiness preparation took 5.212 seconds. The exact-byte comparison and
bounded declaration lookup took 0.048 seconds. No new qualifying declaration
was found for the selector-width issue, so the equivalent exhausted source
hypothesis was not repeated. The item remains raw and was only temporarily
excluded from this trial's selection. Raw identity is not proof that all
future source contexts are equivalent; new declaration evidence can justify a
revisit. We did not measure the counterfactual time that a repeated attempt
would have cost.

## Serialized handoff and validation

The integrator applied only the actor worker's C source diff, used supported
inventory transactions, and independently reproduced scores 4512 and 1493
for its two warm-up candidates and 1104 for the timed target. Those handoff
transactions and checks took 18.394 seconds; this is separate from sampling
and includes the two non-pilot functions.

An incremental complete US game-code and external-rodata comparison then
passed in 8.891 seconds. The 2,072,880-byte game-code image remains identical
to the owned ROM; mapped data and zero-alignment checks also passed. Progress
and whitespace passed. No clean `verify-batch` was due because the pilot
accepted no functions, and no empty batch or redundant full test suite was
run. The preceding combined workflow/bootstrap suite passed 1,092 tests
(12 skipped). A future exact match still requires every applicable focused,
integration and clean-batch gate.

A separate in-flight emitter warm-up, `func_151C4644`, improved 403 → 10 → 10.
One multiply's operands remain commuted. Source operand reversal was unchanged;
it was deferred before sampling and is not counted as a pilot match.

## Recommendation and limits

1. Keep exact raw fingerprints and declaration evidence in the attempt ledger.
   Screening a known equivalent hypothesis before another compile avoids
   redundant work; this trial demonstrated one such instance.
2. Prefer a concrete new call contract or established sibling/type pattern
   over an arbitrary low mismatch score. Family reuse reduced uncertainty in
   the initial source, but did not produce an exact result here.
3. Keep two isolated source streams and one serialized integrator when two
   productive families are available. They operated without source/build
   collisions. This trial does not establish a matches-per-hour speedup.
4. Keep the small hypothesis cap. Compiler latency is not the main opportunity
   shown here; spending more variants on near-misses would not be justified
   by these results alone. Retain the existing validation gates.

This was a small, nonrandom, uncontrolled sample. Target difficulty differed;
the ready queue itself selected two related descriptor routines, so selection
and reuse effects are confounded. There was no serial control, model comparison
or token measurement. No exact-match ETA or general speedup factor is claimed.
Broader matching was paused after this bounded pilot so its findings could be
reviewed before choosing another trial.
