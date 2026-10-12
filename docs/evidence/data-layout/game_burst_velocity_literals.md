# US burst velocity literals

Three previously deferred burst constructors share the same instruction pattern
and use a single-precision velocity multiplier of `0.2f`. The independent US
assembly loads the constant into `$f2` in the prologue. A named snapshot of an
extern float placed the load later; direct literal expressions reproduce the
original scheduling. No compiler flags, assembly or comparison rules changed.

| Function | Source object | Registered text span | Constant address | Game-data offset |
| --- | --- | --- | --- | --- |
| `func_150C60D8` | `game_F3270.o` | `[0x150C60D8, 0x150C63EC)` | `0x800A041C` | `0x1D8FC` |
| `func_150C6A08` | `game_F3BA0.o` | `[0x150C6A08, 0x150C6D1C)` | `0x800A045C` | `0x1D93C` |
| `func_151AB3A4` | `game_1D6E80.o` | `[0x151AB3A4, 0x151AB6B8)` | `0x800A8FF4` | `0x264D4` |

`rom_game_data()` from `scripts/verify_game_rodata.py` normalizes and validates
the US ROM against SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a` before
extracting the archive. Its data base is `0x80082B20`. Each address above contains
big-endian `3E4CCCCD`, the exact single-precision representation of `0.2f`.

Each compiled object has the complete `.rodata` input
`3e4ccccd000000000000000000000000`: a four-byte payload followed by twelve zero
alignment bytes. The sole literal HI16/LO16 relocation pair is at object text
offsets `0x48`/`0x50` for `game_F3270.o` and `game_F3BA0.o`, and
`0x320`/`0x328` for `game_1D6E80.o`. These are function-relative offsets
`0x4`/`0xC`, matching the raw prologue loads.

The INFO sections in `config/game/us-rodata.ld` place each input at its original
address without appending it to the code-only payload. Each mapping asserts a
`0x10` input-section extent and declares a four-byte payload. The existing
`verify_game_rodata.py` verifies the linked payload against the validated archive
and checks that the remaining compiler alignment is zero. Adjacent ROM data is
neither claimed as padding nor replaced. No verifier or asset reconstruction
changes are needed.

Each function passed its independent full-span `CURRENT (0)`, source-unit
layout, progress and whitespace gates. Integrated image and external-data
acceptance are supplied by the clean `verify-batch` gate recorded with the batch.
