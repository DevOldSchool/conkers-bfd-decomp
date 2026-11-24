# US game_108320 beam constants

`func_150DB114` advances a beam's two scale factors and reflects each one when
it leaves the range 0.8 to 1.2. The raw function loads three per-function
rodata literals through HI16/LO16 pairs: `D_800A0BE4` (upper bound, used for
both factors), `D_800A0BE8` (lower bound of the first factor) and `D_800A0BEC`
(lower bound of the second factor).

| Address | Word | Value |
| --- | --- | --- |
| `0x800A0BE0` | `38D1B717` | 0.0001f (`func_150DAE70`, see below) |
| `0x800A0BE4` | `3F99999A` | 1.2f |
| `0x800A0BE8` | `3F4CCCCD` | 0.8f |
| `0x800A0BEC` | `3F4CCCCD` | 0.8f |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`). Writing the
bounds as `1.2f` and `0.8f` literals reproduces the raw function (CURRENT 0);
IDO emits one 0.8f literal per comparison.

`func_150DAE70` (matched in round-30) precedes `func_150DB114` in the unit and
rejects a degenerate beam with `fabsf(squared) < 0.0001f`. While it was
`GLOBAL_ASM` the word at `0x800A0BE0` was the external reference `D_800A0BE0`
and the mapping started at `0x800A0BE4` with twelve payload bytes. Written as
the literal, the unit's `.rodata` begins with it: the object's `.rodata` is now
`38d1b7173f99999a3f4ccccd3f4ccccd`, sixteen payload bytes with no alignment
tail and no data relocations.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A0BE0`
as informational data with `SUBALIGN(4)`, an exact 16-byte size assertion and a
16-byte payload-size symbol. The existing verifier compares every payload byte
with the ROM. The next word, `D_800A0BF0` (0.7111111f), belongs to
`game_108AE0`.
Focused matching, source-unit integration and clean batch verification remain
separate required checks.
