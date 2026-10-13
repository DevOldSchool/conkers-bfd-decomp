# Independently authored bounded DEFLATE encoder

`scripts/deflate_encoder.py` implements the reviewed compression profile in
Python, under the repository's MIT license. It replaces the locally vendored
GNU gzip-derived utility. It was authored from [RFC 1951](https://www.rfc-editor.org/rfc/rfc1951),
the recorded [EOF/block diagnostics](us_bounded_compression.md), and black-box
compression comparisons, without copying or translating the vendored C code.
The historical JSON evidence for the previous encoder remains historical.
RFC 1951 specifies the format; the tuning and tie-breaking behavior are
compatibility choices from the recorded diagnostics. Output comparisons verify
compatibility, not the authorship of an implementation.

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
  histogram estimates the compressed size and may end a block early. Its input
  extent is measured before consuming the checkpoint token, while the emitted
  block includes the complete token. The literal byte pending in the lazy parser
  belongs to the following block.
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

## Match checkpoint regression

A subsequent review found a counterexample to the early-block heuristic: when
its checkpoint token was a match, the estimate used the input position after
consuming that match. The compatibility profile requires the position before
consuming it. The fix preserves that position for the estimate without changing
the actual emitted block boundary.

`test_match_at_early_block_checkpoint` generates the reported seed-215 input:
a 600-byte random prefix followed by random gaps and 258-byte copies into that
prefix, stopping once the input reaches 30,000 bytes. The resulting 30,232-byte
input has SHA-256 `e6e6e7cd9960dcf5df430448886befcdd289d5901d0b1db5ebc4377713e6a303`.
The previous Python implementation produced 14,410 compressed bytes. The fixed
implementation and retained reference executable both produce the same 14,343
bytes, SHA-256 `a914382a565ab3c562059709b2c27f9bdf14d1e94ad93b4ff7e1b89785d45b75`.
The test also independently decodes the output with zlib. Running it against the
previous Python implementation fails, confirming that it detects this bug.

The [follow-up acceptance record](us_deflate_block_checkpoint.json) records the
full-ROM and matching checks after this fix and integration of current `main`.
The original replacement's before/after-removal evidence above remains unchanged.
