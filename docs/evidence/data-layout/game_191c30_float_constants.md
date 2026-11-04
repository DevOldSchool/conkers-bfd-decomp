# US game_191C30 phase constants

`func_1516489C` compares six oscillator phases against `3.1415927f`, one
literal per unrolled block. As `extern` symbols (`D_800A6B20`..`D_800A6B34`)
IDO schedules the loads differently; as C literals it emits six separate
pool words in first-use order and the function reaches full-span
`CURRENT (0)`.

The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds big-endian `40490FDB` (3.1415927) in each
of the six words `0x800A6B20..0x800A6B37`. The raw HI16/LO16 pairs are in
`asm/nonmatchings/game_191C30/func_1516489C.s`. The following words
(`0x800A6B38..`) are the jump table of the unmatched `func_15164F0C` and stay
outside this mapping; the preceding words belong to other units.

The generated `game_191C30.o` has 0x20 bytes of `.rodata`: the six words
followed by 8 zero alignment bytes, with no data relocations. No other C
function of the unit produces rodata. `config/game/us-rodata.ld` maps it as an
INFO section at `0x800A6B20` with a 0x20 extent assertion and a 0x18 payload
size; `config/data/us.json` records the owner. `verify_game_rodata.py`
compares only the payload with ROM. No reference assembly, compiler flag or
verifier change is involved.
