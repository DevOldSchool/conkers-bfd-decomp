# US game_E7970 particle constants

`func_150BA55C` spawns particles from a packet at `arg0 + 0x28`. Its raw
HI16/LO16 pairs in `asm/nonmatchings/game_E7970/func_150BA55C.s` load eleven
consecutive words at `0x8009FE30..0x8009FE5B`; no other reference function in
the unit or elsewhere touches them. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds:

| Address | Word | Literal |
| --- | --- | --- |
| `0x8009FE30` | `3EA0EBEE` | `0.3143f` |
| `0x8009FE34` | `3F14BC6B` | `0.58100003f` |
| `0x8009FE38` | `C11528F6` | `-9.3225f` |
| `0x8009FE3C` | `419528F6` | `18.645f` |
| `0x8009FE40` | `3DC08313` | `0.094000004f` |
| `0x8009FE44` | `3D50E561` | `0.051000003f` |
| `0x8009FE48` | `3DA3D70B` | `0.080000006f` |
| `0x8009FE4C` | `3DCCCCCD` | `0.1f` |
| `0x8009FE50` | `3EA5E354` | `0.324f` |
| `0x8009FE54` | `BF1020C5` | `-0.563f` |
| `0x8009FE58` | `3F71E1F4` | `0.944854f` |
| `0x8009FE5C` | `00000000` | alignment padding |

The C source writes each value as the literal above. The generated
`game_E7970.o` has 0x30 bytes of `.rodata`, byte-identical to
`0x8009FE30..0x8009FE5F`, with no data relocations. `config/game/us-rodata.ld`
maps it as an INFO section at `0x8009FE30` with a 0x30 extent assertion and a
0x2C payload; `config/data/us.json` records the owner. No reference assembly,
compiler flag or verifier change is involved.
