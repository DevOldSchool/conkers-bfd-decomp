# Main startup, transfer wait and video helpers

Startup, transfer-wait and video roles; conditional regional aliases remain
unchanged.

| Symbol | C name | Source | Bytes |
| --- | --- | --- | ---: |
| `80001050` | `boot_init` | `init_1050.c` | 168 |
| `800010F8` | `idle_thread_entry` | `init_1050.c` | 156 |
| `800014A0` | `main_thread_stop` | `init_1420.c` | 36 |
| `80004674` | `pi_dma_wait_pending` | `init_4470.c` | 112 |
| `800039C0` | `video_init` | `init_39C0.c` | 268 |

## Boot and thread roles

Original code at `80005AF4..80005B00` transfers to runtime alias `10001050`.
The boot routine clears BSS, invalidates a TLB-entry range, initializes the OS,
sets CPU/FPU state, creates thread ID 1 at priority 5 with entry `100010F8`,
then starts it. Existing conditional labels are not authoritative: `queue_start`
resolves to bzero, `reset_task` to osInitialize, `queue_message` to the reviewed
thread initializer, and `enable_interrupts` to the FPCSR setter. Those historic
aliases remain unchanged; numeric callee evidence establishes the roles.

The idle entry initializes transfer queues, creates thread ID 3 at
`D_80031AE0` with entry `10001194` and priority 10, and starts it only when
`D_8002AC5C == 0 && D_80000310 == 0x17D9`. These gates are preserved without
assigning a purpose. It lowers its own thread at `D_800318B0` to priority zero
and loops forever. Raw `80022BB0` and pinned SDK evidence identify
osSetThreadPri; zero is the idle priority. The unreachable epilogue remains
part of the complete registered span.

The stop wrapper passes that same thread ID 3 object to `80022E00`, the
verified osStopThread implementation. Its entry initializes runtime state
and calls the game entry through source alias `85007830` from `80001404`.
This stops the specific thread, not every system thread, and does not destroy it. No direct caller was found in the
bounded textual search; the target object and callee support its name.

## Recorded asynchronous PI transfers

`80004674` receives messages in blocking mode from `D_800388C8`, once per
recorded count `D_8003A571`, then clears the count. Raw producer `80004514`
selects that completion queue and increments the count for its asynchronous
device-to-RDRAM PI-DMA path. Original game caller `15018CBC` invokes the wait
after completing display-list commands.

The byte-sized counter is repeatedly reloaded in the original loop. Receive
results are ignored, no timeout is added, and the producer counts a request
without checking its submission result. Preserve those behaviors: this is
not a global PI-idle test or a guarantee of recovery/successful completion.

## Video initialization

The video helper sets 292-by-216 dimensions and corresponding scale factors,
allocates a 292*216*2-byte buffer, clears the existing framebuffers through
raw `80003ACC`, forwards dimensions to `85015FBC`, selects a VI mode and
requests a swap to the opposite indexed framebuffer. Original caller is
`80005138`; SDK mappings identify `800247C0` as osViSetMode and `80024830`
as osViSwapBuffer. Mode selection retains `D_80000300 == 2`, and the index
retains XOR one. No role is assigned to the extra allocated buffer beyond
these observed operations, and a swap request does not establish display.

## Evidence and acceptance

Original references `1050.s`, `1420.s`, `4470.s`, `39C0.s` and `5AB0.s`, SDK
assembly/profile mappings and pinned sources support all five roles. The
actual SDK gitlink/checkout is `87af1e4d8ed666f2ad407dc11c6e47736094f2f8`;
current US mappings select the reviewed 2.0G objects for these SDK calls.
Existing boundary evidence covers
[bootstrap](../../boundaries/main/main_bootstrap_source_units.md), [system
wrappers](../../boundaries/main/main_system_wrapper_boundaries.md), and
[allocator/transfer/controller
units](../../boundaries/main/main_allocator_transfer_controller_boundaries.md). Registered spans
total 740 bytes. Raw implementations, endpoint initializer `80003930` and its
unresolved wider role remain untouched; no new C match or source-unit
completion is claimed.
