# US game_1865D0 particle float constants

`func_1515AB88` is a looping particle emitter in the same family as `func_150E8470`. Before its emission loop the raw function keeps `0.25`, `D_800A641C` (0.15), `D_800A6418` (0.1) and `D_800A6414` (0.08) in saved FP registers across the per-particle calls. IDO only hoists literal constants that way: extern symbols are reloaded after every call, and named copies add three frame words (frame 0x120 versus raw 0x110).

The checksum-validated US game-data archive contains big-endian `3DA3D70A 3DCCCCCD 3E19999A` at 0x800A6414, exactly the single-precision values of `0.08f`, `0.1f` and `0.15f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_1865D0.o` has rodata `3da3d70a3dcccccd3e19999a00000000`: the three constants in function order followed by 4 zero alignment bytes, with no data relocations. The unit's other functions still reference their constants through extern symbols, so no other function produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.

## func_15159C08 sub-pool (round-23)

`func_15159C08` loads `6.2831855f`, `0.001f`, `0.01f`, `6596.0f`, `2402.0f`, `0.1f`, `0.15f` and
`0.15f` in first-use order. Its raw HI16/LO16 pairs address 0x800A63C4..0x800A63E3, which the
checksum-validated archive holds as `40C90FDB 3A83126F 3C23D70A 45CE2000 45162000 3DCCCCCD 3E19999A
3E19999A`; no other reference function reads them. It precedes `func_1515AB88` in text, so its
literals lead the object `.rodata`, which is now 0x30 bytes: these eight words, the existing three
constants and 4 zero alignment bytes. The words between (0x800A63E4..0x800A6413) stay extern reads of
other members, so `game_1865D0.o` joined `GAME_SPLIT_RODATA_OBJS` and
`scripts/split_game_rodata.py` splits it into `.rodata.1865d0_0` (0x20 at 0x800A63C4) and
`.rodata.1865d0_20` (0xC at 0x800A6414), each with an exact linker size assertion, replacing the single
placement and its payload symbol. The matched prototype `func_151303BC(void *, u8, s32)` now agrees
with its definition, and the sibling `func_15159890` passes its packet without an `(s32)` cast; it
stays `CURRENT (0)`.
