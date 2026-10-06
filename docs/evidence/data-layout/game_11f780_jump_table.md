# US switch table for game_11F780

`func_150F22D0` dispatches byte values 3 through 8 through six word-sized
jump targets. The raw HI16/LO16 address pair identifies the table at
`0x800A192C` in the separately loaded US game-data archive.

| Selector | Target |
| --- | --- |
| 3 | `0x150F2310` |
| 4 | `0x150F2318` |
| 5 | `0x150F2320` |
| 6 | `0x150F2328` |
| 7 | `0x150F2330` |
| 8 | `0x150F2338` |

All six words were independently checked using the checksum-validated ROM
loader in `scripts/verify_game_rodata.py`. The compiler emits 24 payload bytes
and eight existing zero alignment bytes in a 32-byte `.rodata` section.

`config/game/us-rodata.ld` maps `game_11F780.o(.rodata)` to `0x800A192C`
as an informational section with `SUBALIGN(4)`, an exact 32-byte size assertion,
and a 24-byte payload-size symbol. The existing verifier compares every
relocated payload byte with the ROM and separately requires the alignment
bytes to be zero. No padding is added and no verification rule is changed.
The unchanged game-data archive supplies these bytes at runtime.

Without this placement, the linker appended the section at `0x151FA130`,
expanded the game-code payload by 32 bytes and changed the two address-bearing
instructions at code offsets `0xF22FC` and `0xF2304`.

This mapping preserves the reviewed source boundary documented in
`docs/evidence/boundaries/game/families/game_raw_internal_call_callback_clusters.md`. Focused instruction
matches, source-unit integration and clean batch verification remain separate
required checks.
