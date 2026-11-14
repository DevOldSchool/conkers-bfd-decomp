# US game_EC420 func_150BF21C constants

`func_150BF21C` uses five float literals whose low halfwords are non-zero:
`0.05f`, `1500.0f`, `0.2f`, `0.4f` and `1.1f`, in that object order (IDO
emits one word per use). The checksum-validated US game-data archive
(game-data base `0x80082B20`) holds
`3D4CCCCD 44BB8000 3E4CCCCD 3ECCCCCD 3F8CCCCD` at `0x800A0110..0x800A0123`,
read with `build/us/manual-attempts/nov02/lit.py`.

The compiled `game_EC420.o` has a 0x20-byte `.rodata` section with exactly
these five words and twelve zero alignment bytes. It has five HI16/LO16 pairs
in `.text` and no data relocations. The neighbouring words
`0x800A0100..0x800A010C` and `0x800A0124..0x800A0130` stay extern symbols
(`D_800A0124`..`D_800A0130` in `func_150BF760`, and others read by raw members),
so only this object's section is mapped. The other raw members of the unit
emit no `.rodata`.

`config/game/us-rodata.ld` places the section at `0x800A0110` as
informational data with `SUBALIGN(4)`, an exact 0x20-byte size assertion and
a 0x14-byte payload-size symbol. `config/data/us.json` records the owner.

## func_150C01DC sub-pool (round-24)

`func_150C01DC` fills a burst record and a spawn record. Its raw HI16/LO16
pairs address 0x800A014C..0x800A016F, which the checksum-validated archive
holds as:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800A014C` | `BFD9374C` | -1.697f |
| `0x800A0150` | `3EFF7CEE` | 0.499f |
| `0x800A0154` | `3F4CCCCD` | 0.8f |
| `0x800A0158` | `3F99999A` | 1.2f |
| `0x800A015C` | `4174C8B5` | 15.299001f |
| `0x800A0160` | `3E8624DE` | 0.26200002f (stored to two spawn fields) |
| `0x800A0164` | `3F85E860` | 1.046154f |
| `0x800A0168` | `43988000` | 305.0f |
| `0x800A016C` | `3F65D40F` | 0.897767f |

With extern symbols the deferred body scored CURRENT 910; as literals it is
`CURRENT (0)`. The other constants (20, 12, 8, 218 and 19) are built with
`lui`. The function follows `func_150BF21C`, so the object's `.rodata` is now
the five `func_150BF21C` words, these nine words and eight zero alignment
bytes (0x40 bytes, 0x38 payload). The words 0x800A0124..0x800A0148 stay extern
reads of the matched `func_150BF760` and `func_150BFFE0`, so game_EC420 becomes
a split unit: `scripts/split_game_rodata.py` splits it into
`.rodata.ec420_0` (0x14 at 0x800A0110) and `.rodata.ec420_14` (0x24 at
0x800A014C), each with an exact linker size assertion, as described in
[game rodata literal sub-pools](game_rodata_literal_sub_pools.md); the object is
listed in `GAME_SPLIT_RODATA_OBJS`, and `config/data/us.json` records both
sections. The words from 0x800A0170 stay extern reads of later members.
