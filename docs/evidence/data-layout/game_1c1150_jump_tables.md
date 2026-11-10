# US game_1C1150 func_15194FF4 switch tables

`func_15194FF4` dispatches twice through jump tables. The raw code
(`asm/nonmatchings/game_1C1150/func_15194FF4.s`, reference text 0x15194FF4) bounds the first
index with `sltiu $at, $t6, 0x7A` and loads `jtbl_800A84C0_game` (HI16/LO16 at
function offsets 0x48/0x50), then bounds the second with
`sltiu $at, $v0, 0x17` and loads `jtbl_800A86A8_game` (offsets 0x68/0x70).
The tables are contiguous in ROM: 0x7A words (0x1E8 bytes) at `0x800A84C0` and
0x17 words (0x5C bytes) at `0x800A86A8`.

The compiled `game_1C1150.o` now has 0x2A0 bytes of `.rodata`: the existing
0x5C bytes of reviewed tables and literals, then the two new tables at object
offsets 0x5C and 0x244, with no alignment padding. Their HI16/LO16 sites are
`.text` offsets 0x139C/0x13A4 and 0x13BC/0x13C4 (the function starts at text
offset 0x1354). Each `R_MIPS_32` table entry, relocated by the text base
(0x15193CA0), equals the checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`)
word for word over all 0x244 bytes at `0x800A84C0..0x800A8703`; the targets
are `0x15195070` and `0x151951D0`.

`scripts/split_game_rodata.py` lists the two ranges
`(0x5C, 0x1E8, 0x139C, 0x13A4)` and `(0x244, 0x5C, 0x13BC, 0x13C4)` and the new
0x2A0 object extent. `config/game/us-rodata.ld` maps them as INFO sections at
`0x800A84C0` and `0x800A86A8` with base symbols and extent assertions;
`config/data/us.json` records the owners. No reference assembly, compiler flag
or verifier change is involved.
