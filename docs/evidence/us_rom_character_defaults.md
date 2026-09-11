# ROM character appearance defaults

`./conker model-assets preview --bank 01 --rom-defaults` resolves the ordinary
character renderer's initial facial texture selection from ROM data. It rejects
`--runtime-materials` and `--runtime-appearance`. Captures are optional validation
references, never exporter inputs. The preset uses the initializer's selectors,
zero blink selectors and no expression override; it does not describe every
possible gameplay appearance.

Instance-dependent materials may use a separately recorded ROM-proven preview
preset. [Wise Guys entry 59](us_wise_guys_shirt.md) selects the first multiplayer
shirt variant after its generic initializer; the raw header remains unchanged
in the manifest. It is not a universal shirt selection for every instance.

Regenerate the separate ROM-only corpus without overwriting captured exports:

```sh
./conker model-assets preview --bank 01 --rom-defaults \
  --output build/assets/models/rom-only/us-bank-01-preview --force
./conker model-assets validate
./conker model-assets inspect
```

## Address and byte evidence

All addresses below refer to the US ROM with normalized SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The exporter verifies consumer
instruction words against the decompressed ROM executable. The manifest records
those words, each indexed asset's ROM span and decompressed hash, its default
header hash, selected descriptor, texture offsets and pixel/palette hashes.

1. `func_1503D774` passes a two-component indexed path with bank `0x11` and
   character index to `func_1502B6BC` at `0x1503D7C8`. The immediate at
   `0x1503D7B8` is `0x11`; `0x1503D7C0` supplies path length two. This is distinct
   from animation bank `0x02` and placement bank `0x0B`.
2. `func_1502B6BC` traverses the indexed ROM table at `0xAB1950`, decompresses
   through `func_1502B350`, and relocates the two requested descriptors through
   `func_1502B4A8`. `func_1503D774` stores the first segment pointer in
   `D_800D1C90[character]`.
3. All 186 present bank-`0x11` assets have a 16-byte descriptor header followed
   by a 64-byte default segment. The optional second expression segment starts
   at byte 80; its size has the terminal high bit set. The parser checks ranges,
   empty descriptors and zero alignment padding without altering the payload.
4. `func_150839B8` copies default-header bytes `0x3B` and `0x3C` into actor bytes
   `0x68` and `0x69` at `0x15083A50..0x15083A5C`. `func_1507E5C8` may later
   replace them for an expression. That override is outside this preset.
5. `func_1502F01C` selects segment 6/7 through the three-value blink tables at
   header offsets 8/11, and segment 10/11 through actor bytes `0x68`/`0x69`.
   Selection uses a 12-byte descriptor stride (`0x1502F17C`) in
   `D_800C5338[character]`. `func_1503DC3C` loads each descriptor's flat ID at
   offset 4 through `func_1510D0EC`, storing the resulting base at offset 0.

The special renderer `func_150911F4` separately selects four flat IDs from
`D_800D24C8`; its state is not the ordinary model-default contract.

## Display-list texture contract

The parser now retains explicit segmented TLUT loads. For example, Conker
entry 0 loads pixels from segment 11 at offset zero (`0x5328` in the model),
then its palette at offset `0x400` (`0x5350`, followed by LoadTLUT). Segment
10 does the same. Segments 6 and 7 address their palettes at `0x800`.
These are explicit offsets, not assumed trailing palettes.

The ROM decoder requires a valid selected descriptor, proven image dimensions,
a supported combiner, bounded LoadBlock/LoadTLUT spans, compatible render/load
tiles and RGBA16 lookup mode. For a segment-8 OtherMode call it checks that all
11 ROM table variants agree on lookup mode; it does not choose a blending pass.
Pixel decoding applies the recorded TMEM stride and odd-row word swap. Missing
evidence, overlapping spans, transparent combiner-dependent images and
unrecognized multitexture formulas remain unresolved. Retained texture state on colour-only
draws does not cause an image to be assigned.

The expanded ROM-only corpus contains 183 characters and links 215 default
facial material runs covering 2,542 exported faces, an increase of 15 runs and
173 faces. Another 28 segmented runs do not sample a texture; 22 remain
unresolved: six palette bindings, three TMEM spans, three payload spans and
ten transparent images with unresolved combiner behavior.

`func_1502F01C` supplies only descriptor pointers to segments 6/7/10/11; it does
not use descriptor dimensions to set tile bounds. Explicit SetTileSize bounds
can therefore supersede descriptor metadata when the full LoadBlock/TLUT and
payload spans agree. This resolves three runs. It does not resolve Haybot run
16: its selected descriptor cannot supply the complete requested image and
palette. No neighboring asset or alternative selector is guessed.

Twelve other runs use the exact two-cycle G_CC_TRILERP character formula
`FC26A080 151492FF`. The decoder requires two-cycle, clamped LOD mode, all ROM
mip tiles, matching format, halving masks/shifts, nonoverlapping TMEM extents,
and a payload span ending before the palette. The diffuse PNG is the base
image at LOD fraction zero; glTF does not reproduce native distance-dependent
interpolation. Manifest evidence retains every mip's dimensions, stride and
ROM byte offset. Haybot run 26 uses flat ID 3826 with mip offsets 0, 1024, 1280
and 1344 and a 256-entry palette at 1376. Conker entries 0, 1 and 130 still
resolve all four facial runs; Haybot now resolves two of its three.

## Verification and inspection

Batch validation reconstructs all default bindings from the ROM, checks the
exported provenance and exact PNG bytes, and separately compares 12 facial
runs across entries 0, 1 and 130 with existing captured PNGs. All 12 match byte
for byte. This proves those texture selections, not native raster, lighting,
expression animation, UV-origin or part-visibility parity.

The local audit under
`build/assets/models/reference/rom-defaults-work/export_without_captures.py`
regenerates the corpus while rejecting capture/research-output reads; its
`export-read-audit.json` records actual file reads. No captures are required.
Tests cover descriptor bounds, changed consumer instructions, explicit palette
offsets, odd-row swizzling, incomplete load state, disagreement between ROM
lookup tables and rejection of captured material inputs.

The inspection index starts with `conker-rom-defaults.glb` (rig, 764 ROM
animation Actions and 16 stored shape keys) and `haybot-rom-defaults.glb`.
Only ROM-derived exports are displayed; captured copies remain archived as
comparison evidence. [Bank-13 position morphs](us_character_morph_targets.md)
add shape keys to ROM-default models 0000 and 0058 without changing their neutral
pose. Initial reference renders remain separate from pre-existing baselines.

The inspection configuration enables `rom_only`. Publication checks the
selected source model's preview manifest and material records, rejects captured
compositions and runtime material evidence, and requires the ROM-default corpus
for characters. It repeats the provenance check before writing any gallery
files. A mixed comparison corpus may still supply an individual model whose
selected record uses no captured data. The inspection manifest records this
per-model ROM provenance.

The ordinary preview now selects the [primary character draw table](us_character_draw_tables.md)
for 31 models instead of overlaying a separate renderer-mode-three table.
Raw extraction retains both tables. Additional direct RGBA32 textures and IA4/I8
mipmap bases are accepted only when all eleven ROM segment-8 variants produce
the same texture. The latter path checks every declared mip level, format,
mask, shift, stride and TMEM extent, including the RGBA16 LoadBlock transfer
tile. These paths link 47 more runs and 851 faces across ten models. No effective
blending pass is chosen from this agreement. Both bind and animated glTF files
retain the full table evidence in `romTextureStateConsensus` material extras.
An additional exact two-cycle formula, `FCFFFE80 F514F8FF`, uses texture RGB
but obtains alpha from shade and environment state. Its I8 image therefore
stores intensity in RGB and one in texture alpha, preserving the separate
vertex and renderer alpha contract. This recovers another 53 runs and 1,141
faces across entries 0048, 0118, 0150, 0151 and 0152. The decoder checks all
eleven ROM state variants, bounded LoadBlock rows, the RGBA16 transfer tile,
I8 render format and two-cycle tile-LOD mode. It does not infer runtime
primitive/environment colours or claim native pixel parity for these runs.

Explicit OtherMode IA8 draws now reach the same verified mip-chain decoder.
Previously the direct intensity path rejected any combiner sampling TEXEL1,
even when the exact G_CC_TRILERP formula and complete mip ladder were present.
The new route still requires two-cycle, clamped LOD mode, no TLUT, the RGBA16
transfer tile, zero-DXT LoadBlock, matching formats, halving masks and shifts,
and bounded nonoverlapping TMEM and payload extents at every level. Unsupported
draws retain the existing unresolved result.

This restores three runs on 48 faces each for entries 0015, 0070 and 0076,
plus one run on four faces for entry 0151: ten runs and 148 faces altogether.
The three flower variants share flat asset 2246 and a 32-by-32 IA8 base image;
their mip offsets are 0, 1024, 1280 and 1344. Its decoded PNG SHA-1 is
`fd887ebd681889acbec1ba122956f65b245801b2`. The PNG preserves ROM intensity
and alpha at LOD zero; runtime colour factors and distance-dependent mip
interpolation remain outside this result. The complete four-bank probe found
no additional accepted explicit IA/I mip runs. Local probe, reproduction and
render evidence is under `build/assets/models/reference/expansion-20260910-one-hour/`.

The ROM-default corpus has 51,552 nonzero-area primary faces, of which 48,511
have linked ROM textures; unresolved materials remain explicit.


## Direct facial formats, RGB mipmaps and invisible overlays

The next bounded extension links 20 more runs and 262 faces across ten entries.
The two newly accepted direct facial formats retain the bank-11 descriptor
selection: entry 0023 uses IA8 flat 3316 on 40 faces, and entry 0119 uses RGBA32
flat 4354 on eight faces. Their PNG SHA-1 values are respectively
`b026a3da6a3abc84063292adac93b5a5c0269ae9` and
`f298ed4dbe82adbe32d8688246f0baa76133c723`. The decoder requires matching
render/descriptor dimensions, an explicit compatible OtherMode, the expected
SetTextureImage format, a supported alpha expression and a bounded source load.
It resolves a copied binding and retains the original segmented binding as
provenance. Entry 0040 remains unresolved because its dimensions and payload
span do not support the requested draw.

The exact RGB-only mip formula `FC269880 1514FEFF` interpolates texture colour
while multiplying texture alpha by shade and environment alpha. Entries 0019,
0035 and 0057 now link six runs on 64 faces. Every declared CI4/CI8 mip tile
must have the expected halved dimensions and shifts, a sufficient row stride,
and nonoverlapping TMEM/load/payload bounds. The preview uses the base image;
unlike the RGB-and-alpha trilinear formula, this variant preserves vertex alpha.
The four-bank scan found no additional matching runs outside bank 01.

Ten default facial runs on 150 faces across entries 0008, 0069, 0082, 0084 and
0146 select all-zero-alpha ROM palettes. They are accepted only when both
combiner cycles preserve zero alpha and the second-cycle blender is
`IN*A_IN + MEM*(1-A_IN)`, with FORCE_BL and IM_RD, no coverage-alpha replacement,
no alpha comparison and no depth update. The images and geometry remain intact;
the decoder does not invent an opaque palette. Missing or incompatible state
continues to return an unresolved result. Entry 0082 requires the stored-expression selection described below to close
the inactive face's eyelids.

Local evidence is under
`build/assets/models/reference/expansion-20260910-late-hour/`. Independent
fresh exports of banks 01, 04 and 09 reject capture/research-file reads. All 88
newly selected gallery source documents, buffers and images reproduce byte for
byte from those exports. These are extraction and importability results;
part visibility, native lighting and distance-dependent raster parity remain
separate questions.


## Explicit Carl expression preview

Carl/Quentin (bank-01 entry 0082) stores both faces in one mesh. Initializer blink
zero selects transparent eyelid overlays for both, exposing both pairs of eyes.
Bank-11 entry 0082 contains three ten-byte expression records with eye descriptor
pairs `(5,5)`, `(5,4)` and `(4,5)`. The inspection preset explicitly chooses
record 1, `(5,4)`, which leaves Carl's eyes open and closes Quentin's eyes. This
is a stored-expression inspection choice, not a claim about initial actor state.
Both faces, the complete rig and all compatible ROM animations remain intact.

`func_1507E5C8` adds ten to each stored descriptor and writes actor bytes
`0x6C/0x6D`. `func_1502F01C` subtracts ten for codes at least ten and bypasses the
ordinary blink lookup table, then binds the selected descriptors to segments six
and seven. The complete 240-byte expression application routine and the
296-byte descriptor path beginning at `0x1502F09C` are SHA-1 guarded. The latter
hash is `d8f5f30395b69f0c6bcd8cbe1461bb914e4ae070`.

The shared selector accepts only stored expressions with no morph change,
no animation action and no reserved flag. It rejects descriptor-code overflow,
out-of-range presets and overlapping instance texture presets. Zero overrides
for segments ten and eleven retain their initializer values. Evidence records
the original and selected descriptor indices, exact preset fields and consumer
hashes. Native expression timing and transitions remain unimplemented.

The closed-eyelid result agrees with the
[Carl reference](https://conker.fandom.com/wiki/Carl/Quentin). The reference
identifies the appearance; the geometry, descriptor choice and image pixels are
all sourced from the ROM. Scanning the other unpublished characters found no
additional missing-texture gains from supported texture-only expression records.


## Explicit stationary tank and undamaged Experiment previews

Entry 0040's header chooses descriptor zero for both headlights, but the
vehicle updater replaces that selection. `func_150ED748` at `0x150EE00C`
accepts model IDs 0040 and 0119. With actor float fields `0x3C` and `0x44`
both zero, it stores blink codes 25 and 19 at `0x6C/0x6D`; the guarded blink
consumer resolves those to descriptors 15 and 9. Their flat assets 4355 and
4368 supply the two RGBA32 images, linking eight previously unresolved faces.
The explicit stationary inspection preset is applied to entry 0040. Entry 0119
retains its separate initializer preview. The complete 256-byte selector span
has SHA-1 `b9a32d2f1c61ad06f2d63f3b2dadddbe614b31bd`.

The character updater loads actor model ID at `0x15061BD8` and calls
`func_150F1CB0` only for entry 0123 at the reviewed branch `0x150622F8`.
That 96-byte helper selects segment-ten descriptor 12 when logical animation
is not 20, and segment-eleven descriptor 19 when damage flags are zero.
The explicit inspection state sets both actor fields `0x84` and `0x2E4` to zero.
The newly selected flat 7161 resolves 80 previously untextured faces; flat 7166
replaces two initializer overlays with their undamaged-state image. Both the
helper and the model dispatch are SHA-1 guarded, with hashes
`4ceb60c5b35d31cc6e2df4d6a5b06b979ffb86e3` and
`acb3c86862962cf9c98de7e18d177209c2c0bcb0` respectively.

Neither inspection state is presented as an actor initializer default. Both
preserve the original selectors and record the explicit runtime fields and
consumer evidence. The normal texture decoders still check descriptor, format,
load, palette and pixel extents. Together with the earlier fixes, this pass
links 24 previously unresolved material runs on 350 faces across twelve entries.
All 88 newly published model sources reproduce without capture reads. The
remaining white surfaces on character 0066 are not resolved by these selectors,
and that variant remains outside the gallery.
