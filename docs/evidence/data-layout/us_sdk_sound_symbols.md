# US sound strings and declared SDK globals

Accepted gain: **240 bytes**, verified by the full suite, rebuilt-asset ROM,
native report and preservation audit. The report now matches the sound
player (192), timer services (16) and thread globals (32). Runtime archives,
source implementations, allocation boundaries and denominators are unchanged.

## Sound-player strings and table

`lib/libultrare/src/libultrare/audio/n_sndplayer.c` passes two literal formats
to `osSyncPrintf`. The actual archive uses LUI/ADDIU to place their addresses in
`a0`, followed by the named call, with the argument retained through its delay
slot. The first address setup is at object offsets `0xF3C/0xF40`, the call at
`0xF4C`; the second setup is `0xF58/0xF5C`, with the call at `0xF60`.

The candidate-only recognizer accepts this narrow call contract. It permits
only bounded integer loads and arithmetic that preserve `a0`, rejects stores
and control transfers, requires the exact `osSyncPrintf` relocation with no
call addend, and checks the delay slot. A bounded ASCII scan includes the
first NUL terminator. It reads no reference names, ROM bytes or next-symbol
extent. The two objects are 42 and 44 bytes at `8002C6B0` and `8002C6DC`;
the two intervening alignment bytes remain present and anonymous. Existing
relocation/overlap checks also reject pointers into the middle of an object.

The sound player's switch at object load offset `0x5E0` has an unsigned bound
of 16. Its 64-byte table starts at `8002C708`; eight trailing alignment bytes
remain in the full 160-byte read-only section. The established
[main-runtime pointer comparison](us_sdk_pointer_symbols.md) now includes this
fifth explicit owner. Every effective table pointer and all other object bytes
remain invariant, independently of native comparison output. Whole-object links
and original-ROM code/data checks cover all code and data, including BSS placement.

## Declared globals and BSS pointers

The sound source declares three state-list pointers, its player pointer and a
signed 16-bit playing count. Their original object symbols give extents 4, 4,
4, 4 and 2 bytes at `8002BA20..8002BA32`. Fourteen alignment bytes remain in the
32-byte section. The player pointer's original word is `80042850`, agreeing
with the existing Makefile alias `__conker_sound_player_storage` and the
source declaration; the referenced player structure occupies 88 bytes.

`lib/ultralib/src/os/timerintr.c` declares `__osTimerList = &__osBaseTimer`.
The actual four-byte pointer at `8002BD70` contains `80042990`, the linked
address of its 32-byte `OSTimer`. Twelve alignment bytes remain in that section.

Both destinations lie outside the initialized-data reference image. The narrow
`config/relocs/main-data-us.txt` records those two source-proven R_MIPS_32 fields.
The independent reference linker still must reproduce the original stored
words; it does not substitute candidate pointer bytes. This metadata file is
applied only to main data reference generation, never GAME or debugger contexts.

`lib/ultralib/src/os/thread.c` declares an eight-byte `__osThreadTail`, followed
by four four-byte queue/thread pointers at `8002BDF8..8002BE08`. Two point to the
tail and two are NULL; the tail contains NULL and priority -1. Canonical names
and exact declared sizes preserve the original relocations and eight trailing
alignment bytes. Neither the timer nor thread candidate needs any annotation.

## Validation

The three complete code/data spans and actual BSS placements independently
match the original ROM through separate links of raw and comparison objects.
All 196 single-byte mutations across declared payloads lose a perfect native
match. The full section/ROM checks also retain all 44 alignment bytes.

The focused report suite passes 173 tests with one expected skip (9.708 seconds).
Regression fixtures cover exact NUL extents, retained arguments, named call
identity, delay-slot clobbers, stores, branch/call addends, non-ASCII data and
missing terminators. The two pointer declarations have explicit scope and
original-word checks.

The full Docker suite passes 2,958 tests with eight expected skips (176.161
seconds). The rebuilt 67,108,864-byte US ROM is byte-identical (49 seconds
including setup). The native report completes with zero compile errors
(353.9 seconds preparation, 26.3 seconds report and validation). Only the
three intended unit measures change; all 26,809 prior editable source hashes,
three SDK archive objects, code metrics and denominators are preserved.
Progress and whitespace checks pass.

Data matching is **63,125,280 / 65,120,512 bytes (96.93610%)**, leaving
1,995,232 bytes unmatched. Complete data remains 63,079,392 bytes. Tested base
commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, with local changes.
