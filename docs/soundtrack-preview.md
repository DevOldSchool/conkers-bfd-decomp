# Local soundtrack listening and naming

The audio tools extract 149 retail US compact sequences, 2,258 unique ADPCM
sample ranges and a 170-instrument sound-bank graph. A sequence is an event
stream, not a recording. The bank also contains jingles, ambience and sequenced
effects. Sample ranges are instrument/sound building blocks, not soundtrack
tracks. Separately, `mp3-assets` extracts 453 MP3 streams and three decoder
assets; those streams include material that cannot be classified as music from
file format alone.

`audio-assets soundtrack-preview` makes a dedicated browser listening desk and
149 stereo PCM WAV renders using the extracted game samples. Numeric CSeq IDs
remain unchanged; MIDI and CSeq downloads are provided alongside each render.
Samples have their own section. Nominated MP3 music comparison candidates use
their own stream IDs, separate from sequence IDs.

## Build and open

Use a Python environment with NumPy installed for rendering. No soundfont,
FluidSynth, MIDI player, external browser script or audio upload is required.
Supply the reviewed ROM locally; extracted files and renders stay under ignored
`build/` directories.

```sh
./conker audio-assets extract --rom /path/to/owned-us-rom.z64
./conker audio-assets verify --rom /path/to/owned-us-rom.z64
./conker mp3-assets extract --rom /path/to/owned-us-rom.z64
./conker mp3-assets verify --rom /path/to/owned-us-rom.z64
# Activate a Python environment containing NumPy before invoking ./conker.
./conker audio-assets soundtrack-preview \
  --mp3-input build/assets/mp3/us \
  --output build/assets/soundtracks/us-albums
```

Open `build/assets/soundtracks/us-albums/index.html` directly in a browser.
The HTML embeds sequence/sample metadata; audio, CSS and JavaScript use relative
paths. Keep the whole preview folder together. No server or JSON fetch is required.
An optional static HTTP server can serve the same folder for browser automation.
Add `?sequence=66` to select a stable numeric ID. `--input` defaults to `build/assets/audio/us`;
`--labels` defaults to `config/audio-sequences.json`. `--mp3-input` is optional.
The default output is `build/assets/soundtracks/us`, but an existing output is
always refused. Choose a fresh output rather than replacing a prior preview.
Rendering publishes a complete directory only after success and verifies the
extracted CSeq and sample hashes. Included MP3s must match the same ROM hash.
Reference recordings used for comparison are not copied into the listening desk.

Naming drafts use browser storage when available, keyed by ROM hash and numeric ID.
Direct-file storage varies by browser and file location; a persistent notice warns
when storage fails. Drafts then remain only in the open page. Prepare and copy JSON
before leaving or moving the folder. HTTP and file origins do not share drafts.
Their sequence source hashes must still match when reloaded. Prepare naming export
displays reviewable JSON without starting a download. Copy the JSON or explicitly
choose Download prepared JSON, which may open the browser's Save dialog.
Drafts do not modify repository labels or imply an independently
verified identity. Export drafts before changing browser/profile, host, port or
clearing browser storage. Removing a draft restores the preferred album title or contributor label.

## Render scope

Instrument major controller 32 and program change select `(major << 7) + program`.
Sound lookup mirrors the reconstructed player's binary search over key and
velocity ranges. Pitch uses key base and signed detune; sample loops repeat
while notes sound. The renderer approximates attack, decay, release, velocity,
volume and pan. It attenuates peaks to prevent clipping without amplifying quiet
material. Source hashes, loop markers, mapping counts, sample IDs, PCM rate,
duration, attenuation and WAV hashes are retained in the preview manifest.

These are listening approximations. CSeq loops are not expanded. All tracks
sound together, without runtime channel mutes, fades or sequence-volume changes.
Native effects, filters, vibrato and tremolo are absent. Volume, pan and pitch
bend are captured at note-on; changes to held notes, sustain, runtime channel
envelope overrides and finite sample-loop counts are not reproduced. The
renderer is neither native N64 playback nor the album recording. MP3 candidates
play the exact MPEG frames without synthesis or loop expansion. Browser MP3s omit
native post-frame `L:` callbacks and trailing metadata; byte-identical original
streams remain separately under `music-streams/sources/` with source hashes.

The reviewed local render contains 149 sequence WAVs, 147 with nonzero PCM.
`0000` has no notes; `0008` has one mapped note but its bank sound volume is zero.
One of 108,836 note events has no matching key/velocity sound, in `0052`.
Source CSeq and MIDI remain available for both silent entries. This is render
coverage, not proof that every entry is music or used during gameplay.

## Names and album comparison

The existing [label map](../config/audio-sequences.json) retains 112 contributor
identifications, four tentative labels and 33 unknown entries. The
[listening evidence](evidence/us_music_track_names.md) explains their provenance;
automated gameplay-recording references are supporting leads, not proof of use.
No existing confidence is promoted. The gamerip listing’s exact titles and capitalization are canonical vocabulary
for supported candidates; older album titles remain source-specific aliases; contributor names remain searchable aliases.
Asset-match confidence is separate and remains tentative until independent
listening or other identity evidence establishes correspondence. One album song
may contain multiple ROM segments; no one-to-one mapping is imposed.

[Comparison metadata](../config/soundtrack-reference.json) records the linked
[18-track soundtrack](https://downloads.khinsider.com/game-soundtracks/album/conker-s-bad-fur-day-soundtrack)
and [27-track Unreleased Tracks listing](https://downloads.khinsider.com/game-soundtracks/album/conkers-bad-fur-day-unreleased-tracks),
checked on 2026-10-04. Listing order is never mapped to ROM order. Title/context
leads are marked separately from strong audio-correlation candidates.

All 45 entries now have an explicit review, with a complete table in
[Retail US album correspondence review](evidence/us_album_correspondences.md).
The soundtrack has 18 tentative entries and no unresolved entries; the unreleased
listing has 25 tentative entries and two unresolved entries (`electric wires` and
`zombie attack`). No full recording identity has been independently confirmed by
listening. With the additional gamerip review, candidate titles cover 78 sequence IDs and 11 MP3 streams, while the
original 112 / 4 / 33 label confidence counts remain unchanged.

The additional [71-track Unofficial Soundtrack / gamerip listing](https://downloads.khinsider.com/game-soundtracks/album/conker-s-bad-fur-day-gamerip)
has 71 tentative material/segment correspondences and no independently verified full identities.
Its site info file supplies no ROM revision or extraction/recording method. All 71 recordings
were compared against the same 149 renders and 453 streams; the original 45 recordings
were also compared against the new inventory. The closer audio adds 25 candidate sequence
IDs, including four original unknowns (0027, 0045, 0134, 0136). Explicit preferred-variant
resolutions select Cognitive Cogs (0018), Credits (0113), Broken Franky (0119), and
The Panther and the Weasel (0140); earlier album titles and contributor aliases remain
searchable. Original label/confidence counts and original album coverage are unchanged.

The user-selected canonical vocabulary now covers 68 sequence candidates and seven MP3
candidates. Ten sequence leads and four MP3 leads have no established gamerip counterpart
and remain explicitly qualified older-reference labels. Exact listing punctuation/case
are preserved, including `Conker the King Reprise`, `It’s War`, `Enter the Vertex`, and
`Ole!!!`. Sequence 0053 prefers `Poo (Instrumental)` and 0066 `Sloprano (Instrumental)`;
the older Poo/Sloprano titles remain aliases. These names describe candidate material,
not independently verified complete recordings or recovered source symbols.

The gamerip’s Sloprano and Sloprano (Instrumental) both share 0066 instrumental material;
the latter has the closer excerpt alignment. This does not turn the render into a vocal mix.
Frying Tonight has only a 3.53-second ending candidate (0134), Countdown only a 6.87-second
cue (0136), and The Eel only an opening candidate (0135). Credits (Alternate) is a weaker
partial 0113 lead and strongly overlaps the older album’s Reprise edit. Those recordings
are not interchangeable. The electric wires bridge resembles a different portion of
Frying Tonight than 0134, so it remains unresolved; zombie attack has no reliable bridge.

The primary search compared all 149 sequence renders and 453 sanitized MP3 streams.
Weak entries also received isolated-channel, short-cue, tempo/pitch and broad-spectrum
sample checks. A correspondence can be a shared theme, ambience component or song
segment. The metadata retains source/reference hashes, offsets, competing rankings,
selected evidence windows and reasons for uncertainty. Scores are not probabilities.
Source changes are rejected rather than carrying reviewed evidence onto new bytes.

The reference album entries show tentative/unresolved status and controls for each
accepted sequence or stream candidate. A sequence control opens the naming desk;
a stream control opens its separate player. Press Play explicitly after reviewing.
Earlier preview folders and browser draft keys remain preserved. `Sloprano` keeps
its instrumental sequence description and separate streamed segments; no full vocal
mix or unsupported vocal/instrumental stream classification is supplied.

## Validation

The targeted audio/preview suite tests tempo and note timing, bank/program
selection, duplicate-key durations, key/velocity lookup, sample loops,
envelopes, stereo PCM, silence, invalid MIDI, source hashes, unsafe paths,
existing-output preservation, and MP3 ROM compatibility.

```sh
PYTHONPATH=tests python3 -m unittest test_audio_assets test_soundtrack_preview
git diff --check
```

The existing ROM verifier reconstructs the complete compact sequence bank
byte-identically. It verifies 362 sample loop-state contexts: 359 exact frames,
maximum error two PCM levels. The MP3 verifier reconstructs all 456 assets
byte-identically. Browser validation must additionally exercise selection,
actual playback, filters, naming-draft persistence/export preparation and sample controls.
Desktop and narrow mobile layouts, sequence/sample/MP3 playback, filters and
draft persistence were checked over localhost. The generated page has no metadata
fetch or HTTP-only resource links. Direct `file://` browser automation was blocked
by its protocol policy, so direct-file playback and persistence remain unverified
in that browser. The static server is temporary and is not required by the page. Export JSON was checked
without requiring a completed browser download. All 149 render hashes also
matched a repeat generation.
No function-matching or full-ROM code build is required for this tooling change.

## Shared preview styling

`scripts/preview-common.css` holds the existing model inspection page base styles.
Model generation embeds them to retain its standalone HTML behavior; soundtrack
generation copies them beside the HTML. Both use the same charcoal panels, blue
accents, system typography, margins, controls and focus states. Page-specific
layout remains separate; other generated previews were not overwritten.
