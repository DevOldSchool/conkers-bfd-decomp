# US game_83300 velocity float constants

`func_1505A770` integrates a velocity at 0x20 into a position at 0x18 in fixed 0.1-second steps. Its raw code loads three per-function rodata constants:

- `D_800994DC` (0.1) once into `$f12`, shared by the step count `D_800D1550 / 0.1f` and the decrement `velocity_scale * 0.1f`.
- `D_800994E0` (0.05) in the peeled remainder iterations of the step loop.
- `D_800994E4` (0.05) in the four-way unrolled body of the same loop.

The two 0.05 words are IDO's per-copy literal loads after it unrolls one source loop, so a single extern symbol cannot reproduce them; the C uses the literals `0.1f` and `0.05f`. The checksum-validated US game-data archive contains big-endian `3DCCCCCD 3D4CCCCD 3D4CCCCD` at 0x800994DC (0.10000000149011612, 0.05000000074505806 twice). ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_83300.o` has rodata `3dcccccd3d4ccccd3d4ccccd00000000`: the three constants in load order followed by 4 zero alignment bytes, with no data relocations. The following word `D_800994E8` (0.4) belongs to another function, keeps its extern symbol and lies outside this mapping's owned payload; it is not treated as padding or replaced. The remaining constants in `func_1505A770` (-500.0, 0.5) are `lui` immediates and need no rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. The function reached full registered CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.

Update: `func_1505F188` added a second pool at 0x8009962C. The unit is now
split, and this pool is mapped as the exact 0xC-byte `.rodata.83300_0`
section with no payload-size symbol. See
[literal sub-pools](game_rodata_literal_sub_pools.md).
