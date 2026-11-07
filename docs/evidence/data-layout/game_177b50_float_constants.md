# US game_177B50 particle float constants

`func_1514AB5C` builds a particle descriptor and loads seven per-function rodata constants in source order: the drag and scale fields `D_800A57B0` (0.045) and `D_800A57B4` (0.7), the x-scale factors `D_800A57B8` (22.6) and `D_800A57BC` (13.786), and the y-scale factors `D_800A57C0` (57.969), `D_800A57C4` (42.714) and `D_800A57C8` (118.763).

With the existing extern symbols IDO allocates a larger frame and reorders the float work (CURRENT 4857); the literals reproduce the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `3D3851EC 3F333333 41B4CCCD 415C9375 4267E042 422ADB23 42ED86A8` at 0x800A57B0, exactly the single-precision values of those literals. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_177B50.o` has rodata `3d3851ec3f33333341b4cccd415c93754267e042422adb2342ed86a800000000`: the seven constants in load order followed by 4 zero alignment bytes, with no data relocations. The following word `D_800A57CC` (`3DA3D70B`, 0.08) is still loaded through its extern symbol by `func_1514AD9C`; it lies outside this mapping's owned payload and is not treated as padding or replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. The function reached full registered CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.

## func_1514B8E4 pool

`func_1514B8E4` builds a motion record from ten per-function constants. Its raw HI16/LO16 pairs address `0x800A5860`..`0x800A5884`, which the checksum-validated US ROM holds as `4678FC00 45D26800 468FC800 4170B96F 40BBC3D6 4141C87A 3ECAD752 3DD58454 3F050D7E 3EB026C8`: 15935.0, 6733.0, 18404.0, 15.045272, 5.8676558, 12.111444, 0.396174, 0.1042563, 0.5197371 and 0.34404588 (single precision, shortest round-trip spelling). With those values as C literals the function reaches full-span CURRENT (0); with the old externs the best candidate stayed at a float-register swap.

The generated object's `.rodata` is now 0x50 bytes: the 0x1C-byte `func_1514AB5C` pool, then these 0x28 bytes, then zero padding, with no data relocations. Because the two pools are apart in ROM (`0x800A57CC`..`0x800A585C` belongs to assembly members and keeps its extern symbols), `scripts/split_game_rodata.py` splits game_177B50 into `.rodata.177b50_0` (0x800A57B0, 0x1C) and `.rodata.177b50_1c` (0x800A5860, 0x28); see `game_rodata_literal_sub_pools.md`. The next word, `D_800A5888` (0.35), is still read through its extern by `func_1514BC08`.
