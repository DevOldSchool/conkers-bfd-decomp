# US game_1CBE20 float constants

Two matched functions in game_1CBE20 multiply by 0.1f, and each raw function loads its own copy of the constant:

- `func_1519EB8C` loads `D_800A8CD4` once and uses it for two packet values.
- `func_1519ED24` loads `D_800A8CD8` before the linked-object pointer and scales two transform components.

With extern symbols IDO schedules both loads differently (the constant load later in `func_1519EB8C`, the pointer load first in `func_1519ED24`); float literals reproduce the raw order in both. The checksum-validated US game-data archive contains big-endian `3DCCCCCD 3DCCCCCD` at 0x800A8CD4, exactly 0.10000000149011612 twice, reproduced by `0.1f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_1CBE20.o` has rodata `3dcccccd3dcccccd0000000000000000`: two four-byte constants in function order followed by 8 zero alignment bytes, with no data relocations. Each function has one HI16/LO16 pair referencing its own constant. The earlier unit constants at 0x800A8CC0..0x800A8CD0 keep their extern symbols and are outside this mapping's owned payload; the following ROM words (0x800A8CDC zero, 0x800A8CE0 nonzero) are not treated as padding or replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. Both functions reached full registered CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commits that add and extend this mapping. No reference assembly, compiler flag or verifier changes are involved.
