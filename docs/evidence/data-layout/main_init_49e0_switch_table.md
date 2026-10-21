# Scheduler dispatch table integration

`func_800049E0` independently matches the complete 976-byte US span, with
its original 0x68 frame. The reviewed unit is ROM `0x49E0:0x50A0`;
[boundary evidence](../boundaries/main/main_allocator_transfer_controller_boundaries.md)
records all five members. The completed source is `src/done/main/init_49E0.c`.

The raw dispatch at `0x80004A84:0x80004AA8` checks a selector below seven,
multiplies it by four and reads `jtbl_8002C0A0`. The original table at ROM
`0x2C0A0:0x2C0C0` consists of these runtime pointers and four zero padding bytes:

| Selector | Runtime target | Meaning |
| --- | --- | --- |
| 0 | 0x10004AAC | client notification and timer scheduling |
| 1 | 0x10004CE0 | scheduler ready |
| 2 | 0x10004BEC | task completion |
| 3 | 0x10004D04 | timer completion |
| 4 | 0x10004A70 | next message |
| 5 | 0x10004A70 | next message |
| 6 | 0x10004D4C | conditional `func_80024BC0` call |

Every target is inside the independently matched function. The preceding
queue table ends at `0x2C0A0`; this mapping owns only the compiler's complete
32-byte pool. Its SHA-256 is
`b13c787c039489ec848d157413e9991918d3a4d0f0e35d6b1fefd3d2a32c7e6a`.
The 67,108,864-byte US ROM has SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The compiler emits exactly seven `R_MIPS_32` relocations from `.rodata` to
`.text`, with addends `CC, 300, 20C, 324, 90, 90, 36C`. Adding runtime base
`0x100049E0` reproduces every original word. The existing object preparer
applies the established `-0x70000000` code-pointer alias to fresh compiler
output; it changes neither text nor relocation records. A phony refresh
prevents a focused compile from bypassing preparation or being rebased twice.

The required integration repair consumes this object's pool at `0x8002C0A0`
as non-allocated read-only INFO, retaining the original allocated ROM bytes.
The owner is recorded in `config/data/us.json`. The linker asserts a 32-byte
extent and verifies every linked byte against the ROM,
including padding. The first integration attempt lacked this mapping and
shifted main BSS by 32 bytes; its transaction rolled back. This extends the
existing queue/selector table path solely to integrate already-matched C.
It does not modify the C match, assembly, shared headers, compiler flags or
asset reconstruction. Full ROM integration and a clean batch are still required.
