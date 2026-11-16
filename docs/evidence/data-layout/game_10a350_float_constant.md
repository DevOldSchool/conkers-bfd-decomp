# US game_10A350 emission threshold constant

`func_150DCEA0` advances a trail emitter and only emits once its accumulated
count exceeds a threshold. Its raw HI16/LO16 pair in
`asm/nonmatchings/game_10A350/func_150DCEA0.s` (`150DCF58`/`150DCF84`)
addresses the word `0x800A0CF4`. No other reference function touches it. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds `3F7FFF58` there, the single-precision value
of the literal `0.99999f` used in the C source. The other float operand,
`1.0f`, is built with `lui` and needs no rodata.

The generated `game_10A350.o` has 0x10 bytes of `.rodata`: the constant and 12
zero alignment bytes, with no data relocations. `config/game/us-rodata.ld` maps
it as an INFO section at `0x800A0CF4` with a 0x10 extent assertion and a 0x4
payload; `config/data/us.json` records the owner.

The preceding word `0x800A0CF0` (`3FD9999A`, 1.7f) is read by the raw
`func_150DC558` of game_109220 through an extern and lies just past that
unit's reviewed 0xB0-byte pool, which ends at `0x800A0CF0`. The informational
alignment bytes cover `0x800A0CF8..0x800A0D03`: `0x800A0CF8` and `0x800A0CFC`
are zero in the ROM, and `0x800A0D00` (`000000BE`) is read by game_10BC70
through an extern. The game-data archive still supplies those words. The other
member of this unit, `func_150DD640`, remains raw and reads no rodata in this
range. No reference assembly, compiler flag or verifier change is involved.
