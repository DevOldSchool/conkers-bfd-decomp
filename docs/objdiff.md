# Experimental objdiff comparison

Use objdiff alongside the existing registered-span asm-differ adapter:

```sh
./conker objdiff install
./conker objdiff compare func_15178750 func_15040A40 func_15001970 \
    func_1516972C func_15015F40
# Interactive terminal only:
./conker objdiff view func_15001970
```

`compare` and `view` install the CLI automatically if necessary. The official
[v3.8.1 release](https://github.com/encounter/objdiff/releases/tag/v3.8.1)
is pinned by version and per-platform SHA-256 in `toolchain/tools.lock.json`.
The binary runs natively from ignored `build/host-tools/` on Linux or macOS,
on x86_64 or ARM64. First use needs HTTPS access and host `curl`; subsequent
uses verify the cached binary and can run offline. Compilation and reference
assembly still use the existing pinned Docker image.

The command accepts registered US work-item IDs with either active C or a
preserved deferred candidate. Deferred C is activated in a generated copy;
canonical source, match records, and integration records are not changed.
A raw GLOBAL_ASM function without a preserved candidate is rejected.

## Comparison inputs and output

Both tools use the same IDO-compiled C candidate and independent raw US assembly
reference. GLOBAL_ASM members are excluded from the focused candidate object.
Each selected ID gets its own candidate copy, including when multiple deferred
functions share a source file.

Raw assembly symbols sometimes have no ELF size, so objdiff can infer a span
that includes a neighboring function. The adapter sets only the selected
reference symbol's type and size in a temporary ELF copy, using the exact
registered span from `diff.py`. It preserves section bytes and relocations and
rejects a reference too short for the span. Candidate symbol sizes are left as
emitted by IDO. The summary checks that objdiff returned all registered reference
instructions, including instructions after a return and trailing nops.

Results are saved under `build/us/objdiff/`:

- `comparison.json`: both scores, spans, candidate/reference hashes, deferred
  status, and separate tool invocation timings.
- `<id>/asm-differ.json` and `<id>/objdiff.json`: full machine-readable diffs.
- `<id>/inputs.json`, `reference.o`, and `candidate.o`: reproducible input metadata
  and object snapshots.
- `objdiff.json`: a GUI project containing the selected comparisons. Open the
  `build/us/objdiff/` directory in the separately installed objdiff GUI.

The GUI project is a snapshot with automatic builds disabled. Rerun `compare`
after source edits. Its targets cover selected functions while each candidate
can contain other C functions from the source unit. **Do not publish a progress
report from this project to decomp.dev**: it is not a full-project inventory or
an object-boundary reconstruction.

`CURRENT` is asm-differ's weighted difference score; objdiff reports a match
percentage. These numbers have different scales. Objdiff percentages are
experimental diagnostics and cannot record a match. `./conker finish` remains
the authoritative full-span US match/layout gate; source-unit integration and
batch verification retain their existing rules.

## Initial US pilot

The first run on the isolated tooling checkout produced:

| Function | Case | CURRENT | objdiff | Reference / candidate bytes |
| --- | --- | ---: | ---: | ---: |
| `func_15178750` | Existing exact match | 0 | 100% | 84 / 84 |
| `func_15040A40` | Deferred early-return mismatch | 200 | 60% | 20 / 12 |
| `func_15001970` | Deferred near-match | 10 | 99.7368% | 152 / 152 |
| `func_1516972C` | Callback helper with relocations | 0 | 100% | 112 / 112 |
| `func_15015F40` | Eight-case switch | 0 | 99.6774% | 124 / 124 |

All five returned the full registered reference span. Without explicit reference
symbol sizing, the first case initially showed 91.3043% because objdiff included
a neighboring `jr ra` and delay slot. With the registered 84-byte boundary it
correctly reports 100%. The early-return case retains the missing tail as a
mismatch rather than stopping at the first return.

The switch case differs at the `R_MIPS_HI16`/`R_MIPS_LO16` operands for
`jtbl_800966C0_game`: the raw reference uses that undefined named symbol, while
IDO references the local `.rodata` section. Objdiff reports two argument
mismatches; the registered-span asm-differ comparison reports zero. This is
an object representation difference, and the text-only raw reference does not
provide enough table-data evidence to claim full object equivalence. The adapter
preserves the discrepancy instead of ignoring relocations.

In the warm five-function run on Apple Silicon, individual native objdiff
invocations took about 6 ms, versus about 0.5 seconds for asm-differ in the amd64
container. This small pilot is sufficient to establish that native invocation
overhead is lower in this environment, not to measure general diff performance.

Timings in `comparison.json` cover only each differ invocation, excluding
compilation, Docker setup, and downloads. Objdiff runs natively on the host;
asm-differ runs inside the amd64 container. They are not an architecture-neutral
benchmark, and a first binary launch can have substantially more overhead.

Validation: the full host tooling suite ran 1,009 tests successfully (7 skipped),
including 12 new boundary, output-coverage, and checksum tests. Shell syntax,
progress consistency, and whitespace checks passed. The interactive terminal
viewer was smoke-tested on the near-match. No game source or progress inventory
was changed by this experiment.

## Full-repository CPU-code report

```sh
./conker objdiff report
```

This builds the mapped SDK archives and active C implementations, prepares
independent splat targets for every range in `config/overlays.json`, and invokes
the pinned native `objdiff-cli report generate`. It covers both US CPU overlays,
including raw/unassigned code. The command uses four object-preparation workers
and validates cached base object hashes before reuse. The first run requires the
pinned `lib/ultralib` submodule (`git submodule update --init lib/ultralib`).

Unlike `compare`, the repository report leaves deferred `#if 0` candidates
disabled. GLOBAL_ASM placeholders are removed from generated C copies, so
undecompiled assembly cannot earn matching credit as if it were C. Source
units marked `integration: c` supply completion metadata; SDK completion comes
from their canonical archive mappings. Objdiff calculates matching independently
from the newly built objects.

The code range is partitioned into source units, SDK objects, and unassigned
ranges, with no overlap or gaps. An isolated splat configuration enables
`make_full_disasm_for_code: true` and `asm_emit_size_directive: true` for each
overlay. Source ranges use `c` segments and SDK/unassigned ranges use `asm`.
Splat source creation is disabled and every output goes under the report's
`targets/` directory. The existing matching/reference assembly is untouched.
This follows [splat's full-disassembly support](https://github.com/ethteck/splat/pull/448).

Targets are assembled from the complete emitted translation units, preserving
splat's function sizes, padding, labels, and relocations. Only the existing
GNU-as syntax normalization is applied; registered instruction spans no longer
override report symbols. All targets in an overlay are linked at their original
addresses, with a size assertion for every unit. Splat's unresolved-address
definitions supply external symbols while target definitions resolve internal
references. The linked bytes must exactly reproduce the original main CPU-code
range and the freshly decompressed game code. Both inputs are checksum-validated.

For SDK objects, unambiguous target-to-base symbol names are mapped at identical
offsets within their canonically mapped object. Units without C or SDK bases
retain their targets and stay in the denominator.

Native objdiff counts the sizes of function symbols, which can exclude padding
within the mapped text range. The generator audits symbol extents for overlaps
and checks every excluded byte against the independently linked original image.
Only zero-filled gaps are permitted. `coverage.json` records each gap's offsets
and reconciles native symbol bytes plus excluded zero bytes with the complete
mapped text size. No function is resized to include padding or improve a score.

Output is local under `build/us/objdiff-report/`:

- `report.json`: the unmodified native objdiff v2 report.
- `us_report.zip`: the same JSON packaged as `report.json`, demonstrating the
  GitHub Actions artifact contents. The protected US CI workflow uploads the
  JSON directly as `us_report`; this local command does not upload or register
  anything. See [CI and registration](ci.md#register-with-decompdev).
- `objdiff.json`: the complete generated CPU-code project.
- `targets/`: isolated splat configs, original full assembly, normalized copies,
  target objects, linker scripts, linked validation images, and logs.
- `coverage.json`: range ownership, source/SDK mappings, target link proofs,
  excluded zero ranges, cache keys, object hashes, and any compiler failures.
- `validation.json`: snapshot revision/fingerprint, exact denominator checks,
  timings, native measures, and existing tracker totals.
- `self-changes.json`: the report compared with itself through objdiff's native
  parser; it must contain no changed units.

Generation checks every reported unit's code count against its audited target
symbols, reconciles the aggregate denominator and excluded zero bytes with the
mapped ranges, and verifies that project source inputs stayed
stable and the validated target objects did not change. Compilation failures
remain explicit in coverage, retain the reference
in the denominator, and produce a failing command exit status. See each unit's
`build.log` for diagnostics.

### Scope and first full test

This is an exhaustive report of the project's **tracked US CPU-code ranges**,
not a claim of full ROM reconstruction. Main/game data, BSS, assets, boot code
outside those ranges, and RSP microcode are not measured. In particular, objdiff
emits 100% data fields for a zero data denominator; those fields do not establish
any data coverage. EU/PAL remains outside the active target.

Full-disassembly output follows the sections in the current maps. These report
maps cover CPU text; complete per-object data/rodata/BSS ownership is not yet
established. An unexpected nonempty allocated target section fails validation
instead of being silently discarded. Exact code-image relinking does not prove
original source boundaries or full-object data equivalence.

### Validated splat-target report

The full run on `feature/asm-to-c` at
`57d871d8900c3a07605fb5bf71fe02db701a5510`, including the local tooling and
source changes, passed all 922 units with no compiler errors. The 169 main
targets re-linked to the exact 164,512-byte ROM code range; the 753 game targets
re-linked to the exact 2,072,880-byte decompressed code image.

| Measure | Native splat-target report | Existing progress tracker |
| --- | ---: | ---: |
| Code denominator | 2,232,288 function-symbol bytes | 2,237,392 registered-range bytes |
| Exact matched code | 327,708 (14.6804%) | 336,172 (15.0252%) |
| Fuzzy matching | 14.9620% | Not reported |
| Completed/linked code | 159,424 (7.1417%) | Different completion semantics |

The remaining 5,104 mapped bytes are zero-filled gaps outside splat's function
symbols, verified against the linked original images and recorded individually
in `coverage.json`. Native code plus these gaps equals all 2,237,392 mapped bytes.
The native report contains 5,856 functions, of which 2,458 match exactly. The SDK
category reports 96.0435% exact matching and 99.9720% fuzzy matching. The historical
custom-target run below used an older source snapshot as well as different
target symbols, so the numerical change is not a controlled comparison of the
target generators alone.

Validation also confirmed that all 3,133 `GLOBAL_ASM` function names in the
project source units are absent from their compiled base text symbols. Source
fingerprints and target hashes stayed stable. Native self-comparison reported
no changes, and `us_report.zip` contained only the exact native `report.json`.
The full tooling suite ran 1,041 tests successfully (6 skipped); progress and
whitespace checks passed. Preparation took 161.82 seconds; native reporting,
validation, and packaging took 0.18 seconds. This is a local validated artifact;
no upload or decomp.dev registration was performed.

### Historical custom-target experiment

The following results predate the splat target generator and are retained as
experimental history. They do not describe the current report implementation.

The first full test used the isolated tooling checkout at
`cfc1d3c9734f1024a7d74777051982f31829e2e8`, including these uncommitted tooling
changes. It did not include the separate original checkout's uncommitted function
work. The report covered 2,237,392 bytes in 922 units: 716 source units, 172 SDK
ranges, and 34 unassigned ranges. All prepared without compiler errors.

| Measure | Native objdiff report | Existing progress tracker |
| --- | ---: | ---: |
| Tracked CPU-code bytes | 2,237,392 | 2,237,392 |
| Exact matched code | 275,752 (12.3247%) | 324,112 (14.4862%) |
| Fuzzy matching | 14.3953% | Not reported |
| Completed/linked code | 160,480 (7.1726%) | Different completion semantics |

The report has 5,864 function/code-span entries, including raw SDK functions and
two synthetic coverage spans. This is a different population from the tracker's
5,231 registered functions. Objdiff reports 2,179 exact entries.

The totals are not interchangeable with the authoritative tracker. Objdiff
compares ELF function sizes and object relocations, while the existing gate
compares the full registered instruction span and separately credits verified
SDK text ranges. For example, padding included in a registered/reference span
can lie outside IDO's function symbol size, reducing objdiff's percentage despite
a zero registered-span diff. SDK code reports 99.4397% fuzzy matching but only
77.9586% exact matching under these symbol boundaries. All 156 registered zero-diff functions that scored below 100% in this report
have different reference and compiled symbol sizes (for example,
`func_15005AF0`: 16 versus 12 bytes, reported as 75%). These size differences
need to be understood before treating the new exact percentage as the existing
project match percentage.

Native `report generate` also uses different defaults from the interactive
`diff` command: function relocation differences are ignored by default. The
earlier `func_15015F40` switch therefore reports 100% here, versus 99.6774% in
the standalone diff pilot. The report uses the upstream defaults unchanged.
Native metrics remain separate from the authoritative registered-span match
tracker. These first results describe a local snapshot, not a published run.

Final validation: 1,021 host tests passed (7 skipped). Every unit and the overall
CPU-code denominator matched the plan; the native report parser, source-input
fingerprint, report SHA-256, and ZIP contents passed checks. Final object
preparation took 85.47 seconds; native report generation, round-trip parsing,
and packaging together took about 0.17 seconds.
