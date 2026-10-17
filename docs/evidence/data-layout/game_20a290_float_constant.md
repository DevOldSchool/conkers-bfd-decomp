# US game_20A290 spawn literal pool

`func_151DCDE0` fills a spawn configuration from four float constants at 0x800AB558..0x800AB564: one value stored to two fields, then three more fields. With extern symbols IDO loads `D_800AB558` after the packet header stores; float literals reproduce the raw schedule, where it is loaded first.

The checksum-validated US game-data archive contains big-endian `3E4CCCCD BF316873 3E9BA5E4 41CDB646` at 0x800AB558, reproduced by `0.2f`, `-0.693f`, `0.30400002f` and `25.714f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_20A290.o` has a 0x10-byte `.rodata` equal to those 16 ROM bytes, with no padding and no data relocations; only `func_151DCDE0` references it. The descriptor words at 0x800AB550 and 0x800AB554 are passed by address and keep their extern symbols outside this mapping.

The INFO mapping retains linked bytes for verification without appending to the code-only payload, and a size assertion detects constant-pool growth. The full registered instruction comparison reached CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.
