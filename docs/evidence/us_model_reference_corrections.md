# US model reference corrections

The supplied [Tediz reference](https://models.spriters-resource.com/nintendo_64/conkersbadfurday/asset/295089/)
exposed texture and composition errors that byte verification and Blender import
could not detect. The [Haybot reference](https://models.spriters-resource.com/nintendo_64/conkersbadfurday/asset/298509/)
provided a second check. The cutscene Conker package is excluded from this
comparison. Reference meshes and images are inspection inputs only; generated
models, UVs, joint transforms, and textures still come from the US ROM.

## Runtime texture IDs are not physical stream ordinals

`func_1510D374` sums the unsigned 16-bit compressed sizes in `D_80091D20`
before adding the flat archive base `0x1A37E0`. `func_1510D0EC` checks the same
table at `0x1510D164` and returns its empty-asset sentinel for zero-sized slots.
The table contains 7,762 runtime slots, including two empty slots at 1767 and
1768. The contiguous archive contains only 7,760 deflate streams. The size sum
is exactly `0x90E161`, and every nonempty entry's deflate extent matches its
declared compressed size. Skipping empty slots while numbering streams shifted
every later model texture reference by two.

Tediz runtime texture 4398 resolves to physical stream 4396 at ROM `0x7BDD24`.
The previous physical stream 4398 lookup selected different pixels at
`0x7BE5B5`, creating horizontal stripes on its belly. Correct runtime pixel and
palette SHA-256 values independently match the captured renderer data:

```text
pixels:  21411686136d08232f99208bc7d6b9bc27df21659f1a22d4c6e45dfbe757bbbb
palette: 927eb934be9414091a3a3cc2af088330624b6bfe7b01c0737eee17c9c4371081
```

`iter_indexed_flat_rzip_entries` now validates the size table and preserves those
runtime IDs. Model preview and coverage consumers also translate the existing
texture manifests' physical ordinals through that table. Standalone texture
archive numbering and repacking remain physical and byte-preserving. Preview
manifests record both identity domains; the correction uses table contents,
not a hard-coded subtraction or per-texture image override.

## Cached triangles survive state commands and display-list returns

The correlation decoder previously cleared its remembered VTX command on every
non-triangle command. Matrix changes, material changes, and returns from called
lists therefore hid valid triangles from composition. These operations do not
invalidate the RSP vertex cache. Clusters now retain the load and record the
actual triangle-command start and end separately, so material correlations use
the correct draw span. A matched command prefix grants only its captured face
count, never the unmatched remainder of a static cluster.

Existing raw traces are retained. Activity and material extraction refresh the
derived correlations from hash-checked command-buffer and nested-list captures;
matrix, texture, light, and normal captures stay attached to the original draw
state. Tediz entry 90 now includes 27 clusters and all 338 source triangles,
instead of 16 clusters and 180 triangles. Across all observed character and render-to-texture compositions,
327 clusters contain 4,555 source faces and 4,549 retained preview faces. The
render-target split below keeps their roles separate.
The external high-detail Tediz OBJ has 333 faces. That remaining five-face
difference is not erased or relabeled as an extraction defect without evidence.

## Mipmap bases and neutral-pose renders

Correcting the texture IDs also removes the premise for withholding ordinary
character trilinear textures. The accepted first cycle is exactly `G_CC_TRILERP`
from `lib/ultralib/include/PR/gbi.h`: `(TEXEL1 - TEXEL0) * LOD_FRACTION + TEXEL0`
for both RGB and alpha. At fraction zero it is the stored highest-resolution
image. Only that exact cycle followed by the already-supported character colour
stage is admitted, with a proven second tile and valid pixel/TLUT spans. Other
two-texture combiners remain unresolved. This alpha formula ignores vertex
alpha; the preview therefore preserves RGB while forcing that unused factor
to one, including the eight models with non-opaque source vertex alpha.

Twelve Haybot reference images match the corrected ROM image dimensions and
every RGB component after normalizing both to their original five-bit channels.
This includes six images formerly withheld by the blanket mipmap rejection.
The resulting base bindings restore the metal hands and body panels. glTF
consumers generate their own lower mip levels; `textureLodPreview` explicitly
records that native distance-dependent LOD parity is unverified. Dynamic colour,
lighting, detail-texture blends, and secondary-pass appearance remain distinct.

Blender automatically assigns the first imported Action. The deterministic
preview renderer now imports a temporary animation-free JSON view when needed,
preserving original node and skin transforms and external assets. It does not
reset Blender pose bones, which would erase required skin corrections. The
original animated glTF and all its Actions remain unchanged.

## Captured native formats

The captured-image decoder also treated every four/eight-bit image as indexed,
even when the task disabled TLUT lookup. The explicit palette-disabled state
occurred in 327 previously bound aggregate variants. Format selection now uses
the actual runtime tile and OtherMode: RGBA4/8 and I4/8 read as intensity with
`G_TT_NONE`, and IA8 preserves separate intensity and alpha. This follows the
[GLideN64 texture dispatch table](https://github.com/gonetz/GLideN64/blob/41c7ba273a6c9afb43c0574cf3cf5d139182d070/src/Textures.cpp#L518).
A retained palette no longer supplies colour when lookup is disabled. Missing
mode evidence, unsupported formats, and runtime size/addressing changes that
require different UVs remain unbound.

Against the same 19 aggregate tasks, 145 existing variants across six models
have corrected pixels, 233 unsupported bindings are removed, and six newly
bounded images become available. At that stage, 1,441 captured variants in 506
material records use 287 distinct base PNGs: 801 CI8, 489 CI4, 98 I8, and 53 IA8
variants. The renderer-return catalog then had 804 captured variants, including 24
IA8 variants, in 152 records and 61 base PNGs. Material observations and raw trace
bytes are unchanged; these are format and binding corrections.

## Render-to-texture geometry is separate from the character body

The gray shell around Conker was produced by merging an offscreen pass into
body geometry. `func_15184FA4` emits `FF48003F` with the address loaded from
`D_800DF088`, calls `func_1502CCFC` at `0x1518514C` with draw mode 3, then samples
that target as I8. The call returns to `0x15185154`. This identity classifies the
pass generically; a model number, an extra-part label, or draw mode 3 alone does
not authorize removing geometry from body composition.

The captured Save-Game-13 task confirms the consumer chain:

| Flattened command offset | Command / address | Role |
| --- | --- | --- |
| `0x0E68` | `FF48003F 800DE080` | Select 64-wide, eight-bit render target |
| `0x0FA8` | `DE000000 80202628` | Call entry 4's selected list |
| `0x16A8` | `FD900000 800DE080` | Sample the produced target |
| `0x1760` | `FF100123 803D6300` | Restore the 292-wide, sixteen-bit target |
| `0x1B18` | `DE000000 801EFE38` | Call entry 0's main list |

The source is `asm/nonmatchings/game_1B1600/func_15184FA4.s`; the renderer hook
also captures the exact return address. The trace decoder now retains each
triangle command's current color-image descriptor, including changes across
called-list returns. The ignored `captured-color-targets.json` report under
`build/assets/models/reference/conker-pass-review/` joins that state to the
existing source-model correlations.

All 21 observed mode-3 calls through this caller are now represented separately
from the 50 remaining character calls. Their source geometry and matrices are
preserved in three neutral and 21 posed `render-texture-*` glTF files, tagged
with `extras.renderPass`. Normal and render-to-texture calls no longer share a
composition or matrix-observation bucket. The nine body compositions contain
261 clusters and 3,494 source/drawable faces; the three render-to-texture
compositions retain the other 66 clusters and 1,061 source faces. The
`render-pass-audit.json` report proves that every original neutral cluster and
every original instance's cluster union is preserved, with all 71 calls still
accounted for. Coverage exposes `render_to_texture` separately from
`character_composition`, and Blender validation includes the additional files.
The 240-polygon increase in Blender's aggregate audit consists of three
80-polygon armature display shapes generated by the importer. It does not
represent additional exported model triangles.

The two positive review submissions resolved all 31 called lists in the
geometry task. Vertex probes matched every source vertex byte for entries 0
and 4: 14,608 and 2,784 bytes respectively. The first capture exceeded a
128-light limit; repeating with a 512-record bound covered all 210 referenced
light records. These review traces remain separate from the canonical 19-task
material corpus.

The offscreen glTFs document source geometry and captured model transforms;
they do not reproduce the projection, coverage, blending, or generated target
pixels. In particular, an image read from RDRAM before graphics submission does
not establish the pixels of a surface written earlier within that same task.
Full TMEM and render-target feedback remain raster frontiers. Conker's body
preview no longer contains the offscreen shell; dynamic facial inputs, captured
lighting/colour reproduction, and native raster parity still require work.

## Selected texture tiles and captured coordinate origins

The static decoder previously treated tile 0 as the render tile regardless of
`G_TEXTURE`'s selected base tile. It now tracks every tile and its own
`SetTileSize` bounds, resolving the active tile when triangles are emitted.
This corrects 63 material runs across 29 characters, containing 931 source faces, without
changing any material-run or triangle boundaries in any of the four banks.
Missing selected tiles remain unresolved rather than borrowing tile 0.
This agrees with [GLideN64's `gSPTexture` consumer](https://github.com/gonetz/GLideN64/blob/41c7ba273a6c9afb43c0574cf3cf5d139182d070/src/gSP.cpp#L2019).

For example, Conker entry 0 run 29 selects tile 4 through `D7002402`.
Its `F5080800 04014050` descriptor selects a 32x32 eight-bit image, while
tile 0 describes a different 64x32 four-bit view. The runtime enables RGBA16
palette lookup, so the selected facial image is CI8. The renderer-return
capture also sets `F2002002 0407E07E`: a half-texel origin in both axes.
Those bounds are absent from the independently callable stored model list.

The trace refresh now replays tile bounds from hash-checked raw command
buffers, retains them alongside the original recorded state, and verifies
that every triangle command offset and count still agrees. It preserves
per-tile state across called-list returns. Captured texture records carry the
coordinate contract used to decode their images. Unclamped LoadBlock tiles use
their mask dimensions when the complete image fits the lower 2 KiB of TMEM;
fractional or wrapped tile origins scroll that image without redefining its size.
Both standalone and composed OBJ/glTF exports apply that same contract to their UVs. Ambiguous
variants do not donate a coordinate state to another appearance. Runtime
changes to addressing or scale beyond the supported contract still remain
unbound, and full TMEM/raster behaviour remains a separate frontier.

The current catalogs contain 1,474 captured variants in 512 material records
(289 base PNGs) for graphics-task observations, and 834 captured variants in
156 records (61 base PNGs) for renderer-return observations. The selected CI8
eye texture is visible in the Save-Game-13 posed preview. Ordinary compositions
link 162 neutral and 1,431 posed runs before the unused-combiner-input correction below, including
1,389 posed captured-image bindings at that stage. The independent before/after audit preserves all 14,581 aggregate
and 12,486 renderer-return draw identities and loses no previously bound draw.
It gains 102 and 116 captured-image bindings respectively; 30 aggregate draws
also change pixels after correcting their image dimensions. These counts refer
to draw observations, not distinct material runs. This resolves the missing pupil image; captured lighting/colour
reproduction remains visibly different from neutral previews.

## Captured images are not automatically sampled textures

The renderer-return previews attached a captured image whenever its bytes and
coordinates were available, including draws whose combiner has no `TEXEL0` or
`TEXEL1` input. In the Save-Game-13 Conker preview this incorrectly coloured
parts of the muzzle and gloves using a retained image. The common
`FCFFFE8F F517F8FF` formula depends on vertex shade, environment, primitive,
and `K5`; missing captured `SetConvert` state does not introduce a texture input.

Texture eligibility now checks both captured combiner cycles independently of
lighting and constant-factor translation. Every variant must have known
one/two-cycle state before texture absence is proven. Copy mode, missing mode
or combiner state, alpha-only texture use, and unresolved `TEXEL1` expressions
do not trigger suppression. Direct glTF encoding applies the same rule, and
static fallback bindings cannot bypass it. Captured PNGs and runtime material
observations remain in their evidence catalogs.

This removes 457 false bindings over 5,552 faces in 22 ordinary posed previews.
Standalone and neutral linked counts remain unchanged because those aggregate
appearances already lacked an unambiguous image for these runs. Ordinary posed
compositions now link 974 runs and 12,229 faces, with 932 captured-image bindings
(683 CI8, 225 CI4, and 24 IA8). Both composition families together copy 114 PNGs.
The ignored `combiner-normal-audit.json` records per-file changes and unchanged
source/preview face counts. Conker's muzzle and gloves now retain their source
colours instead of receiving the unused texture.

## Posed exports preserve authored surface normals

The pose baker previously discarded all source normal bytes after transforming
positions. Without a `NORMAL` attribute, [glTF requires flat normals](https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#meshes),
which explains the faceting despite valid topology. The exporter now transforms
each corner's source normal through the inverse transpose of that corner's
vertex-load matrix, normalizes it for glTF, and stores the floating-point
interchange normal separately from CBFD's signed source bytes. Translation does
not affect normals. Non-uniform scale, reflections, and triangles spanning
several matrix slots are covered by regression tests.

Across 44 ordinary posed exports, 55,170 corners retain transformed source
normals and 1,494 use geometric fallbacks. The 21 offscreen posed exports retain
12,163 transformed corners with 62 fallbacks. Zero/missing source vectors and
singular normal transforms use the geometric fallback; face filtering preserves
normal-to-corner alignment. These normals improve ordinary interchange shading.
They do not claim to reproduce the game's vertex lighting, combiner constants,
or framebuffer output. The existing renderer-return captures omit light bytes
and inherited conversion state. Those missing inputs remain explicit appearance
frontiers; full-task colour replay now uses the corrected position space below.

## Captured lighting follows vertices into the cache

The old lighting approximation applied the draw-time matrix/light/normal state
to source coordinates. The CBFD consumer instead lights a vertex when it is
loaded, after its model-view/projection transform and before perspective division.
The tracer now retains both matrix chains and each triangle corner's vertex-load
identity, then captures the actual VTX bytes. Hash-checked replay leaves original
material-state hashes unchanged. The exporter joins runtime cache slots to the
stored source-face order, which differs for the four triangles in TRI4 commands.
It verifies source XYZ before assigning the captured colour, including any
CPU-updated vertex RGB. Source-face identities survive filtering and posing, and
vertices shared by differently lit corners remain separate in glTF.

The vertex-complete Save-Game-13 capture supplies 1,085 consistent face-colour
samples across bank-01 entries 0 and 4 and bank-04 entry 27. Its capture-specific
previews have 42 fully covered runs: 876 faces and 998 floating-point colour
vertices. These materials use `KHR_materials_unlit`; the baked colours are not
lit again by the interchange viewer. Blender imports all 1,314 files in this
four-bank review set. Evidence, previews and the per-run binary audit are under
ignored `build/assets/models/reference/vertex-light-export/`.

Captured XYZ/cache-slot agreement across every draw in a cluster now resolves
17 previously ambiguous clusters (58 draws). Identical geometry in multiple
models or source spans stays ambiguous. This increases the isolated catalog
from 52 to 61 material records and covers all 811 Conker body faces, including
the restored eyes, without a model-specific rule. The aggregate catalog gains
four bank-04 bindings for 197 faces. The new render is
`build/assets/models/previews/conker-captured-colours-bind.png`; it uses a neutral
pose with captured colours and is not a pose-matched gameplay frame.

The character trace's old DMA-only boundary filter also admitted audio tasks.
It now requires a verified OSTask type of 1; known non-graphics task bytes are
excluded from material replay. The earlier lighting audit's second event is
confirmed type 2. The original 416 lightweight boundaries in the character
traces did not retain task headers and are reported as untyped. Their existing
RSP boundary indices remain stable, without proving graphics submission.
A corrected 600-second capture reached one initial graphics task and two
renderer returns, but timed out before a following graphics task. No pose is
assigned lighting from that initial task merely because it is nearby in time.
That dummy-renderer trace, boundary audit and regenerated export audit are under
`build/assets/models/reference/submitted-character-lighting/`.

The follow-up uses pinned CXD4 RSP LLE and Angrylion RDP Plus under Xvfb. The
default dummy video plugin does not signal DP completion, explaining the earlier
scheduler stall. The software run captures two actual graphics tasks around two
renderer calls. Both generated ranges are byte-identical in task 2 and execute
exactly once, with matching nested geometry and triangle counts. The submitted
matrices at the same addresses supersede the earlier float matrices; slots 13
and 14 have zero linear transforms, removing 34 ear triangles. Material evidence
is scoped to the proven caller range, preventing another instance's shared-list
observations from being substituted. The resulting Conker body has 777 drawable
faces from 811 source faces, all with captured colours. Native screenshots show
the green helmet, subsequently recovered by the attachment follow-up below.
The canonical trace replacement retains all 71 calls and 128 part selections,
with 400 old untyped boundaries and two verified graphics submissions. Evidence,
native screenshots and regeneration commands are under
`build/assets/models/reference/software-submitted-lighting/`.

Captured vertex agreement now gates unique command-pattern matches as well as
ambiguous candidates. A falsely assigned tank-flag draw had matching command
shape but different captured positions. Fourteen assignments in the new capture
and seven in the aggregate catalog are now excluded as unproven. Older traces
without vertex bytes retain their weaker command-only evidence. A separate
vertex-complete Tediz task captures two 338-face instances; their colour variants
are kept separate because sharing a list does not prove shared lighting.

The attachment follow-up captures `func_150311C4`'s selected part and return
hooks. It resolves bank-09 entries 29 and 133 to the same parent character and
bone 12, with command ranges `0x8011C788:0x8011C818` and
`0x8011C818:0x8011C8A8`. The first has 16 vertices/20 faces; the second has 69
vertices/58 faces. All captured positions agree with the source payloads, and
part pointers yield consistent loaded bases `0x80192B60` and `0x801900C0`.
The only changed display-list arguments are texture pointers and the proven
normal-stream relocations. The final task buffer and every captured matrix
are byte-identical to the body-capture task. The parent hidden-bone mask is
`0x6000`; `func_15034728` clears each selected bone's 3x3 linear transform,
called by `func_150347E8` immediately before palette conversion.

`func_1502FE10` explicitly loads `[09, entry]`, derives the part count from the
first header pair, relocates the part pointer table, and exposes vertex base
`+0x18`, normal data from pair 2 and optional joint metadata from pair 1.
`func_1502FFD8` copies the vertex range for double buffering when required.
The production parser now includes all 155 matching containers with 10,235
vertices and 8,896 faces, alongside the six existing direct-header bank-09
models. It validates every declared range, independent part boundary, normal
pointer and joint hierarchy. Reconstruction uses decoded vertices, part pointers
and joint fields plus hash-checked opaque regions; all native bytes agree.
The 35 jointed attachments use the same pose builder as character models:
`func_1503F4B0` passes their joint table to `func_150A81D0`. Their neutral glTFs
preserve that hierarchy; parent placement and animation require runtime evidence.
Of the 483 nonempty bank-09 entries, 322 still lack a classified model contract.

The posed review identifies entry 29 as the cigar and entry 133 as the helmet.
Captured RGBA32 materials resolve the previously white straps and front panel.
The admitted contract is a complete zero-DXT LoadBlock at TMEM origin zero,
with RGBA32 image/render formats, no palette lookup, matching stride and byte
count, and the eight-byte odd-row swap already proven by `texture_native.py`.
Partial loads, nonzero origins and incompatible state remain unsupported.
All 78 attachment faces carry captured per-corner colours and resolved texture
images from their exact ranges in graphics event 5 of the attachment trace.
The normal composition exporter now accepts repeatable `--attachment-trace`
inputs. It pairs selected parts and returns by record/stack identity, checks
native part pointers and relocations, and proves that the selected parts cover
all submitted triangles in the renderer range. Body association requires the
same parent pool slot/model/root, submitted command bytes and attachment matrix
hashes. The body's submitted task supplies vertex attributes, normals and
material observations; an unrelated render-target image differs between the
two captures and is not treated as interchangeable. Missing/ambiguous parents
and mismatched matrices remain unresolved instead of receiving guessed poses.

The canonical Save-Game-13 composition has 889 source faces and 855 drawable
faces, preserving the original body's 777 drawable faces and all 78 attachment
faces. All 855 use captured vertex colours. Its rendered pixels exactly match
the earlier isolated joined review. The binary data and material records of the
body remain unchanged inside the joined glTF. Other 43 ordinary poses and all
render-to-texture compositions retain their geometry counts. Evidence, source
inventory comparisons, `composition-audit.json` and the original isolated review are under
`build/assets/models/reference/software-submitted-lighting/attachments/`.

Aggregate previews require agreement across every observation of a face. Missing
projection/vertex inputs in older traces therefore prevent a bake. The previous
161 draw-time approximations have been removed, while source-face and texture
binding counts remain unchanged. Full runtime appearance still requires more
captures, submission-state linkage for the remaining character poses, and the remaining
combiner/raster inputs. The capture-specific colour proof does not establish
complete native appearance for the whole model or corpus.

## Verification boundary

All four model banks still verify byte-identically. Regression coverage includes
empty texture slots, changed table extents, physical-to-runtime catalog mapping,
cached vertices across state commands and returns, bounded prefix correlations,
hash-checked trace refresh, the exact trilinear colour formula, native runtime
formats, unused palettes, incompatible runtime addressing, caller-proven
render-to-texture classification, separate exports, coverage roles, and target
state across display-list returns, selected nonzero tiles, fractional/wrapped
origins, image/UV dimension agreement, projection/matrix stacks, captured vertex
bytes, per-corner lighting and source-face identity. The complete unit suite
passes 564 tests, including attachment reconstruction, invalid ranges/joints,
independent-part cache isolation, captured RGBA32 pixels/alpha, attachment
submission matching, missing-part rejection and runtime vertex/normal inputs. The main
Blender validation imports 1,546 glTFs, 3,088 meshes,
399,100 polygons and 2,621 Actions. Its mesh/polygon totals include Blender
armature helper geometry; source-face counts come from the glTF accessors.
The captured-colour review set validates 1,469 glTFs, 2,997 meshes and 370,596
polygons, also with 2,621 Actions. Current per-file texture/buffer
fingerprints are in `build/assets/models/blender-validation.json`; current
coverage is in `build/assets/models/us-coverage.json`.

Review images are under `build/assets/models/previews/`, including
`tediz-front.png` and `haybot-reference-review.png`. Prior renders remain in
archive directories. Dynamic facial inputs and other unresolved runtime
material inputs remain visible limitations. Successful import and the two
reference comparisons do not establish visual parity for all 1,186 models.
