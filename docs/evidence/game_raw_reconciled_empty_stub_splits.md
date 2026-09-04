# Reconciled US empty-stub source families

Evidence kind: `structural_analysis`. Six otherwise complete raw-map families
initially disagreed with the independent US function CSV because the generated
assembly folded an eight-byte `jr $ra; nop` function into a neighbor. Explicit
raw-map splits now regenerate each empty body independently. Raw assembly and
CSV membership therefore agree exactly for every range below.

All outer endpoints are 16-byte aligned, no conditional branch crosses an
endpoint, and every member remains raw assembly.

| Source | US range | Entries | Bytes | Selected | Local edges | Debug strong/mapped | ECTS strong/mapped | Range SHA-1 |
| --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| `src/game/game_20B0D0.c` | `0x1DDC20:0x1DE8F0` | 7 | 3,280 | 4 | 1 | 1/3 | 0/1 | `f8a19829a4c6b3f1ae1cff5c4de0ae85c279493c` |
| `src/game/game_1E30A0.c` | `0x1B5BF0:0x1B6010` | 4 | 1,056 | 2 | 0 | 1/2 | 0/1 | `8ad695a355baed1e4b5e106c88a93788f3d0c4d5` |
| `src/game/game_1890A0.c` | `0x15BBF0:0x15C2F0` | 11 | 1,792 | 6 | 0 | 3/8 | 3/6 | `d8676ceaeb3045b0c78e95ad43df409692788f00` |
| `src/game/game_197F20.c` | `0x16AA70:0x16D400` | 11 | 10,640 | 2 | 4 | 8/9 | 3/5 | `a22d00fa16b83e892dff85af4ec7292670c00b5d` |
| `src/game/game_B4080.c` | `0x86BD0:0x8EF80` | 68 | 33,712 | 0 | 37 | 22/31 | 31/37 | `520b0360123b1c5d26354660d0de72499dac6ea6` |
| `src/game/game_C1D70.c` | `0x948C0:0x94EA0` | 4 | 1,504 | 0 | 1 | 3/4 | 0/0 | `4ca2421127ed45f69df0a39cef0dcc908fb39065` |

The reconciled empty entries are `func_151DE6CC`, `func_151B5E8C`,
`func_1515BE48`, `func_1516D2D8`, `func_15086C68`, and
`func_15094E98`. The regenerated raw files prove each exact two-instruction
body without changing the ROM or hand-writing assembly.

The large `0x86BD0:0x8EF80` controller family contains 37 direct local edges
spanning the range and 31 strong ECTS correlations. The `0x16AA70:0x16D400`
family links its two selected entry points to four later members. The remaining
ranges have exact selections or direct calls plus preserved beta order.
