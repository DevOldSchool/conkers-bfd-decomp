# US model defaults and direct drawing data

This batch reconstructs 1,864 native bytes: 1,368 bytes of model
defaults at `800A26C0` and ten directly submitted display lists totaling
496 bytes. Forty compiler alignment bytes are excluded from matching credit.

## Model defaults

`src/game/data/model_defaults.c` contains 114 twelve-byte records. The full
2,964-byte original `func_150039E0` is ROM-checked. It uses the same selector
for a bank-03 model load and for `800A26C0 + selector * 12`. The multiply is
implemented as `(selector * 4 - selector) * 4`.

The original loads establish every byte's field width and signedness:

| Record offset | Native load | C field |
| --- | --- | --- |
| `00` | unsigned byte | `u8 field00` |
| `01` | unsigned byte | `u8 field01` |
| `02` | signed halfword | `s16 field02` |
| `04` | signed halfword | `s16 field04` |
| `06` | unsigned halfword | `u16 field06` |
| `08` | unsigned byte | `u8 field08` |
| `09` | unsigned byte, flags masked before storage | `u8 flags09` |
| `0A` | unsigned halfword, stored as object flags | `u16 flags0A` |

The ROM placement scan finds 66 distinct bank-03 selectors on the native
defaults path. Two resolved placement records select index 113, the final record,
which is all zero. Function literal pools and a jump table follow it, so the
114 records are the whole table. This does not claim that all intermediate
records execute. There are no opaque bytes or guessed padding fields in the
twelve-byte record. The compiler emits 1,376 bytes; its final eight zero
alignment bytes are not part of the reconstructed table.

## Direct drawing lists

The sources in `src/game/data/draw_graphics/` use SDK `Gfx` macros. Complete
original functions are checked against the ROM before verifying their paired
`DE000000` command and address stores. The companion evidence records the
full spans and the precise instruction addresses.

| List address | Bytes | Proven submitting function |
| --- | ---: | --- |
| `80084160` | 48 | `func_1502BAD0` |
| `80084190` | 40 | `func_1502BAD0` |
| `80084350` | 48 | `func_150368C4` |
| `800859A0` | 40 | `func_1516C934` |
| `80086B80` | 32 | `func_1507DB6C` |
| `80087390` | 32 | `func_150918EC` |
| `8008CFA0` | 72 | `func_1517D074` |
| `8008D018` | 56 | `func_15180580` |
| `8008D448` | 80 | `func_15184FA4` |
| `80090028` | 48 | `func_151E89A0` |

Every list ends with its own EndDL command. Adjacent gaps and other data are
excluded. Command fields preserve the original geometry modes, colours,
texture state, combiner selectors, conversion coefficients, scissors and
fill rectangle. The four lists whose size is not a multiple of sixteen
produce 32 compiler alignment bytes in total; those bytes receive no credit.

Two matrix commands store physical address `00089470`, the physical alias of
the previously reconstructed identity matrix at `80089470`. Their source
uses `(u32)&D_80089470 - 0x80000000U`, preserving a real `R_MIPS_32`
relocation and its `80000000` addend. The independent reference declares
the same matrix symbol with addend `-0x80000000` at the two native address
words, `8008416C` and `8008CFA4`. Scalar command words do not acquire inferred
pointer relocations. No numeric pointer replacement or assembly edit is used
to make the candidate match.

## Build and verification

All eleven owners are linked at their native addresses in INFO sections,
with exact emitted-size assertions and separate payload sizes. The original
GAME archive still supplies runtime data. The batch adds matched data only;
it does not increase complete data. All selected bytes were unassigned in the
accepted rendering-state baseline.

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted
work. The GAME build and focused tests pass. Actual linked source data
reproduces all 1,864 bytes and both physical matrix references. All 767 prior
GAME objects preserve allocated bytes, symbols and relocations, with no
exceptions. The entire 2,072,880-byte GAME code image and the function/source
inventories are unchanged. Independent native objdiff matches all eleven
owners, 1,864/1,864 bytes. Mutating each payload byte, changing either matrix
destination, or removing either physical-address addend produces 1,868
rejected comparisons.

The full suite passes: 3,033 tests, eight skips, 307.215 seconds. The US
`./conker build --assets` passes and the independently extracted 67,108,864-byte
linked ROM has SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, identical
to the original. Build wall time was 206 seconds; compile/link/verify was
175.641 seconds. Full report preparation took 486.6 seconds, followed by
32.3 seconds for comparison and validation.

Accepted matched data is **63,311,271 / 65,120,512 bytes (97.2217%)**, a gain
of 1,864 bytes; **1,809,241 bytes remain**. Complete data stays at 63,245,911
bytes. Code and function measures are unchanged. All 27,301 prior asset input
hashes and 11,836 asset object hashes are preserved. The eleven actual INFO
objects agree with the report's copied-source candidates; the runtime data
graph and original-assets ELF are unchanged. Progress and whitespace pass.

Report SHA-256:
`9f59c74f50e58d05a773f73f5b07aee950f09e76232413fb6d71840c275217c6`.
Source fingerprint:
`a736505f6f875387caf8bba7223686ab778a616e848f1ef0f488dd912b6f2bc1`.

The companion JSON preserves the native caller/field evidence and storage
hashes. Temporary scripts and audit results are under
`build/us/data-completion/model-draw-*`.
