# US game_71820 look-at epsilon constants

`func_15047390` builds a look-at matrix and guards each of its three normalisations with
`if (mag == 0.0f) mag = 0.001f;`. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_71820/func_15047390.s` address the words `0x80098D60`, `0x80098D64` and
`0x80098D68`, one per guard, as IDO emits a separate word for each literal use. No other reference
function touches them. The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds `3A83126F 3A83126F 3A83126F` there, the single-precision value of the
literal `0.001f` used in the C source, which reaches `CURRENT (0)`.

The generated `game_71820.o` has 0x10 bytes of `.rodata`: the three constants and 4 zero alignment bytes,
with no data relocations; no other member of the unit emits rodata. `config/game/us-rodata.ld` maps it as an
INFO section at `0x80098D60` with a 0x10 extent assertion and a 0xC payload; `config/data/us.json` records
the owner. The informational alignment word `0x80098D6C` holds zero in ROM and is not read by any reference
function. The words below `0x80098D60` (`99999.9f`, `-10000.0f`) belong to other units and are not part of this
mapping. No reference assembly, compiler flag or verifier change is involved.

The recorded blocker (conflicting one- and two-argument `func_150A7BC0` declarations in this source) is
resolved: the matched `func_15047700` now uses the one-pointer `void func_150A7BC0(Game71820Matrix *)`
declaration that this function also calls, matching the project prototypes.
