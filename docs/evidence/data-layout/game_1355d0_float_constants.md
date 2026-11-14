# US game_1355D0 particle constants

`func_15108120` fills an effect packet before calling `func_15152190`. The raw
function loads four per-function rodata literals through HI16/LO16 pairs; the
first is loaded once and stored to two packet fields.

| Address | Word | Value | Packet field |
| --- | --- | --- | --- |
| `0x800A2438` | `3E9C28F6` | 0.305f | `field30`, `field34` |
| `0x800A243C` | `BF4CCCCD` | -0.8f | `field24` |
| `0x800A2440` | `3EB020C5` | 0.344f | `field28` |
| `0x800A2444` | `41D349BB` | 26.411001f | `field38` |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`). Writing them as
literals reproduces the raw function (CURRENT 0); IDO merges the repeated
`0.305f` into one literal, so the object's `.rodata` is
`3e9c28f6bf4ccccd3eb020c541d349bb`: sixteen payload bytes with no alignment
tail and no data relocations. The ROM words at `0x800A2448` and `0x800A244C`
are zero, and `0x800A2450` begins the `game_135780` constants.

The mapping in `config/game/us-rodata.ld` places this section at `0x800A2438`
as informational data with `SUBALIGN(4)`, an exact 16-byte size assertion and a
16-byte payload-size symbol. The existing verifier compares every payload byte
with the ROM.

The two words before the pool, `D_800A2430` (`000000E2`) and `D_800A2434`
(`3F800000`), are passed by address to `func_15152190` and stay external
references; this mapping does not own them. The preceding `game_133190` pool
ends at `0x800A2430`. If those objects are later defined in this unit, they
precede the literals in its `.rodata`, so this mapping must move to
`0x800A2430` and its extent assertion must grow. Focused matching, source-unit
integration and clean batch verification remain separate required checks.
