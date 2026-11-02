# US switch table for game_20BDA0

`func_151E2404` copies a ten-byte record and dispatches the record index 0
through 9 through ten word-sized jump targets. The raw HI16/LO16 address pair
(`0x151E247C`/`0x151E2484`) identifies the table at `0x800AB9BC` in the
separately loaded US game-data archive.

| Selector | Target | Body |
| --- | --- | --- |
| 0 | `0x151E2490` | `record[5] = source[4]` |
| 1, 2 | `0x151E249C` | `record[5..6] = source[0xD..0xE]` |
| 3, 4, 6 | `0x151E24CC` | none (shared tail) |
| 5, 7 | `0x151E24B0` | `record[5] = source[0x12]` |
| 8, 9 | `0x151E24BC` | `record[5] = source[7]`, `record[6] = source[0x13]` |

All ten relocated words were independently compared with the checksum-validated
US ROM using `rom_game_data` from `scripts/verify_game_rodata.py` (game-data base
`0x80082B20`). The object contains a 48-byte `.rodata` section, ten word
relocations against `.text`, 40 payload bytes and eight zero alignment bytes.
The ROM words after the table (`0x40490FD0 0x3FC90FD0` at `0x800AB9E4`) belong
to the following unit, so the alignment bytes are checked in the object only.

The mapping in `config/game/us-rodata.ld` places this section at `0x800AB9BC`
as informational data with `SUBALIGN(4)`, an exact 48-byte size assertion and a
40-byte payload-size symbol. The other `game_20BDA0` members are `GLOBAL_ASM`
and emit no `.rodata`; their tables (`jtbl_800AB960`, `jtbl_800AB978`,
`jtbl_800AB994`) and literals precede this table in ROM. Matching one of them
grows the object's `.rodata`, which fails the exact size assertion, so the
unit then needs a `scripts/split_game_rodata.py` layout as described in the
[sub-pool record](game_rodata_literal_sub_pools.md).

## Dispatch shape

IDO schedules the bound check (`sltiu at,v1,10`) and the index shift
(`sll t5,v1,2`) ahead of ten record-copy loads and stores, leaving only
`beqz at` and its `sb` delay slot before `lui`/`addu`/`lw`/`jr`.
`scripts/candidate_tables.py` accepts this distant form only when the guard
immediately precedes the shift, at most eleven stores, loads, `addu`/`subu`/`or`
or `mflo`/`mfhi` instructions (and the delay slot) separate them from the
branch, none writes the index, guard or shift register, the guard is not in a
delay slot, and no direct edge or table target enters the guarded region.
`tests/test_candidate_tables.py` covers the US words and each rejection.

## Recognizer audit

The old and new recognizers were run over all 87 raw game functions with a
jump table, against the checksum-validated US ROM. Two results changed:

- `func_150538CC` (game_80B80) is now accepted. Its second dispatch is
  `sltiu at,t7,15; sll t7,t7,2; beqz at` with a `swc1` delay slot: the guard
  reads the index before the shift overwrites it, and the ROM table has 15
  entries. Its first dispatch was already in the supported form.
- `func_15007168` (game_33990) still fails, now as "switch bound is missing
  or ambiguous" instead of "unsupported switch dispatch shape".

No previously accepted function changed. No debugger-overlay raw assembly with
a jump table is present under `asm/`, so none was compared.

## Call argument

The raw function loads `&D_800E0BE0` into `a0` and never writes `a0` again
before calling `func_150076A0`. About thirty source forms without an argument
(local or global source, declaration and assignment orders, `volatile` or
not, index and record types) all allocate the pointer to `v1`; passing it
reproduces the original `a0`. The callee (game_33990.c) cannot take a
parameter: an unused named parameter makes IDO store `a0` to its home
(CURRENT 200), which the original does not. So the original caller passed an
argument that the parameterless callee ignores. `func_151E2404` is the only
caller, called itself without arguments from `func_151E09DC`.

As with `func_150ADA20` ([shared RNG prototype](../matching/rng_shared_prototype.md)),
the caller's declaration is deliberately unprototyped, `void func_150076A0();`,
and passes `D_800E0BE0` without a cast. The callee definition keeps `(void)`.
