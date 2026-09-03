# Conker US continued library reconstruction

This pass remains library-only, including library code located in the game
overlay. It does not authorize ordinary game-code matching.

The complete eleven reconstructed objects contribute 11,552 text bytes and
34 functions. Each complete text template has one main-executable occurrence;
every relocation resolves to a reviewed retail address and every allocated
nontext section is accounted for. The audited objects have no nonempty BSS.
This is independent comparison against the owned US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`, not comparison with generated C.

| Reconstructed member | Main ROM text interval | Bytes | Functions | Normalized complete-object MD5 |
| --- | --- | ---: | ---: | --- |
| `libc/syncprintf.o` | `0x2070:0x20d0` | 96 | 2 | `97231c99cb43c199a338fe1cb3c7c74b` |
| `audio/n_synthesizer.o` | `0x18e60:0x19ab0` | 3,152 | 9 | `a6bbe68588a5e3d50b331739541e4046` |
| `audio/n_drvrNew.o` | `0x1cbf0:0x1d900` | 3,344 | 6 | `101c524fed18ca3bc40e7838b0bfb1da` |
| `audio/n_mainbus.o` | `0x1fb40:0x1ffe0` | 1,184 | 1 | `8fe243e53dc86ec6dd3a873bc6556b39` |
| `audio/n_cspchan.o` | `0x17af0:0x17d80` | 656 | 8 | `a1820cafda59b6d19b21d810ec62d5b9` |
| `audio/n_cspsetfxmix.o` | `0x17df0:0x17ec0` | 208 | 2 | `35f91e87abd37cd4c0ee4fc8b2f04513` |
| `audio/n_cspsetfxparam.o` | `0x17f10:0x17f80` | 112 | 1 | `4d2eddff70f2eaf122b18d308389e4db` |
| `audio/n_cspevent12.o` | `0x18c60:0x18cb0` | 80 | 1 | `f667d3813d1d6439dfebbf5e4e4c261e` |
| `audio/n_auxbus.o` | `0x210c0:0x214f0` | 1,072 | 1 | `9df0cb2e008114fee6c1b9d23f868683` |
| `audio/n_resample.o` | `0x22460:0x226b0` | 592 | 1 | `15b4083e89eb181c7c8205d3b34997d3` |
| `audio/n_resample2.o` | `0x22040:0x22460` | 1,056 | 2 | `ac8c9a39179c93988c9a19f8391e256e` |

## Source and boundary evidence

The first four objects have dedicated evidence:
[formatting](libultrare_us_formatting_boundaries.md),
[synthesizer](libultrare_us_synthesizer_boundary.md),
[driver](libultrare_us_driver_boundary.md), and
[main bus](libultrare_us_mainbus_boundary.md).

Perfect Dark revision `169ed48bdcbfb3b568b028bd5bebb27680073514` supplies
independent N-audio source-family references. The reconstruction filenames
identify those families; they do not claim original Conker filenames.

`n_cspchan` groups the contiguous channel controls at `0x17AF0:0x17D80`.
The `0x17C00` raw navigation split falls inside the source-family sequence:
all-channel enable, channel off, channel on, fade, surround, forced fade.
PD's `n_cspchan.c` supplies that sequence; Conker omits the separate automatic
fade wrapper and prefixes two direct setters. The earlier split follows the
channel-off return with no padding. The complete reconstructed object agrees
across it and ends exactly at the independently matched `n_cspsetpan.o`.
Both direct setters keep neutral names because their field meanings are not
yet established. Channel stride 0x3C, fade bytes +0xD/+0xE, sequence channel
mask +0x30, maximum channels +0x34, and state pointer +0x60 are all reproduced.

The two effect-mix entries fill `0x17DF0:0x17EC0`, between exact pan and tempo
objects. They post a pair of floats as event 0x19 and MIDI controller 0x5C.
The effect-parameter entry fills `0x17F10:0x17F80`, following the exact tempo
object, and posts event 0x1A with three bytes and one word. PD's `n_csplayer.c`
provides the corresponding extended-event layouts and dispatch behavior.
The event 0x12 wrapper fills `0x18C60:0x18CB0`, immediately before the exact
sequence setter. Its name remains neutral: the standard header's stopping
event is 0x11, not the retail 0x12. All use Conker queue flags 2. The complete
objects own no nontext sections. The channel, mix and parameter candidates
matched on their first compile; the event wrapper needed its constant corrected.

`n_auxbus.c` supplies the two-pass auxiliary mixer family. Conker traverses
intrusive links at physical voice +0x8, rather than PD's pointer array, and
omits PD's leading clear and redundant bus test. The high-priority pass,
maximum-dependent scale calculation, paired commands, lower-priority pass,
and pull-count updates agree across the complete retail function. Correcting
the loop form, math declaration and macro temporary reproduced the object.

`n_resample.c` supplies the resampler pull family, including pitch clipping,
quantization, fractional samples, decoder calls, and the packed command.
Only the pull function is present: the reference's forwarding parameter helper
is absent. The complete first candidate has 592 text bytes and ends at
`0x226B0`. The following 64 zero bytes before `bzero.o` remain raw, outside
this object's ownership. `n_resample2.c` supplies the immediately preceding
two-function low-pass/scaling family; its first complete candidate matches
with the Conker physical-voice offsets and filter parameter IDs 4/17/18/19.

## Nontext sections and linking

The synthesizer owns 16 rodata bytes at `0x2C750:0x2C760`; the driver owns 32
at `0x2C770:0x2C790`. The auxiliary mixer, per-voice filter and resampler each
own 16 rodata bytes at `0x2C820:0x2C830`, `0x2C830:0x2C840`, and
`0x2C840:0x2C850`. Every byte, including alignment padding, equals the owned
ROM. Other storage references remain external and do not claim allocations.

Sources compile through `./conker libultrare` with the established IDO flags:
formatting uses `-O2 -g3`, audio uses `-O1 -g2`. Only non-runtime `.mdebug`
host/time metadata is stripped before pinning complete-object hashes.
The canonical main map stages these whole archive objects; the independent
comparison map stays raw. The former raw syncprintf, synthesizer and driver
work items were retired with the supported command and their dedicated evidence.

## Remaining library leads

This is not an exhaustion claim. The residual stock I-L template survey is
complete for that corpus; Rare-specific implementation leads remain:

- Main N-audio sequence and sound-player engines around `0x13320:0x17870`,
  and `0x19B50:0x1C060`.
- The subsequent [audio-engine pass](libultrare_us_audio_engine_reconstruction.md)
  resolves the reverb, envelope, decoder, surround, and compact-sequence parser
  families, including their complete nontext ownership.
- Raw formatting `xldtob` and `xprintf`, with existing independently scored
  reconstruction leads and switch-table ownership to resolve.
- MP3 CPU library code starting at overlay `0x151F2960`, including the
  main-bus callee at `0x151F2E88`; compare the pinned PD MP3 sources and exact
  decoder boundaries before claiming ownership.
- Separately bounded RSP audio/MP3 microcode remains raw binary work.

No ordinary game-code C work is included in this pass.

## Integrated validation checkpoint

After mapping all eleven objects and pinning their complete hashes,
`./conker build --profile us` rebuilt the complete 64 MiB US ROM and reported
`build/us/conker.us.z64: OK`. No ROM checksum failure occurred. The first
new driver/main-bus link rejected cross-region JAL relocations; the documented
main-PC aliases corrected linking, and the subsequent full ROMs were exact.

`./conker game-build --profile us` also reproduced the complete game-overlay
payload (`conker.game.us.integrated.bin: OK`); this was validation of shared
library changes, not game-code implementation. All 151 repository tests pass,
`./conker progress check` reports current generated output, and
`git diff --check` is clean. Existing map-count and progress assertions were
updated for the verified archive placements, including the reviewed internal
`0x17C00` navigation split.

The subsequent [sequence helper pass](libultrare_us_sequence_helper_reconstruction.md)
resolves `0x1AAE0:0x1C060` and the heap/bank-relocation families at
`0x12820:0x12D80`. The earlier checkpoint counts above are historical.
