# US game_49D30 initial-value float constant

`func_1501D044` initializes its `initial_value` local from the per-function rodata constant `D_800969C0`.

With the extern symbol IDO allocates the function differently (CURRENT 355); the `999.0f` literal reproduces the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `4479C000` (999.0) at 0x800969C0. The preceding words (a switch-table pointer `1501C784` and a zero word) and the following `4479C000` words belong to other functions and stay outside this mapping. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_49D30.o` has rodata `4479c000000000000000000000000000`: the constant followed by 12 zero alignment bytes, with no data relocations. The verifier compares only the 4-byte payload with ROM. No other function in the unit produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
