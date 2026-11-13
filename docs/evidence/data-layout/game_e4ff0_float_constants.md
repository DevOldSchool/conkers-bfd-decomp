# US game_E4FF0 debris burst constants

`func_150B82D0` spawns a burst of debris particles with random launch speed,
acceleration, size and spin. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_E4FF0/func_150B82D0.s` (`150B8340`/`150B8344`,
`150B8348`/`150B834C`, `150B8350`/`150B8354`, `150B8440`/`150B8444`,
`150B8448`/`150B844C`, `150B84D0`/`150B84D4`, `150B84EC`/`150B84F0`,
`150B8500`/`150B8508`) address the eight words 0x8009FD68..0x8009FD87; no other
reference function touches them. The checksum-validated US game-data archive (ROM
SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20) holds
`C4C44000 45444000 3C23D70A 4498A000 44E1C000 3A83126F 441E4000 3F7149E8` there,
exactly `-1570.0f`, `3140.0f`, `0.01f`, `1221.0f`, `1806.0f`, `0.001f`, `633.0f` and
`0.94253397f`. With `extern f32` symbols the deferred body scored CURRENT 5069; as
literals the function is `CURRENT (0)`.

The generated `game_E4FF0.o` has 0x20 bytes of `.rodata`: the eight constants in ROM
order with no alignment padding and no data relocations. `config/game/us-rodata.ld`
maps it as an INFO section at 0x8009FD68 with a 0x20 extent assertion and a 0x20
payload; `config/data/us.json` records the owner. The preceding words
0x8009FD54..0x8009FD67 stay extern reads of the unmatched `func_150B7B40`, and
0x8009FD88 onward stay extern reads of later members; both lie outside the owned
payload. No reference assembly, compiler flag or verifier change is involved.
