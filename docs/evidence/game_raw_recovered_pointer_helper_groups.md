# Recovered US pointer/helper source groups

Evidence kind: `structural_analysis`. This review recovers eleven source-unit
ranges from still-raw US game-overlay text. The generic source names derive
from retail-ROM offsets and do not claim recovered historical filenames. All
members remain raw assembly.

For every range, the raw reference and independent US function CSV agree on
all entries and spans, both outer endpoints are 16-byte aligned, and no
conditional branch crosses either outer endpoint. Every member is either
selected by an exact big-endian function pointer in the owned US game-data
image or is a local helper called by a pointer-selected member in the same
range. This accounts for 49 functions and 6,928 bytes.

| Source | US range | Entries | Bytes | Range SHA-1 |
| --- | --- | ---: | ---: | --- |
| `src/game/game_11D770.c` | `0xF02C0:0xF0380` | 5 | 192 | `3410a7496e7a700462156872de4b7a696d1c0e3b` |
| `src/game/game_1238D0.c` | `0xF6420:0xF64B0` | 4 | 144 | `506136c54c08909372e7b1f40841509212260773` |
| `src/game/game_129DE0.c` | `0xFC930:0xFC9D0` | 3 | 160 | `125b889b421162d9d73f8f112beed70e4c262d95` |
| `src/game/game_12B050.c` | `0xFDBA0:0xFDD10` | 4 | 368 | `02d8840d8b0b3f5272e23c41d76e764abdbdffe0` |
| `src/game/game_1478C0.c` | `0x11A410:0x11A7C0` | 4 | 944 | `06c6618c234830c007b5ad0c508d331e1a27e200` |
| `src/game/game_179400.c` | `0x14BF50:0x14C2F0` | 6 | 928 | `b2b920f1f6b973dabf1fb80d204b37d5d8f2669c` |
| `src/game/game_1861B0.c` | `0x158D00:0x159120` | 4 | 1,056 | `feb2fa5d6b8925366b19865bb1922333dd3511bf` |
| `src/game/game_1BB950.c` | `0x18E4A0:0x18EB10` | 8 | 1,648 | `01ab2828fee934ad7043ad90146502b7a290bd66` |
| `src/game/game_1BD8B0.c` | `0x190400:0x190490` | 3 | 144 | `297b91974c6c4b3f71d1b2752e40ac308e98d7a7` |
| `src/game/game_1D3FC0.c` | `0x1A6B10:0x1A6C90` | 4 | 384 | `103b5c021ea86204ee0ff90c4a6d1172a51b6f32` |
| `src/game/game_1EBFD0.c` | `0x1BEB20:0x1BEEE0` | 4 | 960 | `8835913a6c6677997142eae485a9b80c90ac945f` |

The owned selections and local-helper links are:

| Function | US span | Selection or local link |
| --- | --- | --- |
| `func_150F02C0` | `0xF02C0:0xF02EC` | `0x8008A708` |
| `func_150F02EC` | `0xF02EC:0xF0318` | `0x8008A830` |
| `func_150F0318` | `0xF0318:0xF0328` | called by `func_150F02C0` and `func_150F02EC` |
| `func_150F0328` | `0xF0328:0xF0354` | `0x80089FC4` |
| `func_150F0354` | `0xF0354:0xF0380` | `0x8008A00C` |
| `func_150F6420` | `0xF6420:0xF644C` | `0x80089F1C` |
| `func_150F644C` | `0xF644C:0xF6478` | `0x80089F50` |
| `func_150F6478` | `0xF6478:0xF6484` | called by `func_150F6484` |
| `func_150F6484` | `0xF6484:0xF64B0` | `0x80089FDC` |
| `func_150FC930` | `0xFC930:0xFC974` | `0x80086C90` |
| `func_150FC974` | `0xFC974:0xFC9A4` | called by `func_150FC9A4` |
| `func_150FC9A4` | `0xFC9A4:0xFC9D0` | `0x8008A71C` |
| `func_150FDBA0` | `0xFDBA0:0xFDC2C` | `0x80089EAC` |
| `func_150FDC2C` | `0xFDC2C:0xFDCAC` | called by `func_150FDCAC` and `func_150FDCD8` |
| `func_150FDCAC` | `0xFDCAC:0xFDCD8` | `0x80089F24` |
| `func_150FDCD8` | `0xFDCD8:0xFDD10` | `0x80089F58` |
| `func_1511A410` | `0x11A410:0x11A494` | called by `func_1511A494` |
| `func_1511A494` | `0x11A494:0x11A6FC` | called by `func_1511A6FC` and `func_1511A738` |
| `func_1511A6FC` | `0x11A6FC:0x11A738` | `0x80088DBC` |
| `func_1511A738` | `0x11A738:0x11A7C0` | `0x80088E7C` |
| `func_1514BF50` | `0x14BF50:0x14BF7C` | called by `func_1514C288` |
| `func_1514BF7C` | `0x14BF7C:0x14BF9C` | `0x80089DF0` |
| `func_1514BF9C` | `0x14BF9C:0x14C258` | called by `func_1514C258` and `func_1514C288` |
| `func_1514C258` | `0x14C258:0x14C288` | `0x80089D38` |
| `func_1514C288` | `0x14C288:0x14C2B8` | `0x80089D3C` |
| `func_1514C2B8` | `0x14C2B8:0x14C2F0` | `0x80089E18` |
| `func_15158D00` | `0x158D00:0x158D2C` | `0x8008BE2C` |
| `func_15158D2C` | `0x158D2C:0x158FA4` | `0x8008BE00` |
| `func_15158FA4` | `0x158FA4:0x159084` | `0x8008BE1C` |
| `func_15159084` | `0x159084:0x159120` | called by `func_15158D2C` |
| `func_1518E4A0` | `0x18E4A0:0x18E4CC` | called by `func_1518E4CC` and `func_1518E4F8` |
| `func_1518E4CC` | `0x18E4CC:0x18E4F8` | `0x8008BB84` |
| `func_1518E4F8` | `0x18E4F8:0x18E524` | `0x8008BB88` |
| `func_1518E524` | `0x18E524:0x18E5D8` | `0x8008D620` |
| `func_1518E5D8` | `0x18E5D8:0x18E66C` | `0x8008D624` |
| `func_1518E66C` | `0x18E66C:0x18E6D4` | `0x8008D628` |
| `func_1518E6D4` | `0x18E6D4:0x18E73C` | `0x8008D62C` |
| `func_1518E73C` | `0x18E73C:0x18EB10` | `0x80089E30` |
| `func_15190400` | `0x190400:0x190454` | `0x8008B1E4` |
| `func_15190454` | `0x190454:0x190464` | called by `func_15190464` |
| `func_15190464` | `0x190464:0x190490` | `0x8008B29C` |
| `func_151A6B10` | `0x1A6B10:0x1A6B3C` | `0x80089F20` |
| `func_151A6B3C` | `0x1A6B3C:0x1A6B68` | `0x80089F54` |
| `func_151A6B68` | `0x1A6B68:0x1A6BD8` | `0x8008B0A0` |
| `func_151A6BD8` | `0x1A6BD8:0x1A6C90` | called by `func_151A6B68` |
| `func_151BEB20` | `0x1BEB20:0x1BEC94` | `0x8008ADA8` |
| `func_151BEC94` | `0x1BEC94:0x1BECB8` | `0x8008ADBC` |
| `func_151BECB8` | `0x1BECB8:0x1BEE94` | `0x8008AD94` |
| `func_151BEE94` | `0x1BEE94:0x1BEEE0` | called by `func_151BECB8` |

The pointer addresses are runtime locations in the owned US data image. They
are used as structural selections, not as recovered symbol or filename claims.
