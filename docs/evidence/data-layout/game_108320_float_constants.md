# US game_108320 beam scale constants

`func_150DB114` advances a beam's two scale factors and reflects each one when
it leaves the range 0.8 to 1.2. The raw function loads three per-function
rodata literals through HI16/LO16 pairs: `D_800A0BE4` (upper bound, used for
both factors), `D_800A0BE8` (lower bound of the first factor) and `D_800A0BEC`
(lower bound of the second factor).

| Address | Word | Value |
| --- | --- | --- |
| `0x800A0BE4` | `3F99999A` | 1.2f |
| `0x800A0BE8` | `3F4CCCCD` | 0.8f |
| `0x800A0BEC` | `3F4CCCCD` | 0.8f |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`). Writing the
bounds as `1.2f` and `0.8f` literals reproduces the raw function (CURRENT 0);
IDO emits one 0.8f literal per comparison, so the object's `.rodata` is
`3f99999a3f4ccccd3f4ccccd00000000`: twelve payload bytes followed by four zero
alignment bytes, with no data relocations.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A0BE4`
as informational data with `SUBALIGN(4)`, an exact 16-byte size assertion and a
12-byte payload-size symbol. The existing verifier compares every payload byte
with the ROM and checks that the alignment bytes are zero. The next word,
`D_800A0BF0` (0.7111111f), belongs to `game_108AE0`.

`func_150DAE70` is still `GLOBAL_ASM`; its literal `D_800A0BE0` (`38D1B717`,
0.0001f) stays an external reference and is not owned by this mapping. When
that function is matched in C, the unit's `.rodata` begins with that literal,
so this mapping must move to `0x800A0BE0` and its extent assertion must grow.
Focused matching, source-unit integration and clean batch verification remain
separate required checks.
