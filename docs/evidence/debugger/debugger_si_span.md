# Debugger SI DMA registered-span composition

The US work item `func_160019A8` retains its registered `0xC4` bytes at
`0x160019A8..0x16001A6C`. The independent raw reference is recovered from the checksum-validated US
debugger image; the focused workflow retains it locally as
`build/m2c/debugger/func_160019A8.s`. Its DMA wrapper
returns at `0x16001A5C`, with a nop at `0x16001A60`; the final eight bytes are
another `jr $ra; nop` at `0x16001A64..0x16001A6C` (ROM `0x1A04EC..0x1A04F4`).
Both return pairs are `03E00008 00000000`. This is a registered comparison span,
not evidence that these bodies formed one original function or object.

Representing the last return as adjacent C `void func_16001A64(void) {}` is intended to emit
its own eight-byte function symbol. The existing analogous C empty functions
`func_16000304` and `func_1600030C` follow `func_16000224`, whose ordinary
full-span comparison includes all three symbols. The existing compiler object
records these empty C bodies as global STT_FUNC symbols, size 8, in executable
PROGBITS text. This establishes the source representation; it does not by itself
establish a match for `func_160019A8`.

The linked-alias verifier permits this one explicit composition only when called
for the debugger overlay, canonical start `0x160019A8`, and unchanged size `0xC4`.
The primary must have extent `0xBC`, followed without gaps by the uniquely named
`func_16001A64` of extent 8 in the same executable text section. Both must be global
function symbols with default visibility. The local, default-visible `.text`
section symbol at offset zero may describe either zero bytes or the complete
section: IDO emits this coverage metadata alongside the function symbols.
Shifted, partial, globally bound, or hidden section metadata is rejected.
Additional overlapping sized symbols,
function entries within the span, tail relocations, truncated text, or incorrect
return bytes reject the composition. Other extent mismatches remain rejected.
No bytes, symbol extents, source instructions, registrations, or ROM data are
rewritten to establish that coverage.

Coverage only permits the existing proof to run: validate every raw instruction
against the checksum-approved ROM, link the raw reference and candidate naturally
at the canonical address, and require all `0xC4` bytes to agree independently.
Comparison objects are produced only after both complete equality checks. The
empty body must remain part of the comparison; separately registering it would
shorten the current workflow's effective span and is not this recovery path.

## Debugger address aliases and defined calls

`func_160018BC` names the PIF-buffer end as `D_80042A50` in raw assembly; a typed
C array may emit the equivalent relocation `D_80042A10 + 0x40`. Its primary span
is `0xC8` bytes. The debugger alias path now uses the same conservative natural-call
validation as the previously reviewed SI literal path. This permits unrelated
same-object calls in compacted candidate prefixes without assigning new addresses
to their definitions. Defined calls inside the compared span must already resolve
to the canonical address encoded in their symbol name, with zero JAL addend.
Unsupported defined-data relocations, non-JAL calls, ambiguous names and wrong
natural target addresses remain rejected. The game-overlay alias path is unchanged.
A wrong end addend, register or final word still fails complete linked-byte equality.

This evidence introduces no source-unit ownership claim, compiler option change,
assembly change, smaller comparison range, or automatic match status. Live focused
verification, layout/progress/whitespace gates and clean US batch verification
remain required for each recovered C candidate.

## Validation

The approved implementation passed independent full-span `CURRENT (0)` for
`func_160018BC` and `func_160019A8`, with `func_16001984` rechecked. Clean US
`verify-batch` completed successfully: full-ROM equality, the 208-byte formatter
table check, layout, progress, and whitespace gates passed. The batch ran 1669
tests with 12 expected skips. All 28 linked-alias tests also passed in the pinned
toolchain container, including the actual IDO section-symbol metadata regression.
Task receipts are in
`build/us/manual-attempts/debugger-20261002/batch-8.log` and
`verified-batch-8.json`; generated receipts are local verification artifacts.
