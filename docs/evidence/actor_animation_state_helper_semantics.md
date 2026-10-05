# Actor animation state and model-resource helpers

Five existing matched C functions use source-local descriptive aliases. Numeric
linked symbols, signatures, padded layouts, volatile accesses and operations
remain unchanged. All surrounding unmatched functions retain their status.

| Symbol | C name | Span |
| --- | --- | --- |
| `1503D45C` | `actor_scripts_relocate_program_offsets` | `0x28` |
| `150838EC` | `actor_create_animation_state` | `0xCC` |
| `1505DFDC` | `actor_reset_animation_state` | `0x84` |
| `1505E060` | `animation_state_copy_primary_to_secondary` | `0x64` |
| `15004F30` | `model_resources_clear_cache_state` | `0xB0` |

## Bank-0F actor scripts

`1503D45C` adds the supplied base to the first word of each eight-byte record,
stopping before a zero-pointer sentinel and leaving the other word untouched.
The sole direct call at `1503D70C` passes the bank-0F header's relocated first
pointer and payload +0x10. Unlike `asset_relocate_untagged_offset`, this helper
has no tag test or already-relocated check; neither table extent nor null input
is validated.

`1507BB28` obtains this table through `D_800D1588[model] - 0x10`, searches its
key byte at record +4, and returns the pointer at +0. The actor-script
interpreter `1507BC14` calls that lookup at `1507BCC0`, stores the result at
actor +0x218, and dispatches its commands at `1507BD60`. These are actor-script
programs, distinct from the route-event offsets at route +4 described in the
[existing relocation evidence](actor_representation_asset_semantics.md).

The original US bank-0F data has 152 present entries. Its 121 present script
tables (119 nonempty) contain 1,076 records; all tables terminate and all nonzero
program offsets plus 0x10 remain inside their payload. These data checks support
the stored contract, not gameplay activation.

## Allocation, reset and paired state

`150838EC` uses actor model byte +4 and skips allocation if its route root or
count is absent. Otherwise it allocates 0x3E0 bytes with the original arguments
(1, 2, 0), stores the result at actor +0x2D0, clears only the first 0x40 bytes,
and calls animation selector `1505E650`. Return one means allocation failure;
zero means either skipped or successful. Existing-state protection, freeing,
model-index validation and whole-allocation clearing are absent. The u16
animation argument and both s32 forwarding arguments keep their exact ABI.
Original direct calls are at `1502DC4C`, `15082FC4`, `15083D68` and `151954F4`.

`1505DFDC` always writes actor +0x84 = 0xFFFF. If animation state exists, it
clears its +0x28 word, zeros [state+0x40, state+0x3E0), sets bytes +0x41 and
+0x211 to the truncated value `D_800C4ED0[model] + 1`, and clears +0x30/+0x34.
It does not free the allocation, clear the entire header or reset actor event
state. Calls at `1502D87C`, `1505E440`, `1505E718` and `1505E760` connect this
to frame fetching, failed descriptor loading and absent/invalid routes.

`1505E060` copies halfword +4 to +6, floats +8 to +0xC, +0x10 to +0x14,
+0x20 to +0x24 and +0x18 to +0x1C, byte +0x38 to +0x39, and word +0x28 to
+0x2C. It then copies 0x1D0 bytes from +0x40 to +0x210. The sole direct call
at `1503311C` supplies an attachment's animation state from +0x48, so the
helper's name is not actor-only. Consumer `1502D824` reads both blocks with
stride 0x1D0; `1505E0C4` repeats this snapshot sequence before installing a
primary descriptor. It is a partial primary-to-secondary snapshot, without a
claim about a rendered previous frame or a specific blending outcome.

## Shared model cache reset

`15004F30` clears nine arrays for the 187-model cache: 0x2EC bytes each at
`D_800D19A0`, `D_800D1C90`, `D_800D1588`, `D_800C5C08`, `D_800C6070` and
`D_800C6360`; 0xBB bytes each at `D_800D1F80` and `D_800D2040`; and 0x176
bytes at route-count table `D_800C5A90`. Existing bank01/bank11/bank0F loaders
and consumers establish the resource-pointer, usage/countdown and count roles.
The direct call at `150169B0` precedes bank-0E loading. It frees no resource and
does not clear every installed model/draw table.

## Full-span evidence

Original references `3CF20.s`, `81690.s`, `55E50.s` and `4F30.s` cover all
652 registered bytes and agree with the checksum-validated US game image.
`15004F30` retains the two standalone trailing NOPs at `15004FD8/15004FDC`.
The complete loader, script lookup/interpreter, descriptor installer and paired
frame consumer support the roles above. Full registered CURRENT (0), existing
source-unit layout gates and complete-image equality gate the aliases; static
call-site evidence is not proof of runtime reachability or indirect-call coverage.
