# US game_124920 particle constant

`func_150F802C` stores one float constant twice into its particle packet (offsets 0x08 and 0x0C). The raw code loads it with `lui`/`lwc1` from 0x800A1BDC, an IDO per-function literal rather than a named global: written as the literal `0.020000001f` the function reaches CURRENT (0), while the former `extern f32 D_800A1BDC` declaration scored 1325.

The checksum-validated US game-data archive contains big-endian `3CA3D70B` at 0x800A1BDC, which `0.020000001f` reproduces (`0.02f` rounds to a different word). ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_124920.o` has rodata `3ca3d70b000000000000000000000000`: the constant followed by twelve zero alignment bytes, with no data relocations; only `func_150F802C` references it. The words from 0x800A1BC0 to 0x800A1BD8 and from 0x800A1BE0 (used by the unit's remaining `GLOBAL_ASM` members through extern symbols) are outside this mapping's owned four-byte payload and are not treated as padding or replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload, and a size assertion detects constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
