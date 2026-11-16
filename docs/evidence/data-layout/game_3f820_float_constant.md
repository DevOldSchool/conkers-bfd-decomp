# US game_3F820 impact scale constant

`func_150124A0` casts thirty rays and pulls each hit point 3% toward the
emitter. Its raw HI16/LO16 pair in `asm/nonmatchings/game_3F820/func_150124A0.s`
(`150124E4`/`150124E8`) addresses the word `0x80096570`. No other reference
function touches it. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds
`3F7851EC` there, the single-precision value of the literal `0.97f` used in the
C source. The other float operands (`10.0f`, `-10.0f`, `300.0f`) are built with
`lui` and need no rodata.

The generated `game_3F820.o` has 0x10 bytes of `.rodata`: the constant and 12
zero alignment bytes, with no data relocations. `config/game/us-rodata.ld` maps
it as an INFO section at `0x80096570` with a 0x10 extent assertion and a 0x4
payload; `config/data/us.json` records the owner. The informational alignment
bytes cover `0x80096574..0x8009657F`, which are zero in the ROM.

The word at `0x80096560` (`469C4000`, 20000.0f) is followed by zeros up to
`0x8009656F`. It is read by the matched sibling `func_15012370` through
`extern f32 D_80096560` and is not owned by this mapping; the game-data archive
still supplies it. Converting that sibling to a literal would place 20000.0f
first in the object, so this pool would then need a split rather than a moved
start.

The loop end in `func_150124A0` is `D_800DCA30 + 0x1E0`, which the reference
names `D_800DCC10`. The two names resolve to the same linked address; finish
proves that alias with the complete linked unit against the ROM. No reference
assembly, compiler flag or verifier change is involved.
