# Character vertex-load matrices and preview corrections

The September 8 visual review found real exporter errors in previews that had
passed byte reconstruction and Blender import. Those checks establish storage
and interchange properties, not correct vertex placement or appearance.

## Cached vertices retain their load-time matrix

`DA380003` selects a segment-3 matrix. `01` loads and transforms a range of
vertex-cache slots. A later matrix command does not transform cached vertices
again. Standard and packed triangle commands can therefore combine corners
loaded under different matrices.

For US bank-01 entry `0000`, the first triangle at model offset `0x3D80` uses
cache slots `(0, 1, 6)`. Their load-time matrix slots are `(12, 12, 1)`, while
the matrix active at the triangle command is slot `0`. Assigning slot `0` to
the entire triangle moves all three corners incorrectly. The same defect affects
37,520 of the bank's 62,073 source faces across 160 of its 183 models. Every
character face corner has a matrix selection at its vertex load.

The parser now retains a matrix per face corner. Bind-space export, glTF
`JOINTS_0`, composition merging, captured-pose baking and validation-atlas
positions use that ownership. Vertex deduplication includes matrix identity, so
reloading one source vertex under another matrix creates distinct output
vertices. Pose export requires every referenced vertex matrix, including matrices
no longer active at draw time. Joint-local zero-area triangles spanning several
matrices are retained until transformed positions can establish degeneracy.
Character OBJ files remain joint-local diagnostics; use glTF for assembled bind
geometry and captured poses.

This preserves the earlier format and address findings: renderer-return palettes
contain row-major floats, submitted task palettes contain split fixed-point N64
matrices, and global palette slots use absolute addresses relative to the renderer
root. No matrix codec or root-address correction was reverted.

## Callable lists have independent material inputs

Character pointer-table entries are callable display lists, not a proven execution
sequence. The decoder previously carried RDP state across adjacent stored lists.
Entry `0004` illustrates the error: its primary list ends at `0x1B70`; the secondary
list begins at `0x1B78` and contains no image load. It nevertheless inherited flat
image `3093` from the primary list, putting a shirt texture on unrelated surfaces.

The parser now clears inferred material state at each character `EndDL`. A missing
texture-enable command is unknown, not proof of untextured geometry. Missing
pixel or coordinate state stays unresolved unless supported by the supplied
runtime evidence. This withdraws unsupported flat-image inheritance from 224
runs covering 9,782 faces in 33 models. Two formerly merged material spans split
at callable-list boundaries; the complete inventory now has 8,991 runs.

The nine neutral compositions retain 3,769 of 3,775 source faces. Forty-four
captured poses remain exportable, with six invalid/conflicting Save-Game-24
instances excluded. Neutral output links 91 texture runs; posed output links
1,045 runs, including 1,024 task-local captured images, to 78 copied PNGs.
Plain secondary-pass surfaces are an explicit remaining appearance gap. They
must not be relabelled complete merely because their source event is known.

## Preview framing and validation

Blender's default camera far plane also hid large models completely. Entries
`0094` and `0130` placed the preview camera about 2,470 and 1,251 units away,
beyond the default 1,000-unit plane. The renderer now scales both clip planes
with the model diagonal. The corrected renders visibly contain these models.

All four `./conker model-assets verify --bank XX` checks pass byte-identically.
The 491-test Python suite passes, including regressions for mixed cache matrices,
source-vertex reloads, glTF joints, composition/pose propagation, missing matrices,
transformed degeneracy and independent-list material state. Blender 5.2.1 imports
1,367 current glTFs with 2,869 meshes, 383,167 polygons and 2,621 Actions.
The regenerated atlas contains all 1,031 models: 417 accepted by its structural
rules, 614 requiring review and zero rejected. These statuses are not visual
parity claims.

Current images are in `build/assets/models/previews/`; prior renders are preserved
under `archive-before-vertex-load-fix/`. Four character identities were inspected
in Blender renders, including a separate vertex-colour geometry view of Conker.
The remaining frontier includes runtime vertex colours, inherited textures and
coordinates, secondary-pass blending, normal/lighting state and exact raster
behaviour. No new emulator capture or exact N64 visual validation is claimed.
