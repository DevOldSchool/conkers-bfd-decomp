# Preserved US singleton at `0x1B3040`

Evidence kind: `structural_analysis`. The raw assembly index and independent US
function CSV agree that `func_151B3040` occupies the complete aligned range
`0x1B3040:0x1B30B0`. The same 112-byte function has a strong ordered match in
the debug beta. No conditional branch crosses either endpoint.

The generic source path is `src/game/game_1E04F0.c`, derived from the retail-ROM
offset. The range SHA-1 is `12873119317ab401c2c4138e11196f2d1ab563f2`.
The function remains raw assembly.
