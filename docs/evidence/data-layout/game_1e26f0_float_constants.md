# US game_1E26F0 beam strip constants

`func_151B5328` draws a wavy beam between two actors as ten quads. It steps
along the beam in tenths, advances the wave phase by pi/10 and the texture
coordinate by 204.8 per segment. The raw function loads four per-function
rodata literals through HI16/LO16 pairs, in the order IDO emits them:

| Address | Word | Literal | Load site |
| --- | --- | --- | --- |
| `0x800AA41C` | `3DCCCCCD` | 0.1f (segment step) | `151B56C8` |
| `0x800AA420` | `3EA0D97C` | 0.31415927f (phase step) | `151B5884` |
| `0x800AA424` | `434CCCCD` | 204.8f (texture step) | `151B595C` |
| `0x800AA428` | `3DCCCCCD` | 0.1f (segment counter step) | `151B5A24` |

The words were read from the checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`). No
other reference function loads these addresses. The other float operands
(`0.5f`, `1.0f`, `0.0f`) are built with `lui` or `$zero` and need no rodata.

The last literal feeds a float segment counter that the reference adds to and
stores to its stack slot (`sp+0xD0`) each iteration but never reads; the C
source keeps it as the write-only local `count` so the fourth pool word and the
store are both produced.

The generated `game_1E26F0.o` has 0x10 bytes of `.rodata`: these 16 payload
bytes in this order, with no alignment tail and no data relocations.
`config/game/us-rodata.ld` maps it as an INFO section at `0x800AA41C` with a
0x10 extent assertion and a 0x10 payload; `config/data/us.json` records the
owner.

The words before the pool stay extern reads of this unit's members and are not
owned by this mapping: the two attachment offset vectors `D_800AA400` and
`D_800AA40C` passed to `func_15143134` by this function, and `D_800AA418`
(`3F666666`, 0.9f) read by `func_151B5240`. They follow the reviewed game_1E2490
pool (`0x800AA3E8..0x800AA3F7`). `0x800AA42C` is zero. Matching this function
also replaces the 0x580-byte padding at the start of `Game1E26F0State` with
the two 44-entry vertex buffers it fills and names the width and fade fields at
`+0x590..+0x5A0`. The sibling functions `func_151B5240` and `func_151B5A9C`
still score `CURRENT (0)` with the extended record. No reference assembly,
compiler flag or verifier change is involved.
