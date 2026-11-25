# US scene headers and lookup-ID containers

Bank `15` contains 69 slots, of which 67 hold uncompressed two-child scene
containers. This reconstruction owns **6,292 bytes** beyond the already credited
552-byte outer directory:

| Component | Bytes |
| --- | ---: |
| 47 typed fields in each 76-byte header | 4,288 |
| Generated two-record nested directories | 1,072 |
| 226 lookup IDs | 452 |
| Generated minimum eight-byte alignment | 480 |

The remaining **804 bytes** are twelve unexplained bytes per header. They stay
in preserved backing and receive no credit. The codec exposes no raw-byte field.

## Native ownership and types

`15002FB4` requests bank `15`, scene index, at depth two through `1502B6BC`.
At `15003008..15003014`, child zero becomes `D_800B0DF0`. The nested-directory
relocator `1502B4A8` reads eight-byte offset/size records and their final-record
flag. Complete checksummed loader spans are authenticated before reconstruction.

Direct native `lb`, `lbu`, `lh` and `lhu` operations prove the fixed offset/type
map in `scene_header_codec.FIELDS`. The evidence JSON includes representative
load sites and complete consumer checksums. An independent machine-word analysis
confirmed all 46 original straight-line load sites without carrying facts across
branches or calls. Additional fields have explicit native evidence:

- `151732E0` copies offsets `00`, `02`, `3A..46` to `D_8008CC70`; both incoming
  paths retain the header pointer in `v1` or reload it before the copy.
- `15178E50` reads mode `14` and signed threshold `16`. The branch-likely delay
  slot clears `v0` only on the taken path; the threshold read uses the header.
- `150000B0` copies the fourteen bytes `2C..39` to stack `60..6D`. Subsequent
  loads establish signed halfwords at `2C/32`, unsigned halfwords at
  `2E/30/34/36`, and unsigned mode bytes `38/39`.
- `1504A730` reads unsigned callback selectors `49/4A`; each dominating
  `lui t9,800B` survives the intervening branches until the header-pointer load.
- `80012020` tests bit zero of unsigned byte `2A`.

Offset names deliberately retain their native widths and locations where the
higher-level meaning is not established. Unknown offsets are `04`, `15`, `20`,
`22..28`, `47` and `48`; even their observed zero values are not inferred padding.

## Lookup list and packing

The scene loader copies header byte `12` to `D_800D2F3C`, and the second child
pointer to `D_800D2F40` at `150030B8..150030C4`. `1509B4A0` loads unsigned
halfword IDs at `1509B508/1509B524`, advances by two and stops at that count.
`15017868` walks the same list with a signed halfword read at `150178B8`.
Sources retain the 16-bit ID bit pattern. All 67 stored child sizes equal twice
the original header count; the 54 nonempty lists contain 226 IDs in total.

Every native container has a 16-byte directory, a 76-byte header at offset 16,
and its ID list at offset 96. The four bytes before the list and the container's
minimum trailing eight-byte alignment are generated zeros. The codec checks
these rules against every original record and rejects nonzero or extra padding.
The directory is generated from the fixed header extent and the typed ID count,
not preserved as opaque bytes. Field-count mismatches fail.

## Editable sources and linked proof

`build/assets/asset-directories/us/bank15/scene-headers/` contains a manifest and
`scenes.json`. The existing parent manifest, directory and backing are preserved.
Changed or missing child inputs fail without replacement; explicit
`./conker asset-directories recover --part bank15` backs up the whole parent
before recovery. Make tracks child edits and deletions.

The actual `asset_bank_15.o` contains the freshly encoded supported spans and
preserved unknown bytes. The report verifies that whole object against the
current source reconstruction and independent ROM, then compares only disjoint
owned spans. Mutating an uncredited backing byte still fails whole-object
validation; it cannot silently receive credit.

## Validation

66 focused tests passed. Independent reads checked all fields, generated indexes,
IDs and alignment; all 3,375 semantic field/ID mutations changed encoding or
were rejected. All 78 full-consumer endpoint mutations were rejected. The linked
pilot matched 6,292/6,292 bytes; independently changing each of those bytes made
all 6,292 native comparisons reject a perfect match.

All 48 Make integration tests passed, followed by the full Docker suite
(2,985 tests, eight skipped). `./conker build --assets` rebuilt the exact
67,108,864-byte US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Progress and whitespace checks passed.
Tested base: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, with these working-tree
changes applied.

The final full native report accepts **+6,292 matched and complete data bytes**:
63,209,268 / 65,120,512 matched, with 1,911,244 remaining. Only bank 15's
unreconstructed unit shrank (7,096 to 804); all earlier unit measures were
preserved. All 27,251 previous editable-source hashes and all previous linked
asset-object hashes remained identical; two child source files were added.
Four CPU object containers and the final ELF were rebuilt. Their old containers
were not retained for section-level diagnosis, so no cause is inferred for the
hash changes: fresh full-span code/data proofs are unchanged, and independently
extracting the current linked ELF reproduces the exact original ROM.

The accepted report SHA-256 is
`5f11e0b5669df08e73bce68de9f5165c7160fe9cdf42946a8e3699a07a56fef7`.
See [machine-readable evidence](us_scene_headers.json) for consumer spans
and field-load evidence.
