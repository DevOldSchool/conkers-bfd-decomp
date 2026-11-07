# US game_1AC2F0 camera clamp constants

`func_1517F814` clamps two projected coordinates to `[-10000, 10000]`. The raw
HI16/LO16 pairs in `asm/nonmatchings/game_1AC2F0/func_1517F814.s` address
`0x800A7280`, `0x800A7284` and `0x800A7288`. The checksum-validated US ROM
(SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`)
holds big-endian `461C4000 C61C4000 C61C4000` there: `10000.0f` and two copies
of `-10000.0f`. IDO emits one pool entry for each use of the literal, which
explains the duplicate.

The generated `game_1AC2F0.o` has 0x10 bytes of `.rodata`: these three words
and four zero alignment bytes, with no data relocations. No other C member of
the unit produces rodata. The next word, `0x800A728C`, is used by the assembly
member `func_15180580` and keeps its extern symbol. `config/game/us-rodata.ld`
maps the section as INFO at `0x800A7280` with a 0x10 extent assertion and a
0xC-byte payload, and `config/data/us.json` records the owner. No reference
assembly, compiler flag or verifier change is involved.
