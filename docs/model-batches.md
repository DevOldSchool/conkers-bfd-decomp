# Resumable model batches

Use the batch driver to keep repeated model work in local processes and return
short reports. It coordinates existing extraction, test, validation and inspection
commands; it does not invent texture bindings or mark visual comparisons complete.

```sh
# Refresh the triage report without exporting, rendering or starting an emulator.
./conker model-assets batch

# After a proven decoder fix, refresh all four banks and the approved gallery.
./conker model-assets batch --run

# Use a selected bank only when the fix is known to affect that bank alone.
./conker model-assets batch --run --bank 03

# Resume constructor argument research without exporting or publishing.
./conker model-assets batch --constructors --bank 09
```

The default report and journal are `build/assets/models/batch/report.json` and
`state.json`; full subprocess output goes to `logs/`. Console output is bounded
to stage transitions, counts and eight leading blocker groups. A successful
command means the requested workflow finished, not that all materials or native
appearance are complete. Missing inputs or failed stages return a nonzero exit.

## Review and investigation state

The report groups unpublished material blockers by decoder status and suggests
a representative with a large affected face count. Groups can overlap. Matching
failure strings are triage leads, not proof that all members share one runtime
consumer. Missing combiner state remains unresolved rather than being treated
as proof of an untextured draw.

`review-needed.json` contains material-complete unpublished models whose visual
review is missing or stale. Existing approved gallery entries remain selected;
their remaining material blockers are still visible in their report rows.

Reviewed fragments and the purple flamethrower imp's (model 66) appearance
blocker are retained in
[model-batch-reviews.json](../config/model-batch-reviews.json). Each decision binds
the manifest record and the actual glTF, buffer and texture contents. Changed
inputs reopen visual review. The initial decisions carry forward existing review
results; their fingerprints do not establish native appearance.

```sh
./conker model-assets batch --defer-model 04:0004:27 \
  --reason "Example: reviewed fragment needs room context"
./conker model-assets batch --defer-group runtime-segment \
  --reason "Caller-selected bindings need additional consumer evidence"
./conker model-assets batch --reopen-group runtime-segment
```

The model example is illustrative: only a model currently marked `review-needed`
can be deferred. Model decisions update the tracked review configuration. Group
investigations stay in the ignored journal and automatically reopen if member
inputs or decoder/tool source changes. Neither command approves a new gallery
entry or guesses a material. Add accepted models and render references through
the existing inspection and validation configuration after review.

Static scene assemblies are tracked separately in `published_scene_assemblies`;
they do not inflate standalone source-record publication counts. Their explicit
selections live in [model-scene-assemblies.json](../config/model-scene-assemblies.json).
Use `./conker model-assets scene-assemblies` to regenerate them. A batch run also
refreshes configured assemblies after its bank exports and before validation,
so component provenance stays current. See [the scene assembly evidence](evidence/us_static_scene_assemblies.md).
The 44 published assemblies include scenes 40 and 51, which expose deferred
components `04:0040:07`, `04:0051:01` and `04:0051:04` in ROM placement context.
Scenes 38, 39 and 66 additionally expose `04:0038:01`, `04:0039:01` and
`04:0066:01`, retaining the primary and secondary surfaces together.
Scenes 4, 16 and 19 additionally represent 23 deferred components; scenes
1, 56, 58 and 64 add another 16, and scene 10 adds two, bringing the
assembly-represented count to 221.
Their standalone decisions remain deferred;
scene inclusion is not native appearance or simultaneous-visibility proof.

Inspection records may declare `gallery_replaced_by` with another configured
export name. Replaced records retain validation and source-publication evidence
but have no card or README download; their replacement is the only visible
choice. Targets must exist, share the category and remain visible. Preserve
original names as aliases on the replacement. `gallery_count` and
`gallery_curated_count` count visible cards; `curated_count` retains the full
export count. Triage and extracted-review selection still use all curated
source identities, so replaced bases do not reappear as review cards.

The gallery's **Extracted review** tab shows records not already represented by
a curated standalone export or an approved scene assembly, without changing
their underlying triage decisions. It is generated from the ROM-only manifests and
current review fingerprints by `model-assets inspect`. Thumbnail rendering is
cached by source content and renderer identity; existing validated renders can
be reused. Files still require current glTF and Blender import evidence, even
when their materials or appearance remain unresolved. Review exports are stored
in a separate folder and `review_models` manifest list, so they do not inflate
the batch driver's curated publication count. After final provenance verification,
material-complete deferred components with exact source/assembly evidence receive
derived `gallery_represented_by` links. Their separate cards are suppressed and
their labels, ROM IDs and review filenames become searchable assembly aliases.
`review_count` remains the physical source-export count; `gallery_review_count`
and `represented_review_count` distinguish the presentation. Manual
`gallery_represented_by` configuration is rejected; blockers and stale reviews
remain visible. Source files and native-appearance limitations are preserved.

At the 2 October checkpoint, 612 physical review exports produce 369 visible
review cards: 221 are represented in assemblies and 22 share an exact exported
presentation with curated models. Of the 587 underlying deferrals, 344 remain
individually visible. The 22 material blockers, one appearance blocker and two
empty records remain separate. The gallery has 904 curated cards from 921
curated exports (875 indexed standalone, 44 assemblies and two embedded primitives), with sixteen base cards
replaced by assemblies and one cash variant consolidated: 1,273 visible cards
in total. These presentation counts do not include every remaining defect;
three curated models still have 43 unresolved texture faces, and native
appearance remains an independent gate.

Current validation passes 5,450 file entries and 975 render cases, with the
eight known render comparisons still incomplete. The current model suite passes all 855 tests. The animated entry-66 and scene-55 Blender publications preserve every one
of the 1,531 raw GLBs and all 1,527 unrelated preview files; the two records without
drawable geometry still have no preview. Each replaces its existing card's one
download. Entry 66 retains its appearance-blocked status. Desktop and mobile
browser checks verify both downloads, source-name search, scene-base aliases and
cash-card consolidation. Separate fresh Blender reconstruction verifies the
animated rig's 294 pose/view samples and scene 55's independent texture sampling. The new
type-13 card adds a separately verified counter-5 I8 inspection: 2,048 raw pixels,
24 RGB/alpha/clamp samples and five coherent-mutation rejection checks, including
saved camera framing. All 1,531 earlier records and 3,062 published artifact
files were unchanged by its publication. That checkpoint retained 1,532 raw GLBs; the subsequent type-6 card adds one more.
Desktop/mobile checks confirm one card and one linked Blend for the new primitive.

The optional `embedded_type13_inspection` setting selects the supported
counter-5 material artifact through its build output path. The batch driver
creates a missing artifact and verifies an existing one before inspection;
failed verification preserves the gallery. The publisher admits this primitive
separately from indexed-bank reviews: fresh ROM reconstruction and Blender
reopen verification bind its original source, and the pinned Khronos validator
checks that glTF with current dependency bytes. Final preflight checks all
source, manifest, tool and artifact hashes. One parts/effects card links its
Blend while retaining the raw GLB in the manifest. No bank identity or native
appearance claim is invented. This independent check does not rewrite or
inflate the main validation report's indexed/assembly counts.

For historical comparison, the previous full 1,194-test suite reported 1,181
passed, 11 skipped and two known macOS baseline failures. The earlier
43-assembly validation was an unpublished intermediate checkpoint (5,449 files;
965 passed renders plus eight incomplete).

Assembly representation takes precedence over presentation equivalence. In this
batch, `04:0064:05/06/07` move from equivalence to scene-58 parts into scene-64
assembly representation. Thus 18 additional represented components reduce the
visible review queue by 15 (388 to 373), while the separate equivalent count
falls from 25 to 22. Compute totals from the final manifest subsets; adding
new representation counts alone would count these three records twice.

A fingerprint-bound review decision can also name `presentation_equivalent_to`.
After assembly representation, the publisher freshly compares eligible sources
with that visible curated target, including exact buffer/image bytes and all
standard glTF fields except asset metadata, names and diagnostic extras. Only
supported extensions qualify. Successful comparisons derive `gallery_equivalent_to`
and target search aliases; `equivalent_review_count` records this separate subset.
Missing or hidden targets, conflicting claims and stale source evidence stop
publication. A stale review decision cannot hide a card. Distinct ROM identities
and runtime questions remain in the manifest and the target's export details.


The bank-09 UI material changes for entries 162/164 reuse the implementation
from recovery commit `4f80ae55eeb322a170837319257ed0ab9da58c97`. Preserve that
provenance when rerunning the batch: the 49 restored ROM-only texture-linked
faces are integration of existing recovery evidence. Captured-material precedence
and geometry/UV/joint buffers remain unchanged; UI initial state is explicit,
with native opacity and animation unresolved. See
[the reused UI proof](evidence/us_ui_constructor_materials.md).

The original scene-49/53/55 appearance audit left the raw exports unchanged.
Scene 49 already uses opaque materials. Scene 55 now has a
[supported Blender inspection](evidence/us_scene55_dual_texture_inspection.md)
with a bounded second-TMEM-plane decoder and independent texture sampling; its
raw assembly GLB is preserved. A flattened PNG is not a correct substitute.
Scene 53 still requires per-view primitive/environment colors. ROM-initial zero
scroll is recorded separately from a live or first gameplay frame. Preserve these
[explicit limits](evidence/us_static_scene_assemblies.md#curated-combiner-limits-scenes-49-53-and-55)
when selecting the next batch; do not rerun the same source scan as a fix.

Gallery publication shares assembly-set verification within each read phase and
repeats it independently before writing outputs. Triage likewise verifies each
assembly set once during collection and once in an independent final phase.
Every scene lookup checks the manifest hash; the final phase recomposes the
current components, selections and output bytes. Evidence never survives a
scan, and standalone verification remains uncached. This requires two whole-set verifications per report regardless of the number
of published assemblies. Focused tests
cover reuse, separate scans, changed manifests between lookups and component,
selection or output changes before the final phase.

## Explicit material inspection

[Model appearance extraction](model-appearance.md) documents the capture-scoped
Scene60, Library155, Haybot and boat presets, separate ROM Haybot variants,
guarded bank09 consumers, event diagnostics and coverage semantics. These
explicit presets do not approve gallery publication or change the ROM-only
corpus by themselves.

## Character alpha frontier

`./conker model-assets alpha-frontier` audits the remaining bank-01 entries
154, 155 and 162 directly from ROM without extraction, rendering or publication.
It records palette hashes, primary face counts, texture-independent combiners,
conditional renderer table selection, guarded caller opacity calculations,
and exact bank-0E spawn records. The default targets share scene 60; source
record indices are distinguished from combined indices and live actor slots.
Use repeatable `--entry` values for
other decimal bank-01 identities. The result is evidence, not a selected render
preset or acceptance decision. See the [alpha frontier](evidence/us_character_alpha_frontier.md).

## Execution and resume

A run executes the Python suite, verifies each selected ROM bank, then refreshes
its configured ROM-only, ordinary comparison and captured-colour corpora. The
ROM-only character export uses ROM defaults and never receives a capture catalog.
Comparison catalogs remain separate inputs. The driver does not start emulator
captures or generate missing research inputs.

Successful verification/export steps are reused only when their commands,
source/configuration/ROM/texture inputs and recorded outputs still match. Deleted
or modified output files, changed inputs, failures and interruptions cause the
step to run again. The first run establishes its own records; it does not assume
an existing export was generated by current code. Resume by repeating the same
command. The journal is written atomically and a lock prevents simultaneous runs
in the same checkout, including runs using different journal directories.
Use one journal to retain a continuous resume and review history.

Constructor analysis uses that same journal. The report links to
`constructors-bank09.json` and includes the seven-model renderer queue. Analysis
follows constant arguments, stack fields, branch joins, delay slots and initial
ROM table reads. Unsupported paths remain explicit barriers. Candidate function
boundaries and initial data values require consumer review; they never grant an
export context. Unchanged analysis and its intact report are reused on resume.
Work on the shared consumer, then publish all accepted models together.

The bank-09 constructor report also includes `attachment_events`: a ROM-only
lookup from character animation routes to attachment create/remove actions.
It follows the native relative pointers and representative-character groups,
and records unresolved event lists explicitly. Use it to find an attachment's
parent and animation before investigating inherited textures. These references
do not establish gameplay reachability or grant export eligibility. See
[attachment animation events](evidence/us_attachment_animation_events.md).

Successful Python suite evidence is reused when the interpreter and repository
source, test, configuration and documentation inputs match. Failed or interrupted
tests run again. Export dependencies follow local Python imports, including lazy
imports; unrelated ASM automation scripts and gallery labels do not invalidate
exports. Layout, ROM, texture and capture changes still do.

The driver always invokes the authoritative validation gate. It hashes shared
inputs once per phase, then verifies every input in an independent final phase.
The report records content-read counts. Deleted or changed dependencies fail the
run. Blender workers retain their independent fingerprint implementation and
existing tool identities. The validator owns its existing content/tool caches;
regression comparisons have their own cache keyed by both PNG hashes and the
comparison/PNG-decoder code. Model changes do not invalidate unchanged image
comparisons. Missing or modified difference images are regenerated. The report
counts fresh comparisons separately from fresh renders.
the driver does not add an outer shortcut around capture or Blender dependencies.
Validation errors stop publication. New or changed incomplete render comparisons
also stop publication and produce `render-review.json`. Existing unchanged
exceptions are retained from the first run's validation snapshot across retries.
Review the changes and update appropriate baselines only after establishing their
cause, then repeat the run. Merely retrying does not approve an exception.

When the inspection configuration opts into `texgen_inspection`, the driver
then invokes `model-assets texgen-inspection` with the configured ROM and output,
forwarding `--blender` when supplied. Explicit `mode: animated` selects
`model-assets texgen-animation-inspection`; omitted mode retains the neutral
artifact. Other mode values are rejected. The output must be a child of `build/`.
A missing output is created; an existing output is always checked with
`--verify`. This stage runs on every attempt, without an outer cache. Incomplete
or stale existing artifacts stop the batch without being overwritten, before
the published gallery can change. Configurations without this opt-in retain
the ordinary GLB publication flow. A separate optional `scene55_inspection`
output invokes `model-assets scene55-inspection` under the same create/verify
and failure-preservation rules. Each enabled artifact replaces one existing
card's visible download and preview while retaining raw GLB/source evidence.
All artifact rechecks finish before any gallery file is written.

On success, the existing inspection publisher refreshes only already-approved
entries. It verifies current source and image fingerprints and packs embedded
resources. The batch driver does not add models to the gallery, accept baselines,
change the roadmap's counts automatically, commit files or claim native parity.

[model-batch.json](../config/model-batch.json) controls the three preview corpora
and input paths. Logs, journals and exports remain ignored. Use
`--batch-config`, `--output` and `--blender` for explicit local overrides. These
commands need the owned US ROM and the locally generated inputs required by the
existing extraction/validation configuration.

### Selected Haybot phase

The optional `haybot_inspection` setting creates or verifies the source-bound
`haybot-inspection` artifact before gallery publication. Existing artifacts
must pass fresh ROM reconstruction and a reopened Blender comparison; the
batch does not overwrite them. The current configuration selects phase0 and
updates Haybot's existing card with one Blend. Original source exports and
review counts remain unchanged. The 2 October checkpoint passes 670 model
tests, canonical create/verify, five coherent artifact mutation rejections,
and desktop/mobile download checks. Main validation report counts continue to
cover the original source corpus; the selected material proof is additional.

### Selected type-6 material

The optional `embedded_type06_inspection` setting creates or verifies the
`embedded-geometry --primitive type06 --material-inspection elapsed0` artifact
before publication. Fresh ROM reconstruction preserves four vertices, three
ordered faces and the stored vertex alpha. The selected translucent unlit GLB
is checked by Khronos and reopened in Blender, including six measured alpha
interpolation samples and reproducible previews. Coherently rehashed changes to
material opacity, vertex alpha, face order and preview are rejected.

The 2 October publication adds one parts/effects card with one derived GLB
download, retaining the raw diagnostic GLB separately. All 1,532 earlier records
and 3,066 published artifact files are unchanged. The gallery has 1,273 cards
and 1,533 raw source GLBs; review counts are unchanged. Desktop/mobile checks
cover the new GLB and all four existing selected-state Blend downloads, original
name aliases, and one-card scene/cash consolidation. The 687 model tests pass.
Native effect placement, runtime copies, inherited shading flags and raster
parity remain outside this selected material proof.
