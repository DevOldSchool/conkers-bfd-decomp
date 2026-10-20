# US game_F44D0 particle float constants

`func_150C71C0` scales a direction by `D_800A0494` and builds three random particle parameters from `D_800A0498`/`D_800A049C` and `D_800A04A0`/`D_800A04A4`. All five are per-function rodata literals loaded in source order.

With the extern symbols IDO allocates the function differently (CURRENT 442); the literals `0.407f`, `0.020000001f`, `1.0400001f`, `0.194f` and `-0.35000002f` reproduce the raw function (CURRENT 0). The checksum-validated US game-data archive contains big-endian `3ED0624E 3CA3D70B 3F851EB9 3E46A7F0 BEB33334` at 0x800A0494, exactly those single-precision values (the spellings are the shortest decimal forms that round to the ROM words). The preceding word `3EF1A9FD` belongs to another function and stays outside this mapping. ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`; game-data base 0x80082B20.

The generated `game_F44D0.o` has rodata `3ed0624e3ca3d70b3f851eb93e46a7f0beb33334000000000000000000000000`: the five constants in load order followed by 12 zero alignment bytes, with no data relocations. The verifier compares only the 20-byte payload with ROM. No other function in the unit produces rodata.

The INFO mapping retains linked bytes for verification without appending to the code-only payload. A size assertion detects unexpected constant-pool growth. No reference assembly, compiler flag or verifier changes are involved.
