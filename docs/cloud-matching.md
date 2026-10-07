# Cloud matching and reset recovery

Setup, isolation and recovery for `DevOldSchool/conkers-bfd-decomp` in a cloud
Linux executor. Read [AGENTS.md](../AGENTS.md), [CONTRIBUTING.md](../CONTRIBUTING.md)
and any relevant checkout-local `.agents/skills/*/SKILL.md`; some checkouts have
no such directory. Ordinary matching commands live in the
[workflow reference](decompilation-workflow.md).

## 1. Establish the checkout and ownership

- Honor the requested cloud environment. A fresh executor has no previous
  filesystem or logins; do not silently move work to the user's desktop.
- Verify repository URL, requested branch, full commit, dirty status and work
  owner. Preserve unrelated changes. Use isolated implementation checkouts:
  worktrees share Git metadata; independent clones also isolate branch/ref
  operations. Never reset, clean or rewrite another worker's checkout or branch.
- Assign one integrator ownership of canonical inventories, linker configuration,
  generated progress, acceptance commands and pushes. Review shared changes
  explicitly and coordinate disjoint source ownership.

Take the branch from the current task or handoff, not a past session:

```sh
branch='your-assigned-branch'  # Replace with the requested branch.
git check-ref-format --branch "$branch"
git clone --branch "$branch" https://github.com/DevOldSchool/conkers-bfd-decomp.git conkers
cd conkers
git remote get-url origin
git fetch origin
git rev-parse HEAD "origin/$branch^{commit}"
git status --short
git submodule update --init --recursive
git submodule status --recursive
```

For checkpoint reproduction, verify the manifest's exact commit in a new
isolated checkout: its branch may have moved. For live continuation, compare
the remote tip with the checkpoint and retain newer accepted work. Record the
selected branch, full commit and owner in the handoff, not this reusable guide.

Dependency pins are not progress checkpoints. The `lib/ultralib` pin is
`87af1e4d8ed666f2ad407dc11c6e47736094f2f8`; verify the selected checkout's gitlink
with `git ls-tree HEAD lib/ultralib` and initialize its exact submodules in every
build checkout. `doctor` can pass without a submodule required by real builds.
Never substitute a submodule's latest branch.

## 2. Restore the exact compiler environment

Use ordinary Docker with the repository's pinned image when available. On a
restricted Linux x86-64 executor where Docker/rootless Docker cannot operate,
use the reviewed [namespace adapter](../toolchain/cloud-bootstrap/README.md).
Its `bin/docker` wrapper routes supported `./conker` calls through `unshare` and
`bwrap` into the verified image root filesystem, without a Docker daemon.
It implements only the project's required subset; enhanced renderer/debug
images and arbitrary Docker operations are unsupported and fail closed.

Current immutable pins, also checked against `toolchain/tools.lock.json`:

- CPU image: `ghcr.io/devoldschool/conkers-bfd-decomp-toolchain@sha256:b3e29a92f2c26f11a58fbafde2d5d3b1184416e21b635e07b2a6303591ed5c8b`
- Linux AMD64 manifest: `sha256:3da4b9927f4cc0db09155734cf7572dbb379020ac93cad6c3e796b4ceef40d2b`
- Image configuration: `sha256:10a77ef378fd060dfec5756b8b195197fbf5c399c4f35798eb1ca9344c934fc8`
- IDO static recomp: `v1.2`; archive SHA-256
  `ab5c741561f80913d58c8b074771f23941a3edd312505a8ebed6d1dfeb65e506`
- RSP armips: `156f78f6bccfc07498578ac491ce7fe2a1e807a6`
- RSP recipe SHA-256: `b161bd2fdb84561aa0480fe553e1806420ba7f3caf648dffa0331b42b426713c`

The image does not supply the project's RSP extension. Bootstrap rebuilds
armips from pinned upstream source using the verified image's compiler and the
repository recipe; its CMake wheel is pinned by version and SHA-256. A reviewed
private recovery kit may supply the verified armips binary with its license and
receipt. Keep binaries, image layers, tool caches and recovery artifacts out of Git.

### Source-only bootstrap

Prerequisites: Linux x86-64, Python 3 with pip, Git, `/usr/bin/bwrap`,
`/usr/bin/unshare`, permitted unprivileged namespaces, and access to public
GHCR, GitHub and the Python package registry. Install missing host tools through
the executor's approved setup path. Namespace/network policy failures are blockers.

Choose a new writable runtime directory outside every repository:

```sh
repo="$PWD"
runtime=/absolute/writable/path/conker-cloud-toolchain
test ! -e "$runtime" || exit 1
mkdir -m 700 "$runtime"
cp -R toolchain/cloud-bootstrap/. "$runtime/"
python3 "$runtime/bootstrap.py" --rebuild-armips "$repo"
export PATH="$runtime/bin:$PATH"
./conker host-setup
./conker doctor
```

Restore this PATH in subsequent shells and keep the runtime warm across targets.
When adding a worker, coordinate with the integrator and pass all explicit build
checkout roots in one invocation: the allowlist is replaced, not appended. Never
allow a parent workspace or credential directory.

The adapter verifies OCI manifest/config/layer digests, CPU/RSP pins and armips
provenance. It uses unprivileged user/network namespaces, read-only root/source
mounts, no external routes, zero capabilities, NoNewPrivs and fresh PID/IPC/UTS/
cgroup namespaces. Only requested repository output mounts are writable.
RLIMIT_NPROC caps processes at 512 per real host UID, not per Docker cgroup.
Each execution creates fresh isolation from a saved mount recipe; `/tmp` is not
persistent. See the adapter README for verification and limits.

Never bypass failure with privileged execution, host networking, arbitrary
mounts, `--not-a-security-boundary` or mutable substitute images. Never mount
credentials, or change CPU flags or assembly to force a match.

## 3. Restore the private owned-ROM input and prove setup

Restore the user's privately supplied owned North American ROM through the
executor's supported private file-input mechanism. Verify it exists locally,
then copy it into this checkout's ignored `roms/` directory. Do not obtain ROMs
from public downloads or another decompilation repository.

```sh
mkdir -p roms
cp /private/input/owned-us-rom.z64 roms/baserom.us.z64
sha1sum roms/baserom.us.z64
./conker setup --us roms/baserom.us.z64
```

Required SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`, pinned in
`config/roms.json`. Stop on mismatch. US is active; EU/PAL does not gate work.
Never commit or publicly attach ROMs, extracted/generated ROM-derived payloads,
credentials, signed URLs or private input identifiers.

Before selecting new work, find an accepted C entry in this checkout's
`progress/functions.json` with `regions.us.state` equal to `matched`. Use its
top-level `symbol` and confirm its recorded source contains the C implementation:

```sh
known_match='accepted-work-item-id'  # Replace with the inventory symbol above.
./conker diff "$known_match"
./conker rsp
./conker build --all
./conker game-build --refresh
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

The smoke diff must report independent raw-assembly `CURRENT (0)`. If there is
no accepted C function, report that limitation and still run the other gates;
do not invent a match. `rsp`, the main ROM build and the game-image build verify
different outputs. Preserve logs, tested commit and tool pins. Neither the smoke
diff nor `doctor` replaces the full baseline gates.

## 4. Match efficiently without repeating exhausted work

Follow [matching a function](../CONTRIBUTING.md#match-a-function) and the
[focused iteration reference](decompilation-workflow.md#focused-iteration).
CONTRIBUTING.md owns attempt limits; AGENTS.md owns agent lookup budgets and
terminal-action handling;
[sustained manual matching](decompilation-workflow.md#sustained-manual-matching)
owns hypothesis reuse and durable attempt records.

Before selecting hypotheses, read relevant `docs/evidence/` and prior ledgers
under `build/us/manual-attempts/`. After a reset, restore private attempt records
separately from Git. Check source, reference, declaration/header/toolchain and
search-setting fingerprints before reusing results. If artifacts are missing,
report that limit rather than claiming an untried search. Carry the relevant
ledger, best artifacts and pending batch IDs across resets and worker handoffs.

## 5. Parallel source work, serialized acceptance

The integrator assigns disjoint source families, target IDs, base commit,
allowed files and hypothesis budgets. Each worker uses a separate checkout and
returns a source-only patch plus evidence and attempts. Workers must not edit
shared headers, linker scripts, canonical JSON or generated progress, or run
mutating commands in the integration checkout. Different workers must not edit
targets in the same C file concurrently.

Workers may inspect independently or test in fully initialized isolated
checkouts. A worker running `finish` locally must follow all acceptance rules;
return only the allowed source patch and report local state/evidence separately.
Worker acceptance never updates the canonical branch. Isolate generated output
and writable submodule build directories too, or serialize builds through the
integrator.

The sole integrator checks and applies patches one at a time, immediately runs
authoritative `finish` for each target, and handles shared changes, source-unit
integration and clean batches. Discard/rebase stale patches rather than
overwriting newer candidates. Resolve overlapping ownership before further edits.

## 6. Acceptance and checkpoint checklist

Follow [acceptance and integration](../CONTRIBUTING.md#acceptance-and-integration)
and the [clean batch gate](decompilation-workflow.md#builds-and-batch-verification).
Worker results and setup smoke checks do not replace canonical acceptance.
Preserve pending IDs until clean `BATCH_COMPLETE`; fix source/layout before
retrying a failed batch, and report unresolved groups in the handoff.

Before compaction, reset or handoff, retain the task ledger and ignored evidence
needed to resume. For an authorized commit, use explicit paths, inspect staged
content for private inputs and unrelated work, and record tested commit, focused
and batch results, attempts, changed files and limitations as required by
[review and handoff](../CONTRIBUTING.md#review-and-handoff). Do not merge unless
separately authorized.

## 7. Push safely, verify remotely, retain recovery fallback

Prefer ordinary Git push over large connector uploads. Verify the authenticated
account and exact HTTPS remote; reuse an existing authorized login. Never print,
read, copy or package the credential store.

Fresh authentication requires explicit user approval of the persistent grant.
Explain the installed CLI's requested scopes: `repo`, `read:org` and `gist`, for
example, grant account-wide access. Disclose a plaintext fallback if secure
credential storage is unavailable. The user completes the secure/device flow;
never request tokens or passwords in chat.

For a read-only home directory, create a mode-700 private configuration directory
outside repositories. Answer **No** to global Git-auth configuration and use the
helper only on the needed command. These placeholders are local values:

```sh
export GH_CONFIG_DIR=/absolute/private/outside-repos/github-cli
# For a new directory only, before the user-approved login:
mkdir -m 700 "$GH_CONFIG_DIR"
gh auth login --hostname github.com --git-protocol https --web
# Do not dump gh config, tokens, environment, or credential files.
gh api user --jq .login
git remote get-url origin

# Restore the assigned branch in a new shell; do not guess it.
: "${branch:?Set branch to the explicitly assigned destination branch}"
test "$(git branch --show-current)" = "$branch" || exit 1
sha=$(git rev-parse HEAD)
GIT_TERMINAL_PROMPT=0 git -c credential.helper= \
  -c 'credential.helper=!gh auth git-credential' \
  push https://github.com/DevOldSchool/conkers-bfd-decomp.git \
  "$sha:refs/heads/$branch"

gh api "repos/DevOldSchool/conkers-bfd-decomp/git/ref/heads/$branch" --jq .object.sha
git rev-parse "$sha^{tree}"
gh api "repos/DevOldSchool/conkers-bfd-decomp/git/commits/$sha" --jq .tree.sha
```

Require exact remote SHA/tree agreement before reporting success. If the remote
moved, fetch and reconcile with its owner; never force-push or reset another
worker's work. Read back the remote before retrying an ambiguous timeout. Check
CI for the exact published commit where available; it does not replace local
ROM-backed acceptance.

If push is blocked, preserve a private cumulative Git bundle and nonsecret
manifest with repository, branch, full head/tree SHA, parent/base, checks and
pending IDs. Include all history required to restore the branch:

```sh
git bundle create /private/output/matching-checkpoint.bundle "$branch"
git bundle verify /private/output/matching-checkpoint.bundle
sha256sum /private/output/matching-checkpoint.bundle
# Test restoration in a separate empty destination, never over active work.
git clone --branch "$branch" /private/output/matching-checkpoint.bundle \
  /private/output/restore-check
git -C /private/output/restore-check rev-parse HEAD HEAD^{tree}
```

Save bundle and manifest through the authorized private artifact channel. Keep
owned ROM input, attempt-ledger archive and toolchain recovery kit separate;
never include authentication material. Bundles omit ignored files, submodule
working trees, login state and uncommitted work; record those gaps. After reset,
verify artifact hashes and restored branch, initialize pinned submodules, restore
toolchain/ROM privately, then rerun setup and baseline checks.

## Diagnose persistent storage and address near-misses

The [matching conversion audit](evidence/matching/matching_conversion_audit.md) records
storage/address cases worth consulting before retrying a stable frame or
temporary mismatch:

- Preserve source/object hashes, compiler settings, raw span, full diff and
  failed forms. Map each differing stack access; a larger frame need not shift
  every object uniformly.
- Separate loop-carried values and aggregate storage from recomputable
  expressions/addresses. Debug homes can describe pre-optimization storage;
  distinguish them from runtime spills and predict the instruction/home change.
- Test the proposed source exactly, one relation at a time. Equivalent spellings
  can change register allocation; inspect the predicted change as well as score.
  Check control-flow form and declared storage separately: recovering one can
  disturb the other, and identical declared homes do not prove identical frames.
- Retain informative experiments and the best valid candidate under the normal
  ledger/acceptance rules. Never add padding, dummy values, volatile accesses or
  declaration permutations merely to consume bytes or force a frame. Stop when
  source/assembly evidence supports no new hypothesis.

These cases establish a diagnostic method, not a universal allocation formula
or measured throughput guarantee.
