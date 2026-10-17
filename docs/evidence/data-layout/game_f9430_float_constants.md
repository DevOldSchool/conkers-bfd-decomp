# US game_F9430 particle constants

`func_150CC6B8` builds a particle packet from four float constants at 0x800A06CC..0x800A06D8. The first (`D_800A06CC`, 401.0) keeps its extern symbol: as a literal IDO rotates the following FP temporaries, while the extern reproduces the raw registers. The other three must be literals: with extern symbols IDO schedules the later loads into different registers (`$f4`/`$f6` instead of raw `$f6`/`$f8`).

The checksum-validated US game-data archive contains big-endian `3DCCCCCD 3F851EB8 3F66A7F0` at 0x800A06D0, reproduced by `0.1f`, `1.04f` and `0.901f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_F9430.o` has rodata `3dcccccd3f851eb83f66a7f000000000`: the three constants in load order followed by four zero alignment bytes, with no data relocations; only `func_150CC6B8` references it. 0x800A06CC and the following words from 0x800A06DC (used by later functions of the unit through extern symbols) are outside this mapping's owned payload and are not treated as padding or replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload, and a size assertion detects constant-pool growth. The full registered instruction comparison reached CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.
