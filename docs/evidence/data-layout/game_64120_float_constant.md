# US game_64120 float constant

`func_15038468` converts an angle with the radians-to-degrees factor at 0x80098648. With an extern symbol IDO schedules the constant load and its consumers differently; the float literal `57.295776f` reproduces the raw instructions exactly.

The checksum-validated US game-data archive contains big-endian `42652EE0` at 0x80098648, exactly 57.295776 (`57.295776f`). ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_64120.o` has rodata `42652ee0000000000000000000000000`: one constant followed by 12 zero alignment bytes, with no data relocations; only `func_15038468` references it. The following ROM words (0x8009864C onward, used by other unit functions such as `func_1503B708` at 0x800986EC) keep their extern symbols and are outside this mapping's owned payload. A later literal in another function of this unit would make the object pool noncontiguous and needs its own placement proof.

The INFO mapping retains linked bytes for verification without appending to the code-only payload, and a size assertion detects constant-pool growth. The full registered instruction comparison reached CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.
