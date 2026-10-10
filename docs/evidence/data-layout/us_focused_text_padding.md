# Five US focused text-padding discrepancies

Before the comparator correction below, these five existing matched entries
reproduced nonzero focused scores on the `codex/data-boundaries` worktree based
on `eac2329`. The correction changes neither C source nor match inventory.
The baseline records below distinguish the ELF function size, registered span,
and bytes physically available in the reduced focused object.

| Function | Source under `src/game/` | ELF function bytes | Registered bytes | Missing focused bytes | CURRENT |
| --- | --- | ---: | ---: | ---: | ---: |
| `func_1507EB4C` | `game_AB760.c` | 44 | 52 | 4 | 100 |
| `func_15141928` | `game_16DC80.c` | 64 | 72 | 8 | 200 |
| `func_1515D130` | `game_1897A0.c` | 772 | 784 | 12 | 300 |
| `func_151898C0` | `game_1B5CC0.c` | 56 | 64 | 8 | 200 |
| `func_1519EF04` | `game_1CBE20.c` | 100 | 108 | 8 | 200 |

The displayed mismatches are exclusively absent terminal NOP words. The ELF
function size comes from compiler metadata, not from searching for a return
instruction or truncating the reference. For `1507EB4C`, the focused object
contains four zero alignment bytes after its 44-byte function but still lacks
four bytes of the 52-byte registered span.

## Cause and ownership

All five are final functions in registered mixed source units. The existing
`diff.focused_candidate_source` removes unrelated `GLOBAL_ASM` members before
compilation. That changes each terminal function's section offset and the
amount of padding produced by the compiler's 16-byte section alignment.
A byte tail present in the complete mixed object can therefore be absent from
the focused object even when its C instructions are unchanged.

Before this correction, GAME selected its full-unit proof only for supported
address-alias cases. Padding-only discrepancies retained the nonzero focused
scores above. Those baseline scores are not new C matches or evidence that a
shortened span should be accepted.

| Function | Registered source-unit address range | Function-end tail |
| --- | --- | --- |
| `1507EB4C` | `0x1507E2B0–0x1507EB80` | `0x1507EB78–0x1507EB80` |
| `15141928` | `0x151407D0–0x15141970` | `0x15141968–0x15141970` |
| `1515D130` | `0x1515C2F0–0x1515D440` | `0x1515D434–0x1515D440` |
| `151898C0` | `0x15188810–0x15189900` | `0x151898F8–0x15189900` |
| `1519EF04` | `0x1519E970–0x1519EF70` | `0x1519EF68–0x1519EF70` |

All ends are exclusive. The authoritative working-group boundaries and evidence
references remain in `progress/source_units.json` and `config/game/us.yaml`.
These are existing reviewed working groups; this audit does not recover their
historical filenames or prove original object ownership from alignment alone.
The tails belong to the reviewed text spans, not to the loaded game-data image.

## Reproduction

Run each of these from the repository root:

```sh
./conker diff func_1507EB4C
./conker diff func_15141928
./conker diff func_1515D130
./conker diff func_151898C0
./conker diff func_1519EF04
./conker game-build --refresh
```

`diff` is diagnostic and can exit zero while displaying a nonzero CURRENT
score; check the score itself. The saved local results are in
`build/us/data-boundaries/padding-review/`, including the five full diffs,
`focused.json`, the GAME build log and the numerical boundary audit.

## Current linked verification

On 2026-10-08, the rebuilt 2,072,880-byte GAME code image matched the decoded
checksum-validated US ROM exactly. All five complete mixed objects passed the
existing member-offset/layout verifier. Their measured `.text` sizes were
exactly 2,256, 4,512, 4,432, 4,336 and 1,536 bytes respectively, each aligned to
16 bytes and equal to its registered source-unit extent. No linker-added bytes
were needed to supply these tails: the bytes already exist in the mixed objects.
Every target linked at its registered address; its complete registered span and
its complete containing unit matched the ROM, including all 44 tail bytes.

The focused objects lack 40 of those 44 bytes in total. Their reduced offsets
change section rounding; `1507EB4C` retains four of its eight tail bytes.
The prior spark naming audit recorded eight missing bytes; the current source
context yields twelve. The current measurements above supersede that old count
for this checkout, without changing the registered span.

## Implemented comparison correction

`linked_aliases.game_eligible` now permits an attempt at full-unit proof when
the ELF function extent is shorter than its registered span by 4, 8 or 12 bytes.
This eligibility check grants no match and does not append bytes to the focused
object. `diff.prepare_game_comparison` freshly compiles the complete source unit
and independently assembles the raw reference, using its existing input
fingerprints to reject changes during proof.

`linked_aliases.prepare_game` requires the target to end at the reviewed unit
endpoint. The complete span must physically exist in its real `.text` section;
its terminal padding must be zero, without another symbol or relocation. Every
registered member must retain its offset, the object must have exactly the
registered unit extent and 16-byte alignment, and all dependencies must pass the
existing restrictive relocation proof. The independently linked reference and
target must match the original ROM span; the entire linked candidate unit must
also match its ROM interval. Only then are full-length comparison objects passed
to the unchanged bounded asm-differ gate. Unsupported dependencies still cannot
use this path, and watch mode remains symbolic.

On 2026-10-08, all five functions passed the strict `--require-match` path with
`CURRENT (0)` over their original registered spans. The opt-in regression also
verified each entire candidate unit against the checksum-validated ROM and
checked that C sources and match inventory remained unchanged. These are
comparison-tooling repairs to existing matches, with no new match credit.

Validation in the pinned Docker toolchain:

- `CONKER_ROM_TESTS=1 python3 -m unittest discover -s tests -p
  'test_game_comparison.py' -v`: all 24 tests passed, including the five real
  padding cases, existing alias cases, and the held jump-table rejection.
- Related linked-alias, debugger, main comparison, diff, registered-span,
  jump-table, layout and candidate-compilation suites: 123 tests, 121 passed
  and two opt-in tests skipped.
- Negative cases cover absent padding, nonzero/named/relocated tails, extended
  objects, wrong instructions, wrong neighbors, shifted members and unreviewed
  boundaries. Existing stale-input and full-span scoring checks also passed.

Local logs are `build/us/data-boundaries/padding-review/regression-game.log`,
`regression-related.log`, and `fixed-func_*.log`. The baseline `focused.json` and
`boundaries.json` remain diagnostic records of the original reduced objects.
