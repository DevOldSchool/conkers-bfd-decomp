# US game_183640 effect record constants

`func_15156D24` fills an effect record before spawning it. The raw function
loads five per-function rodata literals through HI16/LO16 pairs; the first is
loaded once and stored to two record fields.

| Address | Word | Literal | Record field |
| --- | --- | --- | --- |
| `0x800A6040` | `3FD851EB` | 1.6899999f | `field_20`, `field_24` |
| `0x800A6044` | `40DF0A3D` | 6.97f | `field_18` |
| `0x800A6048` | `4057AE14` | 3.37f | `field_1C` |
| `0x800A604C` | `4000A3D7` | 2.01f | `field_38` |
| `0x800A6050` | `404147AE` | 3.02f | `field_3C` |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`). The first word
is spelled `1.6899999f` because `1.69f` rounds to `3FD851EC`. The function's
other constants (150, 196 and 1.25) are built with `lui` and add no rodata.
The generated `game_183640.o` has rodata
`3fd851eb40df0a3d4057ae144000a3d7404147ae` followed by twelve zero alignment
bytes, with no data relocations. With extern symbols the deferred body scored
CURRENT 2335; as literals the function is `CURRENT (0)`.

The words before the pool (`D_800A6030` to `0x800A603F`) are read by
`game_182140` members, and the ROM words `0x800A6054` to `0x800A605C` are
zero; `0x800A6060` is read by later units. The other members of this unit,
`func_15156190` and `func_151564F8`, are still `GLOBAL_ASM` and reference no
rodata.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A6040`
as informational data with `SUBALIGN(4)`, an exact 32-byte size assertion and
a 20-byte payload-size symbol. The existing verifier compares every payload
byte with the ROM and checks that the alignment bytes are zero. Focused
matching, source-unit integration and clean batch verification remain separate
required checks.
