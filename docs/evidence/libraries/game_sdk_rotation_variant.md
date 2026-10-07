# US game-overlay rotation variant

The complete range `0x48190:0x48360` (464 bytes, two functions) is the SDK
I/J rotation algorithm compiled with Conker's `-O2 -g3` settings. It links
from the reconstructed `libultrare:rotate.o` rather than being attributed to
an unchanged stock archive. No existing source unit or work item occupied it.

## Evidence

The inputs are the owned US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-code SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`, and independently generated
`reference/game/us/asm/48190.s`. Source algorithms come from pinned
`lib/ultralib` revision `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`,
`src/gu/rotate.c`, selecting the pre-K expressions.

A scan of 986 unique stock text templates of at least 64 bytes, using up to
nine intact instruction windows per template, identified this near-match.
The stock J ROM object differs at 13 instruction words, including argument
setup and return scheduling. Compiling the same algorithm with `-O2 -g3`
reproduces every instruction. This is evidence for different compilation
settings, not proof that Rare changed the rotation mathematics.

The exact object has `guRotateF` at offset `0`, size `0x180`, and `guRotate`
at offset `0x180`, size `0x50`. These match the raw entries `0x15048190` and
`0x15048310`; the entire section ends at the existing next unit, `0x48360`.
Its complete relocation-masked text occurs exactly once in the game image.
Opcode and register bits remain checked in relocated instructions.

| Text relocation | Symbol | Retail target |
| --- | --- | --- |
| `0x24` | `guNormalize` | `0x151EFFF0` |
| `0x2C`, `0x34` | local `.data` | `0x80098DC0` |
| `0x3C` | `__conker_game_sinf` | `0x15047D60` |
| `0x48` | `__conker_game_cosf` | `0x15047C00` |
| `0x98` | `__conker_game_guMtxIdentF` | `0x150A7BC0` |
| `0x1AC` | `guRotateF` | `0x15048190` |
| `0x1B8` | `__conker_game_guMtxF2L` | `0x150A7790` |

The scoped helper names preserve the game-engine bindings without changing
other SDK members' references to their tail copies. They change symbol names
only; the source algorithms and instruction bytes remain intact. The resolved
text SHA-1 is `f20886668a9c616c8d0d14428f600ca79cda9c8a`.

The only allocated runtime section besides text is `.data`, exactly 16 bytes:
`3c8efa35000000000000000000000000`. Those bytes equal game-data offset
`0x162A0`, whose runtime base is `0x80082B20`. The complete extracted data
payload SHA-1 is `42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`. A `NOLOAD`
section binds all 16 bytes at `0x80098DC0`, leaving their original RZIP payload
intact. There is no BSS or rodata section to discard. The object MD5
`e08a8c3f1ea1282f5cd4dfae5d6f749a` is recorded as a Conker reconstruction
checksum, with the retail comparison providing independent match evidence.

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
