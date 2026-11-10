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
