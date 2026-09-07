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

## Record model draw state

`mupen-trace` drives the same pinned debugger through a private pseudo-terminal
and writes versioned JSON Lines records. It is intended for repeatable model
research where copying register values out of the interactive prompt would be
too error-prone. The checked-in starter specification records resolved texture
commands from `func_1510CE60`:

```sh
./conker mupen-trace \
  --spec config/model-trace-texture-parser.json \
  --output build/assets/models/us/runtime-traces/texture-parser.jsonl \
  --max-events 8
```

The cross-bank graphics-task specification hooks the main executable's
`__osSpRawStartDma` at debugger address `0x10023DF0`. It filters the 64-byte
DMA to SP DMEM `0xFC0` for `M_GFXTASK`, follows the task's `data_ptr` and
`data_size`, and decodes the submitted F3DEX2CBFD command buffer:

```sh
./conker mupen-trace \
  --spec config/model-trace-gfx-task.json \
  --output build/assets/models/us/runtime-traces/gfx-tasks.jsonl \
  --max-events 8
```

Run the four model-bank extraction commands first because this specification
also correlates runtime geometry with banks `01`, `03`, `04`, and `09`.
Vertex addresses are relocated at runtime, so correlation normalizes only that
address while retaining the exact vertex-load and triangle command words. A
runtime cluster may be an exact prefix of a larger static cluster when the game
submits only its visible triangles. Results distinguish unique matches,
byte-identical entry aliases, genuinely ambiguous matches, and unmatched
clusters; an alias set is never collapsed to a guessed entry.
Each indexed static cluster also carries its containing material-run identity.
For unique matches, the trace joins the runtime pixel and TLUT addresses back
to the original flat texture IDs, material-run index, and expected matrix slot.
Byte-identical materials shared by several candidates may expose one common
material without choosing an unsupported model identity. Ambiguous materials
remain unresolved. Every linked draw run records its runtime-cluster and
material-correlation indices so the full RDP state is not duplicated.
The walker follows every captured direct or live-segment `G_DL` target,
requires bounded reads, and discovers and inlines calls in execution order
before recording effective material state. Discovery replays `DB0600xx`
segment-base changes made by earlier called lists; a breadth-first scan is not
valid because the same encoded segment address can resolve to different runtime
lists later in the task. Every `DE` record retains both its encoded and resolved
address. Raw submitted and nested buffers remain separately hashed in the
evidence record. It also follows each resolved `DA380003`
model-view matrix pointer and decodes the RSP's 64-byte row-major `4x4` matrix
from its split signed-16.16 representation. It ties the resulting matrix hash,
capture index, and decoded
translation to every affected draw run, retaining the encoded segment, offset,
and aligned `0x40` matrix slot where present.
Segmented matrix references are resolved only from a preceding captured
`DB0600xx` segment base. References without such evidence remain explicit
instead of being read as guessed host addresses.
The decoder also replays every F3DEX2 `D9` geometry-mode update. Each draw run
therefore records the exact mode word and whether `G_LIGHTING` was active rather
than assuming that source vertex RGBA is the final RSP shade value.
For lit draws it also mirrors the dedicated F3DEX2CBFD handler rather than the
standard F3DEX2 macros: `DB` index `0x02` stores `argument / 48` active lights,
`DB` index `0x10` updates the sixteen coordinate-modifier values, `DC` selector
`0x0A` selects a light slot from its 48-byte offset, and `DD` enables the
advanced-lighting path. The recorder follows each resolved light pointer and
captures the full 48-byte CBFD record, including its two RGB triplets, signed
direction, attenuation byte, and extended signed position. Draw runs retain the
exact slot set, decoded values, capture hashes, light count, coordinate
modifiers, and basic/advanced selection.

Correlated draw states can be reduced to reusable, ROM-validated material
variants and embedded into model previews:

```sh
./conker model-assets materials \
  --trace build/assets/models/us/runtime-traces/gfx-tasks.jsonl \
  --force

./conker model-assets preview --bank 04 \
  --runtime-materials build/assets/models/us-runtime-materials/manifest.json \
  --force
```

The material step removes pose matrices, normal streams, and segment bases from
its identity hash, but retains resolved texture addresses, tile/TMEM state,
combine and other modes, primitive/environment RGBA, geometry mode, and decoded
CBFD lighting state. Matrix and normal-stream inputs are attached as separate
per-variant lighting contexts. It keeps
multiple observed variants instead of selecting one arbitrary scene state.
The material manifest summarizes nested-call resolution, including segment-8
call counts and the distinct resolved runtime addresses, so an incomplete walk
cannot be mistaken for complete render-state evidence. On the supplied OpenEmu
state, resolving the ten segment-8 calls changes the effective state of 34 out
of 75 correlated material records and 541 draw observations; those records had
previously inherited stale parent-list OtherMode state.
glTF receives exact sampler filtering and a conservative alpha-mode translation;
explicit RDP coverage/blender behavior, `TEXEL0`/`TEXEL1` LOD, unsupported
combiners remain fully described in extras. For a lit texture-times-shade
variant with exactly one complete observed context, preview export mirrors
GLideN64's CBFD basic or advanced vertex lighting and writes floating-point glTF
vertex colours. Ambiguous contexts remain unbaked. The capture includes each
active model-view matrix and the 32 signed-XY normal slots selected by `DC`
selector `0x0E`; signed Z remains in the source vertex flag. This establishes a
reproducible emulator-equivalent preview, not independent hardware-microcode
verification.

Use `--force` to replace an existing trace or `--append` to add events. A
savestate can be supplied with `--savestate build/trace.st`. When a run is
already narrowed to one exported model, attach its stable identity with
`--bank`, `--entry`, `--segment`, and `--material-run`; otherwise those fields
remain null rather than guessing a static association.

Each draw-state record contains the breakpoint and guest PC, all 32 integer
registers, bounded memory probes with their addresses and hashes, a structured
state object, and a canonical render-state hash. The schema reserves explicit
locations for segment bases, pixel and TLUT addresses, tile/TMEM state, combine
and other modes, primitive/environment colour and alpha, joint matrices,
48-byte CBFD lights, and 32-slot CBFD normal streams.
Fields not observed by a particular breakpoint remain null or empty. This is
important: the texture-parser specification proves the parser's resolved source
address, mode, payload size, and rewrite-table argument; it does not relabel that
source as pixels or a TLUT until the consuming draw state proves which role it
has.

Trace specifications accept only debugger breakpoint data, register names, and
bounded memory expressions of the form `0xADDRESS`, `$register`, or
`$register+offset`. A later probe may safely take its address and bounded length
from bytes already captured by an earlier probe; the graphics-task spec uses
that facility for `OSTask.data_ptr` and `OSTask.data_size`. Output is confined
to ignored `build/` paths. Add a new checked-in specification for each reviewed
runtime hook rather than embedding ad-hoc debugger commands in scripts.

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
