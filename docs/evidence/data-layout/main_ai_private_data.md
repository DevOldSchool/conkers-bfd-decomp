# AI buffer submission private data

The reviewed singleton `func_80002DB0` owns the complete 160-byte ROM text
span `0x2DB0:0x2E50`; its working text boundary remains documented in
`main_system_wrapper_boundaries.md`. This note adds a private-data mapping,
without changing any text boundary or claiming a historical filename.

The pinned SDK `lib/ultralib/src/io/aisetnextbuf.c` independently identifies
the routine's initialized function-local `static u8 hdwrBugFlag`. Its
pre-I mask and pre-J device-busy ordering agree with the US instructions.
The preserved implementation retains that byte, the adjusted buffer snapshot,
and two aligned volatile writes to AI registers `0xA4500000` and `0xA4500004`.
No hardware register is modeled as ordinary nonvolatile storage.

The original raw instructions at `0x80002DBC/0x80002DC0`,
`0x80002DE8/0x80002DF0`, and `0x80002DF4/0x80002DF8` load/store one byte at
`0x8002AB40`. A complete named raw-reference search finds flag accesses only
in this routine. This is positive static ownership evidence together with the
SDK private variable; absence of indirect aliases is not claimed. The original
next labeled storage starts at `0x8002AB50`. The checksum-validated US ROM
contains sixteen zero bytes at `0x2AB40:0x2AB50`, immediately after xprintf data.
Only the first byte is claimed as the variable; the remaining fifteen bytes
are the compiler's observed section alignment, not invented C objects.

With the pinned compiler and unchanged flags, the real mixed object has a
160-byte .text section (148-byte function symbol plus its actual three padding
words), and a 16-byte, 16-aligned, zero-filled .data section. Its six flag
relocations reference the .data section at zero addend; the private variable
has no ordinary ELF symbol. Merely renaming relocations is insufficient proof.

`config/main/private-data.json` records the reviewed source aliases, .data
address, extent, alignment, flags, original ROM digest and this ownership note.
`scripts/main_private_data.py` consumes this contract through the existing main
layout gate. It validates the actual compiler section and preserves natural
linker resolution of its relocations; no individual variable is rebound.
It independently links the raw object and the candidate. All 160 text bytes,
including actual padding, must equal the raw object and checksum-validated ROM.
The linked data's payload and address, extent, alignment and type must agree too.
Unregistered local-data cases retain conservative rejection; originals are never
rewritten. The manifest framework also supports reviewed nonzero .data, .sdata
and .rodata, while additional storage and pointer initializers are rejected.

For integration, the generated `build/us/main-private-data.ld` consumes only the
active source's exact object into a non-allocated INFO PROGBITS section at
`0x8002AB40`. Original allocated main data supplies ROM/RAM backing. The build
verifier requires the reviewed INFO contract and ownership, checks its full
payload and backing, and compares every byte of the entire reviewed source unit
with the US ROM. Normal whole-ROM comparison remains mandatory.

Final validation: full-span US `CURRENT (0)` and layout attempt
`12096ada8085474a90a6a812ec009756`; supported integration completed
`src/done/main/init_2DB0.c` and reproduced the whole US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Clean `BATCH_COMPLETE` ran
1,902 tests successfully (40 skipped). The pinned comparison/layout regression
suite ran 55 tests successfully (2 skipped), including all nine new AI tests.
The C body is byte-for-byte identical to the best preserved candidate.
The host dependency gap found during this validation is now covered by pinned
`./conker host-setup` and early `host-check` readiness/batch gates.

General framework validation: changed-tooling `finish` attempt
`2365168920724186af89a8a815363722` retained full-span `CURRENT (0)` and layout.
The clean batch passed 1,910 tests (41 host skips), exact whole-ROM comparison,
all storage verifiers, metadata, progress and whitespace. Forty pinned MIPS
comparison/private-data tests passed with no skips, including an unrelated
function using nonzero data, read-only constants and MIPS small data. The managed host environment
passed exact package/import checks without a manually adjusted PATH.
