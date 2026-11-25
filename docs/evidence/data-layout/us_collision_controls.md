# US collision-control subset

Bank `0F` entries 12, 27, 46, 51, 62, 69, 77, 84, 102, 107, 120, 126,
127, 158, 166 and 172 reconstruct **6,056 stored bytes**. They contain 42
collision-response records, alongside the previously established animation
routes, events, actions and behavior programs. This is a restricted subset of
the 49 collision-bearing entries (59,622 stored bytes), not their completion.

## Native evidence

The existing loader `func_1503D660` relocates the header's collision pointer at
offset 4. `func_1505C1A4` obtains that pointer through `D_800D1588`, whose stored
route-table base is 16 bytes past the header. `func_1505C7D8` selects a record
using `(actor[0xD0] - 1) * 40`; `func_1505B9C4` independently multiplies its
record index by 40. Both consumers read the following fields directly.

| Offset | Storage | Native use |
|---|---|---|
| 0 | u8 | Response selector, with high-bit handling at `1505B9F0..1505BA1C` |
| 4 | u32 | Sound value at `1505BE5C`, passed through `D_800D1580` |
| 8 | u8 | Callback selector at `1505BD70` |
| 9 | u8 | Angle shifted by eight at `1505C904..1505C914` |
| 10 | u8 | Distance converted to float at `1505C8D8..1505C938` |
| 12 | s16 | Height contribution at `1505C9C8..1505C9F4` |
| 14 | u8 storage | Extent; unsigned and signed interpretations at `1505C97C` and `1505CB44` |
| 15 | u8 | Damage/response flags at `1505BACC..1505BB58` |
| 16 | u8 | Response angle contribution at `1505BA5C..1505BA6C` |
| 20, 24, 28 | f32 | Values copied to actor offsets `0x3C`, `0x20`, `0x24` at `1505BB10..1505BB30` |
| 32 | u8 | Copied to actor offset `0x109` at `1505BAFC..1505BB04` |
| 34 | u8 | High bit enables a low-six-bit value written to actor `0x125` at `1505C118..1505C128` |
| 36 | u16 | Flags read by both consumers, beginning at `1505BA24` and `1505C8B0` |

The codec emits zero for the inter-field lanes at 1..3, 11, 17..19, 35 and
38..39, consistent with these widths and the native stride. **Byte 33 remains
unresolved.** The supported format constrains it to zero and rejects any
nonzero value; it is neither called padding nor exposed as an editable opaque
field. Entries 0 and 128 contain the two nonzero instances (value 14) and remain
excluded. This subset does not establish the meaning or reachability of that
byte in those entries.

Collision arrays follow the action table (or events/routes when no actions
exist), and end at the first behavior-program pointer. The decoder requires
exactly contiguous sections and a multiple-of-40 collision extent. The encoder
derives all offsets from the typed lists. It preserves the native float bits,
including signed zero, and rejects nonfinite values and out-of-range integers.
Fresh level-six raw DEFLATE plus the decoded-length prefix reproduces every
selected original stream.

Three additional complete consumer spans are guarded by SHA-1:

| Start | Size | SHA-1 |
|---|---:|---|
| `1505B9C4` | 1,916 | `2f1e6ec26658042e24f9235e4fe108b9d32eda77` |
| `1505C1A4` | 64 | `2917af6483e72651d562e20f057fbf0aeb1d2364` |
| `1505C7D8` | 2,124 | `0fd78a95b2be0c345f10fabeceea6a50773c90e3` |

## Source and reporting contract

`./conker animation-control build` creates a separate `collision-controls/`
child under `build/assets/animation-control/us/bank0F/`, containing a checked
manifest and editable typed controls. It preserves the original three source
files and their existing 82 reconstructed entries. Existing malformed or missing
child files fail without overwrite. `recover --bank 0F` explicitly backs up the
whole folder, including the child, before restoring the reviewed inputs.

Make tracks both new files for edits and deletions. The production builder
composes both families into the actual `asset_bank_0f.o` linker object. Each
report family claims only its own disjoint physical stream ranges, verifies the
whole linked payload, and checks source stability. No unselected entry or bank
directory receives additional credit.

## Validation and remaining limits

The independent ROM audit checks all 42 records against the native field layout.
All **630 field mutations** change only their intended decoded field, and all
six consumer endpoint mutations are rejected. Seven focused tests cover field
widths, signed zero, invalid storage and boundaries, preservation and recovery,
source races, and comparison with the actual linked object. The real Makefile
scheduling test includes edits and deletions of both collision source files.

The 49-entry pilot also found independent event gaps and incomplete behavior
instruction tails. Consequently, resolving byte 33 alone would not unlock the
entire 59,622-byte candidate group. The other 33 entries remain excluded under
the existing strict event/program rules. No gap or incomplete instruction was
converted into opaque source data to enlarge this batch.

## Accepted batch

On 2026-10-30, all 2,926 Docker tests passed (eight skips; 170.143 seconds).
The full US asset build reproduced all 67,108,864 ROM bytes exactly in 134
seconds including setup. Native objdiff added exactly 6,056 matched and complete
Data bytes, producing **63,092,078 / 65,120,512 (96.88511%)** matched Data.
Remaining unmatched Data: **2,028,434 bytes**.

All 26,434 prior unique editable-source hashes were preserved. Exactly two new
source files were added. Code totals and matches, the Data denominator and every
other existing unit measure were unchanged; only bank 0F unreconstructed storage
fell by 6,056 bytes to 63,209. Progress and whitespace checks passed, and the
native report snapshot was verified current.

Tested base: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` with uncommitted changes.
Report SHA-256: `3fef97aef7414392cf913d83296fb99385f6f1f14bbb4d9228c21f7024660c33`.
Source fingerprint: `cb9d0abca6a4e70571218955f7432592e20e24e38f24c0f5ec16cff3bbecb9e3`.
Machine-readable evidence is in [us_collision_controls.json](us_collision_controls.json).
