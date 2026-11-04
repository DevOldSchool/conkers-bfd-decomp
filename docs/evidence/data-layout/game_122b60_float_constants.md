# US game_122B60 float constants

`func_150F5C98` (raw, now matched) builds a spark packet whose random spread
terms use four per-function literals: `0.21900001f`, `0.086f`, `0.041f` and
`0.078f`. As `extern` symbols IDO keeps their loads in place and the function
does not match; as literals they are scheduled like the raw code and the full
registered span reaches `CURRENT (0)`.

The checksum-validated US game-data archive (ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20, read
with `rom_game_data()` from `scripts/verify_game_rodata.py`) holds
`3E60418A 3DB020C5 3D27EF9E 3D9FBE77` at 0x800A1B60..0x800A1B6F. Each literal
was checked bit-for-bit against its word. The generated
`build/us/src/game/game_122B60.o` rodata is exactly these 16 bytes in load
order, with no data relocations; its HI16/LO16 sites are text offsets
0x39C/0x3A0, 0x3A4/0x3A8, 0x3BC/0x3C0 and 0x3C4/0x3C8. No other function in
the unit produces rodata.

The words at 0x800A1B50..0x800A1B5F (`0.26000002`, `0.19500001`, `0.973034`,
`1.022472`) are also loaded by this function. They stay extern symbols: the
function matches either way, and they sit outside this mapping's payload.
0x800A1B74 onwards belongs to game_123D40.

The INFO mapping retains linked bytes for verification without appending to
the code-only payload, and a size assertion detects constant-pool growth. No
reference assembly, compiler flag or verifier changes are involved.
