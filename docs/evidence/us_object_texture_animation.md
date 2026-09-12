# ROM object texture-animation bindings

The scene/object animation binding resolves missing textures on 33 bank-04
models and 713 faces. It selects the first stored frame for inspection while
retaining every frame's ROM flat index, decoded PNG hash and timing descriptor.
It does not select an observed gameplay time or replace source display lists.

## Consumer chain

Evidence uses normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`; captures are not inputs.

- `150039E0` maps bank-11 placement `+0x10` to the bank-04 segment and stores
  that selector with bit 15 at object `+0x54`. Placement `+0x14` selects a
  twelve-byte update-dispatch row at `0x80088C90`; its function becomes object
  `+0x38`. The ordinary renderer remains `151137D4`.
- `15113E54` conditionally invokes object `+0x38`. Reviewed update indices
  21, 25 and 41 reach `1511D7BC`, `1511A6FC` and `1511A738`, respectively.
  Those functions call `1511A494` with the object and its animation state.
- `1511A494` scans the 24 twelve-byte records at `0x80089324..0x80089444`
  in order. It checks scene and model, applying bit 15 for scene-specific
  model selectors. Model byte 255 is a wildcard; the first matching row wins.
- Each row supplies a frame-array pointer, frame count, period and ping-pong
  flag. The consumer advances its phase, divides by the period, then loads
  the selected flat index through `1510D0EC`. The export explicitly selects
  stored frame zero instead of inferring a current phase.
- `1510D874` registers pixels on segment 4. When the source list contains a
  palette load, the updater registers the final 32 payload bytes on segment 5.
  `1510D8C0` emits those bindings for the matching object before `151137D4`
  submits its display list. Later commands in this direct draw path do not
  replace segments 4 or 5.

The new module pins the complete reviewed updater/dispatcher functions,
animation table, three frame arrays and relevant update-dispatch pointers.
Existing object-material guards cover the loader, renderer, registration
functions and all registration call sites. Changed evidence fails closed.

## Binding and preview contract

Only resolved ordinary bank-11 placements with a reviewed updater are eligible.
The existing context rejects the rewritten-list flag. Unreviewed updater
indices do not inherit the wildcard row. Source pixel segment 4 and optional
palette segment 5 must have zero offsets and no competing flat binding.

The proven arrays contain fifteen 64 × 64 CI4 water frames and two groups of
three 32 × 64 IA8 frames. For every frame, the existing decoder verifies native
loads, tile state, payload spans and the palette tail. Every frame must decode
with the same dimensions and sampled format before the first is exported.
The source segmented addresses and geometry remain unchanged.

The manifest records `rom_object_texture_animation`; glTF materials record
`romObjectTextureAnimation`. These are separate from render-state consensus
and captured materials. Batch validation independently reloads the ROM
consumer context, reproduces every frame and checks the published image bytes
and provenance. Cache dependencies include the animation-linked images.

## Verification and inspection

Independent indexing checks all 73,728 RGBA pixels across the 21 unique frame
images. Numeric comparison checks every recovered model's faces and UV corners.
Thirteen mutations of the actual ROM consumer, dispatch, table and array bytes
are rejected. Unit regressions cover first-match/wildcard ordering, wrong scene,
unreviewed update dispatch, rewritten lists, nonzero binding offsets, incomplete
frames and distinct animation provenance.

Seventeen distinct water surfaces, waterfalls and an animated-sided B pad are
selected for inspection. Four recovered models have byte-identical source
geometry and the same first-frame image as another selected record. Twelve
sparse glowing fragments require scene/effect composition. Those sixteen stay
available as extracted diagnostics without additional gallery cards.

The full batch passes all 783 Python tests and 5,406 file checks. Its 814
passing renders include all seventeen additions; eight existing render cases
remain incomplete. All seventeen final self-contained GLBs pass both Blender
import checks and Khronos validation. The 1,562 pre-existing gallery GLBs and
preview PNGs remain byte-identical.

Stored frame zero does not prove initial update timing, current phase, native
interpolation, visibility, lighting or complete gameplay appearance. UV and
vertex animation remain separate from texture-frame selection.

Local evidence is under
`build/assets/models/reference/blocked-batch-20260911/`: `rom-proof.json`,
`read-audit-bank04.json`, `animation-table.json`, `recovered.json`, the isolated
`preview-bank04/`, and reviewed renders. See the
[asset roadmap](../asset-roadmap.md) for current validation totals and remaining
work.
