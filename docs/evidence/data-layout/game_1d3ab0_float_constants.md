# US game_1D3AB0 float constants

`func_151A6600` (raw, now matched) draws spark sizes and speeds with four
per-function literals: `0.393f + rand * 0.437f` and `rand * 0.284f + -0.91f`.
As `extern` symbols IDO schedules their loads differently; as literals the
full registered span reaches `CURRENT (0)`.

The checksum-validated US game-data archive (ROM SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base 0x80082B20, read
with `rom_game_data()` from `scripts/verify_game_rodata.py`) holds
`3EC9374C 3EDFBE77 BF68F5C3 3E916873` at 0x800A8DA0..0x800A8DAF. The generated
`build/us/src/game/game_1D3AB0.o` rodata is exactly these 16 bytes in load
order, with no data relocations; its HI16/LO16 sites are text offsets
0x198/0x19C, 0x1A0/0x1A4, 0x1EC/0x220 and 0x224/0x228. No other function in
the unit produces rodata. The next word (0x800A8DB0, 0.2f) is owned by
game_1D4140 (`D_800A8DB0`), and 0x800A8D90..0x800A8D9F lies outside this
mapping.

The INFO mapping retains linked bytes for verification without appending to
the code-only payload, and a size assertion detects constant-pool growth. No
reference assembly, compiler flag or verifier changes are involved.
