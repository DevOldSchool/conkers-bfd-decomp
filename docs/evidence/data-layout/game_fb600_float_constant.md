# US game_FB600 remap bound float constant

`func_150CE200` projects a linked object's transform to screen space and clamps the resulting remap rectangle to the
visible area. Its raw HI16/LO16 pair in `asm/nonmatchings/game_FB600/func_150CE200.s` (`150CE2A4`/`150CE2A8`)
addresses the word `0x800A0800`, the right-hand screen bound compared against the rectangle's left and right edges.
No other reference function touches it. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds `43918000` there, the single-precision value of the literal `291.0f` used in the C
source. The bottom bound `215.0f` is built with `lui` and needs no rodata. With `extern f32 D_800A0800` the candidate
scored CURRENT 960; with the literal the function is `CURRENT (0)`.

The generated `game_FB600.o` has 0x10 bytes of `.rodata`: the constant and 12 zero alignment bytes, with no data
relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A0800` with a 0x10 extent assertion and a
0x4 payload; `config/data/us.json` records the owner. The preceding words `D_800A07F0` (vector argument of
`func_15143134`, still an extern of this function) and `D_800A07FC` (loaded by the unmatched member `func_150CE150`)
stay outside the mapping. The informational alignment bytes cover `0x800A0804..0x800A080F`, which overlap the start of
the byte table addressed through `D_800A080F` in `game_FBBF0`; they do not describe ROM contents and only the 0x4 payload
is compared. Converting `func_150CE150` to a literal would place its constant ahead of this one and requires a
literal-pool split as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md). No reference
assembly, compiler flag or verifier change is involved.
