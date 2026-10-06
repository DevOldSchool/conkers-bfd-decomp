# US actor command dispatcher table

`func_15033FE0` manually matches its full 476-byte raw span. Existing command
helpers establish the command-pointer and actor-index call contracts. The
source-local actor retains its 812-byte stride and names only observed fields.
Using the actor type directly in the switch, rather than an extra byte local,
recovered the original argument-register lifetime. Ordering the used actor,
result and command locals recovered the final result's SP+0x20 spill. Scores
were 2243, 8 and 0; a transient declaration edit error was fixed separately.

The full integrated object emits 37 table relocations for selectors 0x74–0x98.
The candidate-table verifier independently proved all targets against the
checksum-validated owned ROM. The original table starts at 0x80097C80. Its
148-byte payload is followed by 12 zero object-alignment bytes, giving an exact
0xA0 object extent. Before mapping, the integrated image was 160 bytes too long
and only the table-address words at 0x1503408C and 0x15034094 differed in the
original code extent. The informational linker section selects only this
object's `.rodata`, with exact extent and payload assertions. The alignment
bytes do not claim ownership of following ROM data.

The source unit remains mixed. No assembly, compiler settings or shared type
was changed. Acceptance requires the clean batch's full game-code and mapped
rodata comparisons, tests, progress and whitespace checks.

The clean batch passed: full US game-code and all mapped rodata are byte-identical,
1,075 tests passed (12 skipped), and progress/whitespace passed. The result was
`BATCH_COMPLETE`. This checkpoint was flushed before the parallel-worker handoff.
