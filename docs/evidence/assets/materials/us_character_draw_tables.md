# Character primary and secondary draw tables

Thirty-one bank-01 characters contain both primary and secondary display-list
pointer tables. The native renderer selects one table per invocation. Earlier
ROM-default previews concatenated them, allowing duplicate, often untextured
secondary geometry to obscure the ordinary textured character.

`func_1503CF20` installs the model header pair at offset `0x08` into
`D_800C4488[model]` and the pair at `0x28` into `D_800C48F0[model]`.
`func_1502CCFC` compares its rendering mode with three at `0x1502D3C0`:
mode three uses `D_800C48F0`, while the other branch uses `D_800C4488`.
An absent secondary table produces no secondary draw. The actor's part mask
at offset `0x94` separately controls individual parts.

`scripts/model_character_parts.py` verifies the complete 1,096-byte loader
and 2,128-byte renderer against the validated US ROM. It bounds each declared
list through EndDL, rejects aliases and overlaps, and requires every decoded
triangle command to belong to exactly one declared list. It selects all primary
parts for ROM-default previews, retaining source vertex indices, material-run
indices, command offsets, joints, normals and face-culling state. The 31 models
exclude 10,502 secondary triangles from their ordinary previews.

Raw extraction retains both tables. Captured render corpora and submitted-pose
comparisons keep their existing contracts. ROM-default glTF files record the
selection and original triangle indices under `romCharacterDrawPass`;
validation repeats the selection from fresh ROM data and checks both bind and
animated exports against every source corner. This is evidence for table
selection, not a claim that every actor part is visible in every game scene.

The corrected previews reveal coherent winged imps, a green dinosaur, the
hooded skeleton, female squirrel variants and several vampire forms without
using captured vertex buffers, textures or visibility masks. Native lighting,
runtime part visibility, environment colours and exact raster output remain
separate appearance questions.
