# US game_F52B0 camera float constants

`func_150C7E00`, the only function of `game_F52B0`, interpolates a camera
distance and height: `103.0f * t + D_800A04E0` and `224.0f * t + D_800A04E4`.
Both addends are per-function rodata literals loaded in source order.

| Address | Word | Literal | Use |
| --- | --- | --- | --- |
| `0x800A04E0` | `438F8000` | 287.0f | `distance` base |
| `0x800A04E4` | `443B8000` | 750.0f | `height` base |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) with
`rom_game_data` from `scripts/verify_game_rodata.py`. `0x800A04DC` and
`0x800A04E8..0x800A04EF` are zero; `0x800A04F0` (`422B3333`) belongs to a later
unit. No other reference function reads the two words. `103.0f` and `224.0f`
are built with `lui`/`mtc1` and add no rodata.

The generated `game_F52B0.o` has rodata `438f8000443b80000000000000000000`:
the two constants in load order followed by 8 zero alignment bytes, with no
data relocations. With the extern symbols or with the literals the function is
`CURRENT (0)` once the unit declares `func_1509BFB0` as returning `s32` (its
twin `func_1509BE40` and the integrated callers in `game_10E240` and
`game_118670` already do); the literals make the unit own its pool.

The mapping in `config/game/us-rodata.ld` places the section at `0x800A04E0`
as informational data with `SUBALIGN(4)`, a 0x10-byte section-size assertion
and an 8-byte payload-size symbol. The verifier compares the payload bytes
with the ROM. Focused matching, source-unit integration and clean batch
verification remain separate required checks.
