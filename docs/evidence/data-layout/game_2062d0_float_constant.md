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
`scripts/split_game_rodata.py` splits game_2062D0 into `.rodata.2062d0_10` (0x18 at
0x800AB480) and `.rodata.2062d0_28` (0x4 at 0x800AB49C; offsets as renumbered in round-23), each with an exact linker size
assertion, as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md).

## func_151DA08C sub-pool (round-23)

`func_151DA08C` spawns a drifting particle and seeds its motion amplitudes with
`(func_150ADA68() * 0.2f + 0.1f) * center` twice. Its raw HI16/LO16 pairs address the four
words 0x800AB470..0x800AB47F, which the checksum-validated archive holds as `3E4CCCCD
3DCCCCCD 3E4CCCCD 3DCCCCCD`: exactly `0.2f`, `0.1f`, `0.2f` and `0.1f`, one word per use
as IDO emits them. No other reference function reads them. The function precedes
`func_151DA368` in text, so its literals lead the object `.rodata`, which is now 0x30
bytes: these four words, the six `func_151DA368` words, the `1.1f` constant and 4 zero
alignment bytes. The split layout gains a leading `.rodata.2062d0_0` (0x10 at
0x800AB470); the two existing ranges keep their runtime addresses and move to object
offsets 0x10 and 0x28 (`.rodata.2062d0_10`, `.rodata.2062d0_28`), with base symbols,
linker assertions and `config/data/us.json` sections renumbered. 0x800AB46C stays an
extern read of the caller `func_151D9FC0`, which now passes the decay factor as `1.01f`
(in an integer argument register, as before) to the corrected prototype
`void *func_151DA08C(u8, f32, f32, u8, s16, s32, f32 *, s32, s32)`.

The recorded blocker (the shared `func_1513D668` prototype returning `void`) is resolved:
`include/game_functions.h` and the `game_169510.c` definition now return `void *`, so the
body consumes the returned pointer without a shared-dependency change.
