# US single-precision trig and two-angle perspective objects

Three complete reconstructed objects map `0x47C00:0x48190`: 1,424 text bytes
and four functions. They use the SDK algorithms with Conker-specific floating
point precision, constants, and perspective parameters. Each first candidate
compiled to the complete retail text with IDO `-O2 -g3`.

## Source and behavior evidence

The algorithm reference is pinned `lib/ultralib` revision
`e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`, files `gu/cosf.c`, `gu/sinf.c`,
and `gu/perspective.c`. The authority is the owned US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-code SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, and game-data SHA-1
`42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`.

Unlike the stock double-precision trig algorithms, every operation in these
retail routines uses single precision. Both retain the same exponent tests,
argument reduction, polynomial evaluation, sign handling, and NaN path.
The exact coefficient and scalar bits are recovered from their independently
decoded data references. Several constants differ from simply casting the
stock double coefficients to float; they are preserved explicitly as typed
IEEE-754 union initializers. The NaN reference remains the existing main
`libm_vals` constant at `0x8002C920`.

The perspective routine accepts two field-of-view angles in the third and
fourth argument positions. It computes separate cotangents for the diagonal
X and Y entries, then retains the SDK depth, scale, and normalization logic.
The retail sequence calls cosine and sine twice and reads two half-degree
conversion constants, rather than deriving the X entry from an aspect ratio.
Its source keeps the existing SDK signature types and represents the changed
argument meaning in the implementation. Scoped helper names retain the game
engine's matrix implementations.

## Complete text and relocations

| Member | Game range | Function offsets | Resolved text SHA-1 |
| --- | --- | --- | --- |
| `cosf.o` | `0x47C00:0x47D60` | `0` | `87761a59579c97606776c2f5a86312cd1fc13def` |
| `sinf.o` | `0x47D60:0x47F00` | `0` | `b3d651cd78c74babb47adddbc4a5bbccac743c14` |
| `perspective.o` | `0x47F00:0x48190` | `0`, `0x234` | `fec13647d760b619962a19a639a94d31b2823c9c` |

Each complete relocation-masked section has exactly one game-image occurrence,
including padding. Actual HI16/LO16 and MIPS26 relocations were then applied
using the reviewed symbols and section bases. Each resulting byte array equals
the full retail range, rather than merely matching masked instruction shapes.
The starts and ends are existing raw map boundaries; the next object is the
independently verified rotation object. No work-item records or C source units
occupied these three ranges.

Cosine and sine reference their respective complete sections below and the
main NaN constant only. Perspective calls game `guMtxIdentF=0x150A7BC0`,
cosine `0x15047C00`, sine `0x15047D60`, its own float entry `0x15047F00`,
and game `guMtxF2L=0x150A7790`. The two literal loads resolve to
`0x80098DB0` and `0x80098DB4`. No library instruction is patched.

## Complete non-text sections

| Member/section | Runtime range | Game-data offset | Bytes |
| --- | --- | --- | ---: |
| cosine `.data` | `0x80085EA0:0x80085EB0` | `0x3380` | 16 |
| sine `.data` | `0x80085EB0:0x80085EC0` | `0x3390` | 16 |
| cosine `.rodata` | `0x80098D70:0x80098D90` | `0x16250` | 32 |
| sine `.rodata` | `0x80098D90:0x80098DB0` | `0x16270` | 32 |
| perspective `.rodata` | `0x80098DB0:0x80098DC0` | `0x16290` | 16 |

Both scalar sections contain `3ea2f98440490fdc330885a300000000`.
Both polynomial sections contain
`3f800000be2aaaa63c088769b94fb7fd362edefa000000000000000000000000`.
Perspective's complete section is `3c0efa353c0efa350000000000000000`.
Their bytes equal the preserved RZIP data payload, with relocation targets
selecting the correct copy of each repeated section. Exact-size `NOLOAD`
sections bind those existing allocations without inserting code-image bytes.
There is no BSS or other runtime section to omit.

The reconstruction object MD5s are recorded in `lib/libultrare/object-md5s.txt`:
cosine `22fa88bd212a9a2715b0691f8b2adc32`,
sine `93edd75ae15162f707bae9e8926189e4`,
perspective `3cb6acf4a40bff731765fb9b4bc4b46d`.
They pin independently reviewed output, not an upstream archive checksum.

## Reproducible object metadata

IDO `-g3` embeds build timestamps and the container hostname in `.mdebug`.
The reconstructed objects remove that non-runtime section after compilation,
retaining the code-generation settings. Before normalization, separate builds
differed only in `.mdebug`; all runtime sections, symbols, and relocations
were equal. A forced rebuild after normalization reproduced every pinned MD5.
GNU objcopy canonicalizes section-symbol names but preserves their sections,
values, sizes, and relocation bindings.

## Validation

On 2026-09-02, the complete US ROM passed `./conker build --profile us`
with SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The clean
`./conker game-build --refresh` also passed, preserving all 2,072,880 game-code
bytes and SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
All 151 Python tests passed; generated progress and whitespace checks passed.
The main and game comparison maps retain independent raw assembly.
