# US debugger TLB capture

`func_16003650` occupies ROM `0x1A20D8..0x1A2178`, virtual
`0x16003650..0x160036F0`. The full registered span is 160 bytes: 152
instruction bytes followed by eight zero alignment bytes. It is the standalone
`debugger/tlb` unit between formatter text and loaded data, independently bounded
by the loader.

## Maintained source and contract

`src/debugger/tlb.s` is the maintained implementation. It reconstructs the
reviewed instruction stream with symbolic data references and comments explaining
the register contract, hardware operations, hazard spacing and alignment. It is
not regenerated from the ROM during a build. The explicit US Makefile rule
assembles this file into `build/us/asm/us/debugger/tlb.o`, the object already
selected by the canonical `asm, debugger/tlb` placement. Generated disassembly
remains independent reference material. `src/debugger/tlb.c` is only the existing
inventory/reference scaffold and is not the runtime or objdiff implementation.

The routine iterates the 32 CP0 TLB indices, executes `tlbr`, and stores EntryLo0,
EntryLo1, EntryHi and PageMask to four 32-word arrays at `0x160038AC`,
`0x1600392C`, `0x160039AC`, and `0x16003A2C`. It takes no arguments and has no
stack frame or return value. It clobbers `at`, `a0..a3`, `t0..t4` and CP0 Index,
EntryLo0, EntryLo1, EntryHi and PageMask. It preserves `ra` and returns normally.
It leaves CP0 holding the last entry, and does not restore prior CP0 state or
change interrupt enablement. The explicit hazard nops, trapping `addi`
instructions, pointer-update order and branch delay slots preserve the original
privileged execution behavior. This is not a portable C implementation.

The function's ELF size is 152 bytes. The following two zero instructions retain
the original eight-byte alignment tail without inflating native function credit.

## Matching and completion policy

Original assembly is maintained source, following the approach exemplified by
[Melee's matching MetroTRK assembly](https://github.com/doldecomp/melee/blob/master/configure.py).
`matched_code` measures matching source objects, including reviewed assembly;
it is not inherently a C-only metric. The existing function inventory retains
`original_asm`, so C-only statistics and selection still exclude this routine.
No C match or completed C source unit is recorded.

For every report, `objdiff_original_asm.py` requires all of these checks:

- Fresh independent original-span proof and unchanged registered ROM hash.
- Exact canonical ASM placement and full registered member coverage.
- A maintained `.s` source, freshly assembled into a separate candidate object.
- An exact object comparison with the actual runtime linker input.
- A separate link of the candidate at its original address, comparing all 160
  bytes, including padding, against the checked US ROM.
- A byte-identical allocated debugger runtime image.
- A native objdiff match of all 152 instruction bytes against the independent
  full-disassembly target. Matching counts are never edited after generation.

The report displays `debugger/tlb.s`, sets its source path to the maintained
assembly, and assigns the `Original assembly` category alongside `Debugger
overlay` and `Project code`. Both matching and linked completion require the
proofs above. The final source/object hash checks prevent stale inputs from
receiving credit. Missing source, changed instructions, changed padding, a
different runtime object, absent proofs or missing category labels are rejected.

This policy applies to this explicitly reviewed maintained unit. Generated
`GLOBAL_ASM` fallbacks do not acquire matching credit.
