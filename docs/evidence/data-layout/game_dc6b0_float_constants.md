# US game_DC6B0 particle float constant

`func_150B0094` fills a particle packet and stores the same per-function rodata constant `D_8009F7D8` into two packet fields (`packet.field8 = packet.fieldC`).

With the extern symbol IDO allocates the value differently (CURRENT 75); the `0.7f` literal reproduces the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `3F333333` (0.7) at 0x8009F7D8. Its neighbours (`40490FDB`, `3E89374C` before and `3F834B16` after) belong to other functions' pools and stay outside this mapping. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_DC6B0.o` has rodata `3f333333000000000000000000000000`: the constant followed by 12 zero alignment bytes, with no data relocations. The verifier compares only the 4-byte payload with ROM. No other function in the unit produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
