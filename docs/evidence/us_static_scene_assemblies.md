# Static ROM scene assemblies

The inspection gallery includes 29 composed scenes from the ROM-only bank-03
and bank-04 exports. These provide context for small parts and level fragments
without treating every fragment or variant as a useful standalone gallery entry.
The labels describe appearance; they are not recovered level names.

| Scene | Selection | Unique models | Instances | Triangles |
| --- | --- | ---: | ---: | ---: |
| 0 | Cavern workshop and target fixtures; grate 15 selected, colocated untextured surface 13 and effect planes omitted | 12 | 22 | 1,815 |
| 2 | Lava caverns and stone structures; selected surface variants, repeated weights and unresolved fragments omitted | 24 | 39 | 4,624 |
| 6 | Spiral stone tower, meadow and ruins; barrier 30 selected, colocated parts and untextured effects omitted | 30 | 38 | 6,191 |
| 11 | Stone tower and platforms; overlapping surface layers and untextured triangle omitted | 13 | 14 | 2,658 |
| 12 | Windmill clearing and elevated platforms; complete animal head selected, colocated fragments omitted | 17 | 29 | 4,071 |
| 14 | Fortified courtyard, pipes and bridges; origin-positioned platform, beams and effect planes omitted | 13 | 17 | 3,170 |
| 23 | Industrial shafts; initial slots 0/1 and all 18 bank-0B placements | 20 | 20 | 4,575 |
| 25 | Domed lava chamber; runtime effect planes omitted | 11 | 11 | 2,888 |
| 26 | Industrial hub and passages; untextured effect surface omitted | 9 | 15 | 2,848 |
| 27 | Stone walkway network; runtime effect planes and untextured slot 2 omitted | 11 | 22 | 2,748 |
| 28 | Bridge and fortified doorway; colocated panel fragments omitted | 22 | 31 | 4,380 |
| 30 | Branching walkway network | 6 | 23 | 1,681 |
| 35 | Circular plaza and vine-covered columns | 17 | 19 | 3,616 |
| 36 | Circular stone arena; all recovered renderable placements | 9 | 35 | 4,152 |
| 40 | Curved green channel and grille; runtime effect planes omitted | 3 | 3 | 669 |
| 41 | Forest cliffs, bridge and waterfall; colocated rock fragments omitted | 17 | 18 | 3,428 |
| 44 | Industrial shafts and tunnels; runtime effect planes and untextured slot 2 omitted | 11 | 22 | 3,904 |
| 45 | Fortified courtyards and grassy passage; map easel selected, colocated tower and effect planes omitted | 25 | 41 | 4,178 |
| 46 | Mossy chamber with doors | 4 | 4 | 730 |
| 47 | Tiled room interior; runtime effect planes omitted | 8 | 11 | 1,216 |
| 49 | Stone chamber with steps; surface variant 14 retained | 15 | 20 | 1,514 |
| 50 | Lava course with rock platforms; runtime effect planes omitted | 11 | 19 | 2,750 |
| 51 | Lava channels, bridges and placed props; all recovered renderable placements | 5 | 13 | 2,498 |
| 52 | Tiered industrial yard; paired doors and isolated untextured surfaces omitted | 15 | 21 | 4,405 |
| 53 | Stone cavern with circular platforms; plain-faced panel retained | 20 | 28 | 3,319 |
| 54 | Stone corridor; intact walls and unlit indicators | 9 | 18 | 1,815 |
| 65 | Graveyard and water cavern; surface 11 selected, alternative 15, untextured panel 16 and effect planes omitted | 16 | 21 | 3,989 |
| 67 | Lava chamber with central platform; untextured ring and wall surfaces omitted | 8 | 8 | 2,780 |
| 68 | Lava chamber with platforms | 7 | 7 | 926 |

Together they place 356 distinct ROM source models in 589 instances and expose
169 source records that remain deferred for standalone inspection. Each deferred
record's review note names its available scene assemblies. The inventory still
contains 1,487 extracted records; gallery totals count the 29 assemblies
separately from 863 standalone exports.

## Sources and selection

The assembler decodes fresh ROM bank-04 bundles and both proven placement
tables through `load_object_placement_manifest`, then uses the
[reviewed scene consumer graph](us_model_scene_consumers.md). Initial slots
0–2 have conditional renderer edges and use identity transforms. Slot 3 has
only collision evidence and is always excluded. Object instances retain the
original placement bank, record index, raw record, position, YZX rotation and
scale. Vertex, index, UV, colour and image bytes come from the existing ROM-only
exports; the assembler relocates glTF references and instances meshes.

Scene 54 contains multiple damaged wall models at the same positions. Its
static inspection selection uses segment 6 and excludes segments 7–13. Indicator
states 14–20 likewise overlap: the selection uses unlit segment 14. Bank-03
model 51 produces large untextured effect planes whose runtime appearance is
unresolved, so those four instances are omitted. Every omitted instance and
its reason is retained in the generated manifest. Other bank-0C placements
remain included. This selection does not claim to reproduce an observed frame.

Scenes 25, 27, 44, 47 and 50 also omit the bank-03 model-51 effect planes.
Scenes 27 and 44 omit untextured initial slot 2: disconnected dark surfaces and
white vertical surfaces respectively require native appearance context. These
omissions are explicit inspection choices, not claims that the game never draws
those surfaces. The remaining placements in scenes 25, 27, 30, 44, 46, 47, 50
and 68 have no different model identities at identical placement matrices.
Front and rear renders show coherent structures, but this does not establish
that every selected object is simultaneously visible during gameplay.

Scene 28 omits colocated panel fragments 31–34, and scene 41 omits colocated
rock fragments 5–9: their fracture/visibility state is not established by the
placement records. Scene 53 retains plain-faced segment 4 and omits patterned
alternative 9. Scene 49 retains segment 14 and omits overlapping surface
variants 15/16. Scene 11 omits small overlapping layers 12/13 and untextured
triangle 15; scene 67 retains the textured head while omitting untextured
surfaces 10/11. The applicable bank-03 effect planes remain excluded.

Candidate assemblies 57 and 60 are not published. Their front and rear renders
show detached elevated geometry requiring conditional-visibility or placement
investigation. Their standalone source records remain available, with review
notes recording this assembly-level limitation.

Scene 45's bank-0B records 8 and 9 place map easel segment 12 and tower segment
13 at the same identity transform. Their control bytes differ (`...01f701...`
versus `...01f601...`), but the meaning and visibility condition are not proven.
The inspection selection retains only the easel. Scene 65 similarly retains
textured surface 11 instead of colocated alternative 15. Its untextured corner
panel 16 sits below the water and is omitted pending runtime appearance or
visibility evidence. Both scenes omit bank-03 effect model 51. The selected
object placements in each have no different model identities at identical
matrices. This check is limited to exact transforms, not a general overlap or
simultaneous-visibility proof.

Three-quarter and rear renders show coherent fortified courtyards in scene 45
and a connected graveyard/water-cavern structure in scene 65. The two assemblies
provide 62 instances and 37 previously unassembled source identities, including
12 otherwise deferred records. These descriptions are visual labels, not
ROM-proven level names. Candidate 10 remains held for loose geometry below the
floor, and candidate 20 for detached elevated arch pieces. Their source records
remain available without promoting either assembly.

The gallery IDs are `scene-45-assembly-rom` and `scene-65-assembly-rom`.
Their source identities are:

- Scene 45: bank-04 entry 45 segments 0, 1, 4–12, 14 and 15; bank-03
  entries 57–60, 62, 82–87 and 92 (segment 0).
- Scene 65: bank-04 entry 65 segments 0, 1, 4–14 and 17; bank-03 entries
  1 and 94 (segment 0).

The selections, component identities, held-candidate renders and decisions are
retained under `build/assets/models/reference/scene-review-20260915/`. The tracked
validation configuration keeps front and rear regression views of accepted
scenes 45 and 65. Regression baselines represent the reviewed static export;
they are not native game captures or native appearance evidence.

For these two scenes, fresh ROM placement decoding and byte recomposition,
Khronos source checks, Blender import and both regression views pass. The packed
GLBs also pass Khronos validation with zero errors and warnings, retaining all
source geometry and image bytes (165 embedded images for scene 45, 95 for scene
65). The final validation reuses all unchanged imports and renders; the eight
pre-existing incomplete appearance comparisons are unchanged. No extractor or
validation implementation changes were needed for these selections.

The complete selection is tracked in `config/model-scene-assemblies.json`.
Sources with unresolved texture inputs, captured materials, skinning, morph
targets or unsupported material channels are rejected. Texture animations use
the existing exported static frame. No missing texture is guessed and no alpha,
mesh geometry or lighting is changed to make the assemblies look complete.

## Arena and industrial-yard selections

Scene 36 includes initial slot 0 and all recovered object placements. It uses
bank-04 entry 36 segments 0/4 and bank-03 entries 70–72, 80, 81, 88 and 95.
The 35 instances form a circular stone arena in three-quarter and rear views.
The label is descriptive, not a recovered level name. Segment 4 remains deferred
as a standalone duplicate; its ROM identity and placements are preserved here.
The gallery ID is `scene-36-assembly-rom`.

Scene 52 uses bank-04 entry 52 segments 0/6/7 and bank-03 entries 57–62,
82, 83, 86, 87, 92 and 94. The selected 21 instances form a tiered industrial
yard. It omits untextured bank-03 effect model 51, bank-03 surface 113, and
bank-04 segments 8–10 pending runtime appearance or visibility evidence.
The gallery ID is `scene-52-assembly-rom`.

Bank-0B records 0–5 pair scene-52 door segments 4/5 at three equal transforms.
Equal transforms are insufficient to call them alternatives: the vertices of
segment 4 extend to local Z=-209 and segment 5 to Z=211, from a shared origin.
Their control bytes differ, but complementary versus conditional visibility is
unresolved. Both members of all three pairs are omitted, with explicit reasons;
no door is repositioned and no model geometry is edited. The retained object
placements have no different model identities at identical matrices. This is
not proof of simultaneous gameplay visibility.

These two assemblies add 56 instances and ten previously unassembled source
identities, including one otherwise deferred source. Fresh ROM placement
verification, byte recomposition, Khronos checks and Blender imports pass.
Three-quarter and rear views were reviewed; the packed GLBs have zero Khronos
errors or warnings and retain the source geometry and image bytes. Native
lighting, fog, animation and conditional visibility remain unresolved.
Local decisions, door-coordinate evidence, validation and render records are
under `build/assets/models/reference/scene-review-20260916/`.

## Tower/meadow and fortified-courtyard selections

Scene 6 uses bank-04 entry 6 segments 0/1, 4–10, 12–27 and 30,
and bank-03 entries 1, 3, 98 and 102. The 38 instances form a spiral stone
tower, meadow and ruins in three-quarter and rear views. Its gallery ID is
`scene-06-assembly-rom`.

Bank-0B records 24–26 place barrier segments 28/29/30 at the same transform.
The inspection selection retains segment 30 and omits 28/29. The two omitted
meshes total 30 triangles, as does segment 30, but neither their vertex attributes
nor their oriented position-triangle sets match. This is an explicit overlapping
variant selection, not a proven byte-identical union or native visibility rule.
Colocated segments 7/8 form different water surfaces, and segments 24/25 have
different local shapes; both pairs remain selected. Bank-03 untextured models
51 and 97 are omitted pending appearance or visibility evidence.

Scene 14 uses bank-04 entry 14 segments 0/1, 4/5 and 8–15, and bank-03
entry 3. The 17 instances form a fortified courtyard and bridges. Its gallery ID
is `scene-14-assembly-rom`. Platform segment 6 and four identical segment-7
beam placements are stored at the origin. Their runtime placement or visibility
is unresolved, so they are omitted along with bank-03 effect model 51. Water
surface 11 has distinct world-space geometry and remains selected. Both scenes
exclude collision-only initial slot 3. Labels are visual descriptions, not
ROM-proven level names.

These selections add 55 instances and 40 previously unassembled source
identities, including 15 otherwise deferred components. Fresh ROM placement
verification and byte recomposition pass, as do source Khronos checks, Blender
imports, and the reviewed three-quarter/rear regression views. Packed GLBs
have zero Khronos errors or warnings and preserve component geometry and image
bytes. Regression baselines describe the static exports, not native captures.
Conditional visibility, animated placement, lighting, fog and exact native
appearance remain unresolved. Local decisions, barrier comparison, packed-file
validation and renders are retained under
`build/assets/models/reference/scenes-06-14-20260916/`.

## Lava-cavern and windmill-clearing selections

Scene 2 uses bank-04 entry 2 segments 0/1, 4–8, 10/11, 13/14,
16–18, 23–25 and 27–32, plus bank-03 entry 3. Its 39 instances form lava
caverns and stone structures. The gallery ID is `scene-02-assembly-rom`.
The inspection selection retains structure 10 instead of colocated variant 9,
green surface 11 instead of 12, and rock 14 instead of 15. These are explicit
static choices; the native state-selection rules remain unresolved.

Colocated door halves 17/18 both span local X=0–50 and Y=1–205, but their
Z ranges are -128–0 and 0–128. Both remain selected because equal placement
matrices alone do not prove alternatives. Colocated panel/fragments 19–22
are omitted pending state evidence. Two segment-26 weight assemblies occupy
the same transform; both remain omitted pending runtime placement or visibility.
Isolated untextured surfaces 33–37 also remain omitted.

Scene 12 uses bank-04 entry 12 segments 0/1, 6–13 and 25–30,
plus bank-03 entry 3. Its 29 instances form a windmill clearing with wooden
fixtures. The gallery ID is `scene-12-assembly-rom`. Nineteen placements of
animal fragments 14–24 and complete head 25 share the transform at
(751, 146, -1384). The selection retains only head 25; fragment motion and
conditional visibility remain unresolved. Segments 6/30 share an identity
transform but occupy different local regions, so both remain selected.
Both scenes omit bank-03 effect model 51 and collision-only initial slot 3.
Names are visual descriptions, not recovered level names.

Together these scenes add 68 instances and 39 previously unassembled source
identities, including 19 otherwise deferred components. Fresh ROM placement
verification and byte recomposition, source Khronos checks, Blender imports,
and reviewed three-quarter/rear regression views pass. Packed GLBs have zero
Khronos errors or warnings and preserve source geometry and image bytes.
Native visibility, animated placement, lighting, fog and exact appearance remain
unresolved. Local placement records, bounds, decisions, packed validation and
renders are under `build/assets/models/reference/scenes-02-12-20260916/`.

## Cavern-workshop selection

Scene 0 uses bank-04 entry 0 segments 0/1, 4/5, 8–12, 14/15, plus
bank-03 entry 3. Its 22 instances form a cavern workshop and target fixtures
in three-quarter and rear views. The gallery ID is `scene-00-assembly-rom`;
the label is a visual description, not a recovered level name.

The inspection selection retains grate 15 instead of colocated untextured dark
surface 13. Bank-03 effect model 51 and collision-only initial slot 3 are
excluded. Model geometry, materials and ROM placement transforms are unchanged.
This is an explicit static selection, not proof of simultaneous native visibility.

The assembly adds eleven previously unassembled source identities, including
four otherwise deferred sources: `04:0000:01`, `04:0000:10`, `04:0000:11`
and `04:0000:14`. Fresh ROM placement verification, byte recomposition,
Khronos source checks, Blender import and both regression views pass. Its packed
GLB has zero Khronos errors or warnings and preserves source geometry and image
bytes. Native lighting, fog, animation and exact appearance remain unresolved.

Candidate scene 18 remains unpublished. Its main room `04:0018:00` has
41 untextured faces across two runs and prominent white surfaces in the
assembled view. Omitting untextured segments 2/11/12 and mixed textured/untextured
platform `03:0049:00` does not remove the main-room appearance question.
The candidate's placement and packed-file checks pass, but these do not prove
its effective appearance. No texture, colour or opacity override is applied.
Candidate renders, omissions, packed checks and accepted-scene validation are
retained under `build/assets/models/reference/scenes-00-18-20260916/`.

## Scenes 40 and 51: channel surfaces and placed props

`scene-40-assembly-rom`, **Curved green channel and grille — static ROM scene
40**, combines `04:0040:00`, `04:0040:06` and `04:0040:07`: three instances,
669 triangles. Segment 7's green surface follows the curved room and channel;
segment 6 uses bank-0B record 0's placement `(1805, -10, -1873)`. Bank-03
effect model 51 and collision-only initial slot 3 are omitted.

`scene-51-assembly-rom`, **Lava channels, bridges and placed props — static ROM
scene 51**, combines `04:0051:00`, `04:0051:01`, `04:0051:04`, `03:0100:00`
and `03:0101:00`: thirteen instances, 2,498 triangles. Initial slots 0/1 supply
terrain and lava surfaces; bank-0B supplies four segment-4 placements; bank-0C
supplies three twin-canister and four missile props. Collision-only initial
slot 3 is omitted. No colocated alternative group occurs in either selection.

These assemblies add eight previously unassembled source identities and expose
three additional deferred sources in context: `04:0040:07`, `04:0051:01` and
`04:0051:04`. Standalone deferral remains unchanged. Both labels are visual
descriptions, not ROM-proven level names. Geometry, textures, culling and
placement transforms are retained; static inclusion does not establish native
visibility, animation, lava motion, lighting, fog or pixel parity.

Fresh ROM placement checks, byte recomposition, glTF checks, Blender import and
three-quarter/rear regression views pass. Both packed GLBs have zero Khronos
errors and warnings. Candidate views, selections, source fingerprints, packed
checks and publication preservation checks are retained under
`build/assets/models/reference/scenes-40-51-20260916/`.

## Reproduction and publication

```sh
./conker model-assets scene-assemblies
./conker model-assets validate
./conker model-assets inspect
```

The first command writes `build/assets/models/rom-scene-assemblies/`. Validation
compares the scene inputs to a fresh ROM decode and recomposes every output byte
from its component sources. Existing ROM geometry/material checks cover those
sources. The assembly glTFs also receive Khronos and Blender checks and deterministic
render comparisons. Inspection publication requires current validation of the
assembly manifest, recomposes the source again and embeds the unchanged buffers
and images into GLBs.

Gallery publication recomposes each assembly set once during preparation and
once again in its independent final phase, sharing that result across entries
in the same set. It discards preparation evidence before the final gate and
checks manifest hashes on every lookup. Component or placement changes during
packaging still prevent publication; no verification result persists between
commands. Focused tests cover this reuse and the changed-input rejection.

Focused regression checks cover nonuniform placement transforms, collision-slot
exclusion, explicit alternative selection, unresolved consumers, modified scene
nodes and changed ROM placements. Native visibility, animation, render order,
combiner behaviour, lights and fog remain separate appearance work.

Packed GLBs retain the original component triangles, even where Blender removes
exact duplicate triangles during import. Publication checks the final GLBs and
preview hashes as well as the source glTFs. The validator retains eight unrelated
incomplete appearance comparisons.
