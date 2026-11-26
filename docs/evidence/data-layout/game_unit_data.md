# US GAME unit-owned initialized data

[Data layout index](README.md)

These matched units define their complete `.data` section in their own source.
Each section is placed by a `.game_rodata_<unit>_data` INFO output section in
`config/game/us-rodata.ld`; the GAME data image takes the bytes from the linked
object. The method and the first unit are described in
[game_185560_data.md](game_185560_data.md).

## Ownership

The GAME data image holds every object's `.data` in link order, then every
object's `.rodata` in the same order. IDO aligns each object's `.data` to 16
bytes. A unit's extent is therefore fixed when:

- the previous unit's last referenced address leaves only one 16-byte boundary
  before this unit's first referenced address, which becomes the start;
- this unit's last referenced address leaves only one 16-byte boundary before
  the next unit's first referenced address, which becomes the end; and
- every referenced address in the extent is referenced only by this unit.

Bytes between the last object and the end are zero (object alignment).

| Unit | Extent | Payload | Objects |
| --- | --- | --- | --- |
| `game_35D20` | `0x80082BD0`-`0x80082BE0` | 8 | two `func_150089D0` callbacks |
| `game_42DD0` | `0x80082F80`-`0x80082F90` | 8 | one ROM range |
| `game_F3270` | `0x800887D0`-`0x800887E0` | 12 | zero vector |
| `game_F52B0` | `0x80088800`-`0x80088810` | 4 | zero word |
| `game_F5800` | `0x80088810`-`0x80088820` | 8 | pointer pair into `0x80090230` |
| `game_108320` | `0x80088910`-`0x80088950` | 60 | one-entry beam parameter tables |
| `game_10B7D0` | `0x80088950`-`0x80088960` | 16 | two 8-byte lookups |
| `game_115D70` | `0x80088A80`-`0x80088A90` | 8 | pair `{25, 72}` |
| `game_118670` | `0x80088A90`-`0x80088AA0` | 4 | zero flag |
| `game_126BD0` | `0x80088B50`-`0x80088B60` | 1 (4 word-rounded) | `u8` 23 |
| `game_12BD10` | `0x80088BA0`-`0x80088BB0` | 1 (4) | `u8` 9 |
| `game_12D7F0` | `0x80088BC0`-`0x80088BD0` | 5 (8) | five-byte copy source |
| `game_1861B0` | `0x8008AFD0`-`0x8008B040` | 112 | 23-entry callback table, five rule pointers |
| `effects/colourframebuffer` | `0x8008B0D0`-`0x8008B0F0` | 32 | three callback tables |
| `game_1B7870` | `0x8008D5B0`-`0x8008D5C0` | 16 | two index pairs |
| `game_1B7EC0` | `0x8008D5C0`-`0x8008D5D0` | 12 | callback table |
| `game_1B9F30` | `0x8008D5D0`-`0x8008D5E0` | 8 | callback table |
| `game_1FFF60` | `0x8008FC40`-`0x8008FC70` | 44 | eight callback tables |

`game_1861B0` does not meet the end rule on references alone: its last
referenced address is `0x8008B02C`. The five-entry table there points at the
unit's own rule arrays at `0x800A62E0`-`0x800A6350` and fills the extent to
`0x8008B040`, the first address referenced by `game_1865D0`.

Payload sizes are rounded up to whole words, as the linker scripts require.
Trailing zeros inside a table (for example the last word of `game_1B7EC0`)
are counted as alignment.

## Deferred

- `game_1E26F0` (`0x8008FB80`-`0x8008FB90`): the two `u8` objects sit four
  bytes apart, so the IDO alignment of a lone `u8` needs a check first.
- `game_1865D0`, `game_188440` and `game_188F90`: the unreferenced display
  lists at `0x8008B050`-`0x8008B077` could belong to any of these units.

## Verification

`make game-integrated-raw`: every placement's payload matches the US ROM, the
alignment bytes are zero, the GAME data image matches with 38,228 linked bytes,
and `conker.game.us.integrated.bin` is unchanged (OK).
