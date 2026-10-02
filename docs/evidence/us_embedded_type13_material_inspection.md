# US embedded type13: selected counter 5 material inspection

The supported inspection contains one original six-vertex, four-triangle mesh
with its source-proven I8 texture and explicitly selected counter value **5**.
It is a self-contained Blender file. This is a useful stored-state inspection,
not a native first-draw, runtime placement, effect-identity or raster-parity claim.
Constructor counter 10 and all three runtime matrix instances are not selected.
The original geometry-only type06, type08 and type13 exports remain unchanged.

## Reproduce

From the repository root, after the ordinary type13 geometry export exists:

```sh
./conker model-assets embedded-geometry --primitive type13 --material-inspection counter5
./conker model-assets embedded-geometry --primitive type13 --material-inspection counter5 --verify
```

The default destination is `build/assets/models/embedded-type13-material-inspection`.
Creation refuses an existing destination. `--verify` reconstructs source from
the US ROM, then reconstructs expected Blender data before opening the saved
file with scripts disabled. Both commands accept `--rom`, `--output` and
`--blender`; verification does not write the artifact or its source files.
No pinned configuration or shared texture-decoder change is required.

## Source and material contract

US ROM SHA1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
The existing embedded exporter proves vertices at `8008B3E0`, their complete
96-byte span and ordered triangles `(5,3,0)`, `(2,5,0)`, `(1,4,5)`, `(1,5,2)`.
All stored flags, ST and RGBA bytes are zero. Its complete dispatcher and
`151669A0..15167010` consumer-family guards are reused, rather than substituting
a triangle-signature search. The family SHA1 is
`3f95afd4d65830cd0c4b2e1903e8307746524610`.

The dispatcher sets `800DD220=0` and `800DD224=2` at `15167648/15167654`
inside each type iteration before setup. Type13 setup `15166F6C` passes texture
descriptor `8009054C`, selector 0, zero offsets, mode 2 and cache lifetime 3
through `15094F70`/`15095060` to `150950D4`. Descriptor/data bytes at `80090548`
are `000010b3800905480100004000200401`: flat 4275, one frame, 64×32, format 4,
size 1 (I8). Loader table bytes at `8009DEB0` are
`03010000020100000101020202020203`. The exporter pins these complete additional
consumer spans, their raw SHA256 values, the descriptor and table:

| Entry | Bytes | SHA256 |
| --- | ---: | --- |
| `150950D4` | 1384 | `aeb811e28bae3309dbdafe4d58660070783dacc04cc93b78ac04e166ff8fa367` |
| `1510D0EC` | 648 | `4a073d41f9ff67477c0ad6e8dcf73df2b875d7280a472319fbccd8667aff1f4c` |
| `15094F70` | 120 | `8d9ae7535f57bf56b9ce25835cb5dc2d6cf8b9fd835967b89a85a095ac263f64` |
| `15095060` | 116 | `7e3c0b9009d0e83b9a405b6373de2aacc7545df9c12723db4fc78095317b0b55` |

The exact reconstructed commands are:

```text
E7000000 00000000
FD900000 flat4275-data
F5900000 07000000
F3000000 073FF000
F5881000 00094260
F2400400 004FC47C
```

They load 2048 bytes as 1024 16-bit texels, then sample I8 from TMEM 0 with
64-byte rows, clamp S/T, masks 6/5, zero shifts and tile origin (256,256).
No inherited TLUT or palette is needed. The flat loader's final argument 3 is
cache lifetime; `1510D0EC` uses the standard decompressor, without conversion
or padding. Compressed ROM span `0x7938A2..0x793D76` has SHA256
`0aa54ddb1831ce231ef70e814d5831b963547db097540d184578013606e26266`.
Its decoded 2048 bytes have SHA256
`bb14d7224693e5aa0312bc85e0a86115894c3cf70d76d03f87c3a85a52237f22`.
The odd-row-swapped PNG SHA256 is
`7306b180bfcce6b0c7190a676db71c1e57cb76c60cfdaa7984306356da3c138a`.

Setup list `8008B440` supplies `FCFFFFFF FFFCF279`: RGB and alpha are both
TEXEL0, with no SHADE input. `EF082CAF 00504B50` selects one cycle, bilinear
filtering, no TLUT or alpha test, and translucent blending. The Blender image
is Non-Color with straight alpha: every I8 byte divided by 255 supplies all
four channels. Emission and a transparent mix preserve those RGB/alpha inputs;
the original zero vertex color attribute is retained and does not modulate
the shader. The original imported diagnostic material is also preserved.
This avoids incorrectly interpreting intensity bytes through an sRGB transfer.

## Counter and cached ST

Constructor `151669A0` stores counter 10 at object `+D0` (`15166A08/15166A0C`).
Update `15166B50` decrements it. Renderer `15166D68` overwrites ST for all six
already loaded vertex-cache entries at `15166E08..15166EC0`:

```text
s0 = 0x2800 - trunc((unsigned_counter << 12) / 10)
s1 = s0 + 0x800
t0 = 0x2000; t1 = 0x2400
counter 5: (8192,8192), (8192,8192), (8192,9216),
           (10240,8192), (10240,8192), (10240,9216)
```

The selected cached ST spans the complete texture. It is interpreted as signed
10.5 after vertex-load texture scaling; applying ordinary G_TEXTURE scale again
would be a second scaling operation. The glTF V convention is flipped when
creating Blender UVs. Constructor counter 10 instead clamps to the transparent
left edge for this texture; that is not evidence of the game's actual first
draw or update ordering.

The repository's G_MODIFYVTX definition and the primary emulator implementation
provide the interpretation cross-check: Conker's
[F3DEX2CBFD dispatch](https://raw.githubusercontent.com/gonetz/GLideN64/master/src/uCodes/F3DEX2CBFD.cpp)
maps MODIFYVTX to the standard handler, and
[gSPModifyVertexST](https://raw.githubusercontent.com/gonetz/GLideN64/master/src/gSP.cpp)
cancels the texture scale when accepting signed cached ST. This is emulator
source evidence, not a measured native RSP or fixed-point raster comparison.

## Verification and limits

The worker independently compares all 2048 decoded pixels against raw payload
bytes, every ordered face corner against the ROM positions, all original RGBA
values and all 96 source bytes. It freshly derives the UVs, shader, original
material, packed image, camera and scene before opening an existing Blend.
No embedded text, Actions, drivers, modifiers, constraints, external libraries,
node groups, compositor or non-factory handlers are accepted.

Twenty-four CPU/GPU swatches check raw RGB and alpha separately at fractional
bilinear coordinates, texture edges and coordinates beyond both S edges. The
supported candidate's maximum error was `0.0019286130757419362`, below `2/255`.
This checks the stated Blender sampling contract; it does not equate Blender
filtering, transparency/coverage or RSP interpolation with native output.

Eleven focused tests and all 33 embedded export/routing/inspection tests pass.
Fresh artifact admission and final current checks leave all 12 candidate files
unchanged. Five real Blend mutations (shader strength, UV, original color,
image color space and camera shift), each with coherently changed saved metadata and Blend hash,
are rejected without writes. All five type06, six type08 and five type13 source
files still equal fresh ROM reconstruction. The saved ORTHO framing signature
includes camera shifts, sensor fit, clip planes, disabled depth of field, render
resolution/aspect and crop bounds. An independent review reproduced the omitted
camera-shift guard in the earlier candidate; the corrected candidate rejects it.

Fresh creation, reopen and verification passed in Blender 5.2.1 LTS. Both
768-pixel views show a coherent bright streak; this descriptive appearance
does not identify its game effect. The source preserves one mesh and four
faces, not three invented runtime instances. Native visibility, placement,
frame counter, occlusion and draw ordering remain runtime dependent.

The host's `inspection_artifact` performs fresh ROM/source reconstruction and
fresh Blender verification. `inspection_artifact_current` rechecks all source,
artifact and tool bytes at publication preflight. Proof kind is
`embedded-type13-counter5`; it retains the original glTF fingerprint and raw
GLB hash separately from the Blend and preview hashes. Coherent changes to
saved metadata cannot replace the independently reconstructed source contract.

Ignored, reproducible evidence is retained under
`build/assets/models/reference/resolution-goal-20261002/embedded-type13/material-followup/`:
`audit.py`/`audit.json` cover raw instructions and loader evidence;
`supported-03/` holds the corrected supported candidate; `validate_supported.py`,
`tamper_worker.py` and `supported-validation.json` cover artifact admission,
before/after bytes and coherent tamper rejection. Earlier prototype artifacts
remain separately labelled and are not canonical publication inputs.
