# Progress reports

[Public US objdiff report](https://decomp.dev/DevOldSchool/conkers-bfd-decomp/us?category=all)

Local and public headline progress use native objdiff's `matched_code_percent`,
for version **us**, **all** categories. This measures the tracked main/game/debugger
CPU-code ranges, including SDK code, not whole-ROM completion. Data, assets, other
boot code, RSP and EU/PAL are outside this report. The public page identifies its
source commit; it can lag main while owner approval, generation or ingestion is
pending. Compare the same source inputs and commit before comparing percentages.

## Read progress without a build

```sh
./conker progress                       # Read local objdiff status and inventory.
./conker progress --inventory-only      # Inventory only; no objdiff files needed/read.
./conker progress render                # Save both views under ignored build/progress/.
./conker progress render --inventory-only
./conker progress check                 # Validate canonical inputs and renderers only.
```

These commands do not fetch, install tools, access a ROM or start Docker. A fresh
checkout can show inventory and validate it without generated files. `progress`
reads `build/us/objdiff-report/report.json` and its local `validation.json`. A
current headline requires a successful US report, matching report hash, current
Git revision and unchanged source-input fingerprint, including SDK inputs.
Report provenance shows the full source revision, US profile, input fingerprint,
report hash, and whether inputs were modified at generation. A dirty local build
can match today's working tree but does not represent the clean public commit.

Missing, stale, malformed, failed or older reports without provenance produce an
explicit unavailable headline. A readable stale report's percentage is labeled
as the **last snapshot, not current**. There is no inventory-percentage fallback.
Even an unrelated new commit makes the revision differ; regenerate to associate
the report with that commit. Uninitialized SDK inputs prevent freshness checking.

`render` saves `progress.md` and `summary.json` (including `objdiff` status).
The legacy local `badge-us.json`/`badge-eu.json` files remain clearly labeled
**inventory bytes**, with EU/PAL inactive; they are not used by the public README.
Open the Markdown file in your editor. Saved output is a snapshot: rerun after
edits or pulls. `check` neither reads nor rewrites snapshots and does not establish
objdiff freshness or a successful build. Matching/integration transactions refresh
these local views and restore/remove them when a transaction rolls back.

## Generate the current objdiff report

Use the pinned host dependencies, initialized SDK, Docker toolchain and your own
configured US ROM, as described in [setup](../CONTRIBUTING.md#setup):

```sh
./conker objdiff report
./conker progress
./conker progress render
```

Report generation is explicit and can take several minutes. It installs/verifies
the pinned native objdiff CLI if needed, builds SDK archives and active C, assembles
independent targets, and checks their linked bytes against the original US code.
It generates the same unmodified native report uploaded as `us_report` by the
existing approved-main workflow. It does not require a previous local summary. Failed generation does not establish
a current report. See [objdiff](objdiff.md#full-repository-cpu-code-report)
for generated artifacts, validation and scope. This is diagnostic reporting;
full-span, relocation, layout and byte-identical acceptance gates remain unchanged.

## Inventory details are a different view

Inventory reports retain reviewed/completed source units, mixed C/ASM units,
deferred candidate records, verified original assembly, unassigned functions and
regional registered-span byte counts. They derive from canonical function and
source-unit records, overlay ranges and mapped archive text. They need no ROM or
build. Original assembly and disabled deferred candidates do not earn C credit.

Inventory percentages and native objdiff percentages need not agree at the same
commit: registered spans can include padding outside native function symbols,
and objdiff report matching has different relocation rules. Native completed units
also include SDK objects and unassigned ranges; they are not the inventory's
reviewed-source-unit count. See [metric differences](objdiff.md#interpreting-differences).
No EU objdiff badge is displayed until an EU report exists. Native 100% data fields
with a zero denominator must not be presented as verified data coverage.

## Public badge and freshness

The README uses the official badge API with explicit scope:

```text
https://decomp.dev/DevOldSchool/conkers-bfd-decomp/us.svg?mode=shield&category=all&measure=matched_code_percent&label=US%20objdiff%20code%20match
```

The endpoint shape and measure are defined by the upstream
[URL builder](https://github.com/encounter/decomp.dev/blob/e9c086adb74d2fe569541cd715cd9312d7641313/js/api.tsx)
and [badge renderer](https://github.com/encounter/decomp.dev/blob/e9c086adb74d2fe569541cd715cd9312d7641313/crates/images/src/badge.rs).
The badge alone does not prove freshness: inspect the linked report's commit,
version and category. Site/badge caches and ingestion can lag. The service's
[importer](https://github.com/encounter/decomp.dev/blob/e9c086adb74d2fe569541cd715cd9312d7641313/crates/jobs/src/jobs/workflow_run.rs)
handles default-branch push runs; manual dispatch is not a guaranteed refresh.
Upload alone does not register a project; see [CI integration](ci.md#toolchain-and-reporting).

Live endpoint verification during this change was blocked by HTTP 403/access
restrictions. The syntax is checked against upstream source; no current public
percentage or checkpoint is asserted here. There is no additional publication
workflow, write token, report branch or Pages deployment.

## Migrate existing branches

When reconciling existing PRs with this migration, retain removal of tracked
`progress/summary.json` and `progress/badge-*.json`, and keep this static guide.
Old untracked snapshots at those paths are ignored and unused. Canonical inventory
conflicts still require semantic review; do not union-merge them. Commit source,
configuration, inventory and evidence changes, never generated reports. Run
`./conker progress check` and optionally render local views after reconciliation.
