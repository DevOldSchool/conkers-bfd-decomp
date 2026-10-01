# US bank09 UI constructor materials

`scripts/model_ui_materials.py` derives the bounded initial material state from
normalized US ROM SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. It uses UI
constructor and renderer evidence independently of the specialized165/185
consumer contexts.

## Consumer proof

`151EB06C` calls `151ED90C` for entry 164/animation23 at `151EB5BC` and saves
the result to `80090058`; entry 162/animation8 follows at `151EB5D8`, saved to
`8009005C`. Both globals are zero in ROM initialization data. Later calls at
`151EB714` and `151EB754` pass these pointers to renderer `151EDBDC`.

Constructor `151ED90C` routes the model identifier through `1503F62C` and
`1502FE10`, the existing proven bank09 attachment loader. It copies each model
display list into an allocation. For each EF command, `151EDAF8–151EDB00` clears
word0 bit 16 and replaces word1 with `005041C8`. For each FC command,
`151EDB04–151EDB0C` clears word0. The renderer calls the checked setup list
`80090110`, then emits combiner `FC12FE25 FFFFFBFD` at `151EDD48–151EDD58`
before submitting the copied lists at `151EDEFC–151EDF08`.

For the `80090058` instance only, `151EDE38–151EDED8` decrements byte+15,
reloads a zero counter to `(rng & 127) + 15`, selects flat1287 below 7 and 1288
otherwise, loads it with `1510D0EC` and binds the same returned pointer to
segments 6 and 7. The constructor initializes the byte to1, so its first draw
always reloads 15–142 and selects 1288. This does not claim later frames remain
1288. Both payloads are pinned and independently decoded;1287 is retained as
later-state evidence only. Model164's commands select pixels at offset 0 and the
inline CI8 palette at offset 2048. Their layout agrees with both 2560-byte
payloads. No palette resemblance or adjacency heuristic is used.

The module pins seven complete function bodies, 60 exact instructions, the two
initial globals and setup display list, both complete model payloads and both
blink payloads. It refuses modified source geometry, unsupported inherited
state, changed runtime binding pairs, and changed payloads. It skips the whole
UI rewrite when any captured material is supplied for the model.

## Active integration

The bank09 context loader authenticates the UI consumers and rejects overlapping
model identities. The copied-list state is applied before zero-area omission and
ordinary texture decoding, while source geometry is retained separately.
Captured materials bypass the complete rewrite. The UI context is excluded from
ordinary segment 8 consensus. `rom_ui_material_state` and glTF
`romUiMaterialState` retain the source proof; UI-skinned models identify the
actual UI renderer and neutral/source-only transform scope rather than generic
attachment-renderer claims.

## Verification

Targeted unit tests cover CLI/package dataclass equivalence without relaxing
complete field checks and glTF evidence propagation. Mutations cover every
context field and integer type, model/texture identity, geometry changes
retaining the same counts, copied EF/FC semantics, segment selection, initial
counter/RNG mask, palette pairing, partial state and captured-material
precedence. Guard-specific mutation tests regenerate only their synthetic
fixture body hashes, proving instruction checks reject the mutations
independently of the whole-function check.

The source scope is entry 162:108 faces, including 20 target faces (runs
2/5:8+12), and entry 164:65 faces, including 29 target faces (runs 5/6:15+14).
All173 source faces have decoded textures under this context. The model 164
first-draw 1288 binding and later1287 alternative remain distinct.

```sh
./conker model-assets preview --bank 09 --rom roms/baserom.us.z64 \
  --output build/assets/models/us-bank-09
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_ui_materials.py'
```

These commands require no capture, live UI or Blender input.

The native combiner uses RGB=TEXEL0×ENVIRONMENT and alpha=ENVIRONMENT. The PNG
retains source texel alpha. Dynamic environment opacity, visibility, projection,
native animation/transforms and raster parity remain unresolved; this context
establishes copied texture state and stored geometry, not a complete native UI
appearance.

Independent emitted-geometry comparisons cover all 173 faces and 519 UV/joint
corners. Geometry, UV and rig binary buffers must remain unchanged through the
material update. Full-bank export totals are not part of this isolated proof;
regenerate them for the current exporter.
