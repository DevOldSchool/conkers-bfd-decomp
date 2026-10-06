# Conker US MP3 embedded cue extraction

The reconstructed MP3 runtime supplies a format-level boundary for embedded
records. After decoding an MPEG Layer III frame whose copyright bit is set,
`mp3main_continue_file` reads one null-terminated record and forwards it through
the optional callback stored at `0x800E0E00`. The callback happens after the
frame is decoded, so the cumulative decoded sample count gives an exact event
time without recognizing a cutscene or speaker.

`./conker mp3-assets cue-extract` walks those same frame boundaries in all 453
US bank-16 streams. It writes a manifest and one JSON sidecar per stream that
contains cues under ignored `build/assets/dialogue/us/`. Each cue retains its
stream entry, zero-based MPEG frame, source byte offset, decoded sample offset,
time in seconds, exact payload bytes, and null-inclusive record size.

The US survey contains 282,715 MPEG-2 Layer III frames at 22,050 Hz and 9,856
embedded records across 220 streams. Every record is exactly eight payload
bytes, begins with `L:`, and is followed by one null byte. Payload byte 2 is
`0x01` in 9,837 records and `0x02` in 19 records. The remaining bytes are kept
opaque. The marker suggests a lip-related role, but no runtime consumer has yet
proved that interpretation, and the records contain no independently proven
speaker or subtitle identifiers.

The parser also records but does not consume each stream's trailing bytes. At
the first non-frame boundary, 156 streams carry an ID3v1-shaped `TAG` record;
their metadata identifies Robin Beanland and an `untitled` source, not a
character speaker. Retaining the trailer offset and SHA-1 prevents those source
records from being mistaken for dialogue tables.

`./conker mp3-assets cue-verify` repeats the complete read-only walk and rejects
an unsupported frame, missing terminator, non-eight-byte record, or marker other
than `L:`. It does not rewrite MP3 data, infer subtitle strings, or modify the
ROM. Speaker, subtitle, and cutscene mappings remain deferred until their
runtime selection paths are available in C.
