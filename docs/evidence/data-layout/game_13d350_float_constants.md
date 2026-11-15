# US game_13D350 angle float constants

`func_15111858` loads three per-function constants. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_13D350/func_15111858.s` address `0x800A2F24`, `0x800A2F28` and `0x800A2F2C`; no other
reference function touches them. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds `3C23D70A 393702D3 3C8EFA35` there, the single-precision values of `0.01f`,
`0.00017453292f` (pi/180 scaled by 0.01) and `0.017453292f` (pi/180). With extern symbols the candidate scored
CURRENT 320; with the literals the function is `CURRENT (0)`.

The generated `game_13D350.o` has 0x10 bytes of `.rodata`: the 0xC-byte payload and 4 zero alignment bytes, with no
data relocations; no other member of the unit emits rodata. `config/game/us-rodata.ld` maps it as an INFO section at
`0x800A2F24` with a 0x10 extent assertion and a 0xC payload; `config/data/us.json` records the owner. The preceding
words through `0x800A2F23` belong to other pools, and the alignment word `0x800A2F30` is the first entry of the jump
table that the unmatched `func_15111AF4` reads through `jtbl_800A2F30_game`; it does not describe ROM contents and only
the payload is compared. Matching that function would append its table to this object and requires growing this
mapping. No reference assembly, compiler flag or verifier change is involved.
