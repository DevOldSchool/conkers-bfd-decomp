# Additional reviewed US character-model identities

This expansion adds 24 bank-01 model labels to the 37-model registry, yielding
61 reviewed identities. It preserves every field of those earlier 37 records,
including the three [Lady Cog eye-part consumers](lady_cog_eye_part_semantics.md)
and Haybot's model-specific branch. It changes descriptive naming evidence only:
no linked symbols, C expressions, ABI, matching status, geometry, materials,
scene associations or runtime evidence are changed.

## Exact identities and visible basis

All additions below are bank `01`, segment `0`; entries are decimal. Full decoded
segment sizes, SHA-1 and SHA-256 pins are recorded individually in
[`config/model-semantic-names.json`](../../config/model-semantic-names.json).
The labels identify these exact records, not an entire character family.

| Entry | Reviewed label | Visible basis in the freshly inspected owned-model render |
| --- | --- | --- |
| 0 | Conker | Orange squirrel, bushy tail, blue jacket, white gloves and blue/yellow shoes |
| 1 | Conker — variant 1 | Same character and outfit in a distinct exact model |
| 2 | Conker — variant 2 | Recognizable squirrel form and outfit with a more angular outline |
| 3 | Conker — variant 3 | Recognizable face, ears, tail, blue jacket and gloves |
| 4 | Conker — variant 4 | Recognizable orange squirrel and outfit with a simplified outline |
| 12 | Franky the Pitchfork | Faced wooden handle and dark two-pronged fork |
| 55 | Franky the Pitchfork — rope variant | Matching faced handle and fork with a visible rope |
| 58 | Fire Imp | Orange-red horned and winged imp with yellow eyes and belly, fangs and pointed tail |
| 61 | Fire Imp — grey variant | Matching imp form in charcoal grey with yellow eyes and fangs |
| 82 | Carl / Quentin | Grey cog, central face, yellow eye surfaces and red-tipped cigar |
| 83 | Fangy the Raptor | Green striped raptor with red-brown saddle/harness and pale claws/teeth |
| 90 | Tediz | Brown stitched bear with muzzle, ears and pale belly |
| 95 | Tediz — ammunition belt | Brown stitched bear with prominent yellow ammunition belts |
| 112 | Gregg the Grim Reaper — scythe | Skull-faced black-robed figure with green shoes and curved scythe |
| 114 | Berri — pink outfit | Grey character, blonde ponytail, pink/yellow outfit and pink/white shoes |
| 116 | Tediz — variant 1 | Brown stitched bear with pale belly and a simplified outline |
| 117 | Tediz — variant 2 | Brown stitched bear with pale belly and drooping arms |
| 118 | Panther King | Large dark feline with gold crown, purple-trimmed royal robe and long tail |
| 122 | Tediz — variant 3 | Angular brown stitched bear with pale belly |
| 141 | Tediz — medic | Bear with white apron/coat, red stains and circular medical head mirror |
| 150 | Conker — black outfit | Orange squirrel, white gloves, black outfit and black boots |
| 164 | Count Batula | Pale squirrel-like vampire, large pale coiffure and red robe with white trim |
| 178 | Gregg the Grim Reaper — hooded | Large skull, black hood/robe, skeletal hands and green shoes |
| 180 | Gregg the Grim Reaper — without robe | Matching skull and exposed skeleton, with no robe |

Variant numbers distinguish the reviewed records; they do not assert distance
thresholds, automatic selection or LOD tiers. The rope on Franky 55 does not
establish an executed hanging event. Grey Fire Imp 61 does not establish an
extinguishing transition. Carl / Quentin 82 deliberately omits the selected
preview expression from its identity. The medic label describes costume only.
Conker 150 is limited to the visible black outfit; neither sunglasses nor a
scene-specific role is established.

Berri 151 remains unknown. The fresh render exposes the blonde head/ponytail,
hands and black boots but obscures most body/outfit surfaces, so an outfit label
is not promoted from the existing canonical metadata. Unlisted banks, entries
and segments remain unknown even when they share bytes or family resemblance.

## Provenance and numeric join

Previously reviewed canonical inspection metadata selected each validation case.
The selected source was joined to an actual preview-manifest record's numeric
bank, entry and segment, then to independently decoded `ModelBundle.index`,
`ModelSegment.index` and segment data. The join checked size and both digests.
No filename-derived ID, neighboring-asset inference or external decompilation
name list supplied a numeric identity.

The reviewed canonical inputs were
[`config/model-inspection.json`](../../config/model-inspection.json), SHA-256
`b43ebaff477fe60d72635866310daaec1181df6c630923bf6114aa50cbef9f98`, and
[`config/model-validation.json`](../../config/model-validation.json), SHA-256
`cc9756fdf6ca78a977c456fb9a95c93dd01401fc318722e3947f175bfac48e02`.
Their exact JSON array indices are recorded here to make the metadata join
reviewable without publishing private model paths:

| Entry | Inspection `/models/` index | Validation `/render_cases/` index |
| --- | ---: | ---: |
| 0 | 0 | 28 |
| 1 | 251 | 275 |
| 2 | 252 | 276 |
| 3 | 253 | 277 |
| 4 | 254 | 278 |
| 12 | 24 | 60 |
| 55 | 265 | 289 |
| 58 | 2 | 38 |
| 61 | 3 | 39 |
| 82 | 393 | 417 |
| 83 | 4 | 40 |
| 90 | 5 | 41 |
| 95 | 278 | 302 |
| 112 | 7 | 43 |
| 114 | 8 | 44 |
| 116 | 135 | 159 |
| 117 | 136 | 160 |
| 118 | 20 | 56 |
| 122 | 138 | 162 |
| 141 | 147 | 171 |
| 150 | 21 | 57 |
| 164 | 10 | 46 |
| 178 | 11 | 47 |
| 180 | 12 | 48 |

The fresh source manifest SHA-256 was
`a71f4a2cd984c4d36df7f14966db56b1897b7a3a4e8b7482942b064f6f72a9bd`.
The review explicitly rerooted canonical sources to the available export and
checked the actual manifest after doing so. Source checks excluded captured
materials. Dependency fingerprints covered each glTF and its external buffers
and images, and were unchanged across private deterministic material renders.
Those renders and all five contact sheets were inspected; no model corpus was
re-exported and no external asset was imported. ROM-derived texture composition
is not a runtime capture or proof of native appearance parity.

Existing independent project evidence includes the
[Franky comparison](us_gallery_character_names.md),
[Tediz reference corrections](us_model_reference_corrections.md) and
[Tediz rig validation](us_tediz_submitted_rig_validation.md).
For the other identities this review uses previously reviewed canonical names
plus the freshly inspected owned models. Public reference-image access was
blocked, so no fresh independent external pixel comparison is claimed. Search
captions and filenames are not visual proof. The private byte/dependency/render
recheck verified all 25 reviewed candidates, including the held Berri variant;
only the 24 listed identities are added.

## Fixed ROM and consumer scope

The normalized US ROM remains pinned to `67108864` bytes, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` and SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`.
The complete registry remains pinned in
[`scripts/model_semantic_names.py`](../../scripts/model_semantic_names.py);
there is no alternate registry input or self-authenticating replacement.

Each addition reuses exactly the seven reviewed full-span bank-01 consumers:
`func_1503CF20`, `func_15082A44`, `func_150837D4`, `func_150839B8`,
`func_1507E5C8`, `func_1502F01C` and `func_1502CCFC`. Their exact extents and
SHA-1 pins remain unchanged. See [ROM defaults](us_rom_character_defaults.md),
[draw tables](us_character_draw_tables.md) and the
[earlier character expansion](character_semantic_registry_expansion.md).

This chain connects model identity to shared load, spawn, index-store, default,
expression, texture and part-submission paths. It does not identify exclusive
controllers, prove a live actor instance or establish a scene-specific spawn.
No additional dispatcher/classifier lead is promoted to a registry consumer,
and no new branch is forced into the Haybot-specific branch schema.
The 24 additions contribute 168 references: total references rise from 207 to
375, distinct full spans remain 42, and the sole model-specific branch remains
Haybot's. These counts do not measure newly discovered functions or C matches.

## Validation and reproduction

With an owned reviewed ROM configured locally:

```sh
python3 -m scripts.model_semantic_names --rom "$CONKER_US_ROM"
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_semantic_names.py'
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_coverage.py'
```

The tests pin the exact 61-key/name map, preserve all prior record fields,
limit new records to the shared chain, keep Berri 151 and unrelated namespaces
unknown, and preserve full-span and ROM/model hash rejection. Naming evidence
still cannot promote geometry, materials, visibility, animation, scene association
or native parity. This source-only naming expansion adds 24 reviewed model
identities, leaves 1,426 of 1,487 identities unknown, and adds zero C matches.

The isolated review passed 21 naming tests, 12 coverage tests and nine ROM-policy
coverage tests, with no skips. Its owned-ROM audit verified all 61 model records,
42 distinct full consumer spans and the unchanged Haybot branch. A fresh full
coverage comparison against the 37-name checkpoint changed exactly these 24
naming records: every other model field, all 10,394 material-run records, all
non-naming summary and bank dimensions, evidence availability, texture-input
digests and all other top-level fields were identical. The corpus still contains
232,162 source faces. No export or runtime-observation manifest was supplied for
that comparison. No C build or function-comparison gate is claimed by this
registry-only patch.

The integrated registry passed all 1,726 repository tests in both the host suite
(37 tool/environment skips) and the ROM-enabled pinned-toolchain suite (one
optional Khronos-validator skip). The fresh integrated coverage report is exactly
equal to the reviewed 61-name report. The combined naming checkpoint also passed
focused source/layout checks, a clean batch, integrated game/data/rodata checks,
a byte-exact full US ROM build, progress and whitespace checks. An independent
read-only review authenticated every model pin, all 42 full consumer spans,
canonical numeric joins, rendered evidence and preservation of the earlier 37
records. These gates establish integrity, not additional character behavior.
