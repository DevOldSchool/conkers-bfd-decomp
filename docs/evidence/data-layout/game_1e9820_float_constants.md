# US game_1E9820 float constants

`func_151BC370` builds a random velocity with `func_15143794`, scales it, and
spawns a particle through `func_151A26EC`. It loads five per-function rodata
constants with `lui`/`lwc1` pairs: `D_800AA834` scales the random launch speed,
`D_800AA838` the velocity term, and `D_800AA83C`, `D_800AA840` and
`D_800AA844` form the spin term. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) contains big-endian
`3C23D70A 3A83126F 44832000 C47F8000 3A83126F` at `0x800AA834`, exactly the
single-precision values of `0.01f`, `0.001f`, `1049.0f`, `-1022.0f` and
`0.001f`; the game-data base is `0x80082B20`.

With extern symbols the best candidate reached CURRENT (1110). The literals in
load order, with the first random scale and the second random integer computed
before their calls (the same shape as `func_151B86F4` in game_1E58B0), reproduce
the raw function (CURRENT 0). The generated `build/us/src/game/game_1E9820.o`
has the 32-byte `.rodata`
`3c23d70a3a83126f44832000c47f80003a83126f000000000000000000000000`: the five
constants in load order followed by twelve zero alignment bytes, with no data
relocations. The neighbouring words at `0x800AA82C` and `0x800AA848` belong to
other code or data; they are not owned by this mapping or treated as padding.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 32-byte extent assertion and a 20-byte
payload-size symbol. `config/data/us.json` records the source owner and its
completed-path alias. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.
