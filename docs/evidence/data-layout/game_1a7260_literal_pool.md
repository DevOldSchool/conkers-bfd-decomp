# US game_1A7260 vertex index table and angle constant

`func_15179DB0` animates two vertex buffers. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_1A7260/func_15179DB0.s` address `0x800A7210` (a byte
index table read inside the inner loop) and `0x800A7218` (the degrees-to-radians
factor). No other reference function touches `0x800A7210..0x800A721F`. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds:

| Address | Word | Meaning |
| --- | --- | --- |
| `0x800A7210` | `04090D0E` | indices 4, 9, 13, 14 |
| `0x800A7214` | `0F111300` | indices 15, 17, 19 and one zero pad byte |
| `0x800A7218` | `3C8EFA35` | `0.017453292f` |
| `0x800A721C` | `00000000` | alignment padding |

The C source declares the table as the function-local
`static const u8 sIndices[] = { 4, 9, 13, 14, 15, 17, 19 };` (the inner loop
runs seven times) and writes the factor as `0.017453292f`. `360.0f` is a `lui`
immediate and needs no rodata.

The generated `game_1A7260.o` has 0x10 bytes of `.rodata` that are byte-identical
to `0x800A7210..0x800A721F`, with no data relocations. `config/game/us-rodata.ld`
maps it as an INFO section at `0x800A7210` with a 0x10 extent assertion and a
0xC payload; `config/data/us.json` records the owner. The next word
(`0x800A7220`, `0.01f`) belongs to another unit. No reference assembly,
compiler flag or verifier change is involved.
