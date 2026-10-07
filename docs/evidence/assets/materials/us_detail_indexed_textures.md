# US scene detail textures and indexed mipmaps

The ROM preview exporter resolves the proven detail-texture layout used by
seventeen bank-03/bank-04 models: 36 material runs covering 1,868 faces. The images
come from flat assets 2689, 3525 and 1141. Geometry, tile commands, palette
selection and texture bytes come directly from the validated US ROM.

## Preview selection

In N64 detail mode the declared base tile is the detail image. For a
non-magnified first mip, the RDP selects the following two tiles instead.
The explicit combiner interpolates TEXEL0 and TEXEL1 using LOD_FRACTION;
at zero fraction it selects the first ordinary mip. The exporter uses this
bounded preview state, including that mip tile's own UV shift and SetTileSize
origin. It does not normalize the ordinary image using the detail image's UVs.

This selection follows `compute_lod_2cycle` in
[paraLLEl-RDP's texture shader](https://github.com/Themaister/parallel-rdp/blob/1cecd042b2619bc505c12bfdc713808386f2b54d/parallel-rdp/shaders/texture.h).
For a maximum S/T derivative of 32 in its fixed-point coordinates, the shader
selects base+1/base+2 and a zero LOD fraction. The inspected source's Git blob
hash is `ae754b168961429d7fe564b499cd0d6c6e7bf741`, verified against the downloaded
bytes. This establishes the selection rule; it does not establish a particular
in-game camera distance or claim native filtering parity.

With RGBA16 TLUT enabled, the detail tile's raw IA4 format reads four-bit
palette indices. It is not a direct IA4 intensity image. The same shader's
TLUT sampling dispatch confirms that interpretation.

## ROM layout and guards

| Flat asset | Ordinary base | Pixel payload plus palette | Palette offset | Loaded bytes | Detail image |
| --- | --- | ---: | ---: | ---: | --- |
| 2689 | CI8, 32 x 32 | 2,176 bytes | 1,664 | 1,904 | CI4, 16 x 32 at offset 1,392 |
| 3525 | CI4, 32 x 64 | 2,048 bytes | 2,016 | 2,016 | CI4, 32 x 32 at offset 1,504 |
| 1141 | CI4, 32 x 64 | 2,048 bytes | 2,016 | 2,016 | CI4, 32 x 32 at offset 1,504 |

Each ordinary image has five mip levels, in tiles 1 through 5. The detail
image occupies tile 0 after the ordinary mip data. All index spans fit below
TMEM byte 2,048 and precede the palette in the ROM payload. Flat 2689's pixel
load also transfers some following palette bytes; these are outside every
validated index span. The explicit TLUT upload supplies the palette colours.

The decoder requires:

- Complete two-cycle OtherMode with RGBA16 TLUT, LOD and detail mode, plus the
  exact RGB/alpha lerp and second-cycle shade formula.
- Same-flat mode-zero CI transfer and mode-one/mode-two RGBA16 palette binding,
  complete LoadBlock/LoadTLUT commands, zero DXT and proven transfer origins.
- Every mip tile and its bounds, halving dimensions and integer origins with
  any authored half-texel bias retained at each level, matching shifts,
  repeating masks, zero palette bank and complete non-overlapping TMEM spans.
- The bounded detail tile, its own shift and dimensions, and complete source
  pixels and palette. Missing or conflicting state remains unresolved.

The parser retains per-tile bounds for detail draws. Different mip origins
prevent adjacent draws from incorrectly sharing one material run. Preview UVs
are separate from the declared source tile state and material identity. OBJ and
glTF receive the same selected coordinates. The manifest and glTF material
extras record the chosen tile, bounds, dimensions and preview scope.

## Verification and limits

Five decoder/parser regression tests cover both CI4 and CI8 pixels, palette preservation,
independence from unused detail/lower-mip bytes, glTF UV output, parser state
boundaries, half-texel offsets, the explicit shade-product combiner and rejection
of unsupported layouts. Two additional validation tests recompute the selection
from ROM and reject altered pixels, UVs, image bindings and selection metadata.
Independent checks cover all
5,120 pixels in the three ordinary base images. Canonical sources and resources
match a separate export that rejects save-state and capture inputs.

Eight coherent scene/object exports are configured for inspection. Texture recovery does
not automatically make remaining fragments or incomplete scenes suitable for
the gallery. Distance-dependent detail blending, native lighting, camera state,
secondary passes and complete scene composition remain unverified.

Local evidence: `build/assets/models/reference/expansion-20260910-usage-budget/detail-indexed/`.
