# Experimental objdiff comparison

Use objdiff alongside the existing registered-span asm-differ adapter:

```sh
./conker objdiff install
./conker objdiff compare func_15178750 func_15040A40 func_15001970 \
    func_1516972C func_15015F40
# Interactive terminal only:
./conker objdiff view func_15001970
```

`compare` and `view` install the official v3.8.1 CLI release automatically if
necessary. Platform release checksums are pinned in `toolchain/tools.lock.json`;
installation downloads the executable to ignored `build/host-tools/` and verifies
its checksum on every use. No Rust/Cargo or locally modified objdiff is required.
Game compilation and reference assembly still use the pinned Docker image.

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
plus all bounded asset storage. The font, 6,892 reviewed textures and 914 reviewed
assets in model banks, 149 compact audio sequences, 27 sound-bank parts, three MP3 decoder tables, the complete character morph and event banks, reviewed frames from 453 MP3 streams, 56 sprite entries, 20 visibility codebooks, 16 visibility bitmaps, 69 actor path tables, 31 navigation graphs, bounded scene fields and volumes, 29 native-format bank-0A animation bundles, the complete 483-script bank, 82 animation-control entries and 2,258 complete ADPCM samples have reconstructed candidates; remaining asset storage stays unmatched.
The command uses four object-preparation workers and validates cached base object hashes before
reuse. The first run requires the pinned `lib/ultralib` submodule (`git
submodule update --init lib/ultralib`).

Report preparation shares normalized ROM bytes, their checksum, and decoded game
archives across asset families within one invocation. File changes invalidate the
reference session; a subsequent report starts a fresh session. Bounded asset
families use one common check for disjoint regenerated ranges, source stability,
actual linked bytes, and equality with the independently supplied ROM.

The MP3 build saves encoded typed spans under ignored
`build/us/mp3-spectral/cache/`. The report can reuse them only when editable-input
hashes, the reviewed contract, codec source hashes, and cached output hashes agree.
Missing, corrupt, or stale entries are regenerated. Whole-stream and credited-range
checks against the original ROM still run. Workers receive only their stream,
not a copy of the full ROM. Bounded-DEFLATE source and executable hashes are
reused within a process while file identity, size, timestamps and mode remain
unchanged; changes trigger rehashing and the existing executable-repair checks.

Completed C units without GLOBAL_ASM use freshly built objects from the actual
build. Mixed units use generated C-only copies, leaving deferred code disabled,
so generated assembly fallbacks cannot earn source credit. Reviewed maintained
assembly units are assembled separately, require full-span/runtime proof, and
are labelled `Original assembly`. Coverage records the candidate origin. SDK
candidates come from the canonical archives.

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
- `objdiff.json`: the generated code, initialized-data and stored-asset project.
- `data/`: independently assembled data references, C/SDK candidates and linked image proofs.
- `storage/`: target-only objects for unreconstructed asset spans, grouped by storage region.
- `owned/`: combined source/SDK targets and `verification.json`, proving the exact
  grouped report inputs reproduce all six original code and data images.
- `targets/`: isolated splat configs, original full assembly, normalized copies,
  target objects, linker scripts, linked validation images, and logs.
- `coverage.json`: range ownership, source/SDK mappings, target link proofs,
  excluded zero ranges, cache keys, object hashes, and any compiler failures.
- `validation.json`: US profile, snapshot revision/fingerprint, modified-input status,
  report hash, exact denominator checks, bounded-storage partition proof,
  timings, native measures, and existing tracker totals.
- `self-changes.json`: the report compared with itself through objdiff's native
  parser; it must contain no changed units.

Generation checks every reported unit's code count against its audited target
symbols, reconciles the aggregate denominator and excluded zero bytes with the
mapped ranges, and verifies that project source inputs stayed stable and the
validated target objects did not change. Compilation failures remain explicit
in coverage, retain the reference in the denominator, and produce a failing
command exit status. See each unit's `build.log` for diagnostics.

Report freshness requires the font, texture and model source inputs used to produce their candidates.
Cleaning `build/` invalidates that evidence (and usually removes the report itself);
recreate the inputs and regenerate the report after cleaning. During preparation,
completed source units run Make before the cache check so the cache hashes the
current actual build object. This adds per-unit Make overhead; it is not a promise
that every object is recompiled. Run report generation after ROM-enabled tests
and other builds finish, because they can update the same linked objects.

### Scope

The published report covers the project's **tracked US CPU-code ranges and
initialized main/GAME/debugger data images**, plus **all bounded font, flat and
indexed asset storage**. Its Data denominator is **65,120,512 bytes**:
201,632 initialized CPU-data bytes (7,824 main, 189,088 GAME and 4,720 debugger)
and 64,918,880 stored asset bytes. The asset total includes the entire flat
archive, its alignment gap, the outer bank index, all 30 bank ranges (including
inner indices and gaps), and font storage. See the
[storage accounting evidence](evidence/data-layout/us_asset_storage_accounting.md).

The rebuilt font, reviewed textures, models, animations and audio retain their
independent comparison and completion gates. All remaining bounded asset bytes
have independent ROM targets **without candidates or completion credit**. In
particular, identifying a model bank or repacking original encoded MP3 streams
does not automatically establish reconstruction credit. Newly reconstructed
ranges replace their own unmatched storage spans, keeping the denominator fixed.

Every physical asset byte is counted once. Loaded CPU data and code are measured
in decoded bytes; their compressed GAME archive backing is not counted again.
BSS, unassigned ROM regions before the font/flat archives and after the final
bank, boot code outside tracked ranges, RSP and EU/PAL remain excluded. The sum
of Code and Data is therefore not a partition of the physical ROM size.

All asset storage contributes to the single Data category in the public report.
Storage families remain recorded in the coverage evidence, including their
metadata and gaps, without separate dropdown categories. Bank-family labels are
optional evidence metadata; unlabelled banks are recorded as `unclassified`.
Textures embedded in models do not add another stored allocation.

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
only when its code and every owned data range qualify through the actual build
inputs and independent ROM checks. ROM-identical, relocation-free main SDK data
linked through canonical archive placements is eligible. Debugger source data
requires candidate/linked-object equivalence and a full runtime-image ROM proof.

Completion and native matching are independent measures. Generation passes the
verified eligibility through `metadata.complete` to stock objdiff, which computes
`complete_code` and `complete_data` without changing `matched_code` or
`matched_data`; see the pinned release’s
[report implementation](https://github.com/encounter/objdiff/blob/v3.8.1/objdiff-cli/src/cmd/report.rs#L339-L342).
It does not patch the report or require native data matching to
approve independently proved completion. `completion_notes` in validation lists
complete units with lower native data matching and explains the distinction.
The legacy top-level `complete` option is rejected, and completed data must have
a candidate. Source, linked-object and reference hashes, relocation checks and
complete denominators remain mandatory. Stock objdiff also uses completion as a
fallback percentage when a section has no comparison; the verified report changes
three zero-byte SDK `.text` percentages, without changing any matched byte count
or nonempty-section comparison. Private/INFO/NOLOAD data still supplied by preserved
ROM streams remains incomplete, even when its C owner has integrated code.
A selector such as `*foo.o(.rodata)` alone does not establish that the ROM uses
that object's bytes. Source-owned INFO/NOLOAD placements retain raw ROM or
original GAME-data archive backing, which must be replaced and verified before
completion. Both debugger C units have allocated `.data` and `.rodata` placements in the
canonical profile, with actual runtime-input and whole-image verification.
Native percentages come directly from the unmodified release. Stock objdiff
bounds a data comparison by the last named symbol and compares REL words byte
for byte, so IDO's anonymous switch tables and literals would otherwise leave
the formatter's `.rodata` unmatched. For completed debugger source owners only,
generation compares a copy of the actual linker input (`owned/<key>/base.o`,
built by [`objdiff_candidate.py`](../scripts/objdiff_candidate.py)). The copy
names anonymous tables and doubles found from the candidate's own dispatch
instructions and relocations, and moves each table entry's REL addend into a
destination label. Names come from runtime-ELF anchors, never the reference or
ROM. An independent verifier re-derives every permitted change and checks all
relocation destinations; both copies must link to the runtime ELF bytes.
`validation.json` records each proof under `comparison_copies`. Objects without
anonymous references keep the actual input. Changed literals, table order, case
counts or placement still lower native matching; see the
[formatter evidence](evidence/debugger/debugger_printf_rodata.md#integrated-comparison-copy-2026-10-12).
The independent reference disassembly includes original rodata context for
switch destinations.
The maintained TLB source `src/debugger/tlb.s` supplies an assembled candidate.
Its `Original assembly` unit earns native matching and linked completion only
after full-span candidate and runtime-image verification. Native matched code
includes assembly source; the separate C-only inventory still excludes TLB.
Generated fallback assembly remains ineligible for native source credit.

Known SDK data names and payload sizes come from `config/symbols/us.txt`.
Declaration-backed zero alignment padding stays anonymous in the reference,
while every byte remains in the section and ROM checks. This avoids treating
splat's generated padding labels as missing SDK variables. See the
[SDK symbol evidence](evidence/data-layout/us_sdk_data_symbols.md) for remaining
anonymous pools and incorrect SDK symbol extents.
Native comparisons determine perfect-match credit. Every final unit must satisfy
`complete_data <= matched_data`; category or aggregate totals cannot hide a
violation. Units whose data is still ROM-backed need actual build integration
before they can become complete. This includes preserved GAME data. All debugger initialized data is now allocated
source storage and is compared natively as described above.

When this report is first published, fully-linked code can decrease for two
reasons: a grouped unit owns data still supplied by ROM, or its linked data fails
native symbol matching. Native matched code and function inventory records are
unchanged by this completion policy; the drop reflects a stricter whole-unit gate.
Rebuilt font bytes contribute to Data. The font earns completion when all 95 editable
PGM glyphs and their manifest rebuild through the canonical Makefile rule into the exact original 5,440 bytes
(including 13 alignment bytes). Its candidate concatenates the `.data` payloads of the 96 actual ROM link inputs:
`build/us/assets/font/glyphs/0000.o` through `0094.o`, then `font/padding.o`.
Each input's extent and hash is checked; its independent target comes from the
checked ROM. Both aggregate binaries use the same ordinary linker wrapper.
Canonical YAML boundaries must agree. Changed glyphs remain in the denominator
but cannot retain completion when their rebuilt bytes differ. This does
not change function match records or certify original source-object boundaries.

[The 6,865 selected textures](evidence/data-layout/us_texture_reconstruction.md) are independently
rebuilt from indexed or truecolor PNGs through fresh RZIP compression.
Mipmap bundles require every declared level and a consistent shared palette.
Explicitly verified zero alignment is regenerated; opaque tails are unsupported.
Independent texture references use four bounded workers with unchanged byte and source-hash gates.
Each candidate is the actual ROM link object, checked against a fresh encode;
each target comes from the checksum-validated ROM. Changed texture pixels,
palette, metadata or compressed output fail this exact-reconstruction pilot.
The 8,284,692 reconstructed stored bytes enter Data once; decoded bytes do not
add storage, and adjacent raw storage remains in the denominator without credit. Native matching and source/link-input verification gate completion.

[The 914 selected assets in banks 01, 02, 03, 04 and 09](evidence/data-layout/us_model_reconstruction.md)
reconstruct native headers, vertices, display commands, normal records, attachment
part/joint tables, bundle descriptors, primary surface tables, vertex-color
animation, effect command lists and emission points through fresh RZIP
compression, plus uncompressed native animation channels. The selection contains
183 native characters, 517 standalone models, 53 bundles,
20 emission-point arrays and 141 native animation containers, totaling 6,726,278
stored bytes. Their actual ROM linker inputs and independent stored-byte targets
use the same native matching and source-stability gates. Raw bank index, gaps
and unselected records remain in the Data denominator without credit.

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


### Compact audio sequences

[All 149 bank-17 compact sequences](evidence/data-layout/us_sequence_reconstruction.md)
reconstruct 684,228 bytes from native headers, MIDI events, tempo and loop
fields, and explicit back-reference plans. Actual ROM linker objects and
independent original-ROM targets enter native Data through the same source
and object stability checks. Descriptor tables, sequence padding and MP3 streams retain their existing
reconstruction status.


### B1 sound-bank records

[Typed control and 26 external sound-bank regions](evidence/data-layout/us_sound_bank_reconstruction.md)
reconstruct 434,837 stored bytes from native bank, instrument, sound, envelope,
key-map, wavetable, predictor-book and loop fields. Fresh control compression,
actual linker objects and independent targets gate native Data credit. The
656 unexplained external bytes stay raw and unmatched.


### Complete ADPCM samples

[Complete PCM sample reconstruction](evidence/data-layout/us_adpcm_complete_reconstruction.md)
produces 2,258 sample units totaling 21,705,520 bytes, covering the entire native
sample-storage entry. PCM16 sources and 115 Float32 sources with retained
pre-saturation headroom derive fresh residual nibbles. Native lengths determine
8,131 bytes of zero alignment. Actual linker objects and independent targets
gate native Data credit. Recovery can back up one sample or the complete source
tree before restoring reviewed inputs.

ADPCM source decoding and fresh report encoding use process workers, controlled
by `CONKER_JOBS` (default four). Build batches reuse verified unchanged sample
outputs, while reports always encode current sources independently of those
build receipts. See the [review follow-up](evidence/data-layout/us_asset_review_followup.md)
for cache invalidation, recovery and regression-test details.

### Native characters

[The 183 selected bank-01 characters](evidence/data-layout/us_bounded_compression.md)
rebuild native headers, vertices, both display passes, joint pivots, texture
descriptors, signed normal pairs and procedural indices through fresh pinned
compression. Their 772,691 stored bytes are reconstructed; index and gaps
remain unmatched. Decoded bytes do not add another allocation.


### Native character animation

[The 119 selected bank-02 animation containers](evidence/data-layout/us_animation_reconstruction.md)
reconstruct 3,752,256 uncompressed bytes from typed descriptors and 54,355
source frames. Native masks, bases, bit widths, translations and root/rotation/
scale offsets reproduce each full stored extent. Duration and channel bounds
exclude unresolved tails and duration cases without native evidence. Independent native pose
comparisons and actual linker objects gate the same bounded Data credit.

[The single-pair extension](evidence/data-layout/us_single_pair_animations.md)
adds 22 containers and 30,712 bytes, for 141 containers and 3,782,968 bytes.
Three entries use the verified 641-frame duration constant; 19 use their
descriptor/default durations. The bank-04 scene contract remains unchanged.

[Partial animation clip reconstruction](evidence/data-layout/us_partial_animation_clips.md)
rebuilds another 117 complete clips (219,664 bytes) inside entries 82, 83,
124 and 146. It uses the actual three linker objects but grants credit only
to the independently verified descriptor/frame ranges. The four unexplained
sibling clips and all container directory bytes remain uncredited.


### MP3 decoder tables

[Three bank-17 decoder tables](evidence/data-layout/us_mp3_table_reconstruction.md)
reconstruct 59,552 stored bytes from canonical C Huffman seed records. Typed
codebooks generate the relative trees, their offset table and eight-bit fast
lookup entries. The asset build and native report freshly encode editable
records and compare actual linked objects against independent ROM targets.
Stream reconstruction is separately gated by the coefficient sources below.


### Character morph endpoints

[The complete bank-13 morph storage](evidence/data-layout/us_morph_reconstruction.md)
reconstructs 19,832 bytes from 6,882 signed XYZ positions. Fresh RZIP encoding
and generated nested pair tables reproduce the original bank, including all
indices and alignment. The actual ROM linker object is independently checked
against both editable endpoints and original ROM bytes; whole-bank credit
replaces its previous unreconstructed storage unit.


### MPEG-2 spectral coefficients

[Reviewed complete frames from 453 streams](evidence/data-layout/us_mp3_spectral_reconstruction.md)
reconstruct 23,165,336 stored bytes from native header fields, scalefactors and
signed quantized coefficients. Actual whole-stream ROM objects are checked
against fresh encoding, then only proved frame slices enter native candidates.
Explicit physical ranges preserve provenance and subtract those same bytes
from unmatched storage. Opaque cues, reservoir tails and trailing storage stay
unmatched; repacking their original encoded bytes grants no credit.


### Event programs

[The complete bank-14 event storage](evidence/data-layout/us_event_reconstruction.md)
reconstructs 169,880 bytes from 203 programs, 62,491 instructions and 272
constant strings. Instruction and string labels generate native offsets; fresh
level-6 compression and generated bank tables reproduce the entire allocation.
Actual linker objects, current editable sources and independent ROM targets
gate native Data credit, replacing the same-sized raw-storage unit.

### Sprite PNG sources

[Reviewed bank-00 sprites](evidence/data-layout/us_sprite_reconstruction.md)
rebuild 56 entries from RGBA5551 and I4 PNG planes with the native upload and
sampling layout. Native credit includes only their 273,397 exact stored
bytes. The actual whole-bank linker object must agree with fresh PNG
encoding and preserved backing inputs; its index and padding remain in the
unmatched raw remainder. [Bounded compression](evidence/data-layout/us_bounded_compression.md)
resolves the five previous compression mismatches.


### Visibility codebooks

[Reviewed bank-05 visibility codebooks](evidence/data-layout/us_visibility_reconstruction.md)
rebuild 12,545 stored bytes from explicit byte-symbol Huffman codes. Tree
allocation is derived from unique prefixes, and fresh compression must match.
Sixteen paired bitmaps also rebuild from [visible-node sets](evidence/data-layout/us_visibility_bitmaps.md),
adding 151,949 bytes. Three bitmaps with unexplained node bits, the bank index
and padding remain unmatched.

[Actor paths and navigation graphs](evidence/data-layout/us_route_reconstruction.md)
rebuild 43,813 stored bytes across banks 10 and 19. Editable path indices retain
shared pointers; graph records retain ordered neighbor links and native controls.
Full native consumers and independent actor-placement counts gate the sources.
Only selected entry ranges receive credit; two unproved graph variants and all
bank index/gap bytes remain unmatched.


### Scene trigger volumes and spheres

`./conker scene-volumes build` reconstructs 3,204 trigger volumes and 177
collision spheres from typed records. The actual bank-0C linker object is
verified in full, but only 170,856 regenerated child bytes enter the bounded
`assets/scenes/volumes` unit. Directories and other scene children remain
unreconstructed. See [native scene evidence](evidence/data-layout/us_scene_volumes.md).

[Additional scene fields](evidence/data-layout/us_scene_fields.md) reconstruct
34,702 bytes of model transforms, group references, spawn/view fields and sprite
choices. `./conker scene-fields build` composes these with the volume sources
into the same actual bank object. Separate bounded report units prevent credit
for unproved fields or directory/padding bytes.

[MPEG partial-frame fields](evidence/data-layout/us_mp3_partial_frames.md) extend
the spectral units to final typed headers and complete coefficient bytes.
Incomplete reservoir bytes, cues and arbitrary stream tails stay uncredited.
