# US holtenrope point constants

`func_151B48DC` and `func_151B4B78` each fill the ten rope points of a
`HoltenRopeEffect` in a loop and step the x coordinate once per point. Their
raw HI16/LO16 pairs address two adjacent words: `func_151B48DC` loads
`0x800AA3C4` (`lui` at `151B48E8`, `lwc1 $ft2` at `151B48FC`; unit text offsets
0x1838/0x184C) and `func_151B4B78` loads `0x800AA3C8` (`151B4B80`/`151B4B84`;
0x1AD0/0x1AD4). No other reference function touches them. The
checksum-validated US ROM (SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
game-data base `0x80082B20`) holds:

| Address | Word | Literal | Member |
| --- | --- | --- | --- |
| `0x800AA3C4` | `3DCCCCCD` | `0.1f` | `func_151B48DC` (`step = -(start - end) * 0.1f`) |
| `0x800AA3C8` | `435E38E4` | `222.22223f` | `func_151B4B78` (`x += 222.22223f`) |

With `extern f32 D_800AA3C4` IDO reloads the value inside the unrolled loop
(CURRENT 1110); as literals both functions are `CURRENT (0)`. The ten points
are `HoltenRopePoint points[10]` at offset 0x48 of `HoltenRopeEffect`
(0x18 bytes each: x, y, z and 0xC unknown bytes), replacing the tail of the
former `u8 pad3C[0xFC]`; the struct size and every other field offset are
unchanged.

The generated `holtenrope.o` has 0x10 bytes of `.rodata`: the two constants in
this order and 8 zero alignment bytes, with no data relocations.
`config/game/us-rodata.ld` maps it as an INFO section at `0x800AA3C4` with a
0x10 extent assertion and a 0x8 payload; `config/data/us.json` records the
owner. The ROM word at `0x800AA3CC` is zero. The payload ends at
`0x800AA3CC`; the informational alignment bytes run to `0x800AA3D4` and do not
own the word mapped at `0x800AA3D0`. The words below `0x800AA3C4` are read by
other members through externs and are not part of the mapping. No reference
assembly, compiler flag or verifier change is involved.

## func_151B3CF0 sub-pool (nov14)

`func_151B3CF0` lays out the ten rope points along a sagging arc. Its raw HI16/LO16 pairs
address 0x800AA3A0..0x800AA3AB, which the checksum-validated archive holds as `38D1B717
40490FDB 3EB2B8C3`: exactly `0.0001f`, `3.1415927f` and `0.34906587f` (pi/9). With extern
symbols the deferred body scored CURRENT 7999; as literals it is `CURRENT (0)`. The
object's `.rodata` is now these three words then the existing `3DCCCCCD 435E38E4` pool;
the words 0x800AA3AC..0x800AA3C3 stay extern reads of other deferred members, so
`scripts/split_game_rodata.py` splits holtenrope into `.rodata.holtenrope_0` (0xC at
0x800AA3A0) and `.rodata.holtenrope_c` (0x8 at 0x800AA3C4), each with an exact linker
size assertion, as described in [game rodata literal sub-pools](game_rodata_literal_sub_pools.md).

## func_151B42A4 sub-pool (round-23)

`func_151B42A4` relaxes the rope between its two anchor states. Its three
non-`lui` literals are `0.0001f` and `0.34906587f` twice (IDO emits one word
per use). The checksum-validated archive holds `38D1B717 3EB2B8C3 3EB2B8C3` at
0x800AA3B8..0x800AA3C3. In object order they sit between the
`func_151B3CF0` pool and the `3DCCCCCD 435E38E4` pool, so the object
`.rodata` is still 0x20 bytes, now all payload. The words
0x800AA3AC..0x800AA3B7 stay extern reads of raw members. Holtenrope now splits
into three ranges:

- `.rodata.holtenrope_0`: 0xC bytes at 0x800AA3A0.
- `.rodata.holtenrope_c`: 0xC bytes at 0x800AA3B8 (new).
- `.rodata.holtenrope_18`: 0x8 bytes at 0x800AA3C4, renamed from `_c`.

The match also names two struct fields that were padding before. In
`HoltenRopePoint`, `velocity` (`Vec3f`) replaces `padC[0xC]`. In
`HoltenRopeEffect`, `gain`, `stiffness` and `pad44[4]` replace `pad3C[0xC]`.
No other source reads those bytes.
