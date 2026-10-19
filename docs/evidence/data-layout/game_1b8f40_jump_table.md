# US switch table for game_1B8F40

`func_1518BA90` uses nine word-sized jump targets at `0x800A7410` in the
separately loaded US game-data archive. The raw HI16/LO16 pair at
`0x1518BB20` and `0x1518BB28` identifies this address.

| Table index | Target |
| --- | --- |
| 0 | `0x1518BB34` |
| 1 through 5 | `0x1518BB90` |
| 6 through 7 | `0x1518BBC8` |
| 8 | `0x1518BB3C` |

All nine linked words were independently compared with the checksum-validated
US ROM using `scripts/verify_game_rodata.py`. The 36-byte payload has SHA-256
`5811a2a81ded1abd93f2ca922fe7bc865543fdf1bd2dc84a3d24fb01eed5d1ad`.
The compiler emits twelve zero alignment bytes after that payload, producing
48 bytes of object `.rodata`.

`config/game/us-rodata.ld` maps `game_1B8F40.o(.rodata)` to `0x800A7410`
as an informational section with `SUBALIGN(4)`, an exact 48-byte size assertion,
and a 36-byte payload-size symbol. The existing verifier checks every relocated
payload byte against the ROM and requires the alignment bytes to be zero.
`config/data/us.json` records the reviewed source owner and its completed-path
alias. The original game-data archive supplies the table at runtime; no archive bytes
or verification rules change.

Without this placement, the table was appended at `0x151FA130`, expanded the
code payload from 2,072,880 to 2,072,928 bytes, and changed the two address-bearing
instructions identified above. Full-span focused matching and clean batch
verification remain separate acceptance requirements.
