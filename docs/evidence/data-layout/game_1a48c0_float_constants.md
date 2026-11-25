# US game_1A48C0 vertex effect constants

`func_15177410` registers a per-object vertex effect and is the only member of
`src/game/game_1A48C0.c` that emits `.rodata`; `func_15177A94` uses no pooled
literals. Its five non-`lui` float literals are emitted in use order: `0.01f`
for the radius scale on the non-zero-radius path, `0.01f` again on the
zero-radius path (IDO emits one word per use), `0.017453292f` for the
degree-to-radian factor, `0.7111111f` (256/360) for the byte angle and
`40.743664f` (256/2π) for the `func_150484A0` angle scale. `1.0f` and `0.0f`
are built with `lui`/`mtc1` and need no pool.

The checksum-validated US game-data archive (game-data base `0x80082B20`)
holds `3C23D70A 3C23D70A 3C8EFA35 3F360B61 4222F983` at `0x800A71C0`, directly
after the `game_1A20A0` radian pool that ends at `0x800A71BC`, and was read
with `scripts/rom_span.game_data`. The ROM words at `0x800A71D4`, `0x800A71D8`
and `0x800A71DC` are zero. The compiled `game_1A48C0.o` has a 0x20-byte
`.rodata` section with exactly these five words followed by twelve zero
alignment bytes, and five HI16/LO16 pairs at text offsets `0x100`/`0x1A4`,
`0x1E0`/`0x1E8`, `0x2AC`/`0x2B0`, `0x2D4`/`0x2D8` and `0x58C`/`0x590`; it has
no data relocations. The reference assembly names these words `D_800A71C0`,
`D_800A71C4`, `D_800A71C8`, `D_800A71CC` and `D_800A71D0` at the same uses.

`config/game/us-rodata.ld` places the pool at `0x800A71C0` as informational
data with `SUBALIGN(4)`, an exact 0x20-byte size assertion and a 0x14-byte
payload-size symbol; `config/data/us.json` records the owner. No assembly,
compiler flag or verifier change is involved.
