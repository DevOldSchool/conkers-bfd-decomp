# US game_133190 float constants

`func_15107AE0` writes the points one third and two thirds of the way from a
start vector to an end vector. It loads two per-function rodata constants at
entry with `lui`/`lwc1` pairs. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) contains big-endian
`3EAA7EFA 3F2AACDA` at `0x800A2420`, exactly the single-precision values of
`0.333f` and `0.6667f`; the game-data base is `0x80082B20`.

With extern symbols the best candidate reached CURRENT (1070), because IDO
schedules global loads after the input loads. The literals with a plain
three-component interpolation reproduce the raw function (CURRENT 0). The
generated `build/us/src/game/game_133190.o` has the 16-byte `.rodata`
`3eaa7efa3f2aacda0000000000000000`: the two constants in load order followed
by eight zero alignment bytes, with no data relocations. The preceding words at
`0x800A2418` and `0x800A241C` and the word at `0x800A2430` belong to other code
or data; they are not owned by this mapping or treated as padding.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 16-byte extent assertion and an eight-byte
payload-size symbol. `config/data/us.json` records the source owner and its
completed-path alias. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.
