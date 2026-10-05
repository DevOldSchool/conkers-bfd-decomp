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

## Targeted Sloprano saved-state checkpoint

The two supplied opening/fight OpenEmu saves were found, copied into private
ignored build inputs and successfully loaded with the existing isolated emulator.
Both use the owned US ROM and compatible Mupen save format. Screenshots confirm
the boss opening and fight. Originals and the user's emulator session were
preserved; no controller input or software installation was performed.

[Native review measurements](../../config/soundtrack-native-review-audit.json)
record capture hashes and qualifications. Opening audio lasts 142.550 seconds;
fight audio lasts 135.263 seconds. The opening eventually changes scene and the
unattended fight reaches death. These are full game mixes, not clean music stems
or a complete successful boss playthrough.

The optional `CONKER_AUDIO_US_MP3_REQUEST_LOG=1` capture probe samples the reviewed
retail-US adapter's last-request halfword at physical RDRAM `0x427f4`, using the
core's word-swapped memory layout. It logs state changes at AI DMA boundaries,
exclusively creates its CSV and performs no RAM writes. This is deliberately
US-specific. Same-ID retriggers can be missed; an initial or retained ID does
not prove playback. In the opening, the state changes from retained 457 to 239
at 35.388954492 captured-audio seconds. Fight state remains 239. None of the
later distinct song IDs is observed in these bounded unattended replays.

The extracted MP3 0239 nominal clock is 22,050 Hz; native AI PCM is 22,018 Hz.
An explicit observed-clock comparison of its first six seconds raises waveform
correlation from 0.123452 to 0.935334. Audible alignment is 35.490249 seconds,
about 101.295 ms after the request-state observation. Two/four/six-second
projection gains are 0.471240, 0.472386 and 0.473394. This supports this cue's
clock, excerpt timing and approximate relative amplitude. It does not establish
an exact decoder delay or every cue's gain. The old five-cue experiment applies
0.710459 overall peak attenuation; its relative vocal level remains unverified.
A separate six-second 0239 audition uses the observed clock and 0.473394 gain.
Default sequence renders and the full timed assembly are preserved unchanged.

The new private `us-native-review` preview reuses all 149 sequence WAVs,
149 MIDI/CSeq pairs, 2,258 samples and 11 MP3 candidates from sibling previews.
It adds the two captures and the measured cue audition in a clearly qualified
section. Numeric IDs, canonical candidate titles and confidence metadata remain
unchanged. Sixty-nine Python tests pass, including clock/gain recovery and
capture hash/ROM/path/overwrite guards. Focused C tests cover request-state byte
order, change suppression and overwrite refusal in addition to existing PCM
checks. Browser validation confirms all three new players ready, advancing
playback, mutual pause and no console errors. Direct-file browser automation is
blocked by browser protocol policy; direct-open file integrity is checked but
actual `file://` playback/storage remains unverified. The temporary loopback
validation server is stopped after testing.

## Exact user-authorized health cheat experiment

[Health capture audit](../../config/soundtrack-health-cheat-audit.json) records
three additional runs, clearly marked as altered runtime experiments. The owned
US ROM MD5/CRC/country were checked. A fresh private `mupencheat.txt` contains
only `800CC49A 0006`; the existing console lists it as cheat 0 and records its
activation with `--cheats 0`. The [console format](https://github.com/mupen64plus/mupen64plus-ui-console/blob/2.6.0/src/cheat.c)
and [core semantics](https://github.com/mupen64plus/mupen64plus-core/blob/2.6.0/src/main/cheat.c)
show this is a continuous 8-bit write of 06 at physical RDRAM 0xCC49A. No
additional invulnerability, gameplay, ROM or committed game-source patch is used.

The optional `CONKER_AUDIO_US_HEALTH_LOG=1` capture observer reads that one US
byte at AI DMA boundaries and exclusively creates its change log. It performs
no game-memory writes. Health is initially the save's 5, becomes 6 at 1.002816
captured-audio seconds, falls to 5 at 179.764738 and returns to 6 at 179.771460.
This observes restoration approximately 6.72 ms after a damage decrement; it
does not imply the cheat prevents every kind of death or fixes gameplay.
The health-only capture lasts **266.389681 seconds**, with Conker alive in its
final screenshot. The preserved 135.263-second unmodified replay reached death.

Survival alone does not advance the encounter in this run. MP3 request state
remains 0239 throughout; no later distinct song ID is observed. Two separate
private probes use the documented [Mupen controller API](https://github.com/mupen64plus/mupen64plus-core/blob/2.6.0/src/api/m64p_plugin.h)
for ordinary button inputs, with centred axes and no guest memory access. One
pulses B; the other presses B initially, holds R and pulses Z. Dispatch logs and
focused SDK checks verify their button bits, but **no successful hit, aiming
effect or later phase is verified**. These bounded recordings last 68.567536
and 67.431011 seconds. Seeing paper in a screenshot does not establish that a
probe equipped it, because the saved scene may already include it. The existing
capture image has no installed SDL input driver; these small project-local
probes do not install software or change the normal emulator session.

The longer encounter's six-second independently aligned spectral-window median
is 0.702931 against the instrumental render and 0.695424 against the five-cue
assembly. These exploratory numbers and the absence of later request IDs do
not support further cue timing/gain changes. Existing reconstruction outputs,
canonical candidate titles, numeric IDs and confidence metadata are preserved.
Correctly timed and aimed attacks, or saves after successful phase transitions,
are still needed to obtain evidence for later song sections.

The fresh private `us-health-review/index.html` adds all three labelled recordings
to the previous native review, sharing its files rather than replacing it.
All 69 Python checks and focused capture/health C tests pass. Private controller
checks cover expected B/R/Z masks, centred axes and absent other ports. Browser
validation confirms the three added players ready and advancing, mutual pause,
no console errors or horizontal overflow, and dialog-free JSON preparation.
The temporary loopback server is stopped; direct-file browser testing retains
the protocol-policy limitation already described above.

## Later saved-state excerpts and measured stream experiment

[Phase audit](../../config/soundtrack-sloprano-phase-audit.json) records eight
copied compatible saves: numbered labels 1–5, 7 and 8, plus a separate “first hit”.
No exact hit-6 save was found. Names and timestamps do not establish chronological
phase counters. All eight loaded with the existing isolated core; private copies
were captured for approximately 37–42 seconds each. Original saves and ROM hashes
remain unchanged. Capture cheats were disabled, though source-save history is
unknown. Earlier health-enabled recordings retain their explicit cheat labels.

The hit-8 save initially opens on a pause menu. A private controller plugin sends
one ordinary Start pulse at polls 120–125, then releases it. Screenshots confirm
resume and the boss collapse/ending scene. It uses the documented input API,
with no game-memory writes or additional cheat. The paused diagnostic capture
stays outside the listening preview.

The read-only MP3 request observer plus waveform alignment provides these new
measurements. Times are captured-audio seconds; six-second excerpts are used
except 0272, whose available source lasts about 3.32 seconds. Scores are exploratory
waveform correlations in mixed game audio, not calibrated identity probabilities.

| MP3 ID | Capture label | Request | Aligned onset | Nominal 22,050 Hz score | Observed 22,018 Hz score | Projection gain |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| 0240 | first hit | 3.933 | 4.027 | 0.162 | 0.825 | 0.473 |
| 0241 | first hit | 13.903 | 14.005 | 0.137 | 0.723 | 0.446 |
| 0242 | hit 3 | 5.798 | 5.899 | 0.117 | 0.886 | 0.468 |
| 0238 | hit 7 | 3.359 | 3.459 | 0.057 | 0.980 | 0.470 |
| 0271 | hit 8, resumed | 4.437 | 4.562 | 0.096 | 0.763 | 0.460 |
| 0272 | hit 8, resumed | 29.458 | 29.582 | 0.156 | 0.939 | 0.470 |

Hit 1 independently reproduces 0240/0241 with approximately 97/99 ms onset
lags and similar projections. Combined with the earlier 0239 result, seven
resource IDs now have bounded native excerpt evidence. IDs 0237 and 0432 remain
unclassified; initial values may be retained and are not proof of playback.
The other saves provide game mixes and scene views, not eight distinct verified
musical sections or a continuous successful boss playthrough.

The [explicit experiment profile](../../config/soundtrack-sloprano-stream-experiment.json)
uses the observed 22,018 Hz MP3 clock, common approximate gain 0.47 and 100 ms
onset delay for the five exact CSeq 0066 cues. A common gain avoids mistaking
background-biased per-excerpt projections for different decoder volumes:
`__n_cspMP3Trigger` requests the same `0x7fff` volume and `0x40` pan. Ending
streams 0271/0272 have approximately 124 ms onset lags and no trigger commands
in the linear CSeq; they remain in the native game mix rather than being spliced
into an assumed arrangement.

The new renderer resamples only MP3 clips at their explicitly measured clock.
It preserves the instrumental timeline and applies replacement at delayed cue
onsets. ROM, sequence, instrumental, cue-timing and both stream-source hashes
must match the profile. Existing outputs are refused. Default renders and prior
assemblies remain unchanged. The new assembly needs no additional global peak
attenuation, but its instrumental synthesis, level, channel/marker arrangement,
callbacks, filters and wet buses remain approximate. No label confidence or
album identity is promoted by these measurements.

The fresh private `us-phase-review/index.html` shares the existing 149 sequences,
2,258 samples and 11 MP3 candidates, and adds eight game mixes plus the separate
experiment. Its comparison section now has 15 native/cue/experiment players.
All 73 Python tests pass, including measured clock, gain, delay, replacement,
source/cue guards and output preservation. The private Start plugin compiles
with `-Wall -Wextra -Werror`. Static checks resolve all 2,744 assets and check
available hashes. All nine new players load, advance and mutually pause in the
local browser, without console errors or horizontal overflow; preparing naming
JSON does not open a Save dialog. The loopback-only server and validation tab
are closed. Actual `file://` playback remains unverified under browser protocol
policy; direct-file assets and embedded metadata are checked.
