# US game_155C90 camera blend constants

`func_151287E0` blends a camera's angles towards their targets. Each blend term
has the form `angle * 0.011111111f * scale - angle * speed * 0.00037037037f *
speedScale` (1/90 and 1/2700), and the raw function loads those two literals
for each term through HI16/LO16 pairs.

| Address | Word | Literal | Loaded by the raw function |
| --- | --- | --- | --- |
| `0x800A35B0` | `3C360B61` | 0.011111111f | yes (`D_800A35B0`) |
| `0x800A35B4` | `39C22E45` | 0.00037037037f | yes (`D_800A35B4`) |
| `0x800A35B8` | `3C360B61` | 0.011111111f | no |
| `0x800A35BC` | `39C22E45` | 0.00037037037f | no |
| `0x800A35C0` | `3C360B61` | 0.011111111f | yes (`D_800A35C0`) |
| `0x800A35C4` | `39C22E45` | 0.00037037037f | yes (`D_800A35C4`) |
| `0x800A35C8` | `3C360B61` | 0.011111111f | yes (`D_800A35C8`) |
| `0x800A35CC` | `39C22E45` | 0.00037037037f | yes (`D_800A35CC`) |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`). IDO emits one
literal pair per source occurrence of the term; the second pair
(`0x800A35B8`/`0x800A35BC`) is emitted but its loads are eliminated, both in
the reference and in the compiled C, so it has no HI16/LO16 reference. The
generated `game_155C90.o` has rodata of exactly these eight words (0x20 bytes,
no alignment tail, no data relocations). With extern symbols the deferred body
scored CURRENT 6026; as literals the function is `CURRENT (0)`. It is the
unit's only function.

The words below `0x800A35B0` are read by `camera_camera` members through
externs (up to `D_800A35AC`), and `D_800A35D0`/`D_800A35D4` belong to
`game_156160`; neither range is owned by this mapping.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A35B0`
as informational data with `SUBALIGN(4)`, an exact 32-byte size assertion and
a 32-byte payload-size symbol. The existing verifier compares every payload
byte with the ROM, including the unreferenced pair. Focused matching,
source-unit integration and clean batch verification remain separate required
checks.
