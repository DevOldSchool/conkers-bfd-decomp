# US game_19E040 particle float constants

`func_15171200` emits a burst of particles with randomized drift, lift and
size. The raw function loads four float constants through one HI16/LO16 pair
each: `D_800A6FB0`, `D_800A6FB4`, `D_800A6FB8` and `D_800A6FBC`, the last one
inside the emission loop.

With `extern f32` symbols IDO hoists the in-loop `D_800A6FBC` address out of
the loop and the schedule diverges (CURRENT 1364). Writing the constants as C
literals gives the function its own pool and reproduces the raw schedule
exactly.

The checksum-validated US game-data archive (game-data base 0x80082B20)
contains big-endian `BE4CCCCD 36CCCCCD 3F4CCCCD 40D55556` at 0x800A6FB0,
exactly the literals `-0.2f`, `6.1035157e-06f`, `0.8f` and `6.666667f`.

The generated `build/us/src/game/game_19E040.o` has a 16-byte `.rodata`
section holding the same 16 payload bytes, with no alignment padding and no
data relocations. The neighbouring ROM words (0x800A6FAC `3DB851EC`,
0x800A6FC0 `C49EC000`) belong to other functions still in assembly and stay
outside this mapping's owned payload.

The INFO mapping in `config/game/us-rodata.ld` places the section at
`0x800A6FB0` with `SUBALIGN(4)`, a 0x10 size assertion and a 0x10 payload-size
symbol, so the existing verifier compares every payload byte with the ROM.
`config/data/us.json` records the `.rodata` owner. The function reached full
registered CURRENT (0) with focused layout, progress and whitespace checks;
the clean verify-batch result is recorded with the commit that adds this
mapping. No reference assembly, compiler flag or verifier changes are
involved.
