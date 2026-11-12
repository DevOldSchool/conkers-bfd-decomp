# US game_114B80 float constants

`func_150E8470` scales its spawn packet speed with the same float the raw code
loads from `D_800A1374` into `$f28`. The checksum-validated US game-data archive
contains big-endian `3A83126F` at that address, exactly `0.001f`. ROM SHA1 is
`4cbadd3c4e0729dec46af64ad018050eada4f47a`; decompressed game-data offset is
`0x1E854` relative to base `0x80082B20`.

The literal is required for the register allocation, not only for the bytes.
With an extern `f32` load, IDO promotes the global and disrupts the surrounding
constant schedule into `$f28`/`$f30`/`$f26`/`$f24`/`$f20`. As a written
`0.001f` literal it matches the raw HI16/LO16 pair.

`func_150E7C9C` scales a queued point's x coordinate into a sound pan value. Its
raw HI16/LO16 pair in `asm/nonmatchings/game_114B80/func_150E7C9C.s`
(`150E7E9C`/`150E7EA0`) addresses `0x800A1350`, and no other reference function
touches that word. The archive holds `3EDCEE77` there, exactly `0.43150684f`.
With `extern f32 D_800A1350` the body scores CURRENT 1845; written as the literal
(and with the queue's `points` as a flat `f32[2]` indexed by `index * 2`) the
function is `CURRENT (0)`.

The generated `game_114B80.o` has rodata `3edcee773a83126f0000000000000000`: the
two constants in function order (0.43150684 at offset 0, 0.001 at offset 4) and
8 zero alignment bytes, with no data relocations. The two words are not adjacent
in ROM: `0x800A1354..0x800A1370` hold other members' constants
(`442EC000 43FF8000 3F483128 BF6E147C 3F3AE148 3DCCCCCC 3DB404EA 3F82DE98`),
still read through externs by `func_150E81A8` and `func_150E8470`. The unit is
therefore a split unit: `scripts/split_game_rodata.py` splits it into
`.rodata.114b80_0` (0x4 at `0x800A1350`) and `.rodata.114b80_4` (0x4 at
`0x800A1374`), as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md).
Each INFO section has an exact 0x4 size assertion and `config/data/us.json`
records both owners. The linked bytes are compared with the checksum-validated
ROM by `scripts/verify_game_rodata.py`.

Both functions reached full registered CURRENT (0) with focused layout, progress
and whitespace checks passed. No reference assembly, compiler flag or verifier
changes are involved.
