# Actor-script position and distance commands

Source: `game_A28B0.c`. Handlers retain void(void) signatures and global
operands. Interpreter registration proves availability, not gameplay
activation.

| Symbol | C name | Opcode | Span |
| --- | --- | --- | --- |
| `1507659C` | `actor_script_adjust_position_y` | `0x36` | `0x64` |
| `150779D4` | `actor_script_branch_on_filtered_pool_actor_xz_distance` | `0x6A` | `0xCC` |
| `15078074` | `actor_script_branch_on_any_active_pool_actor_xz_distance` | `0x9E` | `0xC8` |
| `1507839C` | `actor_script_branch_on_selected_actor_distance` | `0xA6` | `0x184` |
| `150793D8` | `actor_script_randomize_bounded_path_point_xz` | `0xB4` | `0x198` |

The shared operand0..3 and encoded branch conventions are documented in the
[path](actor_script_path_helper_semantics.md) and
[program-control](actor_script_control_helper_semantics.md) audits. Successful
conditions call `15075400(operand0)`; the interpreter retains its subsequent
five-byte cursor advance. None supplies an absolute program address.

## Y adjustment

The handler first adds unsigned operand0*100 to actor float Y at +0x18.
If operand3 is nonzero, it then overwrites Y with 1800.0. Operands1/2 are unused.
Both stores and their order remain, including the absolute override; no scene
or movement-mode identity is inferred from that numeric height.

## Three distinct distance predicates

All pool addresses use base `800CC2D0` and stride 0x32C. The
[matched distance helpers](actor_geometry_helper_semantics.md) confirm actor-base
position fields and Euclidean XZ/XYZ metrics. The predicates differ materially:

- Filtered: operand2=0 selects pool index zero; otherwise it selects executing
  actor byte +0x222. The handler excludes the index stored at `800C3E78` and also excludes
  a selected record whose word +0 equals 1 and byte +0x65 is nonzero. It does
  not require a nonzero state word. Passing records branch on strict XZ
  distance < operand3*8. Operand1 is unused; 0xFF has no special threshold role
- Any active: scans exactly 25 slots, indices 0..24. It requires nonzero word
  +0 and index different from that same excluded-index global. The first slot with strict XZ distance
  < operand3*8 causes a branch and return. Operands1/2 are unused. "Active"
  means that exact nonzero-word predicate, without visibility or relationship
  checks
- Selected: actor byte +0x222 selects the pool slot. Operand2=0 measures XZ,
  operand2=1 measures XYZ, and all other values measure absolute Y difference.
  Threshold is operand3*8, except 0xFF substitutes actor byte +0x23D times
  eight. Operand1=0 tests strict less-than, operand1=1 tests strict greater-than,
  and other comparison modes do not branch. Equality does not branch. There
  are no active-state, self-selection or pool-index checks

The filtered predicate's numeric guards are retained without assigning an
ownership/player meaning to the state-word/byte-0x65 combination. Likewise,
slot zero and the excluded-index global do not identify a character here.

## Bounded path-point XZ randomization

Only operand0 is used, as the destination point index. Base X/Z come from pool
actor zero, first truncated from float to integer and narrowed to signed 16 bits.
If either narrowed coordinate is outside inclusive [-1180,1180], both bases
become numeric zero. This fallback is not evidence of a universal world origin.

The low 16 RNG bits become the angle for `1505A184`, supplied with scalar
550.0 and third argument 0.0. That helper halves the scalar before trig
projection: the nominal unclamped XZ offset magnitude is 275, subject to its
original float approximation, not a 550-unit radius. Returned X/Z offsets are
added to the base; results are again truncated and narrowed, then independently
clamped to [-1200,1200]. There is no uniform-randomness or finite-value guarantee.

Stores affect only X at `table + 8 + operand0*8` and Z at
`table + 12 + operand0*8` in the executing actor's selected path table. Point Y,
the fourth halfword and current point index are unchanged. No point-index
validation or geometric suitability test is added.

## Original evidence and acceptance

All 1,300 registered target bytes in `reference/game/us/asm/75400.s` agree
with the checksum-validated US game image. Original dispatch slots at
`80086808`, `800868D8`, `800869A8`, `800869C8` and `80086A00` contain these
handlers in table order above. Initialized game-data SHA-1 is
`42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`.

Original `55E50.s` contains the distance and offset callees; `AD780.s`
supplies the trig entries. The offset helper's constants establish
approximately pi/180 and 2pi/65536. Raw callees retain their status.
