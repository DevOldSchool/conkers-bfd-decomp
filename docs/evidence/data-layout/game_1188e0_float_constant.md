# US game_1188E0 burst spread scale

`func_150EBC80` spawns a burst at an actor position and, in a two-pass loop,
passes a fixed spread scale to `func_151541B8`. It loads that scale once before
the loop from `0x800A14FC` with a `lui`/`lwc1` pair and keeps it in a saved
float register. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) contains big-endian `3FD20C49`
there, exactly the single-precision value of `1.6409999f`; the game-data base
is `0x80082B20`.

With an extern symbol the candidate reached CURRENT (130), with constant
register differences in the hoisted loads. The literal reproduces the raw
function. The generated `build/us/src/game/game_1188E0.o` has the 16-byte
`.rodata` `3fd20c49000000000000000000000000`: one four-byte float and twelve
zero alignment bytes, with no data relocations. The neighbouring words before
`0x800A14FC` are loaded by sibling functions that are still in assembly and the
word at `0x800A1500` belongs to the following data; neither is owned by this
mapping or treated as padding.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 16-byte extent assertion and a four-byte
payload-size symbol. `config/data/us.json` records the source owner and its
completed-path alias. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.
