# US game_1865D0 particle float constants

`func_1515AB88` is a looping particle emitter in the same family as `func_150E8470`. Before its emission loop the raw function keeps `0.25`, `D_800A641C` (0.15), `D_800A6418` (0.1) and `D_800A6414` (0.08) in saved FP registers across the per-particle calls. IDO only hoists literal constants that way: extern symbols are reloaded after every call, and named copies add three frame words (frame 0x120 versus raw 0x110).

The checksum-validated US game-data archive contains big-endian `3DA3D70A 3DCCCCCD 3E19999A` at 0x800A6414, exactly the single-precision values of `0.08f`, `0.1f` and `0.15f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_1865D0.o` has rodata `3da3d70a3dcccccd3e19999a00000000`: the three constants in function order followed by 4 zero alignment bytes, with no data relocations. The unit's other functions still reference their constants through extern symbols, so no other function produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
