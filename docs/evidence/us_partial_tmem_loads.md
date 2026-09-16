# Partial and split-bank texture-memory loads

The US bank-09 attachments 26, 27, 98, 107 and 157 have complete texture
coverage through bounded display-list replay. Their selected render tiles can
retain bytes from earlier loads or read a different texel size from the last
transfer. The decoder preserves that authored state instead of resizing the
tile to the latest image.

## Supported transfers

The parser records each LoadBlock/LoadTLUT together with its load-time tile.
Replay is bounded to one callable display list. Aligned RGBA16 LoadBlocks with
zero DXT overwrite their destination span in lower TMEM, leaving other bytes
intact. CI8 uses the selected flat asset's complete trailing palette; CI4
can select a 16-entry bank from that same 256-entry upload. Both 16- and
256-entry TLUT uploads preserve lower TMEM.
Every sampled index must have a known ROM source.

For an RGBA32 LoadBlock, each source pixel's red/green halfword goes to lower
TMEM and its blue/alpha halfword goes to upper TMEM. A complete source payload
is required even when only the lower bank is sampled. The upper-bank write
invalidates inherited palette evidence. RGBA8 tiles with TLUT disabled expand
each fetched byte into all four output channels, as I8 does. This path retains
the selected tile's dimensions, stride, odd-row addressing and UVs.

The primary implementations supporting these rules are
[GLideN64's gDPLoadBlock and gDPLoadBlock32](https://github.com/gonetz/GLideN64/blob/master/src/gDP.cpp),
[Angrylion-Plus's RGBA8 fetch](https://github.com/ata4/angrylion-rdp-plus/blob/master/src/core/n64video/rdp/tmem.c),
and [paraLLEl-RDP's texture dispatch](https://github.com/Themaister/parallel-rdp/blob/master/parallel-rdp/shaders/texture.h).
These establish fetch and transfer semantics; they are not native captures of
these Conker draws.

Unknown transfers, unsupported LoadTile operations and unrecognised segment-8
calls invalidate inherited memory. Independent EndDL boundaries reset history.
The validated segment-8 slots contain only OtherMode and EndDL and do not
modify TMEM. Missing bytes, segmented pointers, nonzero DXT, unsupported load
sizes, mismatched palettes and multi-texture combiners remain unresolved.
The RGBA8 path also requires complete explicit OtherMode, no TLUT, tile LOD,
clamped detail mode, two cycles and the stored `FCFF9880 F514FEFF` combiner.
It does not extend the existing CI8 path to RGBA32 loads.

## ROM evidence and inspection states

The geometry, image bytes and command sequence come from the checksum-validated
US ROM (`4cbadd3c4e0729dec46af64ad018050eada4f47a`). No save state, captured
texture, external mesh, palette edit or padding supplies missing bytes.

| Bank-09 entry | Inspection label | Faces | Texture coverage |
| --- | --- | ---: | --- |
| 26 | Black weapon attachment A | 66 | Complete |
| 27 | Black weapon attachment B | 66 | Complete |
| 98 | Pink canister attachment | 30 | Complete |
| 107 | Horizontal black weapon attachment | 66 | Complete |
| 110 | Blue hexagonal canister attachment | 20 | Complete |
| 157 | Helium canister attachment | 64 | Complete |

The three black weapon variants' final two faces use the selected tile 1,
`F5081000 01014060`, an RGBA8 64-by-32 tile. The final flat-3112 load uses
`FD180000`, load tile `F5180000 07000000` and
`F3000000 070FF000`: 1,024 source bytes contribute 512 lower-bank bytes.
The other 1,536 bytes retain flat 3793's earlier RGBA16 load. The later tile-0
definition does not change tile 1 selected by `D7000902`. The final OtherMode
is `EF182C3F 04D049D8`, with no palette lookup.

Entry 157's final two faces use a 32-by-64 RGBA8 tile. Flat 2793 supplies
4,096 RGBA32 source bytes, completely replacing the 2,048 lower-bank bytes.
No earlier payload is needed for those pixels. This differs from the three
partial-overwrite cases and is covered separately by the focused tests.

Entry 98 loads flat 4253 before partially overwriting it with 4255, 4252, 4254
and 4164. Each composed CI8 PNG uses the latest selected palette. Manifests and
glTF material extras retain contributing flat IDs, complete payload hashes,
TMEM destinations and load sizes. Split-bank sources additionally record the
transfer bit depth, lower-bank span and RGBA8 fetch interpretation. Composed
textures do not claim a single flat-payload pixel offset.

All labels are descriptive. Parent ownership, attachment poses, runtime
colours, animation and native raster appearance remain separate work.

## Verification

An independent reverse-ownership audit checks all 8,192 pixels in the four
RGBA8 images against ROM payloads, including alpha and odd-row ordering.
Across four banks, all 1,487 parsed model records retain identical geometry
and material-run boundaries. Of 9,552 eligible flat-material runs checked,
only the four final runs change status; 9,163 previously linked textures keep
their exact PNG hashes, dimensions and families. The bank-09 preview delta
contains only those four glTFs and no changed geometry buffers.

Eight focused replay tests cover partial and complete replacement, byte
ownership, RGBA32 channel separation, palette invalidation, independent-list
boundaries and rejection of missing or incompatible state. Preview review and
packed-file checks establish inspection usability, not native raster parity.
Local audits are in `build/assets/models/batch/tmem-replay/` and
`build/assets/models/batch/rgba8-replay/`.


## Four-bit tile with a full palette: entry 110

`09:0110:00` has 20 faces. Its final eight faces keep tile 1 selected by
`D7000902 FFFFFFFF`: a 64-by-64 four-bit tile, 32-byte stride, palette bank
zero. They do not switch to the later eight-bit tile-0 definition.

The same callable list loads 2,048 index bytes from flat 1552 (2,080-byte
payload), uploads its 16-entry palette, then overwrites the first 1,024 TMEM
bytes from flat 1553 (1,536-byte payload) and uploads its full 256-entry
palette. The remaining 1,024 index bytes still belong to flat 1552. The four-bit
fetch uses palette entries 0–15 at flat 1553 offset 1,024, preserving all alpha
bits. The exporter previously discarded the full palette because the selected
tile had four-bit indices, and replay incorrectly invalidated lower TMEM at
the earlier 16-entry palette upload.

Both load spans are complete. The texture is reconstructed with odd-row
addressing, without padding, changing the selected tile or replacing alpha.
Its PNG SHA-1 is `8c285404238a66b52c874de8bb52cac1e2f877a6`.
The model SHA-1 is `8f3d67b20950ca9613e2f421fc36d46cc89b708a`.
All eleven verified segment-8 tables at offset `0x40` select RGBA16 lookup and
produce the same texture bytes; the effective render pass remains unknown.
This is texture completeness, not proof of native blending or colours.

Local reproducible evidence is in
`build/assets/models/reference/material-fixes-20260916/audit.py` and
`rom-audit.json`. The audit independently reconstructs every sampled byte and
selected palette, checks all lookup variants, and scans all four model banks:
only entry 110 uses the newly supported four-bit/full-palette combination.
The bank-09 before/after manifests differ only in this model's material runs.


Entry 110 is published as **Blue hexagonal canister attachment — ROM 09 / 0110**
(`object-bank09-0110-rom`). Its 20-face geometry and identities are unchanged.

For the entry-110 extension, the focused TMEM suite passes 10 tests and the
model-assets suite passes 177. The three affected corpus exports pass Blender
import and Khronos glTF validation. The packed GLB has zero errors and warnings;
front and rear regression views are reviewed. Final validation reuses all
unchanged imports and renders, with the eight existing appearance exceptions
unchanged. These regression baselines do not establish native visual parity.
