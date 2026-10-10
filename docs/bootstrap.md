# Clean-room bootstrap

This guide covers owned-ROM setup and the independently derived raw-assembly
baseline. Start with [contributor setup and scope](../CONTRIBUTING.md#setup);
fresh or reset cloud executors also need [cloud setup and recovery](cloud-matching.md).

## Local ROM setup

Run `./conker host-setup` once with Python 3.12 or newer. Host helpers such as
`project_state.py` need the pinned PyYAML; setup installs it, together with the
host-mode test packages, into ignored `build/host-python`, which `./conker`
selects automatically. Setup never changes global Python. `doctor`, matching
readiness and batch verification reject a missing or stale PyYAML before
Docker/build work.

`./conker test` and `verify-batch` run the Python suite in the pinned toolchain
container, which already has every test package. To run the suite directly on
the host instead (as the Mac and Codex cloud setups do), use
`./conker test --host`, `verify-batch --host-tests`, or set
`CONKER_TEST_RUNNER=host`; host mode also requires the full pinned package set
from `host-setup`. Host mode skips tests that need the container's MIPS binutils
or asm-differ, so CI always also runs the full suite in Docker. Docker mode
never falls back to the host.

The reviewed regional revisions are pinned in `config/roms.json`:

| Release | Status | SHA-1 |
| --- | --- | --- |
| North America | Active target | `4cbadd3c4e0729dec46af64ad018050eada4f47a` |
| Europe/PAL | Future target | `ee7bc6656fd1e1d9ffb3d19add759f28b88df710` |

Copy an owned US ROM into the ignored `roms/` directory and record it through
the supported setup command:

```sh
mkdir -p roms
cp /path/to/your-us-rom.z64 roms/baserom.us.z64
./conker setup --us roms/baserom.us.z64
```

`setup` validates the checksum and stores the local state used by build tools.
It also accepts a ROM held elsewhere. Use `./conker rom-info <path>` to inspect
a ROM before setup. ROMs, generated assembly, extracted assets and build outputs
remain ignored; do not commit or distribute them.

## Established baseline

The profile maps were independently derived from the owned ROMs. The project's
clean-room baseline is a byte-identical raw-assembly rebuild, established before
C functions are promoted. Verify the selected checkout's active full-ROM build:

```sh
./conker build
```

This default uses original ROM asset banks so C contributors avoid asset
reconstruction. Use `./conker build --assets` for asset work and
`./conker build --all --assets` for the ROM-backed CI gate. Both require full
ROM equality; only the latter exercises reconstructed asset inputs. Timings
are printed and saved under `build/timings/`.

Only US is currently active. The [build and batch reference](decompilation-workflow.md#builds-and-batch-verification)
explains the separate canonical game-overlay build and checks required after
source changes. A successful baseline build does not establish a C match or an
original source-file boundary.

Continue with [matching a function](../CONTRIBUTING.md#match-a-function) and the
[workflow reference](decompilation-workflow.md). That reference owns starter
generation, focused comparison, registration, integration and interactive watch
mode; [acceptance and integration](../CONTRIBUTING.md#acceptance-and-integration)
defines the required evidence.

Follow [LEGAL.md](../LEGAL.md) for clean-room requirements and the conditions for
reusing independently authored work from other decompilation projects, including
rights, provenance, compatible licensing and required notices. Confirm imported
boundary-map offsets against the owned regional ROM; maps alone are not match
evidence. External tools must be pinned and used under their own licenses.

## Regional targets

Contributor commands default to US; direct profile-based builds use `PROFILE=us`.
EU/PAL checksums, split maps and inventory records remain future metadata. An
EU/PAL ROM, build or diff is not required for active work; maintainers may record
that owned ROM with `setup --eu`. When activated, regional differences belong
in narrowly scoped build macros or data/configuration, rather than a forked
source tree. See [regional and progress rules](decompilation-workflow.md#regional-and-progress-rules)
for the distinction between function matching and source-unit completion.
