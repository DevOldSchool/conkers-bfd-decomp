# Shared actor model display-list emission

The shared `func_1502CCFC` role is `actor_emit_model_display_lists`. It remains
raw; names do not provide an implementation or identify an exclusive character
controller. See [confidence/provenance](model_name_confidence_review.md) and
[representation selection](actor_representation_selection_semantics.md) for the independent
identity and mutable-model contracts.

## Actor and representation selection

The complete 2,128-byte renderer starts by deriving
`800CC2D0 + actorIndex * 0x32C` at `1502CD34..1502CD60`. This is the actor
pool independently corroborated by `1505F188` and the complete callers below.
The model is initially the unsigned current model byte at actor `+4`.
For modes 3, 4 and 5, the call at `1502CD88` instead obtains both a model and
ordinal from `150849CC`; other modes read the applied ordinal at `+0x1C8`.
The helper's already-reviewed contract is override selector minus one when
nonzero, otherwise the last automatic ordinal, or zero for an empty automatic
prefix. It reads the model from the list at `+0x2C4`. These selection sources
must not be collapsed into immutable spawn identity, a universal detail level,
or the most recently drawn representation.

At `1502CDC0` the renderer calls `1503DA9C(actor, selectedModel,
selectedOrdinal, mode != 3)`. That helper may load model resources, prepare
flat textures and establish the actor's per-representation resource pointers
through `15084044`. This is not a pure table lookup or read-only draw helper.
If this preparation returns nonzero, the renderer returns its original
command cursor. It also returns that cursor when the pointer at
`actor + 0x28C + ordinal * 8 + D_800BE9C0 * 4` is zero. Preparation may already
have had side effects on either early-return path.

The complete direct callers are:

- `1502CBC8` in `1502C974`: forwards an actor index and requested mode after
  its own visibility, representation and draw-data handling
- `150360EC` in `15035FE8`: reads the actor index from byte `+8` of a 12-byte
  queued record and passes mode zero, with the wrapper-list option enabled
- `1518514C` in `15184FA4`: derives the same actor-pool address and explicitly
  passes mode three, again with the wrapper-list option enabled

This is a shared actor/model submission path. The first two callers do not
establish that every model is a character. The third establishes an actual
static mode-three caller, not observed runtime activation. An aligned J/JAL
encoding scan covers the main CPU interval, the complete decompressed game
image and the debugger CPU interval. No additional direct sites or aligned
literal addresses of the renderer or loader were found in those CPU images
and the normalized ROM/decompressed game code/data, respectively. Computed
calls, unaligned encodings, other image interpretations and gameplay
reachability remain outside that bounded scan.

## Part selection and commands

The loop at `1502D1D4..1502D4A8` always uses the selected model's unsigned
primary part count in `D_800C4778`. A set bit in actor word `+0x94` suppresses
that part before its color or geometry commands. The variable shift uses the
processor's five-bit shift amount; the function adds no bounds validation.
Actor word `+0x98` independently chooses the part's color state. It is not a
second suppression mask.

Only mode three selects `D_800C48F0[selectedModel]`, at
`1502D3C0..1502D404`. A zero table pointer suppresses that part's display-list
call. When the table exists, a `DE000000` command invokes its indexed pointer.
Other modes select `D_800C4488[selectedModel]` at `1502D418..1502D494`, call
`151EFE88` with `800C3E98`, emit the `DA380003` matrix command using `000C3E98`,
and then emit the indexed `DE000000` display-list call. The matrix helper
constructs an identity matrix through `151EFE00` and `151EFD00`. The primary
path has no corresponding null-table check.

Thus modes four and five use the alternate selection helper but still draw
from the primary table. Neither table is concatenated with the other. The
secondary table's length is not independently consulted by this renderer.
An independent walk of all 187 bank-01 entry slots found 183 present models,
including 31 with nonempty secondary tables. For each of those 31, primary
and secondary table lengths are equal. Every decoded table and pointer was
bounded against its own entry. This describes the authenticated stored data,
not a new runtime guard or a promise about arbitrary modified data. The
existing [draw-table audit](../materials/us_character_draw_tables.md) separately records
primary-only preview behavior; this role makes no new appearance claim.

## Render setup and effects beyond part calls

The complete function retains the following behavior around the part loop:

1. Depending on the final input flag, it emits a call to `80084160` or a pipe
   sync. It then calls `1502F01C` and `1502F9FC` for the actor's existing
   texture/expression-related command setup. Those helpers use the actor's
   current byte at `+4`; it is not silently replaced by the selected model
   used for the part tables. `1502F9FC` also preserves its model-specific
   `150C3160` branch.
2. It emits segment-base commands using the supplied transform address and
   the selected actor resource pointer minus `0x38`. It obtains color inputs
   through `1502CC34`. Mode three or five selects `800832C0`; other modes
   select `80082FC0` or `80083140` according to the original signed comparison
   of the supplied value with `0xFF`.
3. It emits the original geometry-state commands according to mode, actor
   byte `+0x66` and `D_800DCD7C`. Mode three disables the lighting path.
   Otherwise the eligible path calls `1515D914` using actor position,
   per-view resources, `+0x314` storage and writable pointers including
   actor `+0x302` and `+0x1DD`, plus `800D9E28`. That helper can write lighting
   buffers and cached color/count values and append commands. The role does
   not claim the command buffer is the only output.
4. For nonsuppressed parts, transitions between the two `+0x98` states emit
   pipe sync and fog/primitive/environment-color commands. The ordinary
   state uses the computed colors or `800DD2E4` according to the global
   halfword read through `800B0DF0 + 0x3E`; the other state uses its original
   zero/`0xFF` constants. The choice of part table follows those commands.
5. After the loop, `1502FD70(actor)` updates the current model's byte in
   `800D2040` under its original conditions. The renderer writes one to actor
   `+0x2FE` at `1502D4B8`. Mode zero additionally calls `15030F94`, which walks
   linked attachment records and conditionally invokes their draw helper.
   It may emit the closing wrapper list at `80084190`, restores the original
   mode-zero geometry state, and returns the advanced cursor.

Consequently, all-hidden parts, a zero part count, or an absent secondary
pointer do not by themselves suppress setup, lighting eligibility or the
post-loop updates. No new names are assigned to the unresolved mode meanings,
flags, lighting-cache fields or attachment internals.

## Loader audit without an additional rename

The complete 1,096-byte `1503CF20` still supports its existing shared
`model_load_bank01_resources` role. It returns zero for model `0xFF`, for a
signed index at least `0xBB`, or for an already nonzero `D_800D19A0` cache.
It does not check negative indices. Its second argument is spilled but
otherwise unused. At `1503CFC0` it requests bank path `[1, model]` through
`1502B6BC`, with seven header entries to relocate. A null result returns one.
The general loader uses the indexed ROM table and its allocation/decompression
helper; `1502B4A8` rebases present offsets and masks the header size flags.

For a loaded base `P`, it stores `P + 0x38` in `D_800D19A0[model]`. It
installs header pointers `+0x00`, `+0x08`, `+0x10`, `+0x18`, `+0x20` and
`+0x28` into `D_800C4020`, `D_800C4488`, `D_800C4BE0`, `D_800C5338`,
`D_800C5048` and `D_800C48F0`, respectively. It stores counts derived from
header sizes: `+4 >> 2` in `D_800C4310`, `+0xC >> 2` in `D_800C4778`,
`+0x14 >> 4` in `D_800C4ED0`, and `+0x1C / 12` in `D_800C5628`. Its
`D_800C57A0` count is the distance in 16-byte records from `P + 0x38` to the
`+0x00` pointer, or to the primary table if that pointer is zero.

Both display-list pointer tables are relocated through `1503D438`; each
resulting command stream is visited by `1503D368`. The secondary relocation
loop uses the loaded header's `+0x2C >> 2` count. When the fourth input is
nonzero, `1503DC3C` loads flat texture descriptors; on its success the primary
lists pass through `1510CE60`. Subsequent success paths call `1503D984`
(command-derived count), `1503D804` (the original model-`0x24` special
allocation), optionally `150028BC` when the supplied record's `+0x18` bit
`0x4000` or the fifth input's `0x01` bit requests it, then the existing bank-11
defaults and bank-0F route loaders. These helpers retain their existing numeric
symbols and failure semantics; no additional role is proposed for them.

Accumulated failure runs the original cleanup: it may free `D_800C6360`,
call `1503DD1C`, free and clear `D_800C5C08` and `D_800C6070`, then free the
model allocation at cached vertex base minus `0x38` and clear `D_800D19A0`.
It does not visibly clear every installed table/count in this path; this is
not described as complete rollback. Its two direct callers are `1502DC0C`
in `1502DB84` and `1503DAF4` in `1503DA9C`, both actor resource consumers.
Nothing justifies replacing the existing generic loader role with a
character-specific name, nor is an additional loader-comment edit needed.

A bounded original-instruction harness exercised 1,392 synthetic renderer
cases and every one of its 532 instruction addresses. It explicitly stubs
resource preparation, texture setup, lighting, matrix initialization and
attachment drawing, while executing the original selection helper and the
bounded color/model-use helper paths. It checks emitted primary/secondary
part pointers, hidden-part filtering, wrapper commands, preparation/null
resource exits, matrix-command counts, mode-zero attachment-call eligibility
and the `+0x2FE` store. The scenarios vary modes `0..5`, both masks, table
absence, frame slot, geometry gates, lighting inputs and color inputs.
Instruction coverage is not a claim of exhaustive state or path coverage.

A separate 768-case harness executes all 70 assignment instruction addresses
and the original seven-group representative helper. Controlled route counts
and resolver returns verify the exact `[2, representative]` arguments,
zero-count cache preservation, and caching a zero return on a nonzero-count
path. Testing every input byte, including `0xFF`, is synthetic and does not
make the real caller's following table accesses safe. The bank resolver and
assignment-default callback are explicitly stubbed.

Those harnesses are bounded synthetic checks, not gameplay traces, exhaustive
state/path coverage, full-engine execution or C matching.
