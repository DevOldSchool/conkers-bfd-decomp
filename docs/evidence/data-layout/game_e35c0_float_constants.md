# US game_E35C0 effect constants

`func_150B6110`, the first member of the unit, spawns an effect from four float
constants. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_E35C0/func_150B6110.s` address four words at
`0x8009FCBC..0x8009FCCB` (`150B6194`/`150B6198`, `150B619C`/`150B61A0`,
`150B621C`/`150B6220` and `150B6274`/`150B6278`; unit text offsets 0x84/0x88,
0x8C/0x90, 0x10C/0x110 and 0x164/0x168). No other reference function touches
them. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds
these big-endian words, and each round trips as the literal used in the C
source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x8009FCBC` | `3E19999A` | `0.15f` |
| `0x8009FCC0` | `3E1EB852` | `0.155f` |
| `0x8009FCC4` | `438C8000` | `281.0f` |
| `0x8009FCC8` | `3EDEB853` | `0.43500003f` |

The preserved candidate read them through `extern f32 D_8009FCBC..D_8009FCC8`
and scored CURRENT 1456; the accepted source uses the literals and reaches
`CURRENT (0)`.

The generated `game_E35C0.o` has exactly 0x10 bytes of `.rodata`: the four
constants in this order, no alignment bytes and no data relocations.
`config/game/us-rodata.ld` maps it as an INFO section at `0x8009FCBC` with a
0x10 extent assertion and a 0x10 payload; `config/data/us.json` records the
owner. The neighbouring words (`0x8009FCB8` and below, `0x8009FCCC` and above)
are not referenced by this function and are not part of the mapping. No reference assembly,
compiler flag or verifier change is involved.
