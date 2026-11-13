# US game_10E510 emitter constants

`func_150E114C` builds particle descriptors from the position tables
`D_800A0FE4` and `D_800A0FFC`, which stay extern reads. Its five non-`lui`
float literals are emitted in use order: `0.001f` for the scaled timer step,
`0.962339f` and `1.011462f` for the descriptor scale pair, `357.0f` for the
random size base and `0.001f` again for the speed scale (IDO emits one word
per use). Constants with zero low halfwords (`204.0f`, `159.0f`, `165.0f`,
`195.0f`, `356.0f`) are built with `lui` and need no pool.

The checksum-validated US game-data archive (game-data base `0x80082B20`)
holds `3A83126F 3F765BD9 3F817796 43B28000 3A83126F` at `0x800A1014`, directly
after the two 0x18-byte tables ending at `0x800A1013`, and was read with
`build/us/manual-attempts/nov02/lit.py`. The compiled `game_10E510.o` has a
0x20-byte `.rodata` section with exactly these five words followed by twelve
zero alignment bytes, and five HI16/LO16 pairs at text offsets `0x14C`,
`0x21C`, `0x224`, `0x378` and `0x43C`; it has no data relocations. The ROM
words at `0x800A1028` onward belong to the following unit, so the alignment
bytes are checked in the object only.

The other member, `func_150E1060`, emits no `.rodata`, so the pool is the
object's whole read-only section. `config/game/us-rodata.ld` places it at
`0x800A1014` as informational data with `SUBALIGN(4)`, an exact 0x20-byte size
assertion and a 0x14-byte payload-size symbol; `config/data/us.json` records
the owner. No assembly, compiler flag or verifier change is involved.
