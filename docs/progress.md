# Progress reports

[Public US objdiff report](https://decomp.dev/DevOldSchool/conkers-bfd-decomp/us?category=all)

The project has one progress percentage: native objdiff `matched_code_percent`
for version **us**, **all** categories. It covers the tracked main/game/debugger
CPU code, including SDK code. It does not cover data, assets, other boot code,
RSP or EU/PAL.

Local and public numbers come from the same generator. The approved-main workflow
runs `./conker build --all` and `./conker objdiff report`, then uploads the
unmodified `report.json` that decomp.dev displays. Running the same command
locally produces the same report for the same inputs. The public page names its
source commit and can lag main while verification or ingestion is pending.

## Read progress

```sh
./conker progress                    # objdiff status plus inventory counts
./conker progress --inventory-only   # inventory counts only; no report needed
./conker progress render             # save build/progress/progress.md and summary.json
./conker progress check              # validate canonical inputs and renderers
```

These commands never build, fetch, install tools or read a ROM. `progress` reads
`build/us/objdiff-report/report.json` and `validation.json`. The headline is
current when the report's input fingerprint matches your checkout. The fingerprint
covers `src/`, `include/`, `config/`, `progress/`, `lib/` (including the SDK
submodule), `scripts/` and the build files, including uncommitted edits. A commit
that changes none of these keeps the report current. Otherwise the headline reads
**unavailable** and shows the last snapshot's figures, labeled as not current.
There is no fallback to inventory figures.

To refresh the headline, use your configured US ROM, the initialized SDK and the
Docker toolchain (see [setup](../CONTRIBUTING.md#setup)):

```sh
./conker objdiff report
```

Generation takes several minutes. See the
[objdiff guide](objdiff.md#full-repository-cpu-code-report) for its outputs and
validation. Reporting is diagnostic: full-span, relocation, layout and
byte-identical acceptance gates are unchanged.

## Inventory counts

The inventory section lists counts, not percentages: matched, raw, blocked and
deferred functions; verified original assembly; reviewed and completed source
units; mixed C/ASM units; unassigned functions; and registered-span byte totals.
These come from `progress/functions.json` and `progress/source_units.json` and
need no ROM or build. Registered-span byte totals are bookkeeping and can differ
slightly from objdiff's byte counts; see
[interpreting differences](objdiff.md#interpreting-differences).

Generated files under `build/` are ignored. Commit inventory, source and evidence
changes, never rendered reports. Matching and integration transactions refresh the
local views and restore them on rollback.

## Migrating existing branches

When an older branch conflicts on `progress/summary.json` or
`progress/badge-*.json`, keep the deletion. Keep this guide over the old generated
`docs/progress.md`. Resolve inventory conflicts semantically, never with a union
merge, then run `./conker progress check`.
