# US model review selections

The inspection gallery separates useful standalone exports from the remaining
source records in **Extracted review**. Selection is an inspection decision,
not a claim of native visual parity. Geometry and textures come from the ROM;
no external models or capture textures supply these selections.

## Standalone selections

These sources have complete current material coverage and coherent front and
rear views. Labels are descriptive identifications from the extracted appearance;
they do not establish gameplay names, attachment parents or runtime visibility.

| ROM source | Inspection label | Scope |
| --- | --- | --- |
| `03:0064:00`, `03:0065:00` | Dark wooden door panels | Separate leaves; room and placement unknown |
| `09:0042:00` | Toilet-paper roll | Single prop |
| `09:0075:00` | Flashlight | Parent and use unverified |
| `09:0083:00`, `09:0118:00` | Scalpel and bloodied scalpel | Explicit surface variants; attachment poses unverified |
| `04:0019:15` | Circular metal dish | Function and orientation unverified |
| `04:0004:11`, `04:0004:13`, `04:0004:14` | Crossed steel barriers | Explicit geometry variants; placements unverified |
| `04:0064:21` | Red padded chair | Scene placement and runtime assembly unverified |
| `04:0059:00` | Cavern terrain base | One segment; scene 59 segment 23 remains material blocked |
| `04:0038:00` | Curved room section | One segment; other scene components remain separate |

The 13 source records are selected in
[model-inspection.json](../../config/model-inspection.json). Their render cases
in [model-validation.json](../../config/model-validation.json) use the reviewed
three-quarter images as regression references. A matching regression establishes
repeatable export presentation, not agreement with the game. Rear renders and
local comparison sheets are ignored review artifacts under
`build/assets/models/reference/review-promotions/`.

## Character names from visual references

Five existing bank-01 exports now use their visually identified N64 character
names. Their previous descriptions remain searchable aliases. These names are
appearance-based identifications, not recovered ROM symbols or proof of a
particular runtime consumer; the gallery records that distinction and links each
reference. Geometry, materials, animation data and native-parity status are
unchanged.

| ROM source | Gallery name | Previous description | Visual evidence |
| --- | --- | --- | --- |
| `01:0049:00` | [Monk Gobling](https://conker.fandom.com/wiki/Monk_Gobling) | Turtle character | Short yellow figure wearing a red hooded robe |
| `01:0120:00` | [Wasp Larva](https://conker.fandom.com/wiki/Wasp_Larvae) | Green horned creature | Green segmented body, yellow eyes and large tusk-like jaws |
| `01:0142:00` | [The Grotesque (Gargoyle)](https://conker.fandom.com/wiki/The_Grotesque) | Stone creature | Grey stone body, wings, horns and red eyes |
| `01:0147:00` | [Sweet Corn](https://conker.fandom.com/wiki/Sweet_Corn) | Yellow rounded character | Yellow kernel body with large eyes |
| `01:0181:00` | [Bartender](https://conker.fandom.com/wiki/Bartender) | Muscular squirrel | Muscular grey squirrel with a white waistcoat, dark buttons and moustache |

The supporting contact sheet and source/hash audit are ignored local artifacts
under `build/assets/models/reference/character-discovery-20260913/`. All 183
bank-01 records passed `./conker model-assets verify --bank 01`; this establishes
ROM-byte provenance, independently of these visual names. These five records were
already in the Characters tab, so naming them does not increase export counts.

## Matching and similar exports

The current review configuration identifies 31 deferred records with the same
exported presentation as an existing curated entry. The comparison replaces
external buffer and image URIs with hashes of their actual bytes, ignores `asset`,
object names and diagnostic `extras`, and compares all remaining glTF fields.
This retains geometry, indices, transforms, materials, texture samplers, skins
and animations. It does not compare gameplay consumers or dynamic native state.
Each review reason names the matching curated entry; the separate ROM source
record and downloadable GLB remain available.

Other complete-looking props are similar without being byte-identical exports.
Review notes distinguish these from matching exports: the knives, syringe,
brush, cigarette holder, helmet, roller, boulder, column and reinforced door
retain their source identities for attachment, placement or state comparisons.
Unidentified surfaces and meshes retain concrete descriptions of the remaining
assembly or identity question. Decisions in
[model-batch-reviews.json](../../config/model-batch-reviews.json) bind the source
fingerprints; changed source inputs reopen review.

## Remaining work

Use parent, placement and effect consumer evidence to distinguish runtime roles
for similar exports. Review whole scene selections before combining pieces;
individual terrain segments are not complete assembled levels. Keep material,
visibility, lighting and animation uncertainty explicit when promoting further
standalone models.
