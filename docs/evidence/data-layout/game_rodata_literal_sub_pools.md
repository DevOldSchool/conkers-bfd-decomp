# US game rodata literal sub-pools

Four functions reached full-span US `CURRENT (0)` once their `extern f32`
rodata symbols became C float literals: `func_1505F188` (game_83300),
`func_1513A48C` and `func_1513A5E0` (effects/blood) and `func_15194408`
(game_1C1150). Each literal pool lies in ROM apart from the unit's existing
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

`config/data/us.json` records one owner per address and input-section pair.
These units are now split objects, so `finish` compares their own rodata
symbolically, as it already does for the other split units. The integrated
build's ROM comparison and `verify_game_rodata.py` still cover every linked
byte.

## Validation

On the real compiled objects, the splitter reproduces `.text` byte for byte and
rebinds exactly the sites listed above. The four `finish` runs each reported
`CURRENT (0)` and `AGENT_ACTION: STOP_MATCHED`, with source-unit layout,
progress and whitespace gates passed. See the pull request that adds this
record for the tested commit and the clean `verify-batch` result.
