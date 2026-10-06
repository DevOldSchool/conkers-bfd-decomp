# Continued US call-connected raw segments

Evidence kind: `structural_analysis`. These six complete raw-map segments are
connected by direct local calls and retain strong function identity and order
in the debug beta. Generic source names derive from retail-ROM offsets; every
member remains raw assembly.

The raw assembly index and independent US function CSV agree on every member
and span listed below. All outer endpoints are 16-byte aligned and no
conditional branch crosses an endpoint. Beta correlations are supporting
identity evidence only.

| Source | US range | Entries | Bytes | Local edges | Debug strong/mapped | ECTS strong/mapped | Range SHA-1 |
| --- | --- | ---: | ---: | ---: | ---: | ---: | --- |
| `src/game/game_6E770.c` | `0x412C0:0x415E0` | 4 | 800 | 2 | 4/4 | 4/4 | `5545864a97e71fa9384aef8856f3bcaebbccb957` |
| `src/game/game_A9260.c` | `0x7BDB0:0x7C370` | 3 | 1,472 | 1 | 3/3 | 0/1 | `42e5dfcd6af355b7d266780054aa90849cf50a3e` |
| `src/game/game_19E040.c` | `0x170B90:0x171600` | 5 | 2,672 | 1 | 5/5 | 3/3 | `ab84c479e107e433f619df3811ace6c5835018d6` |
| `src/game/game_138B40.c` | `0x10B690:0x10BF60` | 4 | 2,256 | 1 | 3/3 | 3/3 | `ce866689017444bdb02740729d11282f2c6d98dd` |
| `src/game/game_139FC0.c` | `0x10CB10:0x10D630` | 7 | 2,848 | 2 | 6/6 | 0/1 | `44b679f4e54a737311b555edcd35e85b69fae099` |
| `src/game/game_B21B0.c` | `0x84D00:0x85B70` | 8 | 3,696 | 2 | 6/6 | 2/4 | `6c1182b43062d29a26c03b5d877bf6a3c9f13b45` |

The local relationships are:

- `func_150413FC` calls `func_15041480` and `func_15041508`.
- Closing `func_1507C22C` calls opening `func_1507BDB0`.
- `func_15170EC4` calls opening `func_15170B90`.
- `func_1510B9D0` calls `func_1510B7B4`.
- `func_1510CE60` calls `func_1510D0EC`, which calls `func_1510D374`.
- `func_15085430` calls `func_15084D70`, while closing `func_15085ABC`
  calls `func_15085710`.

## Excluded membership disagreements

Two otherwise plausible call-connected candidates remain unmapped. The
independent CSV records three entries in `0xA50C0:0xA5B90`, while the raw index
records five. It records five entries in `0xAA4D0:0xAB1F0`, while the raw index
records seven. Neither range receives source-boundary credit until those splits
are reconciled.
