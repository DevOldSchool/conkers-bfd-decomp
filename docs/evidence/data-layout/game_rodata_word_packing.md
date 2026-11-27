# US GAME .rodata word packing

[Data layout index](README.md)

Conker's GAME data image packs each object's `.rodata` on a 4-byte boundary
directly after the previous object's. IDO's assembler instead aligns `.rodata`
to 16 bytes and pads its size to 16. The integrated compile step therefore trims
each object with a whole-object `.rodata` placement to its reviewed size with
4-byte alignment (`scripts/trim_game_rodata.py`), and each such placement's
`ASSERT(SIZEOF(...))` in `config/game/us-rodata.ld` states that exact size.

## ROM evidence

Adjacent matched units share no padding between their literal pools:

| Address | Word | Referenced by |
| --- | --- | --- |
| `0x800A8190` | `bfc20c4a` | `game_1BFDD0` (its last literal) |
| `0x800A8194` | `44964000` | `game_1C02A0` (its first literal) |
| `0x800AB004` | `3a83126f` | `game_1FBB80` (its last literal) |
| `0x800AB008` | `40490fdb` | `game_1FBED0` (its only literal) |
| `0x800AB00C` | `38d1b717` | `game_1FC0C0` (its first literal) |

Of the 156 linked whole-object `.rodata` placements, 70 start at an address
that is not 16-byte aligned, 46 of them only 4-byte aligned. `.text` and
`.data` keep IDO's 16-byte object alignment: unit boundaries in the code are
16-byte aligned, and units' `.data` ends are zero-padded to 16 bytes
([game_unit_data.md](game_unit_data.md)).

Banjo-Kazooie, an earlier Rare game also built with IDO 5.3, does not pack this
way: all 423 per-file `.rodata` subsegments in its splat configuration
(`decompressed.us.v10.yaml`) start on 16-byte boundaries.

## Toolchain tests

Each test compiled the same C files (one to nine `float` literals) at
`-O2 -g3 -mips2` and read the object's section headers.

| Toolchain | `.rodata` alignment | `.rodata` size for 1 / 3 / 5 / 9 floats |
| --- | --- | --- |
| IDO 5.3 (project compiler) | 16 | 0x10 / 0x10 / 0x20 / 0x30 |
| IDO 7.1 (decompals static recompilation) | 16 | 0x10 / 0x10 / 0x20 / 0x30 |
| IDO 5.3 front end with IDO 7.1 `as1` | 16 | 0x10 / 0x10 / 0x20 |

- The IDO 5.3 and 7.1 toolchains are the decompals `ido-static-recomp` builds.
  Its IDO 6.2 package contains only the C++ front end, so it offers no other
  assembler.
- Linking with IDO's own `ld` or GNU `ld` keeps each object's 16-byte padding.
- GNU `as` gives 4-byte, unpadded `.rodata` only for `.section .rodata`, but it
  assembles IDO's `li.s` output as `lui`/`ori`, not the `lwc1` literal loads in
  Conker's code.

No tested assembler or linker produces the packed layout, so it came from a
later step in Rare's build, such as a post-link or ROM-building tool. Trimming
to the reviewed size reproduces the result; the trim refuses unless the removed
tail is zero and holds no symbol or relocation.

## Verification

`make game-integrated-raw`: the integrated code is unchanged, the composed GAME
data image matches the US ROM, and `make game-data-link` (now part of
`game-integrated-raw`) links all 305 placements in place with the image matching
the US ROM.
