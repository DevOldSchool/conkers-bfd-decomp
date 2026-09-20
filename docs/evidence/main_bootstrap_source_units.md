# Main bootstrap source-unit boundaries

This note records the reviewed US source-unit boundaries for the two
Conker-specific startup groups preceding the Rare `xldtob.o` object. The names
`init_1050.c` and `init_1420.c` are offset-derived working names; no original
Rare filenames are asserted.

## Inputs

- Canonical US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Independent raw assembly: `reference/us/asm/1050.s` and
  `reference/us/asm/1420.s`.
- Working and reference maps: `config/profiles/us.yaml` and
  `config/reference/us.yaml`.
- Legacy comparison: `mkst/conker` commit
  `3adf229175c037c771f251f169f9dd80ca306924`, especially
  `conker/conker.us.yaml`, `conker/src/init_1050.c`, and
  `conker/src/init_1420.c`.
- Independently reviewed following object:
  `docs/evidence/libultrare_us_formatting_boundaries.md`.

## Reviewed ranges

| US ROM range | Size | Working source | Complete member list |
| --- | ---: | --- | --- |
| `0x1050:0x1420` | `0x3D0` | `src/main/init_1050.c` | `func_80001050`, `func_800010F8`, `func_80001194` |
| `0x1420:0x1550` | `0x130` | `src/main/init_1420.c` | `func_80001420`, `func_80001444`, `func_800014A0`, `func_800014C4` |

The raw assembly has no additional entry points inside either range. The last
function in the first group ends exactly at `0x1420`; the last function in the
second group ends exactly at `0x1550`. Both endpoints are 16-byte-aligned main
map boundaries.

The legacy project independently places `init_1050.c` at `0x1050` and
`init_1420.c` at `0x1420`, with the same member ordering and source grouping.
Its older map leaves the formatting code attached to the latter range, so it is
corroboration for the two starts and the memberships, not evidence for the
second endpoint.

The `0x1550` endpoint is established independently by the complete Rare
`xldtob.o` reconstruction. Its text occupies `0x1550:0x2070`, including the
complete section and final alignment word, and the byte-identical full-ROM link
uses that archive member at `0x1550`. Consequently the preceding proprietary
startup unit cannot extend past `0x1550`.

## Replaced legacy records

The earlier inventory entries described only `func_80001050`
(`0x1050:0x10F8`) and `func_80001420` (`0x1420:0x1444`). Those were function
spans without reviewed boundary evidence, and their non-aligned endpoints could
not represent IDO source objects. They are superseded by the complete ranges
above; the existing exact function result is preserved as function evidence,
not used as boundary evidence.

The old EU record's `0x1050:0x10F8` span is retained only as the independently
matched function's `0xA8` byte count. No EU source-object boundary is claimed.
