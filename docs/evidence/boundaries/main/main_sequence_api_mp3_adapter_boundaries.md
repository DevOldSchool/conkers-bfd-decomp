# US main sequence API and MP3 adapter working units

Evidence kind: `structural_analysis`. Two offset-named working source units
cover 34 complete indexed entries and 4,304 bytes. They remain raw assembly
in the canonical build. No original filenames, matching C, original static
storage ownership or new exact library object are claimed.

## Inputs and complete spans

The checksum-validated ROM, split raw assembly and independently generated
unsplit spimdisasm 1.33.0 IDO index agree on every member and complete span.
All raw words match the ROM and no whole-main conditional branch crosses
these existing aligned endpoints. The
[legacy map](https://github.com/mkst/conker/blob/3adf229175c037c771f251f169f9dd80ca306924/conker/conker.us.yaml)
corroborates the outer grouping. The concrete producer/consumer relationships
below establish working membership separately from that old map.

| Source | US ROM range | Entries | Bytes | Range SHA-1 |
| --- | --- | ---: | ---: | --- |
| `src/main/init_8180.c` | `0x8180:0x8F90` | 27 | 3,600 | `54642d097818a0902de51931a4a4f1df107a3f64` |
| `src/main/init_12560.c` | `0x12560:0x12820` | 7 | 704 | `8a9afaba6a1db81609680ce5ec26abbbf9287060` |

## Sequence-player API, `0x8180:0x8F90`

The initializer creates and wires the bank, sequence descriptors and players.
Its independently documented bank/descriptor relationship is recorded in
[non-MP3 audio assets](../../assets/audio/us_non_mp3_audio_assets.md). Most members are wrappers
on exactly the same indexed player array at `0x8003C900`: start/state, event
queue, channel parameters, tempo, volume, bank/sequence selection and stop.
The local wrapper chains are `0x8790 -> 0x8660`, `0x886C -> 0x8824`, and
`0x88F0 -> 0x85F8/0x862C`. The sequence-data operations at `0x8C04/0x8C6C`
use descriptor state at `0x8003CA58/0x8003CD48`, which the loading member
`0x8CE8` connects back to the same players and bank state.

The complete `0x85A4:0x85B8` no-op entry requires an explicit limit on the
claim. It stores three arguments and returns, so its body alone cannot prove
original ownership. Its game caller is the sequence-system initialization
routine at overlay `0x0:0x90`: that caller builds three message queues, invokes
this family's queue setter `0x8570` for each at offset `0x44`, then calls
`0x85A4` at `0x64` before resetting the sequence controller. Those game words
were independently checked against the owned decompressed overlay. This
specific API-initialization context, exact independent entry span, and complete
legacy grouping support inclusion in this working sequence family. They do
not identify a historical function name or a stock SDK implementation.

The `0x8B2C` tempo getter likewise has no direct caller in the bounded scan,
but its body explicitly selects from the same `0x8003C900` player array and
calls the independently mapped tempo getter at `0x17EC0`. It is therefore
accounted for by positive state/operation evidence, not by a negative call scan.

Complete member starts (prefix `func_800`):
- `08180`, `084D8`, `0853C`, `08570`, `085A4`
- `085B8`, `085F8`, `0862C`, `08660`, `086FC`
- `08744`, `08790`, `08824`, `0886C`, `088F0`
- `08988`, `08A4C`, `08A94`, `08B2C`, `08B60`
- `08BC0`, `08C04`, `08C6C`, `08CE8`, `08EE0`
- `08F24`, `08F58`

## MP3 stream and playback adapter, `0x12560:0x12820`

All seven entries wrap the same reconstructed MP3 playback interface and its
text/callback transport:

- `0x12588` initializes the transport at `0x800427A0/0x800427B0` and installs
  `0x10012560` using the matched `mp3_set_text_callback` at game `0x1F3C1C`.
  Callback `0x12560` and public helper `0x126E8` both operate on that exact
  transport object.
- `0x125CC` checks playback state and uses the matched stop/volume routines.
- `0x1263C` resolves a playback resource, sets volume/pan/options and starts
  the matched MP3 player. It is also an independently reviewed dependency of
  the exact Rare channel-controller object; see
  [channel controls](../../libraries/libultrare_us_channel_controls_reconstruction.md).
- `0x12718` computes the spatial parameters and calls `0x1263C` at
  `0x12758` or `0x127B4`, using the same sound-record spatial helper as the
  reviewed main sound-record family.
- `0x127D0` queries the matched `mp3_is_busy` routine and reports selected
  states.

The relevant matched library entries and identities are documented in
[MP3 playback reconstruction](../../libraries/libultrare_us_mp3_playback_reconstruction.md).
This uses specific independently reconstructed APIs, not generic calls to
shared allocation or math helpers. The complete following `heap.o` begins at
`0x12820`, anchoring the final endpoint. The preceding shared-state controller
ends at `0x12560` and is kept separate.

Complete member starts (prefix `func_800`):
- `12560`, `12588`, `125CC`, `1263C`, `126E8`
- `12718`, `127D0`

## Registration and verification

Replay each table row through `./conker register-source-unit --overlay main
--register-members`, its listed source and bounds, `--evidence-kind
structural_analysis`, and this evidence reference. Preserve concurrent work
by replaying transactions rather than replacing inventory files.

Both units remain `raw_asm`; neither canonical nor reference map changes.
All 75 project-state and 13 segment-map tests pass, generated progress is
current, and whitespace checks pass. No full-main build or mixed integration
is claimed; the cloud CPU image still lacks the RSP extension, and main mixed
integration is unsupported.
