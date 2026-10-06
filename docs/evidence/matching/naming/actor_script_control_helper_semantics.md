# Actor-script program control and playback commands

Source: `game_A28B0.c`. Shared interpreter commands retain their void(void)
signatures and global operands.

| Symbol | C name | Opcode | Span |
| --- | --- | --- | --- |
| `15075DE8` | `actor_script_switch_program` | `0x08` | `0x84` |
| `15075EB4` | `actor_script_branch_random_percent` | `0x0B` | `0x4C` |
| `15077BB4` | `actor_script_reset_program_by_model` | `0x95` | `0x30` |
| `15077E9C` | `actor_script_play_mp3_asset_spatial` | `0x98` | `0x50` |
| `15078520` | `actor_script_branch` | `0xA7` | `0x24` |
| `150792E0` | `actor_script_set_default_program` | `0xB0` | `0x1C` |

Interpreter `1507BC14` loads operand0..3 into `D_800D1890..1893`, dispatches
through `80086730`, then advances the executing actor's cursor +0x218 by five.
The [path-command evidence](actor_script_path_helper_semantics.md) establishes
that shared convention. Original initialized-data slots for this group are
`80086750`, `8008675C`, `80086984`, `80086990`, `800869CC` and `800869F0`.

## Default program and switching

Actor byte +0x232 supplies the program key when the interpreter encounters a
null cursor: original lookup occurs at `1507BCC0..1507BCCC`. The default setter
writes operand0 to this byte without changing the current cursor.

Switching first replaces zero operand1 with the actor's existing default key,
mutating global operand1. Only afterward does nonzero operand3 replace the
default byte. It calls `1507BB28(0, operand1)`, stores the returned program at
+0x218, then subtracts five to compensate for the interpreter's advance.
The prior [program-table audit](actor_animation_state_helper_semantics.md)
connects this lookup to the bank-0F keyed program table. This handler does not
validate the lookup result or reset timer +0x21C.

## Branches

The unconditional command calls `15075400(operand0)`. Below 0xF7 that helper
advances by operand0*5; otherwise it performs its bounded forward marker search.
The interpreter's separate post-handler increment remains. This is encoded
cursor control rather than an absolute destination address; the helper remains
raw/deferred and is not implemented by this naming batch.

The random command takes that same branch exactly when unsigned `RNG % 100`
is below operand2. Its u8 threshold is unchecked: zero never passes and values
at least 100 always pass. "Percent" describes the modulo-100 comparison, not a
claim of a perfectly uniform distribution.

## Model-selected reset

`1505F0AC` searches active actor records (nonzero word +0) and returns the first
whose model byte +4 equals operand1. The reset handler unconditionally clears
that selected actor's +0x218 cursor, then writes operand0 to its +0x232 default.
It selects one actor, not every actor with the model. There is no null check,
self-exclusion, timer reset or minus-five compensation. If the executing actor
is selected, the interpreter's post-handler advance still applies. These
unchecked contracts and exact store order remain unchanged.

## Spatial MP3 request

The playback command assembles `(operand0 << 8) + operand1` and passes the ID
as u16 to runtime `10012718`, with the current actor and constants 24000, 500
and 2500. Its role follows the [matched main adapter](mp3_adapter_helper_semantics.md).
The existing void declaration and ignored result remain despite the main
implementation's s32 return. No asset, voice, music or character identity is
inferred from the command or its parameters.

## Full-span evidence

All 400 original target bytes in `reference/game/us/asm/75400.s` agree with
the checksum-validated US ROM. The six dispatch slots were independently read
from initialized game data with SHA-1
`42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`. Original interpreter, branch
helper, program lookup and active-model lookup support the contracts above.
Handler registration does not establish runtime activation.
