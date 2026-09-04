# US handwritten alternate-entry families

Evidence kind: `structural_analysis`. These twelve raw-map segments form a
handwritten low-level code block with multiple deliberate global entry points.
The linear function CSV under-splits several ranges, but direct `jal` targets
confirm the raw assembly labels as callable entries. Generic source names
derive from retail-ROM offsets; every entry remains raw assembly.

All outer endpoints are 16-byte aligned and no conditional branch crosses an
endpoint. The raw assembly was regenerated from the unmodified US game-code
image; no assembly was hand-written for this mapping work.

| Source | US range | Raw entries | Bytes | Incoming direct calls | Range SHA-1 |
| --- | --- | ---: | ---: | ---: | --- |
| `src/game/game_D0F20.c` | `0xA3A70:0xA50C0` | 6 | 5,712 | 39 | `641320ba2d94f38db169d6fda3ffd81e5c4c4c08` |
| `src/game/game_D2570.c` | `0xA50C0:0xA5B90` | 5 | 2,768 | 11 | `e4c69801a8d3a595cbb95b27820c574157667ffc` |
| `src/game/game_D36C0.c` | `0xA6210:0xA6860` | 5 | 1,616 | 10 | `8d8279b398bc812d165d48d7c15b1e85f6987a2e` |
| `src/game/game_D4450.c` | `0xA6FA0:0xA7770` | 6 | 2,000 | 5 | `3eeda276ddf3d0249016453bd0fff5cf711a7f2f` |
| `src/game/game_D4E10.c` | `0xA7960:0xA7B80` | 4 | 544 | 132 | `ec164a680b9a433f746161e0170548e6b0e3c095` |
| `src/game/game_D50C0.c` | `0xA7C10:0xA7CB0` | 1 | 160 | 0 | `22cbdc0eb197baff64de02b0054f9b02eb4e0f86` |
| `src/game/game_D5650.c` | `0xA81A0:0xA9C40` | 5 | 6,816 | 9 | `7b5b33be1f0c7ac3ebe914696388e3acaf02c87d` |
| `src/game/game_D7980.c` | `0xAA4D0:0xAB1F0` | 7 | 3,360 | 43 | `91a485731964fd42fc1d855b7500ec17ce5d26a5` |
| `src/game/game_D86A0.c` | `0xAB1F0:0xAC9C0` | 3 | 6,096 | 2 | `10f54faf00b863bb03e8b3fbc2b82560712b9b6f` |
| `src/game/game_D9E70.c` | `0xAC9C0:0xAD770` | 2 | 3,504 | 30 | `b066c5877e8de25ed8530406117a6c8a376333d5` |
| `src/game/game_DAC20.c` | `0xAD770:0xAD780` | 1 | 16 | 12 | `409df10bf924719d592b1e4a4bd49e901d47b829` |
| `src/game/game_DAC30.c` | `0xAD780:0xAD8B0` | 2 | 304 | 74 | `7077ee255778e2cf3c8d76461a46e77249657582` |

The strongest alternate-entry evidence includes 86 calls to
`func_150A7960`, 40 to `func_150A7A48`, 32 to `func_150AD780`, 42 to
`func_150AD78C`, 28 to `func_150AC9C0`, and 14 to `func_150AA9A0`.
Other raw-only entries have ordinary stack-frame prologues or are reached by
direct calls from independently indexed retail functions.

`0xA7C10:0xA7CB0` is the sole one-entry gap in the same contiguous handwritten
block and retains a beta candidate with the exact raw span. The mixed
`0xA9C40:0xAA470` remains deliberately excluded because it is
`D_150A9C40` data. The callable `func_150AA470` tail was later split and mapped
separately; see `docs/evidence/game_reconciled_text_data_tail_aa470.md`.
