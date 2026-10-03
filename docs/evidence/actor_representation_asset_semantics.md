# Actor representation and asset relocation names

These are descriptive roles inferred from the checksum-validated owned US ROM,
not recovered original symbols. The linked names, argument and local types,
argument widths, arithmetic, constants, declaration order and source positions
stay intact. The initial slice renamed only function-local identifiers in four
existing matched definitions and added role comments for three raw functions.
The later [selection refinement](actor_representation_selection_semantics.md)
tightens the getter role and distinguishes override control from applied state.
No shared structure, header, alias, runtime observation, model identity or C-match
claim is introduced. Excluded candidates are preserved byte-for-byte.

## Override-or-base representation lookup

`func_150849A0` reads an unsigned selector at actor `+0x1C9`. At
`150849A4` selector zero branches to the first byte through the pointer at
`+0x2C4`; nonzero selectors return byte `selector - 1` through the same pointer
at `150849B0..150849B8`. The names `actor` and
`representationOverrideSelector` describe those local roles. The comment role
is `actor_get_override_or_base_representation_model`. It never reads the applied
ordinal at `+0x1C8`: selector zero returns the first list entry even when automatic
selection has applied another entry. The model byte at actor `+0x04` is mutable,
written by `150837D4`. Neither a `0xFF` sentinel check nor a bounds check occurs
in this getter; no exclusivity to any one character is claimed.

The full initialization helper `1505F188` first clears the 0x32C-byte actor and
sets `+0x2C4` to actor `+0x04` (`1505F1F4/1505F20C`), with counts one at
`+0x2C8/+0x2C9`. The full defaults consumer `150839B8` replaces that pointer
with `D_80086CAC[defaults[5]]` when defaults byte four is nonzero, copies that
byte into `+0x2C8`, and adds defaults byte `0x38` for `+0x2C9`. This proves the
single-model fallback and alternate representation-list relationship. The
[selection refinement](actor_representation_selection_semantics.md) identifies
`+0x2C8` as the automatic prefix count and `+0x2C9` as the total count; suffix
entries require explicit selection rather than ordinary distance selection.
Neither count implies distinct models or a gameplay identity for each entry.

The seven direct calls found in the raw CPU images are:

- `1502C7C4`, in `1502C6E8`
- `1507E6EC`, in `1507E6B8`
- `1507E914`, in `1507E908`
- `1507E980`, in `1507E968`
- `1507EA00`, in `1507E9F8`
- `15083210`, in `15082A44`
- `1517AD68`, in `1517AD00`

The [expression audit](character_expression_semantics.md) and
[morph audit](us_character_morph_targets.md) establish the override-or-base
resource consumers. In particular, the existing argumentless call in `1507E6B8` is not
changed or explained away by a local parameter name.

## Representation resource loading

`func_15084488` receives the creation path's spawn-record pointer at its sole
raw direct call, `15082C04` in `15082A44`. That caller preserves its original
first argument in stack slot `+0x68`, reads model byte `+4` at `15082A8C`, stores
the pointer at actor `+0x144`, then passes it to this function. The descriptive
role is `actor_load_representation_resources`; the pointer is `spawnRecord`.

The function itself reads that byte at `150844AC`, skips model `0xFF`, calls
`1503D774` and fetches `D_800D1C90[model]` at `150844D0`. It starts with the
spawn record's model byte as a one-element list when defaults byte four is zero.
Otherwise it selects `D_80086CAC[defaults[5]]` at `150844FC` and uses defaults
byte four as its initial count. Defaults byte `0x38` is then added in either
case. The loop at `15084518..15084538` loads defaults and bank-0x0F routes for
each listed model, through `1503D774` and `1503D660` respectively.

Local names are `modelIndex`, `defaults`, `modelIndices`, `modelCount`,
`modelEntry` and `modelOffset`. The model count is the original combined count;
no extra validation or fallback is inserted. `arg1` is only spilled and unused
in this function. `arg2` is copied to a saved register and forwarded unchanged
as the second argument to both loading functions. Both names stay unresolved;
no allocation, mode or lifetime role is inferred from forwarding.

`1503D774` passes indexed path length two with bank `0x11` and the model index
to `1502B6BC` at `1503D7C8`, then stores the first relocated segment pointer
in `D_800D1C90[model]`. Its comment-only role is `model_load_bank11_defaults`.
The [defaults evidence](us_rom_character_defaults.md) proves the 16-byte descriptor
header, 64-byte default segment and optional expression segment independently.

## Shared offset and route relocation

The comment role for `func_1503D438` is `asset_relocate_untagged_offset`.
`offsetSlot`, `baseAddress` and `offset` describe its complete 36-byte span:
load the slot, leave zero unchanged, test exactly `0x0F000000`, and add the
supplied base only when that mask is clear (`1503D438..1503D450`). The name
"untagged" means this exact predicate. It does not assert a general pointer
validator, sign test, idempotence or already-relocated-address detection.

This helper is shared. The full loader `1503CF20` calls it at `1503D0F0` and
`1503D154` for primary and secondary display-list pointer tables. The full
command walker `1503D368` calls it at `1503D3D0/1503D3F0` for selected eight-byte
display-list commands before its `0xDF` terminator. The fifth direct call is
`1503D4C4` in `1503D484`. Thus an animation-only or character-only helper name
would be inaccurate.

The comment role for `func_1503D484` is
`animation_routes_relocate_event_offsets`. Its sole raw direct call is
`1503D74C` in `1503D660`, which loads bank `0x0F` through a shared-model
representative and passes payload `+0x10` as the route-record base. The second
argument remains the caller's original model index, for `D_800C5A90`.

`routeRecord` advances in eight-byte increments, stopping before the first
record whose leading unsigned halfword is `0x3E7` (999). `routeBase` retains the
initial pointer. Nonzero words at route `+4` pass through the shared relocation
helper with that initial base. `1503D4E0..1503D4F4` writes `(end - base) >> 3`
as the model's signed halfword count in `D_800C5A90[modelIndex]`. The sentinel is
not counted. No extent check or tagged-pointer behavior is added.

The route/event interpretation is supported by the complete selector
`1505E650`, which indexes `D_800D1588` and uses an eight-byte route stride,
and by `1505E0C4`, which copies route `+4` into actor event pointer `+0x1C4`
at `1505E1D8/1505E1E8`. See the independent
[animation event audit](us_attachment_animation_events.md). These are stored
contracts, not proof that any animation or event runs in gameplay.

## Additional shared loader comments

`func_1503CF20` is labeled `model_load_bank01_resources` only in a comment.
It loads indexed bank `0x01` at `1503CFC0` and installs the vertex-boundary,
primary/secondary draw, and texture-descriptor tables, retaining its full cache,
optional texture loading, companion-resource and failure-cleanup paths. The
[draw-table evidence](us_character_draw_tables.md) independently identifies the
model header pairs and their renderer consumers. No individual character or
controller is attached to this generic loader.

`func_1503DC3C` is labeled `model_load_descriptor_flat_textures` only in a
comment. It takes the model's descriptor count from `D_800C5628`, walks the
12-byte records in `D_800C5338`, passes each flat ID at `+4` to `1510D0EC`
at `1503DCA8`, and stores the result at descriptor `+0`. Its `0x80000000`
failure test and `0x10` result flag stay unchanged. The defaults audit confirms
the texture descriptor contract; neither dimensions nor material appearance
are inferred by this name.

The initial patch omitted raw spawn-initializer and model-assignment comments.
The [selection refinement](actor_representation_selection_semantics.md) later
adds a bounded model-assignment role comment; the spawn initializer remains
chain evidence only.

## Fresh independent full-span evidence

All bytes below were read from the owned ROM, normalized SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, rather than generated candidate
assembly. Extents come from `progress/functions.json` at naming checkpoint
`b01bc28`, unchanged in this slice. Each listed span includes every registered byte, including delay
slots and terminal padding. Existing raw assembly files were separately checked
for contiguous addresses and exact full-span byte equality against the ROM.

| Symbol suffix | Registered bytes | SHA-1 |
| --- | ---: | --- |
| `150849A0` | 44 | `62d89a7ec36b39096dfd2c98896619b96b71866a` |
| `15084488` | 208 | `73e99fd512f1d521f6620a98947843257844411d` |
| `1503D438` | 36 | `add9aec5cb5ff6df58ba80704156c1463b4a2071` |
| `1503D484` | 140 | `40f757370bbf19e10e675591d24421010455453d` |
| `1503CF20` | 1096 | `2335fa3855313510f1f46512cfa704ab301814d1` |
| `1503D774` | 144 | `546821f215679e4d341cd39d98c9a9d6256110d2` |
| `1503DC3C` | 224 | `4d0a13f114d5f3ecad9c56068bdde74a052935af` |
| `15082A44` | 2152 | `df94e52b3063e063c091fac537096563d3e47620` |
| `150837D4` | 280 | `7bd9c8414be99e3bc26944fe08eb04064933a30d` |
| `1503D368` | 208 | `abef1711e0dda14ca8b45eb3689aa144f101bb5f` |
| `1503D660` | 276 | `698addad07c12e755805e484a22441109dd90252` |
| `150839B8` | 272 | `83514e60fb88c39b8e225ba6b68a54a5094c2dff` |
| `1505F188` | 272 | `c4b6d2297e2dc2c7f3c7c5724781e9042b9d3204` |
| `1505E0C4` | 1420 | `3e17bb649f54edb53a448676e71fbea0adce0e10` |
| `1505E650` | 380 | `7ff7faebb700286719b32f4b7390b9c9f772236b` |
| `1507E908` | 96 | `c602e20a2b335d94feb349539cbdb76d69957d50` |
| `1517AD00` | 2048 | `a16226b408961566109c7c0088fd15ae34c76f1c` |
| `1502CCFC` | 2128 | `2176c655198fed8b1867b28f059cb4765bced897` |

Direct-call observations scan aligned J/JAL instructions in both the raw main
CPU interval and decompressed game CPU image. They exclude indirect calls and
other overlays and do not establish runtime reachability. All reported direct
sites have a unique current inventory owner. No matching call to these symbols
was found in the scanned main CPU interval.

## Source equivalence and required acceptance

A scope-local inverse rename followed by removal of only the exact inserted
comments reconstructs both complete input files byte-for-byte. This includes
all excluded C candidates, raw-assembly pragmas and unchanged declarations,
not just the four edited function bodies. Every replacement name is absent
from its original function scope, and the mappings are one-to-one. No runtime
expression, type, constant, field, ABI, store order or source-unit boundary
changes. The existing allocation-related fixes are left intact.

This preparation performed no build, focused comparison, inventory update,
commit or push. Identifier equivalence is not a fresh matching claim. Before
acceptance the exact edited matched IDs are:

```sh
./conker finish func_15084488
./conker finish func_150849A0
./conker finish func_1503D438
./conker finish func_1503D484
./conker verify-batch func_15084488 func_150849A0 func_1503D438 func_1503D484
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

All four must preserve full-span `CURRENT (0)` and current source-unit layouts,
followed by clean batch/game/data/rodata, progress and whitespace gates. The
three role-only raw functions remain raw. No additional caller validation ID
is introduced because this patch changes no linked names, types, fields,
prototypes or shared declarations.

## Accepted result

The four renamed matched functions retain full-span `CURRENT (0)` and reviewed
source-unit layout. The clean batch reaches `BATCH_COMPLETE`; complete ROM,
integrated game code, mapped rodata, progress and whitespace gates pass. The
combined representation/object-registry checkpoint passes all 1,721 tests on
the host (37 skips) and in the ROM-enabled pinned fixture (one optional skip).
Independent review confirms all 18 raw-ROM spans and whole-source inverse
renaming, including preservation of all 23 excluded candidates.

This accepts four descriptive roles on matched C and three comment-only roles
on unchanged raw loaders. It adds no C matches, matched bytes or field layouts.
