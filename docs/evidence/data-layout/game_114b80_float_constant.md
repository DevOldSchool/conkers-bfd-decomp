# US game_114B80 float constant

`func_150E8470` scales its spawn packet speed with the same float the raw code
loads from `D_800A1374` into `$f28`. The checksum-validated US game-data archive
contains big-endian `3A83126F` at that address, exactly `0.001f`. ROM SHA1 is
`4cbadd3c4e0729dec46af64ad018050eada4f47a`; decompressed game-data offset is
`0x1E854` relative to base `0x80082B20`.

The literal is required for the register allocation, not only for the bytes.
With an extern `f32` load, IDO promotes the global and disrupts the surrounding
constant schedule into `$f28`/`$f30`/`$f26`/`$f24`/`$f20`. As a written
`0.001f` literal it matches the raw HI16/LO16 pair once the unit `.rodata` is
placed at `0x800A1374`.

The generated `build/us/src/game/game_114B80.o` snapshot SHA-256 is
`4146bc798d3965bf233be9182a646b910dec9276c1d30df27739f5f9bbed476f`.
Its rodata is `3a83126f000000000000000000000000`: one four-byte constant
followed by 12 zero alignment bytes, with no data relocations.

`verify-batch` runs `scripts/verify_game_rodata.py` against the
checksum-validated `rom_game_data()` with section size `0x10`, target address
`0x800A1374` and payload size 4. Only the four payload bytes are owned; adjacent
ROM values are not padding. The INFO mapping retains linked bytes for
verification without appending to the code-only payload. A size assertion
detects unexpected constant-pool growth.

The full registered instruction comparison reached CURRENT (0), with focused
layout, progress and whitespace checks passed, and `verify-batch func_150E8470`
is the linked integration gate. No reference assembly, compiler flag or
verifier changes are involved.
