# Maintainer-only US verifier

Deploy this bundle to the **private** `DevOldSchool/conkers-bfd-verifier` repository.
Place `verify-pr.yml` at `.github/workflows/verify-pr.yml`; keep the Python files
and `settings.json` at its root. Do not install this workflow in the public repo.
The public copy is reviewable source, not an active ROM workflow.

## Owner setup

1. Keep this repository private and limit write access to trusted maintainers.
   Protect `main` and require owner review of all verifier changes. Dispatch only
   from `main`. Untrusted public PR contributors must not have access to this repository.
2. Create a `rom-verification` environment. Allow only the `main` branch and
   set required reviewers if your plan supports them. On the current plan this
   feature is unavailable: there is **no environment approval gate**. Instead,
   the workflow accepts only manual dispatches and reruns by `DevOldSchool`
   (immutable actor ID `168640902`), with an explicit reviewed-revisions checkbox.
   Every credentialed job repeats the actor check, including job-only reruns.
   Set `ROM_ASSETS_READ_TOKEN` to a fine-grained,
   expiring token with **Contents: read** on `conkers-bfd-assets` only. Do not
   reuse a broad personal token. The checkout uses only the US file and never
   persists credentials into Git configuration.
3. Create a private GitHub App with webhook delivery disabled, installed only
   on `DevOldSchool/conkers-bfd-decomp`, with **Commit statuses: write** (metadata
   read is implicit). The configured App ID is **5045941**. Store this numeric
   `VERIFIER_APP_ID` and its PEM
   `VERIFIER_APP_PRIVATE_KEY` as secrets in a separate `status-publisher`
   environment restricted to `main`. These credentials are never given to the
   ROM/build job. Public PR workflows need neither secret. The existing approved-main
   reporting workflow retains its separate ROM-access environment.
4. Review `settings.json`. Its initial trusted public-project revision is
   `5cefc17f41b4fe0e4e4005eaa89b3bbbd63802b9`, the maintainer's PR #12 snapshot.
   The image is the published OCI index for main `f2caf3aac99a5e6f9aaa796a674821101a97de0c`:
   `sha256:b3e29a92f2c26f11a58fbafde2d5d3b1184416e21b635e07b2a6303591ed5c8b`.
   Its Dockerfile and tool inputs are unchanged in the PR snapshot. The old image
   pin was not retrievable anonymously during setup; its original
   publication history is unconfirmed. The US ROM/game hashes remain those
   of the trusted snapshot. Promote a new tooling revision only through explicit maintainer review of its scripts,
   Makefiles, dependencies, compiler configuration, and reference definitions.
5. Dispatch **Private US verification**, supplying the PR number, full reviewed
   head SHA, and current full base SHA. Review the workflow revision and inputs,
   then check the reviewed-revisions box. Clicking Run workflow is the approval;
   no later approval screen is provided on the current plan. An agent account
   cannot dispatch this workflow. Keep private repository write access restricted:
   writers able to change trusted workflow code can change its safeguards.
6. After the named public gate and private result both pass, run the public
   repository's `scripts/configure_pr_protection.py --pr N --app-id 5045941` to preview
   the rules migration; rerun with `--apply` from an owner/admin session. It
   preserves unrelated rules and the existing review-count policy, replaces the
   legacy status, and binds the ROM result to this App. Do not enable unavailable
   required checks in advance. Once another maintainer joins, add a second
   eligible CODEOWNER and use `--require-reviews` to require fresh second-person
   reviews; authors cannot approve their own changes.

## Trust and verification

`verify.py` fetches immutable public revisions without checking out or executing
PR scripts on the host. It confirms the PR is open, targets main, and that the
merge parents are the approved base and head. Candidate paths, regular-file
modes, and the single fixed submodule are validated before export. Symlinks,
path traversal, and Make/shell metacharacters in paths fail closed.

Changes to executable tooling, workflows, assembly macros, linker/layout files,
reference definitions, or dependencies are rejected until the pinned trusted
revision is reviewed and updated. Only C/header source, function/progress data,
documentation, and test-source changes can differ automatically. PR tests run
in the public workflow only; the private run never executes them. This policy
must not be relaxed to work around an inconvenient failing PR. New source-unit
integration or build-tooling PRs may require a separate tooling promotion.
Inventory changes may update progress states and evidence, but registered
addresses, sizes, symbols, source ownership, unit membership, boundary evidence,
and integration modes must match the approved snapshot. Registering new spans
or changing these definitions requires promotion; a PR cannot shorten its own
reference span to claim an exact match.

Before ROM processing, the coordinator resolves the digest-pinned CPU image
and builds the same pinned RSP assembler extension as `./conker`. That networked
image-build context contains only the trusted `toolchain/rsp.Dockerfile`; it has
no ROM, PR source, or credentials. The completed image is selected by content ID.

The fresh verification container has no networking, credentials, host Docker socket, writable
host mounts, or host Git metadata. Its image is pinned, its root filesystem is
read-only, and CPU/memory/process limits apply. A temporary in-container copy is
used for the build. Only the sandbox script is mounted from the private verifier
checkout; the checkout itself, its Git metadata, and its diagnostics are excluded.
The ROM is read-only. The controller captures raw build
output into a private local file instead of printing it into Actions' workflow
command parser. No build logs, ROM-derived binaries, caches, or reports are
uploaded by this workflow. Private inputs and diagnostics are deleted afterward.
A local failed run retains its log for maintainer inspection until its work
directory is deleted; never paste that log publicly without reviewing it.

The sandbox checks metadata/progress, clean US main and game builds, independent
full-span focused diffs for changed matched functions and existing matches in
changed C units, and affected original-assembly proofs. Header changes recheck
all matches. It compiles each complete source unit once, including neighbouring
GLOBAL_ASM members, and checks reviewed symbol layout. Ordinary function-sized
spans use the existing focused compiler and byte-verified address-alias proof,
with that compilation also cached once per source. Spans extending beyond the
emitted function symbol use the complete source-unit object so real terminal
alignment bytes remain available. Every registered instruction word stays in
the comparison; padding is never synthesized or ignored. The trusted host independently compares the two final binary hashes
against the pinned reference hashes. Compiler/parser or container escape bugs
remain residual risks; sandboxing is defense in depth, not a proof of zero risk.

A separate fresh runner publishes only fixed pending/success/failure text. It
rechecks PR freshness and posts on the **synthetic merge commit**, binding the
result to both the base and the head. A new commit or base update needs a new
run. Failed/cancelled/stale runs cannot publish success; if publishing itself
fails, the required result remains missing or pending and must be retried.
No arbitrary file, log string, or contributor-provided status payload crosses
from the builder into the publisher.

## Local tests

The public repository has regression tests in `tests/test_ci_checks.py`.
The ROM-free compile gate is `python3 scripts/ci_checks.py compile` inside the
pinned toolchain image. A local private-verifier run needs explicitly approved
ROM access, a fresh work directory, and Docker; it makes no public status writes:

```sh
python3 ci/private-verifier/verify.py run \
  --settings ci/private-verifier/settings.json \
  --pr N --head FULL_HEAD_SHA --base FULL_BASE_SHA \
  --rom /absolute/path/to/baserom.us.z64 --work /private/tmp/conker-private-run
```

The status publisher requires the App secrets and is intended only for its
separate trusted workflow job. Never run arbitrary PR code in a credentialed
`pull_request_target`, `workflow_run`, or public approval-gated ROM job.
