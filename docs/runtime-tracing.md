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

Automated `mupen-trace` runs use a one-shot container rather than the warm
compiler container. This keeps a long emulator capture isolated from concurrent
matching or permutation work in the same checkout.

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

### Software graphics for successive tasks and native frames

Use `mupen-trace --software-renderer` when the capture needs completed graphics
tasks or an emulator-rendered frame. The default dummy video plugin has an
empty `ProcessDList`; it does not raise the DP completion interrupt needed by
the game's graphics scheduler. It can expose an initial task and CPU renderer
calls while never reaching the following graphics submission.

```sh
./conker mupen-trace --software-renderer \
  --spec config/model-trace-character-draws.json \
  --output build/assets/models/software-character-draws.jsonl \
  --savestate build/trace.st --session-timeout 600
```

This opt-in mode builds `toolchain/Dockerfile.mupen-software` on the existing
Mupen image, keyed by that Dockerfile and the base image's immutable ID. It uses
pinned CXD4 RSP LLE (`00906a92641c540a64e4e7505012157315314810`) and Angrylion
RDP Plus (`9c8b9ed3e7d7f00dff8bc872ccdd3fba1a3673fc`). Xvfb supplies the
presentation surface, with Mesa software rendering. The runtime remains an
ephemeral container without networking; the default trace and warm compiler
images remain available. The session records the selected backend, tool
revisions and additional emulator arguments. Conflicting graphics, RSP or CPU
overrides are rejected in this mode.

For native screenshots, append Mupen's `--sshotdir` and `--testshots` options
after `--`. The directory must be a writable path inside the container (for
example `/workspace/build/assets/models/native-frames`). Mupen exits after the
last requested frame, so allow later frames when the debugger still needs more
events. Screenshots validate the exercised emulator state, not every exported
model or exact hardware raster parity.

## Record model draw state

### Ordinary-object selectors and callbacks

```sh
./conker mupen-trace --software-renderer \
  --spec config/model-trace-object-selectors.json \
  --output build/assets/models/object-selectors.jsonl \
  --savestate build/trace.st --session-timeout 90
```

This specification captures constructor templates at `1513264C`, reference-count
writes at `151328B4`, callback dispatch at `15132C60`, and the primary-list
address write at `15132DC4`. The debugger can report the following instruction,
`15132DC8`; each event retains that reported PC. A hit identifies the CPU
submission path, not native appearance or completed rasterization. Object and cache
selectors remain distinct from the model IDs in the 233-entry lookup table.
Full flags and raw callback bytes are retained; byte 255 means signed sentinel
-1. Constructor return addresses identify caller leads without admitting a
material binding.

The run stops at two graphics-submission hooks or 256 recorded events, with
the command's wall-clock bound as a further limit. It captures small object
records rather than decoding whole graphics tasks. Use a state/action that
reaches the target constructor: absence from an idle saved state is only
bounded negative evidence. See the [material frontier](evidence/us_model_material_frontier.md)
for the seven bank-09 selectors still needing such a trigger.

### General draw-state capture

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
  --max-events 8 \
  --session-timeout 300
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

`rdp.vertex_loads` retains the model-view and projection command chains, lights,
normal stream, and coordinate modifiers present at each vertex load. Triangle
records carry `vertex_cache_indices` and `vertex_load_indices` for every corner;
changing a matrix or light after a load does not replace that cached state.
Unsupported vertex modifications invalidate the affected source-load link.
Matrix capture includes projection loads/multiplies and model-view stack
operations. `processing_matrices.combined_rows` uses the row-vector
model-view/projection product before perspective division. Missing initial
matrices, uncaptured addresses, or invalid stack operations remain unresolved.
Projection matrices retain N64 split fixed-point layout even when the character
palette is captured before its float-to-fixed conversion.

The graphics-task specification also enables `capture_vertices`, bounded by
`max_vertex_blocks`. It deduplicates VTX source spans and retains their bytes as
`runtime-vertex-block-*` memory evidence, so lighting replay can use CPU-updated
vertex colours. A sample is exported only after the task header matches the full
captured command buffer and source triangle positions/cache slots match the ROM
geometry. Renderer-return subranges do not establish the initial task lighting
mode. Captured colour evidence remains attached to its source face and event;
missing or contradictory observations prevent an aggregate lighting bake.

Correlation refresh also reconstructs `replayed_vertex_loads` and per-draw
`replayed_vertex_load_indices`/`replayed_vertex_cache_indices` from verified
command, matrix, light, and normal bytes. These derived fields leave the original
draw state and its material hash intact. Older captures that omitted projection
bytes cannot acquire a complete combined transform merely by replaying commands.
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
evidence record. It also follows each resolved `DA380003` model-view matrix
pointer. Graphics-task submissions use the standard 64-byte split signed-16.16
RSP layout. The internal character-renderer return hook instead captures the
same palette before task submission, while it is still Conker's row-major
16-float layout. For the float form, the affine three columns are validated
independently because the unused fourth column can retain unrelated data. The
recorder ties the resulting matrix hash, capture index, and decoded translation
to every affected draw run. Each reference retains the encoded segment, offset,
segment base active at that command, and aligned segment-relative `0x40` slot.
A segment-relative slot is not treated as a palette-global identity: character
display lists can rebind segment 3 to an interior palette address. Character
composition derives its global slot from the renderer's root palette address
and the captured absolute matrix address.
Segmented matrix references are resolved only from a preceding captured
`DB0600xx` segment base. References without such evidence remain explicit
instead of being read as guessed host addresses.
Every graphics-submission specification, including character activity and part
tables, now checks `OSTask.type == 1`, in addition to
the DMA direction, address and length. DMA register values alone also select
audio tasks. Replay excludes a captured task whose verified header is not type
1. Old lightweight character traces omitted the header. After replacing the
Save-Game-13 capture, 400 canonical boundaries remain explicitly untyped and two
have verified graphics headers. `task_submission_index` retains each trace's RSP
boundary numbering so saved pose identities stay stable; it does not prove that
the renderer's returned command range was submitted for graphics. Separate
manifest counters report graphics, non-graphics and untyped boundaries.
Replay also records each effective command's physical address and ancestor
call-site addresses. Material evidence retains this `command_path`, preserving
which instance called a shared display list. This provenance is required before
linking a renderer range to inherited submission-time state. A dummy-renderer
600-second Save-Game-13 capture reached the initial scene task and two renderer
returns, but no subsequent graphics submission. Its bounded negative audit is
under `build/assets/models/reference/submitted-character-lighting/graphics-only/`.
The software-renderer follow-up succeeds: both returned ranges occur
byte-identically and execute exactly once in the next verified graphics task.
The linker also checks geometry-bearing list hashes, triangle counts, task
buffer identity, and matrices at the same physical addresses. Task material
observations are restricted to that command range's ancestor paths, separating
instances that call the same list. Submitted split-16.16 matrices replace the
earlier float matrices only with this proof; both versions remain recorded.
In this state palette slots 13 and 14 collapse after renderer return, hiding
34 ear triangles. Native screenshots show a helmet, whose separate attachment
is not yet included in the body composition. The trace, linked ranges,
screenshots and regeneration script are under
`build/assets/models/reference/software-submitted-lighting/`.

The attachment follow-up uses ordinary selected-part/return hooks at
`0x15031870` and `0x15031914` in `func_150311C4`, plus alternate selected-part
hook `0x15035F60` in `func_15035D6C`. It captures the attachment record, parent
character, generated command range and the following graphics task. Bank-09
entries 29 and 133 match all 85 captured vertex positions; their part pointers,
relocated normal/texture arguments and submitted matrices establish the cigar
and helmet on parent bone 12. Their 78 faces now export captured textures and
per-corner colours, including the helmet's complete zero-DXT RGBA32 loads.
The isolated joined review and reconstruction audit are under
`build/assets/models/reference/software-submitted-lighting/attachments/`.
The generic parser covers 155 attachments. The repeatable `--attachment-trace`
option on `model-assets compose` joins captured parts to a matching ordinary
body submission. It retains the original body data, requires every selected
native part and captured matrix, and records missing or conflicting evidence.
Parent attachment observation does not establish a numeric scene identity.

Capture with `config/model-trace-attachment-draws.json` through the same
software-renderer command above, using the same savestate as the character draw
capture. Then pass the resulting JSONL alongside the activity and task material
manifests:

```sh
./conker model-assets compose \
  --activity-manifest build/assets/models/us-character-activity/manifest.json \
  --runtime-materials build/assets/models/us-runtime-materials-all-states-with-textures/manifest.json \
  --task-runtime-materials build/assets/models/us-runtime-materials-character-draws/manifest.json \
  --attachment-trace build/assets/models/reference/software-submitted-lighting/attachments/save-game-13.jsonl \
  --textures build/assets/textures --force
```

The parent task's material catalog must include the same graphics submission.
The exporter uses captured normal/UV/colour attributes and records their hashes;
changed source XYZ still requires additional deformation evidence. Uncaptured
attachments, animations and complete native raster output remain unverified.

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
  --activity-manifest build/assets/models/us-character-activity/manifest.json \
  --force

./conker model-assets preview --bank 04 \
  --runtime-materials build/assets/models/us-runtime-materials/manifest.json \
  --force

# Reproduce one captured graphics task instead of merging scene variants.
./conker model-assets preview --bank 01 \
  --runtime-materials build/assets/models/us-runtime-materials/manifest.json \
  --runtime-appearance 1:0 \
  --output build/assets/models/us-bank-01-preview-trace-001-event-000 \
  --force
```

For character-heavy states, the smaller
`config/model-trace-character-activity.json` specification snapshots all 25
runtime character records at the same first graphics-task boundary. Record one
JSONL file per savestate, then aggregate them with:

```sh
./conker model-assets activity \
  --trace build/assets/models/us/runtime-traces/character-activity/save-game-13.jsonl \
  --draw-trace build/assets/models/us/runtime-traces/character-draws/save-game-13.jsonl \
  --part-table-trace build/assets/models/us/runtime-traces/character-part-table-headers/save-game-13.jsonl \
  --runtime-materials build/assets/models/us-runtime-materials/manifest.json \
  --force
```

The activity manifest proves only that a bank-01 entry was selected in a live
character record. It does not by itself prove that the character was visible.
`model-assets materials --activity-manifest ...` therefore refines an ambiguous
draw only when the active bank-01 candidate is also the sole candidate whose
static material matrix slot equals the runtime-selected slot. If the runtime
slot is absent, refinement is permitted only when every original candidate is
already in bank 01. Object and level candidates are never rejected using the
character pool alone.

`config/model-trace-character-draws.json` adds entry and return breakpoints on
`func_1502CCFC` and continues through 16 graphics-task submissions. Each
completed call binds the live character slot and bank-01 entry to its aligned
output command range, then decodes that range and its nested display lists.
Two internal hooks record the renderer's selected normal or extra part table,
display-model index, part index, and exact display-list address before the
`G_DL` command is emitted. Across the supplied corpus this records 128 part
selections spanning display-model indices `0`, `1`, `4`, `67`, `90`, `94`,
`115`, `127`, `130`, and `140`. The display-model index and ordering between
sibling parts resolve 122 selections to one exact bank-01 cluster sequence.
For entry `0130`, subtracting each ROM header's primary/secondary list pointer
from the selected runtime address produces one consistent loaded-model base;
that exact relocation identity resolves the remaining six observations.
Across the 26 supplied states, 402 task boundaries contain 71 completed calls for
entries `0000`, `0001`, `0067`, `0090`, `0094`, `0115`, `0127`, `0130`, and
`0140`; all nine already have correlated material evidence. Intersecting each
call's model candidates and requiring a strictly increasing static-cluster
sequence resolves the exact ROM face order for 69 calls. The pointer-table
identity above resolves the two duplicate-looking entry-`0130` calls, so all 71
captured calls now have exact ROM cluster sequences.
This ordered proof is stronger than choosing a whole bank record: entries
`0000` and `0001` each compose their own clusters with a second pass sourced
from entry `0004`.

`config/model-trace-character-part-tables.json` independently snapshots the
188-slot renderer header tables at the first graphics-task boundary. Repeat the
trace once per state and pass the results to `model-assets activity` with
`--part-table-trace`. The 26-state sweep observes headers for all 147 bank-01
records initialized by those states and retains their exact part-count variants
and pointer-table addresses. The other 36 of the 183 non-empty bank records are
reported as unobserved; the header addresses are not treated as part-list
contents or as proof that an unrendered model was visible.

The activity manifest records 50 task-local composition instances and an
aggregate composition for each of the nine observed entries. The corrected
26-state replay captures 1,721 character matrices: 1,415 valid affine float
matrices and 306 invalid or uninitialized snapshots, all confined to six calls
in Save-Game-24. The matrix lifecycle is now statically closed: after
`func_1502CCFC` emits the character lists, `func_1502E474` selects the active
double-buffered palette and passes its exact count to `func_150A9984`. That
routine converts every `0x40`-byte row-major float matrix in place into the
standard split signed-16.16 RSP form and canonicalizes the unused affine column
to `[0, 0, 0, 1]`. Absolute-address comparison with the adjacent submitted
task agrees across the full 28-slot palette apart from expected frame motion
and fixed-point quantization. Generate neutral and task-local posed geometry
previews from only the ordered, resolved clusters with:

```sh
./conker model-assets compose \
  --activity-manifest build/assets/models/us-character-activity/manifest.json \
  --runtime-materials \
    build/assets/models/us-runtime-materials-all-states-with-textures/manifest.json \
  --task-runtime-materials \
    build/assets/models/us-runtime-materials-character-draws/manifest.json \
  --output build/assets/models/us-character-compositions --force
```

That output contains nine neutral glTF/OBJ compositions assembled from 245
exact static clusters: 3,775 source faces and 3,763 nonzero-area preview faces.
It also emits 44 task-local posed glTFs for all nine drawn entries, using the
captured matrix palette and centering only the global translation. Six
Save-Game-24 instances with invalid or conflicting matrices remain explicitly
excluded. Use the neutral-bind compositions for topology review. Posed vertex
positions now follow the proven runtime row-vector matrix and in-place
float-to-RSP conversion contract; they remain preview artifacts rather than
proof of exact N64 normal, combiner, mipmap, or raster output. With only the
aggregate catalog, the output links
110 neutral and 478 posed material runs to 24 proven static or uniquely
captured PNGs. The texture-enabled renderer-return replay now captures 744
referenced RDRAM texture images across 50 of the 71 returns with zero unresolved
addresses. Its material catalog contains 132 records, 681 variants, and all 71
return-event appearances; 639 variants have captured base images deduplicated
to 49 PNGs. Every one of the 1,647 resolved instance clusters has exactly one
trace/event owner. Supplying that catalog through `--task-runtime-materials`
raises the posed output to 1,311 linked runs and 79 copied PNGs; 1,320 runs
carry an exact event-local runtime material and 1,024 select an event-local
captured indexed image. Missing event correlations fall back only to the
independently proven static texture catalog, never to another runtime
appearance. This proves material provenance, but core glTF still does not
reproduce every N64 combiner, mip, or two-texture operation, so a Blender render
is a validation preview rather than final raster parity. Unobserved entries
remain open rather than being inferred.

The material step removes pose matrices, normal streams, and segment bases from
its identity hash, but retains resolved texture addresses, tile/TMEM state,
combine and other modes, primitive/environment RGBA, geometry mode, and decoded
CBFD lighting state. Matrix and normal-stream inputs are attached as separate
per-variant lighting contexts. It keeps
multiple observed variants instead of selecting one arbitrary scene state.
Each source trace and graphics-task event also receives a stable zero-based
`TRACE_INDEX:EVENT_INDEX` appearance identity. `--runtime-appearance` filters
every model material to only observations from that task; material runs not
seen in the selected task remain unassigned instead of borrowing another
scene's state. This is the appropriate preview mode for character-state and
level-state variants. The aggregate mode remains useful as an evidence catalog,
but is not a claim that every variant occurred simultaneously.
When `capture_textures` is enabled, the recorder also resolves each `FD` image
through the segment state active at its `F3` pixel or `F0` TLUT load, derives
the exact loaded byte span, and stores a content-addressed RDRAM snapshot in the
trace evidence. The Save-Game-13 task captures 98 unique images totalling
110,824 bytes with no unresolved texture address. Material extraction composes
23 distinct task-local CI4/CI8 PNGs from those exact pixel and palette spans;
32 material variants receive a captured texture.
Repeating that bounded capture for all 19 positive OpenEmu tasks gives exact
pixel/TLUT snapshots to 1,281 of the aggregate manifest's 1,442 variants. Those
variants cover 348 of 368 material records and deduplicate to 233 task-local
PNGs. Captured images occur in nine bank-01 entries, two bank-03 entries, and
ten bank-04 entries; a model or material absent from those tasks remains
uncaptured rather than inheriting another appearance.
The material manifest summarizes nested-call resolution, including segment-8
call counts and the distinct resolved runtime addresses, so an incomplete walk
cannot be mistaken for complete render-state evidence. On the supplied OpenEmu
state, resolving the ten segment-8 calls changes the effective state of 34 out
of 75 correlated material records and 541 draw observations; those records had
previously inherited stale parent-list OtherMode state.
Across the 26 supplied OpenEmu states, 19 one-task sessions reached the reviewed
hook and seven ended as bounded negatives. The successful sessions contain
43,181 submitted and 92,011 effective commands, 20,597 draw runs, 1,498
matrices, 1,034 lights, and 1,288 normal streams. Aggregation plus the
character-activity refinement produces 368 ROM-correlated material records with
1,442 observed variants across 73 models and 16,233 source faces. All 1,772
captured nested calls resolve; the 742
segment-8 calls select 22 distinct runtime lists. The seven negative states are
not treated as evidence about models they did not reach. Each correlated
material observation now also resolves its own static segment-8 offset through
the draw's captured base and verifies the captured list payload hash. Across
the aggregate corpus, 8,070 assignments in 138 material records reproduce the
draw's effective OtherMode exactly: 125 records in bank 01, two in bank 03, and
11 in bank 04. Thirteen unique payloads are tied to material assignments and 11
of those are proven effective at the draw. Another 38 bank-03 assignments prove
the referenced list but
also prove that a later command replaced its state before the draw; five
bank-03 assignments from Save-Game-4 lack a captured segment base and remain
explicitly unresolved. This distinction prevents a resolved address alone from
being mistaken for the material's final state.
glTF receives exact sampler filtering and a conservative alpha-mode translation;
explicit RDP coverage/blender behavior and `TEXEL0`/`TEXEL1` LOD remain fully
described in extras. The current translator has no generic unsupported combiner
left in the 1,442-variant corpus: 281 variants map directly to glTF base-colour
products, 921 map after runtime-lighting replay, 238 use explicit RDP mip-level
blending, and two multiply two texture tiles without LOD. glTF cannot reproduce
the latter two families with one base-colour texture. For a lit
texture-times-shade variant with exactly one complete observed context, preview
export mirrors GLideN64's CBFD basic or advanced vertex lighting and writes
floating-point glTF vertex colours. Ambiguous contexts remain unbaked. The
capture includes each active model-view matrix and the 32 signed-XY normal slots
selected by `DC` selector `0x0E`; signed Z remains in the source vertex flag.
This establishes a reproducible emulator-equivalent preview, not independent
hardware-microcode verification.

The recorder also retains `SetConvert` (`EC`) state. Offline material extraction
replays each retained command buffer and its resolved nested lists, so older
captures gain task-local conversion coefficients without being rerun. This
recovers conversion state for 1,028 variants: 156 K5 combiner variants use the
captured coefficient exactly as `K5 / 256`; 414 variants precede any task-local
`SetConvert` and therefore retain an explicit inherited-state limitation rather
than a guessed value.

The captured pixel spans include packed mip payloads. Material extraction now
decodes all 238 observed mip variants into 753 mip-chain images, deduplicates
them to 213 PNGs, and records their exact source and TMEM offsets and hashes.
Preview output copies 41 distinct mip PNGs for bank 01 and 172 for bank 04,
exposing them through each glTF material's extras. Six detail-mode variants have
a CI4 `TEXEL0` detail tile at the end of the load plus a CI8 `TEXEL1` mip chain;
both sources are now separated instead of decoding the start of the chain as
the detail tile.
Blender still displays the base level because standard glTF cannot prescribe
the N64's explicit per-draw LOD interpolation.
The two non-LOD two-texture variants share one captured 64x32 CI4 `TEXEL1`
image at source offset `0x400`; it is exported and copied beside the preview as
well, while the exact texture multiplication remains in material extras.

After regenerating all four preview banks, validate the interchange boundary
with Blender itself:

```sh
blender --background --factory-startup \
  --python scripts/validate_model_previews_blender.py -- \
  --model-root build/assets/models \
  --composition-root build/assets/models/us-character-compositions \
  --output build/assets/models/blender-validation.json
```

The validator reads the generated manifests rather than a hard-coded filename
list. It imports every bind model, animated bank-01 model, direct model, and
assembled scene, neutral composition, and posed composition; checks for finite
vertex coordinates; counts meshes and polygons; and records imported Actions.
The texture-enabled aggregate previews retain the same geometry boundary. The
current complete pass validates 1,367 glTF files, 2,869 meshes, 382,895 polygons,
and 2,621 Actions in Blender 5.2.1 LTS.

Render one generated glTF without manually framing it in Blender with:

```sh
blender --background --factory-startup \
  --python scripts/render_model_preview_blender.py -- \
  --input build/assets/models/us-character-compositions/geometry/0000-00-composed.gltf \
  --output build/assets/models/model-preview.png --view three-quarter
```

Use `--force` to replace an existing trace or `--append` to add events. A
savestate can be supplied with `--savestate build/trace.st`. When a run is
already narrowed to one exported model, attach its stable identity with
`--bank`, `--entry`, `--segment`, and `--material-run`; otherwise those fields
remain null rather than guessing a static association.
`--timeout` bounds an individual debugger stop or command;
`--session-timeout` places a wall-clock bound on the complete recorder session,
including repeated non-qualifying breakpoint hits. Use both when processing a
collection of external states so one state cannot stall the whole batch.

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
