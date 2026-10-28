# US game_97AA0 float constants

`func_1506A5F0` fills a local effect record from an object's position and fixed
parameters, then submits it with `func_151A6F00`. It loads six per-function
rodata constants with `lui`/`lwc1` pairs. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) contains big-endian
`43178000 4171999A 41C9999A 3EC6A7F0 3E78D4FF BF828F5D` at `0x80099A10`,
exactly the single-precision values of `151.5f`, `15.1f`, `25.2f`, `0.388f`,
`0.24300002f` and `-1.0200001f`; the game-data base is `0x80082B20`.

With extern symbols the best candidate reached CURRENT (514). The literals in
first-use order, with the record's zero field written as an integer `0` (IDO
materializes that conversion separately from the shared `0.0f` register),
reproduce the raw function (CURRENT 0). The generated
`build/us/src/game/game_97AA0.o` has the 32-byte `.rodata`
`431780004171999a41c9999a3ec6a7f03e78d4ffbf828f5d0000000000000000`: the six
constants in load order followed by eight zero alignment bytes, with no data
relocations. The word `D_80099A28` that follows is loaded by another function in
this unit through its extern symbol and is not owned by this mapping.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 32-byte extent assertion and a 24-byte
payload-size symbol. `config/data/us.json` records the source owner and its
completed-path alias. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.
