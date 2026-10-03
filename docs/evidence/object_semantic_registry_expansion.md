# Reviewed US object-model names

This source-only expansion adds 20 exact bank-03/bank-09 identities to the
[17 bank-01 character models](character_semantic_registry_expansion.md), for
37 reviewed descriptive names. It changes the fixed registry, its review pin,
naming tests and scoped documentation. No C, linked symbol, ABI, model asset,
compiler, comparator or matching status changes.

## Source identity and visual review

Every addition is segment `0` of normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a` (67,108,864 bytes; SHA-256
`32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`).
The [schema-2 registry](../../config/model-semantic-names.json) pins each exact
bank/decimal-entry/segment, source size, SHA-1 and SHA-256, plus the complete
consumer bodies and their SHA-1 values. Its complete bytes are authenticated
by `REGISTRY_SHA256` in [the existing naming module](../../scripts/model_semantic_names.py).

For each reviewed model, the canonical `config/model-inspection.json` record's
`render_case` was joined to `config/model-validation.json` and its exact source
path, then to a fresh preview manifest's numeric bank, entry and segment.
Independent ROM decoding supplied source bytes and digests. The actual glTF
and every buffer/image dependency were fingerprinted; the review image hash
was checked again after visual review. Configured non-ROM-only roots, where
present, were explicitly mapped to equivalent fresh ROM-only roots with the
same relative source path. A path selects the record; it does not identify the
model semantically. No name comes from a filename, neighboring ID, scene art,
external decompilation name list, or captured material.

Neutral-source renders of all 20 models were visually reviewed, with cigar and
helmet also inspected individually. These observations support descriptive
source-model identity only. They are not native frames, live state, actor
identity, observed visibility, or controller-exclusivity evidence.

| Bank:entry:segment | Label | Bytes | Bounded visual basis |
| --- | --- | ---: | --- |
| `03:0001:00` | Square-base hanging bell | 2632 | Brown square-based bell with loop/cord top |
| `03:0060:00` | Three throwing knives | 2488 | Three blades with riveted brown handles; throwing behavior unobserved |
| `03:0061:00` | Crossbow | 3672 | Wooden stock, transverse limbs and string |
| `03:0062:00` | Chainsaw | 2920 | Yellow body, black handle and toothed saw bar |
| `03:0077:00` | Cock and Plucker sign | 2264 | Framed sign with THE COCK AND PLUCKER lettering |
| `03:0082:00` | Curved sword | 872 | Curved blade, circular guard and wrapped grip |
| `03:0083:00` | Revolver | 4600 | Barrel, cylinder, trigger guard and dark grip |
| `03:0087:00` | Grenade crate | 792 | Wooden crate marked GRENADES |
| `03:0091:00` | Vitamin bottle | 792 | White-capped yellow bottle marked VITAMINS |
| `03:0095:00` | Tracked vehicle | 4792 | Green armored body on tracks; no exact gameplay vehicle identity |
| `03:0098:00` | Closed / Back at 10 sign | 680 | Suspended sign marked CLOSED / BACK AT 10; no opening-time claim |
| `03:0110:00` | Bombs crate | 792 | Metal crate marked BOMBS |
| `09:0029:00` | Cigar | 552 | Brown cylindrical body and pale tip |
| `09:0133:00` | Military helmet | 2072 | Green dome, white marking and two straps |
| `09:0162:00` | Wall-mounted flame (UI model) | 2728 | Tapered flame-like surface with a small wall plate |
| `09:0164:00` | Upright cash bundle | 3256 | Folded green banknotes, red band and eyes |
| `09:0165:00` | Upright cash bundle — attachment variant | 3320 | Similar imagery to 164, distinct source and specialized consumer |
| `09:0185:00` | Conker HUD head | 5768 | Orange squirrel head, cream muzzle and black eyes |
| `09:0186:00` | Digital timer | 1928 | Four-digit device; displayed digits belong to an inspection preset |
| `09:0345:00` | Hanging bell | 872 | Small green bell hanging from a dark cord |

## Separate consumer domains

The new records reference 33 distinct complete consumer spans, all checked
against current inventory lengths and original ROM code. Together with the
unchanged bank-01 records there are 41 unique full spans and 204 references.
Only Haybot retains its one bounded `model_specific_branch`; the generic
bank-01 load/default/expression/draw consumers are not copied to these objects.
Full-body hashes preserve the surrounding control flow, not just convenient
literal-loading instructions. Shared consumers remain shared functions.

- **Action attachments, 09:29 and 09:133.** `1514DCAC` requests action **35**
  followed by **68** on the same parent. Action 35's header `80086DD4` points
  to one record at `8009D1E0` (model **133**, kind 2, animation selector 2).
  Action 68's header `80086EDC` points to one record at `8009D1F0` (model
  **29**, kind 1, selector -1). `15083568` passes the distinct fields through
  `15030AF4` and `1502FFD8`; the animated path uses `1503F62C`, while both
  reach explicit bank-09 loading in `1502FE10`. Owner checks, duplicate
  suppression, allocation and loading can prevent creation. No Conker parent,
  smoking controller or guaranteed creation is inferred.
- **Direct timer, 09:186.** `15093878` calls `1518C900` with model 186 and
  stores its primary list at `800D2448`. `150938BC` derives digit textures
  from `800D2450`, binds four pixel segments and submits that retained list.
  The registry also pins the relocation and texture/matrix helpers selected
  by the [direct-binding evidence](us_direct_segment_texture_bindings.md).
  The rendered 00:00 is an explicit inspection preset, never an initial or
  observed gameplay time. The label therefore omits the preset.
- **Dedicated HUD head, 09:185.** `1509093C` loads model 185 through
  `1502FE10`, retains its list at state `800D24C8+0x80` and maintains four
  correlated texture selectors. `150911F4` uses `1510D0EC` to bind them and
  submits the retained list. This is separate from bank-01 Conker model 0,
  which remains unnamed. The label does not select a texture phase or native
  HUD deformation. See [specialized consumers](us_special_attachment_materials.md).
- **Copied-list UI, 09:162 and 09:164.** `151EB06C` requests model 164 /
  animation 23 at `151EB5BC`, and model 162 / animation 8 at `151EB5D8`.
  `151ED90C` constructs the copied lists; `151EDBDC` renders them. Their
  shared animation/model/texture helpers are pinned separately from the
  specialized attachment path. The flame's shape is not world-placement or
  damage-controller evidence. See [UI constructors](us_ui_constructor_materials.md).
- **Specialized cash attachment, 09:165.** `150FAE18` or `151D6BFC` passes
  model 165 to `15157010`. Callbacks `150FB1E8` / `151D710C` bind descriptor
  195 through `15133EEC`; type-54 renderer `15157420` submits the model.
  Source hashes, size and native alpha handling differ from UI model 164,
  even though displayed mesh/rig/images agree. Neither identity collapses
  into the other, or into bank-01 character 165. Whole constructors have
  broader unproved event purposes. See [specialized consumers](us_special_attachment_materials.md).
- **Ordinary lookup, 09:345.** `15010A60` stores lookup selector **86** at
  template `+0x56` and flags `0x0D00` at `+0x50`, then calls `1513264C`.
  The table at `800A3880` maps selector 86 to model **345**; `151336A8`
  loads it and `15132B80` submits its list. The reviewed initial callback
  flag is clear. This is not ringing behavior, and neither 86 nor 345 is
  the square-base bank-03 bell. See [ordinary objects](us_bank09_object_materials.md).
- **Placed bank-03 objects.** Each chosen model has an exact bank-0C
  placement record whose defaults admit the ordinary direct branch.
  `150039E0` reads the model index at record `+0x10`, retaining the model
  list at runtime record `+0x1C`; `151135C4` selects the `0xA0`-byte record
  and `151137D4` submits its primary list. These three shared full spans are
  pinned for each identity. Numeric placement association grants no scene
  name or observed visibility. See [placement consumers](us_model_scene_consumers.md)
  and [ordinary material consensus](us_object_material_consensus.md).

One independently checked placement witness per bank-03 model is recorded
below. Bank is `0C`; scene and record indices are decimal. SHA-1 covers the
complete placement record. These are static associations, not live observations.

| Model | Scene / record | Initial flags | Record SHA-1 |
| ---: | --- | --- | --- |
| 1 | 6 / 7 | `0x04` | `4fd6e090dcb8e6fc81ebf8d66d56dc7ac6819f1f` |
| 60 | 26 / 1 | `0x00` | `c9bd88f28110e2300b32fa13cd36ab3c611b4673` |
| 61 | 26 / 2 | `0x00` | `731431ea0fc68109b5e9409e92963323e8081f52` |
| 62 | 33 / 0 | `0x00` | `1e522ed1b7dfefdbb3c8e1ec301f57c656f458e5` |
| 77 | 29 / 7 | `0x00` | `cf4c77f91fc13171b560973a8a7880bf60c9f2ff` |
| 82 | 45 / 19 | `0x00` | `b1809ee3ba54517430f78710c9f68b93f8dddd1e` |
| 83 | 45 / 4 | `0x00` | `289c30554b392a57cf8dcfd13b5e9fadc7c78b24` |
| 87 | 26 / 10 | `0x00` | `76d1125070a50e131c8a854d89ae0e1bbe7c2ce8` |
| 91 | 43 / 0 | `0x00` | `b7558da5b6decf2373ed1acd7cc9408af814c266` |
| 95 | 35 / 0 | `0x04` | `0615424ddcf44d171596ee388a2183ec92f62269` |
| 98 | 6 / 4 | `0x00` | `94d4b649f642574d5e4efbd2b9a6e2fd37acc88b` |
| 110 | 63 / 19 | `0x00` | `3a5d4b89539db4a8f6a75b3cc9fe72457fd5f16c` |

Unlisted models remain unknown, including bank-03 crate 0, barrel 39 and mines
crate 109, and bank-09 roll 42. Familiar-looking art is insufficient without
the separately followed consumer association. Names grant no extraction,
material, scene, visibility, native-parity or runtime-observation credit.

## Reproduction and scope

```sh
python3 -m scripts.model_semantic_names --rom roms/baserom.us.z64
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_semantic_names.py'
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_coverage.py'
```

The naming tests check all 37 exact keys, domain-specific consumer sets, source
pin separation for the cash variants, and the unchanged Haybot-only branch.
Equal synthetic bytes cannot merge distinct model namespaces. Action IDs,
lookup selectors, nearby unreviewed models and nonzero segments remain unknown.
With the owned ROM present, the audit checks every listed model and all 41
complete consumer spans, plus the single Haybot branch. No compile, CURRENT,
layout, full-ROM rebuild or C-match acceptance is claimed by this metadata-only
change.

The isolated source check passed 18 naming tests, 12 coverage tests and the
broader 875-test model suite (one optional skip). The owned-ROM audit verified
37 model identities, all 41 inventory-sized consumer bodies and the one Haybot
branch; the two attachment action headers/records and 34 instruction guards
were also rechecked. The 17 prior registry records remain unchanged.

Fresh isolated coverage contains 1,487 models, 10,394 material runs and 232,162
source faces: **37 reviewed names and 1,450 unknown**. Against the saved
17-model-stage report, exactly the 20 named keys above change from unknown to
reviewed. Every non-naming model field, material-run row, non-naming summary
and per-bank summary, evidence-availability field and other top-level evidence
field is identical. The six texture-manifest digests also agree. The naming
registry digest changes as intended. No model export, runtime-observation,
Blender-validation or extra scene-consumer manifest was supplied.

The combined integration checkpoint passes both complete 1,721-test suites
(37 host skips, one optional ROM-enabled pinned skip), independent review of
all 37 model pins and 41 full consumer spans, and fresh whole-corpus naming
invariance. Its separate C naming batch, full-ROM/game/rodata, progress and
whitespace gates also pass. The registry adds twenty named model identities
and no C matches.
