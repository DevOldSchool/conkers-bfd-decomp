# US game_11D030 motion spawn constants

`func_150EFB80` spawns motion particles. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_11D030/func_150EFB80.s` address three consecutive words
at `0x800A1824..0x800A182F`, and no other reference function touches them. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A1824` | `3A83126F` | `0.001f` |
| `0x800A1828` | `C4DC2000` | `-1761.0f` (written `+ -1761.0f`, an `add.s`) |
| `0x800A182C` | `3A83126F` | `0.001f` (second, separate use) |

The generated `game_11D030.o` has 0x10 bytes of `.rodata`
(`3a83126f c4dc2000 3a83126f 00000000`): the constants in load order and 4 zero
alignment bytes, with no data relocations. The alignment bytes fall on
`0x800A1830` (`0.7f`), which the compiled `func_150EFEC8` in this unit reads
through the extern `D_800A1830`; only the 0xC payload is owned and compared.
`config/game/us-rodata.ld` maps the object as an INFO section at `0x800A1824`
with a 0x10 extent assertion and a 0xC payload; `config/data/us.json` records
the owner. No reference assembly, compiler flag or verifier change is involved.
