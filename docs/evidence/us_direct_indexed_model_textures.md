# US direct indexed model texture images

The direct CI4 preview path now decodes a command-selected image from a larger
payload containing mip levels, padding and a trailing 16-colour palette. A
standalone pixels-plus-palette storage PNG is no longer required to preview that
image. The same helper retains the existing direct CI8 path.

## Source contract

`FD500000` selects a flat payload for a 16-bit transfer. The direct CI4 path
requires a zero-origin, zero-DXT `LoadBlock`, a known load tile at TMEM origin
zero, an explicit CI4 render tile, and a compatible stride and image extent.
The full odd-row word swap must fit inside the loaded bytes and below the
palette in the source payload. The selected pixel span must fit the lower
2 KiB of TMEM.

The following same-index `FD100000` mode-two reference selects the trailing
32 bytes, as established by the shared loader's mode-bit branch. A 16-entry
TLUT upload at TMEM word `0x100`, render palette bank zero, and explicit RGBA16
lookup state are required. Other destinations, unknown lookup state, odd image
widths and unsupported row conversions remain unresolved. A reversible storage
PNG does not override those draw-specific constraints.

For an unclamped tile, the masks establish its repeating image dimensions when
the complete mask-sized image fits the proven load and stride. Image decoding
and UV normalization use that same extent while preserving the tile origin.
This corrects 24 bank-04 runs covering 294 source faces. Clamped tiles and
incomplete mask-sized loads retain their bounds; captured runtime dimensions
remain authoritative.

The output keeps the command-derived image dimensions. It excludes subsequent
mip levels from the base PNG while retaining their original source bytes and
display-list state. This proves the selected image, not native LOD interpolation
or the complete primitive/environment colour calculation.

## Evidence

The pre-change gap report identified 546 direct CI4 runs lacking standalone
images: 535 in bank 04 and 11 in bank 03. The new path resolves 521 bank-04 runs
and nine bank-03 runs, covering 22,315 source faces in total. Fifteen runs lack
proven palette lookup state; one has unsupported odd dimensions. The latter is
bank 04, entry 45, segment 0, run 19: its bounds describe 63 by 63 texels, while
its masks describe a 64-texel period. It needs a separate sampling contract.

The captured-image comparison gains 215 bank-04 CI4 observations. Every decoded
RGBA pixel matches its independently captured texture. Across the prior CI8 and
character CI4 checks, all 1,121 comparable observations match. The comparison
requires equal output dimensions and ROM-identical palette bytes; dynamic or
different-size images are not silently treated as static equivalents.

Four regressions check packed mip payloads with a distinct trailing palette,
invalid load/TLUT/lookup state, and command-derived dimensions taking precedence
over a differently shaped storage preview, plus consistent mask-sized images
and UV periods. The complete Python suite passes 568 tests. All four model banks
still rebuild byte-identically.

The aggregate previews gain texture links on 20,501 source faces across 177
models. Nine previously linked runs covering 70 source faces now remain
explicitly unresolved: seven lack proven lookup state and two have unsupported
odd dimensions. Fourteen existing links gain corrected image shapes. Static
coverage rises from 7,394 to 7,915 resolved material runs; 1,505 remain missing
and 170 do not require textures. These counts describe static image selection,
not complete runtime appearance.

Both complete Blender inventories remain validated: 1,546 main glTFs and 1,469
captured-colour review glTFs. The final validation reimports 57 changed files in
each set and retains prior results only for identical file fingerprints. All
1,186 model identities, 222,842 source faces, placement records and composition
geometry counts are preserved. Haybot and the captured Conker body with cigar
and helmet render pixel-identically to their pre-change previews.

The regenerated scene-4 preview recovers the missing walls and foreground
texture. Source geometry, placement records, character poses and attachment
instances remain separate from texture selection. Complete native material,
filtering and raster appearance is still unverified.

Before images, the gap survey, captured pixel comparisons, regeneration scripts
and validation logs are under `build/assets/models/reference/direct-indexed-mips/`.
The current coverage report remains `build/assets/models/us-coverage.json`.
