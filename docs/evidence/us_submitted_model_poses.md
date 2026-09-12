# US models from one graphics submission

The extraction question is whether geometry, pose, UVs, colours and image pixels
can be joined to one submitted graphics task, without choosing a similar-looking
frame. These checks use normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. They extend the independent
[rig comparison](us_tediz_submitted_rig_validation.md); they do not establish
native RSP/RDP raster parity.

## Export and comparison

`./conker model-assets submitted` exports the instances configured in
`config/model-validation.json`. Each captured VTX corner identifies its matrix
palette through the source joint slot and absolute load address. Materials are
filtered by that instance's draw indices, so different characters in one task
cannot share lighting merely because their model and material numbers agree.

The baked glTF retains every submitted source triangle, including a triangle
collapsed by a captured matrix. Its origin is the translation of the lowest
used palette slot. It retains the submitted model-view orientation and scale;
it is a captured pose with no animation Actions. The separate rigged inspection
models remain available for animation testing. The captured-colour Conker
animated source has identical mesh accessors, material definitions, image bytes,
skin inverse binds and node transforms to its neutral source; only object names
and the 764 decoded animation clips differ. Its curated GLB is an animation test
asset, not proof of animation or animated-lighting parity.

The validator reads emitted accessors directly. It compares positions against
raw captured VTX coordinates transformed by the fixed matrices, checks winding
and complete face coverage, recomputes lighting samples from the captured loads,
and checks UVs, image pixels, sampler, culling, alpha and unlit material factors.
Tests reject changed positions, colours, material state, incomplete clusters,
wrong instance ownership and incomplete face coverage.

The following positive captures were checked on 2026-09-09:

| Character | Capture / graphics event | Faces | Palette root | Result |
| --- | --- | ---: | --- | --- |
| Tediz instance 1 | `tediz-vertex-lighting/save-game-14.jsonl`, 0 | 338 | `0x8012F180` | Complete pose and material replay |
| Tediz instance 2 | same event | 338 | `0x8012F880` | Complete pose and material replay |
| Conker | `vertex-light-export/trace.jsonl`, 0 | 811 | `0x8012EA80` | Complete pose and material replay, including eyes |
| 0001 | `entry0001-submitted/save-game-6.jsonl`, 13 | 525 | `0x80128EC0` | Complete pose and material replay |
| 0094 | `entry0130-submitted/selected-parts/save-game-26.jsonl`, 43 | 622 | `0x8013A1C0` | Complete pose and material replay |
| 0067 | same event | 80 | `0x8013A000` | Complete pose and material replay, including IA16 images |
| 0130, selected ordinary parts | same event | 793 | `0x80139A00` | Complete pose and material replay, including IA4 images |

Capture paths in the table are relative to `build/assets/models/reference/`.
All seven baked outputs have exact float32 positions for their captured transforms.
The two Tediz submissions contain zero-scale limb matrices. Their fragmented
appearance is present in those matrix inputs, so these remain diagnostic
outputs. `inspect/tediz-animated.glb` remains the useful Tediz inspection model.
The Conker capture likewise intentionally collapses 34 faces through zero-scale
slots 13 and 14; the exporter preserves those submitted faces and reports them.

## Selected parts in the submitted task

0130 contains alternate parts and a separate render-to-texture pass. A whole
source-model match is inappropriate for one ordinary call. The paired capture
records renderer-selected display lists, renderer returns and the next graphics
task. Existing checks prove that the command range occurs exactly once, nested
geometry bytes agree, and palette matrices are captured at submission.

The new cluster join requires complete, ordered command clusters with equal
signatures and triangle counts inside that byte-verified range. It transfers
the proven selected-part identities to the submission; actual captured VTX
bytes still gate each material observation. Missing, repeated, partial or
reordered clusters are rejected. This recovers captured lighting for all 793
ordinary faces, up from 293. The posed comparison checks 2,379 position/colour
corners, 1,962 UV corners and 62 captured image bindings. Geometry/lighting and
captured-image coverage remain separate report dimensions. The configured case
requires zero unresolved textured faces; losing coverage fails validation.

The capture has 44 events, eight renderer calls and two graphics submissions;
all eight calls link positively. Its SHA-256 is
`af12cf10b6fb9c3d5000226c60a11b31d1df970a3ee03e4c96157edcdc42158f`.
The source 0130 model SHA-1 is `1935d366617a4f6d17ef607d62d1523f98fb13c4`.

Reproduce the paired capture using the local checksum-validated save state:

```sh
./conker mupen-trace --spec config/model-trace-character-draws-submitted.json \
  --output build/assets/models/reference/entry0130-submitted/selected-parts/save-game-26.jsonl \
  --savestate build/runtime-traces/openemu/all-states/save-game-26.st \
  --software-renderer --session-timeout 480
./conker model-assets materials \
  --trace build/assets/models/reference/entry0130-submitted/selected-parts/save-game-26.jsonl \
  --output build/assets/models/reference/entry0130-submitted/selected-parts/materials --force
./conker model-assets activity \
  --trace build/assets/models/us/runtime-traces/character-activity/save-game-26.jsonl \
  --draw-trace build/assets/models/reference/entry0130-submitted/selected-parts/save-game-26.jsonl \
  --output build/assets/models/reference/entry0130-submitted/selected-parts/activity --force
./conker model-assets compose \
  --activity-manifest build/assets/models/reference/entry0130-submitted/selected-parts/activity/manifest.json \
  --textures build/assets/textures \
  --runtime-materials build/assets/models/reference/entry0130-submitted/selected-parts/materials/manifest.json \
  --task-runtime-materials build/assets/models/reference/entry0130-submitted/selected-parts/materials/manifest.json \
  --output build/assets/models/us-submitted-compositions --force
./conker model-assets submitted
./conker model-assets validate
./conker model-assets inspect
```

## Texture decoding corrections

Eight 0130 faces initially lacked images because the captured decoder omitted
IA4. Its three intensity bits expand to `(0, 36, 73, 109, 146, 182, 219, 255)`;
its alpha bit expands to zero or 255. This follows the software renderer's
[IA4 texel fetch](https://github.com/ata4/angrylion-rdp-plus/blob/master/src/core/n64video/rdp/tmem.c#L280).
The codec now supports reversible IA4 PNGs, with exhaustive nibble and row-swap
tests. Captured decoding requires no TLUT, a complete zero-DXT load and zero
TMEM/source offsets. An independent raw-byte comparison verified all 4,096
pixels of 0130's 64×64 image: source SHA-256
`534d7542a1b0d79af0d7aa7f30c6a52a514d3eee0079788294f21a18fa5203db`, PNG SHA-1
`85149ab3c69d72c46770f28bf4756a0175a93c05`. The captured 2,048 bytes also equal
the complete ROM flat asset 1915. The static full-payload texture
inventory has not been expanded to classify IA4 contracts in this change.

Captured IA16 images now retain independent eight-bit intensity and alpha.
The admitted case requires a proven IA16 render tile without a TLUT, a complete
zero-DXT load, zero TMEM/source offset and sufficient row bytes. Other 16-bit
formats and unsupported mip layouts remain unresolved. Entry 0067's 32×32
image contains 2,048 captured bytes, SHA-256
`b59dcb32f52d5393ba25edd124a711f1763d471cd6de422ac29f143c116f5b38`.
Those bytes equal the complete ROM flat asset 4295.
Fixtures verify independent intensity/alpha values and reject short loads,
nonzero DXT/TMEM offsets and palette lookup.

Static intensity images can now expose fewer columns than the stored TMEM row.
The decoder uses the SetTile row stride, swaps odd rows before cropping, and
requires the complete stored span. Two scene segments (bank 04, 27/04 and 30/07)
use flat asset 3297 with a 63×64 visible IA8 image and 64-byte rows. An independent
raw-byte comparison checked all 4,032 RGBA pixels. The PNG SHA-1 is
`76dac14593b0f9a6f683e32fb74977054a73af3f`. Across 9,590 static material runs,
exactly these two selections gained images; the previous 8,341 image selections
were unchanged. Both main and captured-colour bank-04 corpora were regenerated.

## Automated discovery and remaining work

`config/model-trace-submitted-inputs.json` captures a complete first graphics
submission, including VTX, matrices, normals, lights and images. After extracting
its material catalog, use:

```sh
./conker model-assets discover-submitted --trace path/to/trace.jsonl \
  --runtime-materials path/to/materials/manifest.json --output path/to/discovery.json
```

For paired character traces, discovery separates calls using the validated ROM
part sequence and exact renderer-command range found in the next graphics task.
Each case retains `draw_call` (return event, active entry, slot, task index and
render-pass kind), alongside the source-model target and captured palette root.
The active character entry is distinct from the source model selected by an
offscreen pass. Keep this selector when adding a discovered case and its
`exports` to `config/model-validation.json`: export and validation resolve it
again and check the saved provenance in the resulting glTF.

Results distinguish `exportable`, `rig-only`, `partial-composition`,
`unresolved-rig` and `unresolved-call`, with concrete reasons. A partial
composition has verified selected geometry, but is not accepted as a complete
source rig or a material-complete export. Missing or ambiguous call evidence
cannot fall back to a whole-task success for that source. Unattributed objects
and earlier tasks without captured calls retain whole-task discovery. Discovery
does not add files to the curated inspection set.

The bounded six-state survey under `reference/submitted-state-survey/` captured
positive submissions from Save-Game-2, 3, 6 and 18. Save-Game-9 and 11 timed out;
a software-renderer retry of 9 also timed out. These are bounded negative traces,
not evidence that those models never draw. State 6 identifies a complete
525-face entry-0001 rig with initially unresolved materials. A subsequent paired
capture using `config/model-trace-character-draws-submitted.json` on Save-Game-6
records 14 events, four positively linked renderer calls and two graphics tasks
(trace SHA-256 `58366db793cb485bbdf5852139c9d7714becaae0d210b960ce9d7bf67b4b9531`).
The ordinary call selects source entry 1; its separate offscreen call selects
entry 4. Transferring those part identities into submission resolves the material
ambiguity, and the configured event-13 export checks all 525 faces successfully.
The activity manifest also verifies that the cluster mapping survives JSON
round-trip without changing key types. State 18 identifies two
12-face entry-0115 instances. Partial entry-0004 coverage remains unresolved.
These results provide concrete next targets without manual Blender searching.

A final paired survey under `reference/submitted-state-survey/paired/` captured
Save-Game-4, 19 and 3. State 4 has no character calls in either its first two or
its extended eight-task window; those are bounded negative draw observations.
State 19 again verifies entry 0001 and the small entry-0115 instances. State 3
previously retained three ambiguous clusters because ordinary and offscreen
draws share source candidates. Automatic call selection now identifies both
ordinary draws as exportable. The configured event-13, return-12 case at
palette `0x8011E040` exports all 525 source faces, 55 clusters and 28 material
runs. Its checker compares 1,575 position/lighting corners and 1,536 UV corners,
with zero float32 position error and zero unresolved textured faces. Both
entry-0004 offscreen calls remain explicitly unresolved against their source rig.

The same discovery path was checked on Save-Game-19 and Save-Game-26. State 19
separates its two entry-0115 calls while retaining the earlier unpaired task;
state 26 separates each 793-face ordinary/offscreen entry-0130 selection from
the 1,586-face source rig and finds complete 0094/0067 instances. Across these
three traces, discovery reports ten exportable cases, four partial compositions,
one rig-only case and four unresolved rigs. These are cases, not ten newly
identified model assets, and do not establish native raster parity.

The new diagnostic export is
`us-submitted-poses/geometry/character-0001-save3-selected-call.gltf`; the curated
inspection set stays at 19 models. This pass preserved the hashes of all 50
existing inspection GLBs, preview PNGs and submitted glTF/buffer files. Discovery
reports, test output and preservation evidence are under
`build/assets/models/reference/call-scoped-discovery-work/`.

## Verification of the inspection set

The final checked set passes 664 unit tests, all four ROM model-bank rebuilds,
3,034 Khronos/Blender file checks, six complete-rig submission cases and the
selected-part 0130 case. All 19 packaged inspection GLBs were reimported in
Blender 5.2.1 and compared with their source glTFs: geometry, indices, UVs,
vertex colours, texture pixels, rig data and the 849 imported animation Actions
are preserved. Action counts and byte-preserving packaging do not establish
that the decoded animations match the game.

All new render references were inspected before being added. The batch retains
five pre-existing intensity-correction differences against older references;
those references were not overwritten. The report remains `incomplete` for
whole-corpus native appearance, with no failed consistency checks. The final
call-selection batch also passed its code/configuration/ROM stability gate; the
earlier run that overlapped the last audio-boundary fix is preserved separately. Generated
evidence is in `build/assets/models/reference/submitted-pose-work/`; the current
user-facing files are in `build/assets/models/inspect/` and `previews/`.
