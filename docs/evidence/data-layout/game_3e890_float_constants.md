# US game_3E890 scene constants

`func_150113E0` builds a scene parameter block, an extra-value block and
several scene descriptors. The raw function loads eighteen per-function rodata
literals through HI16/LO16 pairs, in the order IDO emits them:

| Address | Word | Literal |
| --- | --- | --- |
| `0x800964C0` | `432F8000` | 175.5f |
| `0x800964C4` | `42E6CCCD` | 115.4f |
| `0x800964C8` | `3F856042` | 1.042f |
| `0x800964CC` | `3F66A7F0` | 0.901f |
| `0x800964D0` | `3F99BA5E` | 1.201f |
| `0x800964D4` | `3F33C9EF` | 0.7023f |
| `0x800964D8` | `45121000` | 2337.0f |
| `0x800964DC` | `450AC000` | 2220.0f |
| `0x800964E0` | `3ED1EB85` | 0.41f |
| `0x800964E4` | `3E4CCCCD` | 0.2f |
| `0x800964E8` | `3EB33333` | 0.35f |
| `0x800964EC` | `3EB33333` | 0.35f |
| `0x800964F0` | `358637BD` | 0.000001f |
| `0x800964F4` | `45121000` | 2337.0f |
| `0x800964F8` | `450AC000` | 2220.0f |
| `0x800964FC` | `44678000` | 926.0f |
| `0x80096500` | `C4318000` | -710.0f |
| `0x80096504` | `C3A98000` | -339.0f |

The words were read from the checksum-validated US ROM (normalized SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`) using `rom_game_data` from
`scripts/verify_game_rodata.py` (game-data base `0x80082B20`). The generated
`game_3E890.o` has a 0x50-byte `.rodata` section: these 72 payload bytes in
this order followed by eight zero alignment bytes, with no data relocations.
With extern symbols the deferred body scored CURRENT 1745; as literals the
function is `CURRENT (0)`.

The match also corrects two local record sizes. `Game3E890SceneParameters`
drops its trailing `pad59[0x23]` and is 0x5C bytes, as the reference frame
requires. `Game3E890SceneDescriptor` grows `pad48` from 0xC to 0x10 bytes,
making the full 0x58-byte packet that `func_1513D524` copies (the same size
used by other scene-descriptor users such as `game_1FBB80.c`). No other
function in the file uses either type.

The words up to `0x800964B0` belong to the preceding unit, and
`0x800964B4..0x800964BF` are zero. `D_80096508` and the following words are
read by the raw `func_1501175C` of this unit through externs and are not owned
by this mapping; the eight alignment bytes of the object span
`0x80096508..0x8009650F` informationally but are not compared with the ROM.
When `func_1501175C` is matched with literals, its words follow this pool in
the object and the extent assertion must grow.

The mapping in `config/game/us-rodata.ld` places this section at `0x800964C0`
as informational data with `SUBALIGN(4)`, an exact 0x50-byte size assertion and
a 0x48-byte payload-size symbol. The existing verifier compares every payload
byte with the ROM and checks that the alignment bytes are zero. Focused
matching, source-unit integration and clean batch verification remain separate
required checks.
