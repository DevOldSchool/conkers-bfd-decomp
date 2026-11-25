# US native angle lookup tables

This batch reconstructs 772 bytes in two source-compatible definitions:

| Address | Definition | Payload | Excluded compiler tail |
| --- | --- | ---: | ---: |
| `8009A220` | `f32 D_8009A220[65]` | 260 | 12 |
| `80098E00` | `u16 D_80098E00[256]` | 512 | 0 |

Both existing declarations are unsized arrays of the same element type. No
function body, shared header, assembly, or function/source-unit inventory changes
are needed. These are INFO verification definitions; the original GAME archive
continues to provide runtime storage. No original source-object boundary or
runtime immutability is inferred.

## Quarter-wave table

The full registered native spans of `150489B0` (144 bytes) and `151423D8`
(108 bytes) match the original ROM instruction for instruction. An independent
bounded interpreter executes their original instructions, including branch delay
slots, for every input from zero through 255. Both mask the input to one byte.
All 512 executions perform exactly one single-precision table read, and each
consumer's exact read-index set is zero through 64. This establishes the 65
represented floats without using the next symbol's address as an extent.

The consumers have two deliberately retained output differences: at input 64,
the first returns positive zero and the second negative zero; at input 192 the
signs are reversed. Their nonzero outputs agree. The initial hypothesis that
every result bit pattern agreed was rejected; no function is replaced or changed
on the basis of that hypothesis.

## Unsigned inverse-angle table

The complete 132-byte native span of `150487E0` is authenticated against the
original ROM. Its straight-line prefix loads the original scale at `80099000`,
takes the absolute value of the input, multiplies in single precision, truncates
to an integer, doubles that index, and reads `D_80098E00[index]` with `LHU`.

For each index `i` from zero through 255, `(2*i + 1)/512` is an exactly
representable single-precision input. Integer/rational IEEE rounding of the
native multiplication, followed by native truncation, selects index `i` in
each of the four rounding modes. All 1,024 instruction-prefix executions read
the expected original unsigned halfword. All 256 elements are therefore
proven, and they fill the storage up to the next object. This does not
establish a whole-program input bound or gameplay reachability of each input.
Only the read prefix is executed; the full registered function is authenticated
separately. No function-match claim is made from this bounded execution.

## Validation

Tested base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted
work. Both pinned-compiler pilots pass unchanged extent/padding checks and their
independent full-GAME references reproduce the original image. Native comparisons
match 260/260 and 512/512 bytes. All 772 individual byte corruptions are rejected.
The integrated GAME build passes. All 1,938 prior GAME objects preserve their
allocated bytes, symbols and relocations; the complete 2,072,880-byte GAME code
image is unchanged. Actual linked candidates match all 772 bytes and reject
772 native-byte and 772 independent ROM-byte mutations.

The regression suite passes 3,038 tests with eight skips. The asset build passes,
and independent extraction reproduces the entire original 67,108,864-byte ROM.
Progress and whitespace checks pass. The full report audit preserves all 27,323
previous asset source hashes and 11,847 asset object hashes. Every other report
unit retains its measures; the two previous unmatched ranges are partitioned
without overlap, with exactly 772 bytes moved into matching C owners.

The accepted report credits 63,342,677 / 65,120,512 data bytes, leaving 1,777,835.
Complete-data and code/function measures are unchanged. Report SHA-256:
`668210b18180ec703fae6959861c196965f6c813d44a485d018b4df7d8d3fa26`.
