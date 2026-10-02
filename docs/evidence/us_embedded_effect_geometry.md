# US embedded effect geometry

The checksum-validated US game data contains a four-vertex, three-triangle
primitive at `0x8008D538`. It is submitted by the type-6 effect renderer
`func_15187A98`, outside the four indexed model banks. Its game identity is
unresolved; the export uses its source address and object type as identifiers.
It does not add a character, prop, scene or twelve-instance gameplay assembly
to the existing gallery or model count.

## Source and consumer proof

The exporter pins these complete US functions, including delay slots and
padding. Independent raw-ASM reconstruction matches the decoded ROM bytes.

| Function | Bytes | SHA-1 |
| --- | ---: | --- |
| `151674F8` dispatcher | 1,392 | `1a4cc2434666765a39feb16096d26a83d4b8fcc3` |
| `151875E0` constructor | 920 | `4a3d8d5343c1a47014ffc4c7551897e3eeb5c6c3` |
| `15187978` update | 288 | `8cc428786a1ddea876f0cd501c799dc24f977f6f` |
| `15187A98` draw | 724 | `57240400027c3c203cd122ec5387ae58336fed56` |
| `15187D6C` matrix helper | 340 | `da3f2f65e100988423a3e91aae0221d175d5274d` |

The 52-byte type descriptor at `0x8008B5E0` selects update `15187978`, draw
`15187A98`, setup list `8008D4F0` and teardown list `8008D520`. Its SHA-1 is
`ca02188ff3d12958c8e29136b2455302f43cdb51`.

Instructions `15187B18/15187B28` construct the vertex address.
`15187CC8..15187CD4` emits vertex command `01004008` with that address:
four vertices, cache slots 0–3. The following commands are `05000204`,
`05000206`, and `05000406`, each with a zero second word. They select ordered
triangles `(0,1,2)`, `(0,1,3)`, `(0,2,3)`. No closing base face is supplied.

The exact 64 source bytes have SHA-1
`290aab191fa562144dec98402a04c45dbe7ced77`:

| Index | Native XYZ | Stored RGBA |
| --- | --- | --- |
| 0 | `(-625, 0, 0)` | `(255,255,255,16)` |
| 1 | `(625, 31, 0)` | `(255,255,255,255)` |
| 2 | `(625, -31, 31)` | `(255,255,255,255)` |
| 3 | `(625, -31, -31)` | `(255,255,255,255)` |

Flags and signed texture coordinates are all zero and remain in the raw source
and manifest. Original positions, index order and vertex bytes are preserved.
When the dispatcher accepts the object and its signed `object+0xA8` counter
is nonnegative, the draw loops exactly twelve times over `0xA0`-byte effect
records. This is a conditional code path, not twelve observed instances.
Constructor randomness, per-instance matrices and activation state are runtime
data. This exporter stores the primitive once without synthesizing those states.

## Known render setup and diagnostic boundary

The dispatcher emits descriptor `+0x10` before the draw at
`1516774C..1516776C`. The 48-byte setup list at `8008D4F0`, SHA-1
`da9454df2434e87c06c268496589724ac78aa40d`, contains:

- `D7000000 00000000`: texture disabled.
- `E7000000 00000000`: pipe synchronization.
- `FC323864 FF73FFFF`: both combiner cycles select primitive multiplied by
  shade for RGB and alpha.
- `D9FDF9FF 00000000`: clear lighting and both culling bits (`0x020600`).
- `EF082CAF 00504A50`: one-cycle translucent state with forced blending.
- `DF000000 00000000`: end.

The renderer emits `FA000100` with white primitive RGB and runtime alpha from
its record counters at `15187C20..15187C88`: signed halfwords at record
`+0x96` and `+0x94` supply `(lifetime - elapsed) * 255 / lifetime`, with signed
integer truncation followed by `& 255`. The counter domain and activation are
not synthesized. Therefore stored vertex alpha is not the final native opacity. Other geometry-mode flags may remain inherited.
The 24-byte teardown at `8008D520`, SHA-1
`ed4f53bb562de37ca2dd4b4d54496adb7b951274`, restores a matrix and synchronizes
the pipe; it does not establish a new complete material.

The diagnostic glTF has **no assigned material**. Its `COLOR_0` accessor uses
normalized unsigned bytes, preserving all original RGBA values, but a viewer's
default opaque material and backface culling differ from the known native
setup. Explicit extras retain that limitation and the native command state.
No texture, normal, opacity override, instance matrix, skin or animation is
invented. The source-space geometry is useful for inspection, not as a claim
of the effect's in-game appearance.

## Extraction and verification

```sh
./conker model-assets embedded-geometry
./conker model-assets embedded-geometry --verify
```

The default output is `build/assets/models/embedded-geometry/`. It contains
`manifest.json`, `source/vertices-8008d538.bin`,
`geometry/embedded-type06-8008d538.gltf`, its `.bin`, and
`embedded-type06-8008d538.glb`. `--rom` and `--output` are supported. Extraction
refuses an existing output directory. Verification rederives the source and
compares every expected output byte without rewriting the destination.

The packed GLB uses the existing byte-preserving inspection packer. Focused
ROM-free tests cover whole-span and every-byte data mutation rejection,
boundaries, independent F3DEX2 decoding through the existing geometry parser,
exact glTF positions/RGBA/index bytes, packed preservation, overwrite refusal
and tamper detection. Live US derivation separately checks the original ROM.

The separate [selected elapsed-zero material inspection](us_embedded_type06_material_inspection.md)
now supplies a translucent unlit GLB and one parts/effects gallery card. It
preserves the original four vertices, three faces and vertex alpha, selecting
constructor elapsed zero with source-proven positive lifetimes. The raw
diagnostic export above remains byte-identical and is retained as source
evidence; only the selected material GLB is the visible download. Native
instance transforms, effect activation and raster parity remain unresolved.

This is a demonstrated gap in the prior indexed-bank-only geometry inventory,
not evidence of an unbounded supply of unextracted model containers. The
bounded discovery audit under
`build/assets/models/reference/extraction-coverage-20261001/discovery-audit/`
records remaining format limits separately.

## Second primitive: shared type-8 family

A bounded check of neighbouring effect dispatch entries found a second stored
mesh at `0x8008CD90`: six vertices and four triangles. Type 7 has no draw
callback. Type 5 uses the generic sprite rendering path; this pass did not
identify a second static vertex set there. Type 8 explicitly submits the
stored display list at `0x8008CDF0`, so its identification does not depend on
searching for plausible triangle bytes.

The shared family was previously documented as a source boundary in
[US quad rendering and actor-state effects](game_raw_quad_actor_effect_groups.md).
The new extraction connects that renderer to its actual stored vertex data.
Types 8, 9, 12 and 89 use the same geometry, exported once. No new gallery card
or indexed-bank model count is implied.

The source guard covers dispatcher `151674F8` and the complete 3,024-byte
family `15179FE0..1517ABB0`, SHA-1
`695b7d3f515a5c4ee888aba10551844fcc18f751`. It includes both constructors,
updates, the draw routine, texture-selector helper, setup and adapters.
The bounded audit independently reconstructed 1,405 raw ASM instructions
across the dispatcher, neighbouring type-5 renderer and available raw family
members. The three already matched family helpers remain covered by the
complete ROM span; generated assembly was not substituted as their proof.

The four 52-byte dispatch rows at `8008B648`, `8008B67C`, `8008B718` and
`8008C6BC` bind renderer `1517A3A0` and setup callback `1517A958`. The
dispatcher submits each row's setup list at `1516774C..1516776C` and invokes
its draw callback. Instructions `1517A618/1517A61C` form `8008CDF0`, and
`1517A620..1517A628` emit `DE000000 8008CDF0`. That list contains:

| Command | Source effect |
| --- | --- |
| `0100600C 8008CD90` | Load six vertices into slots 0–5 |
| `05000204 00000000` | Triangle `(0,1,2)` |
| `05000602 00000000` | Triangle `(0,3,1)` |
| `05080206 00000000` | Triangle `(4,1,3)` |
| `050A0806 00000000` | Triangle `(5,4,3)` |
| `DF000000 00000000` | End |

The 96 vertex bytes have SHA-1
`93628695ad949451da5fa2199e8e60578149a9b6`; the 48 list bytes have SHA-1
`7fdfb9b9c212494ce10c5b808762eed458f13815`. Every stored vertex has flag zero
and RGBA `(254,254,254,255)`.

| Index | Native XYZ | Signed ST |
| --- | --- | --- |
| 0 | `(7,4,0)` | `(9234,8351)` |
| 1 | `(-7,4,0)` | `(8200,8334)` |
| 2 | `(0,1,3)` | `(8720,8107)` |
| 3 | `(7,14,0)` | `(9202,9040)` |
| 4 | `(-7,14,0)` | `(8213,9024)` |
| 5 | `(0,21,4)` | `(8698,9694)` |

Types 8/9 use setup list `8008CE20`; types 12/89 use `8008CE40`. Both call
the shared list at `8008CE60`. Its combiner `FC121624 FF2FFFFF` multiplies
texture and shade for RGB, and texture alpha and primitive alpha for opacity.
The draw routine passes object byte `+0x9F` to `1517A9A8`, which passes the
selector shifted by eight to `15094F70` with descriptor `80090614`. Its
table at `8009060C` contains flat indices 2990 and 2988. These links are
recorded as evidence; the complete texture-loader, tile and normalized-UV
contract is not reconstructed by this export.

Primitive alpha comes from object byte `+0xB3`, cached at `800DD450`.
Signed position/angle halfwords at `+0x90..+0x9A`, float scale at `+0xA8`,
and per-buffer matrices determine runtime placement. Constructors and updates
also use runtime randomness, timers and visibility conditions. None is
invented in the diagnostic artifact. The glTF retains local positions and
byte RGBA, has no assigned material, texture, normalized UVs, animation or
instance transform, and records signed ST in extras and its manifest.

```sh
./conker model-assets embedded-geometry --primitive type08
./conker model-assets embedded-geometry --primitive type08 --verify
```

The separate default output is `build/assets/models/embedded-geometry-type08/`.
It contains the manifest, raw vertex and display-list bytes, a glTF and binary,
and `embedded-type08-8008cd90.glb`. Omitting `--primitive`, or selecting
`type06`, retains the original type-6 default directory and byte-identical
output. Both variants refuse overwrite and verify without rewriting files.

The 13 focused tests pass. They cover complete consumer-span mutations,
every source-data byte, list submission and bounds, independent F3DEX2
decoding, exact geometry and RGBA, packed preservation, CLI selection,
overwrite and tamper rejection. Both actual-ROM exports pass verification.
Khronos `2.0.0-dev.3.10` reports zero errors, warnings, infos or hints for the
new glTF and GLB. Blender `5.2.1 LTS` imports each as one mesh with six vertices,
four polygons and no actions, with identical imported positions. A rendered
geometry diagnostic was inspected; it does not establish native appearance.

Reproducible source proof, the initial draft and structural/render reports are
under `build/assets/models/reference/resolution-goal-20261002/embedded-neighbours/`.
The separate type-6 verification still compares every original file byte
successfully after this addition.

### Type-8 material follow-up

A further source audit verifies 3,209 independent raw instructions. The shared
texture descriptor at `80090614` specifies two 32×44 CI8 images. Each decoded
payload contains 1,408 index bytes followed by a complete 512-byte RGBA16
palette. Independent pixel expansion agrees for all 1,408 pixels in each image.
The images visually depict green and brown leaves; this is a descriptive visual
identification, not a recovered effect name.

| Selector | Runtime flat index | Compressed ROM start | Decoded SHA-1 |
| --- | ---: | --- | --- |
| 0 | 2990 | `0x5D8C19` | `06e22d77c9f055a98d5182c18aafa0a214d22561` |
| 1 | 2988 | `0x5D7D70` | `016d0a3c402e80f05a015cb41b7467b99da10aed` |

The loader establishes tile 0, its line stride, clamp flags and bounds
`(256,256)..(287,299)`. That origin explains the large stored ST values.
The selector comes from caller state; one wrapper chooses it randomly.
Constructor alpha 255 is proven initialization, not a first-frame observation.
Neither texture is a universal default.

The remaining material gate is specific: the 256-entry palette loads through
**inherited tile 6**, and the reviewed dispatcher, local setup and loader do not
define that tile's TMEM address. The source call chain includes intervening
scene lists and earlier effect callbacks. A dominating initializer and absence
of intervening writes have not been proved. Capture the last tile-6 `F5` command
at `DE000000 8008CDF0`, including its TMEM address, selected payloads, primitive
alpha and final draw state, before attaching a native material to the GLB.
The diagnostic geometry stays unchanged.

The old generic texture catalog's item named 2990 is a different CI4 asset at
ROM `0x5D98A8`; its number is not an interchangeable source identity. The new
raw PNGs, full hashes, command reconstruction and bounded caller audit are in
`embedded-neighbours/material-followup/` under the goal reference directory.
Adjacent type 10 reuses indexed bank-09 models; type 11 generates a camera-facing
quad dynamically. Neither establishes another stored embedded primitive.

## Third primitive: type 13

A bounded follow-up from the effect dispatch table identifies six stored vertices
at `0x8008B3E0`, used by type-13 draw callback `15166D68`. This is a separate
four-triangle primitive outside the indexed banks. The type descriptor at
`8008B74C` selects this callback, update `15166B50`, setup list `8008B440`,
setup callback `15166F6C` and teardown callback `15166FD8`.

The guard covers the complete 1,648-byte family `151669A0..15167010`, SHA-1
`3f95afd4d65830cd0c4b2e1903e8307746524610`, plus the already pinned dispatcher.
All 760 raw ASM instructions across those spans independently match the decoded
US ROM. The 96 vertex bytes have SHA-1
`dc13f954ac0a0693b224e05c9742597282cf1c6c`.

| Vertex | Local XYZ |
| --- | --- |
| 0 | `(-400,-34,-40)` |
| 1 | `(-400,-34,40)` |
| 2 | `(-400,34,0)` |
| 3 | `(0,-34,-40)` |
| 4 | `(0,-34,40)` |
| 5 | `(0,34,0)` |

Instructions `15166D9C/DD0` construct that address; `15166DB0/DBC` construct
`0100600C`. Stores at `15166DFC/E00` submit the six-vertex load. The four
triangle commands emitted at `15166ECC..15166F20` preserve ordered faces
`(5,3,0)`, `(2,5,0)`, `(1,4,5)` and `(1,5,2)`. No closing faces are added.
The native loop uses three matrices at object offsets `+10`, `+50` and `+90`;
the extraction stores the primitive once, without constructing random rotations
or caller-dependent placement and scale.

All stored flag, ST and RGBA values are zero. Before drawing, `G_MODIFYVTX`
commands replace every cached ST pair using unsigned object byte `+D0`:

- `s0 = 0x2800 - trunc((object_D0 << 12) / 10)`; `s1 = s0 + 0x800`.
- Vertices 0/1 receive `(s0,0x2000)`, vertex 2 receives `(s0,0x2400)`.
- Vertices 3/4 receive `(s1,0x2000)`, vertex 5 receives `(s1,0x2400)`.

The setup enables texture and uses `FCFFFFFF FFFCF279`, selecting TEXEL0 for
both RGB and alpha in both cycles. Thus the stored zero colors are not the
native texture-only appearance. The setup callback invokes `15094F70` using
descriptor `8009054C` and its flat texture index 4275. A later
[selected counter-5 material inspection](us_embedded_type13_material_inspection.md)
proves the complete I8 loader, tile and combiner contract. The diagnostic glTF preserves
raw positions and zero RGBA, but has no assigned material, normalized UVs,
texture, animation or instance transforms. Its viewer appearance is diagnostic.

```sh
./conker model-assets embedded-geometry --primitive type13
./conker model-assets embedded-geometry --primitive type13 --verify
```

The separate output `build/assets/models/embedded-geometry-type13/` contains
raw vertex bytes, a manifest, glTF/binary and
`embedded-type13-8008b3e0.glb`. Creation refuses overwrite; verification compares
every file against fresh ROM derivation without rewriting it. All original
type-6 and type-8 output files remain byte-identical.

All 19 embedded-geometry tests pass, covering source corruption, load/triangle
contracts, independent decoder agreement, packed preservation and output guards.
The pinned Khronos validator reports zero issues for both formats. Blender
5.2.1 imports both as one mesh with six vertices, four faces and no Actions;
the imported glTF/GLB positions agree exactly. The diagnostic render was
visually inspected. Source proof and validation artifacts remain under ignored
`build/assets/models/reference/resolution-goal-20261002/embedded-type13/`.
The geometry-only command adds no indexed-bank model count. The separate
material inspection is eligible for one parts/effects gallery card, with
original raw GLB evidence retained and only the selected-state Blend linked.
Its publisher independently reruns the pinned Khronos validator and fresh
Blender verification; original source, manifest, tool and artifact bytes are
rechecked before any publication write. It is never assigned a synthetic bank ID.
