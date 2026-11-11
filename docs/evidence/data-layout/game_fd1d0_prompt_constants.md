# US game_FD1D0 prompt string and constant

`func_150D032C` draws a `C:> ` console prompt followed by a text buffer that reveals at a fixed rate. Its raw
code builds the prompt from the address pair `150D0338`/`150D033C` (`lui`/`addiu` of `0x800A0880`, copied by
`lwl`/`lwr` plus `lbu` into a stack array) and loads the reveal rate with the HI16/LO16 pair
`150D03B0`/`150D03B4` from `0x800A0888` (both in `asm/nonmatchings/game_FD1D0/func_150D032C.s`). No other
reference function touches either address. The checksum-validated US ROM (SHA1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base `0x80082B20`) holds:

| Address | Bytes | Source |
| --- | --- | --- |
| `0x800A0880` | `433A3E20 00000000` | `"C:> "` (array initializer), terminator and 3 zero alignment bytes |
| `0x800A0888` | `3EDFBE77` | `0.437f` |

With the deferred `extern u8 D_800A0880[]` / `extern f32 D_800A0888` form the function scored CURRENT 1898;
written as `u8 prompt[] = "C:> "` and the `0.437f` literal (with `GameFD1D0TextCursor` gaining its
`buffers[2]` and `state` fields in place of padding) it is `CURRENT (0)`.

The generated `game_FD1D0.o` has 0x10 bytes of `.rodata`: `433a3e20 00000000 3edfbe77 00000000`, the
string with its terminator padded to a word, the constant, and 4 zero alignment bytes, with no data
relocations. `config/game/us-rodata.ld` maps it as an INFO section at `0x800A0880` with a 0x10 extent
assertion and a 0xC payload; `config/data/us.json` records the owner. The informational alignment word
`0x800A088C` is zero in ROM and is not referenced. No reference assembly, compiler flag or verifier change is
involved.
