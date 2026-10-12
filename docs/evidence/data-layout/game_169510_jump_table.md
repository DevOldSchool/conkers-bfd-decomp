# US actor callback dispatcher table

`func_1513DF9C` in `game_169510.c` dispatches an actor callback using a byte
selector at offset `0x19` when flag `0x400000` is set in the word at offset
`0x58`. Its full registered text span is `[0x1513DF9C, 0x1513E070)` (212 bytes).
The direct selector expression and separate default assignment reproduce the
original register allocation and control flow.

The original instructions load the table base at `0x1513DFD8` and access its
word at `0x1513DFE0`. The unsigned guard admits selectors 0 through 12. The
table starts at `0x800A5188`, offset `0x22668` in the game-data archive based at
`0x80082B20`. `rom_game_data()` normalizes and validates the owned US ROM
against SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a` before extraction.
Its thirteen big-endian target words are:

| Selector | Original target |
| --- | --- |
| 0 | `0x1513DFFC` |
| 1 | `0x1513E004` |
| 2 | `0x1513DFFC` |
| 3 | `0x1513E01C` |
| 4 | `0x1513E03C` |
| 5 | `0x1513E00C` |
| 6 | `0x1513E014` |
| 7 | `0x1513E024` |
| 8 | `0x1513E02C` |
| 9 | `0x1513E034` |
| 10 | `0x1513E044` |
| 11 | `0x1513DFF4` |
| 12 | `0x1513DFEC` |

Case 10 reaches the default assignment at `0x1513E044`, whereas cases 0 and 2
reach the separate zero block at `0x1513DFFC`. An earlier instruction-only zero
candidate incorrectly grouped case 10 with cases 0 and 2; authoritative
`finish` rejected its table. The corrected C passes independent full-span
`CURRENT (0)`, all table targets, source-unit layout, progress and whitespace.

The complete mixed source object emits a single `0x40`-byte `.rodata` section:
thirteen relocated target words (`0x34` bytes) followed by twelve zero bytes
of object alignment. Its thirteen `R_MIPS_32` relocations refer to the original
source-unit text section starting at `0x1513C060`. Adding that base to every
emitted addend gives the original ROM target listed above.

Without an external mapping, the integrated image was 64 bytes too long and
only the HI16/LO16 table address differed within its code payload. The INFO
section in `config/game/us-rodata.ld` consumes only `game_169510.o(.rodata)` at
its original address. An assertion fixes the input extent at `0x40` and the
explicit payload size is `0x34`. The existing verifier compares every linked
target with the checksum-validated ROM and separately requires twelve zero
alignment bytes. It does not claim the following ROM data as padding.

The source unit remains mixed. Clean `verify-batch` supplies the integrated
GAME image and external-data acceptance recorded with this batch. No assembly,
compiler settings, verifier, shared declaration or asset reconstruction changed.
