# Explicit US return-only callback symbols

Evidence type: `structural_analysis`

Sixteen eight-byte routines are explicit targets of real retail callback tables,
but the code-only reference disassembly previously kept their `jr $ra; nop`
words attached to the preceding function. The beta discovery index split them
as separate candidate functions. This note reconciles that disagreement using
the owned retail data and callers, without hand-editing generated assembly.

`config/symbols/game-us.txt` declares only these independently referenced
function entry addresses and their eight-byte sizes. The symbol list is read
by both the raw comparison map and the canonical integration map. The build
preparation dependency includes the symbol file so changes invalidate the
integrated split. Source names remain generic address-based identifiers.

## Runtime table evidence

- At game offsets `0x40B04:0x40B1C`, the dispatcher multiplies a byte index
  by four, loads through `800844B0`, then executes `jalr`. Its second slot
  `800844B4` points to `150407A0`.
- At `0x5E39C:0x5E3B4`, a halfword index selects a member of the table at
  `8008630C`, storing the callback into a runtime descriptor. The entries
  below point to twelve distinct return-only handlers among the neighboring
  nontrivial functions in `0x6AD30:0x75400`.
- `func_1507BC14` dispatches bytecode through `80086730`. At
  `0x7BD04:0x7BD70`, it reads a byte opcode, handles opcodes below `0xF7`
  with four following operand bytes in `800D1890:800D1893`, indexes the
  handler table, calls it via `jalr` at `0x7BD60`, and advances the stream
  pointer by five bytes. The table references the three return-only entries
  in `0x75400:0x7BDB0` listed below.

All table words were read directly from the owned US initialized game data
(base `80082B20`, SHA-1 `42bbe7f02702ca7af5da499fb5cf2f34b7d3d23b`).
Each function body was independently checked as the exact bytes
`03 E0 00 08 00 00 00 00` in the US game image (SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`). None of these functions has
a direct J/JAL caller in the scanned game code; the table references explain
why code-only discovery missed their identities.

| Entry symbol | Game offset | Verified table slot addresses |
| --- | --- | --- |
| `func_150407A0` | `0x407A0` | `0x800844B4` |
| `func_1506B070` | `0x6B070` | `0x80086320` |
| `func_1506B368` | `0x6B368` | `0x80086348` |
| `func_1506B3B0` | `0x6B3B0` | `0x80086380` |
| `func_1506B5A4` | `0x6B5A4` | `0x80086358` |
| `func_1506B5AC` | `0x6B5AC` | `0x8008635C` |
| `func_1506D4EC` | `0x6D4EC` | `0x8008643C` |
| `func_1506D950` | `0x6D950` | `0x8008630C`, `0x80086328`, `0x80086370`, `0x80086374`, `0x80086378`, `0x800863FC`, `0x80086438`, `0x80086450`, `0x80086468` |
| `func_1506DCF8` | `0x6DCF8` | `0x800864B0` |
| `func_1506DDB8` | `0x6DDB8` | `0x800864C4` |
| `func_1507304C` | `0x7304C` | `0x800865DC` |
| `func_15073C48` | `0x73C48` | `0x800863D4` |
| `func_15073F54` | `0x73F54` | `0x800863E0` |
| `func_15076600` | `0x76600` | `0x80086824` |
| `func_15076E48` | `0x76E48` | `0x800868F4` |
| `func_1507735C` | `0x7735C` | `0x80086730`, `0x8008693C`, `0x8008694C`, `0x80086950`, `0x80086954`, `0x8008695C` |

## Limits and validation

Identical bytes alone do not identify a callback or library object. The seven
other return-only candidates without a direct game-data pointer are not
promoted by this symbol change: `150045BC`, `15040A4C`, `15073070`,
`1507DB34`, `1507DB3C`, `1507DB64`, and `1513E134`. Their bytes remain
inside the existing raw spans until stronger entry-point evidence is available.
No SDK ownership, C implementation or historical function name is inferred.

Regenerate the ROM-derived comparison assembly using `./conker game-asm
--profile us`. Verify that exactly these sixteen top-level function labels are
added and that every range retains its original bytes. Register their owning
source groups separately after reviewing the full boundaries, then require a
byte-identical complete US overlay integration. This note records function
identity evidence; it does not on its own claim a source-unit boundary.

The regenerated raw comparison adds exactly the sixteen listed function names,
removes no existing function name, and preserves the instruction words. The
subsequent four-group integration passes on its first attempt with a complete
US overlay SHA-1 of `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. All sixteen
entries are registered as raw ASM within their reviewed source groups. All 170
Python tests, progress generation and whitespace checks pass.
