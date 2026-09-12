# US ROM-default CI8 address wrapping

The ROM-default texture decoder supports complete CI8 loads whose logical
image extends past the lower 2 KiB of TMEM. It reconstructs the index addresses
used by palette lookup rather than reading overwritten upper-TMEM bytes or
discarding the image.

## Addressing evidence

With TLUT enabled, index reads wrap through mask `0x7FF`, followed by the
odd-row four-byte XOR. Palette colours come from the upper-TMEM TLUT. This is
independently implemented in
[paraLLEl-RDP's texture shader](https://github.com/Themaister/parallel-rdp/blob/master/parallel-rdp/shaders/texture.h)
(`sample_texel_ci8_tlut`) and
[Angrylion's TMEM sampler](https://github.com/ata4/angrylion-rdp-plus/blob/master/src/core/n64video/rdp/tmem.c)
(`fetch_texel_entlut_quadro` and its nearest variant).

The inspected Git blob identities are respectively
`ae754b168961429d7fe564b499cd0d6c6e7bf741` and
`e2d5833c2319e6ae16aa2857ec8eb364589785df`. Downloaded source bytes were checked
against those Git blob hashes. These references establish texture addressing;
the model selectors, load commands and palettes come from the validated US ROM.

## Supported ROM contract

Bank `01 / 0010 / 00` uses flat asset 1300 for two seven-face runs. Bank
`01 / 0043 / 00` uses flat asset 2616 for one eight-face run. Both select
44 × 44 CI8 images with 48-byte rows, so the logical image occupies 2,112 bytes.
The pixel LoadBlock is `F3000000 / 0741F000`, through RGBA16 transfer tile
`F5100000` at TMEM zero, with zero DXT. The 256-entry RGBA5551 palette is read
from explicit payload offset 2,112 and uploaded at TMEM word `0x100`.

Rows zero through 41 stay below the boundary. Row 42 wraps after column 31;
row 43 starts at lower-TMEM byte 16 and applies the odd-row XOR. The later TLUT
upload therefore does not supply index bytes for those pixels. All eleven
verified ROM segment-8 tables agree that RGBA16 palette lookup is enabled.

The extended path requires CI8, a non-mip draw, complete mode evidence,
zero load and render origins, an entire ROM-backed image and load no larger
than 4 KiB, and a separate complete palette. Other origins, partial modes,
unsupported transfers and incomplete payloads remain unresolved. Existing
images wholly below 2 KiB keep their prior encoding.

## Exports and verification

The catfish with glasses (`character-bank01-0010-rom`) has its ROM-default
face textures and thirteen ROM animations. The Big Big Guy
(`character-bank01-0043-rom`) has the ROM texture behind its furnace grille;
its twenty-nine animations remain available. Character names and descriptive
variant labels are separate from recovered source names.

Tests verify wrapped pixels and unchanged palettes, prove that changing the
unused upper index bytes does not change the image, and reject invalid origins,
partial state, short transfers and truncated palettes. Independent per-pixel
checks cover all 3,872 pixels of the two images. The canonical glTF, buffers
and textures match an independent export that rejects capture reads.

Local evidence and the reviewed previous Big Big Guy baseline are under
`build/assets/models/reference/expansion-20260910-usage-budget/ci8-wrap/`.
ROM bytes remain unchanged. The checks establish texture extraction and
addressing, not native lighting, dynamic expressions, part visibility or
complete raster parity.
