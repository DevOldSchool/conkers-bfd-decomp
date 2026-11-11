# US game_DDF10 spawn constants

`func_150B0D20` uses nine float constants. Its raw HI16/LO16 pairs in
`asm/nonmatchings/game_DDF10/func_150B0D20.s` address nine words at
`0x8009F874..0x8009F897` (the `lui` instructions are at `150B0DE0`, `150B0EB4`,
`150B0ED8`, `150B0EE4`, `150B0EF0`, `150B0F48`, `150B0FC4`, `150B0FCC` and
`150B1008`). The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds
these big-endian words, and each round trips as the literal used in the C
source:

| Address | Word | Literal |
| --- | --- | --- |
| `0x8009F874` | `3FACCCCD` | `1.35f` |
| `0x8009F878` | `3C8EFA35` | `0.017453292f` |
| `0x8009F87C` | `407147AE` | `3.77f` |
| `0x8009F880` | `3FB33333` | `1.4f` |
| `0x8009F884` | `3F6CCCCE` | `0.9250001f` |
| `0x8009F888` | `4081EB85` | `4.06f` |
| `0x8009F88C` | `3E3645A2` | `0.178f` |
| `0x8009F890` | `BEE24DD4` | `-0.44200003f` |
| `0x8009F894` | `3D343959` | `0.044000003f` |

The generated `game_DDF10.o` has 0x30 bytes of `.rodata`: the nine constants in
this order and 12 zero alignment bytes, with no data relocations (nine
HI16/LO16 pairs in `.text`). `config/game/us-rodata.ld` maps it as an INFO
section at `0x8009F874` with a 0x30 extent assertion and a 0x24 payload;
`config/data/us.json` records the owner.

The words below the mapping stay external: `0x8009F860..0x8009F86F` are the
`D_8009F860[]`/`D_8009F868[]` tables this function indexes, and `0x8009F870`
(`0.7111111f`) is read by the matched `func_150B0A60`. The ROM words at
`0x8009F898` and `0x8009F89C` are zero. The payload ends at `0x8009F898`; the
informational alignment bytes run to `0x8009F8A4` and do not own the
`game_DE5A0` word mapped at `0x8009F8A0`.

An earlier candidate reached zero only with an empty `if (A && B) {}`. The
accepted source uses a plain early return for that check, a separate `s32 big`
flag for the pre-loop table index, and block-scoped `size`/`min` locals. No
reference assembly, compiler flag or verifier change is involved.
