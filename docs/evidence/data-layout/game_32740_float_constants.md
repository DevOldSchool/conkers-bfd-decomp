# US game_32740 view reset constants

`func_150054C4` clears and re-initialises a 0x9A0-byte view record. The raw
function loads four per-function rodata literals through HI16/LO16 pairs:

| Address | Word | Literal | Store |
| --- | --- | --- | --- |
| `0x800959E0` | `4479C000` | 999.0f | `field384` |
| `0x800959E4` | `4479C000` | 999.0f | `field7BC`, actor offset 0x18C |
| `0x800959E8` | `C61C4000` | -10000.0f | `field364` |
| `0x800959EC` | `4479C000` | 999.0f | `field86C` |

`func_15005818` (matched in round-30) adds a fifth literal to the same pool:

| Address | Word | Literal | Use |
| --- | --- | --- | --- |
| `0x800959F0` | `C61C4000` | -10000.0f | thirteenth argument of `func_1510E7A4` |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`). IDO emits one word per
load in source order; the adjacent `999.0f` store to the actor at offset 0x18C
reuses the `field7BC` register. The other constants (60, 40, 216, 1, -1 and
50) are built with `lui` and add no rodata; `field26C = 1.0` is folded to a
single `lui` (writing `1.0f` instead changes the schedule, CURRENT 35). The generated
`game_32740.o` has rodata `4479c0004479c000c61c40004479c000`: sixteen payload
bytes with no alignment tail and no data relocations. With extern symbols the
deferred body scored CURRENT 485; as literals the function is `CURRENT (0)`.

The match also narrows the third parameter in this file's prototype and
definition to `s16 resource`: the raw prologue homes `a2` and reloads it with
`lh` from the home slot.

`D_800959D0` and `D_800959D4` (with zero words to `0x800959DF`) belong to
`game_30E90` (`func_150045C4`). `D_800959F0` (`C61C4000`) was an extern
reference while `func_15005818` was raw; written as the literal `-10000.0f` it
follows the four `func_150054C4` words in source order, so the generated
`game_32740.o` rodata is now
`4479c0004479c000c61c40004479c000c61c4000` (twenty payload bytes) and the
section extent grew from 0x10 to 0x20 (payload 0x14). With the extern the natural body
scored CURRENT 10 (and needed the `void *` third parameter of
`func_1512D560`, which its definition in `game_15AA10` now declares; the
callers in `camera_camera`, `game_B4080` and `game_C3E20` compile to identical
objects). `0x800959F4..0x800959FF` are zero, and `jtbl_80095A00` belongs to
`game_33990`.

The mapping in `config/game/us-rodata.ld` places this section at `0x800959E0`
as informational data with `SUBALIGN(4)`, an exact 0x20-byte section-size
assertion (twenty payload bytes plus the object's twelve zero alignment bytes,
which cover the zero ROM words up to `0x800959FF`) and a 20-byte payload-size
symbol. The existing verifier compares every payload
byte with the ROM. Focused matching, source-unit integration and clean batch
verification remain separate required checks.
