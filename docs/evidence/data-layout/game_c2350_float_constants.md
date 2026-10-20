# US game_C2350 primitive-depth float constant

`func_150958B0` emits a G_SETPRIMDEPTH command whose depth is `sp3C / sp38 * D_8009DEC0 + D_8009DEC0`. `D_8009DEC0` is a per-function rodata literal loaded once and used for both the scale and the offset.

With the extern symbol a named copy is needed to reproduce the single load, which takes an extra -g3 home (frame 0x50 versus raw 0x48, CURRENT 118); the `16352.0f` literal used in both places reproduces the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `467F8000` (16352.0) at 0x8009DEC0. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_C2350.o` has rodata `467f8000000000000000000000000000`: the constant followed by 12 zero alignment bytes, with no data relocations. The ROM words that follow (0x8009DEC4..0x8009DECF) are also zero. No other function in the unit produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
