# VI manager source and private storage

The reviewed `0x34E0:0x37F0` unit contains the VI manager initializer
`func_800034E0` (376 bytes) and its thread entry `func_80003658` (408 bytes).
Original boundary evidence remains in `main_system_wrapper_boundaries.md`.
The checksum-validated US ROM text span has SHA-1
`6dcbd6357a68a1997e878debaca752a1b7daf2fb`.

The pinned `lib/ultralib/src/io/vimgr.c` provides independent source evidence:
its initializer owns a 4096-byte `STACK(viThreadStack, OS_VIM_STACKSIZE)`, a
queue, five messages, and two `OSIoMesg` event records. Its thread entry owns
a function-local static `u16 retrace`. `PRinternal/macros.h` defines the stack
as a `u64` array and `STACK_START` as its one-past byte endpoint;
`PR/os.h` gives `OS_VIM_STACKSIZE = 4096`. `PR/os_message.h` defines the
24-byte queue and `PR/os_pi.h` the 8-byte header and 24-byte I/O message.
Source-local types retain these exact fields and contracts. The external
thread object and the 0x80-byte gap preceding the stack are not reconstructed.

| Object | Original address | Size | Compiled BSS offset |
| --- | --- | --- | --- |
| VI stack | `0x80036DD0` | `0x1000` | `0x0` |
| Event queue | `0x80037DD0` | `0x18` | `0x1000` |
| Five message pointers | `0x80037DE8` | `0x14` | `0x1018` |
| Retrace event | `0x80037E00` | `0x18` | `0x1030` |
| Counter event | `0x80037E18` | `0x18` | `0x1048` |
| Retrace counter | `0x80037E30` | `0x2` | `0x1060` |

The initializer's raw queue/buffer/event references and its independently
materialized thread-stack endpoint, plus the thread's halfword counter
references, establish these addresses. Complete named C/include references
for the queue, buffer and events belong to this source; the counter's named
raw/C references belong only to the callback. Indirect alias absence is not
claimed. The allocated private queue and events can escape through their
normal SDK calls and the existing external device-manager fields.
The compiler supplies the observed four-byte alignment gap after the buffer
and rounds the section to 0x1070; no dummy padding was added.

The initial queue-as-stack-endpoint candidate collapsed two actual SDK
objects and scored 350. The real private stack/endpoint restores full-span
zero. The callback's external-counter candidate scored 1484; SDK private
storage and direct counter updates recover the original frame and instructions.
It scores 200 in isolation only because two unreachable alignment NOPs differ.
The actual matched 376-byte initializer prefix restores the original callback
placement (eight modulo sixteen), and its unchanged body passes full 408-byte
zero. No ASM, compiler settings or registered spans were changed.

Both functions still pass full-span zero with all SDK-owned queue/message
storage defined: initializer attempt `6e580a37cfa441298ef8d654befeacf2`,
callback attempt `d82c8fb8729449458b748d135d48d8e2`.

The first supported integration rolled back on a ROM mismatch: the private
C BSS was inserted at the start of main BSS, growing it from 0x16690 to
0x176A0 and shifting later SDK globals. `config/main/us-vi-bss.ld` consumes
only this object's BSS into a non-allocated writable zero-filled INFO PROGBITS section at
`0x80036DD0`. The existing canonical main BSS supplies its zero-initialized
RAM backing; the reference section does not add a second allocation or ROM
payload. GNU ld materializes the input NOBITS as zero-filled, writable
PROGBITS in the ELF only; the verifier checks every byte is zero. Original
main BSS must stay `0x8002D4B0:0x80043B40`.

`scripts/verify_main_vi_bss.py` requires the exact section address, type,
flags, alignment and size, checks the original main BSS bounds, and compares
all 784 linked VI code bytes (including every storage relocation) with the
checksum-validated US ROM. The full canonical ROM comparison remains a
separate integration/batch gate. Focused matches alone do not establish this
storage mapping or a completed source unit.

Final validation after the supported move to `src/done/main/init_34E0.c`:
initializer full376 zero/layout `ac4f1edd838441cd8443d9286ff2fa5b`;
callback full408 zero/layout `6c26b9c2d76d41b3bc975b16d2dbb4bd`.
Supported integration completed the C source unit. Clean two-function
`BATCH_COMPLETE`: 1844 tests in 37.052 seconds, 37 skipped; exact full US ROM,
strict VI storage checks, both existing linked tables, metadata, progress and
whitespace passed. Source/matching settings stayed fixed during validation.
