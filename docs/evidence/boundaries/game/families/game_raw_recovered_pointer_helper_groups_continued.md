# Continued recovered US pointer/helper source groups

Evidence kind: `structural_analysis`. This review continues the exact
owned-pointer and local-helper search across still-raw US game-overlay text.
The seven generic source names derive from retail-ROM offsets and do not claim
historical filenames. All 45 functions remain raw assembly.

For every range, the raw reference and independent US function CSV agree on
all entries and spans, both endpoints are 16-byte aligned, and no conditional
branch crosses an outer endpoint. Every member is selected by an exact
big-endian function pointer in the owned US game-data image or participates in
a direct call between members of the same range. The ranges account for 22,272
bytes.

| Source | US range | Entries | Bytes | Range SHA-1 |
| --- | --- | ---: | ---: | --- |
| `src/game/game_125A50.c` | `0xF85A0:0xF9720` | 4 | 4,480 | `83f2b962d8e24afed7a4c917ce00adb96544d80e` |
| `src/game/game_129EE0.c` | `0xFCA30:0xFCFB0` | 3 | 1,408 | `639d7e7061b492559b3255a4f4c3f7173ccedb6b` |
| `src/game/game_143870.c` | `0x1163C0:0x116930` | 4 | 1,392 | `fc0770bf6ac567347783af2a392cd930c9e502e0` |
| `src/game/game_1449A0.c` | `0x1174F0:0x1177C0` | 4 | 720 | `7949f70f9deba1488c0275426f018d8396cb1855` |
| `src/game/game_144C70.c` | `0x1177C0:0x119FC0` | 14 | 10,240 | `dea51b229664db8158e543cc5c696c7e5b56c49c` |
| `src/game/game_1D4140.c` | `0x1A6C90:0x1A7610` | 4 | 2,432 | `2ce15c8c6689d2cbdcf1e4b1cedd1e3bce77da56` |
| `src/game/game_1EB6C0.c` | `0x1BE210:0x1BE850` | 12 | 1,600 | `d34e275f977e219213e2ffed7333a4624e5312a4` |

## Membership review

`0xF85A0:0xF9720` is selected at `0x800866F8`, `0x8008B0B4`, and
`0x8008A9B8` by its first three members. The third member
`func_150F887C` calls the final member `func_150F892C`.

`0xFCA30:0xFCFB0` contains the direct local pair `func_150FCA30` and
`func_150FCBC0`, followed by pointer-selected `func_150FCF1C` at
`0x8008B394`. The first aligned endpoint after the pair is the end of that
selected member. The next entry, `func_150FCFB0`, has its own independent
selection at `0x8008CD44` and is excluded.

`0x1163C0:0x116930` contains pointer-selected `func_151163C0` at
`0x80088F54` and `func_15116924` at `0x80088FE4`. The two middle members form
the direct local pair `func_1511650C` -> `func_15116888`. The next entry has a
separate selection at `0x80088E98`.

`0x1174F0:0x1177C0` has selections for `func_151174F0` at `0x80088E88`
and `func_15117770` at `0x80088DA4`. The latter calls local
`func_15117518`, which is also called by closing `func_15117798`.

`0x1177C0:0x119FC0` has owned selections for ten of fourteen members:
`func_151177C0`, `func_151179BC`, `func_15117D3C`, `func_15117F3C`,
`func_1511896C`, `func_1511898C`, `func_15118F24`, `func_151193AC`,
`func_151193F4`, and `func_15119938`. The remaining members are connected by
direct local calls: `func_15117F3C` calls `func_15117DA4`; the two selected
wrappers at `0x11896C` and `0x11898C` call `func_151189AC`; and selected
`func_15119938` calls `func_151196D4`, which shares local
`func_151194D4`. The selections occupy
`0x80088CA0/0x80088CB8`, `0x80088E58`, `0x80088F18`, and the ordered
`0x80088FD8:0x80089068` callback area.

`0x1A6C90:0x1A7610` contains the direct local pair
`func_151A6C90` -> `func_151A6F00`, followed by `func_151A73EC` and
`func_151A743C`, selected at `0x80089928` and `0x80089944`. Its end is the
existing reviewed boundary for the following source.

`0x1BE210:0x1BE850` has selections for ten members across
`0x80089894`, `0x80089DF4`, `0x80089E08`, `0x80089E90`,
`0x80089F18:0x80089F80`, `0x80089FD8`, and `0x8008A020:0x8008A06C`.
Local `func_151BE644` is called by selected wrappers `func_151BE674` and
`func_151BE6A0`; local `func_151BE7C8` is called by selected wrappers
`func_151BE7F8` and `func_151BE824`. The two initially detected adjacent
subranges are deliberately merged because `func_151BE6A0` crosses their
internal boundary to call `func_151BE644`.

Pointer locations are runtime locations in the owned US data image. They are
structural selections only and do not establish names by themselves.
