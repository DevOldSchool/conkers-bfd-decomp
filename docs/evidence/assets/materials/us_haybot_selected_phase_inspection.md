# Haybot selected texture phase inspection

`./conker model-assets haybot-inspection` creates a separate, self-contained
Blender inspection of the existing bank-01 entry 75 export. It supplies the
previously unresolved image on material run 16, affecting 24 faces. It preserves
the original 1,225 exported faces, UVs, vertex RGBA, 45-joint rig, 15 Actions,
18 original images and all original materials. The replaced untextured material
is retained as a Blender datablock. The original glTF, binary, raw GLB and gallery
source inventory remain unchanged.

The selected state is **post-update phase 0**, selecting descriptor 15 for
segment 10 while segment 11 remains descriptor 0. This is a source-supported
inspection choice, not a recovered universal default or an observed first draw.
The shader also explicitly selects source-initial full opacity, zero primitive
and environment RGB, and the stored vertex RGBA. These values are individually
proved by source; their concurrent appearance in a native submitted draw has
not been captured. The saved rig pose is neutral and its original Actions remain
available. This does not supply a native material-animation timeline, reproduce
other texture scrolling, or establish native lighting, visibility, intermediate
animation interpolation or raster parity.

## Source and selected state

The US normalized ROM SHA-1 is
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Model 75's decompressed bank-01
payload SHA-256 is
`09f6c4551ca0d12b46109a45f01703fb21ba7f10d15764aa807a4c9701936e81`.
The existing source is
`build/assets/models/rom-only/us-bank-01-preview/geometry/0075-00.gltf`:

| Resource | SHA-256 |
| --- | --- |
| Original glTF | `a02f92412a139bc528d6fc51d0d17f2153312edcbb2a9e573e35aa5d93ed9ce4` |
| Original binary | `bd9fefc58b3bab6e74158cafbe8b8e39bb9a6cc7d62fd8deb6c20862b181a417` |
| Packed original GLB | `8b129aacfe3128cd50407ba2909cdb030f0445ecf4d3a88304389737ddb946bd` |

The exporter freshly reconstructs the original glTF and binary from the ROM,
including the existing primary draw selection, the one existing zero-area face
omission, and all animation clips. It also freshly decodes every original image
and requires byte equality with the current source files. It adds no geometry
omissions or material changes to that source.

`func_15061B4C` iterates 25 actor controls. The model-75 branch requires a live
control word and nonzero actor byte `+0x2FA`. When shared timer byte `800CC2A7`
is at least four, it resets the timer and advances actor `+0x69`. Previous phase
5 wraps to 0; other valid phases increment. Updated phases 0–5 select descriptors
15, 16, 17, 17, 16, 15 at actor `+0x68`. The timer is shared and checked per
qualifying control, not once per frame. Below the threshold the branch increments
the timer and leaves the selectors alone.

The bank-11 initializer selects 0 for both `+0x68` and `+0x69`; its first eligible
advance would select descriptor 16. Thus the selected phase 0 is specifically the
wrap result, not an initializer claim. `func_1502F01C` reads these two bytes to
bind segments 10 and 11 respectively. Phase 0 preserves segment 11's original
zero selector, and the current Haybot display lists do not sample segment 11.
The alternative images below are source evidence only; they are not three
independent full-model appearances.

The model-specific branch also invokes `func_15062D10` on native command indices
`0x173`, `0x175`, `0x177`, once per updater invocation. They alter tile origins at
payload `0x7598`, `0x75A8`, `0x75B8` in an earlier run. Target run 16 independently
sets its tile at `0x7630`, so its stored UVs can be preserved. The inspection does
not animate the other three origins.

The ordinary frame path can update through `15019130 -> 15018DFC -> 1502378C`
or `1504A730`, both reaching `15061B4C`, before later rendering. Updates can be
skipped and further callees run before drawing; this is conditional call-order
evidence, not proof that no later caller changes a selector.

## Exact image and combiner contract

The target starts at raw source face 368, exported face 367, and contains 24 faces
with stored vertex RGBA `(255,255,255,255)` at all 72 corners. It loads 2,048 CI4
index bytes from segment 10 offset 0 and 16 RGBA16 palette entries from offset
`0x800`. The target commands include:

```text
75D8 FCFF9880 F514FEFF   two-cycle combiner
75E8 FD100000 0A000000   selected pixel source
75F8 F3000000 073FF000   2048-byte pixel transfer
7610 FD100000 0A000800   selected palette source
7618 F0000000 0603C000   16-entry TLUT
7628 F5000800 00098260   32-byte row stride, clamp S/T
7630 F2002002 000FE0FE   independent 64x64 tile bounds
7638 DE000000 08000040   selected renderer state
```

All eleven ROM segment-8 tables agree on RGBA16 lookup at offset `0x40`.
The existing strict decoder accepts complete 2,080-byte payloads for these
three source descriptors:

| Descriptor | Flat asset | PNG SHA-256 |
| --- | --- | --- |
| 15, selected | 3823 | `0c984d18d271a89a163e648c9b7801bd6ad8b7984df56f419390ee087c31f78d` |
| 16, evidence | 3822 | `1290ef17797b01c2c9d01272c1ab0842f1f02d3092ef53263d8d9ab23e291999` |
| 17, evidence | 3824 | `c09a6887c481458b29463c423aad762d1b383e413f9412945e9cf72ac38d1479` |

An independent nibble/TLUT oracle checks all 4,096 pixels per image, including
the odd-row four-byte swap and vertical conversion. Although the palettes have
unused transparent entries, **every used pixel in all three images is alpha
255**. All original palette bytes remain in the source evidence.

The exact combiner is:

```text
cycle 0: RGB = TEXEL0; alpha = TEXEL0.a * SHADE.a
cycle 1: RGB = (SHADE.rgb - ENV.rgb) * COMBINED.rgb + PRIM.rgb
         alpha = COMBINED.a * ENV.a
```

`func_150006E0` explicitly initializes the two RGB arrays at `800D9B68` and
`800D9B78` to zero. The matched `func_1502CC34` reads them; later native updates
can change them. The inspection selects their initialized values rather than
claiming an actual scene draw still has those values.

For opacity, `1505F188 -> 150615DC` initializes actor `+7` and `+B..E` to 255.
The two stored model-75 bank-0E spawn rows (scene 16 record 0, scene 24 record 1)
both have flags `0x0020`, so the constructor's `flags & 6` mode-4 fade override
does not apply. Both rows are script gated; their later VM/handler behavior is
not asserted absent. The ordinary `1502C974 -> 1506196C` wrapper returns exactly
255 for initialized `255 * 255`, rather than truncating that product to 254.
The inspection selects this initialized full-opacity condition and ordinary
draw modes 0–2, excluding the separate mode-4 multiplier.

`1502CCFC` receives that opacity, writes it to environment alpha, and selects
segment-8 table `80083140` for opacity 255. At offset `0x40` that table contains
`EF18AC3F 04D12078`: two-cycle, bilinear, RGBA16 lookup, opaque, without alpha
comparison or forced blending. The worker retains the full RGB and alpha node
formula. Because all used texel and stored vertex alpha values and selected
environment alpha are one, the result is opaque. It uses raw-byte `Non-Color`
image values and an unlit shader for the selected stored-SHADE calculation;
it does not reinterpret raw bytes as sRGB or invent runtime lighting.

The separate `15035FE8` queue path is **not** an opacity-255 proof. Its literal
255 belongs to a different blend-color vector; environment alpha comes from
dynamic queue byte `+4`. The queue producer and geometric/fade calculations are
recorded in the ignored independent audit, and excluded from this contract.

## Creation and verification

```sh
./conker model-assets haybot-inspection
./conker model-assets haybot-inspection --verify
```

The default output is `build/assets/models/haybot-phase0-inspection`. Creation
refuses any existing destination. Verification checks the fresh ROM/source
contract, reconstructs the expected imported mesh, shader, packed images, rig,
Actions, neutral pose, NLA state and camera before opening the saved Blend with
execution disabled. It compares the reopened state to those independent
expectations, not to a user-editable saved audit alone. Text blocks, drivers,
external libraries, non-factory handlers and extra modifiers are rejected.
It performs no writes to an existing artifact.

Publication admission returns one Blend, one preview and a proof bound to the
current source fingerprint, original raw GLB, all prepared/artifact bytes and
the relevant tool files. The final publication preflight freshly rederives the
source and rejects any changed proof. Gallery routing is owned by the publisher;
this exporter does not create a second Haybot card or change the extraction
status of the original source.

Research and real-ROM validation are saved under
`build/assets/models/reference/resolution-goal-20261002/haybot-followup/`:
`audit.json`, `caller-spans.json`, `pixel-oracle.json`,
`independent-review/source-review.json`, `independent-review/alpha-review.json`
and `supported-validation.json`. Candidate `supported-02` passed actual-ROM
creation, fresh CLI verification and real publication admission/preflight, with
all 34 files unchanged during verification. Its Blend SHA-256 is
`c3bbcc058384963c20dd710b7ade24fa577613c51f4d5984b12d4489eba1a3b3`.
Five copied Blends, each with only its saved Blend hash updated, were rejected
without writes after mutations to camera shift, combiner alpha, an original
Action key, an original UV and the selected image color space.
The supported candidate retains every original
source byte and has 19 packed images, 15 original Actions and a neutral saved
pose. Both front and rear views show coherent geometry, including the selected
button texture on the back. Eleven focused host tests cover selected phase,
material/source bounds, exact spawn conditions, opacity scope and admission /
no-overwrite behavior; real coherent-tamper checks additionally exercise the
saved Blender scene against fresh reconstruction.
