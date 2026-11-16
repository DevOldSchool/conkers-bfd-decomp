# US game_147C70 ripple constants

`func_1511A838` animates a vertex ripple. When it first builds its per-vertex
tables it weights each vertex's distance by `1.2f`; while a ripple decays, each
phase wrap multiplies its amplitude by `0.8f` (or `0.5f` while the amplitude
is below its target). The raw function loads two per-function rodata literals through
HI16/LO16 pairs, in the order IDO emits them:

| Address | Word | Literal | Load site |
| --- | --- | --- | --- |
| `0x800A3180` | `3F99999A` | 1.2f | `1511AA1C` |
| `0x800A3184` | `3F4CCCCD` | 0.8f | `1511ABD8` |

The words were read from the checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`). No
other reference function loads these addresses. The other float operands
(`0.5f`, `1.0f`, `3.0f`, `0.0f`) are built with `lui` or `$zero` and need no
rodata.

The generated `game_147C70.o` has 0x10 bytes of `.rodata`: these eight payload
bytes followed by eight zero alignment bytes, with no data relocations.
`config/game/us-rodata.ld` maps it as an INFO section at `0x800A3180` with a
0x10 extent assertion and a 0x8 payload; `config/data/us.json` records the
owner.

The preceding words `0x800A3170..0x800A317F` are the reviewed game_147470 pool,
which ends at `0x800A3180`. The informational alignment bytes cover
`0x800A3188..0x800A318F`, which hold `3C23D70A 3B03126F` (0.01f, 0.002f). They
are read through externs by game_1483E0 (`D_800A3188`, `D_800A318C`) and are
not owned by this mapping; the game-data archive still supplies them. No
reference assembly, compiler flag or verifier change is involved.
