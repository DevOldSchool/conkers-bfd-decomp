# US bank-17 audio storage boundaries

Verified on 2026-10-08 against US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The original boundary pass defined bank `0x17` as a byte-aligned group with
272 explicit subsegments in `config/profiles/us.yaml`. The later
[sound-bank reconstruction](us_sound_bank_reconstruction.md) expands this to
322 splits by separating typed external records from unexplained spans. The
[ADPCM reconstruction](us_adpcm_reconstruction.md) expands the sample entry into
5,104 complete-frame and raw regions, for 5,425 splits overall. The group covers ROM `[0x29AE9E8, 0x3F82170)`:
22,886,280 stored bytes. These are actual splat extraction boundaries and
individual linker inputs under `build/us/assets/audio/bank17/`.

| Range | Stored bytes | Boundary evidence |
| --- | ---: | --- |
| Seven-entry bank index | 56 | First bank-relative offset and seven records |
| Sound-bank control, RZIP | 4,885 | Entry 0 stored extent; decodes to 7,768 bytes |
| Entry alignment padding | 3 | Zero-filled to the next 8-byte boundary |
| External sound-bank data | 430,608 | Entry 1, runtime bank patcher |
| ADPCM wavetable/sample storage | 21,705,520 | Entry 2, runtime wavetable relocation |
| Sequence descriptor table | 1,196 | S1 header and 149 offset/length descriptors |
| 149 individual compact sequences | 684,228 | Each descriptor's exact offset and length |
| 114 sequence padding ranges | 232 | Bytes between descriptor-defined extents |
| MP3 Huffman offsets | 144 | Entry 4, decoder initialization |
| MP3 lookup tables | 17,408 | Entry 5, decoder initialization |
| MP3 Huffman data | 42,000 | Entry 6, decoder initialization |
| Total | 22,886,280 | Complete contiguous partition |

The roles are established by the existing [audio runtime evidence](../assets/audio/us_non_mp3_audio_assets.md)
and [MP3 decoder contracts](../../rzip-assets.md#loader-proven-us-mp3-streams-and-tables).
This change uses those parsers; it does not infer roles from neighboring data.

Sequence offsets are four-byte aligned. All 114 following spans are exactly
the 1–3 bytes needed to reach the next four-byte boundary. They are named
`audio/bank17/sequences/padding/`; 88 contain nonzero bytes, which are preserved
verbatim. Padding is classified by the alignment rule, not by requiring zero
contents. The bank also has three bytes of zero-filled entry alignment padding. The index includes each sequence's
actual payload length, excluding its following padding.

`scripts/audio_boundaries.py` compares every checked-in YAML boundary and name
against checksum-validated bank records, loader-proven entry contracts and
sequence descriptors. It also reconstructs the complete sequence container
from its descriptors, payloads and padding as a boundary check. The Makefile
obtains input names from the YAML and requires this verifier before linking.

At the boundary-mapping stage these inputs remained raw extracted ROM storage. The compressed control graph is
kept as its stored RZIP range; the 21,705,520-byte wavetable remains one range.
Its 2,258 known sample ranges are a later subdivision. This step does not add
an ADPCM encoder, MIDI import or independently rebuilt sound-bank graph.

At that stage all 22,886,280 bank-17 storage bytes were included in the published
report denominator as unmatched targets. The later [sequence reconstruction](us_sequence_reconstruction.md)
replaces 149 payload candidates (684,228 bytes) with native event reconstruction. Named boundaries
and copied ROM inputs alone do not establish reconstruction credit.

Validation:

- `./conker build --all`: complete 67,108,864-byte ROM byte-identical; log at
  `build/us/data-boundaries/bank17-build.log`.
- Boundary tests cover exact partitions, nonzero sequence padding, index
  disagreement, false padding and YAML drift.

See [the published report scope](../../objdiff.md#scope).


The later [B1 reconstruction](us_sound_bank_reconstruction.md) supplies fresh
candidates for the 4,885-byte control and 429,952 external bytes. The other 656
external bytes remain raw. This preserves the complete bank extent and its
original entry order.

The PCM16 encoder supplies 2,690 complete-frame candidates totaling 21,691,971
sample bytes. Ambiguous frames, incomplete tails and storage gaps occupy the
remaining 13,549 raw bytes. The native sample graph and explicit frame exclusions
derive this partition; only reconstructed complete frames receive Data credit.
