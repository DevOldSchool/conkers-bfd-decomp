# US game_12B7D0 particle float constants

`func_150FE604` spawns a particle burst and loads two per-function rodata constants: `D_800A1FF0`, added to the first random spread value, and `D_800A1FF4`, the scale of the speed term.

With extern symbols IDO allocates the function differently (CURRENT 330, frame 0x70 versus raw 0x68); the literals reproduce the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `406D70A3 43968000` at 0x800A1FF0. `43968000` is 301.0. `406D70A3` is 3.7099998 and is one unit below the nearest single-precision value of 3.71 (`406D70A4`), so the source spells it `3.7099998f`, which IDO rounds to the ROM word. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_12B7D0.o` has rodata `406d70a3439680000000000000000000`: the two constants in load order followed by 8 zero alignment bytes, with no data relocations. The preceding word 0x800A1FEC (`3B5A740E`) and the vector tables `D_800A1FC8`/`D_800A1FE0` stay outside this mapping. No other function in the unit produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
