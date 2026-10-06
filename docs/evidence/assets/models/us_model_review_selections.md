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
| `09:0029:00` | Cigar | Attachment action 68; paired creation with helmet action 35; actor identity and pose unverified |
| `09:0228:00` | Green and yellow starburst | Stored effect mesh; gameplay use and native effect behavior unverified |
| `09:0288:00` | Grey lower leg with pink shoe | Stored detached part; actor identity and runtime pose unverified |
| `09:0401:00` | Grey lower leg with black shoe | Stored detached part; actor identity and runtime pose unverified |
| `09:0404:00` | Dark lower leg with broad black boot | Stored detached part; actor identity and runtime pose unverified |
| `04:0060:14` | Corner cobweb | Stored scene prop; native visibility and scene-60 composition remain unresolved |
| `09:0042:00` | Toilet-paper roll | Single prop |
| `09:0075:00` | Flashlight | Parent and use unverified |
| `09:0112:00` | Hexagonal dumbbell | Capped weights and handle; parent and use unverified |
| `09:0083:00`, `09:0118:00` | Scalpel and bloodied scalpel | Explicit surface variants; attachment poses unverified |
| `04:0019:15` | Circular metal dish | Function and orientation unverified |
| `04:0004:11`, `04:0004:13`, `04:0004:14` | Crossed steel barriers | Explicit geometry variants; placements unverified |
| `04:0064:21` | Red padded chair | Scene placement and runtime assembly unverified |
| `04:0059:00` | Cavern terrain base | One segment; scene 59 segment 23 remains material blocked |
| `04:0038:00` | Curved room section | Source retained; its assembly is now the gallery download |

These 20 source records are selected in
[model-inspection.json](../../../../config/model-inspection.json). Their render cases
in [model-validation.json](../../../../config/model-validation.json) use the reviewed
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
record and GLB remain in the export manifest. Nine of these records are already
represented in assemblies; the other 22 now share the existing curated card and
download. Their original names, ROM IDs and filenames remain searchable.

Other complete-looking props are similar without being byte-identical exports.
Review notes distinguish these from matching exports: the knives, syringe,
brush, cigarette holder, helmet, roller, boulder, column and reinforced door
retain their source identities for attachment, placement or state comparisons.
Unidentified surfaces and meshes retain concrete descriptions of the remaining
assembly or identity question. Decisions in
[model-batch-reviews.json](../../../../config/model-batch-reviews.json) bind the source
fingerprints; changed source inputs reopen review.

## Remaining work

Use parent, placement and effect consumer evidence to distinguish runtime roles
for similar exports. Review whole scene selections before combining pieces;
individual terrain segments are not complete assembled levels. Keep material,
visibility, lighting and animation uncertainty explicit when promoting further
standalone models.

## Dumbbell and represented scene components

`09:0112:00` is promoted as **Hexagonal dumbbell** after three-quarter and rear
review. All 62 faces use the existing CI8 flat-1341 material; its 32 x 32 image
uses the palette at byte 1,408 of the 1,920-byte payload. A fresh US ROM decode
reproduces the current glTF, binary buffer and PNG exactly. Model SHA-1 is
`8106c82ce82f846d644a2ca42f1cdaf07069aff1`. Canonical glTF comparison against the
prior 896 curated records found no matching presentation or geometry buffer.
The descriptive name does not establish its attachment parent or gameplay use.

The gallery now consolidates 221 deferred source-component cards into its
44 scene assemblies. The earlier checkpoint had 180 represented records across
36 assemblies; scenes 4, 16 and 19 added 23 represented components, followed by
16 more in scenes 1, 56, 58 and 64 and two in scene 10. The source records,
standalone deferral decisions, geometry, materials and unresolved native
appearance remain intact. This is representation of existing extracted sources,
not 221 newly recovered models or a claim that all native behavior is complete.

Links are derived after the publisher's fresh final provenance check. Each
component must match the current review source's ROM identity, path, dependency
fingerprint, nested ROM evidence and face count. Only drawable, material-complete,
currently deferred records qualify. Conflicts stop publication; changed review
inputs, blockers, omitted components and hidden targets cannot hide a source card.
A source can retain multiple containing assemblies. Its original label, ROM ID
and review filename are searchable on every containing assembly.

The manifest retains `review_count` for all physical review exports and adds
`gallery_review_count` and `represented_review_count` for the visible and
represented subsets. Runtime material, visibility, lighting and animation work
remains separate. Local review evidence is under
`build/assets/models/reference/review-resolution-20261001/`.

## Equivalent exported presentations

The 31 documented comparisons were rechecked against current validated sources,
review fingerprints and published files. Explicit `presentation_equivalent_to`
metadata is bound to each existing review decision. Changed fingerprints reopen
review and cannot carry an equivalence link forward. After final ROM provenance
checks and assembly representation, the publisher compares still-visible eligible
sources with their named visible ordinary curated targets.

Canonical glTF documents are compared directly, with exact buffer/image bytes.
Only top-level `asset`, names and diagnostic `extras` are ignored. Geometry,
indices, transforms, materials, samplers, skins, animations and array order remain
significant. Unsupported extensions do not qualify. A changed source, target or
claimed equality stops publication; blocked and empty records remain visible.
The derived `gallery_equivalent_to` and `equivalent_review_count` fields are
separate from scene-containment metadata. Source ROM provenance, review status
and native-appearance limits remain intact.

The previous pass consolidated 25 duplicate presentations. Together with scene
55's three newly represented components, it reduced visible review from 449 to
421 without deleting any of its then-622 source exports. It does not establish
shared gameplay consumers, placements or native dynamic state. The independent
pair audit is under
`build/assets/models/reference/review-next-20261001/equivalents/`.

## Cigar and further scene context

`09:0029:00` is now selected as **Cigar** in Parts & effects. Its 20 faces use
one 16 x 32 CI8 flat-806 texture: 512 pixel bytes followed by a 512-byte palette.
Fresh normalized-ROM decoding reproduces the existing glTF, binary buffer and
PNG exactly. Source model SHA-1 is `48ddf0a838a1d41c2bf79ae90b00f02e512bc684`.
Canonical comparison against the prior 899 curated exports found no identical
presentation or geometry buffer. Front and rear 768-pixel views show a coherent
brown cigar and pale tip; the descriptive label does not establish smoke, actor
identity, attachment pose, visibility or native shading.

ROM action 68 has header `80086EDC`, pointing to the record at `8009D1F0`:
`1D0C000100000000000000000000000000`. It selects attachment 29 on slot 12.
The independently pinned 72-byte caller `1514DCAC` creates military helmet
action 35, then action 68, with the same parent. Its SHA-1 is
`39365f94e0a7a6b0bfa482f77edee0c0c042b57b`. This is constructor context, not
proof of a particular actor or gameplay state. Packed GLB validation has zero
errors or warnings. The previous review label, filename and ROM ID remain
searchable on the new card; the old review files remain intact.

In the earlier cigar/scene checkpoint, scenes 7 and 48 additionally represented
four previously visible deferred components. Visible review decreased from 421 to 416;
its then-621 source exports retained 180 scene-represented records, 25 equivalent
presentations and the remaining visible records. Review status and native
appearance remain separate from gallery representation. Other examined props
remain deferred where they are near variants or lack a useful identification.
That checkpoint's local evidence is under
`build/assets/models/reference/review-followup-20261001/`.


## Further parts, cobweb and recovery UI integration

The four new bank-09 Parts & effects selections are recognizable stored meshes,
not arbitrary fragments renamed to clear the queue. Their source evidence is:

| ROM source | Faces | Flat assets | Source model SHA-1 |
| --- | ---: | --- | --- |
| `09:0228:00` | 20 | 1859, plus an untextured run | `c4179203e2a8aacf57763b5cb4b5d9dead1a463e` |
| `09:0288:00` | 23 | 7759, 3714, 7751 | `65b15358e81e6e3ca4ee0dd800a45b0c02dce13e` |
| `09:0401:00` | 22 | 3714, 1358, 4211 | `0ff72a313444a3d212466a2f417a283c8580d697` |
| `09:0404:00` | 22 | 3714, 1358, 1363 | `272a45b11470db955a6036d69b188973b28e3ab3` |

Fresh ROM decoding reproduces each glTF, geometry buffer and strictly decoded
PNG byte-for-byte. Canonical comparison against the preceding 902 curated
exports finds no identical presentation or geometry buffer; nearby published
limbs also have different positioned triangles. Front, rear and three-quarter
768-pixel renders show distinct shapes/materials. Packed GLBs have no Khronos
errors, warnings or informational findings. Their model-table selectors at
`800A3880` are respectively 14, 173, 156 and 159; those lookup entries establish
model selection, not actor identity, motion, lighting, opacity or native parity.

**Corner cobweb** (`04:0060:14`) has eight triangles, 24 vertices and four IA8
flats 4172–4175. Its source SHA-1 is
`5d1bb62cf34a01815279eb674aeaca405bc4c1ff`. Fresh ROM decoding reproduces the
glTF, buffer and PNGs exactly, and the packed GLB has no Khronos findings.
It differs from the existing scene-19 web, which uses flats 5715/5716. Scene-60
segment 15 contains a seven-web layout using the same four textures; it remains
scene-context evidence. Promoting the single cobweb does not approve the held
scene-60 assembly or establish native visibility.

The same audit preserves specific holds for near variants, including the
riveted strip `09:0280:00`, green leaf `09:0418:00`, shard/grass effects
`09:0378:00` and `09:0379:00`, and the footbridge `04:0007:12`, which resembles
the bank-03 bridge design already included in scene 7. Visual similarity does not qualify for
a presentation-equivalence link. The systematic bank-04 audit records all 222
then-visible rows, verifies their source/preview fingerprints and rechecks the
three complete ROM consumer hashes. Its 38 slot-3 rows have collision-input
edges only in the reviewed graph; this bounded evidence is not a universal
no-render assertion. Scene-54 indicator states 14–20 share one exact placement
each and remain a source-linked variant-set lead, with no invented playback.

The UI material implementation and its evidence were reused verbatim from
recovery commit `4f80ae55eeb322a170837319257ed0ab9da58c97`; this branch does not
claim a new UI discovery. Entries `09:0162:00` and `09:0164:00` regain 20 and 29
ROM-only texture-linked faces respectively, including the cash bundle eyes.
All 460 other bank-09 model records and all geometry/UV/joint buffers are
unchanged. Captured-material precedence is preserved. The first blink state is
explicit; native environment opacity, animation, projection, transforms and
raster parity remain unresolved. See [the reused UI evidence](../materials/us_ui_constructor_materials.md).

At the completed five-prop and scenes 4/16/19 checkpoint, the manifest retained
910 curated exports (871 standalone, 39 assemblies) and 616 physical review
sources. That checkpoint had 899 curated cards and 388 review cards: 203 review
sources were represented in assemblies and 25 had equivalent presentations.
Eleven curated base cards were replaced by assemblies. Underlying review still
contained 587 deferrals, 26 material blockers, one appearance blocker and two
empty records; 359 deferrals remained individually visible. Separately, the
curated frontier retains 43 unresolved texture faces across Haybot (24), entry
183 (13) and entry 167 (six). Gallery counts do not measure every remaining defect.

Ignored reproducible evidence is under
`build/assets/models/reference/review-completion-20261001/props/`, its `bank04/`
subdirectory, and the sibling `ui/` and `scenes/` directories. No decoder bounds,
source orientation, alpha, geometry or unresolved native state were relaxed to
publish these selections.

## Further scene selections

Scenes 1, 56, 58 and 64 add 16 represented deferred records: respectively
`04:0001:01/02/04/06/07/08/11`, `04:0056:10`, `04:0058:01/04` and
`04:0064:04/05/06/07/09/10`. Each containing assembly replaces its former base
card and keeps the source labels and filenames searchable. The visibility audit
checks initial singleton groups through the native candidate-list consumer;
it does not promote omitted variants or claim a complete gameplay frame.
The [scene evidence](us_static_scene_assemblies.md#scenes-1-56-58-and-64-initial-visibility-evidence)
records source preservation and the exact selection boundaries.

Scene 10 subsequently represents `04:0010:21/22`, with its prior below-floor
hold resolved by verified initial inactivity and singleton visibility groups.
The assembly preserves all 1,953 exported triangles; its 14 repeated-index
Blender import difference is explained in the [scene-10 proof](us_static_scene_assemblies.md#scene-10-metal-chamber-with-pipes-and-stairs).

At the 44-assembly checkpoint, before the later bank-09 material fixes and
selected embedded inspections, the manifest retained 915 curated exports
(871 standalone and 44 assemblies) plus 616 physical review sources. The
gallery had 899 curated
cards and 373 review cards, or 1,272 total: 221 review sources are represented
in assemblies and 22 are separately consolidated by equivalent presentations. Sixteen curated base cards
were replaced by assemblies. Underlying review then comprised 587 deferrals,
26 material blockers, one appearance blocker and two empty records; 344
deferrals remained individually visible. Those assembly changes preserved
source status and bytes and did not resolve the separate curated material or
native-appearance frontier. Later material and inspection updates are recorded
below and in the [current roadmap](../../../asset-roadmap.md).

Three of the newly represented records, `04:0064:05/06/07`, already shared
curated cards through equivalence to `04:0058:05/06/07`. Assembly representation
is applied first, so their final gallery links move into scene 64 and the
separate equivalent count falls from 25 to 22. The last five assemblies add
18 represented components but reduce visible review by only 15, from 388 to
373. No previously consolidated record becomes visible, and this presentation
transition changes neither source bytes nor review status.


## Specialized bank-09 consumer fixes, 2 October 2026

Reused the exact guarded material helpers from recovery revision
`4f80ae55eeb322a170837319257ed0ab9da58c97`; the existing strict UI proof checks
remain in the validator. Fresh ROM export and independent CI4/CI8 palette
expansion verify 69 newly textured faces across eight runs. All 462 geometry
binaries and 458 unrelated model records remain identical in each of the three
corpora. Two rendered views of each changed source were inspected before its
regression references were accepted.

| Source | Reviewed result | Remaining appearance scope |
| --- | --- | --- |
| `09:0165:00` | Upright cash attachment variant, all 65 faces textured and pupils visible | Native pose, visibility, dynamic colours and opacity |
| `09:0185:00` | Conker HUD head, first correlated texture phase; all 112 texture-sampling faces linked | Stored geometry only; HUD deformation, active phase, colour/opacity and native raster output |
| `09:0203:00` | Fiery particle polyhedron, all 20 faces textured through its initial type-16 consumer | Particle motion, lifetime, draw colour/opacity and activation |
| `09:0213:00` | Tapered yellow spike, four faces textured through stored-script selector 13 | Scene activation, placement, later flags, opacity and native raster output |

Entry 185's other 58 faces use `FCFFFE8F/F517F8FF`, with SHADE,
ENVIRONMENT, K5 and PRIMITIVE inputs and no TEXEL input. They retain colour-state
uncertainty, not a missing-image claim. The specialized helper's raw status
`external-runtime-texture` is retained as source metadata; review uses the
actual combiner inputs.

Entry 165 has the same standard glTF geometry, rig and exact image bytes as
entry 164. Their alpha modes differ (MASK versus BLEND) because their native
consumers differ, so they are not declared fully presentation-equivalent. Both
validated exports remain in the manifest; the existing upright-cash card
represents the attachment variant too, keeping one card and one visible download.
The variant source ID and filename remain searchable there. No runtime identity
or universal alpha state is inferred from the common stored geometry.

The former `01:0066:00` stationary-tank wording was incorrect. The pinned
`150EE018` instruction is `24010028`, selecting decimal model 40; model 119 also
shares that handler. Model 66's purple flamethrower imp appearance remains under
investigation and its export is unchanged.
