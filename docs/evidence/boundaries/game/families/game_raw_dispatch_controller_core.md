# US dispatch controller core at `0x1DE8F0`

Evidence kind: `structural_analysis`. This review covers the complete
12-function controller range `0x1DE8F0:0x1E24F0`, assigned the generic source
`src/game/game_20BDA0.c`. The name derives from the retail-ROM offset and does
not claim a historical filename. All functions remain raw assembly.

Owned pointer word `0x8008FDF8` selects opening `func_151DE8F0`. That routine
directly calls nine later members: `func_151DF1BC`, `func_151DF574`,
`func_151DFF38`, `func_151E0424`, `func_151E09DC`, `func_151E0B70`,
`func_151E1214`, `func_151E1744`, and `func_151E2284`. The two remaining
members are also connected internally: `func_151E0424` calls
`func_151E22BC`, and `func_151E09DC` calls `func_151E2404`.

The endpoint stops before shared helper `func_151E24F0`. It is called from this
controller but is also called from the following code-selected
`func_151E2834`, so it is not absorbed merely because of one incoming call.
Other later calls similarly remain external shared helpers.

The raw assembly index and independent US function CSV agree on all twelve
entries and spans. Both endpoints are 16-byte aligned, no conditional branch
crosses an endpoint, and the exact 15,360-byte range has SHA-1
`da1359939a8b8bdf465130b8e5289a335344d031`. Six members correlate with the
debug beta, five strongly; beta evidence supports identity but is not the
boundary proof.
