# US game_40490 angle float constants

`func_150144B8` converts two packet angles from degrees to radians with `D_80096688` and scales a packed byte by `D_8009668C`. Both are per-function rodata literals loaded in source order.

With the extern symbols IDO allocates the function differently (CURRENT 207); the literals `0.017453292f` (π/180) and `0.7853982f` (π/4) reproduce the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `3C8EFA35 3F490FDB` at 0x80096688, exactly those single-precision values. The surrounding words (`3A83126F`, `2F0BCDFE` before and further `3C8EFA35` words after) belong to other functions' pools and stay outside this mapping. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_40490.o` has rodata `3c8efa353f490fdb0000000000000000`: the two constants in load order followed by 8 zero alignment bytes, with no data relocations. The verifier compares only the 8-byte payload with ROM. No other function in the unit produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
