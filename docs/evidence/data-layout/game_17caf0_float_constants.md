# US game_17CAF0 particle float constants

`func_15153CCC` and `func_15153F18` are twin particle emitters. Each loads one per-function rodata constant before its emission loop and passes it twice to `func_151DA6F8`: `D_800A5FFC` (1.7) and `D_800A6000` (1.7).

With extern symbols IDO keeps a named copy of the value and allocates two extra frame words (frame 0xC0 versus raw 0xB8, CURRENT 54 for both); the `1.7f` literals reproduce both raw functions (CURRENT 0). The checksum-validated US game-data archive contains big-endian `3FD9999A 3FD9999A` at 0x800A5FFC, exactly the single-precision value of the literal in function order. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

`func_1514FF44` and `func_15150178` are an earlier pair of particle emitters in the same unit. Each passes the literal `1.4f` twice to `func_151D9014`, loaded once before its emission loop from its own word: 0x800A5FF0 and 0x800A5FF4, both `3FB33333` in the same ROM. With extern symbols the candidates scored CURRENT 940 and 1119. With the literals, `func_151D9014` declared with the byte and halfword parameters its raw assembly homes (`lbu`/`lh`), and `func_1514FF44` taking the `Game17CAF0ParticleConfig *` its body reads (its local prototype and the caller `func_1514FEFC` moved after that typedef), both functions are CURRENT (0).

The word 0x800A5FF8 between the two pools (`3F0F9DB3`, 0.561) is loaded by the assembly member `func_1515080C` and stays an extern. The generated `game_17CAF0.o` therefore has 0x10 bytes of `.rodata`, `3fb333333fb333333fd9999a3fd9999a`, all payload in function order and with no data relocations, split by `scripts/split_game_rodata.py` into `.rodata.17caf0_0` (0x8 bytes at 0x800A5FF0) and `.rodata.17caf0_8` (0x8 bytes at 0x800A5FFC) as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md). `config/game/us-rodata.ld` maps both as INFO sections with exact extent assertions and per-range base symbols; `config/data/us.json` records both owners.

No reference assembly, compiler flag or verifier changes are involved.
