# US retail debugger overlay

The debugger occupies ROM `[0x19EA88, 0x1A33E8)`, loads at `0x16000000`,
and enters at `0x16000B14`. Evidence comes from the owned US ROM and local
reviewed library code; external screenshots were discovery leads only.

- US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`
- Debugger image SHA-1: `6298456bc25ca48e90fcdda6ca3878dd888cc631`

## Mapping decisions

All range ends are exclusive. The two C collections contain individually
verified C functions and preserved deferred candidates with active `GLOBAL_ASM`
bodies. Their grouping is provisional, not recovered original source ownership.

| Region | US ROM range | Virtual range |
| --- | --- | --- |
| [28 debugger/UI functions](../../src/debugger/debugger_0000.c) | `0x19EA88–0x1A0558` | `0x16000000–0x16001AD0` |
| [10 library helpers](../../src/debugger/debugger_1AD0.c) | `0x1A0558–0x1A20D8` | `0x16001AD0–0x16003650` |
| Raw TLB capture and alignment | `0x1A20D8–0x1A2178` | `0x16003650–0x160036F0` |
| Raw loaded data | `0x1A2178–0x1A33E8` | `0x160036F0–0x16004960` |

Loader instructions at ROM `0x7F20–0x7F40` form both ROM endpoints and DMA
`0x4960` bytes. JAL `0x0D8002C5` at `0x8070` targets `0x16000B14` through
main's `0x1000xxxx` runtime alias; the static `0x8000xxxx` view mislabels it
`0x86000B14`. Preserve the debugger's encoded external call aliases.

The TLB routine returns at `0x160036E0`, followed by its delay slot and eight
alignment bytes. Data begins with writable controller storage, passed at
`0x16000E24` and read at `0x16000E40/44`. Four six-byte slots are supported
by main's count initialization at ROM `0x25498/0x254A0` and the debugger's
six-byte stride at `0x160018B0`. `align: 8` preserves the image endpoints.

Keep privileged TLB instructions and loaded data in raw assembly. The
independent reference remains wholly raw. The matching workflow now supports
individual debugger registration and explicitly reviewed debugger source units;
see the [workflow](../decompilation-workflow.md#source-unit-boundaries-and-integration).
The two provisional collections have not been registered or marked reviewed
as source units, so neither receives completed source-unit credit. Individual
function matches are counted separately: all 28 debugger/UI spans and
all 10 library-helper spans have full-span US `CURRENT (0)` and clean batch
verification. Both C collections contain no remaining `GLOBAL_ASM` bodies.
The 14,064-byte code interval is included as a separate US progress area;
no EU/PAL interval is inferred.

## Supporting evidence

The [data access map](us_debugger_data_objects.json) records all 4,720 loaded
data bytes across 65 ranges, 117 symbolic references, and 109 string payloads.
It includes hashes, access widths, consumers, and explicit unknown intervals.
Scalar footprints and NUL terminators do not establish original allocations.

Five formatter bodies match reviewed main code after address substitutions:

| Debugger virtual range | Identity |
| --- | --- |
| `0x16001BB4–0x160021FC` | `_Printf` |
| `0x160021FC–0x1600288C` | `_Putfld` |
| `0x1600288C–0x16002D2C` | `_Ldtob` |
| `0x16002D2C–0x16002DE4` | `_Ldunscale` |
| `0x16002DE4–0x160033A8` | `_Genld` |

All 1,533 words' differences are relocated calls or data addresses. `_Litob`
at `0x160033A8` additionally shares a 600-byte tail apart from one relocated
call; its prologue differs. Existing complete library objects cannot be
imported: their member order, alignment, or trailing padding conflicts with
the debugger layout. For example, `xprintf.o` padding would overlap `_Ldtob`.
See [main formatter provenance](libultrare_us_xprintf_reconstruction.md).

## Matched helper names

The ten matched library helpers use source-local aliases, retaining numeric
linked symbols, calling conventions, data layouts and operations. These are
descriptive names, not claims of original debugger symbols or source ownership.

| Symbol | C name | Behavior boundary |
| --- | --- | --- |
| `16001AD0` | `debugger_copy_bytes` | Forward byte copy; returns the original destination, without overlap handling |
| `16001B00` | `debugger_string_length` | Byte count before NUL; no null-pointer handling |
| `16001B34` | `debugger_sprintf` | Variadic formatting and termination on a nonnegative result; no capacity argument |
| `16001B8C` | `debugger_append_bytes` | Copy callback returning destination plus count; no allocation |
| `16001BB4` | `debugger_vformat_to_callback` | Parses format state and emits chunks through the supplied callback |
| `160021FC` | `debugger_format_field` | Consumes the selected vararg and prepares field/padding segments, including `%n` writes |
| `1600288C` | `debugger_format_f64` | Finite decimal conversion plus existing NaN/Inf handling |
| `16002D2C` | `debugger_unscale_f64` | Existing exponent classification/adjustment, not general `frexp` or subnormal normalization |
| `16002DE4` | `debugger_format_decimal_digits` | Fixed/exponent arrangement of supplied significant digits and padding |
| `160033A8` | `debugger_format_integer_digits` | Octal/decimal/hexadecimal digits with existing signedness and precision rules |

Raw calls at `16001020/16001278` use the variadic wrapper with the loaded
`%s%s%f` format. It passes the append callback to `16001BB4` at `16001B5C`;
field conversion is called at `16001E8C`. The field path calls string length
at `16002818`, integer formatting at `16002418/1600256C/160027EC`, and floating
formatting at `160026D4`. Floating conversion calls exponent adjustment at
`16002914` and decimal arrangement at `16002CFC`. The loaded data map and
reviewed SDK comparisons above independently support these roles. The callback
formatter includes the terminating NUL in its final literal chunk; callback
failure returns the accumulated count. No standard-library conformance claim
is added by these names.

`16002D2C` returns -1 for normal encodings, stores their old characteristic
minus `0x3FE`, and changes exponent bits to `0x3FF`. It returns one for infinity,
two for NaN, and zero for zero-exponent encodings. Its big-endian halfword
accesses and original subnormal treatment are preserved. All registered spans
remain complete, including the eight final padding bytes after `160033A8`'s
return sequence.

The alias parser uses a logical line-spliced view with original source offsets.
It permits unrelated continued macros but still rejects continued, conditional,
repeated, undefined or chained aliases and physically split alias uses. The
existing `ATOI`, `PAD` and `PUT` macros remain byte-for-byte unchanged; complete
preprocessing output is identical before and after naming. This does not add
general macro expansion or claim runtime debugger execution.

## Unresolved boundaries

- Mutable state and constants interleave; no original `.data`/`.rodata` split
  or additional C-file boundary is established. Three video-coefficient blocks
  match main data, but their surrounding records are not proven `OSViMode[3]`.
- Initial SP is backing base plus `0x5958`; entry stores through `+0x595C`.
  Neither SP nor the 128 KiB TLB mapping proves BSS or stack ownership.
- ROM `[0x1A33E8, 0x1A37E0)` lies outside the DMA and contains structured
  records. Keep it in the following bin; it is not debugger padding.
- Live debugger entry/resumption remains unverified. Loader gating uses
  `0x800E9D00 & 0x2000`; byte `0x8002AAE0` is checked on the fault path.
  Diagnostic pointer order does not establish an error-ID mapping.

## Validation

The initial scaffold validation on 2026-10-02 reproduced the complete US ROM
with `./conker build --all`. All 94
relevant tests, progress, and whitespace checks passed. The 3,516 scaffold/TLB
words equal the independent raw reference; all data-map hashes and ranges
were checked against the ROM. Main discovery remains 542 functions, ending
at `0x292F0`. These checks validate packaging, not original source boundaries.

Detailed local audits and the data-map regenerator remain under
`build/research/debugger-overlay-map/boundary-followup/` (ignored research
outputs). This note and the JSON retain the reviewable boundary evidence.
