# US game_1A20A0 float constants

`func_1517725C` swings two pairs of model vertices by converting degrees to radians four times. Its raw HI16/LO16
pairs in `asm/nonmatchings/game_1A20A0/func_1517725C.s` address four consecutive words at
`0x800A71AC..0x800A71BB` (`15177294`/`15177298`, `151772C4`/`151772D0`, `1517730C`/`15177344`,
`1517735C`/`15177368`). No other reference function touches them. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3C8EFA35` in each word, the
single-precision value of `0.017453292f` (pi / 180). IDO emits a separate pool word for each written use of the
literal, so the four `0.017453292f` multiplications in the C source produce exactly these four words in load order.

With `extern f32 D_800A71AC..D_800A71B8` the deferred body scored CURRENT 1884; as literals the function is
`CURRENT (0)`.

`func_15174BF0` spawns leaf actors and scales a random yaw step by `0.01f`. Its raw HI16/LO16 pair
(`15174CC4`/`15174CD4` in `asm/nonmatchings/game_1A20A0/func_15174BF0.s`) addresses `0x800A7174`, which holds
`3C23D70A` (0.01) in the same ROM. No other reference function touches that word; the identical value at
`0x800A7178` stays an extern read of `func_15175958`, and the byte table at `0x800A7170` stays an extern of three
members. With `extern f32 D_800A7174` the deferred body scored CURRENT 2285; as a literal the function is
`CURRENT (0)`.

The generated `game_1A20A0.o` has rodata `3c23d70a 3c8efa35 3c8efa35 3c8efa35 3c8efa35` (the `func_15174BF0`
constant, then the four radian constants in function order) and 12 zero alignment bytes, 0x20 in all, with no data
relocations. The two pools are not adjacent in ROM, so game_1A20A0 is a split unit: `scripts/split_game_rodata.py`
splits it into `.rodata.1a20a0_0` (0x4 at `0x800A7174`) and `.rodata.1a20a0_4` (0x10 at `0x800A71AC`), each with an
exact linker size assertion, as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md).
`config/data/us.json` records both owners. The words between them (`0x800A7178..0x800A71A8`) and from `0x800A71BC`
on are not part of either mapping. No reference assembly, compiler flag or verifier change is involved.
