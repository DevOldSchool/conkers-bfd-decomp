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

## Published code and data report

```sh
./conker objdiff report
```

This builds the mapped SDK archives and active C implementations, prepares
independent splat targets for every range in `config/overlays.json`, and
invokes the pinned native `objdiff-cli report generate`. It covers tracked
main/game/debugger US CPU code and initialized data, including raw/unassigned ranges,
plus the rebuilt font and 663 reviewed textures. The command uses four
object-preparation workers and validates cached base object hashes before
reuse. The first run requires the pinned `lib/ultralib` submodule (`git
submodule update --init lib/ultralib`).

Completed C units without GLOBAL_ASM use freshly built objects from the actual
build. Mixed units use generated C-only copies, leaving deferred code disabled,
so preserved assembly cannot earn source credit. Coverage records the candidate
origin. SDK candidates come from the canonical archives.

Owned code and data references are combined into one source/SDK object unit.
The YAML, private-data configuration and reviewed linker placements own the
boundaries, payload extents and padding contracts. `config/data/us.json` records
only owners keyed by overlay, hexadecimal loaded address and input section.
Every audit and US build checks that these keys cover exactly the mapped ranges
and that owners agree with the build selectors. Unknown ranges are derived from
the build partition and have no owner entry. Changing an extent requires editing
its canonical build placement, without maintaining a second copy in this manifest.
Unassigned ranges remain separate. Reference grouping preserves section extents
and relocations; it never creates symbols or absorbs padding. The final grouped
objects must also relink at their original addresses and reproduce all six
main/GAME/debugger code and data images byte for byte.

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
- `objdiff.json`: the generated code and initialized-data project.
- `data/`: independently assembled data references, C/SDK candidates and linked image proofs.
- `owned/`: combined source/SDK targets and `verification.json`, proving the exact
  grouped report inputs reproduce all six original code and data images.
- `targets/`: isolated splat configs, original full assembly, normalized copies,
  target objects, linker scripts, linked validation images, and logs.
- `coverage.json`: range ownership, source/SDK mappings, target link proofs,
  excluded zero ranges, cache keys, object hashes, and any compiler failures.
- `validation.json`: US profile, snapshot revision/fingerprint, modified-input status,
  report hash, exact denominator checks,
  timings, native measures, and existing tracker totals.
- `self-changes.json`: the report compared with itself through objdiff's native
  parser; it must contain no changed units.

Generation checks every reported unit's code count against its audited target
symbols, reconciles the aggregate denominator and excluded zero bytes with the
mapped ranges, and verifies that project source inputs stayed stable and the
validated target objects did not change. Compilation failures remain explicit
in coverage, retain the reference in the denominator, and produce a failing
command exit status. See each unit's `build.log` for diagnostics.

Report freshness requires the font and texture source inputs used to produce their candidates.
Cleaning `build/` invalidates that evidence (and usually removes the report itself);
recreate the inputs and regenerate the report after cleaning. During preparation,
completed source units run Make before the cache check so the cache hashes the
current actual build object. This adds per-unit Make overhead; it is not a promise
that every object is recompiled. Run report generation after ROM-enabled tests
and other builds finish, because they can update the same linked objects.

### Scope

The published report covers the project's **tracked US CPU-code ranges and
initialized main/GAME/debugger data images**, plus the **rebuilt font and 663 reviewed textures**. Its data
denominator is 1,296,953 bytes: 201,632 loaded bytes (7,824 main, 189,088 GAME and
4,720 debugger), 5,440 bytes of font storage and 1,089,881 stored texture bytes. Existing
YAML placements and reviewed linker/private-data contracts establish mapped
ranges; all remaining bytes stay as unassigned targets. Shared storage is
counted once. BSS, other stored assets (including MP3 and raw audio), boot code
outside the tracked ranges, RSP and EU/PAL are excluded.

Data references are assembled independently with original code as disassembly
context, and each complete linked data image must reproduce the checked ROM.
Candidates use active C with GLOBAL_ASM removed and deferred code disabled, or
mapped SDK objects. Reviewed payload extents distinguish compiler padding from
neighboring ROM data. Candidate sections and relocations are preserved. Split
rodata without a proved C-only partition keeps its target without a candidate.

The native report provides `total_data`, `matched_data` and
`matched_data_percent` to decomp.dev's blue **Data** bar. The site shows
`complete_data` as “fully linked” and matching beyond that as “perfect match”;
see its [rendering implementation](https://github.com/encounter/decomp.dev/blob/main/crates/web/src/handlers/common.rs).
Data placement alone grants no fully linked completion. A grouped unit is complete
only when its code and every owned data range qualify. ROM-identical,
relocation-free main SDK data linked through canonical archive placements is
eligible, but completion also requires every data byte in its grouped unit to
match in native objdiff. Generation first measures candidates, removes completion
from eligible units with incomplete native data matching, then regenerates the
native report. It never patches the report counts. `completion_downgrades` in
validation records affected units and their code/data bytes. Private/INFO/NOLOAD data still supplied by preserved ROM streams remains
incomplete, even when its C owner has integrated code. This can reduce a file's
fully-linked code measure while retaining its native matching credit.
A selector such as `*foo.o(.rodata)` alone does not establish that the ROM uses
that object's bytes: all current source-owned external placements are INFO/NOLOAD
verification sections. The raw ROM or original GAME-data archive still supplies
the final bytes. A future source-data integration must replace that backing and
add verification of the actual linked input before it can receive completion.

Known SDK data names and payload sizes come from `config/symbols/us.txt`.
Declaration-backed zero alignment padding stays anonymous in the reference,
while every byte remains in the section and ROM checks. This avoids treating
splat's generated padding labels as missing SDK variables. See the
[SDK symbol evidence](evidence/data-layout/us_sdk_data_symbols.md) for remaining
anonymous pools and incorrect SDK symbol extents.
Native comparisons determine perfect-match credit. Every final unit must satisfy
`complete_data <= matched_data`; category or aggregate totals cannot hide a
violation. Units whose data is still ROM-backed need actual build integration
before they can become complete. This currently includes GAME and debugger data.

When this report is first published, fully-linked code can decrease for two
reasons: a grouped unit owns data still supplied by ROM, or its linked data fails
native symbol matching. Native matched code and function inventory records are
unchanged by this completion policy; the drop reflects a stricter whole-unit gate.
Rebuilt font bytes contribute to the ordinary Data category, with no separate
Font or Rebuilt assets category. The font earns completion when all 95 editable
PGM glyphs and their manifest rebuild through the canonical Makefile rule into the exact original 5,440 bytes
(including 13 alignment bytes). Its candidate concatenates the `.data` payloads of the 96 actual ROM link inputs:
`build/us/assets/font/glyphs/0000.o` through `0094.o`, then `font/padding.o`.
Each input's extent and hash is checked; its independent target comes from the
checked ROM. Both aggregate binaries use the same ordinary linker wrapper.
Canonical YAML boundaries must agree. Changed glyphs remain in the denominator
but cannot retain completion when their rebuilt bytes differ. This does
not change function match records or certify original source-object boundaries.

[The 663 selected textures](evidence/data-layout/us_texture_reconstruction.md) are independently
rebuilt from indexed PNG pixels and palette through fresh RZIP compression.
Each candidate is the actual ROM link object, checked against a fresh encode;
each target comes from the checksum-validated ROM. Changed texture pixels,
palette, metadata or compressed output fail this exact-reconstruction pilot.
The 1,089,881 stored bytes enter Data once; decoded bytes and adjacent raw storage
do not add credit. Native matching and source/link-input verification gate completion.

Generation validates code and data counts per unit, aggregate data coverage,
unassigned ranges, target/base hashes, and asset source/build-input hashes.
Saved snapshots become stale when editable glyphs change. The JSON remains native objdiff
output. The existing CI upload of `build/us/objdiff-report/report.json` as
`us_report` supplies both bars; no separate report upload or site configuration
is required for data. A local generation does not publish anything.

### Why retain native objdiff generation?

N64 projects such as Puzzle League and Snowboard Kids use mapfile_parser's
objdiff-format exporter. Its [configuration documentation](https://github.com/Decompollaborate/mapfile_parser/blob/2.x/src/mapfile_parser/frontends/objdiff_report.py)
requires `.NON_MATCHING` markers on both function and data symbols when data
reporting is enabled, and warns that missing markers inflate progress.
Conker does not provide those markers comprehensively. Its preserved GAME data
stream and INFO verification sections also require explicit backing ownership.
Switching exporters alone would therefore misrepresent credit. We retain native
comparisons, source-object grouping, complete loaded-image denominators and
independent ROM checks. A future exporter migration must first prove equivalent
marker coverage and unique runtime storage accounting.

## Data boundary groundwork

```sh
./conker objdiff data-audit
```

This separate, ROM-validated audit partitions the loaded US main, game and
debugger data images into existing mappings and explicit unassigned ranges.
It validates the checked-in ownership manifest against SDK placements,
private-data mappings and external linker payload contracts; shared backing is counted once, and explicit compiler padding does
not claim neighboring ROM data. BSS and RSP remain outside its scope.

The command writes `build/us/data-boundaries/audit.json` without building,
installing objdiff or changing native report credit. Mapped ranges are placement
evidence, not original object-boundary or C-match certification. See the
[data boundary audit](evidence/data-layout/us_data_boundary_audit.md) for the
first verified totals, evidence limits and remaining report work.

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
