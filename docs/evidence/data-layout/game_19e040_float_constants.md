# US game_19E040 particle float constants

`func_15171200` fills a particle packet in a loop and loads four per-function rodata constants: the drift factor `D_800A6FB0` (-0.2), the random-range scale `D_800A6FB4` (6.1035157e-06), the lift factor `D_800A6FB8` (0.8) and the flag scale `D_800A6FBC` (6.666667).

With the existing extern symbols IDO hoists the in-loop `D_800A6FBC` address and allocates differently (CURRENT 1364 recorded for the extern form); the literals `-0.2f`, `6.1035157e-06f`, `0.8f` and `6.666667f` reproduce the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `BE4CCCCD 36CCCCCD 3F4CCCCD 40D55556` at 0x800A6FB0, exactly the single-precision values of those literals. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_19E040.o` has rodata `be4ccccd36cccccd3f4ccccd40d55556`: the four constants in load order with no alignment padding and no data relocations. The preceding words `D_800A6FA0` through `D_800A6FAC` are loaded by `func_15170F4C`, still in assembly, and the following word `D_800A6FC0` (`C49EC000`) belongs to `src/game/game_19EAB0.c`; both lie outside this mapping's owned payload and are not treated as padding or replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. The function reached full registered CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.
