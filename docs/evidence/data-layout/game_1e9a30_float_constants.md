# US game_1E9A30 burst float constants

`func_151BD828` spawns a burst effect with two sparks and two glows around its owner. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_1E9A30/func_151BD828.s` address the thirteen words `0x800AA868..0x800AA89B` in first-use
order; no other reference function touches them. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds `4170B96F 40BBC3D6 4141C87A 3ECAD752
3DD58454 3F050D7E 3EB026C8 434F8000 42493333 41F73333 3DCCCCCD 3F333333 358637BD` there, the single-precision values
of `15.045272f`, `5.8676558f`, `12.111444f`, `0.396174f`, `0.1042563f`, `0.5197371f`, `0.34404588f`, `207.5f`,
`50.3f`, `30.9f`, `0.1f`, `0.7f` and `0.000001f`. The raw function had no C candidate; with these literals (and its
local burst packet typedefs) it is `CURRENT (0)`.

The generated `game_1E9A30.o` has 0x40 bytes of `.rodata`: the 0x34-byte payload and 12 zero alignment bytes, with
no data relocations; no other member of the unit emits rodata. `config/game/us-rodata.ld` maps it as an INFO section
at `0x800AA868` with a 0x40 extent assertion and a 0x34 payload; `config/data/us.json` records the owner. The
preceding words `0x800AA848..0x800AA867` stay extern reads of other members of this unit, and the alignment bytes
`0x800AA89C..0x800AA8A7` cover the following ROM words (`3EB33333`, 0.35f, at `0x800AA89C`), which no reference
function addresses by symbol; they do not describe ROM contents and only the payload is compared. Converting those members' constants to literals would grow this pool
or need a literal-pool split as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md). No
reference assembly, compiler flag or verifier change is involved.
