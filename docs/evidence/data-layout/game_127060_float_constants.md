# US game_127060 transform float constant

`func_150FB188` stores the same per-function rodata constant `D_800A1DC0` into two transform fields before calling `func_15157DEC`.

With the extern symbol IDO allocates the function differently (CURRENT 654); the `0.3f` literal reproduces the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `3E99999A` (0.3) at 0x800A1DC0, followed by zero words. The preceding words (`3DA3D70B`, `3E3851EC`) belong to other functions and stay outside this mapping. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_127060.o` has rodata `3e99999a000000000000000000000000`: the constant followed by 12 zero alignment bytes, with no data relocations. The verifier compares only the 4-byte payload with ROM. No other function in the unit produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
