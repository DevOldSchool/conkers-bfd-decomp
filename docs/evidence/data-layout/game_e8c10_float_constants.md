# US game_E8C10 particle float constants

`func_150BCBBC` randomly spawns at most one debris particle around an object of
kind `0x20`. The raw function loads five float constants through one HI16/LO16 pair
each: `D_8009FEE4` for the initial particle scale and two `0.03f * rand + 0.01f`
size draws inside the spawn loop (`D_8009FEE8`/`D_8009FEEC`,
`D_8009FEF0`/`D_8009FEF4`).

With `extern f32` symbols IDO hoists the loop-invariant loads out of the loop
and the register allocation diverges (CURRENT 60 at best). Writing the
constants as C literals gives each use its own function-local pool entry, as
IDO emits for repeated literals, and reproduces the raw schedule exactly.

The checksum-validated US game-data archive (game-data base 0x80082B20)
contains big-endian `3E99999A 3CF5C28F 3C23D70A 3CF5C28F 3C23D70A` at
0x8009FEE4, exactly the literals `0.3f`, `0.03f`, `0.01f`, `0.03f`, `0.01f`.

The generated `build/us/src/game/game_E8C10.o` has a 32-byte `.rodata` section:
the same 20 payload bytes followed by 12 zero alignment bytes, with no data
relocations. The neighbouring ROM words (0x8009FEE0 `BFCCCCCD`, 0x8009FEF8
`3F8CCCCD`) belong to other functions still referenced through externs or
assembly and stay outside this mapping's owned payload.

The INFO mapping in `config/game/us-rodata.ld` places the section at
`0x8009FEE4` with `SUBALIGN(4)`, a 0x20 size assertion and a 0x14 payload-size
symbol, so the existing verifier compares every payload byte with the ROM and
checks that the alignment bytes are zero. `config/data/us.json` records the
`.rodata` owner. The function reached full registered CURRENT (0) with focused
layout, progress and whitespace checks; the clean verify-batch result is
recorded with the commit that adds this mapping. No reference assembly,
compiler flag or verifier changes are involved.
