# US game_1B0740 slot-type switch and scale constants

`func_15183290` claims a free effect slot and dispatches on the slot type with a twelve-case
`switch`. The raw guard is `sltiu at,t7,0xC` (`1518333C`) and the table base is loaded with
`lui`/`lw` of `jtbl_800A72F0_game` at `1518334C`/`15183354` (text offsets 0xBC/0xC4 of the unit,
whose first member is this function). The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds these twelve words at
0x800A72F0..0x800A731F:

| Case | Original target |
| --- | --- |
| 0 | `0x15183360` |
| 1 | `0x151833AC` |
| 2 | `0x151833FC` |
| 3 | `0x15183490` |
| 4 | `0x151834F8` |
| 5 | `0x15183668` |
| 6 | `0x1518371C` |
| 7 | `0x151837B8` |
| 8 | `0x151834F0` |
| 9 | `0x1518384C` |
| 10 | `0x15183558` |
| 11 | `0x151835B8` |

The compiled `switch` emits them as text-relative `R_MIPS_32` entries (0xD0 .. 0x328 from the
function start), each equal to the ROM target minus `0x15183290`.

The cases then load nine float literals in first-use order from 0x800A7320..0x800A7343, which the
ROM holds as `3F4CCCCD` seven times, `3D23D70A` and `3CCCCCCD`: exactly `0.8f` (one word per case
that uses it, as IDO emits them), `0.04f` and `0.025f`. No other reference function reads these
words; with extern symbols the function does not match, and with literals it is `CURRENT (0)`.

The generated `game_1B0740.o` has 0x60 bytes of `.rodata`: the 0x30 table, the 0x24 literal pool and
12 zero alignment bytes; no other member of the unit emits rodata. `config/game/us-rodata.ld` maps
it as one INFO section at `0x800A72F0` with a 0x60 extent assertion and a 0x54 payload;
`config/data/us.json` records the owner. The alignment bytes `0x800A7344..0x800A734F` are not owned.
No reference assembly, compiler flag or verifier change is involved.
