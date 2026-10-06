# Main AI, PI, VI/timer and thread helpers

Main system roles; runtime `D_100...` entry aliases and private
initialized-data/BSS ownership remain unchanged.

| Symbol | C name | Span |
| --- | --- | --- |
| `80002DB0` | `ai_submit_buffer` | `0xA0` |
| `80002E50` | `pi_dma_manager_thread_entry` | `0x250` |
| `800030A0` | `pi_dma_manager_init` | `0x180` |
| `800034E0` | `vi_timer_manager_init` | `0x178` |
| `80003658` | `vi_timer_manager_thread_entry` | `0x198` |
| `800037F0` | `thread_init` | `0xD0` |

## AI submission

`80002DB0` writes the translated buffer address to AI_DRAM_ADDR and the supplied
byte length to AI_LEN, returning zero. If the previous-call boundary flag is
set, the buffer is first adjusted by -0x2000. It computes and stores the next
flag from `((originalAddress + length) & 0x3FFF) == 0x2000` before the FIFO check;
this flag update also occurs on rejection. The check at `80023390` tests
AI_STATUS_FIFO_FULL, not general DMA activity; a full FIFO returns -1 without
submitting. Original call `800095FC` supplies the prior task's adjusted buffer
and sample count multiplied by four. No new alignment, size or address checks
are introduced. The [reviewed private-data proof](../main_ai_private_data.md),
including the original 16 zero bytes, remains unchanged.

## PI command processing

The PI thread receives commands indefinitely. Types 0xB/0xC invoke ordinary
read/write DMA; 0xF/0x10 invoke handle-based read/write DMA. Type 0xA attempts
an immediate nonblocking reply. On a zero DMA result, the thread waits for
completion, attempts the return-queue notification, and releases access.
The custom read-side stop/flag handling and existing nonzero-result behavior
are preserved; the name does not promise successful delivery or error recovery.
The original seven-entry dispatch table at ROM `2C080:2C09C` independently
confirms these paths.

The PI initializer returns immediately if its manager is active. Otherwise it
creates command/event queues, registers PI event 8, installs ordinary/extended
DMA callbacks, initializes the manager thread and starts it. It temporarily
raises the calling thread's priority when needed and restores priority and the
interrupt mask afterward. Original call `80004498` supplies priority 150 and
command capacity 200. Existing manager, queue and stack addresses are retained.

## VI and timer events

The VI/timer initializer also has an active-manager guard. It initializes timer
state, a five-message queue, VI event 7 and counter event 3, initializes VI
state and starts its thread. Original bootstrap call `80001284` supplies
priority 254. Its private storage and [VI layout proof](../main_init_vi_layout.md)
are unchanged.

The thread handles retrace message type 0xD by swapping VI context, counting
down and attempting the configured retrace notification, incrementing the
retrace counter, and accumulating CP0 Count deltas. Type 0xE invokes timer
interrupt handling. The existing dead first-count branch, counter behavior,
nonblocking notifications and all storage definitions are retained. The name
includes timers because this thread processes both event families.

## Thread context initialization

`800037F0` initializes an existing thread's ID, priority, saved entry PC,
argument, stack minus 16, return trampoline, status/RCP/FPCSR fields, stopped
state and list links. It neither allocates nor starts the thread. Original
bootstrap instructions `800010AC..800010E4` supply six arguments, followed by
a separate thread-start call to `80022A60`. The existing conditional
`queue_message` label in `init_1050.c` refers to this same US function despite
its misleading name; that US/EU alias block remains outside this batch.

## Evidence and acceptance

All 2,128 registered reference bytes, including terminal padding, agree with
the checksum-validated original US ROM. The pinned libultra headers establish
AI register/status constants, PI message types/directions, VI/PI/counter event
numbers, thread fields and OS_STATE_STOPPED. Existing boundary and storage
manifests are untouched.
