# US direct-model auxiliary records

This batch reconstructs **21 bank-03 models**, occupying 18,483 compressed
ROM bytes, plus 100 bytes of minimum bank alignment. The combined gain is
**18,583 bytes** within six existing linker objects. Their boundaries and all
previously authored model sources remain unchanged.

| Existing raw object | Models | Model and alignment bytes |
| --- | ---: | ---: |
| `00F90626` | 7 | 8,882 |
| `00F954D8` | 6 | 3,297 |
| `00F969E2` | 3 | 2,598 |
| `00F97590` | 3 | 2,208 |
| `00F9BB68` | 1 | 824 |
| `00F9C0B2` | 1 | 774 |

Model 66 remains unproved and its 343 stored bytes inside `00F954D8` remain
backing, without credit. Every other byte in these six objects is generated
from typed models or the existing bank-03 index's minimum alignment rule.

## Native evidence and representation

The existing model-bundle codecs already describe the relevant normal and
face-table layouts. The old direct-model dispatcher excluded all auxiliary
header regions, so it never selected these valid combinations for bank 03.
The new builder applies the existing strict `extended-model` codec with the
non-primary table layout. This reuse is supported by the direct native loader:

- `15003E00` supplies bank 03, and `15003E18` invokes `1502B6BC` with
  relocation mode zero.
- `1502B798` invokes `1502B4A8`, which walks eight-byte header records to
  their high-bit terminator, masks sizes to 28 bits and relocates nonempty
  offsets. The direct model header is five such records, totaling 40 bytes.
- `15003E94` supplies vertices at model + 40. Loads at `15003E98`,
  `15003EA0` and `15003EB4` preserve the header's display-list, secondary
  and tertiary pointers in runtime fields +0x1C, +0x9C and +0x44.

The complete original spans are authenticated: `150039E0` (2,964 bytes),
`1502B6BC` (308), `1502B4A8` (288), `1503D368` (208) and `1503D438` (36).
The latter two are the existing scanner and relocation consumer for the
`DC38000E` normal-table command. The existing normal format and RSP evidence
are documented in the [model inventory](../assets/models/us_asset_inventory.md).
Raw-ASM words and addresses for the loader spans were also compared directly
to the checksum-validated original GAME code.

The 21 records contain 1,497 vertices, 1,239 display-list commands, 31 normal
tables (32 signed XY pairs each), and 654 native face words. Entries 44–50
use face words; 63–65, 67–69, 73–75 and 77–79 use normal tables; 96 and 99
combine both. Every normal table is completely covered by native command
references. Each tertiary table contains one big-endian u32 per parsed face,
without the primary scene surface header. These words retain structural names;
no additional gameplay or collision meaning is inferred. Color tables are
explicitly excluded from this direct-model extension.

All decoded regions are covered by typed fields and the existing codec's
bounded, checked zero intervals. Fresh bounded DEFLATE reproduces each entire
stored stream exactly; no compressed tokens or opaque suffixes are authored.
The remaining 100 bytes are 23 minimum eight-byte alignment gaps derived from
the unchanged bank-03 directory, not arbitrary editable padding.

## Inputs, build and report

`./conker direct-models build` creates checked `manifest.json`, editable
`models.json` and preserved `backing.bin` files under
`build/assets/direct-models/us/<part>/`. It also hashes and validates the
existing `build/assets/asset-directories/us/bank03/` inputs. Make tracks all
own/shared inputs and deletions, and links the freshly composed raw objects.
All selected sources are rechecked before publishing any output part.

Changed or missing inputs fail without replacement. Explicit
`./conker direct-models recover --part ID` backs up that object's source folder;
shared directory recovery remains with `./conker asset-directories`.
The native report compares actual linker objects against fresh sources and
independent original-ROM ranges. Even corruption outside the credited slices
fails whole-object verification. The unproved model 66 is excluded from the
new comparison unit and remains in the bank's unmatched remainder.

## Validation

Accepted validation at base
`38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus uncommitted changes.
The 53 focused and Make integration tests pass. The linked-object native pilot
matches all 18,583 bytes; every individual byte mutation rejects the perfect
match. Independent reads verify all headers, vertices, commands, normals and
face words. All 2,638 individual normal-component/face-word mutations change
only their exact decoded fields, and all ten consumer endpoint mutations fail
full-span authentication. All new owned ranges are disjoint from prior credit.
The full Docker suite passes 3,016 tests with eight skips (286.365 seconds).
`./conker build --assets` reproduces the complete 67,108,864-byte US ROM
exactly (188 seconds including setup; 157.847 seconds compile/link/verify).
An independent extraction from the current linked ELF also matches the ROM.
The full native report has zero compile errors (452.5 seconds preparation,
28.3 seconds report and validation). Progress and whitespace checks pass.

Matched data increases by **18,583 bytes** to **63,281,049 / 65,120,512
(97.175294%)**; complete data increases to 63,234,921. **1,839,463 bytes
remain unmatched.** Six new units account for the entire increase. The only
changed prior unit is the bank-03 remainder, reduced from 18,926 to 343 bytes.
All 27,273 prior editable source hashes and 11,829 prior asset-object hashes
are preserved. Code, function counts, denominators and linked runtime code/data
are unchanged. The report snapshot is current.

Report SHA-256:
`90dd63ae6aaaba73095934bd45eefd47ce2a890667740a9354a24804f346e984`.
Input fingerprint:
`19b64e4a4bc004def977c8fb1cc29dcbf031300db5adabe1bc5a6a701fa6b7a1`.
