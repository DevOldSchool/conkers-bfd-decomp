# US debugger source-unit boundaries

Evidence type: `structural_analysis`

This record reviews the two existing debugger C collections as original object
boundaries. It uses only the checksum-validated US ROM (SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`), the reviewed
[overlay map](us_debugger_overlay.md) and the
[data access map](us_debugger_data_objects.json). No symbol name, type or C
body was imported.

| Source unit | US ROM range | Virtual range | Members |
| --- | --- | --- | --- |
| [debugger_0000.c](../../../src/done/debugger/debugger_0000.c) | `0x19EA88:0x1A0558` | `0x16000000:0x16001AD0` | 28 |
| [debugger_1AD0.c](../../../src/done/debugger/debugger_1AD0.c) | `0x1A0558:0x1A20D8` | `0x16001AD0:0x16003650` | 10 |

## Text padding

Every registered debugger span ends in `jr $ra` plus its delay slot, except
two. `func_16001AB0` carries two extra zero words (`0x16001AC8:0x16001AD0`),
and `func_160033A8` carries two extra zero words before `0x16003650`. These are
the only alignment gaps in the 13,904-byte C interval. They fit IDO's 16-byte
`.text` alignment, closing an object at `0x16001AD0` and at `0x16003650`, where
the raw TLB routine starts.

Every other function begins immediately after its predecessor's delay slot.
A start that is not 16-byte aligned cannot begin a separately aligned object, so
these ranges each stay in one object:

- `0x16000000:0x16001AD0`. Only `0x0590`, `0x12B0`, `0x1390`, `0x14F0`,
  `0x1700`, `0x1830` and `0x1AB0` remain as candidate starts.
- `0x16001B00:0x16003650`. This includes sprintf, `_Printf`, `_Putfld`,
  `_Ldtob`, `_Ldunscale`, `_Genld` and `_Litob`. Main's separately padded
  library objects place these bodies in different objects; the debugger does
  not. Only `0x16001B00` remains as a candidate split, separating the 48-byte
  memcpy body from strlen.

## Data and read-only ordering

The loaded data follows the same two-object link order. Section ranges below
come from the consumers recorded in the data map:

| Virtual range | Consumers | Interpretation |
| --- | --- | --- |
| `0x160036F0:0x16003C70` | `debugger_0000` and the TLB capture | first object's `.data` |
| `0x16003C70:0x16003CE0` | `debugger_1AD0` only | second object's `.data` |
| `0x16003CE0:0x160047F5` | `debugger_0000` only | first object's read-only data, padded to `0x16004800` |
| `0x16004800:0x16004960` | `debugger_1AD0` only | second object's read-only data |

No range in either block is referenced from the other collection. A split at
`0x0590`, `0x12B0`, `0x1390` or `0x14F0` would put later-file data ahead of
earlier-file data in the first `.data` block. Examples are the drawing color
halfword at `0x1600388C` ahead of the controller button word at `0x16003890`,
and the glyph bitmaps at `0x16003CE0` ahead of the string pool at `0x16003FE0`.
Those splits are therefore rejected.

## Residual alternatives

Three aligned candidates in the first range use no debugger-local data, so data
order cannot test them: `0x1700`, `0x1830` and `0x1AB0`. Against `0x1700`,
`func_16001700` is the only caller of the 12-byte identity helper at
`0x160016F4`. `0x1830` and `0x1AB0` begin the controller-read and trailing
empty-stub tails, and no positive evidence separates them. In the second range,
`0x1B00` stays unsupported because memcpy and strlen use no data. Treat any
later evidence for one of these splits as grounds to re-register narrower units.

## Scope

This adopted the existing exact C mappings; both units are integrated under
`src/done/debugger/`. The raw TLB routine
(`0x16003650:0x160036F0`) and all loaded data stay raw. The
[Putfld table mapping](debugger_printf_rodata.md) and the
[SI span composition](debugger_si_span.md) are unchanged. No compiler option,
assembly, linker script or shared header changes.
