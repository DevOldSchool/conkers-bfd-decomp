# US switch table for game_34F20

`func_15007B3C` resets level state and then dispatches on the level number in `D_800BE9F4`. The raw code subtracts
0x13, bounds the index with `sltiu 0x2D` and loads the target from `jtbl_80095A50_game` (HI16/LO16 at `15007B88` and
`15007B90`), so the table holds 45 word-sized targets for selectors 19 through 63 in the separately loaded US
game-data archive (ROM SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`).

| Selector | Target |
| --- | --- |
| 19 | `0x15007BE0` |
| 26, 36, 43, 45, 48, 51, 52, 63 | `0x15007B9C` |
| every other selector in 20..62 | `0x15007C10` (the default path) |

All 45 words were checked against the ROM by `scripts/verify_game_rodata.py`. The compiler emits 0xB4 payload bytes
and 12 zero alignment bytes in a 0xC0-byte `.rodata` section; no other function in the unit produces rodata.
`config/game/us-rodata.ld` maps `game_34F20.o(.rodata)` to `0x80095A50` as an informational section with
`SUBALIGN(4)`, an exact 0xC0-byte size assertion and a 0xB4-byte payload-size symbol, and `config/data/us.json`
records the owner. The alignment bytes fall at `0x80095B04..0x80095B0F`, which are zero in ROM and referenced by no
function; only the payload is compared. The preceding entrypoint table ends at `0x80095A4F`. The C source includes
`game_view.h` for the typed `D_800DBFF0` view array the function indexes. No reference assembly, compiler flag or
verifier change is involved.
