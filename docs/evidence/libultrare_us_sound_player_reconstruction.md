# Conker US sound-player reconstruction

This library-only pass reconstructs and integrates `audio/n_sndplayer.o`:
16 functions, 8,912 text bytes, 32 data bytes and 160 rodata bytes. The active
library search now accounts for 24 integrated reconstructed objects, 134
functions and 58,256 text bytes. Ordinary game-code matching remains outside
the goal scope. The sound player's static storage remains raw, as explained
below; integration does not claim its original source ownership.

## Source family and instruction evidence

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514`,
`src/lib/naudio/n_sndplayer.c`, supplies an independent source-family reference.
Conker's raw US instructions establish the earlier event behavior and its
additional asynchronous sound acquisition path. The reconstruction uses the
existing IDO `-O1 -g2` configuration, removing only non-runtime `.mdebug`.
The original Conker filename is not established by the source-family name.

| ROM start | Function | Bytes |
| --- | --- | ---: |
| `0x155A0` | `n_alSndpNew` | 728 |
| `0x15878` | `_n_sndpVoiceHandler` | 204 |
| `0x15944` | `_n_handleEvent` | 5,452 |
| `0x16E90` | `sndp_free_state` | 112 |
| `0x16F00` | `sndp_apply_detune_pitch` | 128 |
| `0x16F80` | `_removeEvents` | 384 |
| `0x17100` | `sndp_alloc_state` | 408 |
| `0x17298` | `sndp_free_state2` | 300 |
| `0x173C4` | `sndp_get_state` | 116 |
| `0x17438` | `sndp_play_sound` | 348 |
| `0x17594` | `sndp_stop_sound` | 112 |
| `0x17604` | `sndp_post_stopall_event_bulk` | 192 |
| `0x176C4` | `sndp_stop_all` | 40 |
| `0x176EC` | `sndp_stop_nodecays` | 40 |
| `0x17714` | `sndp_post_event` | 108 |
| `0x17780` | `sndp_set_volume_entry` | 228 |

All sixteen complete functions match in their original order. Twelve trailing
padding bytes complete text interval `0x155A0:0x17870`. The independently
relocated full text has exactly one occurrence in the main executable, at
`0x155A0`; it ends at the already integrated surround-control object.
The preceding bank-change wrapper ends at `0x155A0`. The raw comparison map
retains the original larger assembly block beginning at `0x15550`.

Two candidate compilations were required. The first already reproduced all
helper bodies and both entry routines; its event handler was eight bytes
short because acquisition and release used the global synthesizer directly.
The raw calls instead read `g_SndPlayer->drvr`. Correcting those two C
expressions reproduced the complete handler and all dependent call addresses.

Conker reserves a state before its sound is available. Event `0x4000` acquires
and patches the sound, derives keymap pitch/flags, then falls through to play.
Pending loads retry after 33,333 microseconds. The extended voice configuration
carries the cache entry that must later be released. Filter event `0x8000`
updates the state and active voice. Ordinary sound queue events use flag 2;
periodic API events use flag 3. Handle-state lookup guards the second pointer
read with interrupt disable/restore. State allocation has an independently
verified `0x58` stride, with sound at `+0x0C`, voice at `+0x10`, handle at
`+0x38`, bank at `+0x3C`, sound index at `+0x4C`, and state byte at `+0x54`.
These are source-local field views; shared headers are unchanged.

## Complete emitted sections and external storage

Compiler-object MD5: `114d7d3cb3ecc34d21b6e667908924ec`.

| Section | ROM interval | Bytes | Resolved SHA-1 |
| --- | --- | ---: | --- |
| `.text` | `0x155A0:0x17870` | 8,912 | `3488b7c23214b2173b00077d5dae78d05b00662c` |
| `.data` | `0x2BA20:0x2BA40` | 32 | `e1203fb419547371213d569140ca50a1f6853f76` |
| `.rodata` | `0x2C6B0:0x2C750` | 160 | `b0f32ce2999c346b1fec0ede4bb1588260f14609` |

Data contains three state-list pointers, the player pointer, a signed
halfword playing count and alignment. Rodata contains two retained diagnostic
strings, a sixteen-entry event jump table and alignment. Every allocated ROM
byte is compared, including padding. All 257 relocations are resolved:
70 text calls, 85 HI/LO pairs, sixteen rodata code pointers and one data pointer.

The reconstructed object emits no BSS or COMMON allocation. Its two external
storage references are explicitly bound to the raw region:

- `__conker_sound_player_storage`: `0x80042850`, proven by the initialized
  player pointer. Code accesses known fields through `+0x54`.
- `g_SndpVolumeTable`: pointer slot `0x800428B8`, proven by all table loads and
  the constructor's store.

The whole RAM interval `0x80042850:0x800428C0` stays raw. Neither its unused
bytes nor the original source-level ownership split are inferred from the
neighboring exact objects. The Perfect Dark source allocates its player
instance in `osc.c` and declares an additional word before its volume-table
pointer in `n_sndplayer.c`; that placement does not establish Conker's layout.
No fabricated padding allocation or BSS completion credit is introduced.
This is a complete comparison of the reconstruction's emitted sections, not
proof that Conker's original object had no BSS or the same extern declarations.

## Integration and verification

The canonical US map consumes the complete text, data and rodata sections.
The pinned original compiler object remains unchanged. The existing staging
helper rebases exactly sixteen jump-table addends by `-0x70000000`, accounting
for Conker's main runtime mapping. The voice-handler runtime alias derives
from the linked function. The former raw jump-table-label alias is removed.
Raw references and other library object checksums remain unchanged.

`./conker build --profile us` passes on the first integrated build. The full
67,108,864-byte `build/us/conker.us.z64` has SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, identical to the owned baseline ROM.
All 24 objects in the active independent comparison pass. All 157 repository
tests pass after updating the expected mapping counts and byte totals.
Generated progress is current and `git diff --check` is clean.

The canonical main map now links 141 unique library objects through 179
sections, including 92,368 exact library text bytes. Together with existing
overlay library mappings, total exact library text is 108,880 bytes. No
function inventory work items or source-unit records changed. This pass adds
no ordinary game-code implementation and changes no shared type headers.

Remaining library leads include the unresolved sound-player static storage,
formatting helpers, MP3 CPU routines in the game overlay and RSP microcode.
The library search remains active.
