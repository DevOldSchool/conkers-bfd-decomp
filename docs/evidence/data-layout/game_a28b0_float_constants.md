# US game_A28B0 scale float constant

`func_15076D3C` initializes its `scale` local from the per-function rodata constant `D_8009A144`.

With the extern symbol IDO allocates the function differently (CURRENT 180); the `0.01f` literal reproduces the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `3C23D70A` (0.01) at 0x8009A144. The surrounding words (`3DAAAA7E` before, `4B18967F` = 9999999.0 after, which `func_15077C38` still loads through `D_8009A148`) stay outside this mapping. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_A28B0.o` has rodata `3c23d70a000000000000000000000000`: the constant followed by 12 zero alignment bytes, with no data relocations. The verifier compares only the 4-byte payload with ROM. No other function in the unit produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
