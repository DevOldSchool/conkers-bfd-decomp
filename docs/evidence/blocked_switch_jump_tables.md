# Recovered US switch table placement

Both functions independently match their complete registered raw instruction
spans. Their compiler-generated jump tables belong in the separately loaded
game-data archive, rather than at the end of the game-code payload.

| Function | Source object | ROM address | Entries | Object offset |
| --- | --- | --- | --- | --- |
| `func_15031A50` | `game_5D2C0.o` | `0x80096F40` | 15 | `0x0` |
| `func_15031A50` | `game_5D2C0.o` | `0x80096F7C` | 40 | `0x3C` |
| `func_151925C4` | `game_1BF090.o` | `0x800A811C` | 17 | `0x0` |

The raw dispatch bounds and HI16/LO16 address pairs establish these addresses
and lengths. The first two tables are contiguous. Resolving every `R_MIPS_32`
table relocation against the preserved source-unit text starts (`0x1502FE10`
and `0x15191BE0`) reproduces all table words in the checksum-validated US ROM.

The `game_5D2C0.o` section has a `0xDC`-byte payload and four zero alignment
bytes; `game_1BF090.o` has a `0x44`-byte payload and twelve zero alignment
bytes. The following ROM words are other table data (`0x15031D18` and
`0x151928F4`, respectively), so object padding must not claim ownership of
those bytes.

`config/game/us-rodata.ld` places the two sections at their original addresses
with `SUBALIGN(4)`, exact section-size assertions, and explicit payload sizes.
The existing external-rodata verifier checks every relocated payload byte
against the owned ROM and separately checks that compiler padding is zero.
Informational sections do not extend the executable payload; the unchanged
game-data archive supplies the verified bytes at runtime. The clean batch gate
also requires a byte-identical integrated game-code image.

This recovers placement without changing assembly, compiler output, or reviewed
source boundaries. It does not establish complete reconstruction of either
source unit or of the game-data archive.
