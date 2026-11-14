# US game_1FC5D0 gust constants

`func_151CF120` accumulates a gust amplitude and phase with `0.0122f` and `0.037499998f`
and advances its phase by `-0.70900005f * D_800BE9A4`. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_1FC5D0/func_151CF120.s` address the words `0x800AB014`, `0x800AB018`
and `0x800AB01C`; no other reference function touches them. The checksum-validated US ROM
(SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds
`3C47E282 3D199999 BF358107` there, exactly those three literals. The deferred candidate read
them through `extern f32` symbols; written as literals the function is `CURRENT (0)`, and the
externs were removed (`D_800BE9A4` stays).

The generated `game_1FC5D0.o` has 0x10 bytes of `.rodata`: the three constants and 4 zero
alignment bytes, with no data relocations; no other member of the unit emits rodata.
`config/game/us-rodata.ld` maps it as an INFO section at `0x800AB014` with a 0x10 extent
assertion and a 0xC payload; `config/data/us.json` records the owner. The informational
alignment word `0x800AB020` holds `3E6353F9` (0.22200002) in ROM; no reference function reads
it, so it is not owned and only the object's zero tail is checked. The word `0x800AB010`
belongs to another unit. No reference assembly, compiler flag or verifier change is involved.
