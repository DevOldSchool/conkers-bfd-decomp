# US soundtrack renderer fidelity audit

The controller/envelope batch improves a local listening approximation. It does
not establish complete native N64 playback or promote album/name confidence.
[Measured metadata](../../config/soundtrack-render-audit.json) records the method,
source/render/reference hashes, representative results and remaining limits.
ROMs, saved states, extracted audio, native captures and downloaded recordings
remain in local ignored build outputs. Function matching stays paused.

## Grounded player behaviour

- `lib/libultrare/src/libultrare/audio/n_seqplayer.c`, `__n_setInstChanState`:
  program selection loads volume, pan and bend range; instrument sound lookup
  uses sorted key/velocity ranges. Changing program does not reprogram held voices.
- `n_cspctrl.c`, volume/pan/sustain handlers: controls reach allocated voices;
  volume ignores release voices. Sustain postpones release and pedal release
  applies a 16 ms minimum. Normal note-off does not apply that minimum.
- `n_csplayer.c`, MIDI/envelope handling: instrument bend range scales signed
  14-bit bend; pressure changes held velocity. Envelope updates target the
  original endpoint or use a 1 ms gain ramp once that endpoint has passed.
- `n_env.c` in the audio implementation: gain ramps
  are linear integer increments. The Python model interrupts from current gain;
  it does not continue the attack underneath a release multiplier. Negative
  bank decay values of -1 round to zero samples, not an indefinite sustain.
- `n_resample.c`: pitch is bounded and quantized before RSP resampling. Python
  integrates changing increments continuously, retaining linear interpolation.
- `n_csq.c`: loop-end count/current bytes and the physical backwards offset
  drive playback. Source bytes remain immutable in the converter. All owned-bank
  current/count pairs reviewed here are 255/255; no finite-loop bank example is
  claimed. Finite semantics have synthetic regression coverage. A positive
  offline cap stops at the exhausted loop rather than entering unreachable
  marker sections. All 149 sequences decode at cap one: 694 jumps/cutoffs.

The decoded bank has 170 instruments, no enabled bank tremolo/vibrato types,
491 infinite sample loops, 2,120 envelope releases shorter than 16 ms and 1,044
negative decay values. Runtime overrides can still alter the player.

## Sloprano resource commands

Sequence `0066` contains exactly these one-pass MP3 commands:

| Resource ID | Time in seconds |
|---|---:|
| 0239 | 29.250000 |
| 0240 | 95.887500 |
| 0241 | 105.862500 |
| 0242 | 167.187929 |
| 0238 | 220.386192 |

`n_cspctrl.c` uses CC27 as a global major and CC26 as the minor, requesting
`major * 100 + value`. The reviewed main adapter `src/done/main/init_12560.c`
resolves that exact ID in resource bank 0x16; see
[its boundary evidence](main_sequence_api_mp3_adapter_boundaries.md).
The separate experiment places decoded streams at those times and cuts the
preceding stream at the next request. It includes no inferred 0271/0272 trigger.
Native gain, decoder delay, post-frame callbacks and transition parameters
remain unverified; this is a timed assembly experiment, not a verified game mix.
The canonical default for the CSeq remains **Sloprano (Instrumental)**.

## Quantitative comparison

Local comparison uses 61 semitone bands, 11,025 Hz analysis, 2,048-sample hops and
approximately eight-second aligned windows. The table reports median best
window scores. Independent windows can pick different offsets; these numbers
are exploratory similarities, not identity probabilities or an ear review.
Exact downloaded recording hashes and per-window offsets remain in local reports.
No track-order mapping is used.

| Candidate / reference | Original render | Controller/envelope render |
|---|---:|---:|
| 0001 / Windy & Co. | 0.740 | 0.763 |
| 0034 / The Cock and Plucker (Alternate) | 0.958 | 0.958 |
| 0053 / Poo (Instrumental) | 0.916 | 0.931 |
| 0054 / Nintendo & Rare Logos | 0.930 | 0.989 |
| 0066 / Sloprano (Instrumental) | 0.936 | 0.937 |
| 0145 / Conker the King Reprise | 0.857 | 0.989 |
| 0066 / Sloprano, instrumental versus five-cue experiment | 0.767 | 0.928 |

Very short 0134 / Frying Tonight increases from 0.790 to 0.795. Unknown `0093`
was rendered as a regression representative without accepting a reference name.
Small numerical changes and remaining discrepancies are retained, not hidden.
The naming/reference metadata keeps its original source-guarded render hashes;
this separate audit records the new renderer instead of rewriting old evidence.

Reproduce a local comparison with installed NumPy/SciPy/soundfile:

```sh
python3 scripts/soundtrack_compare.py \
  --source /path/to/local-render.wav \
  --reference /path/to/local-reference.mp3 \
  --output build/comparison-new.json
```

The tool refuses to replace an earlier report and includes hashes and every
window offset. It does not select names or upload recordings.

## In-game capture

An isolated owned-ROM boot used existing Mupen64Plus 2.6.0 software-graphics
and CXD4 audio-microcode tooling. The small `scripts/mupen_audio_capture.c`
plugin records stereo AI DMA PCM before host playback or resampling, following
the [official Mupen audio byte-order and DAC-clock contract](https://github.com/mupen64plus/mupen64plus-audio-sdl/blob/master/src/sdl_backend.c).
It accepts only a supplied output directory, exclusively creates each WAV,
rotates on DAC-rate changes, bounds DMA reads and reports failures. It requires
little-endian hosts and an RSP executing audio microcode; its ProcessAList is empty.
This plugin must not be paired with HLE audio dispatch.

The longer opening capture is 22,018 Hz and aligns the logo candidate at
18.3902 seconds. Median similarity rises from 0.485 to 0.588, best window 0.688.
The capture contains the game audio mix, not a clean music stem; the remaining
difference is substantial. This supports opening material/timing only. No
Sloprano gameplay mix or every-track runtime use is verified. A second isolated
read-only saved-state replay outside the Poo area supports an eight-second `0053`
material excerpt at 0.848 before and after; the change is essentially neutral.
A bounded memory-header scan found no `0066` lead in the available states, which
is not proof that a Sloprano state is absent. Existing emulator
sessions and saves were not changed; no new emulator software was installed.

Compile focused plugin checks against an already installed Mupen SDK:

```sh
cc -std=c99 -Wall -Wextra -Werror -I/path/to/mupen64plus/include \
  tests/test_mupen_audio_capture.c -o /tmp/test-ai-capture
mkdir /tmp/fresh-ai-capture-test
/tmp/test-ai-capture /tmp/fresh-ai-capture-test
```

Checks cover channel byte order, RIFF size/rate, rate rotation, overwrite refusal,
DMA range/alignment and invalid DAC values. Python tests cover program defaults,
held controllers, sustain, pressure, interruption, cue replacement, guarded
asset reuse and finite/infinite loop safety. Browser checks exercise native
players, mutual pause, relative source links and responsive layout. Remaining
work is native filters/wet buses, frame/integer rounding, game marker/channel
selection and MP3 playback details, rather than guessed DSP parameters.
