# US byte-opcode command handlers

`D_800844B0` is a 256-entry function-address table covering exactly
`800844B0..800848B0` (1,024 bytes). It contains 56 distinct callbacks and no
null entries. This reconstruction gives the table a data-only source owner;
it does not claim an original C-object boundary or change any function body.

## Native bounds and callback declarations

Both complete consumers are independently checked against the US ROM and raw
assembly: `15040A78` (592 bytes) and `15040CC8` (152 bytes). The first loads an
unsigned byte at `15040B00`, shifts it left two bits at `15040B04`, adds it to
the table base, loads the pointer at `15040B10`, and calls it at `15040B1C`.
The second establishes the same base at `15040CF4..15040CF8`, loads an unsigned
byte at `15040D08`, shifts by two, then loads/calls the selected pointer at
`15040D14..15040D18`. All 256 byte values therefore select exactly one of the
256 words. The extent follows from these instructions, not a neighboring symbol.

All 56 callback targets have existing matched definitions in
`src/game/game_6D800.c`. The data source retains their concrete declarations.
Its generic function-pointer type stores heterogeneous code addresses and never
calls them; explicit casts do not change the callbacks' integer-register ABIs.
The two dispatcher functions remain unmatched and retain their existing
assembly and deferred candidates. This data work awards no code credit.

## Source and build placement

`src/game/data/command_handlers.c` records all 256 symbolic callback addresses,
with their opcode positions. IDO emits 256 pointer relocations. An explicit
1,024-byte INFO section places the compiled table at its original address for
verification. As with the other GAME data-only owners, the original GAME
archive still supplies runtime storage. This can add matched data, not complete
data. The following 32 bytes before the character map stay unclaimed.

## Validation

[Machine-readable evidence](us_command_handlers.json) records full native
consumer hashes, typed symbolic slots, compiled pointers and the report digest.
The actual compiled table has 256 pointer relocations, and the independently
assembled reference has the same destinations and scalar bytes. The linked INFO
section reproduces all 1,024 original bytes. All four consumer endpoint mutations
and all 1,024 byte-position mutations reject a perfect native match. The following
32-byte range remains unassigned. No source function or assembly was edited.

Accepted at base `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus
uncommitted changes. The combined index/handler batch passes 72 focused tests
(two skips), the Make dependency/recovery test (8.514 seconds), and all 3,032
Docker tests (eight skips, 255.838 seconds). The US asset build passes in 170
seconds, including a 147.977-second compile/link/verification stage. Independent
extraction of the current linked ELF reproduces the 67,108,864-byte US ROM with
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The full native report adds exactly 2,960 matched data bytes and 1,936 complete
data bytes. Matched data is 63,297,239 / 65,120,512 (97.20016%), with 1,823,273
bytes remaining. Code measures are unchanged. All 27,295 prior editable asset
input hashes and 11,836 prior asset object hashes are preserved; six new index
source files are added. All 209 prior GAME compiler objects retain identical
allocated sections, relocation records and symbols. The entire 2,072,880-byte
GAME code image remains exact. The snapshot is current, compile errors are zero,
and progress/whitespace gates pass.
