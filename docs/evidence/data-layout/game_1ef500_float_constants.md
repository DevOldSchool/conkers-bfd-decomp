# US game_1EF500 float constants

`func_151C436C` eases three current components at `arg1 + 0x10` toward the targets at `arg1 + 0x1C` once per remaining step, multiplying each difference by one constant. The raw function loads that constant from `D_800AAA7C` before the loop and keeps it in `$f20` together with the three hoisted targets.

With an `extern f32` symbol the loop needs explicit target and step snapshots and still allocates the invariants and current components in different registers (CURRENT 100 to 110; the natural loop with the extern scores 1916). A float literal lets IDO hoist the constant and the targets itself, and the natural `while (arg2 > 0)` loop with three `+=` updates reproduces the raw allocation exactly.

The checksum-validated US game-data archive contains big-endian `3E6A2596` at 0x800AAA7C, exactly 0.2286590039730072, reproduced by the shortest round-trip literal `0.228659f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_1EF500.o` has rodata `3e6a2596000000000000000000000000`: one four-byte constant followed by 12 zero alignment bytes, with no data relocations. The function has one HI16/LO16 pair referencing it. The neighbouring ROM words (0x800AAA74 `3E85A1CB`, 0x800AAA78 `3F5EC5E3`, 0x800AAA80 `40C90FDB`) belong to functions still in assembly and stay outside this mapping's owned payload; they are not treated as padding or replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. The function reached full registered CURRENT (0) with focused layout, progress and whitespace checks; the clean linked verify-batch result is recorded with the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.
