# Rare-modified libultra objects

This directory originally built the eleven complete Rare-modified libultra objects
identified in Conker's US main executable. The bounded source and header
snapshot comes from n64decomp/007 revision
`c4356466796c697dfd298010b9bed261f9ed8c6a` and retains its US IDO 5.3 flags.

Those objects' complete text and allocated non-text sections are mapped in
`docs/evidence/libultrare_us_additional_object_bounds.md`. Their entries in the
checked-in MD5 list are the upstream project's accepted US object output and are
verified before the archive is staged for the Conker link.

This is deliberately separate from the pinned Nintendo `lib/ultralib`
submodule: these members are Rare variants and must not be represented as stock
SDK objects.

The game overlay additionally links a reconstructed `gu/mtxutil.o`. It uses
the pinned stock SDK matrix algorithms with this snapshot's existing `PR/gu.h`,
whose `FIX32TOF` divides by 65,536. With the graphics routines' IDO `-O3`
setting, its complete text matches Conker US, including all four functions,
both resolved calls, and padding. Its checksum is a Conker reconstruction
checksum, separately identified in `object-md5s.txt`; it is not an upstream
GoldenEye object checksum. See `docs/evidence/game_sdk_mtxutil_variant.md`.

The game archive also includes Conker's rotation, single-precision sine/cosine,
two-angle perspective, and SI access wrappers. Their complete text, relocation
bindings, and any data/rodata sections are documented in:

- `docs/evidence/game_sdk_rotation_variant.md`
- `docs/evidence/game_sdk_trig_perspective_variants.md`
- `docs/evidence/game_sdk_si_access_variant.md`

The main archive includes 24 reconstructed N-audio objects, covering 34
functions and 6,736 text bytes, plus the complete initialization data and
output-filter constant sections. These retain reviewed Conker layouts and
behavior, including event flags, release callbacks, auxiliary-bus lists, and
filter parameters. Their source lineage, complete boundaries, and resolved
byte checks are recorded in `docs/evidence/libultrare_us_naudio_variants.md`.
They use bounded partial views where the complete runtime structure is not
needed; those types do not claim allocations for unreviewed fields.

The next library-only pass adds ten N-audio objects and `libc/syncprintf.o`,
covering another 34 functions and 11,552 text bytes. Five whole rodata sections
also match. Synthesizer and driver raw source units were promoted only after
complete-object reconstruction; the extended controls, mixers, and filters use
the same reviewed Conker layouts. See
`docs/evidence/libultrare_us_continued_reconstruction.md` for that pass.
The stock I-L template survey does not exhaust these Rare implementation leads.

The reconstructed `-O2 -g3` graphics/formatting and `-O1 -g2` audio objects remove IDO's
non-runtime `.mdebug` section, which embeds the build hostname and timestamp.
The scheduling flags remain unchanged. Forced rebuilds reproduce the recorded
normalized object MD5s. Existing upstream object checksums are preserved.

Five further N-audio objects reconstruct the complete ADPCM decoder, reverb,
envelope, surround configuration, and compact-sequence parser: 24 functions
and 16,656 text bytes. The decoder and parser own text only; the surround
configuration owns 16 BSS bytes, and envelope/reverb own their complete tables.
Checked main-link preparation adjusts only compiler data-to-code relocation
addends for the main runtime address alias. Original compiler objects retain
their pinned hashes; instructions and relocation records remain unchanged.
See `docs/evidence/libultrare_us_audio_engine_reconstruction.md`.

The sequence helper pass adds `audio/n_seqplayer.o`, `audio/heap.o`,
`audio/bnkf.o`, and `audio/osc.o`: 31 functions and 8,320 text bytes.
Only the oscillator allocates nontext sections: 16 rodata bytes and 16 BSS
bytes. The sequence/channel views now describe the verified voice lists,
oscillator callbacks, and instrument loading state. Bank relocation retains
Conker's encoded instrument addresses and per-wave field at +0x14. See
`docs/evidence/libultrare_us_sequence_helper_reconstruction.md`.

The complete Rare `libc/xprintf.o` now owns both formatting functions and its
original data and rodata sections. It replaces the earlier `xprintf_data` and
`xprintf_rodata` build members; the C switch generates all 52 runtime table
entries. Existing checked relocation preparation adjusts only their execution
alias addends. The map preserves the real rodata section with an explicit
link-order override. See `docs/evidence/libultrare_us_xprintf_reconstruction.md`
for complete-object checks and the byte-identical full US ROM.

The complete Rare `libc/xldtob.o` supplies all three floating-point formatting
functions and its 96-byte rodata section, replacing the separate `xldtob_data`
member. The whole 2,848-byte text, all relocations and constants match, and the
full US ROM remains byte-identical. Its completed source is preserved here via
the supported retirement command. See
`docs/evidence/libultrare_us_formatting_boundaries.md` for the final object hash,
function boundaries and the earlier candidate history.

The MP3 bit/Huffman utility member `mp3/util.o` retains independently sourced
assembly with four approved Conker table-access changes. All five entries and
all 1,152 text bytes match, including every relocation. The stream and decoder
use its real exports in place of their former fixed-address aliases. The
pointer slots remain external and do not claim original BSS ownership. See
`docs/evidence/libultrare_us_mp3_util_boundaries.md` for provenance and checks.
