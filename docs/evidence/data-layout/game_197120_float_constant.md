# US game_197120 float constant

`func_1516A3F4` refreshes a cached value from `func_1510F8D8`, emits a spawn
packet through `func_15167AD8` when that value reaches the object's limit, and
otherwise decays two signed 16-bit fields by a fixed factor. Both decay statements multiply by the
same per-function rodata constant, loaded with `lui`/`lwc1` from `0x800A6CC8`.
The checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`)
contains big-endian `3F7AE148` there, exactly the single-precision value of
`0.98f`; the game-data base is `0x80082B20`.

With an extern symbol the best candidate reached CURRENT (2217). The literal,
together with the raw local order and statement order, reproduces the raw
function (CURRENT 0). IDO shares the two uses of the literal, so the generated
`build/us/src/game/game_197120.o` has the 16-byte `.rodata`
`3f7ae148000000000000000000000000`: one four-byte float and twelve zero
alignment bytes, with no data relocations. The preceding words at `0x800A6CC0`
and `0x800A6CC4` and the words from `0x800A6CD0` belong to other code or data;
they are not owned by this mapping or treated as padding.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 16-byte extent assertion and a four-byte
payload-size symbol. `config/data/us.json` records the source owner and its
completed-path alias. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.

## Debris constants (func_15169C70)

`func_15169C70`, which precedes the 0.98f owner in text order, loads six
literals: `0.4f`, `57.295776f` (twice, one word per use), `-0.4f`, `0.7f` and
`-0.7f`. The checksum-validated ROM holds big-endian `3ECCCCCD 42652EE0
42652EE0 BECCCCCD 3F333333 BF333333` at `0x800A6CB0..0x800A6CC7`, immediately
before the 0.98f word. The mapping now starts at `0x800A6CB0`: the object
`.rodata` is 0x20 bytes, 0x1C of payload and 4 zero alignment bytes.
`progress integrate` rebuilt the integrated image byte-identically.
