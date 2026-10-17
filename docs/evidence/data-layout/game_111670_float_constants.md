# US game_111670 effect literal pool

`func_150E5558` builds an effect packet from eight float constants at 0x800A1140..0x800A115C, in the order the raw code first loads them: two radian-to-degree factors, the packet size, three alternative field4 values, the field4C value and the random yaw scale. With extern symbols IDO allocates and schedules these loads differently (for example `$f12` and `$f0` swap around the 0x800A1148 load); float literals reproduce the raw instructions exactly.

The checksum-validated US game-data archive contains big-endian `42652EE0 42652EE0 3E2E147B 3F19999A 3E99999A 3E99999A BF47AE14 40933333` at 0x800A1140, reproduced by `57.295776f`, `57.295776f`, `0.17f`, `0.6f`, `0.3f`, `0.3f`, `-0.78f` and `4.6f`. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `build/us/src/game/game_111670.o` has a 0x20-byte `.rodata` equal to those 32 ROM bytes, with no alignment padding and no data relocations. Only `func_150E5558` references `.rodata`. Earlier unit constants (for example 0x800A1060 used by `func_150E42F8`) keep their extern symbols and are outside this mapping; the next ROM word at 0x800A1160 belongs to the following data and is not replaced.

The INFO mapping retains linked bytes for verification without appending to the code-only payload, and a size assertion detects constant-pool growth. The full registered instruction comparison reached CURRENT (0) with focused layout, progress and whitespace checks passed; the clean linked verify-batch result is recorded in the commit that adds this mapping. No reference assembly, compiler flag or verifier changes are involved.
