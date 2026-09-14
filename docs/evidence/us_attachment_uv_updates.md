# US attachment texture and UV updates

Bank-09 entry 80 has complete stored-geometry material coverage under an
explicit initial texture and tile-origin preset. All inputs come from the
normalized US ROM, SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
Captures and save states remain comparison evidence only.

## Consumer and state

Action 102's header at `80086FEC` selects the single record at `8009D210`:
`50091301000000020000000000004101`. The action constructor selects model 80,
updater 19 and kind 1. Descriptor `+0x17 = -1` uses the static attachment loader
and stored vertex/joint data. The initializer slot at `80096FE0` targets the
no-op return `15031C00`. The shared constructor, loader, dispatch and renderer
chain is documented in [attachment texture selectors](us_attachment_texture_bindings.md).

The checked updater word at `8008420C` selects `150D83D8`. In the explicit
initial state, descriptor counter `+0x38 = 0` and parent state `+0x84 = 0`:

1. The updater sets accumulator `+0x3C` to 50.
2. It stores flat 7203 from `80090304` into texture selector `+0x18`.
3. Parent state zero excludes state 397's alternate image/animation branch.
4. It finds the first F2 command in the loaded primary display list and
   replaces its first word with `F200203E`.

The renderer's fifth argument and second texture selector `+0x1A` are zero.
`150311C4` loads the selected flat through `1510D0EC`, binds segment 6 and
submits the attachment list without changing its tile origin. The preset does
not claim native parent ownership or that this complete state is reachable.
Later updater states and the alternative image are not admitted by this proof.

## Exact display-list update

The model payload is 1,464 bytes, SHA-1
`d9667ef7783f87f1dbfd616d278539a7f7664fcb`. Its first display list begins at
`0x320`; the updater's first F2 is at `0x340`:

| State | First word | Second word |
| --- | --- | --- |
| Stored ROM | `F2002002` | `0001E0FE` |
| Initial updater preset | `F200203E` | `0001E0FE` |

The updater computes `trunc.f32(120 * f32(50 * scale) + 2) & 0xFFF`, with
float32 rounding after each operation and scale bits `3C23D70A` from
`800A0B14`. The result is 62. The T origin changes from 2 to 62 in quarter-texel
units: **15 texels**, or **15/64** in normalized V coordinates after the PNG
vertical flip. Only the first material's 16 faces inherit this command.
The next F2 restores the stored origin for the remaining 44 faces.

Flat 7203 is the complete 2,048-byte RGBA32 image, 8 x 64 pixels. The first
material's unclamped masks are 3/6, its tile is `F5180400 00018030`, and its
LoadBlock is `F3000000 071FF000`. Together they establish the full repeating
image. Scrolling the tile origin must not crop the image to the smaller
SetTileSize extent. The second material retains flat 1807 and its stored UVs.

`scripts/model_attachment_updates.py` verifies thirteen consumer spans, six
ROM data spans, the complete model payload and the affected material layout.
The preview changes only the first material's tile bounds and explicit image
dimensions. Source extraction and byte reconstruction keep the original bytes;
positions, faces, normals and joints are untouched. A captured first material
keeps its own texture/coordinate state and does not receive this ROM preset.

## Validation and inspection

The manifest's `rom_attachment_update` and glTF's `romAttachmentUpdate` retain
the source identity, selector state, command offset, before/after words and
image dimensions. Validation reloads the ROM context and checks both material
pixels and actual UV accessors. Removing provenance, changing its selector or
origin, or retaining unshifted UVs is rejected.

An independent audit patches the native F2 word in a copy of the raw model,
parses that copy, and compares every decoded geometry field against the preview
selection, allowing only the proven full image dimensions. It checks all
**60 faces and 180 UV corners**: 48 shifted corners and 132 unchanged corners.
Both RGBA32 images are independently decoded, covering **768 pixels** with
odd-row byte swaps and vertical orientation. Nineteen code/data mutations and
four exported-state/UV mutations are rejected.

The six new update tests and affected validation module give **23 passing
tests**. One optional Khronos unit test skips in the isolated worktree because
its local validator package is absent; the final packed GLB receives an actual
Khronos check from the main checkout. Unchanged suites are reused.

The gallery label **Translucent tube effect — initial texture and UV preset**
is descriptive. Native identity, later animation, placement, visibility,
lighting and blending remain unresolved. Reproduction scripts, source
snapshots and final-file checks live under
`build/assets/models/reference/attachment80-20260913/`. Current publication and
validation totals are in the [asset roadmap](../asset-roadmap.md).
