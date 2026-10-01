# US specialized bank09 texture consumers

`scripts/model_special_attachment_materials.py` derives bounded texture bindings
from normalized US ROM SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. The
specialized165/185 consumers are independent of the UI162/164 contexts.

## Exact scope and result

Entry165 has65 stored faces,89 vertices,9 neutral joints and 8 runs. Runs5/6
(first faces 32/47, counts 15/14) are the only added bindings. Both use flat1288
as64x32 CI8 with their inline palette at 2048. All65 faces then decode.

Entry185 has170 stored faces,232 vertices,zero joints and 9 runs. Runs5/6 (first
faces 154/158,4 faces each) use segments 11/10 and 32x32 CI8 with palette at
1024. Runs7/8(first faces 162/166,4each) use segments 6/7 and 32x64 CI8 with
palette at 2048. All four controller phases are decoded as correlated pairs:

| Counter branch | Segments6/7 | Segments10/11 |
|---|---:|---:|
| `<480` |1937|3649|
| `<960` |1937|3657|
| `<1200` |1942|3657|
| otherwise |1946|3657|

The explicit preview selects the first source phase. Later phases are evidence,
not a claim about the active gameplay phase or independent Cartesian choices.
Entry185 reaches112/170 linked faces; run 0's58 external-texture faces remain
unresolved. The native controller also deforms vertices. The export deliberately
retains ROM geometry, so it does not establish the active HUD pose.

Combined, exactly45 faces in six runs gain bindings. No vertices, faces, source
UVs, matrix assignments, joints, source bytes or unrelated runs change. This
context does not establish animations, parent transforms, visibility, colours,
opacity or native raster appearance.

## Actual consumers

For165, constructors `150FAE18` and `151D6BFC` pass native model 165 to
descriptor constructor `15157010`; the copied descriptor selects callbacks2/1 in
table `8008ADBC`. The checked pointers at `8008ADC0` are `151D710C` and
`150FB1E8`; the latter immediately wraps the former plus matrix setup. Object
type54's draw slot `8008BFA8` is `15157420`. The callback calls `15133EEC` for
descriptor195, first segment 6 then7. Descriptor `80091484` points to the first
flat word at `80090B30`, which is1288. Its format0 suppresses the helper's extra
adjacent palette binding; the model commands instead address their palette at
2048 in the same payload. Descriptor16x16 metadata does not redefine the model
tile.

The first constructor's flags 0x61 skip renderer helper `151462C8`. The second's
flags 0x27 allow it, but constructor argumenta3=0 initializes the auxiliary
pointer fields at+FC/+104..+110/+114 tozero, so the helper's initial pointer
checks return before emitting anything. This establishes the initial constructor
preset, not every future mutable object state. Renderer segment 8 changes do not
overwrite these initial texture segment bindings.

For185, controller `1509093C` directly loads model 185 through `1502FE10` at
`15090B3C`, retains its list pointer at state `800D24C8`+80 and sets the four
texture halfwords at+B0/B2/B4/B6 from the checked flat table near`80090258`. The
counter branch thresholds are480/960/1200. Renderer `150911F4` reads those
halfwords, calls `1510D0EC`, and binds segments 6/7/10/11 respectively before
calling the retained list. This dedicated HUD consumer is separate from the
ordinary character default machinery and supplies no animation clips.

The module pins15 complete consumer/helper bodies, five small dispatch,
descriptor, pointer and selection-table spans, eight complete inherited EF+EndDL
state entries, both complete source models and all six texture payloads. Every
specialized renderer alpha/flag arm agrees on RGBA16 TLUT at the target run
offsets; this does not choose a render pass, blend mode or opacity. Before
mapping it independently reparses the pinned source and requires exact geometry
equality. It decodes all correlated phases, checking CI8 layout and exact inline
palette position. A captured material anywhere on either model suppresses the
entire ROM material preset.

## Active integration

The ROM-aware bank09 loader rejects overlapping contexts and retains specialized
consumer hashes. Source bindings are mapped before face omission; the untouched
source geometry remains available for accounting. Captured material precedence
skips the whole preset. Full decoded fields are compared across both direct-CLI
and package dataclass identities. The specialized contexts are excluded from
ordinary segment 8 consensus. `rom_special_attachment_material_state` and glTF
`romSpecialAttachmentMaterialState` retain the complete proof. Specialized
renderer and source-only transform metadata replace contradictory generic
attachment-renderer claims; no new pose or deformation is invented.

Focused tests use a synthetic native attachment container with a real joint,
five faces, four runtime segments and actual CI8 decoding. No ROM bytes are
embedded and parser/decoder subchecks are not mocked. They verify full
consumer/data guards, payload completeness including unselected variants,
source/model/run mutations, exact context and integer phase guards, correlated
alternatives, capture precedence, UV/geometry preservation and OBJ/glTF encode.

Independent scalar CI8/RGBA5551 review covers18 run/phase combinations across
all six targeted runs and four correlated185 phases. Images agree under every
relevant pinned inherited RGBA16 state table; this does not select an observed
runtime phase or establish native renderer output.

```sh
./conker model-assets preview --bank 09 --rom roms/baserom.us.z64 \
  --output build/assets/models/us-bank-09
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_special_attachment_materials.py'
```

The integrated glTF evidence names the specialized renderer and neutral/source-
only transform scope. It must not retain contradictory generic renderer
`150311C4`/selector`15031070` claims in `attachmentColorState` or
`attachmentMatrixState` for these separate consumers.

Independent emitted-geometry comparisons cover165's65 faces/195 UV and joint
corners and 185's170 faces/336 available UV corners. Geometry binary buffers
remain unchanged. Regenerate full-bank reports for current linked totals; they
are separate from these source-identity and bounded consumer checks.
