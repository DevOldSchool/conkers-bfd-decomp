# Independently authored bounded DEFLATE encoder

`scripts/deflate_encoder.py` implements the reviewed compression profile in
Python, under the repository's MIT license. It replaces the locally vendored
GNU gzip-derived utility. It was authored from [RFC 1951](https://www.rfc-editor.org/rfc/rfc1951),
the recorded [EOF/block diagnostics](us_bounded_compression.md), and black-box
compression comparisons, without copying or translating the vendored C code.
The historical JSON evidence for the previous encoder remains historical.

The input is immutable decoded bytes. There are no original compressed bytes,
ROM offsets, asset identities, per-asset recipes, token streams or patch masks
in the encoder interface. `rzip_bounded.py` preserves the existing manifest
contract and adds the native big-endian length prefix. Independent zlib decoding
must consume the entire output and exactly reproduce the input.

## Compression profile

The implementation provides only the reviewed level-six profile:

- Three-byte, 15-bit hash chains and lazy LZ77 selection, using at most 128
  candidates (32 after an eight-byte match), a 16-byte lazy-search threshold,
  and a 128-byte early-stop length. Matches stop at EOF and at 258 bytes.
- The historical effective search distance is 32,506 bytes; three-byte matches
  farther than 4,096 bytes are discarded. Equally long matches keep the newer
  candidate. The initial history position is reserved, matching the measured
  parser behavior. Block boundaries do not reset the history.
- A block holds at most 16,383 tokens. At 4,096-token intervals, the distance
  histogram estimates the compressed size and may end a block early. The
  literal byte pending in the lazy parser belongs to the following block.
- Huffman trees rank by frequency and subtree height with deterministic heap
  ties. Literal/distance code lengths are limited to 15 bits and code-length
  codes to seven. Run-length descriptions restart at each alphabet.
- Fixed, dynamic and stored blocks use their rounded encoded sizes to select
  the representation. Fixed blocks win compression ties; stored blocks are
  available only while the corresponding source range is in the modeled window.

All state belongs to the invocation. There is no compiled executable, subprocess,
network access or compressor cache. Model, sprite and visibility Make stamps
explicitly depend on both Python modules, so encoder edits invalidate packing.
This replacement does not change the separate system GNU gzip dependency used
by other existing asset profiles.

## Compatibility and acceptance

Before removal of the vendored source, the independent encoder reproduced all
**48 affected ROM payloads**, accounting for **980,786 stored bytes**:

| Family | Payloads | Stored bytes |
| --- | ---: | ---: |
| Characters and scene bundles | 27 | 791,897 |
| Sprites | 5 | 36,940 |
| Visibility bitmaps | 16 | 151,949 |

It also reproduced the retained executable's complete output on **244 synthetic
cases**, covering small inputs, EOF, low/high entropy, copied substrings, token
buffer boundaries and sliding-window boundaries up to 250,000 decoded bytes.
Each result independently decompressed with zlib. Five additional deliberately
placed distant-match cases and three long synthetic golden vectors also agreed.
Those comparisons exercised the executable as a black box, not its source.

Permanent tests retain synthetic exact-output hashes for EOF, stored blocks,
dynamic blocks, heuristic block boundaries and long history. They also check
length-limited Huffman trees, independent decoding, malformed/truncated/trailing
output rejection, input validation, and Make dependency invalidation. No ROM
bytes or generated compressor outputs are committed as test fixtures.

The acceptance record in [JSON](us_independent_deflate.json) records full-ROM
and matching-report verification. The full reconstructed ROM must be proven
byte-identical with the independent implementation before the vendored files
are removed; the final build and native report then verify the removal itself.
