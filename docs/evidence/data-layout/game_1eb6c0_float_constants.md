# US game_1EB6C0 sway constants

`func_151BE210` eases an actor's position and scale towards randomly chosen
targets. The raw function loads four per-function rodata literals through
HI16/LO16 pairs, the easing factors of its four blends.

| Address | Word | Literal | Use |
| --- | --- | --- | --- |
| `0x800AA89C` | `3EB33333` | 0.35f | x-position blend |
| `0x800AA8A0` | `3ECCCCCD` | 0.4f | y-position blend |
| `0x800AA8A4` | `3F266667` | 0.65000004f | shared `field_40`/`field_44` blend |
| `0x800AA8A8` | `3ECCCCCD` | 0.4f | `field_3C` blend |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`). `0.65000004f`
is the shortest spelling of `3F266667` (`0.65f` rounds to `3F266666`). IDO
emits one 0.4f word per use. The function's other constants (4, 9 and 10) are
built with `lui` and add no rodata. The generated `game_1EB6C0.o` has rodata
`3eb333333ecccccd3f2666673ecccccd`: sixteen payload bytes with no alignment
tail and no data relocations. With extern symbols the deferred body scored
CURRENT 1010; as literals the function is `CURRENT (0)`.

The match needs no new type: `Game1EB6C0State`, the record at
offset 0x110 already used by `func_151BE4B8`, now names the floats at 0x8 to
0x4C that this function reads. Every previously named field keeps its offset.

`D_800AA898` (`358637BD`) belongs to `game_1E9A30`. `D_800AA8AC` (`3F266667`),
read by the matched `func_151BE6CC` in this unit, stays an extern reference and
is not owned by this mapping. If it is ever written as a literal, it follows
this pool in the unit's `.rodata` and the extent assertion must grow.

The mapping in `config/game/us-rodata.ld` places this section at `0x800AA89C`
as informational data with `SUBALIGN(4)`, an exact 16-byte size assertion and
a 16-byte payload-size symbol. The existing verifier compares every payload
byte with the ROM. Focused matching, source-unit integration and clean batch
verification remain separate required checks.
