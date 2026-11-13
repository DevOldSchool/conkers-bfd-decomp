# US game_2062D0 effect scale constant

`func_151DA938` scales an effect's magnitude before passing it to `func_151DAB58`. Its raw HI16/LO16 pair in
`asm/nonmatchings/game_2062D0/func_151DA938.s` (`151DA9B4` / `151DAA24`) addresses the word `0x800AB49C`.
No other reference function touches it. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3F8CCCCD` there, the single-precision value of the
literal `1.1f` used in the C source, which reaches `CURRENT (0)`.

The generated `game_2062D0.o` has 0x10 bytes of `.rodata`: the constant and 12 zero alignment bytes, with no data
relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800AB49C` with a 0x10 extent assertion and a
0x4 payload; `config/data/us.json` records the owner. The informational alignment bytes cover `0x800AB4A0..0x800AB4AB`,
which are read through externs by other members of this unit and are still supplied by the game-data archive. The
words below `0x800AB49C` are likewise extern reads of other members and are not part of this mapping. No reference
assembly, compiler flag or verifier change is involved.

## func_151DA368 sub-pool (nov14)

`func_151DA368` emits a ring of drifting particles. Its raw HI16/LO16 pairs address the six
words 0x800AB480..0x800AB497, which the checksum-validated archive holds as `3E19999A
3DCCCCCD 43EB8000 461DE800 38D1B717 3A83126F`: exactly `0.15f`, `0.1f`, `471.0f`,
`10106.0f`, `0.0001f` and `0.001f`. With extern symbols the deferred body scored CURRENT
4404; as literals it is `CURRENT (0)`. The object's `.rodata` is now those six words then
the existing `3F8CCCCD` constant; 0x800AB498 stays an extern read of another member, so
`scripts/split_game_rodata.py` splits game_2062D0 into `.rodata.2062d0_0` (0x18 at
0x800AB480) and `.rodata.2062d0_18` (0x4 at 0x800AB49C), each with an exact linker size
assertion, as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md).
