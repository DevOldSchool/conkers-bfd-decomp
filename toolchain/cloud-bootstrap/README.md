# Source-only cloud toolchain bootstrap

Use [the cloud matching runbook](../../docs/cloud-matching.md) for setup,
private ROM handling, parallel ownership, verification and recovery.

This directory contains the nonsecret source of the September 2026 recovered
Conker toolchain adapter. Copy this directory to a writable directory outside
all checkouts before running `bootstrap.py`. It contains no executable compiler,
armips binary, ROM, extracted assets, credentials, private artifact IDs, or
machine-specific runtime state. It is not part of normal Docker execution.

```sh
python3 /outside/repos/conker-toolchain/bootstrap.py --rebuild-armips \
  /absolute/path/to/conkers
export PATH=/outside/repos/conker-toolchain/bin:$PATH
```

`bootstrap.py` verifies checkout image, armips and RSP recipe pins. It downloads
and verifies the immutable public OCI image, then fetches/rebuilds armips from
its pinned official upstream commit with a hash-pinned CMake wheel. The
`provenance/armips.json` receipt describes the original recovery-kit build. A
fresh build records its actual binary hash in local `state/armips.json`; the
adapter verifies that local receipt before execution. `--rebuild-armips` forces
a source rebuild; without it, a supplied private-kit binary is hash-checked.

Runtime requirements: Linux AMD64, Python 3 (and pip for the armips rebuild),
Git, `/usr/bin/bwrap`, `/usr/bin/unshare`, permitted unprivileged namespaces,
and allowed access to public GHCR, GitHub and the Python package registry.
The public image download is about 307 MB and extracts to about 935 MB, before
armips build/cache and repository build outputs. Do not assume a cached rootfs
is portable or untampered: fresh recovery starts in an empty runtime directory;
keep local state private and rebuild if its integrity is in doubt.

## Security contract and limitations

`bin/docker` implements only the subset required by `scripts/conker.sh`. It is
not Docker Engine, does not supply a daemon, and does not support general image
building or alternate images. In particular, optional enhanced renderer/debug
images are outside this adapter's scope. Unsupported commands or pin changes
must stop for review, not trigger a weaker fallback.

Each command enters fresh unprivileged user, network, PID, IPC, UTS and cgroup
namespaces. The OCI root is read-only, capabilities are dropped, NoNewPrivs is
set, further user namespaces are disabled, and host network access is absent.
The outer `unshare --user --map-current-user --net` avoids bubblewrap trying to
configure loopback with a sandbox-forbidden NETLINK_ROUTE operation. Only
explicitly allowed repository-root descendants may be bound into approved
workspace destinations; normal Conker recipes mount source read-only and build
outputs writable. Never allowlist a broad parent workspace or store secrets
inside an allowlisted checkout.

`/tmp` is a 1 GiB nosuid/nodev tmpfs and the normal workspace tmpfs is 256 MiB.
The process cap is RLIMIT_NPROC, at most 512 and potentially less under a lower
host hard limit. It is per real host UID, so simultaneous same-UID work can
consume it; this is not Docker's per-container cgroup accounting. Warm container
names are persisted recipes, not long-running containers. Temporary contents
are lost between executions. OCI registry anonymous pull tokens exist in
memory only and are not saved.

The source includes `check_isolation.py` for a runtime diagnostic. It checks
zero capabilities, NoNewPrivs, non-root UID, process limit, root/source mount
permissions, tmpfs flags and absence of external network access. It expects the
normal 512 limit; a lower host hard limit needs explicit diagnosis rather than
silently relaxing the test. To run it without introducing a host bind, stream
its source to the existing Conker warm recipe through standard input:

```sh
# Obtain the exact warm container name from normal ./conker output/state.
# The recipe must already be configured for this checkout.
docker exec -i <verified-conker-toolchain-name> python3 - \
  < /outside/repos/conker-toolchain/check_isolation.py
```

The recovery kit was tested with doctor (IDO compile and Mupen debugger smoke),
a fresh digest-verified image extraction, and this namespace diagnostic. A
consumer must rerun doctor and its own ROM-backed gates; old logs are not proof
for a new executor. Repository tests cover the source pins, bootstrap placement
and rejected adapter options without downloading tools or requiring a ROM.

Never package generated `state/`, `oci/`, `rootfs/`, `armips/`, or package caches
as public source changes. Keep the compiler/image redistribution boundary and
all upstream licenses intact. No host credential directory, credential socket,
host network, privileged execution or security bypass belongs in this setup.
