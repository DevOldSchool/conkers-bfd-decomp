# US game_1EF500 float constants

`func_151C436C` eases three current components at `arg1 + 0x10` toward the targets at `arg1 + 0x1C` once per remaining step, multiplying each difference by one constant. The raw function loads that constant from `D_800AAA7C` before the loop and keeps it in `$f20` together with the three hoisted targets.

With an `extern f32` symbol the loop needs explicit target and step snapshots and still allocates the invariants and current components in different registers (CURRENT 100 to 110; the natural loop with the extern scores 1916). A float literal lets IDO hoist the constant and the targets itself, and the natural `while (arg2 > 0)` loop with three `+=` updates reproduces the raw allocation exactly.

The checksum-validated US game-data archive contains big-endian `3E6A2596` at 0x800AAA7C, exactly 0.2286590039730072, reproduced by the shortest round-trip literal `0.228659f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

## func_151C2734 constant (round-28)

`func_151C2734` picks a listener in front of its owner and plays a sound for it. The raw function loads one word through a HI16/LO16 pair: `D_800AAA38`, `3F666666` in the same ROM, the single-precision value of `0.9f`, compared against the normalised dot product. With the extern symbol its deferred candidate scored CURRENT 1884; with the literal and a natural `for` loop over the listeners it is `CURRENT (0)`. The neighbouring words `D_800AAA30`/`D_800AAA34` and `D_800AAA3C`..`D_800AAA78` stay externs of other members or functions still in assembly. Once `func_151C2734` was C, the preserved `func_151C2AD0` candidate (with each `vertices++` written as its own statement) compiled to the full original size in file context, so its recorded 20-byte layout failure is gone and it is also `CURRENT (0)`; it emits no rodata.

## Object layout

The generated `game_1EF500.o` has rodata `3f666666 3e6a2596 00000000 00000000`: the `func_151C2734` word at object offset 0, the `func_151C436C` word at offset 4 and 8 zero alignment bytes, with no data relocations. The neighbouring ROM words (0x800AAA74 `3E85A1CB`, 0x800AAA78 `3F5EC5E3`, 0x800AAA80 `40C90FDB`) belong to other functions and stay outside the owned payload; they are not treated as padding or replaced. Because the two words lie 0x44 bytes apart in ROM, `scripts/split_game_rodata.py` cuts the object pool into `.rodata.1ef500_0` and `.rodata.1ef500_4` (four bytes each), and `config/game/us-rodata.ld` maps them as INFO sections at `0x800AAA38` and `0x800AAA7C` with exact extent assertions and per-range base symbols, as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md). `config/data/us.json` records both owners. No reference assembly, compiler flag or verifier changes are involved.
