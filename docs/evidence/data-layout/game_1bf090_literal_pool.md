# US game_1BF090 literal pool before its switch table

`func_15192358` spawns an effect using eight float constants at 0x800A80FC..0x800A8118, immediately before the `func_151925C4` switch table at 0x800A811C described in [blocked_switch_jump_tables.md](blocked_switch_jump_tables.md). With extern symbols IDO schedules the 0x800A8114 load after the `1.0f` setup; float literals reproduce the raw order.

The checksum-validated US game-data archive contains big-endian `3DAA25D9 3A83126F 40C90FDB C496E000 455E5000 45A6C000 3E52F1AB 3CCC63F1` at 0x800A80FC, reproduced by `0.08308f`, `0.001f`, `6.2831855f`, `-1207.0f`, `3557.0f`, `5336.0f`, `0.20600002f` (used twice, pooled once) and `0.02495f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

Because `func_15192358` precedes `func_151925C4` in the unit, the generated `build/us/src/game/game_1BF090.o` `.rodata` is 0x70 bytes: the 0x20 bytes of literals equal to ROM, then the unchanged 0x44-byte relocated table at section offset 0x20, then twelve zero alignment bytes. With maintainer approval (2026-10-17) the placement start moves from 0x800A811C to 0x800A80FC and the payload from 0x44 to 0x64; the table keeps its original address. The earlier unit constants at 0x800A80E8..0x800A80F8 keep their extern symbols and are outside the owned payload.

The existing external-rodata verifier checks every relocated payload byte against the ROM and that compiler padding is zero. The full registered instruction comparison reached CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that extends this mapping. No reference assembly, compiler flag or verifier changes are involved.
