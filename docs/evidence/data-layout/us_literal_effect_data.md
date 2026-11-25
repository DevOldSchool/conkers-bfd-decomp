# US literal effect textures and callbacks

This batch reconstructs 152 bytes in five C owners. All are INFO verification
definitions; the original GAME archive still supplies runtime storage. The
grouping expresses proven contiguous storage without claiming Rare's original
C-object boundaries.

| Native range | Source content | Bytes |
| --- | --- | ---: |
| `8008CB64..8008CB70` | Three initializer callbacks | 12 |
| `800903B8..800903C8` | One frame word and its texture descriptor | 16 |
| `800903E0..80090400` | Five frame words and their descriptor | 32 |
| `80090558..800905A8` | Five frame-word/descriptor pairs | 80 |
| `80091840..8009184C` | One scalar-resource descriptor | 12 |

## Native extent and field evidence

The complete 84-byte `1516706C` initializes its loop pointers to `8008CB64` and
`8008CB70`, loads a callback word, conditionally calls it, and advances by four.
The original instructions were executed for all eight null/non-null masks;
every case reads exactly the three slots. The three original destinations are
`15164EE4`, `1515C158` and `151787A4`. Their existing definitions take no
arguments and return void. The last is a registered eight-byte empty function,
whose original instructions are `jr ra; nop`. Its explicit `type:func size:0x8`
annotation prevents the data reference from misclassifying it as a scalar.
The loop proof assumes the existing ABI's preservation of s0/s1 by callees.

The complete `151668B8` reads a signed phase, increments it by `0x80`, resets
the updated value at `0x500`, and passes the previous phase with descriptor
`800903F4` to `15094F70`. Execution of the original instructions for all 1,280
normal phases proves a closed domain selecting frames zero through four.
The five words at `800903E0` select resources 2320 through 2324. Negative or
corrupt phase states and gameplay activation are outside this bounded proof.

Six other native call paths explicitly pass phase zero: `15036BD0` selects
descriptor `800903BC`; the checked paths in `1516B6BC` select `8009055C`,
`8009056C`, `8009057C`, `8009058C` and `8009059C`. Constant register propagation
over the original instructions verifies the descriptor and phase arguments,
including branch delay slots and transfers from coprocessor registers. The
branch choices are declared native paths, not observed gameplay activation.
Each descriptor points to its preceding four-byte frame word.

`15090630` establishes `80091840` in callee-saved fp, does not overwrite fp
before the checked call, and passes it with phase zero at `15090890`. This
descriptor's first word is scalar resource 1205, not a pointer. Intervening
calls preserve fp under the existing ABI.

The complete shared consumers `15094F70`, `15095060` and `150950D4` establish
the descriptor's resource/pointer word, stored count, dimensions and image
format fields. The wrapper forwards the phase; the frame selector shifts it
right by eight. Descriptor byte `+5` is natural zero alignment. All complete
registered native spans are authenticated against the original ROM.

The `D_80090558` reference annotation specifies word storage. Without it, an
interior native halfword field read makes the disassembler emit the entire
mixed record block as halfwords, losing all five genuine pointer relocations.
This annotation controls reference emission; the C structures retain the
original byte and halfword fields and actual pointer types. Resource words
and packed scalar fields remain scalar.

## Accepted validation

Tested base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus the
uncommitted batch. The dedicated GAME build and independent native comparison
verify all 152 bytes and ten real pointer destinations. Eight compiler-tail
bytes remain excluded. All 870 prior GAME objects retain identical allocated
bytes, symbols and relocations; the complete 2,072,880-byte GAME code image
matches the original.

All 172 byte/pointer/addend corruption cases and 152 independent ROM-byte
mutations are rejected. The full suite passes 3,038 tests with eight skips.
The asset build passes, and independent extraction reproduces the complete
67,108,864-byte US ROM exactly. Progress and whitespace checks pass.

The full report credits **63,332,733 / 65,120,512 data bytes**, an increase of
152, leaving 1,787,779 unmatched. Complete data remains 63,251,041 because these
owners are verification definitions. All 27,323 prior editable asset input
hashes and 11,847 asset object hashes are preserved.

The callback annotation also corrects a reference boundary in the unchanged
`game_1A5C00.c` unit. Previously, the reference combined `15178750` and the
empty `151787A4` callback into one 92-byte function. It now recognizes the
existing 84-byte and eight-byte C symbols separately. Both match exactly,
correcting code accounting by 92 bytes and two matches, with one additional
reported function. This is not new C implementation. The existing function
inventory retains its overlapping 92-byte/eight-byte registrations; the audit
checks the entire 92-byte registered span against the ROM rather than shortening
the verification. Function/source-unit inventories are unchanged.

The accepted report SHA-256 is
`053c98f867b3979cb4e4149523baeffff180ece0108e64fbd3dac0c551ede07d`.
The adjacent JSON records the native evidence, exact changes to accounting,
input preservation, validation results and source fingerprint.
