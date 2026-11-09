# US game_10D7B0 float constants

`func_150E03F8` builds a random velocity with `func_15143794`, scales it, and
spawns a particle through `func_151A26EC`. It loads five per-function rodata
constants with `lui`/`lwc1` pairs: `D_800A0FBC` scales the random launch speed,
`D_800A0FC0` and `D_800A0FC4` form the velocity scale, and `D_800A0FC8` and
`D_800A0FCC` form the spin term. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) contains big-endian
`40BBD70A 3E2D0E57 3E3E76C9 3E6B851F BEAC8B44` at `0x800A0FBC`, exactly the
single-precision values of `5.87f`, `0.16900001f`, `0.186f`, `0.23f` and
`-0.337f`; the game-data base is `0x80082B20`.

With extern symbols the best candidate reached CURRENT (1008). The literals in
load order, with the first random scale and the second random integer computed
before their calls (the same shape as `func_151B86F4` in game_1E58B0), reproduce
the raw function (CURRENT 0). The generated `build/us/src/game/game_10D7B0.o`
has the 32-byte `.rodata`
`40bbd70a3e2d0e573e3e76c93e6b851fbeac8b44000000000000000000000000`: the five
constants in load order followed by twelve zero alignment bytes, with no data
relocations. The preceding words `D_800A0FB4` and `D_800A0FB8` are loaded by
`func_150E0348` through extern symbols; neither is owned by this mapping.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 32-byte extent assertion and a 24-byte
payload-size symbol (see the `func_150E05F8` section below). `config/data/us.json` records the source owner and its
completed-path alias. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.

## func_150E05F8 literal

`func_150E05F8` maps a distance onto a 0..255 fade between two thresholds. Its
first `lui`/`lwc1` pair addresses `0x800A0FD0`, which the US ROM holds as
`4520A000` (`2570.0f`). Written as the C literal `2570.0f`, IDO emits it as the
next word of this unit's `.rodata`, offset 0x14, i.e. exactly `0x800A0FD0`,
and the function reaches full-span `CURRENT (0)`. With the extern it stayed at
265 (the reference loads the constant at the very top). The object's `.rodata`
is now `40bbd70a3e2d0e573e3e76c93e6b851fbeac8b444520a0000000000000000000`: 0x18
payload bytes and eight zero alignment bytes, so the 32-byte extent is
unchanged and the payload-size symbol grows from 0x14 to 0x18.

The upper threshold `D_800A0FD4` (`4570A000`, 3850.0f) stays an extern: as a
literal IDO folds `1 / (hi - lo)` into a constant, which the raw code does not.
That word is read through its symbol and is not owned by this mapping.
