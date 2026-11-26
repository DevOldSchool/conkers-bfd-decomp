# US game_185560 unit-owned initialized data

[Data layout index](README.md)

`src/done/game/game_185560.c` (code `0x1580B0`-`0x158D00`) defines its complete
`.data` section, linked at `0x8008ADD0` by `.game_rodata_185560_data` in
`config/game/us-rodata.ld`.

## Ownership

The GAME data image holds every object's `.data` in link order, followed by
every object's `.rodata` in the same order. Across the referenced data addresses
in the image, 5,620 of 5,933 fit one order-preserving owner chain ordered by code
unit (one chain per section sweep); the rest are tables shared with other units.

- The last address referenced only by `game_1844C0` is `0x8008ADCC`.
- `0x8008AE00`, `0x8008AE0C`, `0x8008AE18` and `0x8008AFB8` are referenced
  only by `game_185560`.
- The first address referenced by `game_1861B0` is `0x8008AFD0`.
- Both ends are 16-byte aligned, and `0x8008AFCC`-`0x8008AFCF` are zero: IDO's
  end-of-object `.data` alignment.

## Contents

| Address | Object | Notes |
| --- | --- | --- |
| `0x8008ADD0` | `Gfx[4]` | pipe sync, `D_80089470` matrix load, texture on |
| `0x8008ADF0` | `Gfx[2]` | texture off |
| `0x8008AE00` | update callbacks `[3]` | `func_15158684`, `func_1518A5F4`, `func_15158AFC` |
| `0x8008AE0C` | draw callbacks `[3]` | `func_1515858C`, `func_1518A914`, `func_15158920` |
| `0x8008AE18` | `Game185560Matrix` | identity; the copy in `func_15158920` fixes 0x40 bytes |
| `0x8008AE58` | `s32[2]` | zero; no native reference |
| `0x8008AE60`-`0x8008AFB7` | five `Gfx` geometry lists | vertices at `0x800A6080`-`0x800A6200` |
| `0x8008AFB8` | `Gfx *[5]` | geometry table; the fifth entry selects `0x8008AEE0` |

The vertex arrays and the `0x800A6070` scale literal lie in `.rodata` between
this unit's last literal and `game_158D00`'s first reference; they are still
preserved bytes, pending a check of IDO's late-rodata ordering.

## Verification

`make game-integrated-raw`: 508 linked payload bytes at `0x8008ADD0` match the
US ROM, 4 object-alignment bytes are zero-filled, and
`conker.game.us.integrated.bin` is unchanged (OK).
