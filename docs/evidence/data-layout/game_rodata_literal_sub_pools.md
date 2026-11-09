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
| blood | 0x0 | 0x204 | 0x800A4350 | table, sites 0x1C / 0x24 | `d321edfc…19b509` |
| blood | 0x204 | 0x5C | 0x800A4554 | table, sites 0x3C / 0x44 | `5147d2f6…6188c3` |
| blood | 0x260 | 0x20 | 0x800A4950 | pool (func_1513A48C, func_1513A5E0) | `3D8F5C29 BF808313 3E820C4A 41BB9169 3CA4A8C1 BEDC28F6 3E8B4396 41A17EFA` |
| game_1C1150 | 0x28 | 0x14 | 0x800A8280 | table, sites 0x78C / 0x794 | `15194440` ×5 |
| game_1C1150 | 0x3C | 0xC | 0x800A8294 | pool (func_15194408) | `3E570A3D 3ECFDF3B 3E99999A` (0.21, 0.406, 0.3) |
| game_1C1150 | 0x48 | 0x14 | 0x800A82BC | table, sites 0xB40 / 0xB48 | `151947F4` ×5 |
| game_64120 | 0x0 | 0x4 | 0x80098648 | pool (func_15038468) | `42652EE0` (57.295776) |
| game_64120 | 0x4 | 0x4 | 0x800986EC | pool (func_1503B708) | `C7C34F80` (-99999.0) |
| game_49D30 | 0x0 | 0x4 | 0x800969C0 | pool (func_1501D044) | `4479C000` (999.0) |
| game_49D30 | 0x4 | 0x4 | 0x800969D0 | pool (func_1501F72C) | `3C23D70A` (0.01) |
| game_1F2730 | 0x0 | 0xC | 0x800AAACC | pool (func_151C577C) | `3DCCCCCD 3E25E354 3E45A1CB` (0.1, 0.162, 0.193) |
| game_1F2730 | 0xC | 0x14 | 0x800AAADC | pool (func_151C577C) | `3DCCCCCD 3F2E978E BED2F1AB 3F736BE3 3A83126F` (0.1, 0.682, -0.412, 0.950865, 0.001) |
| game_90840 | 0x0 | 0xB8 | 0x800996D8 | table, sites 0x450 / 0x458 | 46 action targets |
| game_90840 | 0xB8 | 0x98 | 0x800997E8 | pool (func_15064B94) | 38 words, 0x800997E8..0x8009987F |
| game_173D40 | 0x0 | 0x18 | 0x800A5708 | pool (func_15146A98) | `3CCCCCCC 3CA30553 40FF3B65 BECE5605 3E916873 3F741BDA` |
| game_173D40 | 0x18 | 0x8 | 0x800A5728 | pool (func_15146D60) | `3C40C0C1 3F360B61` (0.011764706, 0.7111111) |
| game_173D40 | 0x20 | 0x18 | 0x800A573C | pool (func_15147318, func_15147478, func_151475D8) | `3BFC0FC1 3F360B61` ×3 |
| game_B4080 | 0x0 | 0x8 | 0x8009DA18 | pool (func_150896EC) | `3F91DE69 AD42C3CA` (f64 0.01745) |
| game_B4080 | 0x8 | 0x20 | 0x8009DA24 | table, sites 0x3028 / 0x3030 | unchanged |
| game_B4080 | 0x28 | 0xFC | 0x8009DA94 | table, sites 0x7B10 / 0x7B18 | unchanged |
| game_B4080 | 0x124 | 0xE4 | 0x8009DB90 | table, sites 0x7BD4 / 0x7BDC | unchanged |
| game_11D830 | 0x0 | 0x4 | 0x800A1854 | pool (func_150F0A24) | `416E147B` (14.88) |
| game_11D830 | 0x4 | 0x20 | 0x800A1878 | pool (func_150F1170) | `3DDF3B65 3E916873 3F7C82E0 3F83D19A 3EAA7EFA 3F039581 3F27EF9E 44008000` |
| game_1E73B0 | 0x0 | 0x48 | 0x800AA718 | pool (func_151BB61C `const` arrays) | `4 4 7 8 18 19 1D 1E 20`, `3F800000 3F800000 3E19999A 3E19999A 3F800000 3F800000 3DC6A7F0 3F800000 3E4CCCCD` |
| game_1E73B0 | 0x48 | 0x4 | 0x800AA7F4 | pool (func_151BB61C) | `3CA3D70B` (0.020000001) |
| game_209B50 | 0x0 | 0x18 | 0x800AB500 | pool (func_151DC97C `const` tables) | `EFE0CD9E 9CA09E9C A0000000 3030309A 69D2D583 91000000` |
| game_209B50 | 0x18 | 0xC | 0x800AB538 | pool (func_151DC97C) | `43C98000 3E439582 3E1A9FBF` (403.0, 0.19100001, 0.15100001) |
| game_177B50 | 0x0 | 0x1C | 0x800A57B0 | pool (func_1514AB5C) | `3D3851EC 3F333333 41B4CCCD 415C9375 4267E042 422ADB23 42ED86A8` |
| game_177B50 | 0x1C | 0x28 | 0x800A5860 | pool (func_1514B8E4) | `4678FC00 45D26800 468FC800 4170B96F 40BBC3D6 4141C87A 3ECAD752 3DD58454 3F050D7E 3EB026C8` |
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
- **blood:** `func_1513A48C` loads 0.07, -1.004, 0.254 and 23.446 from text
  offsets 0x6420..0x64A0. `func_1513A5E0` loads 0.0201, -0.43, 0.272 and
  20.187 from 0x657C..0x65EC, after its `scale` (4.0f, a `lui` immediate) and
  `repeated` (0.0201f) locals were replaced with literals. The two pools are
  adjacent in ROM and in the object, so they form one 0x20 range. The object
  `.rodata` is exactly 0x280 bytes.
- **game_1C1150:** `func_15194408` adds a five-case switch. The raw dispatch
  loads `jtbl_800A8280_game` at 0x1519442C/0x15194434 (text offsets
  0x78C/0x794). All five entries are 0x15194440, the shared spawn block. Its
  literals are loaded at 0x7F4/0x800, 0x804/0x808 and 0x830/0x838. The
  `func_15194794` table keeps 0x800A82BC, but its object offset moves from
  0x28 to 0x48. Its LO16 addend, base symbol and section names now use 0x48.
  The object `.rodata` is 0x60 bytes: 0x5C of payload and 4 zero alignment
  bytes.

- **game_64120:** `func_1503B708` fills six vectors with `-99999.0f`
  (one load, text offset of the pair inside the function at +0xC/+0x10). The
  [existing constant record](game_64120_float_constant.md) covers the first
  word. The words 0x8009864C..0x800986EB belong to unmatched functions and
  keep their extern symbols. The object `.rodata` is 0x10 bytes: 8 of
  payload and 8 zero alignment bytes.
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
