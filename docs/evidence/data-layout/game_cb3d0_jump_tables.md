# US format string and switch tables for game_CB3D0

`game_CB3D0` owns 0xC8 bytes of `.rodata` at `0x8009F300` in the separately
loaded US game-data archive (game-data base `0x80082B20`):

| Address | Size | Contents | User |
| --- | --- | --- | --- |
| `0x8009F300` | 4 | `"%d"` and its terminator, `25 64 00 00` | `func_1509DFC4` case 1 (`D_8009F300`) |
| `0x8009F304` | 0x6C | 27 targets for selectors 0 through 26 | `func_1509DFC4` (`jtbl_8009F304_game`, `sltiu 0x1B`) |
| `0x8009F370` | 0x58 | 22 targets for selectors 0 through 21 | `func_1509E3DC` (`jtbl_8009F370_game`, `sltiu 0x16`) |

`func_1509DFC4` targets, in selector order: `0x1509DFF8`, `0x1509E008`,
`0x1509E064`, `0x1509E074`, `0x1509E084`, `0x1509E094`, `0x1509E0A4`,
`0x1509E0B4`, `0x1509E0C4`, `0x1509E0D4`, `0x1509E0F8`, `0x1509E108`,
`0x1509E118`, `0x1509E12C`, `0x1509E13C`, `0x1509E14C`, `0x1509E160`,
`0x1509E1B0`, `0x1509E1C8`, `0x1509E1E4`, `0x1509E1F8`, `0x1509E20C`,
`0x1509E220`, `0x1509E234`, `0x1509E3AC`, `0x1509E244`, `0x1509E2F8`.
Selector 24 jumps past the code for 25 and 26, so the C lists `case 24:` last.

`func_1509E3DC` targets, in selector order: `0x1509E408`, `0x1509E424`,
`0x1509E478`, `0x1509E488`, `0x1509E498`, `0x1509E4AC`, `0x1509E4B8`,
`0x1509E4C8`, `0x1509E4D8`, `0x1509E4E0`, `0x1509E4F0`, `0x1509E500`,
`0x1509E510`, `0x1509E520`, `0x1509E534`, `0x1509E544`, `0x1509E558`,
`0x1509E56C`, `0x1509E5B0`, `0x1509E5F0`, `0x1509E57C`, `0x1509E57C`.
Selectors 20 and 21 share one target, and 18 and 19 follow it in the code.

All 50 words were read from the checksum-validated US ROM with `rom_game_data`
from `scripts/verify_game_rodata.py` and compared with the compiled object. The
object has a 0xD0-byte `.rodata` section: the string, then the two tables
(49 word relocations against `.text`), then 8 zero alignment bytes. The ROM
bytes at `0x8009F3C8..0x8009F3CF` are zero, and the next reviewed table
(`game_CBBE0`) starts at `0x8009F3D0`. The preceding `game_CA630` section ends at
`0x8009F2FC`.

`config/game/us-rodata.ld` maps `game_CB3D0.o(.rodata)` to `0x8009F300` as an
informational section with `SUBALIGN(4)`, an exact 0xD0-byte size assertion and
a 0xC8-byte payload-size symbol, and `config/data/us.json` records the owner.
The float constants in this unit (`1/65536`, `65536.0` and `0.1`) are built
with `lui`/`ori` immediates and emit no `.rodata`. No compiler flag, reference
assembly or verifier change is involved.
