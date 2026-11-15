# US game_12BD10 trail float constants

`func_150FE860` builds an orientation basis for its owner with `func_15145740`, optionally transforms three attachment
points through the owner's matrix, derives a sideways vector when the direction is not vertical, and emits a trail
through `func_151C229C`. Its raw HI16/LO16 pairs in `asm/nonmatchings/game_12BD10/func_150FE860.s` address the words
`0x800A2030..0x800A203B` in first-use order. No other reference function touches them. The checksum-validated US ROM
(SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `3F4F9DB3 38D1B717 3B5A740E`
there, the single-precision values of `0.81100005f` (the basis scale argument), `0.0001f` (the horizontal-length
threshold) and `0.0033333334f` (the trail rate). `300.0f`, `10.0f`, `25.0f`, `200.0f`, `400.0f` and `50.0f` are built
with `lui`. With extern symbols the candidate scored CURRENT 775; with the literals the function is `CURRENT (0)`.

The generated `game_12BD10.o` has 0x10 bytes of `.rodata`: the 0xC-byte payload and 4 zero alignment bytes, with no
data relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A2030` with a 0x10 extent assertion
and a 0xC payload; `config/data/us.json` records the owner. The preceding words through `0x800A202F` are the
attachment point tables this unit reads through extern symbols. The alignment bytes fall at `0x800A203C`, over
`D_800A203C`, which a later member of this unit still reads through an extern; they do not describe ROM contents and
only the payload is compared. Converting that member's constants to literals would grow this pool and trip its size
assertion. No reference assembly, compiler flag or verifier change is involved.
