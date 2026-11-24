# US switch tables and literal for game_A9820

`func_1507C3E0` switches on the actor kind byte at `+0x04`. IDO splits the
sparse cases into three range tables, which sit in function order in the
unit's `.rodata`, followed by one float literal. Raw HI16/LO16 address pairs
identify each table in the separately loaded US game-data archive
(game-data base `0x80082B20`).

| Address | Contents | Selectors | Entries | Bytes |
| --- | --- | --- | ---: | ---: |
| `0x8009B4A0` | jump table | `0x75`–`0xBA` | 70 | `0x118` |
| `0x8009B5B8` | jump table | `0x25`–`0x53` | 47 | `0xBC` |
| `0x8009B674` | jump table | `0x00`–`0x04` | 5 | `0x14` |
| `0x8009B688` | `f32` `257.0f` (`0x43808000`), case `0x36` height | – | 1 | `0x4` |

Selectors without a case resolve to the shared default at `0x1507C7A4`
(51 entries in the first table, 42 in the second). The other targets are:

| Target | Selectors |
| --- | --- |
| `0x1507C574` | `0x00`–`0x04`, `0x3B`, `0x75`, `0x80`, `0x82`, `0x88`, `0x90`, `0x96`, `0x98`, `0x9C`, `0x9D`, `0x9F`, `0xA0`, `0xB0`, `0xB1`, `0xB2`, `0xB4` |
| `0x1507C6D4` | `0x25`, `0x2E` |
| `0x1507C6F0` | `0x36` |
| `0x1507C70C` | `0x9A` |
| `0x1507C728` | `0xAC` |
| `0x1507C744` | `0x89`, `0xBA` |
| `0x1507C760` | `0x53` |

The literal was previously declared as `extern f32 D_8009B688`. It is the
only value in the function that a `lui` immediate cannot hold, and IDO places
it straight after the tables, so the C now writes `257.0f`.

All 0x1EC payload bytes were checked against the checksum-validated ROM
loader in `scripts/verify_game_rodata.py`. The object's 0x1F0-byte
`.rodata` ends in four zero alignment bytes. `config/game/us-rodata.ld`
maps `game_A9820.o(.rodata)` to `0x8009B4A0` as an informational section
with `SUBALIGN(4)`, an exact 0x1F0-byte size assertion and a 0x1EC-byte
payload-size symbol. The next unit's table (`game_A9D90`) starts at
`0x8009B690`. `config/data/us.json` records the unit as the placement's
data owner. The unchanged game-data archive supplies these bytes at runtime.

This mapping preserves the reviewed source boundary documented in
`docs/evidence/boundaries/game/families/game_raw_direct_helper_pairs.md`.
Focused instruction matches, source-unit integration and clean batch
verification remain separate required checks.
