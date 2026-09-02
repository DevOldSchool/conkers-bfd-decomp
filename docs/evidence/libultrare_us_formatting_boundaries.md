# US Rare formatting-library boundaries

This note records the reviewed main-executable boundaries and function identities
for Conker's Rare-modified formatting code. It creates matching work; it does not
claim that any function or object is instruction-identical yet.

## Evidence

- Canonical US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Raw comparison map: `config/reference/us.yaml`, with the corresponding
  independently generated blocks under `reference/us/asm/`.
- GoldenEye identifies its `libultrare` directory as Rare-modified and places
  `xprintf.c` there, while keeping `xldtob.c` with the original libc sources.
- GoldenEye's Rare `_Printf` has the same distinctive positive-byte scan and
  pointer rollback used at Conker `0x800020D0`.
- GoldenEye and libreultra's sync-print implementations identify the discard
  callback followed by the `_Printf(callback, NULL, fmt, args)` wrapper at
  Conker `0x80002070` and `0x80002088`.
- Stock I/J/K/L object symbols and the corresponding source structure identify
  the private `_Ldunscale`, `_Genld`, and `_Putfld` helpers.

External source references:

- <https://github.com/n64decomp/007/blob/master/src/libultrare/readme.md>
- <https://github.com/n64decomp/007/blob/master/src/libultrare/libc/xprintf.c>
- <https://github.com/n64decomp/007/blob/master/src/libultra/libc/xldtob.c>
- <https://github.com/n64decomp/007/blob/master/src/rmon.c>
- <https://github.com/n64decomp/libreultra/blob/master/src/libc/syncprintf.c>

## Reviewed source units

| US ROM range | VRAM range | Size | Proposed source | Members |
|---|---|---:|---|---|
| `0x1550:0x2070` | `0x80001550:0x80002070` | `0xB20` | `src/libultrare/libc/xldtob.c` | `_Ldtob`, `_Ldunscale`, `_Genld` |
| `0x2070:0x20D0` | `0x80002070:0x800020D0` | `0x60` | `src/libultrare/libc/syncprintf.c` | `proutSyncPrintf`, `osSyncPrintf` |
| `0x20D0:0x2DB0` | `0x800020D0:0x80002DB0` | `0xCE0` | `src/libultrare/libc/xprintf.c` | `_Printf`, `_Putfld` |

`0x1550` begins immediately after the preceding startup function. `0x2070`
follows `_Genld` and its alignment word. `0x20D0` follows the sync-print wrapper.
`0x2DB0` follows `_Putfld` and two trailing alignment words and is already the
next raw-ASM map boundary. All three ranges use 16-byte IDO object boundaries.

## Function work items

| Work-item ID | US symbol | VRAM | Recovered extent | Size |
|---|---|---:|---|---:|
| `_Ldtob` | `func_80001550` | `0x80001550` | `0x1550:0x19F0` | `0x4A0` |
| `_Ldunscale` | `func_800019F0` | `0x800019F0` | `0x19F0:0x1AA8` | `0xB8` |
| `_Genld` | `func_80001AA8` | `0x80001AA8` | `0x1AA8:0x2070` | `0x5C8` |
| `proutSyncPrintf` | `func_80002070` | `0x80002070` | `0x2070:0x2088` | `0x18` |
| `osSyncPrintf` | `func_80002088` | `0x80002088` | `0x2088:0x20D0` | `0x48` |
| `_Printf` | `func_800020D0` | `0x800020D0` | `0x20D0:0x2718` | `0x648` |
| `_Putfld` | `func_80002718` | `0x80002718` | `0x2718:0x2DB0` | `0x698` |

The final recovered extent in each source unit includes any compiler-emitted
tail padding before the next reviewed object boundary. Focused matching still
stops at the function return.

The corresponding complete `xldtob` and `xprintf` initialized/read-only data
sections are now archive-backed at `0x2AAF0:0x2AB40` and
`0x2BF20:0x2C080`. Their separate build representation and exact checksums are
recorded in
[`libultra_us_data_object_bounds.md`](libultra_us_data_object_bounds.md).

## Limits

The text identities and boundaries are strong structural evidence, not a
byte-exact archive match. GoldenEye supplies the closest Rare source lineage,
but its compiled helper order and some instruction details differ. These text
units must remain raw assembly until their C implementations reach `CURRENT
(0)` and the complete US build remains byte-identical. Their exact data
sections do not imply that the text already matches.
