# US game_115F30 effect constants

`func_150E8B1C` reads three float constants. The raw HI16/LO16 pairs in
`asm/nonmatchings/game_115F30/func_150E8B1C.s` address `0x800A1384`,
`0x800A1388` and `0x800A138C`. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds
big-endian `3F85F40A 3EA25D8D 4A45C100` there, reproduced by `1.04651f`,
`0.31712f` and `3240000.0f`. With extern symbols IDO assigned different float
registers; as literals the function matches.

The generated `game_115F30.o` has 0x10 bytes of `.rodata`: these three words
and four zero alignment bytes, with no data relocations. The earlier matched
member reads `0x800A137C` and `0x800A1380` through extern symbols, outside this
mapping. `0x800A1390` onward belongs to the assembly member `func_150E9178` and
keeps its extern symbols. The mapping sits directly after the 0x10-byte
`game_114B80` section at `0x800A1374`. `config/game/us-rodata.ld` maps it as
INFO at `0x800A1384` with a 0x10 extent assertion and a 0xC-byte payload, and
`config/data/us.json` records the owner. No reference assembly, compiler flag
or verifier change is involved.
