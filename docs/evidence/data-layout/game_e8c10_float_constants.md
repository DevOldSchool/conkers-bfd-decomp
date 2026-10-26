# US game_E8C10 particle float constants

`func_150BCBBC` builds a particle descriptor and loads five per-function rodata constants in source order: the descriptor scale `D_8009FEE4` (0.3) and the two random size terms `D_8009FEE8`/`D_8009FEEC` and `D_8009FEF0`/`D_8009FEF4` (0.03 multiplier, 0.01 offset each).

A recorded candidate that loads the constants through extern symbols lets IDO hoist them out of the particle loop and reorders the body (CURRENT 5439); the literals `0.3f`, `0.03f`, `0.01f`, `0.03f` and `0.01f` reproduce the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `3E99999A 3CF5C28F 3C23D70A 3CF5C28F 3C23D70A` at 0x8009FEE4, exactly the single-precision values of those literals. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_E8C10.o` has rodata `3e99999a3cf5c28f3c23d70a3cf5c28f3c23d70a000000000000000000000000`: the five constants in load order followed by 12 zero alignment bytes, with no data relocations. The preceding words `D_8009FED0` through `D_8009FEE0` are loaded by `func_150BC488` and the following word `D_8009FEFC` (`C1B5DD30`) by `func_150BD070`; both functions are still in assembly, and those words lie outside this mapping's owned payload and are not treated as padding or replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. The function reached full registered CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.
