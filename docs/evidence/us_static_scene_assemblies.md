# Static ROM scene assemblies

The inspection gallery includes 18 composed scenes from the ROM-only bank-03
and bank-04 exports. These provide context for small parts and level fragments
without treating every fragment or variant as a useful standalone gallery entry.
The labels describe appearance; they are not recovered level names.

| Scene | Selection | Unique models | Instances | Triangles |
| --- | --- | ---: | ---: | ---: |
| 11 | Stone tower and platforms; overlapping surface layers and untextured triangle omitted | 13 | 14 | 2,658 |
| 23 | Industrial shafts; initial slots 0/1 and all 18 bank-0B placements | 20 | 20 | 4,575 |
| 25 | Domed lava chamber; runtime effect planes omitted | 11 | 11 | 2,888 |
| 26 | Industrial hub and passages; untextured effect surface omitted | 9 | 15 | 2,848 |
| 27 | Stone walkway network; runtime effect planes and untextured slot 2 omitted | 11 | 22 | 2,748 |
| 28 | Bridge and fortified doorway; colocated panel fragments omitted | 22 | 31 | 4,380 |
| 30 | Branching walkway network | 6 | 23 | 1,681 |
| 35 | Circular plaza and vine-covered columns | 17 | 19 | 3,616 |
| 41 | Forest cliffs, bridge and waterfall; colocated rock fragments omitted | 17 | 18 | 3,428 |
| 44 | Industrial shafts and tunnels; runtime effect planes and untextured slot 2 omitted | 11 | 22 | 3,904 |
| 46 | Mossy chamber with doors | 4 | 4 | 730 |
| 47 | Tiled room interior; runtime effect planes omitted | 8 | 11 | 1,216 |
| 49 | Stone chamber with steps; surface variant 14 retained | 15 | 20 | 1,514 |
| 50 | Lava course with rock platforms; runtime effect planes omitted | 11 | 19 | 2,750 |
| 53 | Stone cavern with circular platforms; plain-faced panel retained | 20 | 28 | 3,319 |
| 54 | Stone corridor; intact walls and unlit indicators | 9 | 18 | 1,815 |
| 67 | Lava chamber with central platform; untextured ring and wall surfaces omitted | 8 | 8 | 2,780 |
| 68 | Lava chamber with platforms | 7 | 7 | 926 |

Together they place 211 distinct ROM source models in 310 instances and expose
115 source records that remain deferred for standalone inspection. Each deferred
record's review note names its available scene assemblies. The inventory still
contains 1,487 extracted records; gallery totals count the 18 assemblies
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

The complete selection is tracked in `config/model-scene-assemblies.json`.
Sources with unresolved texture inputs, captured materials, skinning, morph
targets or unsupported material channels are rejected. Texture animations use
the existing exported static frame. No missing texture is guessed and no alpha,
mesh geometry or lighting is changed to make the assemblies look complete.

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
