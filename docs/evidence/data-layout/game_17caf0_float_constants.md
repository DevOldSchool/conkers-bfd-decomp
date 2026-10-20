# US game_17CAF0 particle float constants

`func_15153CCC` and `func_15153F18` are twin particle emitters. Each loads one per-function rodata constant before its emission loop and passes it twice to `func_151DA6F8`: `D_800A5FFC` (1.7) and `D_800A6000` (1.7).

With extern symbols IDO keeps a named copy of the value and allocates two extra frame words (frame 0xC0 versus raw 0xB8, CURRENT 54 for both); the `1.7f` literals reproduce both raw functions (CURRENT 0). The checksum-validated US game-data archive contains big-endian `3FD9999A 3FD9999A` at 0x800A5FFC, exactly the single-precision value of the literal in function order. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_17CAF0.o` has rodata `3fd9999a3fd9999a0000000000000000`: the two constants in function order followed by 8 zero alignment bytes, with no data relocations. No other function in the unit produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
