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

## func_15194810 and func_15194BF0 tables (nov14)

Matching `func_15194810` (five-case type switch) and `func_15194BF0` (a 0x58..0xB4 case
switch plus a 0..0x16 switch) makes the compiler emit their tables into the object's
`.rodata` in source order, between the `func_15194794` table and the `func_15194FF4` tables.
The object rodata is now 0x490 bytes; `scripts/split_game_rodata.py` adds
`.rodata.1c1150_5c` (0x14 at 0x800A82D0, sites 0xBAC/0xBB4), `.rodata.1c1150_70` (0x174 at
0x800A82F0, sites 0xF84/0xF8C) and `.rodata.1c1150_1e4` (0x5C at 0x800A8464, sites
0xFC0/0xFC8), and the two `func_15194FF4` tables move to object offsets 0x240 and 0x428
(`.rodata.1c1150_240`, `.rodata.1c1150_428`) with unchanged runtime addresses and sites. The
words 0x800A82E4..0x800A82EF between the first two new tables stay extern float reads of
`func_15194810`. Every table word is a relocated `.text` pointer that the linked-payload
verification compares against the checksum-validated US ROM.

## func_151945CC literal pool growth (round-28)

`func_151945CC` spawns a packet above its target. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_1C1150/func_151945CC.s` address six constants directly after the
`func_15194408` literals, in first-use order: the double `4070E000 00000000` (270.0) at
0x800A82A0, then `40D66666 40151EB8 3F2E147B 408CCCCD 40A9999A` (6.7f, 2.33f, 0.68f,
4.4f, 5.3f) at 0x800A82A8..0x800A82BB, read from the checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20). No other function
reads these addresses. With extern symbols and a `volatile` parameter the deferred
candidate scored CURRENT 180; with the literals and a block-scoped scratch buffer it is
`CURRENT (0)`. `0.5f` and `0.0f` need no rodata.

The compiler emits the new words at object offsets 0x48..0x63, between the
`func_15194408` literals and the `func_15194794` table; the double's offset 0x48 is
8-aligned, matching its ROM spacing of 0xC after 0x800A8294. The `.rodata.1c1150_3c`
literal range therefore grows from 0xC to 0x28 bytes and ends at 0x800A82BC, where the
`func_15194794` table starts. Every later range keeps its runtime address and HI16/LO16
sites but moves 0x1C bytes in the object, so the sections become `.rodata.1c1150_64`,
`_78`, `_8c`, `_200`, `_25c` and `_444`. The object `.rodata` is 0x4A0 bytes with no
alignment tail. `config/game/us-rodata.ld`, its base symbols and extent assertions, and
the `config/data/us.json` section names follow the new offsets.
