# Shared actor model display-list emission

`func_1502CCFC` has the inferred descriptive role
`actor_emit_model_display_lists`. This is a comment on the existing raw
placeholder, not a recovered developer identifier or a C implementation.
`func_1503CF20` already has the accepted role `model_load_bank01_resources`;
its comment and source file are unchanged. This proposal also corrects the
existing `actor_assign_model` description of actor `+0x58`. It adds one raw
function role and gives no new-role credit to the loader or assignment helper.

No identifier, declaration, signature, ABI, type, field, padding, numeric
symbol, executable expression, source order, candidate guard or score changes.
No character-exclusive function or model identity is inferred.

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
existing [draw-table audit](us_character_draw_tables.md) separately records
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

## Exact assignment-description correction

The existing `actor_assign_model` comment and its earlier
[selection document](actor_representation_selection_semantics.md) called
actor `+0x58` an optional route resource. The independently reviewed
[animation-model representative audit](actor_animation_model_group_semantics.md)
and freshly checked original bytes distinguish two resource domains:

- `150837D4` writes the representative returned by `15084D00` to actor `+6`
- It reads unsigned `D_800C5A90[representative]` at `150838B8`. A nonzero
  value gates `1502B020(0, 2, 2, representative)` at `150838CC`
- That resolver walks bank path `[2, representative]` and returns a ROM/archive
  address. Its returned value, including zero, is cached at actor `+0x58`
  by `150838D4`. A zero gating count skips the resolver and leaves the
  previous `+0x58` value unchanged
- The gating count is produced by the separate bank-0F route system. The
  animation consumer `1505E0C4` uses the cached bank-02 archive, or resolves
  bank 02 using actor `+6`, to fetch descriptor/frame resources. The current
  model at `+4` remains the bank-0F route-selection domain

The correction says exactly that `+0x58` caches a resolved bank-02 ROM/archive
address under a separate nonzero bank-0F route-count gate. It neither calls
this a route payload nor claims the resolver loads the archive contents.
It leaves the `CURRENT (568)` body, its widths, byte mask, sentinel behavior
and inconsistent existing source views untouched. No model-group identity,
new field layout or safe out-of-domain access is inferred.

## Independent checks and limits

The normalized owned US ROM is 67,108,864 bytes, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`.
Fresh in-memory raw-deflate decoding produced the 2,072,880-byte game code
and 189,088-byte loaded data. The complete original reference binary agrees.
Every reference instruction-word comment agrees with the ROM where present;
none of the reviewed spans crosses the reference's unrelated
`150A9C40..150AA470` comment gap.

Registration and relevant source were read at checkpoint
`de5c0b4499c6146146c4417c2186875e73c491a4`. The complete 1,096-byte loader and 2,128-byte renderer, including
their return delay slots, agree with both raw-assembly copies and contiguous
independent reference words. The following complete support spans were also
checked. A reference/raw-body extent is explicitly marked when no registered
size exists; no source-unit ownership is inferred from such a boundary.

| Symbol | Bytes | Extent | Full-span SHA-1 |
| --- | ---: | --- | --- |
| `func_1503CF20` | 1096 | registered | `2335fa3855313510f1f46512cfa704ab301814d1` |
| `func_1502CCFC` | 2128 | registered | `2176c655198fed8b1867b28f059cb4765bced897` |
| `func_1502B6BC` | 308 | registered | `91ed9cccb2168331f871d0b5b3597f9cfc8f558f` |
| `func_1503D438` | 36 | registered | `add9aec5cb5ff6df58ba80704156c1463b4a2071` |
| `func_1503D368` | 208 | registered | `abef1711e0dda14ca8b45eb3689aa144f101bb5f` |
| `func_1503DC3C` | 224 | registered | `4d0a13f114d5f3ecad9c56068bdde74a052935af` |
| `func_1503D984` | 184 | registered | `56cdd8e4b82b2a4222f4e661e22b08cdca30d293` |
| `func_1503D804` | 384 | registered | `486bab26201a574421a430fed7e156346e60b68e` |
| `func_150028BC` | 1668 | reference/raw body | `cffdfd5fb609badb5d60111edaf1c040c4e727cc` |
| `func_1503D774` | 144 | registered | `546821f215679e4d341cd39d98c9a9d6256110d2` |
| `func_1503D660` | 276 | registered | `698addad07c12e755805e484a22441109dd90252` |
| `func_1503DD1C` | 180 | registered | `8488f03d16dd306923361422c315a5db5ec5c746` |
| `func_1510CE60` | 652 | registered | `9a12376e197e0ae05d6d351d5d538865aa7dcc68` |
| `func_1503DA9C` | 416 | registered | `c45efcf48e1487e1c0401c7592c959cd2ddb6898` |
| `func_150849CC` | 76 | registered | `f406a1972f5f0f73bdcce7b9fb373af650daf567` |
| `func_1502F01C` | 584 | registered | `a9ae1253feb21fae8ecc3c314d949162c3e6afa5` |
| `func_1502F9FC` | 492 | registered | `cf59732557feef6b94d12cf90dc99c728f582097` |
| `func_1502CC34` | 200 | registered | `c4fa4d82300818f349512dcc7d9a8cbba96d026a` |
| `func_1515D914` | 2404 | registered | `a0ca1f285c354276fa25543fe54a68ef023f1813` |
| `func_151EFE88` | 48 | reference/raw body | `fef97dc8413dff2d4e193eb0791fb9cc5ed1a906` |
| `func_1502FD70` | 160 | registered | `d88f7df50a833ec02f2c1086371360004e018238` |
| `func_15030F94` | 220 | registered | `244e8f3ea6dd995d239f1b7a561547fa9eb94543` |
| `func_150837D4` | 280 | registered | `7bd9c8414be99e3bc26944fe08eb04064933a30d` |
| `func_15084D00` | 112 | registered | `ff9dc54618c437070a653923b6cedc81f1484759` |
| `func_1502B020` | 240 | registered | `cf808816ca9e3df778eb77490c317e7eb4b57c02` |
| `func_1502AC88` | 636 | registered | `24f02469c9605e212ed65a4c75b216d50ef8577e` |
| `func_1505E0C4` | 1420 | registered | `3e17bb649f54edb53a448676e71fbea0adce0e10` |
| `func_1502AF04` | 284 | registered | `b8f786b34a0b0f6db12c039c68a860a08bd52d1b` |
| `func_1502B110` | 276 | registered | `34a60e9d42e7e0e2a914bc3a2f37c13d0aba4f8a` |
| `func_1505E650` | 380 | registered | `7ff7faebb700286719b32f4b7390b9c9f772236b` |
| `func_1505F188` | 272 | registered | `c4b6d2297e2dc2c7f3c7c5724781e9042b9d3204` |
| `func_15084044` | 776 | registered | `f738e7d7f7530302ba4dade50252079f56071472` |
| `func_1502B4A8` | 288 | registered | `d1a82190ae64677a9404302b5a61653a5770a7dc` |
| `func_151EFE00` | 136 | reference/raw body | `7c13fb05d050330f14f1bfea0340c49362420b40` |
| `func_151EFD00` | 256 | reference/raw body | `8c96268b9cafd0f7e12c9df375e2feadda57a659` |
| `func_1502DB84` | 948 | registered | `a2c545e39bfb534f09979e2d431919fedbe62f20` |
| `func_1502C974` | 704 | registered | `166b05f7f97b828a9ebad3c9a7e51e8a6b748eea` |
| `func_15035FE8` | 352 | registered | `9cc4055fa7f2aaa872df8f2b0af7f5865cf0e11f` |
| `func_15184FA4` | 1200 | registered | `87e9098d44db54c3a41260244ceea5997557bd69` |

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

These are static and bounded synthetic evidence, not gameplay traces, a full
engine execution, a matching attempt or a new C-match result. Exact inverse
comment removal/replacement reconstructs both whole source files byte for
byte. Every disabled-candidate guard, score, body, end marker and adjacent raw
pragma is unchanged, as are source-definition discovery and raw-placeholder
inventories. The assignment-document replacement is one precise passage;
other existing documentation is unchanged. Preparation performs no tracked
source edit, compiler/build invocation, extraction command, queue operation,
finish, commit, push or publication. Independent review and binary/layout/progress gates are still required before acceptance.


## Accepted integration

Independent review approved the exact comment/document patch and repeated both
bounded instruction harnesses. Eight already-matched neighbors in the two source
units remain full-span `CURRENT (0)` with reviewed layout preserved. Their clean
verification batch, full US ROM, integrated game/data/rodata, progress and
whitespace gates passed. Host and pinned ROM-aware suites each passed 1,783 tests
(37 host skips; one optional pinned validator skip). Every allocated section and
all ELF symbol records are identical in the renderer unit (179 symbols) and
assignment unit (145 symbols); only nonallocated `.mdebug` differs. The loader
role/source remains unchanged. This adds one raw-function role and one existing
role-description correction, with zero new C matches, bytes or source units.
