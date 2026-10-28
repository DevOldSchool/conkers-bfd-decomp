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
`func_150E0348` through extern symbols, and the words from `0x800A0FD0` belong
to other code or data; none of them is owned by this mapping or treated as
padding.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 32-byte extent assertion and a 20-byte
payload-size symbol. `config/data/us.json` records the source owner and its
completed-path alias. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.
