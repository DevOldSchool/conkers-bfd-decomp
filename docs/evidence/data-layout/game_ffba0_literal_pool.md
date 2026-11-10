# US game_FFBA0 particle colour table and constants

`func_150D278C` builds a 0x60-byte particle packet. The raw code in
`asm/nonmatchings/game_FFBA0/func_150D278C.s` copies nine bytes from
`0x800A0990` into a stack array (`lbu`/`sb` of byte 8 after word copies),
picks one RGB triple with `random % 3`, and loads five floats from
`0x800A099C..0x800A09AF`. No other reference function touches
`0x800A0990..0x800A09AF`; the literal pool of the unit's unmatched `func_150D2924`
starts at `0x800A09B0`. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds:

| Address | Word | Meaning |
| --- | --- | --- |
| `0x800A0990` | `FFFFFFFF` | colours `{FF,FF,FF}`, `{FF,...` |
| `0x800A0994` | `000000FF` | `...00,00}`, `{00,FF,...` |
| `0x800A0998` | `00000000` | `...00}` and three alignment bytes |
| `0x800A099C` | `40490FDB` | `3.1415927f` |
| `0x800A09A0` | `3ECCCCCD` | `0.4f` |
| `0x800A09A4` | `3E99999A` | `0.3f` |
| `0x800A09A8` | `3E051EB9` | `0.13000001f` |
| `0x800A09AC` | `3E99999A` | `0.3f` (separate word, second use) |

The C source declares the colours as the block-local initialised array
`const u8 choices[9] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00 };`;
IDO places a `const` local initialiser in `.rodata` ahead of the float
literals and copies it to the stack, which is the raw instruction sequence.

The generated `game_FFBA0.o` has 0x20 bytes of `.rodata`
(`ffffffff 000000ff 00000000 40490fdb 3ecccccd 3e99999a 3e051eb9 3e99999a`),
byte-identical to `0x800A0990..0x800A09AF`, with no data relocations.
`config/game/us-rodata.ld` maps it as an INFO section at `0x800A0990` with a
0x20 extent assertion and payload; `config/data/us.json` records the owner.
No reference assembly, compiler flag or verifier change is involved.
