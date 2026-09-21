# Continuous integration

Public pull-request checks never download or handle a game ROM. They validate
project metadata, generated progress, shell syntax, unit tests, whitespace, and
the public Docker image build. The image check also compiles
`tests/fixtures/ido_smoke.c`, so a present-but-broken IDO installation fails CI.

`rom-verify-main.yml` runs only against protected `main`, including when it is
manually dispatched. Dispatches from other branches are skipped. It checks out
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

1. Merge the tooling and workflow changes to `main` and let **Verify protected
   ROM build** succeed. Alternatively, dispatch that workflow on `main` after
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
