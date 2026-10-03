# Reviewed US character-model registry expansion

This records the [Haybot naming pilot](character_semantic_naming.md) expansion
to 17 exact bank-01 model identities. The subsequent
[object-model expansion](object_semantic_registry_expansion.md) adds 20 bank-03
and bank-09 identities, bringing that stage to 37. A further
[character-model review](more_character_semantic_registry_expansion.md) adds
24 exact identities, bringing the registry to 61. The next
[character-model expansion](additional_character_semantic_registry_expansion.md)
adds 30 bounded identities, bringing that stage to 91. The
[scene-prop expansion](scene_prop_semantic_registry_expansion.md) adds 20
bank-04 identities, bringing the registry to 111. Counts and validation results
below describe the 17-model stage. The pilot's totals remain historical.
The additions change descriptive model labels and naming-audit metadata only;
no linked symbol, character controller, C expression, ABI or match status follows
from them.

## Identity evidence and scope

The 16 additions come from the explicitly corrected or refined visual identities
in [the gallery character-name review](us_gallery_character_names.md), including
its separately discussed Red Dinosaur. A fresh review of the current ROM-only
previews confirmed these appearances. The route to each preview was checked
against an actual generated manifest record's numeric bank, entry and segment,
then joined to the independently decoded ROM segment and its size, SHA-1 and
SHA-256. Filenames and labels did not supply the numeric identity. A current
preview dependency fingerprint helped identify the reviewed export; it did not
establish native visual parity. No third-party decompilation name list is used
as the authority for this expansion.

All listed identities are bank `01`, segment `0`; entries are decimal:

| Entry | Descriptive label | Bounded visual basis |
| --- | --- | --- |
| 5 | Wasp | Angular black/yellow insect |
| 10 | Mrs. Catfish | Cat-faced fish with yellow glasses |
| 14 | Corn Bag | Sack with eyes and visible CORN lettering |
| 15 | Lady Cog — red | Red toothed wheel with facial features |
| 24 | Jack — metal box | Riveted gray box with blue eyes |
| 26 | Catfish — skeletal remains | Catfish face and fins with exposed bones |
| 52 | TNT Imp | Purple imp with a TNT-marked keg |
| 68 | Dung Beetle | Red/black beetle with open wing covers |
| 70 | Lady Cog — blue | Blue variant of the cog form |
| 75 | Haybot | Retained [independent Haybot appearance evidence](us_haybot_appearance.md) |
| 76 | Lady Cog — green | Green variant of the cog form |
| 107 | Electric Eel | Elongated blue-green body and yellow eyes |
| 125 | Franky the Pitchfork — broken upper part | Wooden face/handle without the metal fork |
| 165 | Red Dinosaur | Orange-red skin, yellow eyes and reptilian form |
| 173 | Wayne — cigar | Wasp with a visible cigar |
| 174 | Wanka — fat wasp | Broad-bodied wasp-trio member |
| 175 | Wanka — skinny wasp | Thin-bodied wasp-trio member |

Corn Bag's label deliberately makes no claim that the model is unused. Naming
Franky's broken upper part does not name entry 12 or other Franky variants.
Red Dinosaur does not identify this model as Fangy, Fire Imp or Dino Baby.
Conker entry 0 remains unknown; no name in this stage extends to an unlisted
bank/entry/segment identity.

## Fixed provenance and schema

[`config/model-semantic-names.json`](../../config/model-semantic-names.json)
schema 2 records normalized ROM size `67108864`, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` and SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`.
Each record independently pins its decoded segment's size and both digests.
The complete registry bytes remain pinned by a constant in
[`scripts/model_semantic_names.py`](../../scripts/model_semantic_names.py).
There is no caller-supplied registry path, self-declared digest or generated-file
fallback. Schema validation checks structure; it is not identity evidence and
cannot authenticate an arbitrary replacement registry.

Validation rejects unknown or missing fields, duplicate JSON object keys,
duplicate numeric identities, Boolean or noninteger indices, unsupported banks,
empty or nonrelative evidence paths, malformed digests, nonpositive sizes and
invalid consumer ranges. Shared consumer references must agree on symbol,
address, size and digest. A model-specific branch is optional; when present it
must identify that model and fit inside its own declared full consumer span.
The current branch sub-schema retains the Haybot selector/phase/cycle evidence;
other models are not given invented branches to satisfy it.

## Shared consumers, independent evidence

The seven generic bank-01 load, spawn, index-store, default, expression, texture
and part-submission consumers are shared paths. Their complete pinned spans
provide a model-to-loader/render-path connection, not unique actor ownership,
character-exclusive controller identity or evidence that a particular instance
executed. See [ROM defaults](us_rom_character_defaults.md) and
[draw tables](us_character_draw_tables.md).

Only Haybot 75 retains `func_15061B4C` and its bounded model-specific branch
`0x15061FA8..0x1506208C`. Neither that shared dispatcher nor its Haybot branch is
reused as evidence for the new models. There are 120 consumer references across
17 records, but only eight distinct full spans; the audit hashes each distinct
span once and separately checks the one Haybot branch.

The audit loads every bank actually listed by the registry, rather than
hardcoding bank 01. Tests exercise simultaneous bank-03 and bank-04 records and
fail closed for missing or duplicate extracted identities and changed ROM reads.
The actual reviewed expansion contains only bank 01.

Coverage emits `reviewed-registry` for the applicable ROM/profile. Exact named
models get `reviewed`; unlisted bank/entry/segment keys remain `unknown` even if
they share the same bytes or related appearances. Geometry extraction, material,
scene association, visibility, visual parity and runtime observations retain
their independent evidence states. The name adds no evidence to those dimensions.

## Reproduction

```sh
python3 -m scripts.model_semantic_names --rom roms/baserom.us.z64
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_semantic_names.py'
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_coverage.py'
```

The naming tests check all 17 expected keys, unchanged Haybot selector evidence,
malformed expanded records, optional branches, deduplicated consumer counts,
multiple banks, and named and unlisted identities in the same coverage report.
When the owned reviewed ROM is present, they independently verify all 17 model
pins, the eight full consumer spans and the Haybot branch. No new C match is
claimed by this registry-only expansion.

The isolated expansion check passed 872 model tests (one skip), including the
15 naming tests and 12 coverage tests. The owned-ROM audit confirmed all 17
model identities, eight distinct full consumer spans and the single Haybot
branch. Fresh coverage contains 1,487 models, 10,394 material runs and 232,162
source faces: 17 names reviewed and 1,470 unknown. Compared with the pilot's
serialized report, every non-naming model field, every material-run record and
all non-naming summary dimensions are identical. No export or runtime-observation
manifest was supplied for that coverage comparison.

The combined integration checkpoint passes the complete 1,718-test suites on
the host (37 skips) and in the ROM-enabled pinned fixture (one optional skip).
Its separate C naming batch, complete ROM, integrated game, mapped rodata,
progress and whitespace gates pass. Independent review verifies all seventeen
ROM identities, eight full consumer extents, and the manifest/visual evidence
joins. Registry expansion itself adds sixteen named model identities and no
function matches.
