# US game_30E90 collision probe constants

`func_150045C4` passes two per-function rodata literals to `func_1510E7A4`
for each object it probes: `-10000.0f` and `20000.0f`, loaded in source order.

| Address | Word | Literal | Use |
| --- | --- | --- | --- |
| `0x800959D0` | `C61C4000` | -10000.0f | `func_1510E7A4` probe start |
| `0x800959D4` | `469C4000` | 20000.0f | `func_1510E7A4` probe length |

The words were read from the checksum-validated US ROM with `rom_game_data`
from `scripts/verify_game_rodata.py`. `0x800959C8..0x800959CF` and
`0x800959D8..0x800959DF` are zero; `0x800959E0` starts the `game_32740` pool.
No other reference function reads the two words.

The generated `game_30E90.o` has rodata `c61c4000469c40000000000000000000`:
the two constants in load order followed by 8 zero alignment bytes. With the
extern symbols the function scores 1585, because IDO keeps the addresses live;
the literals give the reference `lui`/`lwc1` pairs.

The mapping in `config/game/us-rodata.ld` places the section at `0x800959D0`
as informational data with `SUBALIGN(4)`, a 0x10-byte section-size assertion
and an 8-byte payload-size symbol. Focused matching, source-unit integration
and clean batch verification remain separate required checks.
