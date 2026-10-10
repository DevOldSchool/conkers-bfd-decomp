# Actor representation selection and mutable model bytes

The matched override-or-base getter and actor-script setter use descriptive
source-local aliases with original linked symbols, ABI and operations preserved.
Other function roles remain evidence comments only.
[Confidence and provenance](model_name_confidence_review.md) distinguish code
behavior from model descriptions and runtime activation. Full consumer pins are
in the registry; additional complete support spans are in that note.

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
`+0x1C8` or the applied byte at `+4`. Its local selector is named
`representationOverrideSelector`; the function alias does not change its
parameters, fields or operations.

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

The getter zero branch is at `150849A4`; nonzero list selection is at
`150849B0..150849B8`. Initializer `1505F188` installs the actor-byte fallback
through `1505F1F4/1505F20C`.

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
at `+6`, and, when the separate bank-0F route count for that representative
is nonzero, caches the bank-02 ROM/archive address resolved by `1502B020`
at `+0x58`. A zero count leaves the existing cache unchanged. This is an
archive-address lookup, not a load of the route payload; see the
[animation-model representative audit](actor_animation_model_group_semantics.md).
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


## Source-local model-byte fields

`Game83300Actor.modelIndex`, `GameA28B0State.modelIndex` and
`GameB21B0Object.modelIndex` name existing unsigned bytes at `+4`; no shared ABI
is introduced. The latter two partial views remain size `0x320`, alignment four,
with inner pointers at `+0x31C`; the pool stride is `0x32C`, so the last twelve
bytes are outside those views. `modelIndex` is mutable and includes sentinel
`0xFF`, separate from actor slot, kind, override selector, ordinal and byte `+6`.

## Actor provenance and every member access

The original actor traversal `1504A730` forms the pool base `800CC2D0` at
`1504A7C0/1504A7E4`, stores the current slot in `800D154C` at `1504A8A0`, and
advances it by `0x32C` at `1504AC84` over 25 slots. A second traversal
`1504ADD0` independently stores the active actor at `1504AE58`. The A28B0
receivers are this current-actor global or `other`, explicitly derived from
the same pool in `150768DC`. The local current-actor save/restore paths retain
actor provenance; `15072208` returns only pool slots or null.

`150837D4` computes a pool slot, stores the supplied model at `15083820`,
and calls `15084D00` with that actor at `1508389C/150838A0`. The latter is the
only direct game-overlay caller of B21B0's model-byte consumer. Its returned
model-sharing representative is stored separately at actor `+6` at `150838B0`.
The same B21B0 view's two other typed consumers, `15085410` and `15085420`,
access only the inner pointer. Their proven callers obtain actor slots from
`1505EEF4`; their complete C bodies and signatures remain byte-identical.

| Function | Original instruction address | Member operation |
| --- | --- | --- |
| `15075548` | `15075604` | Read current model for comparison with `0x28` |
| `150768DC` | `150769B4`, `150769B8` | Compare current and other actor models |
| `150768DC` | `15076A0C` | Index model defaults in `D_800D1C90` |
| `15079790` | `150797BC`, `150797CC` | Store `0xFF` or `0x3A` directly |
| `1507BB28` | `1507BB38` | Index model-keyed route/script resources in `D_800D1588` |
| `15084D00` | `15084D04` | Read the actor model before searching model-sharing groups |

Those are all eight member accesses, plus the two declarations. The model
loader `1503CF20` uses bank 01; `1503D774` uses the same index for bank-11
defaults. The script-resource loader `1503D660` resolves bank-0F metadata.
The script-entry key bytes subsequently read in `1507BB28` are a separate
domain and are unchanged. Automatic selection and explicit application both
call `150837D4`; `1505F188` initializes the actor model to `0xFF`. These facts
establish mutability and sentinel behavior without asserting observed gameplay
execution, appearance or complete indirect-call reachability.

`GameB21B0PlayerRecord.field_4` remains an `s32` in a separate `0x1C`-byte
player record; both its declaration and use are unchanged.
`Func1506AC0CPacket.field_4` remains an unsigned byte in an eight-byte stack
packet. Original `1506AC2C/1506AC44` copies argument byte `+0x3B` to this packet,
not actor byte `+4`. Its entire source file is unchanged. No `field_70` name,
appearance label, shared declaration or ABI repair is part of this change.
