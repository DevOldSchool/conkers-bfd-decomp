# US switch table for game_1BA670

`func_1518D1C0` optionally removes existing effects owned by its first argument, then dispatches its spawn kind
(1 through 18) through eighteen word-sized jump targets and spawns the effect with a per-kind duration, enable flag,
direction and mode. The raw HI16/LO16 address pair (`1518D2C4`/`1518D2CC`) identifies the table at `0x800A7B14` in
the separately loaded US game-data archive (ROM SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
`0x80082B20`).

| Selector | Target | Selector | Target |
| --- | --- | --- | --- |
| 1 | `0x1518D3A0` | 10 | `0x1518D2D8` |
| 2 | `0x1518D3D0` | 11 | `0x1518D31C` |
| 3 | `0x1518D404` | 12 | `0x1518D35C` |
| 4 | `0x1518D438` | 13 | `0x1518D55C` |
| 5 | `0x1518D46C` | 14 | `0x1518D5A0` |
| 6 | `0x1518D49C` | 15 | `0x1518D5D4` |
| 7 | `0x1518D4CC` | 16 | `0x1518D618` |
| 8 | `0x1518D4FC` | 17 | `0x1518D65C` |
| 9 | `0x1518D52C` | 18 | `0x1518D690` |

All eighteen words were checked against the ROM by `scripts/verify_game_rodata.py`. The compiler emits 0x48
payload bytes and eight zero alignment bytes in a 0x50-byte `.rodata` section; no other function in the unit
produces rodata. `config/game/us-rodata.ld` maps `game_1BA670.o(.rodata)` to `0x800A7B14` as an informational
section with `SUBALIGN(4)`, an exact 0x50-byte size assertion and a 0x48-byte payload-size symbol, and
`config/data/us.json` records the owner. The alignment bytes fall at `0x800A7B5C..0x800A7B63`, over constants the
unmatched `func_1518D6E0` still reads through extern symbols; they do not describe ROM contents and only the
payload is compared. No reference assembly, compiler flag or verifier change is involved.
