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
