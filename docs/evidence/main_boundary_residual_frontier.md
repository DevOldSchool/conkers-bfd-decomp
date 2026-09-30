# US main boundary review: remaining frontier

This records the remaining frontier of the ongoing 2026-09-30 main review.
It is separate from the already complete game-overlay ownership map and from
ASM-to-C implementation progress.

## Verified progress

Five registration batches added twenty reviewed working source units,
193 entries and 49,360 bytes. Together with the two earlier bootstrap units,
a sixth batch adds one 96-byte fixed-TLB original-assembly unit. Main now has
twenty-three reviewed units, 201 registered entries and 50,736 reviewed source
bytes. All previously registered functions, source units,
match states and matched-byte counts were preserved exactly. The canonical
main and raw-reference maps were not changed.

The CPU interval `0x1050:0x290D0` consists of:

| Classification | Bytes |
| --- | ---: |
| Already exact CPU library text | 98,512 |
| Reviewed working source units, canonically raw | 50,736 |
| Nine remaining raw navigation ranges | 14,720 |
| CPU interval total | 163,968 |

The handwritten `0x1000:0x1050` entry is outside this interval. The existing
progress denominator ends at `0x292F0` and therefore includes a further 544
RSP bytes; this review does not silently change that denominator.

The new memberships and positive evidence are in:

- [System wrappers](main_system_wrapper_boundaries.md): ten units, fourteen entries, 3,616 bytes
- [Allocation, transfer, scheduler and controller](main_allocator_transfer_controller_boundaries.md): five units, twenty-six entries, 8,032 bytes
- [Audio driver and sequence controller](main_audio_driver_sequence_boundaries.md): two units, sixty-five entries, 19,936 bytes
- [Sound-record callbacks and handles](main_sound_record_family_boundary.md): one unit, fifty-four entries, 13,472 bytes
- [Sequence API and MP3 adapter](main_sequence_api_mp3_adapter_boundaries.md): two units, thirty-four entries, 4,304 bytes
- [Fixed TLB alias](main_tlb_alias_boundary.md): one unit, one verified original-assembly span, 96 bytes

These are evidence-backed working families. They do not claim that every
historical object boundary or original filename has been recovered.

## Remaining exact ranges

| US ROM range | Bytes | Current result | Required next evidence/action |
| --- | ---: | --- | --- |
| `0x38C0:0x38E0` | 32 | Varargs-style empty stub, no direct call found in either scanned CPU image | Find an owned selector/reference or independent original grouping; do not name it from its common shape |
| `0x38E0:0x3920` | 64 | Two complete indexed entries, but no reviewed relationship between hardware-writing `0x38E0` and zero-return `0x390C` | Prove common ownership or a justified finer representation; the internal start is not 16-byte aligned |
| `0x39B0:0x39C0` | 16 | Ambiguous no-op return already rejected as a stock SDK identity | Preserve explicit uncertainty unless new ownership evidence appears |
| `0x50A0:0x5570` | 1,232 | Raw/independent-index membership disagreement at `0x5298` | Reconcile the empty entry through regenerated references, then review complete family membership |
| `0x5AB0:0x6240` | 1,936 | Handwritten TLB/control code with alternate entries; unsplit IDO analysis merges across true control transitions | Review explicit entries/shared ABI and support original-assembly ownership without treating every label as an ordinary C function |
| `0x6240:0x71D0` | 3,984 | Split raw entries exist, but independent unsplit index is swallowed by the preceding handwritten range | Reconcile an independently seeded/range-scoped index and inspect alternate entries before registration |
| `0x71D0:0x8120` | 3,920 | Handwritten exception/control paths include callable internal labels not represented as ordinary top-level indexed members | Model complete entry/alias membership and validate against raw words; do not drop those entries |
| `0xA420:0xB1B0` | 3,472 | `0xA420/0xA750` are call-connected; `0xB060` is separately called spatial/pan math | Complete the ownership argument or use a reviewed finer split at aligned `0xB060`, with raw regeneration and main-map validation |
| `0x226B0:0x226F0` | 64 | All zero words, explicitly outside the exact preceding `n_resample.o` | Classify as known padding without inventing its original object owner or a C function |

The first three ranges total 112 bytes. Their bounded negative call scan does
not establish that they are unreachable. The known padding contributes no
callable member and must not be registered as one merely to eliminate a raw
map entry.

## Concrete index conflicts

The independently generated unsplit CPU CSV reports:

- `0x5218:0x5298` followed by `0x5298:0x52A0`. The current raw split labels
  only `0x5218`; ROM words at `0x5298/0x529C` are `jr $ra; nop`.
- A combined `0x5AB0:0x5BE0` span, while raw reference labels expose separate
  `0x5AB0` and `0x5B04` entries.
- A `0x5C2C:0x7C74` span that crosses the `0x6240` and `0x71D0` navigation
  ranges. This is a disassembler control-flow limitation, not proof that they
  were one C object.

Raw assembly also contains indented global labels. Examples are `0x5B3C`
and `0x77B8`; the latter has direct callers including `0x74A4`, `0x74CC` and
`0x77A8`. The ordinary registration parser recognizes only its supported
top-level function-label form. Indented labels can represent alternate entries
or internal targets, so a blanket parser change that promotes all of them to
ordinary functions would be unsafe. Review their ABI and control flow first.

The existing game empty-stub reconciliation is a useful precedent, not proof
for main: [reconciled empty stubs](game_raw_reconciled_empty_stub_splits.md).
A fresh reference generation is essential after any justified symbol/split
change; stale raw caches can conceal the disagreement.

## Safe completion sequence

1. Keep the reviewed metadata separate from concurrent game matching. Reconcile
   by replaying the documented registration transactions onto the chosen
   integration baseline, preserving newer matches and source-unit states.
2. The exact full-main/RSP capability is now restored, with byte-identical full
   ROM equality. See [toolchain and verifier evidence](main_original_assembly_verification.md).
   Retain this gate for any canonical split or original-assembly registration.
3. Resolve the `0x5298` member disagreement first. Regenerate independent raw
   references, compare every word against the owned ROM, and re-review the
   complete `0x50A0:0x5570` family rather than simply attaching a label.
4. Review the handwritten/alternate-entry ranges as original assembly. Keep
   assembly preservation separate from matching C; any supporting tooling
   change needs dedicated tests and final full-ROM equality.
5. Resolve the spatial/pan range through stronger shared-ownership evidence or
   justified smaller units. Keep unknown stubs and padding explicitly classified
   if original ownership cannot be established.
6. Refresh ownership reporting from the canonical intervals and inventories,
   keeping CPU code, RSP, text-resident data, padding and C-match progress as
   separate claims.

Completion requires evidence-backed membership/classification for every scoped
range and all applicable registration/map/build gates. Eliminating `asm` tokens
or incrementing a percentage is not a substitute for that evidence. No unchanged
stock-library scan or exhausted matching candidate is repeated by this plan.

## Verification at handoff

All earlier function and source-unit records remain unchanged. The new units
are `raw_asm`, with no C-match or matched-byte change. Focused metadata and map
tests pass after every batch; a full repository run passes 1,067 tests with
12 declared skips. Generated progress and whitespace checks pass. Raw-word,
unsplit-index, branch and specific callback evidence are recorded in each batch.

The sixth batch passes the full US ROM build, a 96-byte original-assembly
proof, and clean `BATCH_COMPLETE`; the expanded suite passes 1,070 tests with
12 declared skips. No new C-function match, mixed main integration or
combined-branch integration is claimed. The raw references and owned ROM remain
private ignored research inputs; only source/evidence/metadata are committed.

## Separate game function-span caveat

Complete game-overlay source ownership does not establish that every retained
raw function span is already a complete C-rewrite target. The existing
[dispatcher evidence](game_dispatcher_callback_groups.md#resolving-the-function-index-disagreements)
explicitly retains the unproven interior entry proposals `0x15040A4C`,
`0x15073070` and `0x1513E134` inside preceding raw spans.

The current deferred record for `func_15040A40` is a concrete consequence:
its 20-byte span includes the twelve-byte `sw/jr/nop` stub followed by an
unlabelled eight-byte `jr/nop` at `0x40A4C`. The preserved attempt is nonzero;
this review does not claim it was rerun. Shortening the registered span or
inventing a second function just to get zero difference would be unsupported.
Find independent entry/selector evidence first, then reconcile all affected
members and independently regenerate/verify their complete spans. The enclosing
reviewed source-unit range `0x40350:0x40D90` remains fully owned throughout.
No game registration or matching source is changed by this note.
