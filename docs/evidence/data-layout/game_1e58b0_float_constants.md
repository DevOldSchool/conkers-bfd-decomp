# US game_1E58B0 float constants

`func_151B86F4` builds a random velocity with `func_15143794`, scales it, and
spawns a particle through `func_151A26EC`. It loads four per-function rodata
constants with `lui`/`lwc1` pairs: `D_800AA4CC` and `D_800AA4D0` scale the
random launch speed, and `D_800AA4D4` and `D_800AA4D8` scale the velocity and
spin terms. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) contains big-endian
`446C4000 3C23D70A 3A83126F 3A83126F` at `0x800AA4CC`, exactly the
single-precision values of `945.0f`, `0.01f`, `0.001f` and `0.001f`; the
game-data base is `0x80082B20`.

With extern symbols the best candidate reached CURRENT (1110). The literals in
load order, with the first random scale and the second random integer computed
before their calls, reproduce the raw function (CURRENT 0). The generated
`build/us/src/game/game_1E58B0.o` has the 16-byte `.rodata`
`446c40003c23d70a3a83126f3a83126f`: the four constants in load order with no
data relocations or alignment bytes. The preceding word `D_800AA4C8` is loaded
by `func_151B8668` through its extern symbol and the following words belong to
other data; neither is owned by this mapping or treated as padding.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 16-byte extent assertion and a 16-byte
payload-size symbol. `config/data/us.json` records the source owner and its
completed-path alias. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.
