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
[v3.8.1 release](https://github.com/encounter/objdiff/releases/tag/v3.8.1) is
pinned by version and per-platform SHA-256 in `toolchain/tools.lock.json`. The
binary runs natively from ignored `build/host-tools/` on Linux or macOS, on
x86_64 or ARM64. First use needs HTTPS access and host `curl`; subsequent uses
verify the cached binary and can run offline. Compilation and reference
assembly still use the existing pinned Docker image.

The command accepts registered US work-item IDs with either active C or a
preserved deferred candidate. Deferred C is activated in a generated copy;
canonical source, match records, and integration records are not changed. A raw
GLOBAL_ASM function without a preserved candidate is rejected.

## Comparison inputs and output

Both tools use the same IDO-compiled C candidate and independent raw US
assembly reference. GLOBAL_ASM members are excluded from the focused candidate
object. Each selected ID gets its own candidate copy, including when multiple
deferred functions share a source file.

Raw assembly symbols sometimes have no ELF size, so objdiff can infer a span
that includes a neighboring function. The adapter sets only the selected
reference symbol's type and size in a temporary ELF copy, using the exact
registered span from `diff.py`. It preserves section bytes and relocations and
rejects a reference too short for the span. Candidate symbol sizes are left as
emitted by IDO. The summary checks that objdiff returned all registered
reference instructions, including instructions after a return and trailing
nops.

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

## Full-repository CPU-code report

```sh
./conker objdiff report
```

This builds the mapped SDK archives and active C implementations, prepares
independent splat targets for every range in `config/overlays.json`, and
invokes the pinned native `objdiff-cli report generate`. It covers both US CPU
overlays, including raw/unassigned code. The command uses four
object-preparation workers and validates cached base object hashes before
reuse. The first run requires the pinned `lib/ultralib` submodule (`git
submodule update --init lib/ultralib`).

Unlike `compare`, the repository report leaves deferred `#if 0` candidates
disabled. GLOBAL_ASM placeholders are removed from generated C copies, so
undecompiled assembly cannot earn matching credit as if it were C. Source units
marked `integration: c` supply completion metadata; SDK completion comes from
their canonical archive mappings. Objdiff calculates matching independently
from the newly built objects.

The code range is partitioned into source units, SDK objects, and unassigned
ranges, with no overlap or gaps. An isolated splat configuration enables
`make_full_disasm_for_code: true` and `asm_emit_size_directive: true` for each
overlay. Source ranges use `c` segments and SDK/unassigned ranges use `asm`.
Splat source creation is disabled and every output goes under the report's
`targets/` directory. The existing matching/reference assembly is untouched.
This follows [splat's full-disassembly
support](https://github.com/ethteck/splat/pull/448).

Targets are assembled from the complete emitted translation units, preserving
splat's function sizes, padding, labels, and relocations. Only the existing
GNU-as syntax normalization is applied; registered instruction spans no longer
override report symbols. All targets in an overlay are linked at their original
addresses, with a size assertion for every unit. Splat's unresolved-address
definitions supply external symbols while target definitions resolve internal
references. The linked bytes must exactly reproduce the original main CPU-code
range, the loader-proven debugger code interval, and the freshly decompressed
game code. All inputs are checksum-validated. Provisional debugger collections
remain unassigned report ranges until their source boundaries are reviewed.

For SDK objects, unambiguous target-to-base symbol names are mapped at
identical offsets within their canonically mapped object. Units without C or
SDK bases retain their targets and stay in the denominator.

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
  anything. See [CI and registration](ci.md#toolchain-and-reporting).
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
mapped ranges, and verifies that project source inputs stayed stable and the
validated target objects did not change. Compilation failures remain explicit
in coverage, retain the reference in the denominator, and produce a failing
command exit status. See each unit's `build.log` for diagnostics.

### Scope

This is an exhaustive report of the project's **tracked US CPU-code ranges**,
not a claim of full ROM reconstruction. Main/game/debugger data, BSS, assets, boot code
outside those ranges, and RSP microcode are not measured. In particular,
objdiff emits 100% data fields for a zero data denominator; those fields do not
establish any data coverage. EU/PAL remains outside the active target.

Full-disassembly output follows the sections in the current maps. These report
maps cover CPU text; complete per-object data/rodata/BSS ownership is not yet
established. An unexpected nonempty allocated target section fails validation
instead of being silently discarded. Exact code-image relinking does not prove
original source boundaries or full-object data equivalence.

## Interpreting differences

### Function spans and symbol sizes

The initial comparison pilot exposed why the temporary reference symbol must
use the registered span: an 84-byte function otherwise included a neighboring
`jr ra` and its delay slot. An early-return candidate with 12 bytes against a
20-byte reference retained the missing tail as a mismatch. Neither stopping at
the first return nor accepting a neighboring symbol is a valid comparison.

The repository report deliberately uses splat's function symbols instead of
registered spans. Padding can lie inside a registered range but outside IDO's
function symbol. One observed case, `func_15005AF0`, had a 16-byte reference
symbol and 12-byte candidate symbol, producing 75% despite a zero registered-span
diff. Native exact/fuzzy measures and the existing match tracker therefore have
different denominators and completion semantics. Do not replace one percentage
with the other or resize symbols to make them agree.

### Relocation handling

The pilot's `func_15015F40` switch scored `CURRENT (0)` but 99.6774% in standalone
objdiff. Its raw reference used the undefined `jtbl_800966C0_game` symbol;
IDO used the local `.rodata` section. Objdiff reported the `R_MIPS_HI16` and
`R_MIPS_LO16` operands as different. A text-only raw reference does not supply
sufficient table-data evidence to claim full object equivalence, so the adapter
preserves that discrepancy.

Native `report generate` uses different defaults from interactive `diff`:
function relocation differences are ignored by default. The same switch reached
100% in the report. The repository command keeps these upstream defaults;
that result cannot replace the authoritative focused and integration gates.

### Invocation timing

A warm five-function Apple Silicon pilot measured individual native objdiff
invocations at about 6 ms, versus about 0.5 seconds for asm-differ in the amd64
container. This demonstrates lower invocation overhead in that environment,
not general diff performance or end-to-end matching throughput.

`comparison.json` times each differ invocation separately, excluding compilation,
Docker setup and downloads. The host-native/container comparison is not
architecture-neutral, and first binary launch can add substantial overhead.
