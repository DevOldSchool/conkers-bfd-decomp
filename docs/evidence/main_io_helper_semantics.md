# RSP, graphics scheduler and motor-pak helpers

Nine existing matched C helpers use source-local aliases. Numeric symbols,
ABIs, partial types, raw siblings, storage, operations and padding remain
unchanged. These are descriptive roles, not recovered historical symbols or
claims of byte identity to a stock SDK implementation.

| Symbol | C name | Source | Bytes |
| --- | --- | --- | ---: |
| `80003330` | `sp_task_load` | `init_3220.c` | 364 |
| `8000349C` | `sp_task_start_go` | `init_3220.c` | 68 |
| `80004DB0` | `scheduler_update_gfx_task` | `init_49E0.c` | 336 |
| `80004F00` | `scheduler_start_gfx_task` | `init_49E0.c` | 224 |
| `80004FE0` | `scheduler_try_complete_gfx_task` | `init_49E0.c` | 64 |
| `80005020` | `scheduler_complete_gfx_task` | `init_49E0.c` | 128 |
| `80005570` | `motor_pak_stop` | `init_5570.c` | 304 |
| `800057E0` | `motor_pak_init` | `init_5570.c` | 360 |
| `80005948` | `motor_pak_pack_write_command` | `init_5570.c` | 360 |

## SP task loading and execution

The loader obtains the physical-address task copy through raw `80003220`.
For yielded tasks it substitutes yield data, optionally restores loadable
microcode and clears the original task's yielded flag. It writes back the
64-byte descriptor, writes SP status 0x2B00, sets PC to IMEM 0x04001000,
DMA-loads the descriptor to DMEM 0x04000FC0, waits for that transfer, then
starts boot-code DMA to IMEM. It neither waits for this final DMA nor starts
execution. Status 0x2B00 clears yield, yielded and task-done, and enables
interrupt-on-break.

The start helper waits for SP DMA/IO availability and writes status 0x125:
enable interrupt-on-break, clear single-step, broke and halt. Its existing
`u8 *` argument is unused and retained. Neither helper promises bounded
waiting or task completion. Pinned `src/io/sptask.c` corroborates these roles;
raw `80003220` and its storage/matching issues remain unchanged.

## Graphics scheduler

The original producer `1501C880` writes task type 1 at record +0x18
(`1501CA54`), flags 0x23 with optional 0x40, a framebuffer at +0x10, and submits
to queue `8003B1E8` at `1501CBEC..1501CBFC`. Pinned `PR/mbi.h` identifies type 1
as graphics; `PR/sched.h` identifies swap flag 0x40. The project record's
offsets differ from stock `OSScTask`; no structure replacement is implied.
The separate type-2 producer uses queue `8003B200` (`80009798`).

Original initialization at `80005140..80005178` maps VI retrace to message 0,
DP full-sync event 9 to message 1, and SP task-done event 4 to message 2 on
queue `8003B218`. The ROM dispatch table at `2C0A0..2C0BB` independently confirms
the handlers in raw `800049E0`.

- Update: on idle state 0, nonblockingly dequeues a graphics task, checks its
  framebuffer against current/next VI buffers and checks retrace pacing;
  starts it or keeps state 2. State 2 retries pacing without repeating the
  framebuffer comparisons. State 6 retries completion
- Start: unless the stop flag is set, loads/starts the selected task, records
  SP-active/DP-incomplete state, saves/clamps the previous retrace interval to
  `800BE9E4`, resets elapsed retraces, enters state 1 and sends a nonblocking
  notification whose failure is ignored
- Try complete: if elapsed retraces are zero, sets state 6; otherwise calls
  final completion. It returns void and itself tests only retrace count.
  Normal SP/DP event callers establish hardware completion first: SP-done
  clears SP-active and checks DP-done; DP-done sets DP-done and checks SP-active
- Complete: resets state to idle, and with swap flag 0x40 and no stop flag,
  forwards the framebuffer through pre-swap callback dispatch `8515FDA0`,
  then requests a VI buffer swap. It sends the task's completion message in
  blocking mode even when swapping is disabled. A swap request is not proof
  the frame has already been displayed

The original graphics producer and pre-swap dispatcher were checked against
the decoded US game image. No narrower scene or callback identity is needed.

## Motor-pak protocol

Initialization assigns queue/channel, clears status, sets bank 0x80, writes
32 bytes of 0x80 to block 0x400, retries write error 2 once, then reads that
block and requires final byte 0x80. Identity failure returns 11. On success
it constructs two block-0x600 packets: ones in `D_8003BD30[channel]` for start,
and zeros in `D_8003BC30[channel]` for stop. The controller header identifies
0x600 as the rumble register's byte address 0xC000 divided by 32.

The stop helper sends the zero packet, receives a reply, extracts
`(rxSize & 0xC0) >> 4`, and returns 4 on an otherwise successful nonzero data
CRC. It has no initialized guard. Main calls init then stop at
`800053C4/800053CC`; original game `1501C1B0` uses the same channel-indexed
records and calls stop at `1501C2B0`, `1501C328`, `1501C3E0` and `1501C4CC`.
The last call is the active-to-inactive transition. Opposite transitions use
the untouched raw `100056A0`.

The packet builder clears 15 words, sets word 15 to 1, then packs dummy 0xFF,
lengths 0x23/1, write-pak command 3, encoded block address
`(address << 5) | address_crc(address)`, and 32 payload bytes. It prefixes
channel skip bytes, copies the 0x28-byte packet and appends 0xFE. The paired
initializer calls at `80005904/80005928` prove its role; it does not submit
DMA or exclusively start the motor. Original signatures and unchecked channel
and pointer assumptions are retained.

Pinned pre-J `src/io/motor.c` corroborates the family, but this initializer
omits the stock 0xFE rejection probe, error remapping and initialized-guard
update. Runtime packet writes establish buffer roles, not private-data or
BSS ownership. The raw sibling `800056A0` and its boundary mismatch stay
numeric and unchanged; the builder's three terminal NOPs remain in its span.

## Acceptance

The actual SDK gitlink and checkout are
`87af1e4d8ed666f2ad407dc11c6e47736094f2f8`. Existing boundary notes cover
[system wrappers](main_system_wrapper_boundaries.md) and
[allocator/transfer/controller units](main_allocator_transfer_controller_boundaries.md).
All 2,208 registered target bytes retain full-span CURRENT (0), with existing
layout, clean batch, tests, progress, whitespace, RSP and exact complete images
required. No new C match, data owner or completed source unit is claimed.
