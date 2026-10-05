# Audio thread and cache callback helpers

Six existing matched helpers in `src/main/init_8F90.c` use source-local
aliases. Numeric symbols, types, operations and complete spans remain
unchanged. No audio implementation or raw/deferred worker changes are made.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `800093CC` | `audio_thread_stop` | 52 |
| `80009980` | `audio_dma_callback_new` | 60 |
| `80009B2C` | `audio_bank_cache_release` | 32 |
| `80009B4C` | `audio_bank_cache_release_and_queue_reclaim` | 68 |
| `80009B90` | `audio_bank_cache_retain` | 84 |
| `80009FFC` | `audio_bank_fetch_callback_new` | 64 |

## Thread and callback registration

Original initialization at `80009360..800093A4` creates thread ID 4, object
`D_8003E3A0`, entry `10009400`, sets `D_8002AE40`, then starts it. The stop helper
checks that byte and passes the same object to verified osStopThread. Original
shutdown caller `80005310` invokes it alongside other thread stops. It does
not destroy the thread, close the synthesizer, clear initialization or wait
for audio cleanup.

Original `80008FC8..8000900C` installs config offsets +0x10/+0x14/+0x18/+0x1C/
+0x20 as `9980/9FFC/9B2C/9B90/9B4C`. `80018ED4..80018F34` copies these to
synthesizer +0x24/+0x28/+0x2C/+0x30/+0x34, establishing the callback roles.

The DMA factory initializes the shared manager once, always clears the writable
state slot supplied through its existing void* ABI, and returns runtime
callback `100097CC`. Original voice construction at `8001D744..8001D758`
passes voice+0x34 as that slot and stores the callback at voice+0x30.

The fetch factory initializes the shared bank-cache manager once and returns
`10009CBC`. Original `8001BD50..8001BDB8` invokes the factory, then the returned
worker with an owner slot and mode one for instruments or zero for individual
sounds. “New” follows callback-factory convention: neither helper allocates a
fresh independent manager or performs the returned worker's transfer. Existing
ALDMAproc and ConkerBankFetch typedefs remain unchanged.

## Tagged handles and reference operations

The reference helpers receive a handle value, not its slot address or loaded
payload. Odd low-bit-tagged handles do nothing; even values are treated as
AudioBufferState pointers without null/validity checks. The reference count
at +0x14 remains signed s8 with the original byte-store narrowing behavior.
No underflow, overflow or lifetime protection is added.

Release decrements that count only. It does not test zero, unlink or free.
The original voice-free path uses this callback through synth+0x2C at
`8001C8E8..8001C8F4`.

Release-and-queue decrements, reloads the stored signed byte, and invokes raw
`80009BE4` only if it is exactly zero. That worker restores the owner slot's
saved tagged value, unlinks the active record and links it onto manager+0x10.
It does not free the buffer. Raw `8000A03C` processes the reclamation list
later; instrument wave flags can delay reclamation, and allocator release
occurs at `8000A278`. The alias does not imply unconditional queueing or
immediate deallocation. Original `8001B85C..8001B86C` dispatches this callback
through synth+0x34 with an instrument handle.

Retain preserves its special first-use branches:
- State other than one: increment count
- State one and field16 equal to one: increment count, then set state two
- State one and other field16: set state two without incrementing

Original completion at `8000A1B4..8000A1C4` sets state one and increments the
count; the fetch/consumer paths distinguish instrument and individual-sound
modes. Do not simplify these branches to unconditional reference counting.
The reconstructed library helper `__conker_bank_release` at `8001BE1C` actually
dispatches through synth+0x30 to retain; its historic name is not used to invert
this interpretation, and that helper remains untouched.

## Evidence and acceptance

Original `8F90.s`, callback installation/consumers and reviewed library code
support the roles. Existing [driver boundary evidence](main_audio_driver_sequence_boundaries.md)
establishes the complete driver family, including these raw workers, and
distinguishes external SDK callees. All 360
registered bytes require full-span CURRENT (0), existing layout, clean batch,
tests, progress, whitespace, RSP and exact main/game images. No new C matches,
source-unit completion or guarantees of audible behavior are claimed.
