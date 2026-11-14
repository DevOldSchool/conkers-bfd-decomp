# US characterflamethrower preset scale constants

`func_1519C9C4` fills a flamethrower preset and starts with two scale factors.
Its raw HI16/LO16 pairs in
`asm/nonmatchings/effects/characterflamethrower/func_1519C9C4.s` load
`0x800A8AFC` and `0x800A8B00`, and no other reference function touches those
words. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds
`3DCCCCCD` (`0.1f`) and `3D4CCCCD` (`0.05f`) there; the C source writes them as
the literals `0.1f` and `0.05f`.

The generated `characterflamethrower.o` has 0x10 bytes of `.rodata`
(`3dcccccd 3d4ccccd 00000000 00000000`): the two constants and 8 zero
alignment bytes, with no data relocations. The alignment bytes fall on
`0x800A8B04..0x800A8B0B` (`0.87f`, ...), which the same function still reads
through extern symbols together with the rest of the preset words up to
`0x800A8B70`; only the 0x8 payload is owned and compared.
`config/game/us-rodata.ld` maps the object as an INFO section at `0x800A8AFC`
with a 0x10 extent assertion and a 0x8 payload; `config/data/us.json` records
the owner. No reference assembly, compiler flag or verifier change is involved.

## func_151987CC sub-pool (round-24)

`func_151987CC` tests the flamethrower's recorded points against every
collision actor and adds `2500.0f` to the squared actor radius. Its raw
HI16/LO16 pair (`0x151987D8`/`0x151987DC`) loads `0x800A8ADC`, which the
checksum-validated archive holds as `451C4000` (2500.0). With the extern symbol
the deferred body scored CURRENT 1088; as a literal the function is
`CURRENT (0)`. Its loop bound is written as the 25-entry `D_800CC2D0` array
instead of the reference's end symbol `D_800D121C`
(`D_800CC2D0 + 25 * 0x32C`); the linked-alias proof resolves that address at
`finish`, so the now-unused `D_800D121C` declaration was removed.

`func_151987CC` precedes `func_1519C9C4`, so the object's `.rodata` is now
`451c4000 3dcccccd 3d4ccccd 00000000` (0x10 bytes, 0xC payload). The words
0x800A8AE0..0x800A8AF8 between the two pools stay extern reads of other members
(`func_15199C34`, `func_1519A9A4`, `func_1519B4B8`), so characterflamethrower
becomes a split unit: `scripts/split_game_rodata.py` splits it into
`.rodata.characterflamethrower_0` (0x4 at 0x800A8ADC) and
`.rodata.characterflamethrower_4` (0x8 at 0x800A8AFC), each with an exact
linker size assertion, as described in
[game rodata literal sub-pools](game_rodata_literal_sub_pools.md). The object
joins `GAME_SPLIT_RODATA_OBJS`, and `config/data/us.json` records both
sections. The earlier string and literal words (`D_800A8A84` and the
`D_800A8AA4..D_800A8AD8` constants) stay extern reads of other members.
