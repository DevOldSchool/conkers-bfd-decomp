# Sequence-player state and channel controls

Ten existing matched wrappers in `src/main/init_8180.c` use source-local
aliases. Numeric linkage, signatures, operation order and complete registered
spans remain unchanged. No audio implementation or raw/deferred body changes
are introduced. These are descriptive wrapper names, not recovered symbols.

| Symbol | C name | Bytes |
| --- | --- | ---: |
| `8000853C` | `sequence_player_get_state` | 52 |
| `80008570` | `sequence_player_set_notify_queue` | 52 |
| `800085F8` | `sequence_channel_off` | 52 |
| `8000862C` | `sequence_channel_on` | 52 |
| `80008660` | `sequence_channel_fade` | 156 |
| `800086FC` | `sequence_channel_set_surround` | 72 |
| `80008744` | `sequence_channel_set_pan` | 76 |
| `80008790` | `sequence_channels_fade` | 148 |
| `80008824` | `sequence_channel_set_fade_volume` | 72 |
| `8000886C` | `sequence_channels_set_fade_volume` | 132 |

## State and notification queue

The state wrapper returns the complete result of reviewed `alCSPGetState`
(`80017A80`), not a Boolean playing test. Original caller `8000DF18` compares
it with zero before clearing controller records.

The queue wrapper calls `80017AF0`, storing player+0x84. Original game
initializer `15000000` creates three message queues and passes each through
runtime alias `10008570` at `15000044`. Reviewed `__n_cspNotify` (`80019CFC`)
loads that field and calls osSendMesg. This establishes queue semantics even
though the library setter retains a neutral field84 label. The wrapper stores
the supplied pointer; it does not create or drain the queue. Notifications use
nonblocking sends and ignore their return values.

## Channel events and masks

The off/on wrappers call reviewed `n_alCSPChanOff/On` at `80017BB8/80017C00`.
Both post controller 0xFC with values 0/255; on also sets its channel-mask bit
immediately. Original `800088F0` selects these wrappers by mask, and
`8000C608` is a direct off caller. The controls do not report enqueue success.

Fade calls `n_alCSPChanFade` (`80017C68`), posting 0xFD rate followed by 0xFF
target fade volume. Nonpositive duration becomes zero. Positive duration uses
the existing signed `(duration * 10) / 60`, changes zero to one and clamps
values at least 128 to 127. Ordinary positive values therefore become 1..127,
but large inputs can overflow before clamping. No duration-unit or overflow-
safety guarantee is added. A zero rate does not prove immediate change: the
downstream fade-start handler replaces it with 0x88. Original calls include
`8000D578` with duration one and `8000C798` fading selected channels to zero
with duration 90.

Surround and pan call `n_alCSPChanSurround` (`80017CE0`) and
`n_alCSPSetChlPan` (`80017D80`). Original `8000C64C/8000C660` split a packed
value into a shifted surround byte and low-seven-bit pan between those
controls. The surround input is `(packed >> 7) & 0xFF`, not just one bit.
The wrappers forward bytes without semantic range checks.

Fade-volume setting calls `n_alCSPChanFadeForce` (`80017D30`). Its 0xFC control
handler sets current and target fade-volume fields, adjusts the mask and
refreshes active voices. This multiplier is distinct from ordinary MIDI
channel volume. Original callers include `8000C634/8000C758`.

The two plural wrappers iterate channel bits 0..15 only, calling their singular
counterparts. Zero or upper-bits-only masks make no calls. Reviewed event-queue
capacity/reserved-item rules can silently reject posts; a multi-event fade
can be only partially enqueued. No atomicity, immediate application or audible
result is implied by the names.

## ABI and evidence limits

The player selector stays u8 and indexes `D_8003C900` without validation.
Original initialization establishes three players with sixteen channels each;
truncation to u8 does not establish validity. Direct wrappers likewise do not
validate channels. Off/on retain s32 channels; other wrappers retain their
existing u8 forms. No pointer, range or state checks are added.

Proof uses original `reference/us/asm/8180.s` and `B1B0.s`, the game queue
initializer, and reviewed library `n_cspchan.c`, `n_cspsetpan.c`, `n_cspctrl.c`,
`n_csplayer.c`, `n_seqplayer.c`, `n_cspsendmidi.c` and `n_event.c`. Existing
[boundary](main_sequence_api_mp3_adapter_boundaries.md) and
[channel-control](libultrare_us_channel_controls_reconstruction.md) evidence
separate wrappers from SDK implementations. The actual SDK pin is
`87af1e4d8ed666f2ad407dc11c6e47736094f2f8`; current US state-query mapping uses
`libultra_2_0G_d`, irrespective of older historical archive descriptions.

All 864 registered bytes require full-span CURRENT (0), existing layout,
clean batch, tests, progress, whitespace, RSP and exact main/game images.
The empty `800085A4`, packed-field setter `800085B8`, deferred `800084D8` and
`80008CE8`, and the separate held ring reader retain their original status and
numeric bodies. No new C match or source-unit completion is claimed.
