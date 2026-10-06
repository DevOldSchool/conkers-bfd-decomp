# US direct intensity material previews

The exporter decodes direct IA4 images, supported IA4/IA8 mip chains, and
explicit I4/I8 draws whose alpha comes from SHADE. Each path retains the original payload and requires
proven load, tile, lookup, combiner and payload bounds. Capture inputs are not
needed for these bindings.

## Direct IA4

Bank `01 / 0130 / 00` uses flat asset 1915 for a 64 × 64 IA4 image on eight
faces. SetTextureImage `FD700000`, the sixteen-bit LoadBlock transfer and
the IA4 render tile establish the three-bit intensity and one-bit alpha layout.
The decoder swaps odd rows before selecting visible columns and preserves
both channels. It does not infer IA4 from a retained palette or an unrelated
transfer image.

All eleven verified ROM segment-8 tables agree on the image at offset `0x10`.
The first combiner cycle reads TEXEL0 and multiplies its alpha by SHADE; the
second combines colour with shade, environment and primitive state and
multiplies alpha by ENVIRONMENT. The exported texture retains its own alpha;
the effective runtime pass and colour factors remain separate evidence.

The exported character is labelled **Conker — yellow mech suit** from its
visible geometry, not a recovered source name. Its gallery identity remains
`character-bank01-0130-rom`.

## Intensity colour with shade-only alpha

Explicit one-cycle I4/I8 draws can take alpha solely from SHADE. In that case,
intensity must remain RGB colour with texture alpha one. Repeating intensity
into the PNG alpha would incorrectly make dark texels transparent.

The supported contract requires complete OtherMode, no lookup table, tile LOD,
TEXEL0 as the sole texture input and SHADE-only alpha in both encoded cycles.
It accepts the proven sixteen-bit intensity or RGBA transfer tile at TMEM zero,
with zero DXT and complete row and payload bounds. Unknown inherited modes,
other alpha formulas and incomplete transfers remain unresolved. Existing
opaque exports retain their original PNG bytes.

This resolves 159 textured faces in bank `04`: segment `0024 / 02`, segment
`0049 / 01`, and segments `0049 / 14–16`. The existing `0024 / 02` gallery
export now has this correction on run 118 (flat asset 7283, eight faces). Its
room composition and overall appearance remain unresolved. Other scattered
layers and indistinct planes remain outside the gallery.

## Explicit IA4 mip chains

Bank `04 / 0034 / 00` uses flat asset 1697 in six runs on 477 faces. Its
complete 480-byte LoadBlock contains four IA4 levels: 16 × 32 at offset zero,
8 × 16 at 256, 4 × 8 at 384 and 2 × 4 at 448. Each uses an eight-byte row
stride. The load tile is IA16 (`F5700000`), which transfers the packed IA4
bytes in sixteen-bit units with zero DXT. Render masks halve at each level,
S/T shifts match the level, and no span overlaps or exceeds the load.

Explicit OtherMode selects two cycles, clamped LOD and no lookup table.
The first cycle interpolates TEXEL0 and TEXEL1 for both colour and alpha.
The second colour cycle is `(COMBINED - ENVIRONMENT) * SHADE + PRIMITIVE`.
Two exact alpha expressions are supported: `COMBINED * SHADE`, and COMBINED
alone. For the latter, the glTF vertex alpha is one so it does not introduce
a shade-alpha factor absent from the native formula. The source vertex bytes
remain unchanged.

The exported image is the proven LOD-zero base; native distance-dependent mip
selection, coverage and dynamic colour state remain unverified. The coherent
scene piece is labelled **Circular stone platform with three pillars**.
Additional tests cover both alpha expressions, vertex-alpha handling, base
pixels, unchanged base output when lower levels change, and rejection of
missing levels, overlaps, short loads, mismatched base tiles and partial mode
state. An independent check covers all 512 base-image pixels. Local proof is
under `build/assets/models/reference/expansion-20260910-usage-budget/ia4-mip/`.

## Explicit IA8 shade-modulated mip chains

Bank `04 / 0004 / 27` uses flat asset 862 on 74 faces. The ROM load supplies
1,408 bytes with five IA8 levels: 32 × 32 at offset zero, 16 × 16 at 1,024,
8 × 8 at 1,280, 4 × 4 at 1,344 and 2 × 2 at 1,376. Row strides are 32,
16, 8, 8 and 8 bytes. The IA16 load tile transfers these bytes in sixteen-bit
units; complete bounds, masks, shifts, base-tile consistency and each level
are checked before the base image is exported.

The exact two-cycle combiner interpolates both texture channels in the first
cycle, then multiplies both by SHADE. Complete OtherMode selects no lookup
table, clamped LOD and two cycles. IA8 retains its four-bit intensity and
four-bit alpha, and glTF retains vertex alpha. Unsupported formulas, inherited
mode fragments, missing levels and short loads remain unresolved.

The identifiable **Mesh fence sections** are published as parts/effects. An
independent ROM check verifies all 1,024 base pixels, including odd-row swaps
and both channels. Regression tests also establish that changing lower mip
levels cannot change the exported base image. The selected LOD-zero preview
does not reproduce native distance-dependent filtering or coverage. Local
proof is under
`build/assets/models/reference/expansion-20260910-usage-budget/ia8-mip/`.

## Verification and limits

Regression tests check IA4 intensity and alpha, odd-row addressing, shade-only
alpha, load-format guards and rejection of unsupported states. Independent
ROM-to-PNG checks cover 4,096 IA4 pixels and 45,056 I4/I8 pixels. Fresh exports
reject reads from capture files and unrelated generated model directories;
their glTF, buffers and texture bytes match the published source corpus.

Local proof is under
`build/assets/models/reference/expansion-20260910-usage-budget/shade-alpha/`.
Native lighting, dynamic alpha factors, filtering and complete character or
scene appearance are not established by these texture and import checks.
