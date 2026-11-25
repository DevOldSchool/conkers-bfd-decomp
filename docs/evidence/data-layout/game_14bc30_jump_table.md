# US game_14BC30 mover switch and literals

`func_1511E780` in `game_14BC30.c` matches its complete 1,232-byte raw instruction span. It moves
an object along one axis according to the movement type in the high half of its `0x3C` word,
plays an open or close sound from `D_80089260` on a state change, and for types 10 to 13 bobs the
object on a sine of an accumulating phase. Its other members, `func_1511EC50` and
`func_1511ED84`, build every float with `lui`/`mtc1` and emit no `.rodata`.

The second switch dispatches through a 14-entry table at `0x800A331C` (raw HI16/LO16 sites at
`0x1511E8EC` and `0x1511E8F4`; object `.text` offsets `0x16C`/`0x174`). The checksum-validated
US game-data archive (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
`0x80082B20`, read through `scripts/rom_span.py`) holds, from `0x800A331C`:

```
1511E900 1511EC24 1511E9E0 1511E970 1511EA48 1511EC24 1511EA48 1511EA48
1511E9E0 1511EC24 1511EAB0 1511EAD8 1511EBA8 1511EBD0
```

then the function's literals in use order from `0x800A3354`:

```
3C23D70A 3D23D70A 41490FDB 41490FDB 3C23D70A 3D23D70A
```

(`0.01f`, `0.04f`, `12.566371f` twice, `0.01f`, `0.04f`), a zero word at `0x800A336C`, and the
`f64` `180.0` (`40668000 00000000`) at `0x800A3370`. The C cases follow the table: 1, 5 and 9 and
every value of 14 or more leave the position alone, and cases 10 and 12 add `0.01f` before
falling into 11 and 13. The words up to `0x800A331B` belong to `game_1483E0`'s
`func_1511DF6C`, and `0x800A3378` is first read by `func_1511EF40` in the next unit.

The generated `game_14BC30.o` has a 0x60-byte `.rodata`: the table (0x38, 14 `R_MIPS_32` text
relocations), the six floats (0x18) and the double at object offset 0x50, then eight zero bytes.
In ROM the double is 0x54 bytes after the table, not 0x50, so one placement cannot reproduce it.
`scripts/split_game_rodata.py` splits the object into `.rodata.14bc30_0` (table), `_38`
(floats) and `_50` (double). `config/game/us-rodata.ld` places them as INFO sections at
`0x800A331C`, `0x800A3354` and `0x800A3370` with exact extent assertions, and
`config/data/us.json` records the owner. The zero word at `0x800A336C` is not claimed.
`progress integrate` verified all 88 payload bytes against the ROM and reported the game
build byte-identical.

The dispatch's bound check needed a new recognizer in `scripts/candidate_tables.py`: the index
shift `sll t5,v1,2` at `0x1511E8A4` is scheduled above the range/rate if-chain. The guard
`sltiu at,v1,14` sits at `0x1511E8E4`, and the chain's join branch at `0x1511E8D0` carries an
identical copy of the guard in its delay slot (`0x1511E8D4`) to reach `beqz at` directly. See
`JoinedGuardDispatchTests` in `tests/test_candidate_tables.py`.
