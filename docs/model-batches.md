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

Reviewed fragments and the stationary tank's appearance blocker are retained in
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
The 29 published assemblies include scenes 40 and 51, which expose deferred
components `04:0040:07`, `04:0051:01` and `04:0051:04` in ROM placement context.
Their standalone decisions remain deferred; scene inclusion is not native
appearance or simultaneous-visibility proof.

The gallery's **Extracted review** tab exposes every remaining ROM record without
changing these triage decisions. It is generated from the ROM-only manifests and
current review fingerprints by `model-assets inspect`. Thumbnail rendering is
cached by source content and renderer identity; existing validated renders can
be reused. Files still require current glTF and Blender import evidence, even
when their materials or appearance remain unresolved. Review exports are stored
in a separate folder and `review_models` manifest list, so they do not inflate
the batch driver's curated publication count.

Gallery publication shares assembly-set verification within each read phase and
repeats it independently before writing outputs. Triage likewise verifies each
assembly set once during collection and once in an independent final phase.
Every scene lookup checks the manifest hash; the final phase recomposes the
current components, selections and output bytes. Evidence never survives a
scan, and standalone verification remains uncached. This requires two whole-set verifications per report regardless of the number
of published assemblies. Focused tests
cover reuse, separate scans, changed manifests between lookups and component,
selection or output changes before the final phase.

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

On success, the existing inspection publisher refreshes only already-approved
entries. It verifies current source and image fingerprints and packs embedded
resources. The batch driver does not add models to the gallery, accept baselines,
change the roadmap's counts automatically, commit files or claim native parity.

[model-batch.json](../config/model-batch.json) controls the three preview corpora
and input paths. Logs, journals and exports remain ignored. Use
`--batch-config`, `--output` and `--blender` for explicit local overrides. These
commands need the owned US ROM and the locally generated inputs required by the
existing extraction/validation configuration.
