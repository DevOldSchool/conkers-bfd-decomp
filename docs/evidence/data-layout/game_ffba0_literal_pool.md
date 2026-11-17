# US game_FFBA0 particle colour table and constants

`func_150D278C` builds a 0x60-byte particle packet. The raw code in
`asm/nonmatchings/game_FFBA0/func_150D278C.s` copies nine bytes from
`0x800A0990` into a stack array (`lbu`/`sb` of byte 8 after word copies),
picks one RGB triple with `random % 3`, and loads five floats from
`0x800A099C..0x800A09AF`. No other reference function touches
`0x800A0990..0x800A09AF`; the literal pool of `func_150D2924`
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

## func_150D2924 constants (round-28)

`func_150D2924` emits sparks while its emitter counter exceeds one. Its raw
HI16/LO16 pairs in `asm/nonmatchings/game_FFBA0/func_150D2924.s` load two
separate words, `0x800A09B0` and `0x800A09B4`, both `3A83126F` in the same ROM:
`0.001f`, once for each of the two `(random * 80.0f + 50.0f) * 0.001f` products
(IDO emits a pool word per use). The following words `0x800A09B8`/`0x800A09BC`
are zero. No other reference function reads them. The other float operands
(`9.0f`, `22.0f`, `25.0f`, `50.0f`, `1024.0f`, `-2560.0f`, `2048.0f`,
`1536.0f`, `768.0f`, `80.0f`, `1.0f`) are built with `lui`. The raw function was
never matched before; with these literals and local emitter, spark and spawn
records it is `CURRENT (0)`. Once it was C, the preserved `func_150D2D6C`
candidate compiled at its original offset in file context and is also
`CURRENT (0)`; it emits no rodata. Every function of the unit is now matched.

## Object layout

The generated `game_FFBA0.o` has 0x30 bytes of `.rodata`
(`ffffffff 000000ff 00000000 40490fdb 3ecccccd 3e99999a 3e051eb9 3e99999a
3a83126f 3a83126f` and 8 zero alignment bytes), whose 0x28-byte payload is
byte-identical to `0x800A0990..0x800A09B7`, with no data relocations.
`config/game/us-rodata.ld` maps it as an INFO section at `0x800A0990` with a
0x30 extent assertion and a 0x28 payload; `config/data/us.json` records the
owner. No reference assembly, compiler flag or verifier change is involved.
