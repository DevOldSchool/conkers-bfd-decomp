# Actor representation selection semantics

These are descriptive roles inferred from the checksum-validated US ROM, not
recovered original names. They refine the earlier
[representation and asset audit](actor_representation_asset_semantics.md) and
[expression audit](character_expression_semantics.md). The linked numeric
symbols, declarations, types, offsets, source order and executable expressions
are unchanged. Only one matched local identifier is renamed. The other five
role changes are comments, including four on raw/deferred functions.

## Override control and applied state

The fields have distinct contracts:

| Actor offset | Observed contract |
| --- | --- |
| `+0x1C9` | Override/control selector: zero permits automatic selection; a positive one-based selector requests an entry; `0xFF` requests a reset |
| `+0x1C8` | Applied zero-based representation ordinal, written by either automatic selection or explicit application |
| `+0x2C4` | Pointer to the representation model-byte list |
| `+0x2C8` | Count of the list prefix eligible for automatic selection |
| `+0x2C9` | Total considered list count, including the explicit-only suffix |
| `+0x04` | Mutable applied model byte, written by the common assignment helper |

These are evidence descriptions, not new fields or layout changes. The existing
candidate spelling `scale` at `+0x3C` is not independently established as that
field's gameplay meaning, and is not adopted by this audit.

An aligned byte-memory-instruction scan of the normalized main, decompressed
game and debugger CPU images finds 16 direct-offset `+0x1C9` accesses. Fifteen
are actor-related; `151C7C04` is a stack-relative byte store in a rendering
function and is excluded. This scan does not resolve computed aliases, bulk
copies, other overlays or runtime reachability. The separately reviewed bulk
initializer `1505F188` clears all `0x32C` actor bytes, initializes the list to
actor `+4` and both counts to one, then writes model byte `0xFF`.

The non-automatic producers are command handling at `15024CBC/15024CC4`, reset
consumption at `1502FC28`, state-dispatch selection at `150669D4`, the actor-script
handler at `15079210/15079218/1507921C`, and descriptor dispatch at
`1509917C/15099758`. The command path at `15024CBC/15024CC4` maps input zero to
`0xFF`, while `1509917C` and the actor-script handler preserve zero. Thus the
field is not merely a boolean lock or the ordinary distance-selected ordinal.

## Getter refinement

`func_150849A0` is `actor_get_override_or_base_representation_model`.
Its complete 44-byte span returns `list[selector ? selector - 1 : 0]`, reading
the unsigned selector at `+0x1C9` and list pointer at `+0x2C4`. It never reads
`+0x1C8` or the applied byte at `+4`. The only C identifier change is the local
`representationSelector` to `representationOverrideSelector`.

The zero-selector path always chooses the first list entry, even if automatic
selection has applied a different ordinal. Its seven direct call sites are
`1502C7C4`, `1507E6EC`, `1507E914`, `1507E980`, `1507EA00`, `15083210` and
`1517AD68`. The expression and morph consumers therefore need not use the
currently drawn distance variant. This does not assert a runtime call order.
The existing argumentless `func_150849A0()` call in `func_1507E6B8` is preserved;
no calling-convention repair is part of the naming change. The count helper's
separate `actor+4 == 0x96` branch and `0xFF` model sentinel are also unchanged.

`func_150849CC` is `actor_get_override_or_last_automatic_model`. A nonzero
selector chooses `selector - 1`; otherwise the ordinal is
`automaticCount ? automaticCount - 1 : 0`. It optionally writes that ordinal
through its second argument, then returns the selected model byte. The four
direct call sites are `1502CAC0`, `1502CD88`, `15186AB0` and `15189644`.
Its role does not claim a universally distinct, lowest-detail or last-drawn
model. This is an unchanged raw function with a disabled candidate at
`CURRENT (235)`; the role is only a comment before the candidate guard.

Neither getter recognizes the `0xFF` reset request or checks the ordinal
against either count. In particular, an unconsumed `0xFF` selector yields
ordinal 254 rather than a normalized fallback. Naming must not add a safety
check or imply that one exists.

## Actor-script setter

`func_150791F0` is `actor_script_set_representation_override`. It reads the
current actor from `D_800D154C` and operand byte from `D_800D1890`. When the
operand exceeds total count `+0x2C9`, it stores `0xFF` at actor `+0x1C9`;
otherwise it stores the operand unchanged, including zero. It does not apply
the model or change the applied ordinal. Its C body remains byte-for-byte
unchanged; no padded structure is split to name the field.

The data word at `80086A24` points to this function. It is slot `0xBD` of table
`80086730`. The complete interpreter `1507BC14` reads the opcode through actor
`+0x218`, copies the next four operand bytes to `800D1890..800D1893`, calls the
indexed table target at `1507BD60`, and advances by five for this opcode. This
is evidence of the actor-script handler, separate from the 12-byte
animation-event protocol. The complete registered setter span also includes
the store at `1507921C` beyond the preceding return sequence; all 56 bytes
remain part of its independent comparison.

## Automatic distance selection

`func_1502C6E8` is `actor_update_distance_representation`. Its actor address is
`800CC2D0 + actorIndex * 0x32C`; its view address uses a signed view index and
stride `0x9A0` from `D_800DBFF0`. It skips when the override is nonzero or actor
kind is seven. A zero automatic count also exits.

It sums squared XYZ differences between actor `+0x14/+0x18/+0x1C` and view
`+0x2F8/+0x2FC/+0x300`. Strict comparisons against squared thresholds 500, 730,
1500 and 2000 yield an initial ordinal 0 through 4. The middle thresholds are
independently read floats at `80096DE0/80096DE4`. Before applying the result:

- An initial ordinal at least two is decreased by one if actor float `+0x3C`
  is less than three; that float's broader meaning is unresolved
- Base model `0x5A` moves ordinal zero to one; base model zero with
  `D_800BE616 != 0` selects ordinal one
- `D_800C35EA == 1` forces ordinal zero
- The ordinal is clamped using automatic count minus one, preserving the
  original signed checks and sentinel behavior
- A changed ordinal selects its model through `150837D4` at `1502C950`, then
  is stored at actor `+0x1C8` at `1502C960`

These conditions prevent an unconditional mapping from fixed distance bands
to model IDs. Only the automatic prefix is eligible. No field, candidate
expression or condition is renamed or repaired in this function; the
`CURRENT (1493)` disabled candidate and raw assembly remain unchanged.

## Explicit application and model assignment

`func_1502FBE8` is `actor_apply_representation_override`. Selector zero returns.
Selector `0xFF` is cleared and applies ordinal zero without testing whether it
was already applied. Other selectors use `selector - 1`; an out-of-range or
already-applied ordinal returns. Rejected nonzero selectors remain stored and
therefore still prevent automatic selection. This is not normalization or
fallback on every invalid selector.

For an applied change it reads the list, calls `150837D4` at `1502FC74` and
stores the applied ordinal at `1502FC8C`. It compares old and new route-data
pointers, either resets an invalid old route to zero or reselects the old route,
preserves the existing mode-dependent `D_800C3638` stores, and calls default
expression restoration at `1502FD54`. It does not reload the representation
list or counts. The `CURRENT (979)` disabled candidate is unchanged.

`func_150837D4` is `actor_assign_model`. It derives the actor-pool slot and
writes the supplied model byte at `15083820`, in a branch delay slot. For model
`0xFF`, it writes the original field reset/default values; otherwise it reads
model defaults, updates `+0xC8`, calls `15062BDC`, and writes the kind byte at
`+5`. It then derives the animation-model byte through `15084D00`, writes it
at `+6`, and conditionally loads the associated route resource into `+0x58`.
Its four direct callers are automatic selection, override application, actor
creation and actor replacement. The role does not assert an immutable spawn
identity or describe unrelated actor state. Its existing parameter widths and
`CURRENT (568)` disabled body remain unchanged.

## Stored prefix and suffix evidence

All 186 present bank-0x11 bundles were independently parsed against the existing
16-byte descriptor/64-byte-defaults contract. Eleven have nontrivial list
metadata. `150839B8` copies defaults byte four to automatic count, uses defaults
byte five to select a pointer from `80086CAC`, and adds defaults byte `0x38`
to form the total byte count. Its original byte-store truncation is preserved.
When defaults byte four is zero, it retains the initialized one-model fallback.

| Default model IDs | Automatic count | Extra entries | List pointer | Considered model IDs |
| --- | ---: | ---: | --- | --- |
| `0` | 5 | 2 | `8009CDD0` | `0, 1, 2, 3, 4, 130, 150` |
| `1, 2, 3, 4` | 5 | 1 | `8009CDD0` | `0, 1, 2, 3, 4, 130` |
| `58, 61` | 5 | 1 | `8009CDE0` | `58, 58, 58, 58, 58, 61` |
| `104` | 2 | 0 | `8009CDE8` | `84, 104` |
| `116, 122` | 3 | 0 | `8009CDEC` | `90, 90, 90` |
| `150` | 1 | 5 | `8009CDD8` | `150, 150, 150, 150, 150, 130` |

For the model-zero list, IDs zero through four form the automatic prefix;
130 and 150 are explicit-only suffix entries. Repeated IDs in other lists prove
that representation ordinals need not be distinct meshes. Selector six resolves
130 for a model-zero-created list, 61 for a model-58/61-created list, and 130
for a model-150-created list. The generic selector-six stores at
`150669D4/15099758` therefore do not establish a costume label. No new character,
costume, appearance, enum or asset name is introduced.

## Independent full registered spans

These spans were reread from normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` (67,108,864 bytes). Extents use
`progress/functions.json` at checkpoint
`f395dbbf606db66977a64165f98e8b1d92bde416`, descended from fresh-main base
`fb053d62`. Every role span includes all registered bytes, delay slots and
terminal padding. Existing raw or indexed reference assembly was independently
checked for contiguous addresses and exact whole-span ROM equality. These
checks establish evidence identity, not a new compiler match.

| Role symbol | State | Bytes | SHA-1 |
| --- | --- | ---: | --- |
| `func_150849A0` | `matched` | 44 | `62d89a7ec36b39096dfd2c98896619b96b71866a` |
| `func_150791F0` | `matched` | 56 | `4211581561b3dcc5ec600d3a413aacdf8c7b49a4` |
| `func_150849CC` | `raw_asm` | 76 | `f406a1972f5f0f73bdcce7b9fb373af650daf567` |
| `func_1502C6E8` | `raw_asm` | 652 | `a168f14ac1b2fe5bb064d8e6194c3b486dc00023` |
| `func_1502FBE8` | `raw_asm` | 392 | `86363abf6467595cc9d78c3c1b6577bb4374835f` |
| `func_150837D4` | `raw_asm` | 280 | `7bd9c8414be99e3bc26944fe08eb04064933a30d` |

The same complete role spans have these SHA-256 values:

- `func_150849A0`: `a9c2b556bc04c94bc24acdaab75d2f6c1fb49c949ada74fef06f7b2eb09c7e57`
- `func_150791F0`: `7817c73825f853e532b0a31e79d7687fd3a6990615cf0ae183efebf457a85aef`
- `func_150849CC`: `69dd64e52454a5db16aa031021fd5e6ee7c1a1a0140673367baad3924113ab24`
- `func_1502C6E8`: `b6ef1881263be8caaa57f6e0096dc3565202e9c5466c953ae254ec22996e3a40`
- `func_1502FBE8`: `ad1d536ed4dfd8a5b9a285ead4a92591ca5bbbf39cb9ebcd8da4a797981eb8e4`
- `func_150837D4`: `0e24df9eeed925ffd2e61947bf0b1e365a6f375df88e373a673ad6bd781e5af5`

Supporting full-span identity checks:

| Symbol | Bytes | SHA-1 |
| --- | ---: | --- |
| `func_1505F188` | 272 | `c4b6d2297e2dc2c7f3c7c5724781e9042b9d3204` |
| `func_150839B8` | 272 | `83514e60fb88c39b8e225ba6b68a54a5094c2dff` |
| `func_1507BC14` | 412 | `e04f71fcd2150534ad374b1be8b77050eb1be2bd` |
| `func_1507E6B8` | 132 | `059fe16ca29114f79874eb5bba055de0c5c3b12c` |
| `func_1507E908` | 96 | `c602e20a2b335d94feb349539cbdb76d69957d50` |
| `func_1507E968` | 128 | `94fb99b2aabedd05d7d1404d8013af047b86a5af` |
| `func_1507E9F8` | 76 | `31fcadb16432eb6925dc6fcf17d561857102493d` |
| `func_1502C974` | 704 | `166b05f7f97b828a9ebad3c9a7e51e8a6b748eea` |
| `func_1502CCFC` | 2128 | `2176c655198fed8b1867b28f059cb4765bced897` |
| `func_1502460C` | 8128 | `363af55b580310f7cfa3dee99c50a0065274dffd` |
| `func_15065A5C` | 19348 | `7f60cbcdfdc421e08122fd361bcebabd913da9dc` |
| `func_15097A8C` | 8584 | `652bb7dc25c580be9d73f138b68687333da7ce6d` |

## Source equivalence and required acceptance

An inverse whole-word replacement within `func_150849A0` restores all four
occurrences of its original local selector. The replacement name is absent
from the original function. Reversing only the exact role-comment additions
and correction then reconstructs all three complete source files byte-for-byte.
All 55 disabled candidates in those files, including their scores, guards,
end markers and adjacent raw-assembly pragmas, are byte-identical. The complete
expression source is unchanged, including its argumentless helper call.
There are no new types, fields, headers, enums, linked symbols, ABI changes or
source-unit changes, and no altered sentinel or overflow behavior.

Preparation performed no build, matching attempt, inventory edit, commit or
push. Fresh acceptance must recheck these two existing matched IDs:

```sh
./conker finish func_150849A0
./conker finish func_150791F0
./conker verify-batch func_150849A0 func_150791F0
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

The first has a local identifier change; the second has only a role comment.
Both must retain complete `CURRENT (0)` and reviewed source-unit layout, with
clean batch/game/data/rodata, progress and whitespace gates. The four raw
functions remain raw and must not be promoted or sent through candidate repair
for this semantic-only batch. No additional callers require semantic edits
because linked names, prototypes, fields and declarations are unchanged.

## Accepted integration checkpoint

Both matched targets passed independent full-span US `CURRENT (0)` comparisons
and reviewed source-unit layout checks. The clean two-function batch returned
`BATCH_COMPLETE`; integrated game/data/rodata checks, a byte-exact full US ROM
build, progress and whitespace checks passed. All 1,726 tests pass in the host
suite (37 environment/tool skips) and ROM-enabled pinned-toolchain suite (one
optional Khronos-validator skip). Independent read-only review authenticated
all 44 complete supporting spans, the direct selector census, all 186 defaults
and 11 nontrivial lists, and exact source inverse preservation. This adds one
matched-C descriptive role and four raw-function role comments, refines the
existing getter role, and adds no C match, field or shared declaration.
