# Conker's Bad Fur Day decompilation

A decompilation project for *Conker's Bad Fur Day*. The North American release
is the active target; Europe/PAL is preserved as a future goal and does not
currently gate progress.

## Project progress

[![US progress](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2FDevOldSchool%2Fconkers-bfd-decomp%2Fmain%2Fprogress%2Fbadge-us.json)](docs/progress.md)
[![EU progress](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2FDevOldSchool%2Fconkers-bfd-decomp%2Fmain%2Fprogress%2Fbadge-eu.json)](docs/progress.md)

US instruction matches and completed source units are tracked separately. The
EU/PAL badge is informational until that regional target becomes active. See
the generated [progress report](docs/progress.md) for the current function,
source-unit, byte, and executable-area breakdown.

The repository contains no ROMs or extracted game assets. Read
[LEGAL.md](LEGAL.md) before contributing.

## Quick start

Docker is the only supported host dependency. It provides the pinned
IDO-compatible toolchain on Linux, Intel macOS, and Apple Silicon.

```sh
git clone https://github.com/DevOldSchool/conkers-bfd-decomp.git
cd conkers-bfd-decomp
./conker doctor
```

Copy your owned US ROM into the ignored `roms/` directory, then validate and
record it for local builds:

```sh
cp /path/to/your-us-rom.z64 roms/baserom.us.z64
./conker setup --us roms/baserom.us.z64
./conker build
```

The normal function workflow starts with:

```sh
./conker next --ready
# Replace the selected GLOBAL_ASM pragma with the emitted C starter.
./conker finish <work-item-id>
```

Before making a contribution, read [CONTRIBUTING.md](CONTRIBUTING.md). The
[decompilation workflow](docs/decompilation-workflow.md) explains candidate
selection, focused diffs, source-unit registration, integration, and batch
verification in detail.

## Project areas

| Area | Start here |
| --- | --- |
| Function matching and source integration | [Contributing](CONTRIBUTING.md) and [decompilation workflow](docs/decompilation-workflow.md) |
| Current progress | [Generated progress report](docs/progress.md) |
| Clean-room baseline and ROM profiles | [Bootstrap guide](docs/bootstrap.md) |
| Asset extraction and format research | [RZIP and asset extraction](docs/rzip-assets.md) |
| Future asset editing and ROM insertion | [Asset editing](docs/asset-editing.md) |
| Remaining asset research | [Asset roadmap](docs/asset-roadmap.md) |
| Nintendo 64 library reconstruction | [Library track](docs/library-track.md) |
| Debug and ECTS research inputs | [Beta evidence](docs/beta-evidence.md) |
| Runtime investigation | [Runtime tracing](docs/runtime-tracing.md) |
| CI and protected ROM verification | [Continuous integration](docs/ci.md) |

The [documentation index](docs/README.md) provides a complete map of the
project guides and explains which files are generated or evidence-only.

## Active target

Contributor commands default to the US profile. A function counts as matched
only after its US focused diff reports `CURRENT (0)`. A source unit counts as
complete only after every member matches and the unit is integrated into the
byte-identical build. EU/PAL configuration and research are retained for future
activation but do not affect the active completion percentage.

Generated assembly, extracted assets, and build products stay ignored. The
canonical inventories are maintained through `./conker`; contributors should
not edit their JSON files manually.
