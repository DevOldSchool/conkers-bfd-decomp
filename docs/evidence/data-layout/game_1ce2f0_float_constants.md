# US game_1CE2F0 float constants

Two matched twin functions in game_1CE2F0 pass the same scale three times to `func_151A11CC`, and each raw function loads its own copy of the constant:

- `func_151A0E40` loads `D_800A8D20` once, before the prologue's argument homes, and stores it to three outgoing argument slots.
- `func_151A0F28` loads `D_800A8D24` the same way.

With extern symbols IDO schedules the load after the argument homes and the narrowed `u8` argument (CURRENT 180 each); the float literal `2.019f` reproduces the raw entry-block order in both. The checksum-validated US game-data archive contains big-endian `4001374C 4001374C` at 0x800A8D20, exactly 2.0190000534057617 twice, reproduced by `2.019f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_1CE2F0.o` has rodata `4001374c4001374c0000000000000000`: two four-byte constants in function order followed by 8 zero alignment bytes, with no data relocations. Each function has one HI16/LO16 pair referencing its own constant. The following word `D_800A8D28` (1500.0, still loaded by the raw `func_151A1010`) keeps its extern symbol and lies outside this mapping's owned payload; it is not treated as padding or replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. Both functions reached full registered CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.
