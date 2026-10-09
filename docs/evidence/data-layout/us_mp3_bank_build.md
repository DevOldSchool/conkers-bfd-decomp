# US MP3 bank build input

Verified on 2026-10-08 against US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

Bank `0x16` occupies ROM `[0x1330478, 0x29AE9E8)`. Its index and stream
boundaries come from the existing indexed-bank parser and loader-proven MP3
family described in [the asset documentation](../../rzip-assets.md#loader-proven-us-mp3-streams-and-tables).
The bank has a complete, nonoverlapping storage partition:

| Component | Count | Stored bytes |
| --- | ---: | ---: |
| Index records | 462 | 3,696 |
| Encoded MP3 streams | 453 | 23,581,009 |
| Zero-filled alignment padding | 368 | 1,455 |
| Complete bank | 1 | 23,586,160 |

The nine empty slots are 81, 109, 120, 157, 159, 207, 304, 394 and 396.
The last stream, 461, preserves index size/flags word `0x80004BB8`, including
its terminal flag. All 368 padding ranges contain only zero bytes, are 1–7
bytes long, and end at the next 8-byte boundary. All 453 streams begin at an
8-byte boundary. The packer verifies the zero-fill and alignment rule before
classifying these bytes as padding. The final stream ends at the bank end;
there is no trailing padding in this bank.

## Build and edit workflow

```sh
./conker mp3-assets build-bank --input build/assets/mp3-bank/us --output build/us/audio/asset_bank_16.bin
./conker build --all
```

`scripts/mp3_bank.py` initializes an absent input directory from the
checksum-validated ROM. The bundle contains `manifest.json`, 453
`streams/<index>.mp3` files, and 368 `padding/<offset>.bin` files. All 822 inputs
are hashed. Existing inputs are never refreshed automatically, and a partial
directory without its manifest is refused rather than overwritten.

The manifest records provenance, every original index word, exact stream
coordinates, original stream hashes, and padding hashes. Packing regenerates the
index from these records and assembles the complete bank. The manifest must
agree with the reviewed ROM layout. Streams can be edited while retaining
their exact byte lengths and valid MPEG/cue framing. Original stream digests
remain provenance; they do not prevent a changed candidate from being compared.
Alignment padding must remain unchanged. This fixed layout does not yet support
resizing streams or relocating later entries. Structural parsing does not
establish audible fidelity.

The checked-in `config/profiles/us.yaml` defines bank `0x16` as a byte-aligned
group with 822 explicit subsegments: its index, every nonempty MP3 stream and
every padding range. Splat extracts each range separately and generates linker
entries for `build/us/assets/audio/mp3/index.o`, `streams/<index>.o` and
`padding/<offset>.o`. These individual objects are the ROM link inputs.

The Makefile obtains their names directly from the YAML. Its dedicated rule
repacks once per build, verifies every YAML boundary against the checked ROM
manifest, and wraps each rebuilt part separately. Raw splat outputs remain
independent references. Missing files, invalid framing, changed metadata/padding
or changed inputs during packing fail the build. The existing `mp3-assets pack`
workflow retains its stricter original-stream checks.

## Validation and report scope

The complete 67,108,864-byte US ROM passed byte-for-byte validation with these
822 individual linker inputs. The later sequence-padding rename also passed
the full ROM check; see `build/us/data-boundaries/report-review-build.log`.
The packer tests cover index flags, empty slots, fixed ranges, preserved edits,
invalid/missing inputs, input changes during packing, and source protection.

MP3 storage is currently outside the published report denominator and progress.
The bank remains split and verified in `us.yaml` and the ROM build. Generated
bundles remain ignored. See [the published report scope](../../objdiff.md#scope).
