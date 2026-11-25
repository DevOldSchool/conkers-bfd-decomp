# US save-field width table

Bank 07 contains an eight-byte directory, a **69-byte save-field width table**,
and three trailing bytes. The directory is already reconstructed separately.
This extension regenerates only the 69 width bytes; it leaves the final three
bytes outside matching credit.

## Independent native consumers

`func_15006590` loads raw bank 07 at `0x15006604`, advances the returned bank
pointer by eight bytes and stores it in `D_800BE3F0`. Its loop at
`0x1500688C:0x15006968` reads one unsigned byte for each of 69 destination
64-bit fields. It constructs a high-bit mask using width minus one, walks that
many save-stream bits, and advances the destination by eight bytes. Zero-width
fields skip the bit loop. The outer limit is `0x45` at `0x15006958`.

`func_15006BEC` writes the reciprocal stream. Its loop at
`0x15006E88:0x15006F6C` reads the same byte-width table, shifts through each
64-bit field and emits exactly that many bits. Its outer limit is also `0x45`,
at `0x15006F60`. These are actual storage widths, not inferred image dimensions,
guessed padding or an opaque byte-array reconstruction.

Both complete original US function spans are authenticated before reconstruction:

| Function | Bytes | Original SHA-1 |
| --- | ---: | --- |
| `0x15006590` | 1,628 | `324013365c23946b311c63491cf8df35864a68b9` |
| `0x15006BEC` | 1,168 | `8a66e901d3c6cab285c357fd08ad121dbe6ca7b1` |

The independent directory identifies a raw entry at relative offset 8, with
stored size 69 and flag nibble 8. Its bank occupies ROM
`18891696:18891776`; generated widths occupy `18891704:18891773`.
Current widths range from zero to 40 and describe 546 saved bits in total.
The codec accepts exactly 69 integer widths from zero through 64.

## Build and reporting

`./conker asset-directories build` creates a separate `save-layout/manifest.json`
and editable `save-layout/widths.json` beneath the existing
`build/assets/asset-directories/us/bank07/` directory. The previous directory
manifest, table and backing remain unchanged. Existing inputs are validated
before the new source is initialized; malformed or missing source files are
preserved and rejected. The existing explicit `recover --part bank07` command
backs up the complete directory, including the save-width source.

The bank-07 linker object combines the freshly encoded directory and width
table with the three retained trailing bytes. Make tracks both new source
files, their deletion and the codec dependencies. All source hashes are checked
again before publishing output. The complete object must remain identical to
the checksum-validated US ROM.

Native objdiff receives the generated widths as a separate 69-byte unit. Its
physical range is disjoint from the directory's eight bytes. The remaining
three bytes stay in unreconstructed storage. Report preparation checks the
actual linked object's complete bytes against semantic sources and backing,
then compares the credited slice independently with ROM.

Focused tests cover all 69 field mutations, invalid widths/counts, preservation
of existing directory sources, missing/corrupt save sources, recovery backups,
concurrent changes, exact native ranges, modified linker objects and Make
rebuilds after edits/deletion. Whole-project acceptance is recorded after the
full tests, asset build and native report have passed.
