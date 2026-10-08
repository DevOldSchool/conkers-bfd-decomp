# Progress reports

[Latest published checkpoint](https://github.com/DevOldSchool/conkers-bfd-decomp/blob/progress-reports/progress.md)
· [Machine-readable provenance](https://github.com/DevOldSchool/conkers-bfd-decomp/blob/progress-reports/checkpoint.json)

The public report and README badges describe the latest **published verified main
checkpoint**, identified by source commit and verification run. They may lag main
while owner approval, verification or publication is pending. EU/PAL remains
informational. These reports summarize reviewed inventories; generation itself
does not verify matches, gameplay or assets.

## Local reports

Local reporting remains available without a ROM or Docker:

```sh
./conker progress          # Show current working-tree totals in the terminal.
./conker progress render   # Write local Markdown, summary and two badges.
./conker progress check    # Validate canonical inputs and exercise all renderers.
```

Open `build/progress/progress.md` in your editor's Markdown preview. JSON outputs
are beside it: `summary.json`, `badge-us.json` and `badge-eu.json`. The whole
`build/` directory is ignored. Render again after pulling changes if you want to
refresh saved files; `check` does not read, refresh or compare local snapshots.
A fresh checkout needs no generated files for validation. Supported matching and
integration transactions automatically refresh these local views, including
restoring/removing them when a transaction rolls back.

Continue committing and reviewing `progress/functions.json`,
`progress/source_units.json`, source/configuration changes and their evidence.
Never force-add generated reports. Canonical inventory conflicts still need
semantic review; do not union-merge them. All existing matching, layout,
relocation and exact-build acceptance requirements remain in force.

## Migration and first publication

After this change reaches main, update existing PR branches with main as usual.
For conflicts in `progress/summary.json` or `progress/badge-*.json`, retain their
removal. Keep this static `docs/progress.md` guide rather than old generated
Markdown. Resolve canonical inventory/source conflicts normally, then run
`./conker progress check` and `./conker progress render`. Commit the canonical
changes and conflict resolutions only. Old untracked JSON snapshots at the
retired paths are ignored and unused; local reports now live in `build/progress/`.

The first successful owner-approved exact-SHA main verification after merging
this migration creates `progress-reports` and publishes all report files in one
commit. There is no manual seed. Until it succeeds, the report/provenance links
may return 404 and Shields badges may show unavailable data. The static guide
and local commands work throughout; badge caches may take time to refresh.
Later failed, skipped or unapproved runs leave the previous published checkpoint
intact. Rerunning the main workflow can retry a failed publication; same/older
sources cannot replace a newer checkpoint.

The [CI guide](ci.md#approved-main-rom-verification) describes the separate
publisher, permission limits and concurrency protections. It changes neither
main nor contributor branches. If policy blocks its `contents: write` request,
an owner must review that separately; no new credential or setting is required
by the implementation itself.
