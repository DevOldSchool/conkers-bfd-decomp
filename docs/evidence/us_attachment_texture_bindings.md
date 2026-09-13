# US attachment texture selectors

The ROM-only exporter resolves three bank-09 attachment material bindings from
reviewed action records. All three have complete stored-geometry texture coverage. Entry 19 also has
a shade-only surface whose dynamic colours remain unverified.

## Consumer chain

`15083568` selects an eight-byte header at `80086CC4 + (action - 1) * 8`,
then traverses its sixteen-byte records. Record byte 3 equal to 1 selects the
attachment constructor `15030AF4` with descriptor byte `+0x17 = -1`. Record
byte 0 becomes model ID `+1`; byte 2 becomes updater index `+7`. Kind 2 uses a
different loader. Its separately proved entries 153, 141 and 147 are documented in
[direct pixel-segment bindings](us_direct_segment_texture_bindings.md). The three
CI material-binding records below and the two static actions
documented in [constructor-table evidence](us_model_constructor_tables.md)
are admitted; no total action-table extent is inferred.

`15030AF4` initializes texture IDs `+0x18/+0x1A` and counter `+0x38` to zero.
`1502FFD8` routes the `-1` selector through `1502FE10`, loading the model from
bank 09 and relocating its list pointers. The subsequent initializer
`15031A50` is a no-op for model IDs 19, 25 and 49.

`15030468` calls the function at `800841C0[descriptor[7]]`. The remainder of
this path updates transforms, visibility and lifetime, without assigning the
texture fields. `15030E08` submits through `150311C4` with fifth argument zero.
The latter binds the nonzero `+0x18/+0x1A` flat assets, loaded by `1510D0EC`, to
segments 6/7 immediately before its ordinary list submission. Alternate-list
submission, later actor scripts and native appearance are outside this proof.
The complete reviewed functions, dispatch words, headers, records and selected
flat-table spans are checked against the validated US ROM.

## Inspection presets

| Model | Action and record address | Updater | Selected texture |
| --- | --- | --- | --- |
| `09:0019:00` | 9, `8009CE90` | `150D82BC` (index 1) | Flat 1352 from `800902B0`; CI8 64×32, palette at segment 6 + 2048 |
| `09:0025:00` | 21, `8009CF30` | `15031E2C` (index 2) | First frame 2644; CI4 32×32, palette at segment 6 + 512 |
| `09:0049:00` | 76, `8009D120` | `150F56B0` (index 4) | Flat 3256 from `8009028C`; CI4 32×32, palette at segment 6 + 512 |

Entry 25's updater indexes the three words at `800902BC` using `counter` below
3 and `5-counter` otherwise, then increments modulo 6. The resulting frame
indices are `0,1,2,2,1,0`. All three flat assets (2644–2646) must decode with the
same layout; the gallery displays frame zero. Playback phase is not inferred.

Entries 19 and 49 use explicit inspection state: non-null actor animation
pointer `+0x2D0` and actor state `+0x84 = 0`. Entry 19 thereby excludes state
13's alternate texture and UV-scroll branch. Entry 49 excludes state 174's
animation-phase selector and selects table index 6. This establishes an updater
preset, not a current or reachable gameplay state. Geometry and UVs remain the
stored ROM values. Entry 19 resolves 42 textured faces. Its other 16 faces use combiner
`FCFFFE8F F517F8FF`, with SHADE, ENVIRONMENT, PRIMITIVE and K5 inputs but no
TEXEL input. The parser's `external-runtime-texture` placeholder does not imply
a missing image on this run. The lit cigarette is suitable for standalone
inspection, while its dynamic shade/colour state remains unverified.

## Static direct-texture attachments

Actions 48 and 167 select entries 121 and 128 with updater zero and a no-op
initializer. Their renderer preserves its segment-8 binding through submission,
allowing consensus decoding of ROM flat textures. These paths require no
runtime texture-selector preset. Their evidence, pixel checks and remaining
pose/visibility limits are recorded in the
[constructor-table evidence](us_model_constructor_tables.md).

## Validation and remaining work

The resolver requires a segment-6 pixel base and same-segment palette offset
matching the exact 32- or 512-byte payload tail. The display list must establish
CI format, TLUT load size, image dimensions and valid TMEM/payload spans. It does
not inherit a guessed segment-8 state. Every retained frame must decode before
any binding is accepted. Manifest `rom_object_texture_binding` and glTF
`romObjectTextureBinding` preserve action/dispatch/table evidence and explicit
selector state. Validation reloads the ROM to check those records and pixels,
and rejects replacement of captured materials.

Local audit artifacts are in
`build/assets/models/reference/attachment-bindings-20260912/`: isolated export
with capture reads prohibited, numeric geometry checks, five independently
pixel-decoded CI images (6,144 pixels), 34 rejected consumer/data mutations and
three rejected glTF-provenance mutations, plus Blender previews and publication
checks. Captures are comparison evidence only.

Entry 80's paired texture and tile-origin update is now proved in
[attachment texture and UV updates](us_attachment_uv_updates.md). Its initial
preset preserves the full RGBA32 image and shifts only the first material's
UVs; a texture-only binding is not used.
