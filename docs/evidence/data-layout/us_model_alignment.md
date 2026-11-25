# US standalone model-bank alignment

This batch reconstructs 664 complete raw padding objects, totaling **2,671
bytes**, in banks `01`, `03`, `04` and `09`. These spans are selected from the
canonical US profile only when an entire `models/raw/` object is shorter than
eight bytes and ends at an eight-byte boundary. Selection alone earns no credit:
each object must also be exactly one gap derived from its native bank directory.

| Bank | Complete padding objects | Bytes |
| --- | ---: | ---: |
| 01 | 157 | 605 |
| 03 | 43 | 171 |
| 04 | 40 | 160 |
| 09 | 424 | 1,735 |

## Source and native evidence

The existing `build/assets/asset-directories/us/bankXX/` manifest,
`directory.json` and backing inputs are preserved. There are no new editable
files. The reviewed loader spans `1502AC88` (636 bytes) and `1502B5C8`
(244 bytes) authenticate native offset, stored-size and flag interpretation;
see [asset directories](us_asset_directory_reconstruction.md).

For each nonempty typed directory record, the generator advances from the
previous payload end by `(-absolute_cursor) % 8`. The next record must start
there, and the payload must fit inside the native bank. A final gap must end
at the bank boundary with the same minimum alignment. Empty records do not
advance the cursor. No source field supplies arbitrary fill bytes or lengths.
The independently checksum-validated ROM must contain exactly the freshly
generated zeros in every selected span. Larger or mixed raw objects remain
excluded even when some of their bytes satisfy this rule.

`scripts/model_alignment_build.py` writes these fresh parts into
`build/us/model-alignment/parts/models/raw/`. Make builds the canonical linker
objects from those outputs in asset mode, after preparing the existing typed
directories. The original-asset build path is unchanged. A changed source,
missing input, nonminimal gap, nonzero reference or input race fails rather
than replacing editable files. Recovery uses the existing
`./conker asset-directories recover --part bankXX` path.

The report reads each actual whole linker object, checks it against the source
generator, and compares it with an independently created ROM reference object.
Only these 664 disjoint spans gain credit. Native objdiff matches all 2,671
bytes, and a one-bit mutation at each byte position loses its exact match.

## Validation

Accepted at base `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, with modified
inputs. The 102 focused and Make integration tests passed; `./conker test`
passed 2,978 tests (8 skipped). `./conker build --assets` reproduced the full
67,108,864-byte US ROM, SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
Progress and whitespace checks passed.

The final native report adds exactly **2,671 matched and complete bytes**:
**63,202,976 / 65,120,512 (97.0554%)** matched, with 1,917,536 remaining.
Complete data is 63,156,848 bytes. Bank `01`'s final 605-byte unmatched remainder
is exhausted and its empty remainder unit disappears. Banks `03`, `04` and
`09` lose exactly 171, 160 and 1,735 unmatched bytes respectively. All other
existing unit measures and the code/function totals are unchanged.

All 27,251 existing editable source hashes are preserved, with no new editable
files. All prior asset-object hashes are preserved. Four rebuilt CPU object
containers and the rebuilt ELF change hashes; old raw containers were not
retained, so no exact metadata-section cause is claimed. Fresh verification
confirms all three overlays' full linked code/data images are unchanged. An
independent `objcopy -O binary` extraction of the current ELF also reproduces
the original ROM exactly.

These checks establish this batch only; the
remaining untyped asset storage remains unmatched.
