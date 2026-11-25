# US bank-04 model 58: duplicated primary normal storage

Model 58 contains 8,703 compressed bytes at `0x10F8138..0x10FA337`.
Its existing raw object, `models/raw/010F8131`, also contains seven leading
and one trailing minimum alignment bytes. The reconstructed object therefore
owns 8,711 bytes without changing the profile or splitting an existing object.

## Independent format evidence

The 32,208-byte decoded bundle has ten descriptors, eight nonempty model
segments and two empty slots. Existing codecs already describe the primary
model and every other nonempty child except slot one. That child's display
list ends at decoded offset 2,904, but its five normal commands select offsets
4,696, 4,760, 4,824, 4,888 and 4,952. The old codec correctly rejected the
unexplained intervening 1,792 bytes.

Those bytes are exactly the primary model's 28 normal tables, stored a second
time. The primary header independently declares its 1,792-byte region at
17,072, and all 28 tables have normal-command references. Independent reads
compare every signed XY pair in both copies. The child then has five of its
own complete referenced tables. Its other auxiliary header fields are empty;
there is no unexplained gap or suffix after representing this duplication.

The new source records the duplication as a reference to the primary model's
complete typed normal-table sequence. Changing a primary pair regenerates both
physical copies; changing a child's own pair changes only that field. This is
a proven relationship between stored bytes, not a claim that the game aliases
their runtime pointers or that the original exporter used a particular algorithm.

Across the entire bundle, independent checks cover 1,167 vertices, 800 display
commands, 42 normal tables and 560 primary face words. Existing codecs retain
their original roles and formats for ordinary children. The new format rejects
changed duplication references, mismatched copies, malformed descriptors,
incomplete or unreferenced child normal tables and unsupported header regions.
Fresh bounded DEFLATE reproduces the complete original compressed stream;
no compressed token stream or opaque payload is used as source.

The full original native loader/surface spans `150031EC` (712 bytes),
`150039BC` (36) and `150450CC` (576), plus normal scanner/relocation spans
`1503D368` (208) and `1503D438` (36), are independently authenticated against
the checksum-validated US ROM. All ten endpoint mutations fail authentication.
The existing bank-04 directory establishes the entry and both minimal gaps;
its inputs and full directory-loader proofs remain unchanged.

A bounded sibling check of the other unresolved bank-04 models (5, 8, 32, 34,
37) finds no referenced sibling normal tables to explain their secondary
regions. They remain excluded. This extension does not relax the old codec's
requirement for positively identified normal storage.

## Source, build and report

`./conker duplicate-models build` publishes `manifest.json` and editable
`model.json` under `build/assets/duplicate-models/us/58/`. It shares the existing
`build/assets/asset-directories/us/bank04/` inputs. There is no new backing blob:
the entire object is generated from typed model fields and index-derived gaps.

The builder validates decoded and stored hashes, full object extent and hash,
all shared index inputs, and source hashes before publication. Make tracks
both source files and all shared inputs, including deletions. Changed or missing
inputs fail without replacement; `./conker duplicate-models recover` backs up
the model's source directory before explicit recovery. The native report uses
the actual linker object and an independent original-ROM target.

## Validation

Accepted on base `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`
plus uncommitted changes. Fifty focused codec, builder, report and Make tests
pass. The independent field audit checks all 3,248 normal-component and
face-word mutations, including both destinations of every duplicated primary
component. All ten native consumer endpoint mutations are rejected. Every one
of the 8,711 individual byte mutations rejects a perfect native match.

- Full Docker suite: 3,028 tests pass, eight skipped (281.902 seconds).
- `./conker build --assets`: the complete 67,108,864-byte US ROM is
  byte-identical, 192 seconds including setup, 163.016 seconds compile/link/verify.
  Independent extraction from the current linked ELF also matches the ROM.
- Full native report: zero compile errors, 472.2 seconds preparation and
  33.9 seconds report/validation. Progress and whitespace checks pass.
- All 27,293 prior editable source hashes and 11,835 prior asset-object hashes
  are preserved. Two new source files and one newly verified linker object are
  added. Code, function measures and all existing linked runtime code/data are
  unchanged. The report snapshot is current.

Matched data increases by **8,711 bytes** to **63,290,103 / 65,120,512
(97.189197%)**; complete data increases to 63,243,975. **1,830,409 bytes
remain unmatched.** The only changed prior unit is the bank-04 remainder,
reduced from 20,169 to 11,458 bytes. The previous 20,132-byte payload-only
estimate excluded 37 alignment bytes and was not the full report remainder.

Report SHA-256:
`6776bd873e33c43b868d3588d3f8b631c21e50f14a0f4174ad9cb4bd46d20883`.
Input fingerprint:
`7dd20bd98ea047ae88b144e3ac64d80b00f7e6030667f966a946665920dd6420`.
