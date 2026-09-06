# Runtime tracing

Use runtime tracing when static ROM, assembly, or display-list evidence cannot
establish which consumer reaches an asset or code path. Static evidence remains
the preferred starting point because a trace proves only the exercised path.

## Debugger environment

The pinned toolchain image includes Mupen64Plus 2.6.0 with the interpreter and
debugger enabled, plus the HLE RSP required for startup to advance past the
dummy-RSP boundary. The wrapper uses dummy graphics, audio, and input plugins,
so this environment is intended for debugger-driven research rather than
gameplay or visual validation.

The runtime container:

- uses the checksum-validated US ROM already recorded by `./conker setup`;
- has networking disabled;
- mounts only the required project and ROM paths; and
- keeps its emulator configuration in ephemeral container storage.

No host Mupen64Plus installation is required. The immutable tool revisions and
container security model are described in [the CI guide](ci.md).

## Launch a trace

Run the debugger from an interactive terminal after completing US ROM setup:

```sh
./conker mupen
```

Additional Mupen64Plus options pass through the wrapper. For example, launch
from a local savestate with:

```sh
./conker mupen --savestate build/trace.st
```

The savestate and any derived trace material belong under ignored `build/`
paths and must not be committed.

## Evidence standard

Record the exact watchpoint, breakpoint, guest address, relevant register or
memory state, and the code or asset identity being tested. Classify the result
as either:

- a positive runtime hit that identifies the exercised consumer; or
- a bounded negative trace that records the path and conditions exercised
  without claiming the consumer is globally unreachable.

A runtime hit can resolve an ambiguous static interpretation, but it does not
by itself prove an original source-file boundary, semantic asset name, or
complete execution coverage. Preserve those distinctions in the associated
evidence document.
