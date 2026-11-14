# Scheduled boolean work beside a US switch bound

`func_1511DD98` has the following independently ROM-checked dispatch:

- `0x1511DDC0`: `sltiu at,t9,0x36`, bounding the actual table index
- Three independent instructions compute booleans in a3/a2: xori, xori, sltiu
- `0x1511DDD0`: forward `beqz at` to the common exit path
- Its delay slot is `sltiu a2,a2,1`; it cannot change at or t9
- `0x1511DDD8:0x1511DDEC`: index shift, table-address construction, load,
  indirect jump, and nop delay slot

The old bounded recognizer searched one instruction too short and accepted
only up to two independent loads before the branch. The corrected recognizer
admits at most three instructions there and adds only xori/sltiu to its narrow
independent-opcode whitelist. Their destinations must differ from both the
index and the guard result. The guard still has to test the shift's actual
source register, have a unique nonzero limit no greater than 1024, and feed
the exact forward beqz register. No guessed bound or source-selected table
length is used.

Newly admitted boolean schedules additionally reject direct branches/jumps
into the guarded interior, a guard in a control-transfer delay slot, and an
invalid jump delay. This is explicit direct-edge protection, not general CFG
or arbitrary indirect-entry analysis. Legacy accepted schedules include
reviewed loop-entry and guard-in-delay forms; this narrow correction does not
reinterpret those cases.

For this particular raw function, its only indirect transfers are the
identified table dispatch and canonical return. All 54 entries read from
`0x800A3218` target `0x1511DDF0:0x1511DF3C`, strictly beyond the dispatch
and its delay slot. Its direct transfers have no entry into that interior.
ROM checksum, raw instruction bytes, table extent/targets, candidate
relocations, full candidate span and every relocated case target remain
mandatory checks. Linker placement and full code/rodata equality are separate
subsequent acceptance gates.

Thirteen focused tests cover the original schedules, the exact 54-case new
schedule, unrelated boolean comparisons, wrong guard sources/results,
protected-register writes in every independent position, unsupported opcodes,
invalid limits/branches, incoming direct jumps from either side, signed
backward branches, J/JAL high-address reconstruction, and missing/control-flow
delay slots. Existing corruption, missing-relocation, wrong-extent and
wrong-case tests remain active.

A ROM-backed comparison of all 103 currently emitted raw game switches
preserves all 78 previously accepted references and admits exactly this one
additional reference. The full suite passes 1,075 tests (12 skipped).
No match or linker placement is established by this verifier-only change.

## Wider guard window

`func_150DBD70` (game_109220) and the second dispatch of `func_1514CA80`
(game_179F30) put the guard five words before `beqz at`. Between them,
`func_150DBD70` has four stack stores (`swc1`/`sb`/`sh`/`sb`) and an
`or v1,a0,zero` delay slot. `func_1514CA80` has four `addiu tN,zero,imm`
constants and a fifth in the delay slot. The general case of
`scripts/candidate_tables.py` now searches one more word back (guard at
`index - 10`) and accepts a branch up to five words after the guard. It also
accepts `addiu rt,zero,imm` (`is_constant`) in this window only, and only
into a register other than the guard result or index. Every other invariant
is unchanged: protected-register writes, wider or non-zero-based `addiu`,
other opcodes and direct entries into the guarded region are still rejected.
Any constant load or a gap over three makes the dispatch use the strict
entry checks. Hoisted and distant forms are unchanged.

`WideGuardWindowTests` in `tests/test_candidate_tables.py` covers both raw
shapes and their rejections. The previous "four intervening instructions"
rejection now uses five. A comparison over every US game function in
`progress/functions.json` with a `lui`/`addu`/`lw`/`jr` dispatch (125
functions, ROM words) keeps all 110 previously accepted results byte-identical
(same table offsets, bounds and targets). It admits four more: `func_150DBD70`
(6), `func_1511B07C` (8), `func_15146970` (9) and `func_1514CA80` (187, 54, 19,
10).
