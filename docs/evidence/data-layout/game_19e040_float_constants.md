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

## func_15170F4C pool (nov14)

`func_15170F4C` spawns six debris particles from the `D_800A6ED8` table. Its raw HI16/LO16
pairs in `asm/nonmatchings/game_19E040/func_15170F4C.s` address the six words
0x800A6F98..0x800A6FAF, which the checksum-validated US game-data archive (ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, base 0x80082B20) holds as
`3E99999A BF333333 BE4CCCCD 3DCCCCCD 3E6B851F 3DB851EC`: exactly `0.3f`, `-0.7f`,
`-0.2f`, `0.1f`, `0.23f` and `0.09f`. No other reference function touches them. With
`extern f32` symbols the deferred body scored CURRENT 6028; as literals it is
`CURRENT (0)`.

The generated object's `.rodata` now starts with these 0x18 bytes, immediately followed
by the existing 0x10-byte pool, so the owned range simply begins earlier:
`config/game/us-rodata.ld` maps game_19E040 at 0x800A6F98 with a 0x30 extent assertion
and a 0x28 payload, and `config/data/us.json` records the owner at the new start. The
words 0x800A6F88..0x800A6F97 stay extern reads of the deferred `func_15170B90`.
