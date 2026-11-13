# US game_39750 float constants

`func_1500D3AC` loads `0.0000002f`, `0.000015259022f`, `3.1415927f`, `0.013f`, `0.0050000004f`,
`1.6f` and `1.6f` in first-use order. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_39750/func_1500D3AC.s` address 0x8009616C..0x80096187; no other reference
function touches them. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds `3456BF95 37800080 40490FDB 3C54FDF4 3BA3D70B 3FCCCCCD 3FCCCCCD`
there, exactly those literals, which reach `CURRENT (0)` in the C source.

The generated `game_39750.o` has 0x20 bytes of `.rodata`: the seven constants and 4 zero alignment
bytes, with no data relocations; no other member of the unit emits rodata. `config/game/us-rodata.ld`
maps it as an INFO section at `0x8009616C` with a 0x20 extent assertion and a 0x1C payload;
`config/data/us.json` records the owner. The informational alignment word `0x80096188` and the
literals of the raw `func_1500DE88` at `0x800961A8..` stay extern reads and are not owned. The source
now includes `game_functions.h` for its header-owned prototypes. No reference assembly, compiler flag
or verifier change is involved.

## func_1500CE4C (round-23)

`func_1500CE4C` loads `0.0000002f`, `0.000015259022f`, `3.1415927f`, `0.013f` and `0.0050000004f`
from 0x80096158..0x8009616B, which the checksum-validated ROM holds as `3456BF95 37800080 40490FDB
3C54FDF4 3BA3D70B`; no other reference function reads them. It precedes `func_1500D3AC` in text and
its words sit directly before that pool in ROM, so the object `.rodata` is now exactly 0x30 bytes
(both pools, no alignment tail) and the placement moves to `0x80096158` with a 0x30 extent and
payload. `0x80096154` belongs to another member and stays an extern read.

## func_1500D8C8 table and split (round-23)

`func_1500D8C8` picks a particle resource from a block-scope `const u16 resources[14]` (0x76, 0x77,
0x78, 0x79, 0x53, 0x3E, 0x3D, 0x39, 0x02, 0x03, 0x4E, 0x4F, 0x50, 0x51), which the checksum-validated
ROM holds at 0x80096104..0x8009611F as `00760077 00780079 0053003E 003D0039 00020003 004E004F
00500051`, and loads `0.000002f`, `0.000015259022f`, `3.1415927f`, `0.013f`, `0.0050000004f`,
`1.6f`, `1.6f` and `0.35f` from 0x80096188..0x800961A7 (`360637BD 37800080 40490FDB 3C54FDF4
3BA3D70B 3FCCCCCD 3FCCCCCD 3EB33333`). No other reference function reads these words.
`Game39750Particle.resource` is now `u16` (`func_1500D3AC` is unaffected).

IDO emits the `const` table ahead of the unit's literal pools, so the object `.rodata` is 0x70
bytes: the 0x1C table, then the `func_1500CE4C`, `func_1500D3AC` and `func_1500D8C8` literals
(0x50, contiguous in ROM at 0x80096158..0x800961A7), then 4 zero alignment bytes. The words between
(0x80096120..0x80096157) belong to other members, so `game_39750.o` joined
`GAME_SPLIT_RODATA_OBJS` and `scripts/split_game_rodata.py` splits it into `.rodata.39750_0`
(0x1C at 0x80096104) and `.rodata.39750_1c` (0x50 at 0x80096158), each with an exact linker size
assertion, replacing the single placement and its payload symbol. The table-like words at
0x800960F0..0x80096103 belong to another raw member and stay unmapped; 0x800961A8.. stay extern reads
of the raw `func_1500DE88`.
