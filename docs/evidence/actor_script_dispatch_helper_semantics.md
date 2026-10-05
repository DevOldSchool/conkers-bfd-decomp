# Actor-script selected-state and callback helpers

Six existing matched commands in `src/game/game_A28B0.c` use source-local
aliases. Numeric symbols, original parameter types, operand/global writes
and registered spans remain unchanged. Names describe generic actor operations,
not character, model or scene identities.

| Symbol | C name | Opcode | Dispatch slot | Bytes |
| --- | --- | --- | --- | ---: |
| `150778F0` | `actor_script_advance_path_point` | `0x68` | `800868D0` | 184 |
| `1507813C` | `actor_script_branch_on_selected_actor_inactive` | `0x9F` | `800869AC` | 104 |
| `1507879C` | `actor_script_branch_on_selected_actor_animation_time` | `0xA9` | `800869D4` | 216 |
| `15078A08` | `actor_script_copy_selected_actor_animation_times` | `0xAD` | `800869E4` | 88 |
| `1507A8EC` | `actor_script_branch_on_selected_actor_model` | `0x2A` | `800867D8` | 152 |
| `1507B884` | `actor_script_dispatch_callback` | `0xD5` | `80086A84` | 112 |

## Advancing a path point

The command advances actor+0x21E by signed step +0x221, adds the selected
limit, takes remainder by that limit, then clamps upward to minimum +0x220.
Nonzero +0x21F overrides the path-table count minus one. Both additions narrow
back to u8 before the remainder; the intermediate stores are preserved.
This is not ordinary signed modulo. There is no graceful zero-limit handling;
the original division-by-zero trap remains. Existing
[path evidence](actor_script_path_helper_semantics.md) establishes these fields.

## Selected actor and animation state

Actor+0x222 selects pool record `800CC2D0 + index*0x32C`, without index checks.
The inactive predicate branches through `15075400(operand0)` exactly when
that record's word +0 is zero. It does not establish death, destruction,
invisibility or a missing record.

The animation-time predicate dereferences selected actor+0x2D0 and reads
state float +8. Unsigned operand1 is converted to float for comparison:
operand2 zero means strict less-than, one means strict greater-than, and
other modes do not branch. Equality does not branch. There is no actor-state,
index or animation-pointer guard. The original frame consumer `1502D824`
loads actor+0x2D0 at `1502D878/1502D884`, reads float +8 at `1502D8EC` and
truncates at `1502D8F8`, supporting fractional time rather than an integer frame.

The copy command transfers selected actor state floats +8/+0xC into the
executing actor's corresponding primary/secondary times. It does not copy
animation IDs or other state, cap time, check compatibility or guard pointers.
Original `1505E060` snapshots +8 to +0xC; the frame consumer chooses paired
headers with stride four. See [animation state evidence](actor_animation_state_helper_semantics.md).
These are not current/previous rendered-frame guarantees.

## Numeric model predicate

The command compares operand1 with selected actor's model byte +4, then toggles
global operand2 with XOR one on equality. It branches through operand0 whenever
the resulting operand2 is nonzero. For initial modes zero/one this gives
equality/inequality; values at least two remain nonzero and branch regardless.
The global operand mutation is preserved. There is no active-state or index
validation. `D_800CC2D4` is pool base+4, whose model-index role is established
by the existing model/resource consumers; no specific model identity is needed.

## Callback dispatch

The command resolves `D_80086150[operand0]`. For a non-null callback it saves
`D_800D154C` and `D_800C3E78`, calls with the selector as its s32 argument,
then restores those two globals in the original order. It does not restore
operand globals or every callback side effect, and it does not bound the index.
No stronger effect/event/character label is inferred.

Original dispatcher `15071D38` uses the same table at `15071D48..15071D60`.
[Callback-group evidence](game_dispatcher_callback_groups.md) and
[constructor/table evidence](game_981e0_constructor_literal_pool.md) corroborate
the table and argument forwarding.

## Evidence and acceptance

All six opcode entries were read from checksum-validated original initialized
game data, and all 856 original handler bytes in `reference/game/us/asm/75400.s`
were compared with the US game image. Existing [actor utilities](actor_utility_helper_semantics.md)
and [script geometry](actor_script_geometry_helper_semantics.md) support the
shared pool/animation conventions. Full-span CURRENT (0), existing layout,
clean batch, tests, progress, whitespace, RSP and exact main/game images gate
these aliases. Movement modes, generic flags, unresolved selectors and the
held full-span mismatch remain untouched. No new C match is claimed.
