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
