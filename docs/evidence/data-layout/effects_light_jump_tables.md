# US nested switch tables for effects/light

`func_151604A0` dispatches through two contiguous tables in the US game-data
archive. The outer switch has twelve entries at `0x800A6A18` and its nested
switch has 35 entries at `0x800A6A48`. Raw HI16/LO16 instructions at
`0x151604D0` / `0x151604D8` and `0x15160500` / `0x15160508` establish these addresses.

The outer table selects `0x151604E4` for indices 0, 1, 5, 8 and 11; all other
indices select `0x151605C8`. The nested table selects `0x15160514`,
`0x15160520`, `0x15160530`, `0x151605A4`, and `0x151605B8` at indices
23, 24, 28, 31, and 34 respectively. All other nested entries select
`0x151605EC`.

The 188-byte ROM payload has SHA-256
`8c869cc9cc5968e21d64a859801d9239bef047ea007949454b7ad476ddd280e5`.
It was read from the checksum-validated US ROM
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The compiled source unit emits
47 table relocations followed by four zero alignment bytes: 192 bytes total.
The layout object SHA-256 at verification was
`e0e5d70bdcd6af39af22fde94fa9e11b4c95083f2cea8db8dc73709dbb1987eb`.

The reviewed linker mapping consumes `light.o(.rodata)` at `0x800A6A18`
as an INFO section with `SUBALIGN(4)`, a `0xC0` section-size assertion and
`0xBC` payload extent. The owner record includes both the current source path
and its completed-unit alias. The original archive supplies these bytes at
runtime; the four compiler alignment bytes do not claim adjacent ROM data.

The candidate verifier recognizes the independent move in the outer bounds
branch delay slot and the nested shift hoisted across a conditional exit.
It checks the protected registers, forward exit destinations, direct entries,
and table entries that could bypass the bound. Unit tests include malformed
variants and the raw nested dispatch. Full-span CURRENT (0), candidate table
relocations, source layout, and clean linked-ROM batch verification remain
separate gates.
