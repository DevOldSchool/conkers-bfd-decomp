# Continued dense US pointer-selected families

Evidence kind: `structural_analysis`. These fifteen complete raw-map segments
are supported by exact function pointers in the owned game data, direct local
calls, or dense preserved beta order. Generic source names derive from
retail-ROM offsets; every member remains raw assembly.

The raw assembly index and independent US function CSV agree on every member
and span. All outer endpoints are 16-byte aligned and no conditional branch
crosses an endpoint. Beta correlations support identity and order only.

| Source | US range | Entries | Bytes | Selected | Local edges | Debug strong/mapped | ECTS strong/mapped | Range SHA-1 |
| --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| `src/game/game_200930.c` | `0x1D3480:0x1D5E90` | 28 | 10,768 | 4 | 6 | 14/16 | 6/7 | `de0969dd549397c46202558dfdcb6b9da2000401` |
| `src/game/game_80B80.c` | `0x536D0:0x55E50` | 20 | 10,112 | 12 | 2 | 9/12 | 5/9 | `f84f71cbd0cf23a3147d75970aaca87920213f7d` |
| `src/game/game_1EF500.c` | `0x1C2050:0x1C4820` | 16 | 10,192 | 4 | 9 | 8/11 | 3/7 | `7c56debd8ae6509652ff9e7b6915a0195a956228` |
| `src/game/game_1E37D0.c` | `0x1B6320:0x1B8370` | 14 | 8,272 | 11 | 0 | 7/9 | 0/1 | `682e260b8285d49bf6788cdcbcb8116ec4229085` |
| `src/game/game_DC6B0.c` | `0xAF200:0xB06B0` | 18 | 5,296 | 9 | 3 | 5/7 | 3/6 | `1c683f79f6acc7a9461c031f535a8b7976a0c3e6` |
| `src/game/game_1FA770.c` | `0x1CD2C0:0x1CE6D0` | 14 | 5,136 | 7 | 3 | 6/10 | 0/2 | `7440aa1c2833e351e447293fb8db6db9253927c2` |
| `src/game/game_1DD500.c` | `0x1B0050:0x1B1AB0` | 13 | 6,752 | 9 | 3 | 3/8 | 2/4 | `19f7599b5efa26237bee6b24b253c4ac7f960e61` |
| `src/game/game_77BE0.c` | `0x4A730:0x4CA60` | 16 | 9,008 | 0 | 6 | 9/10 | 2/7 | `0791c38001af27f00c67b4f0062894d5e0cf601a` |
| `src/game/game_1028F0.c` | `0xD5440:0xD6730` | 11 | 4,848 | 4 | 4 | 6/10 | 6/10 | `13b7146d26dfa905c7cd98b2a6771c1d1028db0e` |
| `src/game/game_157840.c` | `0x12A390:0x12C490` | 15 | 8,448 | 0 | 7 | 5/6 | 4/5 | `28c2a63442a764ab64e231f6c60513b04b5d0ca6` |
| `src/game/game_EC420.c` | `0xBEF70:0xC09B0` | 10 | 6,720 | 7 | 0 | 2/4 | 2/2 | `08db85d603fb7199f4f5d40bb817092510d0e6b0` |
| `src/game/game_124920.c` | `0xF7470:0xF85A0` | 7 | 4,400 | 4 | 1 | 3/4 | 2/3 | `508764063a07ea123b9977536c8c7622b05444e3` |
| `src/game/game_115F30.c` | `0xE8A80:0xE9890` | 7 | 3,600 | 5 | 0 | 3/5 | 2/4 | `4c9884b49c4df8e3d4f1c54c352578cb2f284f6e` |
| `src/game/game_E8C10.c` | `0xBB760:0xBDB70` | 9 | 9,232 | 3 | 0 | 5/6 | 0/1 | `abe349ce154927d06b58119dd541071f0de85468` |
| `src/game/game_E6A10.c` | `0xB9560:0xB9ED0` | 6 | 2,416 | 5 | 0 | 2/4 | 1/3 | `2a782d0af8bd8d1a6805c0cda3b9f5597cddd806` |

## Selection and call evidence

Exact owned data selections cover 84 members across thirteen ranges. The
densest groups select 12 of 20 members in `0x536D0:0x55E50`, 11 of 14 in
`0x1B6320:0x1B8370`, nine of 18 in `0xAF200:0xB06B0`, nine of 13 in
`0x1B0050:0x1B1AB0`, and seven of ten in `0xBEF70:0xC09B0`.

The `0xBEF70:0xC09B0` range also resolves the earlier isolated
`0xBF760:0xBFFE0` hold: the complete family contains the preceding selected
`func_150BF21C` together with selected `func_150BF760`, `func_150BFA7C`,
`func_150C01DC`, and `func_150C0648`.

Direct calls connect the ranges without data selections. In
`0x4A730:0x4CA60`, opening `func_1504A730` calls `func_1504AF10` and
closing `func_1504C8BC`; later members form three more local relationships.
In `0x12A390:0x12C490`, seven local edges connect `func_1512AD54` through
`func_1512C150`. Both complete spans retain strong ordered beta sequences.

Other local chains provide independent support across selected families:
`func_151D57F8` calls `func_151D5174` and `func_151D5A18`;
`func_151C229C` calls four late members in its range; `func_150B003C` calls
opening `func_150AF200`; and three selected closing members of
`0x1B0050:0x1B1AB0` call `func_151B1918`.
