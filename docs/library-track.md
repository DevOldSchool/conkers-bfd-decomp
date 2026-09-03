# Library track

The project builds Nintendo 64 library code from `lib/` separately from
Conker-specific `src/` code. Stock SDK objects come from the pinned ultralib
submodule, while verified Rare variants live in a bounded Rare source snapshot.

## Reviewed code-boundary coverage

As of the 2026-09-03 search, reviewed source-unit intervals plus exact archive
text cover 268,672 of 2,237,392 tracked US code bytes (12.0083%). Another
1,968,720 bytes (87.9917%) still lack that reviewed ownership coverage.

| Area | Reviewed source-unit bytes | Exact archive text | Combined coverage | Tracked code bytes |
| --- | ---: | ---: | ---: | ---: |
| Main | 0 | 98,512 | 98,512 (59.8813%) | 164,512 |
| Game | 122,368 | 47,792 | 170,160 (8.2089%) | 2,072,880 |

This is boundary coverage, not implementation completion. It merges the US
intervals of the 126 source units with reviewed boundary evidence and the
canonical maps' archive `.text` intervals, separately per overlay, so overlaps
are counted once. The two unreviewed bootstrap units are excluded. Generic
raw split points alone receive no reviewed-ownership credit. Initialized data,
rodata, BSS, and assets are outside this code-byte denominator. The separate
matched-code figure is 150,564 bytes (6.7294%); see generated
[`progress.md`](progress.md).

## Current US integration

`lib/ultralib` is pinned to commit
`e24c836796df4bf520ff8b11a5c9d2cea3a66cbd` of decompals/ultralib. The US
profile links three trimmed archives built from that checkout:

- `libultra_2_0L`: 40 unique objects and 48 mapped sections.
- `libultra_2_0I`: 32 unique objects and 35 mapped sections.
- `libultra_2_0L_d`: three unique audio objects and four mapped sections.

The 2.0L survey covers 6,592 text bytes; see
[`evidence/libultra_us_2_0L_object_bounds.md`](evidence/libultra_us_2_0L_object_bounds.md).
The 2.0I survey covers `0x2DF0` (11,760) text bytes and 49 functions; see
[`evidence/libultra_us_2_0I_additional_object_bounds.md`](evidence/libultra_us_2_0I_additional_object_bounds.md).
The exhaustive I-L ROM/debug survey adds 272 standard audio text bytes; see
[`evidence/libultra_us_audio_object_bounds.md`](evidence/libultra_us_audio_object_bounds.md).
Those ranges are archive-owned and therefore no longer appear as generic
`src/libultra` source units or function work items.

`lib/libultrare` started with a bounded snapshot of eleven Rare-modified objects
from n64decomp/007 revision `c4356466796c697dfd298010b9bed261f9ed8c6a`
plus two Conker-specific VI objects and five initialized-data reconstruction
objects. Every complete object MD5 is checked before the archive is staged.
That initial snapshot contributes 26 mapped sections, covers `0x2230` (8,752) text
bytes, and owns 23 member functions. See
[`evidence/libultrare_us_additional_object_bounds.md`](evidence/libultrare_us_additional_object_bounds.md).
The VI-family and complete RSP blob/overlay boundaries are detailed in
[`evidence/libultra_us_vi_rsp_boundaries.md`](evidence/libultra_us_vi_rsp_boundaries.md).
The five standard initialized-data ranges are detailed in
[`evidence/libultra_us_data_object_bounds.md`](evidence/libultra_us_data_object_bounds.md).
These eighteen build objects likewise no longer have generic
`src/libultrare` work items.

The main profile additionally links 24 reconstructed Conker N-audio objects:
6,736 text bytes and 34 functions, plus two complete initialized/constant
sections. See
[`evidence/libultrare_us_naudio_variants.md`](evidence/libultrare_us_naudio_variants.md).
The source uses reviewed Conker layouts and behavior rather than presenting
near-matching Rare or Nintendo objects as exact stock output. Reconstructed
objects compiled with debug scheduling flags strip only non-runtime `.mdebug`
host/time metadata to make their full object checksums reproducible.

The active US main profile now links 144 unique library objects through
185 mapped sections: 140 CPU objects and four RSP payload members. The independently
generated US comparison map in `config/reference/us.yaml` remains raw assembly.
The complete rebuilt US ROM is byte-identical. EU/PAL mapping remains future
work.

The continued library-only pass adds eleven complete reconstructed objects:
11,552 text bytes, 34 functions, and five complete rodata sections. This
promotes the formerly raw `syncprintf`, synthesizer, and driver units, and
also reconstructs the main mixer, channel/effect controls, auxiliary mixer,
resampler, and per-voice filter. The shared audio views reproduce Conker's
expanded physical voices and linked auxiliary lists. See
[`evidence/libultrare_us_continued_reconstruction.md`](evidence/libultrare_us_continued_reconstruction.md)
for all object hashes, exact intervals, section ownership, and remaining leads.

A further five audio objects add 16,656 text bytes and 24 functions: decoder,
reverb, envelope, surround configuration, and compact-sequence parsing. Their
complete data, rodata, and BSS ownership is recorded in
[`evidence/libultrare_us_audio_engine_reconstruction.md`](evidence/libultrare_us_audio_engine_reconstruction.md).
The reverb and envelope jump tables use checked runtime-address relocation
preparation before the whole objects enter the main archive.

The following pass adds the seventeen sequence-player helpers and the
heap, bank-relocation, and oscillator families: four complete objects,
31 functions and 8,320 text bytes. The oscillator constants and 16-byte BSS
allocation are also mapped. See
[`evidence/libultrare_us_sequence_helper_reconstruction.md`](evidence/libultrare_us_sequence_helper_reconstruction.md).

The complete floating-point formatting unit `xldtob` now links from
`lib/libultrare`: three functions, 2,848 text bytes and 96 rodata bytes.
All three functions have zero-difference evidence, and the complete US ROM
remains byte-identical. The supported retirement command preserves the complete
C source in the archive tree and removes its duplicate source work items. See
[formatting evidence](evidence/libultrare_us_formatting_boundaries.md).
The MP3 bit/Huffman utilities are also reconstructed and linked. The preserved
power candidate and external workspace ownership remain unresolved library
work; ordinary game-code implementation is outside this goal.

The residual I-L archive scan finds no distinctive complete loadable libultra
section in a raw US main range. The only residual exact-boundary result is an
indistinguishable 16-byte no-op/padding sequence at `0x39B0`, which has neither
a call site nor a ROM pointer reference. The audit method, source surveys, and
scope conclusion are recorded in
[`evidence/libultra_us_residual_boundary_audit.md`](evidence/libultra_us_residual_boundary_audit.md).

## US game-overlay libraries

The game map links 15 complete stock 2.0I objects (9,024 text bytes) and 20
Rare/Conker objects (38,768 text bytes). All 35 text mappings retain their raw
comparison counterparts. Complete game data/rodata/BSS bindings are recorded
in `config/game/us-sdk.ld`, including separate engine and tail helper targets.
The complete code payload remains byte-identical, and existing compressed
game-data allocations are preserved.

The boundary evidence is collected in:

- [`game_sdk_tail_text_bounds.md`](evidence/game_sdk_tail_text_bounds.md)
- [`game_sdk_additional_objects.md`](evidence/game_sdk_additional_objects.md)
- [`game_sdk_controller_objects.md`](evidence/game_sdk_controller_objects.md)
- [`game_sdk_mtxutil_variant.md`](evidence/game_sdk_mtxutil_variant.md)
- [`game_sdk_rotation_variant.md`](evidence/game_sdk_rotation_variant.md)
- [`game_sdk_trig_perspective_variants.md`](evidence/game_sdk_trig_perspective_variants.md)
- [`game_sdk_si_access_variant.md`](evidence/game_sdk_si_access_variant.md)

The main and game maps together account for 146,304 exact CPU library text bytes.
This counts each placement once; it is separate from registered handwritten C
function progress and from unverified source-boundary hypotheses.

The continued library-only search adds the audio engine and players, MP3 stream
and decoder, playback wrapper, exponential/logarithm helpers, and independently sourced MP3
assembly transforms and bit/Huffman utilities, plus both complete formatters.
Its 34 reviewed reconstruction objects contain 175 functions and 95,680 text bytes. This is a subset of the totals above, not an additional
amount. Detailed evidence is in the corresponding `libultrare_us_*` notes,
including [MP3 decoder](evidence/libultrare_us_mp3_decoder_reconstruction.md),
[math helpers](evidence/libultrare_us_math_helpers.md), and
[MP3 transforms](evidence/libultrare_us_mp3_transforms.md), and
[MP3 playback](evidence/libultrare_us_mp3_playback_reconstruction.md), and
[main formatter](evidence/libultrare_us_xprintf_reconstruction.md).

The separately assembled RSP boot and audio library adds 6,656 RSP code bytes
and 2,896 initialized data bytes. These stay outside CPU matching and the
historical code-coverage figures above. All four payloads and the complete US
ROM compare exactly; see [RSP evidence](evidence/libultra_us_vi_rsp_boundaries.md).

The MP3 utility now links as a complete Rare assembly member, adding five
functions and 1,152 text bytes after the approved table-access changes; see
[its object comparison](evidence/libultrare_us_mp3_util_boundaries.md).
Remaining library work includes the preserved non-exact power candidate under
`src/libultrare/gu/powf.c` and unresolved external workspace ownership.
The unchanged-template follow-up before MP3 utility integration scanned 6,018 stock/Rare object instances
against both CPU images and the separately compressed game-data image. It finds
no new distinctive text match. Further review rejects one of the three unique
scalar hits as a game callback-table tail; the other two still lack ownership
evidence. The [workspace review](evidence/libultrare_us_workspace_bounds.md)
bounds the MP3 stream and table views but leaves original BSS ownership open.
Four more compiler-mode trials did not improve the power candidate. See the
[residual audit](evidence/libultra_us_residual_boundary_audit.md) for corpus limits
and the subsequently approved MP3 integration. Ordinary game-code implementation is
outside this goal's current scope.

## Contributor commands

Build complete pinned stock archives for SDK-version research with:

```sh
./conker libultra
./conker libultra --version I
./conker libultra --version J
./conker libultra --version K
```

Build the bounded Rare snapshot and verify every object checksum with:

```sh
./conker libultrare
```

Assemble and verify every RSP library payload with:

```sh
./conker rsp
```

After building the I-L `libultra`, `libultra_d`, and `libultra_rom` research
targets, repeat the residual US main scan with:

```sh
./conker library-audit
```

Regenerate the raw target and validate the actual library integration with:

```sh
./conker _prepare-reference --profile us
./conker build --profile us
```

A candidate should move into a library archive only after its complete object
boundary, section ownership, symbols, and relocations are reviewed. Keep the
same range as raw assembly in `config/reference/us.yaml`; a relocation-masked
object resemblance is not a substitute for a byte-identical US rebuild.
