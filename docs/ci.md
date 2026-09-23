# Continuous integration

Public PR workflows never download or handle a game ROM. The **PR validation**
workflow exposes these separate check rows:

| Check | What it establishes |
| --- | --- |
| Repository metadata | Valid function and source-unit inventories |
| Generated progress consistency | Committed progress agrees with inventory |
| PR whitespace and prohibited files | Committed base-to-merge whitespace is clean; prohibited paths, binary outputs and ROM signatures are absent |
| Python tests and shell syntax | Tooling regression tests and entry-point syntax pass |
| Toolchain image and compiler smoke test | The public image builds and IDO/debugger installations work |
| US C compilation (no ROM) | All tracked C units compile with pinned IDO after GLOBAL_ASM lines are omitted from temporary copies |
| GitHub workflow syntax | Checksum-pinned actionlint validates public workflows and the private deployment template |
| All public PR checks passed | Every public job succeeded; failure, cancellation, or skipping fails the aggregate |

Disabled deferred candidates remain disabled in the compile-only check. Neither
it nor the metadata check establishes instruction matching or link correctness.
The file-hygiene check detects common paths/extensions and N64 ROM signatures;
it is not a general detector for deliberately obfuscated copyrighted data.

Local rollout results and outstanding blockers are recorded in the
[verification evidence](evidence/pr_verifier_rollout.md).

## Protected pre-merge verification

The reviewable deployment bundle is [ci/private-verifier](../ci/private-verifier/README.md).
Its workflow runs **only** in the private `DevOldSchool/conkers-bfd-verifier`
repository. It pins reviewed project tooling and an immutable compiler image,
checks the approved head/base/merge revisions, and builds in a disposable offline
sandbox without credentials or writable host mounts. It verifies affected
matched functions and clean US integration, then independently checks the output
binary hashes on the trusted host. Build logs and ROM-derived files never become
public artifacts or check descriptions.

Private comparisons cache complete and focused compilations by source unit.
The complete object preserves real emitted alignment for spans longer than the
function symbol; ordinary spans retain the existing focused address-alias proof.
The independent raw reference still covers every registered instruction word;
no padding is invented or excluded to turn a failed comparison into a match.

A fresh publisher job supplies one fixed result named **US ROM verification
(maintainer approved)** on the tested synthetic merge commit. This binds success
to both base and head. New commits or base changes need a new run. The required
check must be bound to the dedicated GitHub App. Changes to build scripts,
workflows, dependencies, linker/layout files or reference definitions fail closed
until the maintainer reviews and promotes a new trusted tooling revision.
That includes registered addresses, sizes, source ownership and unit boundaries
inside the progress inventories; ordinary state/evidence updates remain allowed.

### Activation order

The current private-repository plan has no required-reviewer environment gate.
Approval therefore occurs when `DevOldSchool` manually dispatches the workflow
for reviewed revisions; owner identity and the review checkbox are enforced
before any secret-bearing job. Private repository writers remain trusted.

1. Deploy and review the private bundle. Configure its two main-only environments,
   ROM-access token, and dedicated status App as described in its README.
2. Publish the public workflow changes and verify all named jobs pass.
3. Dispatch the private workflow for that PR's reviewed full head and base SHAs;
   confirm its result appears on the exact merge revision.
4. From an owner/admin GitHub session, preview the existing ruleset update with
   `python3 scripts/configure_pr_protection.py --pr N --app-id 5045941`, then use
   `--apply`. It requires both new checks to have passed before replacing
   `metadata-and-tooling`, preserves unrelated rules, binds the ROM status to the
   App, and preserves the current review-count policy so the sole maintainer's
   own PRs remain mergeable after both verification gates pass.
5. When a second maintainer joins, add the appropriate CODEOWNERS entry and
   rerun the preview/apply command with `--require-reviews`. This adds one fresh
   second-person approval, code-owner review, stale-review dismissal, and approval
   of the latest push. Authors cannot approve their own PR; sensitive paths need
   another eligible code owner when their listed owner authors the change.

CODEOWNERS assigns review responsibility; it does not restrict contributors or
tools from editing or committing `progress/functions.json` or
`progress/source_units.json`. Review requests use the base branch's CODEOWNERS
file, and approval becomes mandatory only when the corresponding rule is enabled.
See [GitHub's code-owner documentation](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/about-code-owners).

Until these owner-side steps complete, the new protected gate is **not active**.
Do not treat deployment files or local tests as a passing protected PR check.
The current required check name must be migrated deliberately; changing YAML
alone cannot update GitHub rules. Failed, cancelled, or stale private runs must
never be reported as success. A publisher outage leaves a missing/pending check.

## Post-merge verification and publication

`rom-verify-main.yml` runs only against protected `main`, including when it is
manually dispatched. Its visible check is **Approved main — US build and
decomp.dev report**. Dispatches from other branches are skipped. It checks out
the event's exact `main` commit so the report matches the workflow revision. It
retrieves `baserom.us.z64` from the private `DevOldSchool/conkers-bfd-assets`
repository with the environment-scoped `ROM_ASSETS_READ_TOKEN`, then runs
`./conker build --all`. The future EU/PAL ROM is not exposed to or required by
the active verification job.

After the US build succeeds, the same job runs `./conker objdiff report` and
uploads **only** `build/us/objdiff-report/report.json` as the `us_report`
GitHub Actions artifact, retained for 90 days. The artifact contains one
top-level `report.json`; no ROM, assembly, object files, or private asset
checkout is uploaded. Build, report validation, target relinking, and compilation
failures prevent the upload. Report generation uses splat's full-disassembly
targets and requires their linked bytes to match both original US CPU-code
ranges. Native progress counts function-symbol bytes; zero-filled gaps outside
symbols are separately verified and recorded. This uses objdiff's native metrics
for the tracked US CPU-code ranges; [the objdiff guide](objdiff.md#scope-and-first-full-test) explains the
excluded data and the differences from the authoritative match tracker.

## Register with decomp.dev

1. Merge the tooling and workflow changes to `main` and let **Post-merge US verification and progress** succeed. Alternatively, dispatch that workflow on `main` after
   the changes have landed.
2. Confirm that the run exposes `us_report` with `report.json` at its root.
3. As a repository administrator, sign in at
   [decomp.dev project management](https://decomp.dev/manage/new) and register
   `DevOldSchool/conkers-bfd-decomp`, using the US report and Nintendo 64 platform.
   Describe the current coverage as tracked US CPU code; data, assets, boot code
   outside those ranges, and RSP microcode are not measured.
4. Optionally install the [decomp.dev GitHub app](https://github.com/apps/decomp-dev)
   for workflow notifications and progress comments. Public PR builds still have
   no ROM access and do not generate these reports.

The [official integration guide](https://decomp.wiki/tools/decomp-dev) describes
artifact discovery and registration. Uploading the artifact does not by itself
register the project.

## Toolchain isolation

The main-only **Publish toolchain** workflow records the registry manifest digest
in its job summary. Use that value when updating `toolchain/tools.lock.json`;
local Docker image IDs vary by storage backend and should not be assumed to
identify a retrievable registry manifest. Verify anonymous availability and compiler/build
compatibility before changing the pin.

Configure the `rom-verification` GitHub environment so that only maintainers
can use its secret. Do not add ROM secrets to public PR workflows or use
`pull_request_target` to validate forks.

Local toolchain commands default to the exact container digest recorded in
`toolchain/tools.lock.json`. Runtime containers have networking disabled, use a
read-only root filesystem, drop Linux capabilities, and do not mount Git
metadata or local setup. Source and ROM inputs are read-only; only generated
output directories are normally writable. Integration and libultra commands
receive their explicitly required additional writable directories.
`CONKER_IMAGE` remains an explicit override for locally built CI images. Docker
builds use an allowlisted context containing only the Dockerfile and its
explicit toolchain inputs.

Runtime research uses the same image. Mupen64Plus core, console UI, and HLE RSP
are built from the immutable revisions in `toolchain/tools.lock.json`; the core
is compiled with `DEBUG=1`, `DEBUGGER=1`, and interpreter support. The
repository wrapper mounts only the already validated ROM and project paths,
keeps container networking disabled, and stores emulator configuration in the
container's temporary filesystem.
