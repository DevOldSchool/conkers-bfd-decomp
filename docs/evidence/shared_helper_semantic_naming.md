# Shared-helper semantic naming

This small slice adds descriptive roles and parameter/local names while retaining
numeric symbols. The names describe verified behavior; they are not recovered
original names. No new C match, field/type name, enum, alias, shared header,
ABI change or layout change is introduced.

## Roles and naming limits

| Function | Descriptive role |
| --- | --- |
| `151380B4` | `actor_transform_effect_profile_offset` |
| `15149130` | `timer_callback_object_create` |
| `151491F4` | `timer_callback_object_create_without_draw_callback` |
| `15149264` | `timer_callback_object_update` |
| `151336A8` | `model_resource_load_by_lookup_selector` |

The first four retain their matched definitions. Their renamed identifiers are:

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
[actor effect selector evidence](actor_effect_selector_semantics.md).

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

## Complete-span provenance and preservation

The independently normalized US ROM has SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Preparation reauthenticated 175
complete game target/caller/support spans, 48,272 main-reference instruction
words, the 160-byte bzero leaf, nine table spans, both kind records, 20 profiles
and all 233 selectors/232 model resources. `151EFEB8` is full-span reference
support, not a new function registration. Static J/JAL and aligned data-pointer
coverage does not claim completeness for computed runtime calls.

| Function | Full US span, end exclusive | Bytes | ROM/reference SHA-1 |
| --- | --- | ---: | --- |
| `151380B4` | `0x151380b4..0x15138120` | 108 | `7fb98757d8bef9d592831be2ec68857e43f6234a` |
| `15149130` | `0x15149130..0x151491f4` | 196 | `59e729dd3894013d736f5be8800f6150cc222cfd` |
| `151491F4` | `0x151491f4..0x15149264` | 112 | `1005ff2639fcb1610f3923942a985db537659dcd` |
| `15149264` | `0x15149264..0x15149318` | 180 | `2db6209a1a8c9a38d88fa0ec61fe95b84b0bbea2` |
| `151336A8` | `0x151336a8..0x15133760` | 184 | `2432f6c82170d429bdbad3f281b65ca8e0663945` |

Only 76 identifier occurrences and five comments change. Removing the exact
added comments and reversing those identifier occurrences recovers all three
whole sources byte-for-byte. A separate complete-source lossless-token comparison
confirms every other original token, including whitespace, unchanged. All 32
deferred guard-through-pragma blocks are byte-identical; directives, numeric
symbols, literals, types and fields are preserved. No renamed identifier collides
with a tracked C/header macro. Isolated patch apply/reverse and whitespace checks
pass. The three live target sources were unchanged by preparation.

## Frozen source pins

Prepared against `abc5db725707966917b3209b36f137af5fc7b8ae`; exact target-source
hashes guard against unrelated concurrent changes.

| Source | Before SHA-256 | After SHA-256 |
| --- | --- | --- |
| `src/game/effects/blood.c` | `3376e7743c1aa3f6034fcfbbb7e5d796101076c9e3f0013710a2cd30e479266c` | `13f6a0abb0993b88a7f5c24844c060d9be4b2f4a806e65585b6f510acb672bcd` |
| `src/done/game/game_1765E0.c` | `83ae49f606a5192fbd5cda53622bd23c755110649b07de7d678991160b6c6c68` | `474f0f8bddccbdd6dc0fec0842250a061b6524deec0aafd9837ee1e0102a75e2` |
| `src/game/game_15F680.c` | `b471e7fcd34c445e911295a1e135f5befecf492647fca13fb002905d3a169116` | `1d51c07a6835f84d8894be572a7aa0a0dbb6921dba639308352bb5e852b75a95` |

Source-only patch SHA-256: `5ef636aff0e56cd916dbb94f133a5af0d00141efa5ca1bc3ab401da683f6a31b`.

## Acceptance remains separate

This preparation ran no compiler, focused comparator, source-unit layout gate,
game build, matching/queue transaction, commit or push. It adds zero C matches.
Independent focused `CURRENT (0)` rechecks remain pending for `func_151380B4`,
`func_15149130`, `func_151491F4` and `func_15149264`, followed by reviewed layout,
clean batch, full US ROM/mapped-layout, progress/whitespace and complete-suite
gates. Raw/deferred `151336A8` is not promoted by its comment.

## Accepted integration

The four named C functions and same-unit loader neighbor `15132A4C` each retain
full-span US `CURRENT (0)` and reviewed source-unit layout. The clean five-function
batch returned `BATCH_COMPLETE`. Integrated game/data/rodata, the byte-exact full
US ROM build, progress and whitespace passed. All 1,741 tests pass in the host
suite (37 environment/tool skips) and ROM-enabled pinned suite (one optional
validator skip). Independent read-only review reauthenticated the full spans,
tables and model resources and approved the semantic bounds and exact inverse.
The result adds four C-role descriptions and one raw-role comment, no fields,
linked aliases, new C matches or matched bytes.
