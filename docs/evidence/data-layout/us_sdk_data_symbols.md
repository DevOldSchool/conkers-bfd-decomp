# US SDK data symbols and payload extents

`config/profiles/us.yaml` supplies the actual archive/member section placements.
`config/symbols/us.txt` now names known variables within those placements and
records their declared payload sizes. No placement or loaded-byte denominator
changes, and candidates remain the actual archive objects.

## Declaration evidence

| Placement | Payload evidence | Payload extent |
| --- | --- | --- |
| `0x8002B9D0`, `0x8002B9D4` | `lib/libultrare/src/libultra/os/syncputchars_data.c`: two `u32` globals | 4 bytes each |
| `0x8002BA40`, `0x8002BA44` | `lib/libultrare/src/libultrare/audio/n_sl.c`: two O32 pointers | 4 bytes each |
| `0x8002BD10` | `lib/ultralib/src/os/initialize.c`: `OSTime osClockRate` | 8 bytes |
| `0x8002BD18`, `0x8002BD1C`, `0x8002BD20` | Same source: shutdown, interrupt mask, disk flag | 4 bytes each |
| `0x8002BD60`, `0x8002BE20` | `lib/ultralib/src/io/piacs.c`, `siacs.c`: queue-enabled globals | 4 bytes each |
| `0x8002BE10` | `lib/ultralib/src/io/controller.c`: `s32 __osContinitialized` | 4 bytes |
| `0x8002BE30`, `0x8002BE80`, `0x8002BED0` | `lib/ultralib/src/vimodes/vimode{pal,mpal,ntsc}lan1.c`: `OSViMode` | 80 bytes each |
| `0x8002BF20` | `lib/libultrare/src/libultrare/libc/xldtob.c`: nine doubles | 72 bytes |
| `0x8002BF68`, `0x8002BF6C`, `0x8002BF70` | Same source: NUL-terminated `NaN`, `Inf`, `0` strings | 4, 4, 2 bytes |
| `0x8002C1B0`, `0x8002C1D0` | `lib/libultrare/src/libultra/os/exceptasm_data.c`: 32 bytes and nine words | 32, 36 bytes |
| `0x8002C920` | `lib/ultralib/src/gu/libm_vals.s`: one `.word` | 4 bytes |

All addresses agree with the independently mapped section plus the symbol offset
in the actual SDK object. Every affected section's literal bytes already matched
the ROM before the naming correction. Names and payload sizes are not inferred
from zero runs or from the next referenced address.

## Padding in the reference

Report generation enables `SPIMDISASM_CREATE_RODATA_PADS` so explicit sizes
apply to both data and rodata (the latter is disabled by default upstream).
Given explicit sizes, splat emits labels for automatically generated unreferenced
padding. Those labels describe no SDK variable and prevent native section matching.
The report reference normalizer leaves such padding anonymous only immediately
after an explicitly sized canonical symbol, at the declared end address, with
contiguous zero-byte rows no farther than the next 16-byte alignment boundary.
Referenced labels, nonzero rows and unknown gaps keep their symbols. This changes
only reference metadata: all padding bytes remain assembled, counted and included
in the full-image ROM comparison. The real build objects are not modified.

## Remaining limitations

The VI structures are **80 bytes**, not 78. `OSViMode` has a one-byte type, three
alignment bytes, nine 32-bit common registers and two sets of five 32-bit field
registers. The last word is `vIntr = 2`; its last two bytes are real payload.
The current archive ELF symbol reports only 78 bytes. Reducing the reference to
that value would encode an incorrect boundary, so it retains the true 80 bytes.
A byte-identical section may consequently remain incomplete in native objdiff.

Anonymous constant pools retain their ROM-derived references. No artificial
candidate symbols, fabricated padding or changes to native counts are used to
make them qualify. Whole-unit completion still requires native data matching.

## Validation and native result

Validated locally on 2026-10-09 with the SDK correction applied to `35193f6`:

- All 95 objdiff tests pass with `CONKER_ROM_TESTS=1`, including a real splat/ROM
  test that checks all 21 declared symbol addresses and payload sizes.
- `./conker build --all` reproduces the US ROM; refreshed GAME integration matches.
- All six grouped code/data images match the original bytes. Native per-unit
  counts reconcile, and completed data never exceeds matched data.
- Eight units recover completion: `n_sl`, `initialize`, `piacs`, `controller`,
  `siacs`, `syncputchars_data`, `exceptasm_data`, and `libm_vals`.
- Matching code stays at 513,144 / 2,246,328 bytes (22.843681%). Fully-linked code
  rises from 115,088 to 117,284 bytes. Matching data rises from 6,336 to 6,544 /
  207,072 bytes (3.1602535%); complete data rises from 5,568 to 5,776 (2.789368%).
- Fourteen downgrades remain: eleven units containing anonymous constants and
  the three VI tables. Their data still matches the ROM at the byte level.

Final report source fingerprint:
`5f4d0dcca454b995af4472563b5430709a5b6b06d6df4a8935e6dd21bb335cf5`.
