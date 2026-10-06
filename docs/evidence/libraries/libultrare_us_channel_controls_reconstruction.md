# Conker US compact-sequence channel controls

This library-only pass reconstructs the complete `audio/n_cspctrl.o` object:
20 functions and 3,984 text bytes at ROM `0x19B50:0x1AAE0`. The active library
search now totals 21 integrated objects, 109 functions and 40,512 text bytes.
Earlier evidence files retain their historical checkpoint counts.

## Ownership and exact comparison

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514`,
`src/lib/naudio/n_csplayer.c`, supplies an independent source-family reference
for channel controls and filter updates. Conker separates these handlers into
a contiguous object between `cents2ratio` and the previously reconstructed
`n_seqplayer` helpers. The filename and descriptive handler names express
reviewed behavior, not recovered original Conker names. This is a Conker/Rare
reconstruction; it is not attributed to a stock libultra archive.

The complete compiler object uses the existing IDO `-O1 -g2` settings, with
only non-runtime `.mdebug` metadata removed. Its pinned MD5 is
`d688fe9c84900c33df9815cf61f7700a`. Resolving all 26 text relocations produces
3,984 bytes with SHA-1 `88839a33383616c8fef4dc1dfc5ac1ec1e80c542`, identical
to the entire reviewed ROM range. The whole text template occurs only once
in the main executable, at `0x19B50`. Comparison includes function order,
internal calls and the final eight padding bytes.

There are no `.data`, `.rodata`, `.sdata`, literal, BSS or COMMON allocations.
ELF register metadata is not a ROM data section. The canonical map consumes
the complete text member; `config/reference/us.yaml` remains raw assembly.
No target assembly or instruction bytes were edited.

| ROM start | Handler | Function bytes |
| --- | --- | ---: |
| `0x19B50` | `__n_cspVolume` | 216 |
| `0x19C28` | `__n_cspPan` | 168 |
| `0x19CD0` | `__n_cspPriority` | 44 |
| `0x19CFC` | `__n_cspNotify` | 112 |
| `0x19D6C` | `__n_cspInstrumentMajor` | 44 |
| `0x19D98` | `__n_cspRefreshFilter` | 320 |
| `0x19ED8` | `__n_cspFilterEnable` | 96 |
| `0x19F38` | `__n_cspFilterPitch` | 96 |
| `0x19F98` | `__n_cspFilter11` | 152 |
| `0x1A030` | `__n_cspSustain` | 500 |
| `0x1A224` | `__n_cspSurround` | 212 |
| `0x1A2F8` | `__n_cspFXMix` | 164 |
| `0x1A39C` | `__n_cspFXBus` | 68 |
| `0x1A3E0` | `__n_cspMP3Major` | 28 |
| `0x1A3FC` | `__n_cspMP3Trigger` | 96 |
| `0x1A45C` | `__n_cspRefreshVolume` | 172 |
| `0x1A508` | `__n_cspFadeStart` | 508 |
| `0x1A704` | `__n_cspFadeUpdate` | 728 |
| `0x1A9DC` | `__n_cspFadeRate` | 44 |
| `0x1AA08` | `__n_cspFadeVolume` | 208 |

## Conker behavior and layouts

Volume and pan setters update active voices. Sustain release selects either
the channel override or sound envelope, preserving the 16,000-microsecond
minimum. Effects retain the separate surround bit and seven-bit mix value.
Filter updates combine the voice key, sound key base, signed channel pitch
offset, pitch bend and the 440-Hz reference.

The fade handlers use channel +0x10 as a floating-point step, immediately
after current/target/rate bytes at +0x0D/+0x0E/+0x0F. This replaces explicit
padding in the shared field view without changing the 0x3C channel stride.
The player view now exposes its existing 0x14-byte `ALPlayer` node and byte
+0x36; all following offsets remain unchanged. Every previously pinned
library object retains its checksum after rebuilding these shared layouts.

Fades preserve the ROM's asymmetric zero-step timing and channel-mask
updates. The absolute-value expression uses the IDO `fabsf` intrinsic, which
emits the original floating-point instruction without a library call or
handwritten assembly. Four compilations resolved the candidate: initial C,
redundant terminal-return removal, intrinsic selection, and equality operand
order. The final correction accounted for the only two remaining words.

The notification handler posts to the player's configured message queue.
The MP3 controller pair, identified by its source-family counterpart, combines
the stored major byte with the incoming value and passes fixed volume/pan
arguments to the raw callee at `0x1263C`. That callee remains unchanged and
receives no library ownership credit. Its neutral link alias is
`__conker_audio_1263C = 0x8001263C`. Other external calls resolve to already
verified library definitions; internal calls resolve within this member.

## Verification

`./conker build --profile us` reports `build/us/conker.us.z64: OK`.
The complete 67,108,864-byte ROM has SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.
The main profile now maps 138 unique library objects through 171 sections,
including 74,624 exact text bytes. Main and game library maps together contain
91,136 exact text bytes. Inventory function counts are unchanged because this
previously raw range had no registered function work items or source unit.

After rebuilding the shared field views, `./conker game-build --profile us`
also reports its integrated payload `OK`: 2,072,880 bytes, SHA-1
`90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`. This checks existing overlay
library integration without implementing game code. All 157 repository tests
pass, generated progress is current, and `git diff --check` is clean.

The remaining sequence/player objects at `0x13320:0x15550` and
`0x15550:0x17870`, formatting helpers, MP3 CPU library routines in the game
overlay and bounded RSP microcode remain leads. The library search is still
active; ordinary game-code matching is outside the goal's current scope.
