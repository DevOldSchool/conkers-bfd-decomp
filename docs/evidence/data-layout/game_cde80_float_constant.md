# US game_CDE80 zone edge float constant

`func_150A0D8C` walks the active zones of kind 6 and, for each of the 25 actor slots of kind 0 or 1 inside a zone,
calls `func_15035808` with a fade band derived from the zone radius. Its raw HI16/LO16 pair in
`asm/nonmatchings/game_CDE80/func_150A0D8C.s` addresses the word `0x8009F5A8`, loaded once before the zone loop.
No other reference function touches it. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3E4CCCCD` there, the single-precision
value of the literal `0.2f` in `zone->radius * 0.2f`. `100.0f`, `150.0f` and `255.0f` are built with `lui`. With
`extern f32 D_8009F5A8` the candidate scored CURRENT 1208; with the literal (and the actor's leading `active`, `model`
and `kind` fields named in `GameCDE80Actor`, replacing a 0x14-byte pad with the same layout) the function is
`CURRENT (0)`.

The generated `game_CDE80.o` has 0x10 bytes of `.rodata`: the constant and 12 zero alignment bytes, with no data
relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x8009F5A8` with a 0x10 extent assertion and a
0x4 payload; `config/data/us.json` records the owner. The preceding words `0x8009F5A0`/`0x8009F5A4` stay extern reads
of a matched member, and the informational alignment bytes `0x8009F5AC..0x8009F5B7` cover the extern `D_8009F5AC` and
the start of the following data; they do not describe ROM contents and only the payload is compared. Converting the
earlier member's constants to literals would place them ahead of this one and requires a literal-pool split as
described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md). No reference assembly, compiler flag
or verifier change is involved.
