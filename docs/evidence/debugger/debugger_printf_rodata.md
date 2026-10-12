# Debugger formatter source-data integration

The formatter source unit now supplies both of its initialized sections to the
actual US ROM link. The loader-proven original image and independently assembled
references remain the comparison inputs.

| Source section | Loaded range | ROM range | Bytes |
| --- | --- | --- | ---: |
| `.data` | `0x16003C70–0x16003CE0` | `0x1A26F8–0x1A2768` | 112 |
| `.rodata` | `0x16004800–0x16004960` | `0x1A3288–0x1A33E8` | 352 |

The [source-unit review](us_debugger_source_units.md) establishes these blocks.
The [access map](us_debugger_data_objects.json) records their independently
checksum-validated contents and consumers. Definitions in
`src/done/debugger/debugger_1AD0.c` reconstruct padding strings, integer digits,
format qualifiers/flags, flag masks, floating powers of ten and special-value
strings. `config/symbols/us.txt` records their payload sizes; ordinary compiler
alignment remains anonymous and is still included in byte comparisons.

The Putfld switch naturally emits its 52 relocated cases at
`0x1600487C–0x1600494C` (208 bytes, SHA-1
`d1df6f79b540cfcccfc89d76dd0783f081156d03`). The expression
`(ldval - lo) * 1e8` naturally emits the following double at `0x16004950`.
The original table gap and terminal alignment are produced by IDO. No candidate
section is resized and no artificial table or literal symbol is added.

`config/profiles/us.yaml` owns both allocated placements. The old INFO selector
is removed; the generated `.debugger` output consumes the actual C object's
sections. `verify_debugger_rodata.py` checks all 14,064 code bytes and 4,720 data
bytes in that allocated image against the checked US ROM. The ordinary full-ROM
comparison remains required. The reporter rebuilds the runtime image and compares
fresh candidate storage, symbols and relocations to the actual linker input before
allowing either section to be considered for completion. Native matching remains
a separate measurement. The completion-policy correction described below removes
the former requirement that native data matching also reach 100%.

## Native anonymous data comparison

The unmodified objdiff release performs its native symbol-based comparison.
Anonymous switch tables and trailing literals can leave native data matching
below the independently verified allocated byte count. The debugger reference
still includes original rodata context for real switch destinations. Full ROM
verification checks all 464 bytes; native percentages are reported unchanged.

The [UI data reconstruction](us_debugger_data_reconstruction.md) supplies the
other 4,256 bytes. The [TLB routine](us_debugger_tlb.md) remains verified original
assembly. Its maintained source can earn native matching and linked completion
without changing C-only inventory credit.

## Remaining native comparison blocker

The official objdiff v3.8.1 data comparison bounds the displayed/compared byte
range by the last non-hidden, non-section symbol. See upstream
[`diff_data_section`](https://github.com/encounter/objdiff/blob/v3.8.1/objdiff-core/src/diff/data.rs).
The actual formatter candidate has 352 `.rodata` bytes, but its last ELF data
symbol ends at offset `0x7A` (the string at `0x16004878`). The independently
assembled reference's last payload ends at `0x158` (the double at `0x16004950`).
IDO emits the intervening switch table and double without ELF object symbols.
They remain in the actual candidate section and in the verified runtime image.
The stock comparison therefore treats their reference bytes as unmatched; this
is not evidence that those allocated runtime bytes differ.

Two bounded, ignored source experiments tested an explicit C definition for the
existing `1e8` literal. A named scalar moved storage into `.data`; a one-element
constant array moved the double before the switch table and changed floating-point
register allocation and multiply operand order. Both failed exact object comparison
and were discarded. The canonical formatter source and compiler settings remain unchanged. No hand-written switch
assembly, invented comparison symbol, shortened section or relaxed completion
rule was adopted during these experiments. At the time, the project also required
native data matching for linked completion. That policy was subsequently corrected;
the anonymous-data limitation still affects native matching.

The same saved formatter objects were also compared with the official v3.8.2
macOS ARM64 release, downloaded separately and checked against its published
SHA-256 `767c67e13b7b5e6ca545e7d2235e47c7bceac07d47a52776f74a52914cb4085a`.
It produced the same 34.52381% section comparison for `.rodata`. The repository
pin remains v3.8.1; upgrading to the tested release does not resolve this blocker.

## Follow-up investigation (2026-10-12)

No compiler, source-layout or report-policy change was accepted in this pass.
The formatter's `func_1600288C` was rechecked with the pinned toolchain and still
reports full-span `CURRENT (0)`.

- The actual object's `.mdebug` local-symbol records contain no read-only data
  label for the switch table or literal. There is no existing debug symbol for
  those objects to promote into the ELF symbol table.
- IDO's unedited `-S` output names the switch table `$96`, but emits the double
  as the pseudo-instruction `li.d $f8, 1e8`; the assembler creates its pool.
  Reassembling that output with IDO and the pinned compiler options produced
  7,584 text bytes instead of 7,040 and changed rodata. This diagnostic round trip
  was rejected; it is not part of the build.
- A separately compiled literal would require a different source/link layout
  from the reviewed formatter object. The saved named-array experiment also
  changes the floating-point registers and multiply operand order. Merely moving
  that definition into another object does not fix those instruction differences.
  No source-unit split or linker workaround was adopted.
- The official v3.8.1 [configuration schema](https://github.com/encounter/objdiff/blob/v3.8.1/objdiff-core/config-schema.json)
  provides no full-data-section comparison mode that overrides the symbol bounds.

A small original C reproducer isolates the comparison limitation without any ROM
bytes or game source:

```c
const char prefix[2] = "a";
double scale(double value) { return value * 1e8; }
```

Compiling this and a second copy with `1e9`, using the pinned IDO compiler and the
repository's normal `compiler_flags("us")`, gives identical text bytes but
*different* 16-byte `.rodata` sections. The final eight bytes are respectively
`4197d78400000000` and `41cdcd6500000000`. Stock objdiff v3.8.1 reports both text
and rodata as 100% between these objects: the explicit two-byte `prefix` symbol
ends before the anonymous double. Thus a native percentage alone can miss a real
literal mismatch. This is why deleting reference labels, manipulating symbol
sizes or relaxing the independent full-byte checks is not an acceptable remedy.
The real formatter reference retains its table and literal, so its comparison
correctly remains incomplete under the current native symbol-bound rules.

The ignored continuation ledger stores the two reproducer sources/objects, stock
JSON result, rejected round-trip object and focused formatter log under
`build/us/manual-attempts/debugger-completion/`. These are diagnostic results, not
new matches or a new integration batch. At the end of that investigation, the
then-current policy still blocked linked completion; PR #102 remained a draft.
The subsequent policy correction below separates completion from native matching.


## Completion-policy correction (2026-10-12)

Second-opinion review identified that `qualify_data_completion()` conflated
linked completion with native matching. The extra native-data gate belonged to
this project, not objdiff's completion contract. Stock v3.8.1 accepts verified
`metadata.complete` independently of symbol comparison; see its
[report implementation](https://github.com/encounter/objdiff/blob/v3.8.1/objdiff-cli/src/cmd/report.rs#L339-L342).

The reporter now retains the existing `data_completion_verified` and
`linked_inputs` requirements, candidate/actual-object equivalence, relocations,
full runtime-image ROM proof, source/object hashes and complete denominators.
It emits explanatory `completion_notes` instead of clearing eligibility and
running objdiff a second time. No native report counts are edited.

Fresh stock output completes the formatter's 7,032 code bytes and 464 data bytes.
Its native `.rodata` comparison remains 34.52381%, with 112 / 464 native matched
data bytes for the whole unit. The debugger therefore reaches 100% linked code
and data while native matching remains 100% code and 92.54237% data.

Candidate-only annotation derived independently from candidate relocations is
potential follow-up work, not enabled in the production report. The candidate-only
experiment below subsequently tested this approach. It would need object/relocation
invariance, deterministic range derivation and mutation tests that expose changed
constants and jump tables. The ROM-free upstream reproducer remains available;
no upstream issue was posted in this correction. PR #102 remains a draft.

See the [fresh report audit](us_debugger_data_reconstruction.md#completion-policy-verification-2026-10-12)
for the full validation scope and the three empty SDK section percentages.


## Candidate-only annotation experiment (2026-10-12)

The requested annotation was prototyped on copies of the formatter object, with
stock objdiff v3.8.1 unchanged. The prototype derives a 208-byte table from 52
contiguous `R_MIPS_32` relocations and checks that count against the candidate's
`sltiu`/branch/shift/load/jump dispatch. An adjacent relocated `lui`/`ldc1` pair
establishes the double's eight-byte extent. Neither range comes from the reference,
ROM, splat output, a hardcoded formatter offset or the desired match result.

Names use actual linked placement: existing candidate-owned symbols in the runtime
ELF must agree on their section base. This gives `jtbl_1600487C` and `D_16004950`.
The annotation function takes candidate bytes and section bases; a test forbids
file reads and subprocess calls while it runs. All non-symbol/string section
bytes, section headers, existing symbols, relocation records and implicit addends
remain unchanged. Only appended symbol/string entries and their table offsets
and sizes differ. A second pass is byte-identical. A candidate with no anonymous
references is unchanged. Deliberately overlapping named storage, a wrong dispatch
bound, an interior table pointer and changes to code/data during annotation are
rejected.

Both `.rodata` sections retain 352 bytes, and the comparison payload ends at
`0x158` on both sides after annotation. The final eight alignment bytes remain
subject to the independent whole-image ROM proof. No range is shortened.

### A second comparison limitation

The two data symbols alone raise the formatter section score from 34.52381% to
52.677143%, not 100%. The newly exposed switch table has equivalent but differently
encoded relocations. IDO uses a `.text` section target with offsets stored in the
REL words (for example `00000AAC`). The independently assembled reference uses a
named label such as `.L1600257C`, with a zero encoded word. Both resolve to the
same final address.

A second diagnostic adds the eight destination labels, deriving their offsets
only from candidate table relocations and their names from actual code placement.
All 52 relocation comparisons then match. The section still scores only
83.9243% because stock objdiff compares the raw REL words as well as the resolved
relocations. Its
[data-symbol comparison](https://github.com/encounter/objdiff/blob/v3.8.1/objdiff-core/src/diff/data.rs#L365)
explicitly counts relocation bytes once as raw data and again as relocations;
the section-wide fallback also compares the raw bytes. Symbol additions cannot
remove this difference while preserving the required section bytes.

The reference's inferred table symbol also includes four alignment bytes (212
versus the independently derived 208). This experiment did not resize either
symbol or change the reference to improve the score. The smaller reproducer below
has equal symbol sizes and independently demonstrates the REL-byte limitation.

### Mutation results

Every formatter variant keeps the 352-byte data denominator. Annotation preserves
that variant's code comparison; changing the switch count or placement itself
changes instructions and therefore can lower code matching independently.

| Candidate mutation | Two data symbols | Data symbols plus destination labels |
| --- | ---: | ---: |
| None | 52.677143% | 83.9243% |
| `1e8` changed to `1e9` | 51.784283% | 83.03145% |
| First two table destinations exchanged | 52.677143% | 82.722496% |
| 51 cases and matching bound instead of 52 | 52.522564% | 83.16883% |
| Table shifted by four bytes | 36.904762% | 36.904762% |

Thus the two-symbol-only version also fails the requested reordering exposure
test: its already-unmatched relocations conceal the additional error in the score.
With the candidate-derived code labels, all four mutations lower the baseline.
The separate ROM-free anonymous-double reproducer changes from a false 100%
before annotation to 81.25% after annotation; code remains 100% in both comparisons.
These are diagnostic comparisons, not accepted function matches or report credit.

### ROM-free REL-addend reproducer

[`named.s`](../../../tests/fixtures/objdiff_rel_addends/named.s) and
[`section.s`](../../../tests/fixtures/objdiff_rel_addends/section.s) contain the same
12-byte function and four-byte table. Both already expose the same labels. The
only meaningful difference is `.word entry` versus `.word .text + 4`:

| Input | Encoded table word | Resolved destination |
| --- | --- | --- |
| Named label | `00000000` | `.text + 4` |
| Section plus addend | `00000004` | `.text + 4` |

The focused test assembles both with the pinned MIPS binutils, checks the relocation
type and destination, links at fixed addresses, and proves identical code and table
bytes. The linked table word is `80000004` in both cases:

```sh
./conker test -p test_objdiff_rel_addends.py -v
```

To reproduce the native comparison in an environment with those binutils and the
unmodified objdiff CLI available:

```sh
mips-linux-gnu-as -EB -march=vr4300 -mabi=32 -no-pad-sections \
  -o /tmp/named.o tests/fixtures/objdiff_rel_addends/named.s
mips-linux-gnu-as -EB -march=vr4300 -mabi=32 -no-pad-sections \
  -o /tmp/section.o tests/fixtures/objdiff_rel_addends/section.s
objdiff-cli diff -1 /tmp/named.o -2 /tmp/section.o -o /tmp/rel-addends.json
```

Observed with the official checksum-verified v3.8.1 macOS ARM64 release:
`.text` is 100%, the relocation matches, and `.rodata` is 87.5%.

### Disposition

**Blocked under the candidate-symbol-only constraint.** The prototype is not
connected to report generation or runtime linking. No reference, objdiff binary,
compiler setting, production object or report was changed. Linked completion stays
100% and native matching remains 100% code / 92.54237% data. The saved production
report remains current with SHA-256
`cee8d436182b00f17e649e144b16de4c0447b51793f58d5934ec730266e5eece`.

The next investigation must address equivalent REL encodings and reference table
extent independently. An upstream comparison fix or a separately reviewed
relocation-canonicalization method would go beyond symbol-only annotation;
changing raw words without proving relocation semantics is not acceptable.
No upstream issue has been posted. PR #102 remains a draft.

The ignored local directory
`build/us/manual-attempts/debugger-completion/annotation/` retains the prototype,
code-label helper, reproducible experiment script, objects, native JSON diffs and
mutation results. The ROM-free assembly fixtures and their focused test are the
only new executable repository files from this experiment. No fresh function
batch or asset reconstruction is claimed.


## Reviewed relocation trial (2026-10-12)

**The isolated trial reaches 100% native matching and linked debugger code and
data with unmodified objdiff v3.8.1.** Production reporting is unchanged: its
accepted report remains 100% matching code / 92.54237% matching data and 100%
linked code/data. PR #102 remains a draft. Integration requires separate approval.

The [saved evidence](us_debugger_relocation_trial.json) records the tested source
revision, official binary checksum, input/output hashes, mutation results,
independent linker proofs and full-report comparison. The
[prototype](relocation_trial/objdiff_candidate.py) and test drivers are preserved
as experimental evidence only; production scripts do not import them.

### Transformation and independence

The transform first annotates the anonymous double, table and destination labels
using candidate instructions, relocation runs and section bounds. Actual section
placements come from consistent existing candidate symbol anchors in the runtime
ELF. It does not consult the reference object, ROM bytes, comparison score or a
hardcoded table count to derive the annotations.

It then canonicalizes only the table's 52 `R_MIPS_32` records: section-symbol plus
in-place offset becomes an exact destination symbol plus zero in-place addend.
The effective `S + A` destination is unchanged. This is a comparison-copy
transformation, not a change to the compiler output used by the runtime linker.

The verifier independently derives the allowed sites from the original candidate
and checks all 106 relocations. Existing symbols, code, section sizes, unrelated
relocations and all other bytes must remain identical. Only the newly added symbol
metadata and approved relocation words/indices may differ. Derivation runs with
file reads and subprocess access disabled; idempotence and a no-op case also pass.

### Checks and mutation results

| Candidate | Native code | Native formatter rodata |
| --- | --- | --- |
| Canonical comparison copy | 100% | 100% |
| Double changed from 1e8 to 1e9 | 100% | 99.12791% |
| First two table destinations reordered | 100% | 98.49487% |
| 51 cases with corresponding bound | 99.99943% | 98.78664% |
| Table shifted four bytes | 99.99431% | 36.904762% |

The transformation preserves each mutant's original code score. A separate
anonymous-double reproducer reports 81.25% data matching for different constants,
with 100% code. The verifier rejects tampered code, literal bytes, addends,
relocation type/destination and section size. Discovery rejects inconsistent
bounds, an interior table pointer and an out-of-range destination.

GNU ld independently links the raw and transformed copies. Their complete text,
rodata and data payloads are identical at the actual placement and at two other
legal placements. At the actual placement both match the unmodified runtime ELF.
A fresh allocated-byte verifier also confirms 14,064 debugger code bytes and
4,720 initialized data bytes match the checked US ROM. No new C function batch
or asset reconstruction is claimed.

The isolated full report changes only `done/debugger/debugger_1AD0.c` data matching;
all other 10,865 units are identical. It adds exactly 352 matched data bytes,
reaching 4,720/4,720 debugger data bytes and 14,040/14,040 report code bytes. Linked
completion stays 100%. The allocated-byte verifier additionally covers padding;
its code byte count is therefore larger than the report's symbol-based count.

### Reproduction scope and disposition

The saved drivers run from the repository root against the existing ignored trial
artifacts under `build/us/manual-attempts/debugger-completion/`. They document the
actual local experiment, including its macOS ARM64 release binary and previously
prepared mutation objects; they are not yet a portable CI test suite. No ROM or
compiled candidate bytes are committed. `check_trial.py` runs the native mutation
and semantic checks; `run_link_trial.py` and `check_alternate_links.py` require the
pinned MIPS binutils environment and `scripts` on the Python import path.

Automatic approval review rejected production wiring pending completion of these
checks and explicit integration approval. The checks now pass. The prototype
remains isolated and the production report hash remains
`cee8d436182b00f17e649e144b16de4c0447b51793f58d5934ec730266e5eece`.
