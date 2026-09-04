# Dense US pointer-selected raw families

Evidence kind: `structural_analysis`. These nine complete raw-map segments are
dense function families selected by exact big-endian pointers in the owned game
data image. Direct local calls connect members in five ranges, and the debug
beta preserves most of each family in order. Generic source names derive from
retail-ROM offsets; every member remains raw assembly.

The raw assembly index and independent US function CSV agree on every member
and span listed below. All outer endpoints are 16-byte aligned and no
conditional branch crosses an endpoint. Beta correlations support identity and
order only.

| Source | US range | Entries | Bytes | Selected | Local edges | Debug strong/mapped | ECTS strong/mapped | Range SHA-1 |
| --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| `src/game/game_1865D0.c` | `0x159120:0x15AF90` | 19 | 7,792 | 10 | 3 | 18/18 | 11/14 | `4220665d7e15bf0e7f38ea90b5f5935371771a50` |
| `src/game/game_1483E0.c` | `0x11AF30:0x11E780` | 20 | 14,416 | 14 | 4 | 17/18 | 5/8 | `3ae62f902278309b19e0c60ddbdb1e1961186fc7` |
| `src/game/game_12F400.c` | `0x101F50:0x102920` | 8 | 2,512 | 6 | 0 | 7/7 | 5/5 | `5f2117f99dbf947d3a4e059af46a9adfd610da87` |
| `src/game/game_1E9A30.c` | `0x1BC580:0x1BE210` | 19 | 7,312 | 14 | 2 | 11/15 | 7/11 | `67d8774b1f3c1272305c81f1ca9aef8c1df11943` |
| `src/game/game_1FC830.c` | `0x1CF380:0x1D15D0` | 25 | 8,784 | 14 | 9 | 10/20 | 0/2 | `127bdc7b5c8497001b6d2c40fde5fe2af06cafca` |
| `src/game/game_1BC650.c` | `0x18F1A0:0x1903D0` | 16 | 4,656 | 9 | 5 | 8/13 | 5/8 | `5dd1eace18dfcfaf6534a7b15d5b8074e9539b07` |
| `src/game/game_11D830.c` | `0xF0380:0xF20F0` | 21 | 7,536 | 10 | 2 | 8/17 | 6/16 | `dbef19bdfb7b00c005c63c9e4c5b6c8dc347a3e8` |
| `src/game/game_127060.c` | `0xF9BB0:0xFB240` | 13 | 5,776 | 7 | 0 | 11/11 | 0/1 | `254733892389484df63ed2d01c1b46b20469953e` |
| `src/game/game_1E58B0.c` | `0x1B8400:0x1B8B40` | 6 | 1,856 | 3 | 0 | 4/5 | 4/5 | `f01ba39d704c0cdcc22cd9978b76f47619f992d1` |

## Owned data selections

The selected members below occur as exact words in
`build/library-research/game.data.bin`, whose runtime base is `0x80082B20`.
The function lists preserve retail order.

- `0x159120:0x15AF90`: `func_15159594`, `func_151596BC`,
  `func_15159BB0`, `func_15159C08`, `func_1515A11C`, `func_1515A60C`,
  `func_1515A78C`, `func_1515A974`, `func_1515AA84`, and
  `func_1515AB88`.
- `0x11AF30:0x11E780`: `func_1511AF30`, `func_1511B07C`,
  `func_1511B7D4`, `func_1511BA24`, `func_1511BDF4`, `func_1511BEBC`,
  `func_1511C548`, `func_1511C638`, `func_1511CB44`, `func_1511D394`,
  `func_1511D7BC`, `func_1511D9E4`, `func_1511DBC4`, and
  `func_1511DF6C`.
- `0x101F50:0x102920`: `func_15101F50`, `func_151022AC`,
  `func_151025F4`, `func_1510281C`, `func_15102884`, and
  `func_151028AC`.
- `0x1BC580:0x1BE210`: `func_151BC580`, `func_151BC64C`,
  `func_151BC794`, `func_151BCA90`, `func_151BD21C`, `func_151BD2BC`,
  `func_151BD42C`, `func_151BD43C`, `func_151BD750`, `func_151BD79C`,
  `func_151BDD8C`, `func_151BE0AC`, `func_151BE1B8`, and
  `func_151BE1E4`.
- `0x1CF380:0x1D15D0`: `func_151CF380`, `func_151CF844`,
  `func_151D0128`, `func_151D014C`, `func_151D08F0`, `func_151D0F08`,
  `func_151D0F34`, `func_151D1074`, `func_151D10A4`, `func_151D10C4`,
  `func_151D1138`, `func_151D1328`, `func_151D1388`, and
  `func_151D13B4`.
- `0x18F1A0:0x1903D0`: `func_1518F1A0`, `func_1518F384`,
  `func_1518F49C`, `func_1518F7C4`, `func_1518F858`, `func_1518F89C`,
  `func_1518FC04`, `func_1518FC44`, and `func_1518FC84`.
- `0xF0380:0xF20F0`: `func_150F0390`, `func_150F03BC`,
  `func_150F07E4`, `func_150F088C`, `func_150F0938`, `func_150F0E48`,
  `func_150F1020`, `func_150F1170`, `func_150F15F8`, and
  `func_150F1684`.
- `0xF9BB0:0xFB240`: `func_150FA1B8`, `func_150FA468`,
  `func_150FAAEC`, `func_150FACE4`, `func_150FADC8`, `func_150FB188`,
  and `func_150FB1E8`.
- `0x1B8400:0x1B8B40`: `func_151B85AC`, `func_151B863C`, and
  `func_151B86F4`.

## Reconciled membership disagreements

The independent CSV originally recorded one more entry than the raw index in
both `0x16AA70:0x16D400` and `0x86BD0:0x8EF80`. Their folded eight-byte return
stubs were later regenerated independently and both complete ranges integrated;
current evidence is recorded in
`docs/evidence/game_raw_reconciled_empty_stub_splits.md`.
