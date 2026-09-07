# Conker ROM asset inventory survey

This is a ROM-derived boundary and fingerprint survey, not a semantic asset
map. It changes no function inventory, source-unit boundary, or generated
mapping output. No ROM bytes or decoded assets are tracked in the repository.

## Storage inventory

The existing two-level indexed-bank parser was already complete for retail US,
debug, and ECTS. The initial survey found that retail US and debug also carry a
flat RZIP stream before that index, just as ECTS does. Each proposed end was
validated by decoding every entry until the short zero-filled alignment gap
immediately before the configured asset table.

| Profile | Flat ROM range | Alignment gap | Flat entries | Flat decoded bytes | Indexed entries | Indexed RZIP | Total entries |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| US | `0x1A37E0:0xAB1941` | 15 bytes | 7,760 | 16,305,205 | 2,518 | 1,670 | 10,278 |
| Debug beta | `0x199BA0:0xABBCFD` | 3 bytes | 7,808 | 16,422,677 | 2,562 | 1,716 | 10,370 |
| ECTS beta | `0x246E10:0xB802DF` | none | 8,427 | 19,848,186 | 2,457 | 1,674 | 10,884 |

The extractor now fingerprints every decoded flat and indexed entry in the
manifest. This makes `--manifest-only` sufficient for comparisons and avoids
retaining asset payloads merely to find cross-version matches.

## Cross-version signal

Content identity is more reliable than entry number. Retail US has 7,684
unique flat payload hashes and debug has 7,732; 7,644 unique hashes occur in
both profiles, but only 202 entries match at the same numeric index. ECTS
shares 5,071 unique payload hashes with retail US while only 10 same-index
entries match. Any naming or format work should therefore correlate by decoded
fingerprint first, then use table position and loader call sites as supporting
evidence.

The generated full-asset report, which includes both flat and indexed entries,
found 8,715 unique hashes shared by US and debug. Only 1,296 retain the same
locator, while 7,502 shared hashes occur solely at different locators. US and
ECTS share 5,697 unique hashes; only 10 retain the same locator and 5,687 are
relocated. The report retains locator arrays for the 80 US/debug and 62
US/ECTS shared hashes with duplicate occurrences instead of choosing an
arbitrary one-to-one match.

## First semantic format candidate

Retail US has a separate, bounded font collection outside both asset streams.
ROM `0x40F10:0x42443` contains 95 records followed by 13 alignment bytes before
the game archive. Each record has:

- width and height bytes at `+0x0` and `+0x1`;
- two still-unknown metadata bytes at `+0x2` and `+0x3`;
- a big-endian total record size at `+0x4`;
- grayscale RLE bytes from `+0x8`, with the high nibble as intensity and the
  low nibble plus one as run length.

All 95 records were walked using their declared sizes, and every RLE stream
expanded to exactly `width * height` pixels. This is a suitable first
format-specific decoder and packer because its boundary, record count, and
round-trip invariant are already testable.

## First indexed semantic family

The US indexed loader is the `game_57FA0` family. `func_1502AC88` indexes an
eight-byte table record, caches recently used records, DMAs a missing record,
and returns the relative span needed to descend to the next table. The wrapper
at `func_1502B5C8` starts at ROM `0xAB1950`, follows a variadic path of indices,
then loads the selected payload. This independently corroborates the two-level
table parsed by `scripts/rzip_archive.py`.

The exact Rare MP3 playback call path provides a semantic consumer rather than
an inference from payload size. The game loads a selected entry from bank
`0x16`, receives its ROM address and byte length, and supplies both to
`mp3_play_file`; all 453 nonempty entries begin with MPEG frame sync.
`mp3_play_file` then loads `(0x17, 4)` into
`var8009c650`, `(0x17, 5)` into `__conker_mp3_lookup_base`, and `(0x17, 6)`
into `__conker_mp3_huffman_base`. The matching decoder then relocates pointer
slots 1 through 33 from entry 4 against entry 6. The matching assembly utility
uses entry 5 as two lookup halves separated by `0x2200` bytes.

The ROM index agrees with every code-derived constraint:

| Locator | Proven role | Decoded bytes | RZIP |
| --- | --- | ---: | --- |
| `bank-17:0004` | 36 big-endian Huffman offsets | 144 (`0x90`) | no |
| `bank-17:0005` | combined lookup tables | 17,408 (`0x4400`) | no |
| `bank-17:0006` | Huffman data | 42,000 (`0xA410`) | no |

`./conker mp3-assets verify` checks the 453 MP3 streams and reconstructs the
offset table, covering 456 raw payloads in total. Extraction writes the streams
as sparse-indexed `.mp3` files, an editable JSON offset list, and the two
still-opaque binary tables; packing emits exact bank-entry payloads for later
integration. Bank `0x17` entries 0 through 3 are not named from their magic
values alone, and no numeric beta mapping is claimed.

Entry 6 has type flag `0x80`; the table above says it is not RZIP-compressed,
not that all noncompression flag bits are clear. A future bank inserter must
preserve that distinction.

## First visual family

The flat RZIP archive is connected to the renderer by code rather than payload
appearance alone. `func_15003570` walks it from `0x1A37E0` to create compressed-
offset and decoded-size tables. `func_1510D0EC` loads a selected flat index into
the `D_800B0E58` cache, and `func_1510BF60` resolves custom display-list texture
opcode `-3` (`0xFD`) against that cache.

Exactly 704 US entries have the bounded 2,080-byte CI4 layout: 2,048 bytes of
64x64 high-nibble-first indices and a trailing 32-byte, 16-color RGBA5551
palette. Most use TMEM-ready odd scanlines with the two 32-bit halves of every
eight-byte group exchanged. Reversing that permutation lowers median adjacent-
pixel edge energy by 46.6 percent and produces coherent images for 701 of the
704 entries. Flat indices 1296 and 1297 are linear 64-pixel particle textures;
1620 is blank and is unchanged by either layout. Directional artwork also proves
that source rows use a bottom-left origin: reversing the rows makes the `MILK`
and `SAFE` lettering in flat index 1063 upright. The schema-3 manifest records
the selected row layout and both image origins rather than guessing during
packing.

`./conker texture-assets extract` represents the family as indexed four-bit
PNGs, preserving palette order and transparent RGB channels. `pack` reconstructs
the original decoded layout, while `verify` proves all 1,464,320 bytes round-trip
unchanged. `./conker rzip-pack` now preserves unchanged RZIP chunks, recompresses
only edited texture payloads, retains the 15-byte zero loader gap, keeps the
table fixed at `0xAB1950`, and updates the US CIC-6105 header checksum. A no-edit
run must reproduce the entire source ROM byte-for-byte.

The first full-ROM gates pass. Packing all 704 unchanged texture payloads
reproduces SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`. A deliberate
one-byte decoded edit to flat index 35 rebuilds and validates all 7,760 entries:
only index 35 changes, the other 7,759 decoded hashes remain identical, bytes
before the flat stream and from `0xAB1950` onward remain identical, and the
15-byte loader gap remains zero.

The next decoded-size group demonstrates why shape cannot be inferred from
payload length. There are 1,840 flat entries of 1,056 bytes. A display-list
survey recognizes only direct references whose commands jointly prove CI4,
the trailing palette at decoded offset 1,024, and the render-tile line width.
Thirteen entries have complete, non-conflicting contracts: eight are 64x32 and
five are 32x64. They round-trip through schema-4 indexed PNG manifests without
changing a byte. Twelve other directly referenced entries use `F548` 8-bit
render tiles with 256-entry TLUT loads; survey schema 4 records them as
incompatible with the 16-entry CI4 contract rather than promoting them by
appearance or decoded size.

The dynamic-loader trace now accounts for most of the remaining set without
guessing their format. `func_15000AD0` selects one of seven base indices through
the pointer table at `0x800891BC` and calls `func_1510D0EC` across exactly 360
consecutive flat entries. The survey verifies those code words and table
pointers against the decoded US game archive before accepting the ranges.
They contain 1,573 unique 1,056-byte candidates.

`func_15111AF4` consumes five bases from each of those seven records and calls
`func_15110CFC` with a fixed 60x30 tile step over a 360x360 view. The renderer's
format tables prove that 1,056-byte members use 64x32 CI4 storage with a
16-entry palette at byte `0x400`; the alternate CI8 path uses a palette at
`0x800` and cannot fit a 1,056-byte allocation. The 35 view ranges cover 1,816
of the 1,840 candidates. The renderer also has an exact conditional substitution
path at `0x151111C4:0x15111204`: its bounded coordinate calculation selects the
six entries `5747:5753` before calling `func_1510D0EC`. Four are CI4 and two are
CI8, raising the runtime-proven CI4 count to 1,820. None are now preload-only
and only five lack a recovered runtime reference. Eight runtime CI4 tiles also
appear in the direct 256-entry-TLUT set, proving that those reference classes
overlap. The extractor now preserves 2,526 runtime-selected sources: the 2,520
ordinary grid entries plus the six conditional substitutions. Correct preview
assembly applies the two-entry phase to the
continuous flat stream rather than wrapping the last two rows independently in
each column. Each preview therefore uses `base - 2` through `base + 69`. This
moves displaced upper structure tiles one column right and carries a face's
final pair across the next view boundary. The union adds eight context-only
records and retains fourteen runtime tails, producing 2,534 reversible sources:
1,822 CI4, 707 full-width CI8, and the five compact CI8 records. None of the
compact records is used by the 35 previews after phase correction. A no-edit
tile pack inserted through `rzip-pack` reproduces the complete US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The five still-unreferenced entries are `515`, `517`, `1482`, `1655`, and
`7231`. Each has the exact 64x32 CI4 plus trailing RGBA5551-palette structure,
produces a coherent decoded image, and has a byte-identical counterpart in both
debug and ECTS. None appears in the bounded display-list scan, preload ranges,
ordinary tiled-view ranges, conditional renderer override, game code/data
display lists, or flat-asset display lists. They remain explicitly unresolved;
appearance and cross-version persistence are not sufficient runtime evidence.

## Reference-project lessons

[GoldenEye 007](https://github.com/n64decomp/007/tree/master/assets) separates
proven semantic classes such as fonts, images, music, model/level data, and
demo data. Its image workflow keeps the ROM offset list and semantic name list
as distinct sources, then rebuilds one combined binary. That avoids assigning
meaning from position alone.

[Banjo-Kazooie](https://github.com/n64decomp/banjo-kazooie) extracts its single
asset binary with a dedicated tool into a YAML-backed tree and reconstructs the
binary for the matching build. Conker should follow the same staged contract:
boundary inventory, content fingerprints, proven semantic decoders, and only
then byte-identical repacking and build integration. Neither reference is
evidence that Conker shares its actual payload formats.

## Future editing and recomp integration

Editing, palette constraints, controlled-edit evidence, and ROM insertion are
documented separately in
[Future asset editing and recomp integration](../asset-editing.md). They are not
part of the current decompilation build.

## Next bounded work

1. Trace the renderer-selected primitive/environment colors required by the
   decoded model combine modes; keep unrepresented materials visibly unlinked.
2. Keep CI8 indices 2795, 3560, and 4423 explicitly unresolved until a saved
   gameplay state reaches their runtime consumers; do not infer another
   transform from their isolated appearance.
3. Keep partial or extra-data texture candidates and the five unreferenced CI4
   candidates unresolved until stronger runtime evidence appears.

## Direct CI8 extraction and verification boundary

The CI8 survey requires explicit local render-tile CI8 format, line stride,
tile bounds, full zero-DXT load, a same-index 256-entry TLUT, and matching
decoded size. Conflicting local command contracts exclude an index. Loader
instructions at `0x1510CF0C`, `0x1510CF4C`, `0x1510CFBC`, `0x1510CFCC`, and
`0x1510CFD4`–`0x1510CFDC` are verified against decoded US game code. They also
establish a narrower contract than first assumed: mode bit one selects
`payload_end - 0x200` only when the parser's fifth argument is non-null.

The supplied Mupen64Plus core reaches these exact synthetic game-overlay
addresses. An LLDB hardware watchpoint on `D_800B0E58[3358]` captured its cache
slot moving from `-1` to `0x80134040` at guest PC `0x1510D2E8`. The loader
returned to `func_1510CE60` at `0x1510CF54`; the parser's fifth argument was
zero. The active display list contained `FD500000 00000D1E` for the pixels and
`FD100000 00400D1E` for the 256-entry TLUT. Both therefore resolve to the
payload base, making the first 512 bytes serve as both CI8 indices and palette
data. That is incompatible with this extractor's reversible
pixels-plus-trailing-palette contract, so 3358 remains survey evidence but is
not emitted as a PNG.

527 entries satisfy the conservative storage contract, with 526 outside the
existing tiled-view output. All 1,245,216 decoded bytes round-trip through CI8
PNG. A no-op ROM pack validates all 7,760 flat entries, reports 527 overrides
and zero changed entries, and retains the original SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

Inspection of the generated contact sheets found that the local command proof
is not sufficient to certify every preview's appearance. Human review currently
identifies 56 payloads whose preview geometry is the transpose of their render
tile bounds. All become continuous images while retaining the TMEM odd-row
conversion. Flat index 3091 is one example: the earlier 64x32 interpretation
falsely split one vertical eye into two fragments, while 32x64 reconstructs it.
Index 2376 instead uses a reviewed 16x128 geometry. The reviewed square examples
2795 and 4423 remain noise-like under both supported row layouts. Index
3560 is least discontinuous at the command-derived 32x64 TMEM geometry but also
remains visually unresolved. These three need runtime consumer evidence.
The SDK's `gDPLoadTextureBlockS` contract supports the zero-DXT TMEM-ready
row interpretation, but does not identify
which runtime consumer reaches each embedded display list. The tool leaves
these observations explicit in its manifest rather than claiming every PNG is
visually correct or selecting layouts automatically by image-content
heuristics. Index 3358 is the first direct CI8 runtime capture; its exclusion
also demonstrates why a local display-list pattern cannot by itself prove the
standalone trailing-palette format.

## Direct RGBA16 extraction boundary

A separate scan recognizes flat references beginning with `FD100000` only
when the same local display list supplies an RGBA16 render tile, explicit tile
bounds, matching line stride, full zero-DXT load, and a decoded payload exactly
equal to `width * height * 2`. Six flat entries meet that complete contract:
53, 322, 834, 3286, 3291, and 3292. They cover 19,456 decoded bytes and
round-trip through truecolor RGBA PNGs without changing a byte.

Unlike CI8, these records have no independent palette pointer, so their storage
contract does not depend on the parser's fifth argument. The survey still
labels runtime appearance incomplete: direct RGBA16 consumption is proven, but
semantic names and the appearance of each isolated payload are not.

## Other native-color extraction boundary

The remaining full-payload direct formats use a mixed schema because every
record carries its own proven N64 pixel format. The survey promotes 91 flat
entries: 40 RGBA32, 14 IA8, four IA16, 14 I4, and 19 I8. Each has matching
image and render-tile formats, explicit bounds, exact line stride, a full
zero-DXT load, and no unexplained bytes beyond the rendered pixels. Together
they cover 322,048 decoded bytes.

All five encodings round-trip through RGBA PNGs. IA and intensity formats
enforce their channel-sharing and bit-depth constraints during reconstruction;
RGBA32 preserves all four source channels directly and exchanges eight-byte
halves within each 16-byte group on odd TMEM rows. Narrower native formats use
the ordinary four-byte half exchange. The no-edit pack reports 91 overrides,
zero changed entries, and the original normalized US SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The same scan finds no complete full-payload IA4 contract. References with
partial loads, unexplained trailing bytes, or conflicting consumers remain
unresolved instead of being promoted by visual resemblance. With those cases
and the three complex CI8 traces deferred, the bounded standalone texture
families are sufficiently covered to move format research to indexed-bank
models.

## Rigged character-model geometry and animation companions

`func_1503CF20` loads character models through indexed path `[01,
character-model-index]` and proves the seven offset/size regions in their
56-byte headers. All 183 bank-01 entries satisfy the complete boundary contract.
Together they contain 56,412 vertices, 62,073 directly referenced faces, 67,804
material-local UV coordinates, primary and secondary display-list tables, 3,518
sixteen-byte joint records, 1,772 twelve-byte texture descriptor records, and
182,714 bytes of custom-MoveMem auxiliary data. All 1,742,936 decoded bytes verify
byte-identically; two containers have no triangles and remain retained as model
records rather than being silently discarded.

`func_150A81D0` reads each joint's signed parent-matrix byte, matrix slot,
animation slot and float translation, and writes runtime matrices at a 64-byte
stride. A pinned function trace of entry `0000` proves that the 28 local matrix
translations initially equal the corresponding table floats bit-for-bit. The
submitted-task trace establishes the missing composition step: for example,
slot 1's final translation differs from slot 0 by the transformed, half-scale
version of its stored `(0, 15.34798, 1.133891)` translation. The table values
are therefore parent-relative, not absolute model-space pivots. `DA380003`
commands in the model display lists select those final matrix slots. Every
parent and display-list matrix reference resolves. The glTF export uses the
stored translations directly as local node transforms, accumulates them to
obtain each model-space bind pivot, and emits explicit inverse-bind translations
with rigid per-run `JOINTS_0`/`WEIGHTS_0` assignments across all 183 files. The
source vertices are joint-local and are baked through the accumulated pivot for
the shared glTF mesh. Treating each stored local translation as an absolute
pivot separated child parts from their parents. Each animated file has a paired
`*-bind.gltf` with the same
assembled skin and no Actions, providing an unambiguous Blender geometry check.
The same trace reaches bank-02 pair `0025`, frame `0`. Comparing all 28
local matrices proves that the three stored channels are signed full Euler angles;
transposing the runtime row-vector matrices for glTF preserves that sign and
uses half-angle quaternion construction. All
2,621 nonempty bank-02
timelines now have runtime-proven frame boundaries and decoded skeletal
channels. All 2,621 nonempty clips are exported as glTF rotation, root-motion,
and masked joint-translation channels. The masked `s16` values are local-joint
adjustments at `1/16` scale: `func_150A81D0` adds each vector to the three
translation floats in that joint's local matrix before the separate parent
composition loop. The exporter therefore applies the adjustment directly to
the corresponding glTF node and no longer emits a compensating child channel
for an animated parent. One Conker descriptor supplies four
channels beyond the highest slot referenced by its 28-joint table; those unused
channels remain in the manifest rather than invalidating the referenced subset.

`func_1503DC3C` consumes the fourth header pair as twelve-byte texture
descriptors: a pointer slot initialized with the flat texture index, the flat
index passed to `func_1510D0EC`, and stored width and height. All 1,772 records
satisfy that layout, and every bank-01 display-list flat texture reference is
present in its model's table. The sixth pair is an alternate display-list
pointer table: `func_1503CF20` relocates all 43 pointers in 31 models and
`func_1502CCFC` selects it for an alternate render path. The final pair is an
optional two-byte procedural animation joint-index table. `func_1503DA3C`
bounds its byte lookup by the stored size, `func_15033FE0` requests slots zero
and one, and `func_15034860` turns the returned values into joint-channel
overrides. Across 104 models, all 208 slots are either below that model's joint
count or use `0xFF` as the absent sentinel. The intervening fifth pair remains
preserved and now has a direct display-list consumer: `func_1503D368` recognizes
the exact `DC38000E` command and `func_1503D438` relocates its unsegmented
argument by the model base. There are 2,937 such commands in 181 models. Every
pointer is 32-byte aligned relative to the fifth pair; 2,932 start inside it and
five start exactly at its end, where the procedural-table pointer begins. The
dedicated GLideN64 F3DEX2CBFD implementation identifies selector `0x0E` as the
vertex-normal base. Its vertex loader reads signed X and Y bytes at
`base + cache_slot * 2`, then reads signed Z from the low byte of the ordinary
vertex flag. Replaying that contract produces a normal for every corner in the
same 62,073-triangle command order. The glTF export normalizes each nonzero
source vector. It records and replaces 2,575 zero and 111 unavailable corners
with a geometric preview fallback so glTF consumers never receive invalid zero
unit normals. Those fallbacks are preview-derived, not presented as ROM data.

That normal-stream contract is shared by the direct model families. Bank `03`
contains 79 `DC38000E` commands across 28 models; replay yields 3,884 nonzero
and 415 zero source-normal corners. Bank `04` contains 342 commands across 107
models; replay yields 11,634 nonzero and 5,643 zero corners. Their glTF files
now carry normalized ROM-derived normals, with geometric fallback limited to
the explicit zero vectors. A headless Blender 5.2.1 pass imported all 842
bank-03 and bank-04 glTF files with finite positions and loop normals.

The OpenEmu scene trace additionally captures 83 resolved runtime normal
streams and all active model-view matrices. Keeping those inputs outside the
material-state hash preserves 75 material records and 79 variants while
retaining 96 distinct lighting contexts. A GLideN64-equivalent replay now bakes
all 27 unambiguous texture-times-shade lit runs (2,267 vertices) into
floating-point glTF colours. Headless Blender 5.2.1 imports all eight affected
bank-04 files successfully with finite geometry and colour attributes. This is
emulator implementation evidence rather than independent hardware-microcode
proof.

The character display lists use `FD100000` as an RGBA16 transfer image, then
select an otherwise-invalid 4-bit or 8-bit RGBA render tile together with a
same-index mode-two or mode-one TLUT. That combination proves effective CI4 or
CI8 sampling. The manifest retains both pixel and palette load commands and
reports the effective format. The model loader passes a null fifth argument to
`func_1510CE60` while initially preparing slots, but the render-time paths
`func_1518C900` and `func_15183ACC` pass a non-null rewrite table. In that path,
both mode one and mode two start the palette at payload end minus `0x200`;
mode one loads 256 CI8 entries while mode two loads the first 16 CI4 entries.
The preview exporter mirrors that
selection only for a single-`TEXEL0` combiner and a nominal pixel span wholly
before the runtime TLUT. It links 1,338 drawable material runs and 26,395
preview faces to 408 runtime-composed PNGs. Every `F5` render-tile command is retained with its TMEM
offset, but `TEXEL0`/`TEXEL1` mipmapped combiners remain unlinked: glTF cannot
reproduce their RDP LOD interpolation and dynamic primitive/environment
colours, and binding only the base-level mask produces a misleading material.
An explicit CI8 base-level linking experiment reproduced that failure on the
Conker preview: regular colour TLUTs remained coherent, but packed mask assets
became false multicolour surfaces. Those runs therefore stay unlinked rather
than being presented as decoded diffuse textures.

The missing colour input is now bounded. `func_1502CCFC` emits primitive colour
command `FA00F200` and environment colour command `FB000000` before the model
display list. `func_1502CC34` resolves three-byte RGB entries from
`D_800D9B68` and `D_800D9B78`; alpha is supplied by the render caller, and
`func_1502EC34` can override channels for character effects. `func_150006E0`
initializes the tables and `func_1510CB10` updates them. This proves the colours
are character-state dependent, not constants recoverable from the model file.
The glTF and extraction manifest retain that runtime dependency rather than
baking guessed base-colour factors.

Character facial images are also stateful. `func_150911F4` reads four `u16`
texture IDs from character state `D_800D24C8` offsets `0xB0`, `0xB2`, `0xB4`,
and `0xB6`, resolves each through `func_1510D0EC`, and emits segment-base
commands for segments `6`, `7`, `10`, and `11`. Bank-01 display-list references
to those segments are therefore preserved as dynamic slots rather than being
linked to a visually similar global texture.

`func_1503D984` counts the same one-, two-, and four-triangle display-list
opcodes decoded by the exporter and confirms the aggregate 62,073 faces. It
counts 811 triangles for entry `0000`, whose header has no secondary display
list; a larger external Conker mesh is therefore not evidence that ROM geometry
was omitted.

`func_1503D774`, called from the same character setup path, loads indexed path
`[02, character-model-index]`. Extraction preserves all 145 present bank-02
entries and 4,051,200 decoded bytes. Exactly 123 entries round-trip as indexed
tables with an even number of segments, totalling 5,320 segments or 2,660
even/odd pairs. The remaining 22 are preserved as direct companion payloads.
`func_1505E0C4` copies descriptors into zeroed state, `func_1502D824` uses
descriptor byte `5` to select and copy adjacent fixed-stride frames, and
`func_150A8A18` decodes masked joint translations followed by packed root,
rotation, and optional per-axis scale channels. Rotation descriptor bit `0x10`
marks a following scale descriptor and is discarded before the runtime's
five-bit angle lookup. `func_150A81D0` applies each nonzero unsigned scale as
`value / 16384`; zero or an absent channel means unit scale. The glTF exporter
reproduces those scale channels. Descriptor byte `3` supplies duration and
byte `8` plus one supplies stored-keyframe spacing. `func_1503D660` loads the
bank-15 route tables, `func_1503D5F0` selects five shared representative
characters, and `func_1505E650` maps each logical animation ID to an even
bank-02 descriptor segment. The extracted 3,021 route records include Conker
animation ID `0` selecting pair `0025`; 2,982 routes target the 123 indexed
animation entries and 39 accompany the direct payloads. `func_1505E0C4`
leaves a generic `0xFF` duration at `255` ticks and replaces the four character
`0x92` cases from `D_800993F8`. Those exact bounds select 57,732 source frames
across all 2,621 nonempty pair layouts; 39 odd segments are empty. The
compatible glTF export covers all 2,621 nonempty clips and 57,732 source frames.
This excludes 7,177 zero alignment bytes across 1,796 clips that a naive
whole-stride count would misclassify as frames.
Entry `0082` pair `0000` contains 10 duration-selected source frames followed by
1,110 preserved and hashed companion bytes, not another 65 frames. Entry `0124`
pair `0036` retains 590 post-duration bytes, and entry `0146` pair `0021`
retains 145; all three companion tails are hashed rather than decoded as
frames. Every glTF Action records the logical animation IDs that route to its
source pair. `func_1507BDB0` advances the current animation time from the float
delta passed by its callers; the ordinary character path passes `D_800BE9A4`.
A pinned Mupen interpreter trace measured that delta as exactly `1.0`, and the
main scheduler records the normal update after two NTSC video retraces. The
exported descriptor ticks therefore use the runtime's 30 Hz animation clock.
Remaining
character-material sources include packed or mipmapped payloads, dynamic
facial slots, and combiners that depend on primitive/environment colour, so
bank-01 previews retain those material-state runs without guessed diffuse maps.

## Indexed bank-04 model geometry

All 59 decoded entries in indexed bank `04` share a complete outer structural
contract. Their first word is both the first segment offset and the byte size
of a variable descriptor table. Every descriptor contains an aligned offset
and size; the ranges are contiguous, can be zero length, and collectively
consume the decoded entry. Bit 31 is set on the size of the final descriptor
only. Across the US bank this identifies 852 segments without scanning for
byte signatures or inventing boundaries.

`func_150031EC` supplies path `[04, entry]` to `func_1502B6BC`, with the entry
bounded below `0x45`. `func_1502B4A8` scans the returned table to its bit-31
terminator, masks each size with `0x0fffffff`, and rebases nonempty offsets.
That is direct runtime evidence for the outer structure rather than a
file-signature inference.

The same loader rebases model header words at offsets `0x00`, `0x08`, and
`0x10`. It identifies the vertex start as model offset `0x28`, derives the
vertex count from the first rebased pointer with a 16-byte stride, relocates
that primary display list through `func_150049A4`, and passes it to
`func_1510CE60`. `func_1510BF60` independently decodes the 12 five-bit indices
in Conker opcodes `0x10` through `0x1f`, confirming that each packs four
triangles. Standard vertex-load, one-triangle, and two-triangle commands agree
with every cache reference across the family.

`./conker model-assets verify` now parses and rebuilds all 59 decoded bundles
and 852 outer segments byte-identically. The 765 nonempty records contain
209,274 source vertices, 147,723 directly referenced primary-list faces, and
204,493 material-local UV coordinates;
every decoded face index resolves to a loaded vertex. `model-assets extract`
writes the raw segments, OBJ previews, and a provenance manifest under
`build/assets/models/us-bank-04/`.

`model-assets preview` also emits glTF 2.0 files with normalized vertex RGBA,
material-local UVs, decoded CBFD normals where present, and only statically
compatible texture links. The verified
US preview links 1,345 drawable material runs and 36,775 faces to 442 PNGs. It leaves
2,713 mode-one CI8 runs covering 70,348 preview faces unlinked because both the
initial-slot call at `0x150033f4` and the object-model call at `0x150041f0`
pass a null fifth argument to `func_1510CE60`. Those palette pointers remain at
the decoded payload base rather than selecting the trailing palette used by the
reversible CI8 storage previews. This prevents storage-compatible but visually
false materials from being presented as runtime-proven. The same material-proof
boundary now leaves 122 `native-proven` runs covering 2,650 faces unlinked:
their PNGs are reversible pixel-storage views, while their RDP combiner and
primitive/environment color semantics remain unresolved.

The static terrain collision layers are runtime derivatives of these meshes
rather than another hidden geometry bank. `func_15003668` sends bank-04 segment
zero and segment three display lists through
`func_15001460`, which emits one 12-byte triple of relocated vertex pointers per
triangle; `func_15002754` allocates that array together with separate bounds
arrays. `func_150039BC` skips the primary model's eight-byte tertiary header and
exposes one four-byte surface word per triangle. The complete US inventory has
58 primary models and exact one-to-one totals of 97,071 triangles and 97,071
surface words, with 176 distinct values. Segment three supplies another 38
secondary meshes and 1,408 triangles; the runtime does not install a matching
surface table for that layer. `./conker model-assets collision
--force` preserves the surface bytes directly, writes a portable equivalent of
each pointer triple as three big-endian model-relative vertex offsets, and emits
surface-coloured diagnostic glTF files. The glTFs expand coincident source faces
to unique preview vertices so Blender retains every nonzero-area triangle; a
headless Blender 5.2.1 pass imports all 96 files and 98,291 faces. The remaining
188 zero-area source commands stay in the exact record files but are omitted
from the visual mesh. Surface-word physical and audio meanings remain
unresolved. The transformed placement-model collision array built later in
`func_15003668` is now represented as scene glTFs as well. `func_150039E0`
copies placement source byte `0x32` to runtime object byte `0x4F`, and
`func_15003668` excludes exactly `(flags & 0x60) == 0x20`. Of the 1,238 source
records, 1,066 are included and 172 excluded. The 1,055 included records with
available model sources assemble into 98 collision scene files containing
42,901 source faces and 42,885 nonzero-area preview faces. The remaining eleven
included records are precisely scenes 17 and 62, whose bank-04 bundles are
absent. A headless Blender 5.2.1 pass imports all 96 static and 98 placement
files with their exact expected 141,176 visible polygon instances.

The manifest retains all ten header words and reports the remaining limits.
Sixty `DE` commands are now classified as segment-8 `G_DL` references rather
than model-relative pointers. `func_150049A4` reads the opcode with signed
`lb` but compares it with positive `0xDE`, making its apparent `DE` relocation
path unreachable; renderer paths instead emit `DB060020` to select segment 8
at draw time. The four model offsets resolve across eleven contiguous tables
from `0x80082FC0` through `0x80083EC0`. All 264 table entries are fixed
sixteen-byte lists containing one `EF` OtherMode command followed by `DF`
EndDL, so they alter rendering and contribute no hidden vertices or faces. The
graphics-task recorder now discovers nested lists in execution order, retaining
the resolved address for every call after the active `DB0600xx` update. The
supplied OpenEmu task has 36 resolved nested calls and no unresolved target;
its ten segment-8 calls select five exact lists at `0x80083140`, `0x80083180`,
`0x800831B0`, `0x80083240`, and `0x800832C0`. Those counts and addresses are
carried into the ROM-checked runtime-material manifest. Inlining their `EF`
commands corrects 34 of 75 correlated material records and 541 draw
observations: 29 records in bank-01 entries `0001` and `0004`, and five in
bank-04 entries `0045` and `0060`.

The other header pairs now have proven byte boundaries: words `2/3` select 23
secondary regions and words `4/5` select 190 tertiary regions. Extraction
writes both as raw `.bin` files. `func_150031EC` stores the secondary pointers
for the first four slots, but no consumer beyond that loader is currently
identified, so their semantics remain unresolved. For slot zero it passes the
tertiary pointer to `func_150039BC`, which exposes the data after an eight-byte
header. Consumers including `func_150E1D14`, `func_150450CC`, and
`func_15175958` derive an index from a 12-byte collision/surface record and use
it to load a four-byte table value. This proves the first model's 58 present
tertiary tables as surface metadata; the two header words are retained without
assigning unsupported meanings.

Header word `8` is nonzero in five models. `func_15003120` walks a
sentinel-terminated array of twelve-byte records and rebases its first two
pointers. `func_151739B0` proves those fields are an RGB-triplet array and a
`u16` vertex-index array, with the third word as their entry count. Across the
bank this yields 14 vertex-color animation descriptors with 302 validated
vertex references. Header word `9` always has bit 31 set. Its low 31 bits are
zero without a word-`8` table and otherwise equal `(descriptor count + 1) * 12`,
including the sentinel record, across all five models. Words `6/7` are zero in
all 765 models. Model names, semantic material names, transforms, later-slot
tertiary semantics, and the secondary-region format remain unresolved rather
than guessed from appearance.

Primary-list texture references now have a direct runtime contract.
`func_1510CE60` recognizes signed opcode `-3` (`0xFD`), extracts mode bits from
the encoded argument, masks the low 22-bit flat index, calls
`func_1510D0EC`, and overwrites the argument with the loaded address. The model
set contains 8,573 such commands referring to 2,184 unique flat indices:
4,439 use mode zero, 2,341 mode one, and 1,793 mode two. Their image-command
counts are 4,157 `FD100000`, 4,134 `FD500000`, 124 `FD180000`, 95 `FD900000`,
and 63 `FD700000`.

Another 84 `0xFD` commands use the exact addresses `0x01000000` through
`0x0A000000`, all at segment offset zero. They take the parser's non-flat path
and remain runtime segment references. The extractor records both classes per
model, creating a stable model-to-flat-texture binding without claiming a
higher-level material name or forcing dynamic segment sources into static
assets.

Material runs are derived from load state, not merely the nearest preceding
`FD`. An `F3` load binds the pending image as pixel data, an `F0` load binds it
as palette data, `D7` bit 1 controls whether subsequent triangles are textured,
`FC` supplies one of 23 decoded two-cycle combiner formulas, and direct `EF` or
segment-8 state supplies one of 49 direct or 264 table OtherMode pairs. This
distinction prevents a CI palette reference from being mistaken for its pixel
texture. The 147,723 direct primary faces partition exactly into 5,397
contiguous runs: 142,244 flat-textured faces, 1,021 runtime-segment faces,
and 4,458 untextured faces. Extracted OBJs emit these runs as ordered groups and
`usemtl` assignments; companion MTL names preserve the complete proven binding
without claiming semantic material names or paths to unresolved texture files.
The UV exporter applies the display list's `D7` texture scale, `F5` tile shifts,
and `F2` bounds. The 405 textured faces without an `F2` bound all have nonzero
tile masks, which supply their bounded 64x32 coordinate domain.

The separate `model-assets preview` action accepts only the six generated
proven texture-family manifests from the same normalized ROM. It links 1,346
source-compatible material runs and 36,800 source faces to 442 compatible PNGs;
after zero-area filtering, 1,345 drawable runs and 36,775 faces are emitted. It
copies those files into a portable preview directory and verifies every OBJ,
MTL, glTF, PNG hash,
count, and relative texture path. It leaves the incompatible CI8 and unresolved
native-format material families unlinked alongside flat assets without a proven
standalone image and the 63 runtime-segment runs covering 1,021 scene-dependent
faces. This is an explicit evidence boundary rather than a completeness claim
based on visual guessing.

## Direct object-model geometry and placement records

`func_150039E0` loads `[03, object-model-index]` for records whose dispatch word
at `+0x0C` is zero. All 77 nonempty bank-03 entries parse as one direct model
using the same exact 40-byte geometry header as bank-04 segments. They contain
5,062 vertices, 3,894 primary faces, 4,945 material-local UV coordinates, 305
material runs, 518 flat texture references to 198 indices, and 61 segment-8
render-state calls. Extraction and verification preserve all 128,424 decoded
bytes.

Ten bank-03 tertiary regions have a size of exactly `face_count * 4`. Their
values are retained as one structurally proven four-byte record per primary
face, but remain semantically unnamed. Fifteen secondary regions do not yet
have a proven consumer. Most have a size resembling padded vertex-associated
data, but that resemblance is not used as a format claim.

The same function loads `[0B, scene-index]` and divides its decoded size by
`0x44`, then loads child 2 through `[0C, scene-index, 2]` and uses the same
stride. Bank 11 supplies 727 records with dispatch kinds 1 or 2; bank-12 child
2 supplies 511 records whose dispatch word is zero. For those direct-model
records, the word at `+0x10` references 66 existing bank-03 models. The loader
copies position from the signed-short vector at `+0x00`, Euler degrees from the
signed-short vector at `+0x06`, and scale from the three floats at `+0x20`.
`func_1511490C`, `func_151148A8`, and `func_150A8050` prove the YZX rotation
order, degrees-to-radians conversion, and runtime matrix convention. The
extractor preserves all remaining fields and original bytes, and preview
generation assembles all 511 direct records into 48 nonempty bank-12 scene glTF
files. For bank-11 records, `func_150031EC` loads the scene's bank-04 bundle
into `D_800B0E50`; `func_150039E0` indexes that table with the word at `+0x10`
for dispatch kinds 1 and 2. This proves model source
`[04, scene-index, dispatch-index]` and resolves 716 records to 570 bank-04
segments. Preview generation assembles them into 52 additional scene glTFs,
all of which import successfully in Blender 5.2.1 with finite geometry. The
remaining eleven records belong to scenes 17 and 62, whose matching bank-04
entries have zero length. They remain explicit unresolved records rather than
being assigned substitute models.

## Bank-09 direct-model subset

Bank 09 is loaded as a mixed runtime display-list pointer-table family by
`func_1502FE10` and `func_1518C900`. A complete scan nevertheless finds exactly
six entries, 426 through 431, that satisfy the direct model header, vertex,
primary display-list, face-index, and exact payload-boundary invariants without
searching for an interior signature. They add 254 vertices, 256 faces, 254 UVs,
and nine flat-textured material runs. All 7,088 bytes verify byte-identically.
Other bank-09 payloads remain in their broader family rather than being
classified as models.

A complete scan of every indexed bank finds no further payload satisfying the
character-model, direct-model, or segmented-model contracts. Banks 01, 03, 04,
and the proven bank-09 subset contain 1,031 model records (1,029 with faces),
271,002 vertices, and 213,946 primary faces.

Cross-bank validation proves that 380 of those source faces have exactly zero
area: 121 repeat a vertex index, 136 use distinct vertices at duplicate
positions, and 123 are collinear. They occur in explicit standard and packed
triangle commands rather than parser fallback. Preview manifests retain their
source face indices, display-list offsets, and opcodes, while OBJ/glTF output
omits them and contains 213,566 drawable faces.
