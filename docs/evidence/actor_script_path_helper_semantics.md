# Actor-script path-point commands

Eight existing matched C handlers in `game_A28B0.c` use source-local aliases.
Numeric linked symbols, void(void) signatures, padded state views, operand
globals and operations remain unchanged.

| Symbol | C name | Opcode | Span |
| --- | --- | --- | --- |
| `15075A50` | `actor_script_branch_on_path_point_index` | `0x93` | `0x5C` |
| `15077DA0` | `actor_script_set_path_point_index` | `0x96` | `0x1C` |
| `15077DBC` | `actor_script_snap_to_path_point` | `0x99` | `0xE0` |
| `150781F4` | `actor_script_branch_on_path_point_xz_distance` | `0xA1` | `0xD8` |
| `150798F8` | `actor_script_branch_on_current_path_point_xz_distance` | `0xB6` | `0x30` |
| `1507A100` | `actor_script_set_path_point_component` | `0xC5` | `0x64` |
| `1507A528` | `actor_script_update_path_point_step` | `0x86` | `0xF8` |
| `1507ACB0` | `actor_script_set_path_point_range` | `0x1C` | `0x30` |

## Interpreter and path-state contracts

Interpreter `1507BC14` loads four operand bytes into `D_800D1890..1893` at
`1507BD20..1507BD48`, indexes the handler table at `80086730`, dispatches at
`1507BD60` and advances actor script cursor +0x218 by five. The opcode slots
above contain these exact handler addresses in checksum-validated US data.

Actor byte +0x13F selects `D_800D2104`'s point table. Each selected point has
four halfword slots, with record zero reserved: point index i begins at
`table + 8 + i*8`. Signed XYZ occupy the first three halfwords; the fourth is a point
attribute. No general path-origin interpretation is assigned to record zero,
which also serves as a radius-center control record elsewhere.

Original movement consumer `15056B08` at `15057EA4..15057FEC` independently
establishes actor +0x21E as the current point index, +0x220 as the minimum,
+0x21F as an exclusive-limit override and +0x221 as a signed step. A zero
limit override selects the table count minus one. These byte fields and their
existing padded C representation are retained.

## Indexing, position and component writes

The index setter copies operand0 directly to +0x21E. Snap updates that index
unless operand0 is 0xFA, then converts the selected point's signed XYZ directly
to actor float position +0x14/+0x18/+0x1C. It adds no origin, offset or
interpolation, and performs no table/index validation.

The component setter assembles a signed 16-bit value from operand2/operand3
and writes it at `table + 8 + operand0*8 + operand1*2`. Its selector is unchecked.
"Component" includes the fourth halfword; "coordinate" would incorrectly
restrict the established record contract. Existing sign extension, shifts and
narrowing remain unchanged.

## Conditional cursor changes

The point-index branch compares +0x21E with operand1. Operand2=0 selects
equality, operand2=1 selects inequality, and other values do nothing.

The distance branch selects point operand1 and computes `sqrt(dx*dx + dz*dz)`
against actor X/Z. Operand3*8 is the threshold. Operand2=0 selects strict less
than; any nonzero value selects strict greater than. Equal distances do not
branch. Its current-point wrapper first overwrites global operand1 with
+0x21E, then calls this same handler at `15079910`; that global write is retained.

Successful tests call still-raw `15075400(operand0)`. It implements encoded
command skipping below 0xF7 and bounded marker searching otherwise. These
handlers do not supply absolute program addresses. The helper's deferred body
and the interpreter are supporting evidence, not newly completed functions.

## Step and range controls

The range setter writes operand0 to minimum +0x220 and operand1 to limit
+0x21F. It neither clamps nor moves the current index.

The step updater's mode0 stores operand1 at +0x221; mode1 negates that signed
byte. Mode2 negates it, advances the current index by the resulting signed step,
then adds operand3 for a positive step or subtracts operand3 otherwise. It
wraps once using operand2 when nonzero, otherwise the selected table count minus
one. This mode does not use the actor's minimum/limit override fields. Other
modes do nothing. Byte narrowing, zero/invalid ranges and single-wrap behavior
are preserved; this is not unrestricted modulo or a validated path iterator.

## Full-span evidence

All eight original spans are in `reference/game/us/asm/75400.s`, totaling
1,004 bytes. Dispatch slots are `8008697C`, `80086988`, `80086994`, `800869B4`,
`80086A08`, `80086A44`, `80086948` and `800867A0` in table order above. The
checksum-validated initialized game data has SHA-1
`42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`. Full registered CURRENT (0),
existing source-unit layout and complete-image equality gate these names.
Static handler registration does not establish gameplay activation or a
character, scene or specific route identity.
