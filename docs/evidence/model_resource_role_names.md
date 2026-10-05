# Shared effect, resource and timer roles

These roles are inferred from complete original US spans; they preserve numeric
symbols, signed widths and source-local layouts. The [confidence contract](model_name_confidence_review.md)
applies to all model wording. Shared code and conditional requests do not prove
exclusive ownership, live creation or runtime appearance.

## Bounded naming changes

| Existing symbol | Naming-only change |
| --- | --- |
| `func_15141C0C` | C alias `actor_get_effect_selector_callback_index`; existing `arg0` becomes `actor` |
| `func_15141DA4` | C alias `actor_request_timed_effect_handler`; existing `arg0/arg1/arg2/temp_v0` become `actorAddress/selectorCallbackIndex/effectHandlerIndex/handlerRecord` |
| `func_15134070` | Role comment `actor_get_fragment_effect_profile_index` before the existing disabled guard; deferred C is unchanged |
| `func_151B01B8` | Local `kind` becomes `effectProfileIndex`; comment distinguishes optional profile-source actor `arg1` from position/transform actor `arg0` |
| `func_15194B1C` | Local `type` becomes `effectProfileIndex`; comment only describes its guarded first call |

The last two functions retain numeric whole-function identities. No inferred
particle purpose is assigned. All argument types, declaration order, casts,
control flow, checks, layouts, struct fields, shared headers, enums, source-unit
boundaries and function states remain unchanged. The descriptive C aliases
retain numeric linked symbols. `func_151B4CD0`
retains its numeric role.

## Evidence and index domains

- `15141C0C` returns `0..11`. At `15141AAC`, its sole static direct caller
  `15141A7C` obtains the value, then indexes the 12 pointers in `D_8008A084`
  at `15141ABC..15141AC4`. Default slot 11 is null. The selected callback's
  separate result indexes 20 eight-byte handler records in `D_8008A0B4`
  at `15141B14..15141B1C`, after rejecting `-1`.
- The complete `15141DA4` body separately bounds callback index `<12` and
  handler index `<20`, including nonnegative checks, the global gate,
  null slots and the existing redundant `-1` test. Only a positive record
  second word leads to `15141E38`. That helper creates or refreshes an
  actor-attached controller; `15149130` initializes its `+0x0E` counter and
  `15149264` decrements it by `D_800BE9E4`. “Timed” means this engine counter;
  no seconds, frame duration or other physical units are established.
- `15134070` returns `0..19` or unsupported `99`. Its profile is shared by
  20 sixteen-byte descriptors at `D_800A3FD8`, 20 selector-array pointers at
  `D_80089A20`, and 20 element counts at `D_800A3F14`. The descriptor and
  fragment selectors resolve through the separate `D_800A3880` lookup to
  bank-09 models. The profile is neither a bank ID nor a model ID. The existing
  [model-constructor evidence](us_model_constructor_tables.md) covers that
  downstream loader contract.
- All ten static direct callers of `15134070` reject `99` before indexed
  profile use. They are `150D5A6C`, `15136C3C`, `1513783C`, `15138BC0`,
  `15138C80`, `151945CC`, `15194B1C`, `151B01B8`, `151B09BC`, `151B4CD0`.
  The direct-edge scan covers the full decoded game code and 34,460
  independently ROM-checked main-reference words. It finds no other direct
  edge and no literal selector address in aligned game data; computed indirect
  calls remain outside this completeness claim.
- In complete matched `151B01B8`, the selected profile only gates descriptor
  byte `+0x0E` and the packet variant. The separate actor inputs are retained.
  In complete matched `15194B1C`, the profile is passed to `15138120` with mode
  zero only when supported; `15136C3C` and `15194AB4` are called afterward
  regardless of that sentinel test. No broader whole-function role is claimed.

## Qualified character consequences

- Conker models 0–4 and 150 select callback slot 0, but profiles 0 and 7
  respectively. Shared callback membership does not imply an identical profile
- Fangy 83 and Red Dinosaur 165 share callback slot 6 with model 54, but
  **both return 99 from the shared profile selector**. Only the two audited
  caller-local overrides in `151B01B8` and `151B09BC` select profile 4 for
  them; those callers also select 4 for an absent profile-source actor
- Tediz 90/95/116/117/122 select profile 2, while Tediz medic 141 is unsupported
  (`99`). This is not an all-Tediz classification
- Gregg 112/178 select profile 17 and Gregg 180 selects 16. Fire Imp 58/61
  use null callback slot 11 and unsupported profile 99

These shared helpers are not character-exclusive controllers. Neither the
roles nor the descriptor variant establish blood color, footsteps, death
purpose, anatomy, scene activation or native visual appearance.

## Roles and naming limits

| Function | Descriptive role |
| --- | --- |
| `151380B4` | `actor_transform_effect_profile_offset` |
| `15149130` | `timer_callback_object_create` |
| `151491F4` | `timer_callback_object_create_without_draw_callback` |
| `15149264` | `timer_callback_object_update` |
| `151336A8` | `model_resource_load_by_lookup_selector` |

The first four use source-local aliases for their matched definitions,
preserving numeric linked symbols. Their scoped parameter/local names are:

- `151380B4`: `arg0/arg1/arg2` become `actor/effectProfileIndex/outPosition`;
  `temp_v0` becomes `actorMatrices`
- `15149130`: `arg0..arg6` become `initialTimer`, `expiryCallbackIndex`,
  `tickCallbackIndex`, `drawCallbackIndex`, `flags`, `callbackSetIndex`,
  `extraBytes`; `temp_v0/var_v0` become `object/objectKind`
- `151491F4`: `arg0..arg5` become `initialTimer`, `expiryCallbackIndex`,
  `tickCallbackIndex`, `flags`, `callbackSetIndex`, `extraBytes`
- `15149264`: `arg0/var_v0/temp_v0/temp_v1` become
  `object/timerValue/tickCallbackIndex/expiryCallbackIndex`

Constructor `arg7/arg8` and wrapper `arg6/arg7` remain unresolved forwarding
parameters. All existing types, signed widths, fields, volatile-wrapper members,
padding and declaration placement remain unchanged. In particular the wrapper
retains its `void` signature despite inconsistent consumer declarations elsewhere.
Raw/deferred `151336A8` receives only a role comment before its existing disabled
guard; its full candidate, recorded score 473 and adjacent pragma are unchanged.

## Profile-offset evidence

The complete `151380B4` span reads actor +0x1D4, rejects a null pointer and rejects
exactly low nibble 0xF at actor +0x74. Those paths return zero without writing the
output. Otherwise it passes `D_800A3FD8[effectProfileIndex]`, the output pointer
and `actorMatrices +0x300` to `15143134`, then returns one.

All 20 descriptors are 16-byte mixed records. Only their first three floats are
an offset; the fourth word overlays a lookup-selector halfword, variant byte
and an unnamed byte. Complete `15143134`, `150A7960`, `15142314` and `151EFEB8`
spans establish affine position transformation or translation extraction,
including the matrix-format mode. Existing `values[4]` and type names are kept.
No anatomical meaning is assigned to the matrix slot or the +0x74 gate.

Both callers, `15138BC0` and `15138C80`, obtain a profile from `15134070` and
reject 99 before calling this helper. The helper itself has no profile bounds
or sentinel check. Both callers still call `15138120` when this helper returns
zero; only later position-dependent work is gated. See also
[actor effect selector evidence](model_resource_role_names.md).

## Timer/callback evidence

`15149130` allocates 0x28 base bytes plus `extraBytes`. Flag bit 1 selects object
kind 0x5F instead of 0x23. `15167A68` passes that total to the allocator, and
`15168A4C` registers the kind. The constructor stores the signed timer at +0x0E,
expiry/tick/draw selectors at +0x10/+0x11/+0x12, flags at +0x0D and the shared
callback-set index at +0x13. The complete bzero leaf proves that only the
16 bytes +0x14..+0x23 are cleared. The source-local header view is 0x24 bytes;
it does not redefine the 0x28-byte allocation base. `locals.sp24` continues to
hold the total allocation size, and `locals.sp2C` the saved return pointer.

The 52-byte kind records at `8008BBC4` and `8008C7F4` are identical. Their +0x00
update entry is `15149264`, and their +0x08 draw entry is `15149490`. The update
sweep and renderer consume those entries. `15149490` dispatches signed selector
+0x12 through `D_8008A670`, skipping -1; the wrapper explicitly supplies -1
only for this draw selector. The +0x13 index is shared by the callback sets
consumed by `15149394`, `151493E4` and `15149434`.

The update order is optional flag-bit-0 decrement by `D_800BE9E4`, selected tick
callback, negative-timer test, selected expiry callback, and signed timer reload.
Removal is requested only if the resulting timer is still negative. This reload
matters: expiry slot 1 (`15193390`) resets the timer at `151934A0`, and slot 5
(`150C29F0`) resets it at `150C2BEC`. Removal dispatch through `1516972C` does
not prove immediate freeing. No seconds or frames are inferred.

The complete static inventory contains 84 constructor call sites and 34 wrapper
call sites, including different payload sizes and both kind choices. The shared
role is therefore not character-exclusive or particle-only. Expiry/tick/draw
selectors test -1 rather than performing general bounds validation; clamps in
the separate +0x13 callback-set consumers are not constructor validation.

## Model-resource evidence

The sole direct caller, `1513264C` at `15132778`, supplies template halfword
+0x56 as the lookup selector and a separate 16-byte cache node as the output
location. `151336A8` maps the selector through `D_800A3880`, passes the resulting
entry within bank09 to `1502B6BC`, and writes the returned model-resource base
through its output pointer, including on a null load.

The complete loading chain `1502B6BC` / `1502AC88` / `1502B350` / `1502B4A8`
loads the resource and relocates its 8-byte header records. The 233 lookup
selectors resolve to 232 distinct nonempty numeric resources; selector and
bank entry are different domains. Fresh checks cover every resource's five-record
header and terminated first display list. No source assets are reproduced here.

`1510CE60` prepares the first display list and a per-selector auxiliary list;
its result is not checked by the target. `15168E54` adjusts selected command
addresses using the resource base. Renderer `15132B80` follows object +0x8C to
cache node +0, then resource header +0, establishing three distinct pointers:
cache node, model-resource base and first display list. The target returns an
`s32` success flag: one proves a non-null model load, not every downstream
allocation. There is no local selector bounds check or profile-99 sentinel.
See [model constructor table evidence](us_model_constructor_tables.md).

The kind-record receiver paths are `151670C0` (update entry `+0x00`) and
`151674F8` (draw entry `+0x08`, object passed as its second argument).

## Source-local callback bytes

In `src/done/game/game_1765E0.c`, signed byte `+0x12` is `drawCallbackIndex`
in the header and dispatch views; unsigned byte `+0x13` is `callbackSetIndex`
in the header and state views. These are four member spellings for two bytes,
not new fields. Layout probes preserve header size/alignment `0x24/2`, state
`0x14/1`, dispatch state `0x13/1`, effect view `0x12/2`, and the data array.

The same unsigned +0x13 selector indexes three different 74-entry callback
sets: `15149394` uses `D_8008A688`, `151493E4` uses `D_8008A7B0`, and
`15149434` uses `D_8008A8D8`. Each uses `lbu` and substitutes entry zero for
values at least 74. The retained negative test cannot fire for an unsigned
byte. The third consumer additionally skips a null callback; its existing raw
`u8` offset access is unchanged.

These are verified kind-record receiver paths, not phase names inferred from
table order. `1516972C` indexes kind-record +0x28 and `1516979C` indexes +0x2C,
passing the object to `15149394` and `151493E4` respectively. The object-list
walkers `15169070`, `15169260` and `1516944C` invoke kind-record +0x1C, which
points to `15149434`, with the object and forwarded arguments. No broader
initialization, destruction, timing or exclusive-character claim is added.

Bounded execution of the exact four ROM dispatchers over all 256 byte inputs
(1,024 cases), including branch/call delay slots, confirms the unsigned clamps,
third-table null check and signed -1 draw sentinel. Execution stops at callback
entry; it is not runtime observation or a claim that other signed draw indices
are valid.

## Shared resource helpers

The matched helpers below use descriptive C names through source-local aliases;
linked address symbols, types, layouts and operations remain unchanged.

| Symbol | Descriptive role | Evidence boundary |
| --- | --- | --- |
| `func_1500390C` | `flat_asset_find_cached_index` | Returns the first equal cached address, or -1; duplicate pointers/sentinels prevent a unique inverse |
| `func_1510D374` | `flat_asset_rom_address` | Sums preceding compressed sizes onto ROM base `0x1A37E0`; no helper-local index validation is claimed |
| `func_1510D608` | `flat_asset_update_nonzero_state` | Nonzero state becomes `(previousState & 0x40) | stateBits`; bit `0x40` retains no invented meaning |
| `func_151EDB58` | `ui_release_model_resources` | Releases the resource at owner `+0x24`, then tags owner and copied display-list allocations with value four |
| `func_1510D630` | `flat_asset_release_reference_list` | Drops each counted flat-resource reference, then frees the list; no null guard or immediate asset-free claim |

Runtime flat IDs span `0..7761`, through 7,762 unsigned-halfword sizes at
`D_80091D20`. Empty slots 1767/1768 remain part of that identity domain; physical
stream ordinal is different. `func_1510D0EC` calls the ROM-address helper at
`0x1510D1D8`; HUD's descriptor renderer reaches that shared loader at
`0x151ED5E0`. `func_15040CC8` calls the reverse cache search at `0x15040D40`.
State-helper calls at `0x1510D708` and `0x1510D794` establish shared resource use,
not a HUD-exclusive lifecycle. See [HUD/menu evidence](us_hud_menu_assets.md).

The UI owner `func_151EB06C` constructs bank-09 models 164/162 with animation
selectors 23/8 and stores the results in `D_80090058`/`D_8009005C`. It draws those
same pointers and later passes them to `func_151EDB58`. The constructor stores
its display-list count at `+0x14` and list pointers from `+0x04` at four-byte
strides. This supports `uiModel`, `displayListIndex` and `displayListCursor`.
Allocation tagging is not described as immediate deallocation: the helper
continues reading the owner after tagging it. No named character or world
placement is inferred from this UI path.

`1510D630` reads a signed halfword count at list `+0` and halfword flat IDs
from `+2`, calls `1510D694` for each, then frees the list through `10004074`.
The callee decrements nonzero reference counts in `D_800D9F68`; transition to
zero widens the pending range and requests state three through `1510D608` at
`1510D708`. The loader conditionally increments the same counts, saturating at
255 (`1510D338..1510D358`). This names reference release, not immediate asset
deallocation or a new ownership contract.

## Attachment action 35 and 68 requests

`func_1514DCAC` has the bounded role
`actor_request_attachment_actions_35_and_68` through a source-local C alias;
its pointer parameter is `parentActor`.
It first stores numeric `0x6000` at parent `+0x9C`, whose meaning is left unnamed,
then unconditionally requests action 35 followed by action 68 on the same
saved pointer. Its existing raw `s32` argument words, including `0x3F800000`,
are retained without changing the call ABI.

Action 35 has one kind-two record: model byte 133, animation selector two.
The descriptor selector at `+0x17` therefore takes the animated loader path
through `func_1503F62C` and `func_1502FE10`. Action 68 has one kind-one record:
model byte 29 and selector -1, taking `func_1502FE10` directly. Both loaders
resolve bank 09. Numeric-ROM/preview joins identify the exact source records. Prior visual
inspection supports only helmet-like and cigar-like appearance descriptions for
models 133 and 29 respectively. Their item identities, military role and
gameplay use are not confirmed by those images or earlier gallery labels.

Action selectors 35/68 are not model IDs 133/29. Parent `+0x3B` equal to zero,
duplicate suppression, allocation failure or model-load failure can prevent
creation. The caller ignores the returns, so the role describes requests,
not guaranteed attachments or exclusive character ownership.

## Digital timer

These two matched helpers use source-local aliases with unchanged linked symbols.

| Symbol | Descriptive role | Boundary |
| --- | --- | --- |
| `func_15093818` | `timer_display_set_enabled` | Nonzero request initializes only on a disabled-to-enabled transition; zero clears the enable byte |
| `func_15093878` | `timer_display_init` | Loads bank-09 model 186 and allocates `0x80` bytes for matrix storage |

The direct model loader `func_1518C900` supplies the timer display-list address to
`D_800D2448`; the allocation goes to `D_800D244C`. The raw renderer
`func_150938BC` selects digit textures, installs four segment pointers, chooses
matrix storage and submits that display list. The two globals retain their
linked names and types. Clearing the enable byte is not called deallocation.
The inspected `00:00` texture selection is an explicit preview preset, not an
initial or observed runtime timer reading. Timer units and the existing
excluded renderer candidate remain unchanged.

## Bounded source-local action constants

The two calls in `func_1514DCAC` now spell their reviewed selectors as
`ACTION_SELECTOR_35 = 35` and `ACTION_SELECTOR_68 = 68`. These anonymous enum
constants are declared after the reviewed source-unit comment and before use.
They describe action-table selectors, not model IDs or guaranteed creation.
The constants replace only the two unsuffixed integer call operands. The
function separately uses its descriptive C alias. Signatures, parameter types,
other literals and numeric linked symbols remain intact; no shared header or
enum-typed ABI is introduced.

Whole-source m2c context remains available and all recovered signatures are
unchanged. Running the pinned m2c parser on the same raw function with the full
pre/post contexts succeeds in both cases and produces identical output. That
output retains numeric literals, so regeneration does not automatically preserve
the semantic spelling. The enum declarations must remain before their uses.
This result does not authorize enum replacements for unsigned literals, masks,
address offsets, pointer arithmetic, signatures or automatic declaration repair.

Action constants use neutral selector numbers. Legacy cigar/helmet wording is
appearance-based, not confirmed item or military-role identity. The conditional
selector-to-bank-09 routes remain independently proved.
