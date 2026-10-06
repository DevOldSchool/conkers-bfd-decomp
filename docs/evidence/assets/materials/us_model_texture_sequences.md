# Complete ROM texture-sequence exports

The optional `texture-sequences` export materializes every frame admitted by
existing [object animation bindings](us_object_texture_animation.md) and
[primary-scene selectors](us_scene_texture_bindings.md). It writes 41 PNGs,
eight ordered frame arrays and exact source-model/material links. Existing
model previews continue to use their reviewed inspection frame; gallery cards
and geometry are unchanged.

This makes the known alternatives available as a usable sequence set. It is
not a discovery of 41 previously unknown ROM resources. The generic texture
catalog already contains the fifteen water frames, while the active bank-04
model preview directory contains fourteen of the 41 exact decoded images.
Previous material metadata recorded every frame's hash but exported only its
selected image.

## Coverage and provenance

| Binding family | Models | Material runs | Affected source faces | Unique frame images |
| --- | ---: | ---: | ---: | ---: |
| Placed-object animation | 33 | 33 | 713 | 21 |
| Primary scenes 19, 20, 26 and 51 | 4 | 26 | 236 | 20 |
| Total | 37 | 59 | 949 | 41 |

Face counts describe the linked material runs, not complete model geometry.
Scene-7 segments 4 and 6 have an animation-capable placement context but no
eligible stored material run. They remain explicitly unbound; the exporter
creates no texture binding from placement alone.

Input is the normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The extractor reloads source models,
placements, consumers and flat payloads from that ROM. It uses no capture or
existing preview image as an extraction input. Existing whole-function,
dispatch and table guards remain mandatory. Each output frame must match the
PNG hash returned by the complete, unmodified binding resolver before it can
be retained. All alternatives must keep the admitted dimensions and format.
The manifest preserves all 24 original twelve-byte object-animation records,
including their otherwise unused tail bytes.

The eight arrays comprise fifteen 64 x 64 CI4 frames, two three-frame groups
of 32 x 64 IA8, and twenty 64 x 32 RGBA16 scene alternatives. All 114,688 pixels
were also checked using independent CI4, IA8 and RGBA5551 indexing, including
palette offsets, odd-row word swaps and PNG vertical orientation.

Water order is `7188, 7195..7202, 7189..7194`; sorting by flat ID would change
the animation. Every run retains array order and its source segment hash.
Scene 51 keeps its correlated per-segment phase offsets, scene 26 keeps the
adjacent-frame relationship and independent switches, and scenes 19/20 keep
their separate conditional selectors. The exporter does not turn these
alternatives into independent, simultaneously selected textures.

## Native object selector

`1511A494` is pinned as 616 bytes with SHA-1
`c896da27caa019639fe040e1d5bf9034f2663673`. The state helper decodes its packed
word as a signed high-halfword increment and unsigned low-halfword counter.
A zero increment becomes +1. Each invocation advances the counter before
selecting the frame by integer division by the period.

For ping-pong rows, a negative counter becomes `period` with increment +1;
a counter at or beyond `count * period` becomes `(count - 1) * period` with
increment -1. Thus the upper endpoint repeats while the lower bounce advances
to frame 1. A generic forward/reversed frame list is not equivalent. For loop
rows, the span is subtracted only once when reached, and the increment becomes
+1. The helper rejects unsupported resulting counters and out-of-array reads
instead of silently applying modulo or repeated reflection.

This helper models one invocation of an authenticated ROM row. It does not
infer initial phase, frames per second, caller timing, wrapper UV/vertex
updates or gameplay visibility. The static gallery's stored frame zero remains
an inspection choice, not a claim about the first updated frame.

## Reproduce

```sh
./conker model-assets texture-sequences \
  --output build/assets/models/texture-sequences
./conker model-assets texture-sequences \
  --output build/assets/models/texture-sequences --verify
python3 -m unittest discover -s tests -p 'test_model_texture_sequence*.py'
```

Generation requires a new output directory. Verification rederives all PNGs
and metadata and compares output bytes without writing. The manifest links
files to ROM flat IDs, frame arrays, model identities, source material runs,
placement evidence and conditional selector formulas. Native opacity,
lighting, filtering and complete raster equivalence remain unresolved.

The independent ROM/pixel audit and output comparison are retained under
`build/assets/models/reference/continuation-20261001/texture-sequences/`.
This work is separate from recovery branch
`4f80ae55eeb322a170837319257ed0ab9da58c97`; it does not modify that branch's
material recovery paths.
