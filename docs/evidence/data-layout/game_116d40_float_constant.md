# US game_116D40 emitter scale

`func_150E9E34` loads its particle scale from `0x800A140C`, using the raw
HI16/LO16 pair at `0x150E9E9C` and `0x150E9ED0`. The checksum-validated US ROM
(SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`) contains big-endian
`3C23D70A` there: `0.009999999776482582`, exactly the value of `0.01f`.
The decompressed game-data offset is `0x1E8EC`, relative to base `0x80082B20`.

The focused layout-check object has SHA-256
`41df61a2a75d224b65e204ae3fbba6256cdc23d64aca8fbd109e21626c0b3767`.
Its 16-byte `.rodata` is `3c23d70a000000000000000000000000`: one four-byte
float and twelve zero alignment bytes. A read-only ELF32 section audit called
`scripts/verify_game_rodata.py`'s `rom_game_data()` and `verify_bytes()` with
payload size 4; the independent ROM comparison and alignment check passed.

`config/game/us-rodata.ld` places this pool in an INFO section at the original
address with `SUBALIGN(4)`, an exact 16-byte extent assertion and a four-byte
payload-size symbol. `config/data/us.json` records the source owner and its
completed-path alias. Only the four payload bytes are owned; adjacent ROM values
are not padding. The original data archive supplies the runtime bytes.

The function passed independent full-span `CURRENT (0)`, layout, progress and
whitespace checks. Clean batch verification remains the linked integration gate.
No reference assembly, compiler options or verifier rules changed.
