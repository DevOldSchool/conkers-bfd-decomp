# Continuous integration

We use automatic public PR checks, local US verification before merge, and the
existing owner-approved ROM build after merge. Public PR jobs never receive a
ROM or private-storage credentials. There is no automated pre-merge ROM status.

## Public PR checks

The **PR validation** workflow exposes separate check rows:

| Check | What it establishes |
| --- | --- |
| Repository metadata | Valid function and source-unit inventories |
| Generated progress consistency | Committed progress agrees with inventory |
| PR whitespace and prohibited files | Committed changes have clean whitespace; prohibited paths, binary outputs and ROM signatures are absent |
| Python tests and shell syntax | Tooling regression tests and entry-point syntax pass |
| Toolchain image and compiler smoke test | The public image builds and IDO/debugger installations work |
| US C compilation (no ROM) | Active tracked C compiles with pinned IDO; GLOBAL_ASM is omitted only from temporary copies |
| GitHub workflow syntax | Checksum-pinned actionlint validates repository workflows |
| All public PR checks passed | Every public job succeeded; failed, cancelled or skipped jobs fail the aggregate |

Disabled deferred candidates remain disabled. Compilation and metadata checks
are not instruction-match evidence. File hygiene catches common paths,
extensions and N64 signatures, not deliberately obfuscated data.

## Local US verification before merging

A contributor or maintainer uses their own US ROM and Docker. Contributors
without a ROM can submit a PR and ask a maintainer to perform these checks.
Review host-side scripts, build configuration and dependency changes before
running a contributor's checkout: the Docker wrapper itself runs on the host.

Configure the ROM once with `./conker setup --us /path/to/baserom.us.z64`.
For function changes, use the normal [contribution workflow](../CONTRIBUTING.md):

1. Run `./conker finish <function-id>` while matching each function. Require
   independent full-span `CURRENT (0)` and the layout/progress/whitespace gates.
2. Run one `./conker verify-batch <function-ids...>` for the finished group.
   This checks clean integration, tests, metadata and progress; require
   `BATCH_COMPLETE`. It does not replace the individual focused checks.
3. Record the tested commit, commands and concise results in the PR. Recheck
   relevant evidence after source, header, build-input or base changes.

For shared build/layout changes, also verify the applicable complete images:
`./conker build --all` and `./conker game-build --profile us --refresh`.
Tooling-only changes need their relevant tests; documentation-only changes do
not require an empty function batch. US is active; EU/PAL does not gate work.

Local evidence is a maintainer review requirement, not a GitHub-enforced ROM
check or an uploaded attestation. Do not attach ROMs, generated assembly,
objects or raw private build logs to a PR.

## Required checks and reviews

The current ruleset still requires the old `metadata-and-tooling` name. After
the named checks pass on the PR, an owner must replace that requirement with
**All public PR checks passed**, select GitHub Actions as its expected source,
and retain the up-to-date branch requirement. Preserve unrelated rules.
Do not require a private verifier status: that proposed service is not used.
Changing workflow YAML does not migrate GitHub's required-check configuration.

Keep the current zero-required-review policy until another eligible maintainer
joins. Then add another appropriate code owner and enable the desired fresh
second-person and code-owner reviews. Authors cannot approve their own PR.

CODEOWNERS assigns reviewers; it does not prevent contributors or tools from
editing or committing progress inventories. Review requests use the base
branch's CODEOWNERS. See [GitHub's documentation](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/about-code-owners).

## Approved main ROM verification

The existing **Post-merge US verification and progress** workflow runs on main
pushes or manual dispatch from main. Its check is **Approved main — US build and
decomp.dev report**. It checks out the event's exact commit and uses the
`rom-verification` environment, restricted to main with owner approval.
The approval trusts that commit's workflow, scripts and dependencies; it does
not turn arbitrary contributor code into safe code. Do not extend this job to
PR refs or add a privileged `pull_request_target` trigger.

Configure these environment secrets without committing private repository names:

- `ROM_ASSETS_REPOSITORY`: the private ROM storage repository's owner/name.
- `ROM_ASSETS_READ_TOKEN`: an expiring token with Contents: read on that storage only.

The workflow builds the public toolchain before fetching private inputs, checks
out only the US ROM without persisting credentials, and runs `./conker build --all`
and `./conker objdiff report`. Report preparation validates linked targets for
both tracked US CPU-code ranges. Only `build/us/objdiff-report/report.json` is
uploaded as `us_report`, retained for 90 days. No ROM, assembly or object file is
an artifact. Cleanup stops the toolchain and removes the private checkout and
copied ROM; remaining generated files disappear with the disposable hosted runner.

Build/report failures block report publication. They occur after merge and
cannot retroactively prevent it; maintainers must handle the failure promptly.
See the [objdiff guide](objdiff.md#scope-and-first-full-test) for coverage limits.

## Toolchain and reporting

**Publish toolchain** runs only on main and records the immutable registry
digest in its job summary. Verify anonymous availability and compiler/build
compatibility before changing `toolchain/tools.lock.json`. A local Docker image
ID is not necessarily a retrievable registry digest. Runtime containers disable
networking, use a read-only root, drop capabilities and mount ROM inputs read-only.
The build context allowlist excludes private inputs and generated outputs.

After the approved-main report succeeds, a repository administrator can register
the US report at [decomp.dev project management](https://decomp.dev/manage/new).
Uploading the artifact alone does not register the project. Report coverage is
tracked US CPU code, not all data/assets, boot code or RSP microcode; see the
[official integration guide](https://decomp.wiki/tools/decomp-dev).
