# Emitter-state callback matching (US)

The existing reviewed `game_1897A0.c` group contains the table-driven emitter
`func_1515D130` and the state constructor `func_1515D088`. Its source boundary
and retail callback-table evidence remain as documented in
[the group review](../boundaries/game/mapping/game_remaining_upstream_c_groups.md).

## State constructor

The preserved 168-byte `func_1515D088` candidate scored `CURRENT (121)`. The raw
code places its real 12-byte owner/value/selector packet at SP+0x30 and the
saved allocation result at SP+0x3C. Declaring the used result before the packet
recovers this ordinary local order, without padding or artificial fields.

The raw word loaded from owner+0x18 feeds both the selector-byte store and the
unsigned range check. Assigning the packet selector first, then converting it
to `u8` for that check, reproduces the original temporary-register allocation.
These two source-only changes produced full-span `CURRENT (0)` on the first
revision. Source-unit symbol layout, progress and whitespace gates passed.
The source unit remains mixed; matching this member does not complete it.

## Unmatched callback follow-up

`func_1515CF9C` retains its original 265 candidate. Its body is exact until the
return-tail branch scheduling. An explicit successful-path return scored 600;
per-branch assignments to a common result returned 265. Both were discarded.
No extra instructions or function-span changes were used to fill the difference.

`func_1515C534` improved from 179 to 58 after removing spurious third and fourth
callback arguments. The local table members `func_1515CF9C` and `func_1515D030`
use two arguments; a2 retains the owner in this caller and a3 holds its callback-
failure flag, rather than establishing additional callback parameters. The
source-local callback typedef now expresses that two-argument contract.

Its remaining difference is the settings-pointer spill offset plus flags/time
register allocation. An explicit time local scored 78; a byte-sized callback-
result local scored 578. The best 58 candidate is preserved and disabled, with
original assembly active. No automated permutation or shared-header change was
used in this group.

Clean validation on 2026-09-30 returned `BATCH_COMPLETE` for `func_1515D088`:
the complete US game-code image and existing external rodata matched the owned
ROM; all 1,068 tests passed (12 skipped), with metadata, progress and whitespace
checks also passing.
