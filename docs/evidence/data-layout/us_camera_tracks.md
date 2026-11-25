# US camera state delta tracks

Bank 1B stores four compressed arrays of six big-endian `f32` values per frame.
The four streams occupy **5,293 bytes**. The separately reconstructed directory
occupies 32 bytes; 11 bytes between and after streams remain uncredited.

## Native evidence

`func_1512D238` loads all four bank-1B entries through `func_1502B5C8` at
`0x1512D284`. It stores decoded pointers in `D_800DC280` and divides each decoded
byte count by 24 to populate `D_800DC290`. This proves the record stride and
number of tracks independently of the compressed contents.

`func_1512C490` reads a track selector from camera state offset `0x850` and a
frame index from `0x84E`. At `0x1512C9F8:0x1512CA04` it computes frame times 24
and adds the decoded track pointer. The following instructions consume all six
record fields as floats:

| Record offsets | Instructions | Destination state offsets |
| --- | --- | --- |
| 0, 4, 8 | `0x1512CA38`, `0x1512CA48`, `0x1512CA58` | `0x860`, `0x864`, `0x868` |
| 12, 16, 20 | `0x1512CA08`, `0x1512CA18`, `0x1512CA28` | `0x854`, `0x858`, `0x85C` |

Each value is added to the corresponding camera state field. The source names
`delta_860_868` and `delta_854_85c` retain this proved mapping without assigning
unproved axis units. `func_1512D2F8` advances the byte-sized frame index and stops
playback at the decoded count. Camera rendering calls the state update.

The complete original US consumer spans are authenticated before input creation
or reconstruction:

| Function | Size | SHA-1 |
| --- | ---: | --- |
| `0x1512D238` | 172 | `c8377042a8ea9554438110cd544b3504e6e5f58d` |
| `0x1512C490` | 3,040 | `6e3de8106f6ac5997e9db8d4da9acde1a106f965` |
| `0x1512D2F8` | 112 | `2cae95492810b9f2236178b577ecc53922d77624` |

## Representation and compression

The bank starts at ROM `66623040`. Its directory proves these physical extents:

| Track | Relative offset | Stored bytes | Decoded bytes | Frames |
| --- | ---: | ---: | ---: | ---: |
| 0 | 32 | 1,351 | 2,640 | 110 |
| 1 | 1,384 | 1,530 | 3,120 | 130 |
| 2 | 2,920 | 1,783 | 3,120 | 130 |
| 3 | 4,704 | 629 | 3,120 | 130 |

All 3,000 floats are finite. Decimal JSON round-trips the actual single-precision
values exactly. The codec retains signed zero, rejects nonfinite or overflowing
values, and permits one through 256 frames per track, consistent with the native
byte index. The bank requires exactly four tracks. Fresh level-six raw DEFLATE
with a big-endian decoded-size prefix reproduces every original compressed byte.
No compressed byte array, token sequence or patch mask enters the encoder.

## Build and independent reporting

`./conker asset-directories build` adds `camera-tracks/manifest.json` and editable
`camera-tracks/tracks.json` beneath `build/assets/asset-directories/us/bank1B/`.
The original directory sources and backing are preserved. Existing invalid or
missing child sources fail without replacement. Explicit
`./conker asset-directories recover --part bank1B` backs up the entire parent,
including the camera sources, before restoring inputs.

The actual `asset_bank_1b.o` combines the freshly generated directory and four
freshly compressed streams with the excluded gap bytes. Make tracks edits,
missing inputs and encoder dependencies. Source hashes are rechecked before
publication. The complete candidate must match the independent checked US ROM.

The report freshly encodes the camera source, checks the whole actual linker
object and selects only the four exact stored spans. Directory credit remains
separate. No decoded allocation is counted again. Uncredited gap mutations still
fail the whole-object check even though gaps do not enter the native candidate.

Focused tests cover finite floats and signed zero, malformed compression, every
field in a synthetic four-track bank, source edits and deletion, recovery,
source races, exact physical ranges, Make scheduling and linker-object mutations.
Whole-project acceptance additionally requires the full test suite, asset ROM
build, native report, prior-source preservation, progress and whitespace checks.

## Accepted validation

The implementation passed validation on 2026-10-26 against base commit
`38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` with the local changes applied.
On 2026-10-29, the saved native report was confirmed current against both the
checkout and editable asset sources, and the existing built ROM was compared
again with the checksum-validated original. No implementation changes followed
the accepted build.

- All six focused camera tests passed. An independent ROM-backed audit changed
  each of the 3,000 float fields in memory; every mutation changed fresh output.
  Six mutations at the consumer-span endpoints were rejected.
- `./conker test` ran 2,919 tests successfully, with eight skips, in 225.570 seconds.
- `./conker build --assets` reproduced all 67,108,864 US ROM bytes in 259 seconds
  including setup and Docker. ROM SHA-1:
  `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
- Native objdiff added exactly 5,293 matched and fully linked Data bytes in one
  camera-track unit. Bank-1B unreconstructed storage fell from 5,304 to 11 bytes.
  Code, denominators and every other existing unit's measures were unchanged.
- All 26,432 previously recorded editable-source hashes were preserved; exactly
  two camera source files were added. Progress and whitespace checks passed.

Matched Data at this checkpoint is **63,086,022 / 65,120,512 (96.87581%)**;
fully linked Data is 63,065,078 bytes. The eleven gap bytes remain uncredited.
The [machine-readable acceptance record](us_camera_tracks.json) records the
input fingerprint, report digest, physical extents and validation results.
