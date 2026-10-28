# US game_1D4AC0 float constants

`func_151A7610` scales a launch velocity from the caller's direction, picks a
random spread and size, and spawns a particle through `func_151A26EC`. It loads
three per-function rodata constants with `lui`/`lwc1` pairs: `D_800A8DC8`
scales the launch speed, and `D_800A8DCC` and `D_800A8DD0` form the spread
term. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) contains big-endian
`3A83126F 4413C000 3A83126F` at `0x800A8DC8`, exactly the single-precision
values of `0.001f`, `591.0f` and `0.001f`; the game-data base is `0x80082B20`.

With extern symbols the best candidate reached CURRENT (2637). The literals in
load order reproduce the raw function (CURRENT 0) once the source is reshaped:
the radius is read before the position copy, the per-unit and size temporaries
are inlined, and the remaining named locals follow the raw stack homes. The
generated `build/us/src/game/game_1D4AC0.o` has the 16-byte `.rodata`
`3a83126f4413c0003a83126f00000000`: the three constants in load order followed
by four zero alignment bytes, with no data relocations. The preceding words at
`0x800A8DC0` and `0x800A8DC4` belong to other code in this unit and are not
owned by this mapping.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 16-byte extent assertion and a 12-byte
payload-size symbol. `config/data/us.json` records the source owner and its
completed-path alias. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.
