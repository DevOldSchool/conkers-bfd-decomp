# Conker US non-MP3 audio assets

This pass classifies indexed bank `0x17` entries `0` through `3` from the main
audio initialization path. It does not infer their roles from proximity to the
MP3 decoder entries or from file magic alone.

## Runtime ownership

Main function `func_80008180` establishes the four-entry relationship:

- `0x80008220` loads bank `0x17`, entry `2` for the audio DMA configuration;
- `0x80008244:0x80008284` obtains and loads entry `0` into allocated memory;
- `0x80008294` loads entry `1` and `0x800082AC` loads entry `2`;
- `0x800082C0` calls `func_80012934`, the matched
  `__conker_bnkfNew(control, wavetable, bankAddress)`, with decoded entry `0`,
  entry `2`, and entry `1`, respectively;
- `0x800082E0` loads entry `3`, copies its sequence descriptor table, and
  `0x80008368` calls the matched `alSeqFileNew` to relocate those descriptors
  against the original entry-3 base.

The matched Rare bank patcher adds its second argument to every
`ALWaveTable.base`, proving entry `2` as wavetable/sample storage. It uses its
third argument to resolve Conker's encoded external instrument and sound
pointers, proving entry `1` as the external sound-bank data base. Entry `0` is
the root bank-control graph and entry `3` is the compact-sequence collection.

## Structural contracts

| Entry | Role | Decoded bytes | Type flags | Storage |
| --- | --- | ---: | ---: | --- |
| `0x17:0` | `B1` sound-bank control | 7,768 | `0x10` | RZIP |
| `0x17:1` | external sound-bank data | 430,608 | `0x00` | raw |
| `0x17:2` | wavetable/sample data | 21,705,520 | `0x01` | raw |
| `0x17:3` | `S1` compact-sequence bank | 685,656 | `0x00` | raw |

The decoded entry-0 header has revision `0x4231` (`B1`), one bank at offset
eight, 170 instruments, a null percussion slot, and a 22,050 Hz sample rate.
Conker's matched bank patcher explains why most nested pointer values cannot be
treated as ordinary entry-0-relative offsets. Static validation of every object
proves that its external fetch address resolves to
`(encoded_address >> 5) & ~7`. Instrument zero is embedded in entry `0` and its
1,762 sounds use those encoded external addresses. The other 169 instruments
are in entry `1`; their 1,024 sounds use instrument-relative offsets, matching
the sound patcher's selected relocation base.

The complete graph contains 2,786 sounds, envelopes, key maps, wavetables, and
ADPCM books, plus 491 ADPCM loops. Every US wavetable is ADPCM; this bank has no
RAW16 wave. The books all use order two and either one or four predictors.
Conker's extra word at wavetable `+0x14`, which the matched runtime patcher
clears, is preserved in the graph rather than interpreted.

The 2,786 wavetables reference 2,258 unique, non-overlapping sample ranges in
entry `2`. Those ranges cover 21,698,538 of its 21,705,520 bytes. The remaining
6,982 bytes are retained in the complete `wavetable.bin`; 6,978 are gaps
between referenced ranges and four trail the final range. ADPCM lengths retain
their original trailing byte where present, while the manifest separately
records the multiple-of-nine payload length used by Conker's decoder.

Entry `3` has revision `0x5331` (`S1`) and 149 descriptors. The first sequence
begins exactly after the `0x4AC`-byte descriptor table. All sequence offsets are
four-byte aligned; every length is in bounds; and each alignment gap is zero
through three bytes. The bytes in those gaps are retained verbatim because many
are nonzero and therefore cannot be regenerated as generic padding. Every
compact sequence has a valid 68-byte, 16-track header. Observed divisions are
384 and 480 ticks per quarter note, and the collection exercises one through
sixteen active tracks.

## Supported boundary

```sh
./conker audio-assets survey --rom /path/to/baserom.us.z64
./conker audio-assets verify --rom /path/to/baserom.us.z64
./conker audio-assets extract --rom /path/to/baserom.us.z64
./conker audio-assets preview --input build/assets/audio/us/sequences
./conker audio-assets sample-preview
```

Extraction emits the three sound-bank companion payloads, the complete
`sound-bank-graph.json`, 2,258 uniquely bounded `.adpcm` sample slices, and 149
individually bounded `.cseq` files. Every sample hash and byte range is tied to
its source wavetable reference. Verification reconstructs the complete `S1`
entry, including descriptor offsets and alignment padding, byte-identically.
It also decodes the 362 unique loop-bearing sample contexts and compares the
16-sample frame containing each loop start with the state retained in `B1`.
Of those frames, 359 match exactly; all samples in the other three are within
two signed PCM levels. A reversible ADPCM encoder remains separate work.

`sample-preview` uses each sample's retained predictor book to write the 2,258
unique ranges as deterministic mono, signed 16-bit PCM WAVs at the bank's
22,050 Hz rate. The generated manifest retains source and decoded hashes,
wavetable references, durations, and loop boundaries. The US set contains
38,573,136 decoded samples (1,749.35 seconds before pitch-shifting, overlap, or
loop repetition). The WAVs deliberately omit an import path and declare
`editable_import_supported: false`; decoding is proven, but lossy re-encoding
is not.

The `preview` action accepts either one `.cseq` file or a directory of them and
emits dependency-free Standard MIDI files. It mirrors Conker's compact-track
reader, including `0xFE` back-references, converts duration-bearing note-on
events into scheduled note-offs, and retains each loop payload in both a
human-readable marker and an exact sequencer-specific event. The preview is a
single linear pass: it does not expand finite or infinite CSeq loops. MIDI
players also substitute generic instruments because the `B1` graph and
wavetable previews are not assembled into a General MIDI soundfont. It therefore
validates event decoding, notes, timing, tempo, controllers, programs, and loop
locations, but not final Conker timbres or full looping playback.
