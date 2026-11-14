# US game_147470 orbit constants

`func_15119FC0` advances an object's phase, derives its height from the phase
and fades it by distance. The raw function loads four per-function rodata
literals through HI16/LO16 pairs:

| Address | Word | Literal | Use |
| --- | --- | --- | --- |
| `0x800A3170` | `4198C9EB` | 19.098593f | phase-to-height scale |
| `0x800A3174` | `4196CBE4` | 18.849556f | phase wrap period (6π) |
| `0x800A3178` | `3DB2B8C3` | 0.08726647f | phase rate (π/36) |
| `0x800A317C` | `38F5C28F` | 0.0001171875f | distance-to-alpha scale |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`). The function's
other constants (0.25, 10, 15, 80, 255 and 6400) are built with `lui` and add
no rodata. The generated `game_147470.o` has rodata
`4198c9eb4196cbe43db2b8c338f5c28f`: sixteen payload bytes with no alignment
tail and no data relocations. With extern symbols the deferred body scored
CURRENT 5142; as literals the function is `CURRENT (0)`. It is the unit's only
function.

The words before `0x800A3170` are read by earlier units (for example
`D_800A315C` by `game_144C70`), and `D_800A3180`/`D_800A3184` by
`game_147C70`; neither range is owned by this mapping.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A3170`
as informational data with `SUBALIGN(4)`, an exact 16-byte size assertion and
a 16-byte payload-size symbol. The existing verifier compares every payload
byte with the ROM. Focused matching, source-unit integration and clean batch
verification remain separate required checks.
