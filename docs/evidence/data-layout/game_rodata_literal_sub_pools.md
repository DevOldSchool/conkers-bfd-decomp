# US game rodata literal sub-pools

Twelve functions reached full-span US `CURRENT (0)` once their `extern f32`
rodata symbols became C float literals: `func_1505F188` (game_83300),
`func_1513A48C` and `func_1513A5E0` (effects/blood), `func_15194408`
(game_1C1150), `func_1503B708` (game_64120), `func_15064B94` (game_90840) and six
game_173D40 emitters. Each literal pool lies in ROM apart from the unit's existing
reviewed rodata, so mapping the unit's single `.rodata` at one address would
misplace it. `scripts/split_game_rodata.py` now also accepts literal-pool
ranges and splits these three objects. Their compiled `.rodata` holds the
existing tables or pool first, then the new pool, in function order.

## Splitter extension

A `LAYOUTS` range is either a jump table `(offset, size, HI16 site, LO16
site)` or a literal pool `(offset, size)`. Ranges must tile the object's
`.rodata` from offset 0. Bytes after the last range must be zero. Table
ranges keep every earlier check: one reviewed dispatch per table, exact
addends and full `R_MIPS_32` text-pointer coverage.

A pool needs no data relocations. A `.rel.rodata` entry inside one stops the
build, and a literal-only unit may have no `.rel.rodata` at all. The splitter
reads each pool's instruction sites from `.rel.text` instead of a stored list.
An LO16 site belongs to the pool that contains its word-aligned addend. Each
preceding HI16 site, whose addend must be 0, joins the next LO16, following the
REL pairing rule. An LO16 that reuses an earlier `lui` must stay in that `lui`'s
pool. Any other reference, an addend outside every pool, or an unpaired HI16
stops the build.

Each site is rebound to the range's linker-defined
`__game_rodata_<unit>_<offset>_base` (runtime address minus object offset).
Instruction words, addends, `.text` and file offsets of untouched sections do
not change.

`verify_game_rodata.py` is unchanged. Each sub-pool section has the exact
payload size and an exact linker `ASSERT`, so it needs no `_payload_size`
symbol. The verifier compares the full linked section with the
checksum-validated US ROM.

## Placements

ROM SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
0x80082B20. The words below were read with `rom_game_data()` from
`scripts/verify_game_rodata.py`.

| Unit | Object offset | Size | Runtime address | Kind | ROM words / SHA-256 |
| --- | --- | --- | --- | --- | --- |
| game_83300 | 0x0 | 0xC | 0x800994DC | pool (func_1505A770) | `3DCCCCCD 3D4CCCCD 3D4CCCCD` |
| game_83300 | 0xC | 0x8 | 0x8009962C | pool (func_1505F188) | `C61C4000 40533333` (-10000.0, 3.3) |
| game_83300 | 0x14 | 0x4 | 0x80099694 | pool (func_150623F4) | `469C4000` (20000.0) |
| blood | 0x0 | 0x204 | 0x800A4350 | table, sites 0x1C / 0x24 | `d321edfc…19b509` |
| blood | 0x204 | 0x5C | 0x800A4554 | table, sites 0x3C / 0x44 | `5147d2f6…6188c3` |
| blood | 0x260 | 0x54 | 0x800A45B8 | pool (func_151356D4, func_15135DD0) | 8 + 13 words (round-23, below) |
| blood | 0x2B4 | 0x1CC | 0x800A4650 | table, sites 0x3604 / 0x360C | func_15137610 switch (nov14) |
| blood | 0x480 | 0x50 | 0x800A4874 | table, sites 0x4CB0 / 0x4CB8 | 20 targets ([func_15138C80](game_blood_jump_tables.md)) |
| blood | 0x4D0 | 0x34 | 0x800A48C4 | pool (func_15138E98) | 13 words (round-23, below) |
| blood | 0x504 | 0x38 | 0x800A4900 | pool (func_15139768, func_15139D74) | `3DEF9DB3 BE49BA5F 3F2624DE C175F7D0 41F5F7D0 40C3D70A 3E54FDF4 BF353F7D`, `3F2624DE BF353F7D 3E54FDF4 40C3D70A C175F7D0 41F5F7D0` (round-23) |
| blood | 0x53C | 0x68 | 0x800A4950 | pool (func_1513A48C, func_1513A5E0, func_1513A6E0, func_1513ABB8, func_1513B0F8) | `3D8F5C29 BF808313 3E820C4A 41BB9169 3CA4A8C1 BEDC28F6 3E8B4396 41A17EFA`, then `3F2624DE BF353F7D 3E54FDF4 40C3D70A C175F7D0 41F5F7D0` ×3 (round-23) |
| game_1C1150 | 0x28 | 0x14 | 0x800A8280 | table, sites 0x78C / 0x794 | `15194440` ×5 |
| game_1C1150 | 0x3C | 0xC | 0x800A8294 | pool (func_15194408) | `3E570A3D 3ECFDF3B 3E99999A` (0.21, 0.406, 0.3) |
| game_1C1150 | 0x48 | 0x14 | 0x800A82BC | table, sites 0xB40 / 0xB48 | `151947F4` ×5 |
| game_1C1150 | 0x5C | 0x14 | 0x800A82D0 | table, sites 0xBAC / 0xBB4 | func_15194810 switch (nov14) |
| game_1C1150 | 0x70 | 0x174 | 0x800A82F0 | table, sites 0xF84 / 0xF8C | func_15194BF0 cases 0x58..0xB4 (nov14) |
| game_1C1150 | 0x1E4 | 0x5C | 0x800A8464 | table, sites 0xFC0 / 0xFC8 | func_15194BF0 cases 0..0x16 (nov14) |
| game_1C1150 | 0x240 | 0x1E8 | 0x800A84C0 | table, sites 0x139C / 0x13A4 | 0x7A targets ([func_15194FF4](game_1c1150_jump_tables.md)) |
| game_1C1150 | 0x428 | 0x5C | 0x800A86A8 | table, sites 0x13BC / 0x13C4 | 0x17 targets |
| game_64120 | 0x0 | 0x4 | 0x80098648 | pool (func_15038468) | `42652EE0` (57.295776) |
| game_64120 | 0x4 | 0x4 | 0x800986EC | pool (func_1503B708) | `C7C34F80` (-99999.0) |
| game_114B80 | 0x0 | 0x4 | 0x800A1350 | pool (func_150E7C9C) | `3EDCEE77` (0.43150684) |
| game_114B80 | 0x4 | 0x4 | 0x800A1374 | pool (func_150E8470) | `3A83126F` (0.001, [record](game_114b80_float_constant.md)) |
| game_200930 | 0x0 | 0x28 | 0x800AB1D4 | pool (func_151D4408) | 10 words ([record](game_200930_float_constants.md)) |
| game_200930 | 0x28 | 0x24 | 0x800AB21C | pool (func_151D5514, func_151D57F8) | unchanged, 9 words ([record](game_200930_float_constants.md)) |
| game_DC6B0 | 0x0 | 0x18 | 0x8009F7B8 | pool (func_150AF328) | `44D44000 38D1B717 3F7870B9 3F82B114 3DC8B43A 3E3020C5` |
| game_DC6B0 | 0x18 | 0x4 | 0x8009F7D8 | pool (func_150B0094) | `3F333333` (0.7) |
| game_1A20A0 | 0x0 | 0x4 | 0x800A7174 | pool (func_15174BF0) | `3C23D70A` (0.01) |
| game_1A20A0 | 0x4 | 0x10 | 0x800A71AC | pool (func_1517725C) | `3C8EFA35` ×4 ([record](game_1a20a0_float_constants.md)) |
| game_1FA770 | 0x0 | 0x8 | 0x800AAFC0 | pool (func_151CD674) | `BE828F5D BE028F5D` |
| game_1FA770 | 0x8 | 0xC | 0x800AAFE4 | pool (func_151CDB94) | `3E49BA5F 3DCCCCCD 40A26FC1` (0.197, 0.1, 5.076142) |
| game_6B320 | 0x0 | 0x8 | 0x80098918 | pool (func_1503E5F8) | `38D1B717 42652EE0` (0.0001, 57.295776, [record](game_6b320_float_constants.md)) |
| game_6B320 | 0x8 | 0x8 | 0x80098928 | pool (func_1503ECA0) | `3ECCCCCD 3F4CCCCD` (0.4, 0.8) |
| game_F3270 | 0x0 | 0x4 | 0x800A041C | pool (func_150C60D8) | `3E4CCCCD` (0.2, [record](game_burst_velocity_literals.md)) |
| game_F3270 | 0x4 | 0x8 | 0x800A043C | pool (func_150C6460) | `46CCCCCD 3E6C8B44` (26214.4, 0.231) |
| game_F3BA0 | 0x0 | 0x4 | 0x800A045C | pool (func_150C6A08) | `3E4CCCCD` (0.2) |
| game_F3BA0 | 0x4 | 0x8 | 0x800A047C | pool (func_150C6D90) | `46CCCCCD 3E6C8B44` (26214.4, 0.231) |
| game_1D6E80 | 0x0 | 0xC | 0x800A8FE0 | pool (func_151AADF8) | `C6147000 46CCCCCD 3E6C8B44` (-9500, 26214.4, 0.231) |
| game_1D6E80 | 0xC | 0x4 | 0x800A8FF4 | pool (func_151AB3A4) | `3E4CCCCD` (0.2, [record](game_burst_velocity_literals.md)) |
| game_2062D0 | 0x0 | 0x10 | 0x800AB470 | pool (func_151DA08C) | `3E4CCCCD 3DCCCCCD 3E4CCCCD 3DCCCCCD` (0.2, 0.1 ×2; round-23) |
| game_2062D0 | 0x10 | 0x18 | 0x800AB480 | pool (func_151DA368) | `3E19999A 3DCCCCCD 43EB8000 461DE800 38D1B717 3A83126F` |
| game_2062D0 | 0x28 | 0x4 | 0x800AB49C | pool | `3F8CCCCD` (1.1, [record](game_2062d0_float_constant.md)) |
| holtenrope | 0x0 | 0xC | 0x800AA3A0 | pool (func_151B3CF0) | `38D1B717 40490FDB 3EB2B8C3` |
| holtenrope | 0xC | 0x8 | 0x800AA3C4 | pool | `3DCCCCCD 435E38E4` ([record](holtenrope_float_constants.md)) |
| game_179F30 | 0x0 | 0x2EC | 0x800A59AC | table, sites 0x14 / 0x1C | 187 targets (func_1514CA80, [record](game_179f30_jump_tables.md); round-23) |
| game_179F30 | 0x2EC | 0xD8 | 0x800A5C98 | table, sites 0x200 / 0x208 | 54 targets (func_1514CA80; round-23) |
| game_179F30 | 0x3C4 | 0x4C | 0x800A5D70 | table, sites 0x518 / 0x520 | 19 targets (func_1514CA80; round-23) |
| game_179F30 | 0x410 | 0x28 | 0x800A5DBC | table, sites 0x598 / 0x5A0 | 10 targets (func_1514CA80; round-23) |
| game_179F30 | 0x438 | 0x10 | 0x800A5DF4 | pool (func_1514D64C) | `358637BD 3F4CCCCD 3F19999A 358637BD` ([record](game_179f30_float_constants.md)) |
| game_179F30 | 0x448 | 0x28 | 0x800A5E20 | table, sites 0x1FB4 / 0x1FBC | unchanged (func_1514EA1C, [record](manual_batch_jump_tables.md)) |
| game_981E0 | 0x0 | 0x38 | 0x80099D54 | table, sites 0x3170 / 0x3178 | 14 targets ([record](game_981e0_constructor_literal_pool.md)) |
| game_981E0 | 0x38 | 0x10C | 0x80099D8C | pool (func_1506DE84 .. func_1506F54C) | unchanged ([record](game_981e0_constructor_literal_pool.md)) |
| game_981E0 | 0x144 | 0x80 | 0x80099EAC | pool (func_15070898) | 32 words ([record](game_981e0_constructor_literal_pool.md)) |
| game_49D30 | 0x0 | 0x4 | 0x800969C0 | pool (func_1501D044) | `4479C000` (999.0) |
| game_49D30 | 0x4 | 0x4 | 0x800969D0 | pool (func_1501F72C) | `3C23D70A` (0.01) |
| game_39750 | 0x0 | 0x1C | 0x80096104 | pool (func_1500D8C8 `const u16` table) | `00760077 00780079 0053003E 003D0039 00020003 004E004F 00500051` ([record](game_39750_float_constants.md); round-23) |
| game_39750 | 0x1C | 0x50 | 0x80096158 | pool (func_1500CE4C, func_1500D3AC, func_1500D8C8) | 5 + 7 + 8 words ([record](game_39750_float_constants.md); round-23) |
| game_1865D0 | 0x0 | 0x20 | 0x800A63C4 | pool (func_15159C08) | 8 words ([record](game_1865d0_float_constants.md); round-23) |
| game_1865D0 | 0x20 | 0xC | 0x800A6414 | pool (func_1515AB88) | `3DA3D70A 3DCCCCCD 3E19999A` (unchanged) |
| game_197F20 | 0x0 | 0x8 | 0x800A6DBC | pool (func_1516CC58) | `3C23D70A 3C8EFA35` (0.01, 0.017453292; round-23) |
| game_197F20 | 0x8 | 0x1C | 0x800A6DC8 | pool (func_1516CC58) | `C0568000 00000000` (f64 -90.0), `3C8EFA35 40490FDB 3F933333 40490FDB 3F851EB8` |
| game_1F2730 | 0x0 | 0xC | 0x800AAACC | pool (func_151C577C) | `3DCCCCCD 3E25E354 3E45A1CB` (0.1, 0.162, 0.193) |
| game_1F2730 | 0xC | 0x14 | 0x800AAADC | pool (func_151C577C) | `3DCCCCCD 3F2E978E BED2F1AB 3F736BE3 3A83126F` (0.1, 0.682, -0.412, 0.950865, 0.001) |
| game_90840 | 0x0 | 0xB8 | 0x800996D8 | table, sites 0x450 / 0x458 | 46 action targets |
| game_90840 | 0xB8 | 0x98 | 0x800997E8 | pool (func_15064B94) | 38 words, 0x800997E8..0x8009987F |
| game_173D40 | 0x0 | 0x18 | 0x800A5708 | pool (func_15146A98) | `3CCCCCCC 3CA30553 40FF3B65 BECE5605 3E916873 3F741BDA` |
| game_173D40 | 0x18 | 0x8 | 0x800A5728 | pool (func_15146D60) | `3C40C0C1 3F360B61` (0.011764706, 0.7111111) |
| game_173D40 | 0x20 | 0x18 | 0x800A573C | pool (func_15147318, func_15147478, func_151475D8) | `3BFC0FC1 3F360B61` ×3 |
| game_131F30 | 0x0 | 0xC | 0x800A23B4 | pool (func_151050B0) | `3D23D70B 3D8F5C29 3EA66667` (0.040000003, 0.07, 0.32500002) |
| game_131F30 | 0xC | 0x18 | 0x800A23EC | pool (func_151058B4) | `3AAA64C3 3AF9096B 40ECCCCC 4122147B 3FBE3540 C043126F` |
| game_111670 | 0x0 | 0x4 | 0x800A1060 | pool (func_150E42F8) | `C61C4000` (-10000.0) |
| game_111670 | 0x4 | 0x34 | 0x800A112C | pool (func_150E4E04, func_150E5558) | unchanged, 13 words ([record](game_111670_float_constants.md)) |
| game_16EE20 | 0x2A4 | 0x4 | 0x800A56A0 | pool (func_1514470C) | `40C90FDB` (6.2831855) |
| game_B4080 | 0x0 | 0x8 | 0x8009DA18 | pool (func_150896EC) | `3F91DE69 AD42C3CA` (f64 0.01745) |
| game_B4080 | 0x8 | 0x20 | 0x8009DA24 | table, sites 0x3028 / 0x3030 | unchanged |
| game_B4080 | 0x28 | 0x8 | 0x8009DA60 | pool (func_1508B9BC) | `3F4CCCCD 3B808081` (0.8, 0.003921569; nov14) |
| game_B4080 | 0x30 | 0xFC | 0x8009DA94 | table, sites 0x7B10 / 0x7B18 | unchanged |
| game_B4080 | 0x12C | 0xE4 | 0x8009DB90 | table, sites 0x7BD4 / 0x7BDC | unchanged |
| game_11D830 | 0x0 | 0x4 | 0x800A1854 | pool (func_150F0A24) | `416E147B` (14.88) |
| game_11D830 | 0x4 | 0x20 | 0x800A1878 | pool (func_150F1170) | `3DDF3B65 3E916873 3F7C82E0 3F83D19A 3EAA7EFA 3F039581 3F27EF9E 44008000` |
| game_1E73B0 | 0x0 | 0x48 | 0x800AA718 | pool (func_151BB61C `const` arrays) | `4 4 7 8 18 19 1D 1E 20`, `3F800000 3F800000 3E19999A 3E19999A 3F800000 3F800000 3DC6A7F0 3F800000 3E4CCCCD` |
| game_1E73B0 | 0x48 | 0x4 | 0x800AA7F4 | pool (func_151BB61C) | `3CA3D70B` (0.020000001) |
| game_209B50 | 0x0 | 0x18 | 0x800AB500 | pool (func_151DC97C `const` tables) | `EFE0CD9E 9CA09E9C A0000000 3030309A 69D2D583 91000000` |
| game_209B50 | 0x18 | 0xC | 0x800AB538 | pool (func_151DC97C) | `43C98000 3E439582 3E1A9FBF` (403.0, 0.19100001, 0.15100001) |
| game_177B50 | 0x0 | 0x1C | 0x800A57B0 | pool (func_1514AB5C) | `3D3851EC 3F333333 41B4CCCD 415C9375 4267E042 422ADB23 42ED86A8` |
| game_177B50 | 0x1C | 0x80 | 0x800A5808 | pool (func_1514B034, func_1514B364, func_1514B8E4) | 11 + 11 + 10 words ([record](game_177b50_float_constants.md); merged round-23) |
| effects_sight | 0x0 | 0x18 | 0x800AAC58 | pool (func_151C899C) | `43F58000 3D77CED9 3D563886 3F32B021 BEE3D70B 3EE1CAC1` (491.0, 0.0605, 0.0523, 0.698, -0.44500002, 0.441; round-23) |
| effects_sight | 0x18 | 0xCC | 0x800AADBC | table, sites 0x2A84 / 0x2A8C | func_151C9BA0 cases 9..0x3B ([record](effects_sight_float_constant.md); round-23) |
| effects_sight | 0xE4 | 0x4 | 0x800AAEBC | pool (func_151CBC60) | `3CEA0EA1` (0.028571429) |
| game_58F80 | 0x0 | 0x100 | 0x80096DF8 | table, sites 0x2068 / 0x2070 | unchanged (func_1502DB20) |
| game_58F80 | 0x100 | 0x18 | 0x80096F04 | table, sites 0x3040 / 0x3048 | `1502EB24 1502EB24 1502EB8C 1502EB5C 1502EBB0 1502EBFC` (func_1502EAFC) |

The blood table hashes are SHA-256
`d321edfcf0ef657c343364be6b03428e24a84df3a377f3acee9bfa8fee19b509` and
`5147d2f64bc55d8d1c9690a7373e01ce362d5350f5b0823d7a904542926188c3`.
The [blood switch record](game_blood_jump_tables.md) describes those tables.
The 0x204/0x5C split follows its 0x81 and 0x17 entry counts. Both tables
keep their runtime addresses.

- **game_83300:** The [existing constant record](game_83300_float_constants.md)
  covers the first pool. The second pool comes from `initial = -10000.0f` and
  the 3.3f store in `func_1505F188`, loaded at text offsets 0x9368/0x936C and
  0x9380/0x9394. The words between the pools (0x800994E8..0x8009962B) belong
  to other functions and keep their extern symbols. The object `.rodata` is
  0x20 bytes: 0x14 of payload and 12 zero alignment bytes, which the splitter
  checks. The former 0xC payload-size symbol is gone; the first pool section
  is now exactly 0xC.
  `func_150623F4` adds a third pool: it compares squared distances with
  `20000.0f` inside a loop, and the reference loads the word once into
  callee-saved `$fs1` (`lui`/`lwc1` at `1506262C`/`15062644`). With
  `extern f32 D_80099694` IDO keeps the address in an s-register and reloads
  the value every iteration; as a literal the function is `CURRENT (0)`. The
  ROM word at 0x80099694 is `469C4000`. The literal follows the two earlier
  pools at object offset 0x14, so the object `.rodata` stays 0x20 bytes: 0x18
  of payload and 8 zero alignment bytes. The words between
  (0x80099634..0x80099693) keep their extern symbols.
- **blood:** `func_1513A48C` loads 0.07, -1.004, 0.254 and 23.446 from text
  offsets 0x6420..0x64A0. `func_1513A5E0` loads 0.0201, -0.43, 0.272 and
  20.187 from 0x657C..0x65EC, after its `scale` (4.0f, a `lui` immediate) and
  `repeated` (0.0201f) locals were replaced with literals. The two pools are
  adjacent in ROM and in the object, so they form one 0x20 range. The object
  `.rodata` is exactly 0x280 bytes.
  Round-23: the blood-burst emitters `func_15139D74` and `func_1513A6E0` each
  load `0.64900005f`, `-0.708f`, `0.208f`, `6.12f`, `-15.373001f` and
  `30.746002f` (first-use order, one word each); the checksum-validated ROM
  holds `3F2624DE BF353F7D 3E54FDF4 40C3D70A C175F7D0 41F5F7D0` at both
  0x800A4920..0x800A4937 and 0x800A4970..0x800A4987, and no other reference
  function reads them. The words 0x800A4938..0x800A494F stay extern reads of
  the matched `func_1513A24C`, so the pools are three ranges in text order:
  `.rodata.blood_47c` (0x18 at 0x800A4920), the existing spray pool renamed
  `.rodata.blood_494` (0x20, runtime address 0x800A4950 unchanged) and
  `.rodata.blood_4b4` (0x18 at 0x800A4970). The object `.rodata` is 0x4D0
  bytes: 0x4CC of payload and 4 zero alignment bytes. `Blood1380B4State`
  gains named `field_3B`, `field_14C` and `field_150` members in its padding
  (size and other offsets unchanged), and `func_1513A5E0` takes its second
  argument as `u8` (definition and prototype), which both emitters pass and
  which keeps that function at `CURRENT (0)`.
  Later in round-23 the remaining blood emitters joined, and contiguous ROM
  pools were merged into single ranges (the ranges above are the final
  layout; the object `.rodata` is exactly 0x5B0 bytes with no alignment tail):
  `func_15139768` (proto `arg4` now `u8`) loads `0.117000006f`,
  `-0.19700001f`, `0.64900005f`, `-15.373001f`, `30.746002f`, `6.12f`,
  `0.208f` and `-0.708f` from 0x800A4900..0x800A491F, directly before the
  `func_15139D74` words, so both form `.rodata.blood_504`. `func_1513ABB8`
  (proto `arg4` now `u8`) and `func_1513B0F8` load the same six burst words
  as `func_1513A6E0` from 0x800A4988..0x800A499F and 0x800A49A0..0x800A49B7,
  extending the spray pool to `.rodata.blood_53c` (0x68 at 0x800A4950).
  `func_1513B0F8` reuses `BloodParticlePacket` (its probe-local burst struct
  had the same 0x7C layout). `func_15138E98` (proto `u8` `arg2`/`arg4`) loads
  `3F2624DE C175F7D0 41F5F7D0 40C3D70A 3E54FDF4 BF353F7D 3F2624DE 40E4CCCC
  412E3D70 4240A1CB C1C0A1CB 3EA56042 BFB5E355` from 0x800A48C4..0x800A48F7;
  0x800A48F8..0x800A48FF stay extern reads of the raw `func_15139578`, so it is
  its own range. `func_151356D4` loads `0.001f` ×4, `0.0001f` ×2, `1300.0f`
  and `0.001f` (`3A83126F` ×4, `38D1B717` ×2, `44A28000`, `3A83126F`) from
  0x800A45B8..0x800A45D7, and `func_15135DD0` (`u8` colour arguments in the
  `func_151DB5D0`, `func_151DA6F8` and `func_151D9014` prototypes) loads
  `C61C4000 461C4000 3A83126F 3F8147AE 3D27EF9E 3A83126F 441A8000 3F81A9FC
  40866667 3FF33333 3A83126F 3E16872B BE9A9FBF` from the adjacent
  0x800A45D8..0x800A460B; 0x800A45B0..0x800A45B7 stay extern reads. The two
  table ranges follow: the 0x800A4650 and 0x800A4874 tables
  moved to object offsets 0x2B4 and 0x480 with their runtime addresses and
  HI16/LO16 sites unchanged.
- **game_1C1150:** `func_15194408` adds a five-case switch. The raw dispatch
  loads `jtbl_800A8280_game` at 0x1519442C/0x15194434 (text offsets
  0x78C/0x794). All five entries are 0x15194440, the shared spawn block. Its
  literals are loaded at 0x7F4/0x800, 0x804/0x808 and 0x830/0x838. The
  `func_15194794` table keeps 0x800A82BC, but its object offset moves from
  0x28 to 0x48. Its LO16 addend, base symbol and section names now use 0x48.
  The object `.rodata` is 0x60 bytes: 0x5C of payload and 4 zero alignment
  bytes.

- **game_16EE20:** `func_1514470C` case 1 multiplies two random values by
  `6.2831855f`. The reference loads the word once (HI16/LO16 at unit text
  offsets 0x3068/0x306C) and uses it for both products. With
  `extern f32 D_800A56A0` the function scores CURRENT 80 (the constant and
  `radiusX` swap `$f2`/`$f16`); as a literal it is `CURRENT (0)`. The literal
  follows the five reviewed tables in the object, at offset 0x2A4, and the
  object `.rodata` stays 0x2B0 bytes: 0x2A8 of payload and 8 zero alignment
  bytes. The neighbouring words 0x800A5694..0x800A569F and 0x800A56A4 are read
  by other members through externs and are not part of this range.
- **game_64120:** `func_1503B708` fills six vectors with `-99999.0f`
  (one load, text offset of the pair inside the function at +0xC/+0x10). The
  [existing constant record](game_64120_float_constant.md) covers the first
  word. The words 0x8009864C..0x800986EB belong to unmatched functions and
  keep their extern symbols. The object `.rodata` is 0x10 bytes: 8 of
  payload and 8 zero alignment bytes.
- **game_197F20 (round-23):** `func_1516CC58` loads `0.01f`, `0.017453292f`, the double
  `-90.0`, then `0.017453292f`, `3.1415927f`, `1.15f`, `3.1415927f` and `1.04f` in first-use
  order. The checksum-validated ROM holds them at 0x800A6DBC..0x800A6DE3, with the double at the
  8-aligned 0x800A6DC8 after a zero padding word at 0x800A6DC4; no other reference function reads
  these words. In the object the double falls at 8-aligned offset 0x8 directly after the two
  floats, so the pool is split around the ROM padding word: 0x8 bytes at 0x800A6DBC and 0x1C bytes
  at 0x800A6DC8. 0x800A6DB8 and 0x800A6DE4.. stay extern reads of the raw `func_1516B6BC` and
  `func_1516D0CC`. The unit had no rodata mapping; `game_197F20.o` joined
  `GAME_SPLIT_RODATA_OBJS`. The object `.rodata` is 0x30 bytes: 0x24 of payload and 12 zero
  alignment bytes.
- **game_49D30:** `func_1501F72C` scales its key time by `0.01f` once before
  its binary search loop. As an `extern` IDO reloads it inside the loop; as a
  literal it is hoisted and the function matches. The checksum-validated ROM
  holds `3C23D70A` at 0x800969D0 (HI16/LO16 at raw 0x1501F988/0x1501F990).
  The [existing constant record](game_49d30_float_constants.md) covers the
  first word. The words 0x800969C4..0x800969CF belong to the unmatched
  `func_1501EA18` and `func_1501EC38` and keep their extern symbols. The
  object `.rodata` is 0x10 bytes: 8 of payload and 8 zero alignment bytes.
- **game_1F2730:** `func_151C577C` hoists eight literals out of loops that
  contain calls; as `extern` symbols IDO reloads them and the function does
  not match. The checksum-validated ROM holds the nine words `3DCCCCCD
  3E25E354 3E45A1CB 3DCCCCCD 3DCCCCCD 3F2E978E BED2F1AB 3F736BE3 3A83126F` at
  0x800AAACC..0x800AAAEF. The raw code loads every word except 0x800AAAD8
  (HI16/LO16 pairs in `asm/nonmatchings/game_1F2730/func_151C577C.s`); no
  function in any unit references 0x800AAAD8. Its value (0.1f) and position
  inside the function's first-use order suggest a literal of the original
  source whose use IDO removed, but no C form tried reproduces it, so the
  object pool has eight words and is split around it: 0xC bytes at 0x800AAACC
  and 0x14 bytes at 0x800AAADC. The unowned ROM word is supplied by the
  original data archive. The object `.rodata` is exactly 0x20 bytes. The
  matched `func_151C5E74` keeps CURRENT (0) after `func_151D9014`'s local
  prototype took a `u8` 15th parameter (it already passes a `u8` there).
- **game_90840:** `func_15064B94` loads 38 literals (0.4, 0.6, 2.6, 0.3,
  0.2 and 0.65, each use its own word, as IDO emits them) from
  0x800997E8..0x8009987F in first-use order; the full 0x98-byte range was
  compared with the checksum-validated ROM by `verify_game_rodata.py`. The
  [action table](game_90840_jump_table.md) keeps 0x800996D8 and object offset
  0; its HI16/LO16 sites are text offsets 0x450/0x458 in `func_150636F0`.
  The words 0x80099790..0x800997E7 belong to unmatched functions. The object
  `.rodata` is exactly 0x150 bytes.

- **game_131F30:** `func_151058B4` loads 0.0013, 0.0018999999, 7.3999996,
  10.13, 1.4860001 and -3.048 (written `+ -3.048f`) from 0x800A23EC..0x800A2403
  in first-use order; the checksum-validated ROM holds exactly those words and
  no other reference function reads them. The words 0x800A23C0..0x800A23EB stay
  extern symbols of the matched `func_1510558C`, so the unit's earlier
  `func_151050B0` pool at 0x800A23B4 and the new pool are two ranges. The
  object `.rodata` is 0x30 bytes: 0x24 of payload and 0xC zero alignment bytes.

- **game_173D40:** Six effect emitters matched once their `void *volatile`
  parameter hack became an early `return` on `arg0->0x1D4 == 0` (the raw
  reloads `arg0` from its home for the call argument because the test and
  the call sit in different blocks) and their extern floats became literals.
  `func_15146A98` loads 0.024999999, 0.0199, 7.9760003, -0.40300003, 0.284
  and 0.95355; `func_15146D60` loads 0.011764706 and 0.7111111; the three
  `func_15141F78` emitters each load 0.0076923077 and 0.7111111.
  `func_15147040` uses only `lui` immediates. The words 0x800A5720..0x800A5727
  and 0x800A5730..0x800A573B stay extern symbols of the matched
  `func_15146BF8` and `func_151470FC`, so the pools are three ranges. The
  object `.rodata` is 0x40 bytes: 0x38 of payload and 8 zero alignment bytes.

- **game_B4080:** `func_150896EC` converts a rail angle from degrees with the
  double literal `0.01745` inside a loop. As an `extern` IDO reloads it every
  iteration (CURRENT 1405); as a literal it is hoisted and the function
  matches. The checksum-validated ROM holds `3F91DE69 AD42C3CA` (exactly the
  double 0.01745, not pi/180) at 0x8009DA18, the 8-aligned word pair after
  this function's 999.0f (0x8009DA0C), 0.017f (0x8009DA10) and a padding word
  (0x8009DA14). The two floats stay extern symbols; the match is identical
  either way, and as literals the padding word would misplace the double in
  the object. The literal load (HI16/LO16 at text offsets 0x2D4C/0x2D54 of the
  integrated object) precedes the first table dispatch (0x3028), so the pool is
  object offset 0 and the three tables move from 0/0x20/0x11C to
  0x8/0x28/0x124. Their runtime addresses and dispatch sites are unchanged;
  base symbols, section names and `config/data/us.json` sections follow the
  new offsets. The object `.rodata` is 0x210 bytes: 0x208 of payload and 8
  zero alignment bytes.

- **game_B4080 (nov14):** `func_1508B9BC` scores route weights with `0.8f` and `1/255`
  (`0.003921569f`). Its HI16/LO16 pairs address 0x8009DA60/0x8009DA64, which hold
  `3F4CCCCD 3B808081`; the deferred body scored CURRENT 3260 with externs and is
  `CURRENT (0)` with literals. They follow the 0x8009DA24 table in object order, so the
  layout gains a `(0x28, 0x8)` pool and the two later tables move to object offsets 0x30
  and 0x12C (`.rodata.b4080_30`, `.rodata.b4080_12c`); their runtime addresses and HI16/LO16
  sites are unchanged. 0x8009DA44..0x8009DA5F and 0x8009DA68.. stay extern reads.
- **game_11D830:** `func_150F1170` loads 0.109000005, 0.284, 0.986372,
  1.029834, 0.333, 0.514, 0.656 and 514.0 (each checked bit-for-bit against
  the ROM; `0.109f` would round to `3DDF3B64`) from 0x800A1878..0x800A1897 in
  first-use order. The [existing constant record](game_11d830_float_constant.md)
  covers the first pool. The words 0x800A1858..0x800A1877 belong to other
  functions and keep their extern symbols, so the unit's single `.rodata`
  placement became two ranges and `game_11D830.o` joined
  `GAME_SPLIT_RODATA_OBJS`; the former payload-size symbol is gone. The object
  `.rodata` is 0x30 bytes: 0x24 of payload and 12 zero alignment bytes.

- **game_1E73B0:** `func_151BB61C` passes two nine-element tables to
  `func_15151D6C`: `const s32 indices[9]` (4, 4, 7, 8, 24, 25, 29, 30, 32) and
  `const f32 factors[9]` (1.0, 1.0, 0.15, 0.15, 1.0, 1.0, 0.097, 1.0, 0.2).
  IDO emits them as `.rodata` in declaration order, matching the
  checksum-validated ROM words at 0x800AA718..0x800AA75F. It also loads
  `0.020000001f` once and uses it twice (as an extern IDO reloads it). That
  word sits at 0x800AA7F4 between this function's other float constants,
  which stay extern symbols because each is used once and compiles the same
  either way. The unit had no rodata mapping; it is now a split object with
  two ranges. The object `.rodata` is 0x50 bytes: 0x4C of payload and 4 zero
  alignment bytes; the HI16/LO16 sites are standalone text offsets
  0x394/0x398, 0x3B0/0x3B4 and 0x3E4/0x3E8.

- **game_209B50:** `func_151DC97C` picks spark colours from two block-scope
  `const u8 [3][3]` tables (EF E0 CD / 9E 9C A0 / 9E 9C A0 and 30 30 30 /
  9A 69 D2 / D5 83 91). IDO pads each 9-byte table to a word, giving exactly
  the ROM words at 0x800AB500..0x800AB517 including their zero tails. Its
  loop-hoisted `403.0f`, `0.19100001f` and `0.15100001f` must be literals and
  sit at 0x800AB538..0x800AB543. The words between (0x800AB518..0x800AB537)
  belong to the unmatched `func_151DC6A0` and to this function's once-used
  floats, which stay extern symbols. The unit had no rodata mapping; it is now
  a split object with two ranges. The object `.rodata` is 0x30 bytes: 0x24 of
  payload and 12 zero alignment bytes.

`config/data/us.json` records one owner per address and input-section pair.
These units are now split objects, so `finish` compares their own rodata
symbolically, as it already does for the other split units. The integrated
build's ROM comparison and `verify_game_rodata.py` still cover every linked
byte.

## Full-unit proof

`linked_aliases.prepare_game` proves a split GAME unit as the build links it.
The unsplit object's rodata relocations and text references are checked first,
as for a single placement. `split_game_rodata.split` then splits the object,
and each `.rodata.<unit>_<offset>` sub-pool is linked at its reviewed address.
Each `__game_rodata_<unit>_<offset>_base` symbol is defined as that address minus
the offset. `game_rodata_split_placements` accepts a unit only when:

- its object rodata extent equals the `LAYOUTS` extent;
- the script has no whole-unit `.rodata` input;
- every range has one placement, one exact `SIZEOF` assertion and one base
  definition with the matching offset;
- every address is word aligned.

The complete linked `.text` must equal the unit's ROM bytes, which proves every
rebased HI16/LO16 pair. Each linked sub-pool must also equal ROM game data at
its address.

This lets `finish` prove terminal padding in split units. `func_15195738` is
the last member of `game_1C1150`. Its 120-byte span ends in 8 zero alignment
bytes that only the complete object contains, so it reached `CURRENT (0)` once
the unit could be linked.

- **game_58F80:** `func_1502EAFC` matched as a six-case `switch`, so the
  object now emits its jump table after the reviewed `func_1502DB20` table.
  The raw dispatch (`sltiu at,t7,6`, then `lui`/`lw` of `jtbl_80096F04_game` at
  text offsets 0x3040/0x3048) addresses `0x80096F04`, whose six ROM words are the
  case targets listed above. The 12 bytes between the tables
  (`0x80096EF8`..`0x80096F03`: 0.1, 0.1, 20000.0) are `func_1502DF38` literals
  still read through externs, so the unit is split at 0x100. The object
  `.rodata` is 0x120 bytes: 0x118 of payload and 8 zero alignment bytes.

## Validation

On the real compiled objects, the splitter reproduces `.text` byte for byte and
rebinds exactly the sites listed above. The four `finish` runs each reported
`CURRENT (0)` and `AGENT_ACTION: STOP_MATCHED`, with source-unit layout,
progress and whitespace gates passed. See the pull request that adds this
record for the tested commit and the clean `verify-batch` result.
