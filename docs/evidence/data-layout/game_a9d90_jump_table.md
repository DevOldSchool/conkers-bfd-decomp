# US switch tables for game_A9D90

The unit's `.rodata` holds three word-sized jump tables in function order.
Raw HI16/LO16 address pairs identify each table in the separately loaded US
game-data archive (game-data base `0x80082B20`).

| Table | Function | Selectors | Entries | Bytes |
| --- | --- | --- | ---: | ---: |
| `0x8009B6DC` | `func_1507D754` | `0x77`–`0x91` | 27 | `0x6C` |
| `0x8009B748` | `func_1507D754` | `0x05`–`0x53` | 79 | `0x13C` |
| `0x8009B884` | `func_1507DF10` | `0x04`–`0x09` | 6 | `0x18` |

`func_1507D754` switches on the actor kind byte at `+0x04`. IDO splits its
sparse cases into two range tables plus direct compares for `0xAD`–`0xAF`.
Selectors without a case resolve to the shared default return at
`0x1507DB1C` (21 entries in the first table, 64 in the second). The other
targets are:

| Target | Selectors |
| --- | --- |
| `0x1507D7F8` | `0x7F` |
| `0x1507D810` | `0x10`, `0x38`, `0x91` |
| `0x1507D820` | `0x3A`, `0x3D` |
| `0x1507D830` | `0x4A` |
| `0x1507D848` | `0x47` |
| `0x1507D860` | `0x25` |
| `0x1507D89C` | `0x79` |
| `0x1507D8B4` | `0x05` |
| `0x1507D8D4` | `0x53` |
| `0x1507D8F8` | `0x90` |
| `0x1507D930` | `0x28`, `0x77` |
| `0x1507DA88` | `0x0D` |
| `0x1507DAA0` | `0x20` |
| `0x1507DADC` | `0x4F`, `0x83` |
| `0x1507DAF4` | `0x34` |
| `0x1507DB0C` | `0x44` |

`func_1507DF10` dispatches selectors 4 through 9:

| Selector | Target |
| --- | --- |
| 4 | `0x1507DFBC` |
| 5 | `0x1507DFBC` |
| 6 | `0x1507DF88` |
| 7 | `0x1507DF88` |
| 8 | `0x1507DF58` |
| 9 | `0x1507DF34` |

The tables are contiguous: `0x8009B6DC + 0x6C = 0x8009B748` and
`0x8009B748 + 0x13C = 0x8009B884`. With both functions in C, the generated
`build/us/src/game/game_A9D90.o` has a 448-byte `.rodata` section (0x1C0,
already 16-byte aligned, so no alignment bytes) with 112 `.text` word
relocations. `./conker game-build` reported `.game_rodata_a9d90: 448 linked
payload bytes at 0x8009B6DC match US ROM data`, compared with `rom_game_data`
and `verify_bytes` from `scripts/verify_game_rodata.py` against the
checksum-validated US ROM. The remaining raw members of the unit do not load
rodata in this range.

The mapping in `config/game/us-rodata.ld` places this section at `0x8009B6DC`
as informational data with `SUBALIGN(4)`, an exact 448-byte size assertion and
a 448-byte payload-size symbol. Before `func_1507D754` was matched the section
held only the `func_1507DF10` table at `0x8009B884` (32-byte section, 24
payload bytes); the start address and extent moved with the new tables, and
the `config/data/us.json` owner key moved with it. No padding is added and no
verification rule is changed. The unchanged game-data archive supplies these
bytes at runtime.

Focused matches, source-unit integration and clean batch verification remain
separate required checks.

## func_1507CD64 table and literals (round-29)

`func_1507CD64` dispatches its event selector (0 through 16) through
`jtbl_8009B690_game` (raw HI16/LO16 pair `1507CEA8`/`1507CEB0`) and computes a
random scale as `func_150ADA68() * 0.1f + 0.3f`. The checksum-validated US ROM
holds the seventeen targets at `0x8009B690..0x8009B6D3`:

| Selector | Target | Selector | Target |
| --- | --- | --- | --- |
| 0 | `0x1507CECC` | 9 | `0x1507CF94` |
| 1 | `0x1507CED4` | 10 | `0x1507CF9C` |
| 2 | `0x1507CEE0` | 11 | `0x1507CEBC` |
| 3 | `0x1507CEEC` | 12 | `0x1507CEC4` |
| 4 | `0x1507CEFC` | 13 | `0x1507CFB8` |
| 5 | `0x1507CF10` | 14 | `0x1507CFAC` |
| 6 | `0x1507CF24` | 15 | `0x1507CF80` |
| 7 | `0x1507CF64` | 16 | `0x1507CFC4` |
| 8 | `0x1507CF6C` | | |

followed by `3DCCCCCD` (`0.1f`) at `0x8009B6D4` and `3E99999A` (`0.3f`) at
`0x8009B6D8`, immediately before the `func_1507D754` table at `0x8009B6DC`. No
other reference function reads `0x8009B690..0x8009B6DB`. The function precedes
`func_1507D754` in text, so the compiled object's `.rodata` now begins with the
0x44-byte table and the two literals, then the three existing tables, for 0x20C
payload bytes and four zero alignment bytes (0x210; ROM `0x8009B89C` is also
zero). The section start moves to `0x8009B690` with an exact 0x210 size
assertion and a 0x20C payload-size symbol, and the `config/data/us.json` owner
address moves with it.
