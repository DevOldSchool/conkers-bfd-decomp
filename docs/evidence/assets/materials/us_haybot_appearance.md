# Haybot selector15 appearance

`haybot-captured-selector15` is a fixed-texture inspection preset for bank01
entry 75. It retains all 1,226 source faces, including collinear face 345, 1,625
vertices/UVs, 45 joints and 15 stored clips / 291 frames. Only the 24 faces of
material run 16 receive the captured selector 15 texture, decoded from flat3823.
The initial descriptor0/default binding is unchanged.

The canonical exporter is `scripts/model_haybot_appearance.py`; its metadata
contract is `config/model-haybot-captured-appearance.json`. Both the contract
identity and source/pixel identities are checked. A pinned capture contract
supports a bounded material choice; it does not make the source-only geometry or
stored animation a captured pose.

## Capture evidence and limits

The reviewed capture inputs include packet SHA-256
`254846215d32ece3913f2adcb8bef94909f1492fbc95b0d70e11d16f0c16615d` and trace
SHA-256 `cceab5ea38d772293946612d3958d2621a3036b841d0185546e4d9fa78e3ab1e`. The
capture audit checks 54 canonical event-state hashes and 2,433 memory blocks.
Fourteen actor samples and the independently decoded saved actor have selector
15 and phase 5. The saved descriptor15 resolves to flat3823, 64×64 texels;
captured pixel and palette spans agree with that ROM payload.

The two recorded renderer ranges are unchanged in their submitted graphics-task
buffers and each occurs once. Each range selects 868 triangles, including the 24
target triangles whose six command records agree with the ROM source. The audit
checks decoder/link metadata and raw range inclusion. It does not perform a new
command-control-flow replay. Scene16 is identified by hash-checked save
metadata, not an independently decoded scene scalar.

For each submission, all 35 segment 3 character matrices match nearest signed
16.16 conversion of returned float32 affine matrices, `round(f32 * 65536)`, with
the unused fourth column canonicalized to `(0,0,0,1)`. Maximum decoded error is
`7.62939453125e-06`, half a 16.16 unit. The non-segment 3 record at `0x800C3E98`
is excluded. The representation conversion changes raw bytes; an empty changed-
matrix list in capture metadata does not establish raw byte equality.

## Independent ROM evidence

The ROM audit authenticates US SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`,
reparses entry 75, and checks all five source sections, the complete run 16
state and cumulative load history, triangle command offsets, native selector
updater, descriptor bindings, compressed texture source and stored animation
companion. The run 16 digest is
`48730d68b4aa72d6e74caf7ca428e3e5b658601561caa87ef84977ae892fa4fc`.

A scalar CI4/RGBA16 decode checks all 4,096 texels and opaque alpha against the
packet RGBA digest. Generated PNG bytes are also checked against their expected
identity. This material proof does not imply that all unrelated Haybot materials
are resolved.

## Generate and verify

Prepare the six locally generated texture catalogs as described in the
[appearance guide](../../../model-appearance.md). With the authenticated ROM/catalogs:

```sh
./conker model-assets appearance --preset haybot-captured-selector15 \
  --output build/assets/models/haybot-captured-selector15
./conker model-assets appearance --preset haybot-captured-selector15 \
  --output build/assets/models/haybot-captured-selector15 --verify

PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s tests \
  -p 'test_model_haybot*.py'
```

Generation builds and verifies an explicit entry 75 baseline with source faces
preserved, then changes only the target image/sampler binding and evidence
metadata. Geometry, skin, animations and binary buffers are checked for exact
preservation. Normal and bind glTF geometry are independently compared with
freshly parsed source. Verification rebuilds expected files and compares bytes;
output paths must be children of `build/`.

These commands use the shipped contract without reading raw captures. Optional
capture/ROM re-audits have separate input requirements documented in [model
evidence audits](../models/us_model_evidence_audits.md). The exporter does not reproduce
captured pose, visibility, texture-animation timing, native lighting, fog,
rasterization or framebuffer output, and it is not a universal default.

## ROM selector variants

```sh
./conker model-assets appearance --preset haybot-rom-selector-variants \
  --output build/assets/models/haybot-rom-selector-variants
./conker model-assets appearance --preset haybot-rom-selector-variants \
  --output build/assets/models/haybot-rom-selector-variants --verify
```

Selectors15/16/17 bind flat3823/3822/3824. The ROM updater and descriptor
contract support these conditional static alternatives. They retain the same
source geometry, rig and stored clips, with no animation in bind glTF.
Capture-specific material labels are removed from the emitted ROM-variant
evidence. Phase, playback timing, pose and visibility remain unknown.
