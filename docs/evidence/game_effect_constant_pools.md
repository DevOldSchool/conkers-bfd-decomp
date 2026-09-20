# Effect helper floating constants (US)

The manually recovered helpers in `game_1DC720.c`, `game_1E2180.c`, and
`game_1E2490.c` use IDO floating literal pools stored in the game-data archive,
separate from the game code payload. Treating these values as mutable external
variables changes instruction scheduling; literals produce exact focused
instruction matches.

The compiled `.rodata` bytes were compared with `rom_game_data()` from
`scripts/verify_game_rodata.py`, which validates the US ROM checksum before
extracting game data:

| Source | Runtime address | Bytes (big endian) |
| --- | --- | --- |
| game_1DC720 | 0x800A9DD4 | `3e051eb9 3fd9999a 3e010625 bf33b646` |
| game_1E2180 | 0x800AA3D0 | `3ee56042 3e51eb86 3fd9999a 3efe76c9` |
| game_1E2490 | 0x800AA3E8 | `3e051eb9 3fd9999a 3e010625 bf33b646` |

Each pool is 16 bytes. `config/game/us-rodata.ld` assigns its original runtime
address in an INFO section with four-byte input alignment. This preserves
the original placement despite IDO marking the input sections as 16-byte aligned. The linker assertions enforce the reviewed sizes;
the existing integrated-build verifier compares every linked pool against ROM
game data. Object basename patterns continue to select the same source after
supported integration moves it into `src/game/done/`.

Before these mappings, the integrated payload grew by 32 bytes from the first
and third pools, with 32 differing instruction bytes confined to eight pool
address references. That failure was a layout mismatch, despite focused
instruction matches.
