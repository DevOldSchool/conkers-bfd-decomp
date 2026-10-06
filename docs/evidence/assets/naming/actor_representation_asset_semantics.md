# Actor representation resources and asset relocation

These inferred role names retain linked numeric symbols, types and ABI. See
[representation selection](actor_representation_selection_semantics.md) for the
exact override-or-base getter, initializer fallback, list counts and call sites.
[Shared provenance](model_name_confidence_review.md) records full original spans.

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
The [defaults evidence](../materials/us_rom_character_defaults.md) proves the 16-byte descriptor
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
[animation event audit](../models/us_attachment_animation_events.md). These are stored
contracts, not proof that any animation or event runs in gameplay.

## Additional shared loader comments

`func_1503CF20` is labeled `model_load_bank01_resources` only in a comment.
It loads indexed bank `0x01` at `1503CFC0` and installs the vertex-boundary,
primary/secondary draw, and texture-descriptor tables, retaining its full cache,
optional texture loading, companion-resource and failure-cleanup paths. The
[draw-table evidence](../materials/us_character_draw_tables.md) independently identifies the
model header pairs and their renderer consumers. No individual character or
controller is attached to this generic loader.

`func_1503DC3C` is labeled `model_load_descriptor_flat_textures` only in a
comment. It takes the model's descriptor count from `D_800C5628`, walks the
12-byte records in `D_800C5338`, passes each flat ID at `+4` to `1510D0EC`
at `1503DCA8`, and stores the result at descriptor `+0`. Its `0x80000000`
failure test and `0x10` result flag stay unchanged. The defaults audit confirms
the texture descriptor contract; neither dimensions nor material appearance
are inferred by this name.

The spawn initializer is chain evidence, not an additional role rename.
