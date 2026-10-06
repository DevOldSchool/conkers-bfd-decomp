# Actor playback-rate update (US)

`func_1505841C` in `game_83300.c` passes authoritative `CURRENT (0)`
across all 468 registered bytes. The source unit remains mixed. The real
actor fields replace equivalent existing padding without changing offsets or
size; the existing actor and inner-state declarations move above their first
new user. The callee `func_1505E650` receives actual floating values in its
third and fourth argument words, as confirmed by raw call and callee handling.

The first direct candidate scored 295, with only register differences.
Separating scaled speed from the destructive rate scale improved it to 85.
An explicit encoded-index temporary did not improve that result and was
removed. Named actor fields reached 35. A full-word local caching the unsigned
byte reached 10; copying speed and applying its scale with a compound update
preserved the raw floating multiply operand order and reached zero. The
successive improvements justified the additional bounded manual revisions.
No permutation, compiler option, assembly, artificial padding, volatile access,
shared header or tool change was used.

Focused acceptance includes source-unit symbol layout, progress and whitespace.
The clean batch for this function and the existing `1505DFDC` actor-layout
regression ended in `BATCH_COMPLETE`. The complete 2,072,880-byte US code
image and all mapped external rodata remained identical to the owned ROM.
All 1,068 tests passed (12 skipped), with progress and whitespace checks.
Only `1505841C` adds a new match; the other ID is an existing-match recheck.
