# Complete US game-overlay mapping

The canonical US game-overlay map now classifies all 2,072,880 bytes
(100%). It contains no `asm` or `hasm` subsegment entries. This is source and
section ownership coverage; it does not claim that every game function has
been converted to matching C.

The final four formerly raw ranges are now represented by their actual kinds:

| US range | Bytes | Canonical mapping | Evidence |
| --- | ---: | --- | --- |
| `0xA9C40:0xAA470` | 2,096 | `data`, `game/data/D_150A9C40` | Text-resident constants and format strings, with the callable `func_150AA470` tail split at `0xAA470`. |
| `0x1DD140:0x1DD3A0` | 608 | `libultrare/conteepread.o(.text)` | Complete reconstructed Rare EEPROM-read object. |
| `0x1DD3A0:0x1DD460` | 192 | `libultrare/conteeplongread.o(.text)` | Complete reconstructed Rare long-read object. |
| `0x1DD460:0x1DD4E0` | 128 | `libultrare/conteepprobe.o(.text)` | Complete reconstructed Rare probe object. |

The data subsegment uses `.text` linker ordering because the retail executable
interleaves this non-code payload with callable text. The three EEPROM objects
are distinct Rare variants compiled with IDO `-O2 -g3`; their complete text,
padding, relocations, and object checksums are recorded in
`game_libultrare_eeprom_variant_boundaries.md`.

A refreshed integrated build reproduces the full 2,072,880-byte overlay with
SHA-1 `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
