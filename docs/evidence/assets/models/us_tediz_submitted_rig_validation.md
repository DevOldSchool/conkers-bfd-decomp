# US Tediz submitted-rig validation

The batch validator now checks an exported character rig directly against
captured submitted vertex inputs. The first case is US bank 01 entry 90,
segment 0 (Tediz), model SHA-1
`d0432d38f7a4f7de2d828c1bd98bb30db39daa0a`, from the normalized US ROM
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The question is whether the current rig can reproduce every submitted triangle
using the captured vertex-load matrices, including the five triangles absent
from the external 333-face reference. The existing vertex-complete capture is
`build/assets/models/reference/tediz-vertex-lighting/save-game-14.jsonl`, event
zero. It contains a positively identified graphics submission and two instances
with distinct absolute matrix palettes. No new emulator capture is required.

## Comparison and limits

`model_runtime_validation.py` reads glTF indices, positions, rigid weights,
joint identities and inverse-bind matrices directly from their buffers. It
recovers joint-local positions without calling the ROM geometry parser or
pose baker. The existing tracer replays the hash-checked task and nested
display lists, with captured vertex bytes and split fixed-point matrix inputs.

Command-cluster candidates identify possible source spans. Actual VTX bytes,
triangle winding and matrix ownership then resolve the correspondence. TRI4
triangle ordering may differ, so whole triangles and cyclic corner rotations
are compared without reversing winding. Duplicate triangles retain their
multiplicity. Each corner's absolute load-matrix address minus its exported
joint slot times 64 must yield the same palette root. Each instance must cover
every source face exactly once; missing, duplicate or ambiguous coverage fails.
The root must also equal the fixture's captured reference address and occur as
a segment-3 base in hash-checked command replay, with subsequent bases remaining
aligned interior rebases. This prevents a uniform shift in exported joint slots
from passing merely by shifting the inferred root.

This is an independent check against the exporter's geometry and skinning
output, using the existing trace decoder. It is not a second RSP emulator or
a measurement of the RSP's final fixed-point vertex outputs. The reported
world-coordinate error evaluates the exported rig under the captured matrices;
it does not establish that an older posed export belongs to this submission.
UV sampling, combiner constants, lighting and full native raster parity remain
separate evidence dimensions.

## Positive findings

Both submitted instances contain all 338 triangles: 676 triangles and 2,028
corners across 54 matched command clusters. Their palette roots are
`0x8012F180` and `0x8012F880`. The maximum local-coordinate error is
`0.000003814697265625`, within the explicit `0.0001` float32 bind-data tolerance.
Evaluating the rig under captured matrices gives a maximum world-coordinate
error of approximately `0.000002852` native units.

All 676 faces agree on culling and alpha-mode classification. Bound texture
pixels match the captured images on 666 faces, corresponding to 333 faces in
each instance. The other ten submitted faces use a combiner without TEXEL0 or
TEXEL1 inputs and need no texture binding. Their source spans are faces 44–46
and 131–132 in each model. Submission proves that the game emits those five
triangles; it does not prove that each contributes visible pixels.

The older Save-Game-14 posed exports use different limb matrices from this
submission. The closest recorded palette differs by about 0.78 in a matrix
component, and the resulting pose differs by more than 42 native units. This
exceeds float-to-fixed conversion rounding. The pairings therefore remain
unproven; those differences are not treated as mesh defects or corrected by
substituting another frame's pose.

## Reproduction

Run `./conker model-assets validate`. The configured `runtime_draw_cases` entry
names the rig, captured task, material catalog, source identity and expected
instance count. Its result appears under `checks.runtime-draw:tediz-submitted-rig`
in `build/assets/models/validation/report.json`. A passed rig check does not
change the report's incomplete native-appearance status.

Cache identity includes the ROM, validation implementation, glTF and imported
dependencies, captured trace and image data, and the source cluster index.
The check verifies input stability around processing. Six regression tests
exercise inverse-bind recovery, mixed vertex-load matrices, changed vertices,
wrong joints, winding, repeated triangles, ambiguous palette roots, complete
instance coverage, invalid weights/transforms and wrong-ROM traces.

The completed batch passes the new submitted-rig check and all 3,015 existing
file checks, with zero new Khronos checks, Blender imports or renders. All four
ROM banks reconstruct byte-identically. All 611 Python tests pass, together
with Python compilation and scoped whitespace checks. The five previously
recorded intensity-render differences remain against their preserved baselines;
this investigation changes no exported model or rendered image.

Investigation records and logs are under
`build/assets/models/reference/tediz-runtime-validation/`. The existing model
exports, captures and regression reference images are preserved.
