# Clean-room bootstrap

This guide covers owned-ROM setup and the independently derived raw-assembly
baseline. Start with [contributor setup and scope](../CONTRIBUTING.md#setup);
fresh or reset cloud executors also need [cloud setup and recovery](cloud-matching.md).

## Local ROM setup

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
./conker build --all
```

Only US is currently active. The [build and batch reference](decompilation-workflow.md#builds-and-batch-verification)
explains the separate canonical game-overlay build and checks required after
source changes. A successful baseline build does not establish a C match or an
original source-file boundary.

Continue with [matching a function](../CONTRIBUTING.md#match-a-function) and the
[workflow reference](decompilation-workflow.md). That reference owns starter
generation, focused comparison, registration, integration and interactive watch
mode; [acceptance and integration](../CONTRIBUTING.md#acceptance-and-integration)
defines the required evidence.

Do not copy C sources, names, comments, symbols or generated files from another
decompilation repository. Reviewed raw-assembly boundary maps are the sole
exception: confirm each imported offset against the owned regional ROM, and
never treat those maps as match evidence. External tools must be pinned and used
under their own licenses. See [LEGAL.md](../LEGAL.md).

## Regional targets

Contributor commands default to US; direct profile-based builds use `PROFILE=us`.
EU/PAL checksums, split maps and inventory records remain future metadata. An
EU/PAL ROM, build or diff is not required for active work; maintainers may record
that owned ROM with `setup --eu`. When activated, regional differences belong
in narrowly scoped build macros or data/configuration, rather than a forked
source tree. See [regional and progress rules](decompilation-workflow.md#regional-and-progress-rules)
for the distinction between function matching and source-unit completion.
