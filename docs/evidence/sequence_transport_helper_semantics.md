# Sequence transport, markers and effect wrappers

Twelve existing matched wrappers in `src/main/init_8180.c` use source-local
aliases. Numeric symbols, original ABIs and operations remain unchanged.
No audio implementation or raw/deferred changes are made.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `800088F0` | `sequence_channels_set_enabled` | 152 |
| `80008988` | `sequence_channel_mask_set_enabled` | 196 |
| `80008A4C` | `sequence_channel_get_fade_volume` | 72 |
| `80008A94` | `sequence_channels_set_fx_bus` | 152 |
| `80008B2C` | `sequence_player_get_tempo` | 52 |
| `80008B60` | `sequence_player_set_fx_param` | 96 |
| `80008BC0` | `sequence_player_set_fx_mix` | 68 |
| `80008C04` | `sequence_collect_loop_markers` | 104 |
| `80008C6C` | `sequence_restore_marker` | 124 |
| `80008EE0` | `sequence_player_set_volume` | 68 |
| `80008F24` | `sequence_player_stop` | 52 |
| `80008F58` | `sequence_player_pause` | 56 |

## Channel mask, fade query and FX bus

`800088F0` iterates selected bits 0..15, calling the existing channel on/off
wrappers. Nonzero enabled selects on, which sets its mask bit immediately and
queues forced fade volume 255; off queues zero. It is not an atomic mask edit.
Original calls `8000B6C4/8000B740` use mask 0x8000 with opposite enable values.

`80008988` instead directly ORs or clears the player's u16 channel mask.
The entire mask operation repeats once per selected low-16 bit; no selected
bit means no write. It does not queue a volume change or stop existing voices.
The reviewed note-on consumer rejects new notes with a clear mask bit.
Original `8000CCE0/8000CD10` toggle selections around zero-volume transitions.
The repeated writes and existing signed mask arithmetic remain intact.

The fade getter returns channel+0x0D, the current fade-volume byte, not target
at +0x0E or ordinary MIDI volume. Original `8000BC44/8000BC54` query channels
zero and six. The FX-bus wrapper posts controller 0x5C for selected channels,
converting its s32 value to u8 at the callee boundary. Control-table slot 92
selects `__n_cspFXBus`, which assigns the bus only below `maxAuxBusses`.
Original caller `8000E738` forwards a mask and value; later validation does not
undo the preceding byte conversion or provide a caller-visible error.

## Tempo, markers and volume

The tempo getter delegates to reviewed `alCSPGetTempo`: zero for a null target
sequence, otherwise `uspt / target->qnpt`. This is not a BPM conversion. No
direct caller was found in the bounded scan; the callee supplies positive role
evidence. The player pointer itself is not validated by the wrapper.

Marker collection scans a temporary decoder over the loaded sequence, saving
pre-event state for loop-start IDs in the requested range. Count is a number
of markers, not ticks; the existing declaration converts first to u32. Each
player has eight saved slots, but count is unchecked. Missing markers get
`lastTicks=0` while other fields may remain stale; the original zero-tick
sentinel and no-success-result interface are preserved. A captured zero-tick
snapshot is also indistinguishable from that unused sentinel. Original `8000D4F4`
passes a metadata-derived count and first ID 100.

Restoration copies selected marker state directly into the decoder: valid
tracks, tick state and sixteen tracks' cursor/backup/status/delta fields.
It is not a queued play/seek request and does not validate marker index or
collection success. Original `8000D514/8000E6CC` subtract one from a one-based
selection. The sequence-volume wrapper narrows its existing s32 input to s16
and queues the volume event; there is no saturation or completion result.
Original caller `8000CD28` supplies its computed volume.

## Stop versus pause: original Conker dispatch

`80008F24` posts numeric event 18 through `80018C60`. The Conker dispatcher
accepts it from playing or paused state, flushes sequence/note-off/MIDI events,
releases voices, updates fade/mask state and schedules final cleanup. This is
an asynchronous stopping request, not a wait for completed cleanup.

`80008F58` posts numeric event 16. Although its reviewed callee retains the
SDK-style name `n_alCSPStop`, Conker handles 16 as pause: playing becomes state
3 and the flushed sequence-reference timing is saved. Original `8000D1F8`
invokes it, followed later by the resume path through `800084D8` at `8000D228`.
Pausing sequence advancement does not immediately silence/free every existing
voice. The final alignment word remains in the wrapper's registered span.

## Extended FX events

The parameter wrapper posts event 0x1A with bus, parameter, section and s32
value. The consumer selects a driver FX reference for parameters below eight,
otherwise an output low-pass reference. Its value therefore has no single
universal unit, and selecting a player queue does not make a driver-bus effect
exclusive to that player. The mix wrapper posts event 0x19 containing its two
unchanged floats; the consumer stores player mix scalars and refreshes active
voices outside their release phase. Neither wrapper validates ranges or waits.

## Evidence and shared limits

Original `8180.s`, `B1B0.s`, the `13320.s` dispatcher and its table in
`reference/us/asm/data/2BE20.data.s`, reviewed `n_csq.c`, `n_csplayer.c`, `n_cspctrl.c`,
`n_cspevent12.c`, `n_cspstop.c`, `n_cspsetvol.c`, `n_cspsetfxmix.c`,
`n_cspsetfxparam.c` and the mapped tempo getter establish these roles.
See [sequence control evidence](sequence_control_helper_semantics.md) for the
three-player/sixteen-channel configuration and event-queue rejection rules.
Player/channel/marker indices remain unchecked. Queued operations can be
silently rejected; these void wrappers cannot report failure or guarantee
immediate application. No-op `800085A4`, opaque packed setter `800085B8`, raw
members and the separate held ring reader remain unchanged.

All 1,192 registered bytes require full-span CURRENT (0), existing layout,
clean batch, tests, progress, whitespace, RSP and exact main/game images.
No new C match, original-symbol identity or source-unit completion is claimed.
