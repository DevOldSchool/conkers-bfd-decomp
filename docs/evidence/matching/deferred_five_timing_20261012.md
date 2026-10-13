# Five deferred matches and tooling timing — 2026-10-12

Five deferred functions were matched on `codex/deferred-five-timings`, branched
from main at `094102644c4c2f5aefaa0fc4b609416918f66f58`. The work used pinned
US references and IDO, with no shared header, compiler, assembly, differ,
permuter or acceptance-rule changes. EU/PAL was not a gate.

## Accepted C changes

| Function | Final source | Bytes | Initial score | Finish calls before batch | Successful change |
| --- | --- | ---: | ---: | ---: | --- |
| `func_1515BE50` | `src/game/game_1890A0.c` | 256 | 30 | 2 | Keep the actual allocation result separately from the typed object; write field34 at the original float-snapshot position. |
| `func_1513D2F0` | `src/game/game_169510.c` | 456 | 10 | 2 | Keep the allocation result and write scale directly at the original load position. |
| `func_150BE850` | `src/done/game/game_EBD00.c` | 352 | 30 | 2 | Name the first helper result and write field374 at the original constant-load position, removing the float alias. |
| `func_1515EB84` | `src/game/game_18A8F0.c` | 244 | 20 after compile repair | 3 | Match the existing return-type declaration locally and initialize X before Y to recover conversion registers. |
| `func_150A32B4` | `src/game/game_CDE80.c` | 124 | 70 | 2 | Remove the float alias and initialize X/Y/Z directly before their repeated field stores. |

All five have independent full-span US `CURRENT (0)`, source-unit layout,
progress and whitespace success. Total matched span: 1,432 bytes.
Finish counts include baseline and final
checks; the fourth includes one inherited declaration compile failure. Probe
batches are separate: respectively three, one, one, one and two; only the
first successful function used a permuter search (eight variants, no gain).
Historical attempts from earlier passes are additional, recorded in the
inherited deferral reasons, and were not reset by this worktree.

`func_150BE850` completed its source unit. `progress integrate` moved the
source to `src/done/game/`, updated `config/game/us.yaml` and the canonical
inventories, and verified byte-identical US GAME output. Progress and
whitespace checks passed immediately afterwards. Other units remain mixed.
After merging #107 and #102 and applying the review corrections, all five
functions again passed independent full-span `finish` checks (`CURRENT (0)`,
`STOP_MATCHED`). The clean five-ID `verify-batch` completed with
`BATCH_COMPLETE`: byte-identical integrated US GAME, including the merged
GAME data-owner and linker-consistency checks, 2,525 tests in 167.184 seconds
(`OK`, nine skips), canonical metadata/progress and whitespace passed.
The complete batch command took 234.64 seconds real, 5.32 seconds host user,
and 1.63 seconds host sys. This verifies C/GAME integration, not reconstructed
assets; no asset reconstruction changed.

Before that final batch, the disabled `func_15002754` candidate was resumed,
compiled without its redundant block-local prototype, and transactionally
deferred again at `CURRENT (200)`. Its canonical `GLOBAL_ASM` is unchanged.
Seven deferred reasons were rewritten through the supported transactions;
candidate bodies and scores were preserved apart from the requested
prototype removal. Both benchmark scripts completed using a fresh nested
output directory, with equal baseline/cache scores; the cache script also
reported its missing-results prerequisite correctly. This was a portability
smoke test, not a replacement for the historical performance samples below.

Detailed attempt identifiers and session notes are retained in the local
attempt ledgers under `build/us/manual-attempts/`.

## Other candidates

The pass also examined `func_1514401C`, `func_15002754`, `func_151957B0`,
`func_151D3354`, `func_150E5558`, `func_151A9CA0`, `func_15183ACC`, and
`func_1515D480`. These remain deferred, with concrete exhausted hypotheses
in the inventory and local ledger. They contribute no matches.

The useful retained C change is the disabled `func_15002754` candidate:
raw calls show `func_1510F800` consumes the table index in a0. Passing the
actual argument repairs the inherited no-argument call using the existing
file-scope declaration, without changing other callers. Explicit allocator writes
retain the raw store sequence. Its valid score is 200; the earlier 2,110
attempt with the omitted argument was marked invalid. No shared dependency
changed. `func_151957B0` retains a registered trailing JR/NOP span that the
trial C did not reproduce; the full-span gate was not weakened.

## Actual permuter commands

Each search used `/usr/bin/time -l ./conker permute <id> --budget 32` in the
warm Docker container through the normal wrapper. The generated variant
space was exhausted in every search; none improved the initial score.

| Function | Compiled variants | Search loop, seconds | Command real, seconds | Host user / sys, seconds | Score |
| --- | ---: | ---: | ---: | --- | ---: |
| `func_1514401C` | 32 | 7.631 | 9.29 | 0.94 / 0.17 | 320 |
| `func_15002754` | 9 | 2.561 | 4.74 | 1.01 / 0.22 | 200 |
| `func_151D3354` | 7 | 1.769 | 3.86 | 0.98 / 0.22 | 5 |
| `func_1515BE50` | 8 | 1.801 | 3.44 | 0.95 / 0.17 | 30 |

The four commands took 21.33 seconds total wall time. The internal loops
sum to 13.762 seconds. Host `user/sys` values exclude container CPU time;
they are not the total CPU consumed by compiler and scorer subprocesses.
These times do not include model reasoning, source inspection, probes,
setup, integration or final batch validation.

## Compile and ASM diff measurements

A separate bounded pilot compiled and scored the unchanged valid candidates
five times each in the already warm container. It called the existing
`compile_c.compile_command` and full-span `diff.asm_diff_command`, retaining
the registered 25/41/98 instruction bounds. It did not edit project source,
inventory, reference spans or production tooling. Each result retained the
same score across every sample.

| Function span | IDO median, ms | Scorer median, ms | Scorer with warm bytecode cache, ms | Scorer reduction |
| --- | ---: | ---: | ---: | ---: |
| 100 bytes (`151D3354`) | 13.15 | 225.36 | 108.78 | 51.7% |
| 164 bytes (`15002754`) | 12.27 | 215.73 | 107.24 | 50.3% |
| 392 bytes (`1514401C`) | 22.04 | 220.86 | 123.29 | 44.2% |

Variant generation took 3.20 ms for seven variants, 2.67 ms for nine, and
26.68 ms for 32. The scorer represents about 91–95% of the measured
compile-plus-score time on this small-function cohort.

One additional cProfile scorer run for the 392-byte candidate recorded
196,733 calls in 0.237 seconds. Source-module execution/import accounting
was 0.202 seconds cumulative; Python source compilation was 0.121 seconds;
asm-differ's main function was 0.041 seconds, `do_diff` about 0.008 seconds,
and two objdump calls about 0.009 seconds. See the [saved profile](deferred-five-20261012/scorer-profile.txt). These are overlapping cumulative
measurements, not additive stage durations, and profiling overhead is
separate from the unprofiled wall-clock medians above.

The cache experiment set only `PYTHONPYCACHEPREFIX` to a writable ignored
benchmark directory. It ran one warmup and five scored samples per input.
The first cache fill took 0.589 seconds; subsequent input warmups were
0.118 and 0.122 seconds. All cached scores still equaled 5, 200 and 320.
Production environment settings were left unchanged.

## Rewrite assessment

These measurements support trying a writable bytecode cache and reducing
repeated imports/process startup first. The cache alone demonstrated a
44–52% scorer reduction without changing its implementation language.
A persistent scorer worker is a plausible next experiment, but was not
implemented or measured here. It must retain independent full-span scoring,
per-candidate isolation and fatal handling of scorer errors.

There is little measured payoff from rewriting this permuter's variant
generation: it took only 3–27 ms per search. Rewriting the core diff algorithm
is also not yet justified by this cohort; startup/import work dominated.
Faster searches would not remedy the exhausted search space seen here:
all five matches came from targeted source hypotheses, while 56 permuted
variants yielded no improvement. Broader or larger functions, concurrency,
and long searches need separate measurements before a language rewrite
can be assessed generally. No language-to-language benchmark was performed.

## Reproduction and environment

[Raw samples and search reports](deferred-five-20261012/timings.json) include
exact compiler/scorer commands, fingerprints, scores and individual wall
times. [Compile/scorer pilot](deferred-five-20261012/benchmark.py) and
[cache comparison](deferred-five-20261012/cache_benchmark.py) preserve the
measurement procedure, with output-directory creation and CLI root/output
options added during review. Both scripts derive the repository root from
their own location, rather than requiring a literal `/workspace` path. Run
inside the pinned toolchain with a prepared US checkout and its ROM/reference
inputs. The first script creates missing output parents; run it before the
cache comparison, which consumes its `results.json` and recorded commands.

```sh
python3 docs/evidence/matching/deferred-five-20261012/benchmark.py
python3 docs/evidence/matching/deferred-five-20261012/cache_benchmark.py
```

Both accept `--root /path/to/checkout` and `--output path/to/results` (relative
outputs are resolved under the repository root). Use the same options for
both scripts and keep generated outputs ignored. A clean output directory
does not remove the requirement to prepare the checkout/toolchain first.
Historical timing samples remain tied to the original benchmark inputs;
record the current revision for any new measurements.

- Platform: Apple Silicon Docker, Linux aarch64, Python 3.12.3; host Python 3.14.
- Toolchain digest: `sha256:67de4f788e404fbe1794725192801956abdae4cecf1db43c01988df058f9b429`.
- asm-differ revision: `c80ea4e3d16ecc8f4c21923633f3f9b1fb534c53`.
- US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

## Acceptance provenance

The independent `CURRENT (0)` results, clean `BATCH_COMPLETE` and source
SHA-256 hashes in [the acceptance manifest](deferred-five-20261012/timings.json)
apply to committed revision `b8f842cc039d5b3fa60cfec27b47f141143a64d8`, which includes merged head
`d11166209aafdf7369350e662637962fe2f01ab7` plus the review corrections.
Verification ran immediately before committing those fixes, on identical
source and tooling inputs; the recorded hashes were checked against that
commit. The following evidence-only commit updates this report and the
manifest without changing verified code or tooling. Session timestamps and
attempt identifiers remain in the local attempt ledger.

The original performance samples retain their original base revision and
input fingerprints. They were not re-labelled as measurements of the merged
revision. Public CI passed all eight checks on `d1116620`; CI for the review
commits is reported separately in the PR, and does not establish ROM matching.
