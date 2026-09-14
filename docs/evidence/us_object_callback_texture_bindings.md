# US object callback texture bindings

Four bank-09 models have complete texture links through two reviewed object
callbacks: entries 269, 270, 304 and 305. Six previously unresolved material runs
cover 57 faces. The gallery uses explicit ROM selector presets and preserves
the correlated alternatives in the material evidence.

The input is normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Save states, capture streams and
other exported models are not extraction inputs.

## Shared callback consumer

`scripts/model_callback_texture_bindings.py` pins 23 complete function spans,
ten ROM data spans and 24 constructor instructions. Changed evidence fails
closed. The ordinary callback-disabled extractor retains its existing limits;
this separate proof admits only four model identities.

`1513264C` copies the constructor template to object `+0x10`, placing callback
byte template `+0x69` at object `+0x79`. Renderer `15132B80` installs its ordinary
segment-8 table, invokes the selected callback, then submits the object's
primary model display list. Dispatch entries at `800899A8` select callback 1
(`15133EB8`) and callback 2 (`15133FD8`).

Callback 1 reads one binding from object `+0x174`; callback 2 reads a count at
`+0x170` and iterates eight-byte binding records starting at `+0x174`. Both call
`15133EEC`. Each record supplies a texture descriptor selector, destination
segment and loader/cache argument. The reviewed payloads target segments 4
and/or 6, so the ordinary segment-8 binding survives to submission.

The helper addresses twelve-byte descriptors at `80090B60 + selector * 12`.
The first word points to a ROM flat-asset index. The reviewed descriptors have
one image, CI8 format, width 32 and height 32 or 64. The helper loads that flat
asset through `1510D0EC`, binds its pixel base to the requested segment, and
binds the trailing 512-byte palette to the next segment. Descriptor and flat
word pointers must stay inside their independently pinned spans.

The existing CI8 decoder checks the display-list load, tile, palette and payload
bounds. The ordinary segment-8 consensus establishes texture interpretation,
not native lighting or blending. No new bank-wide default is introduced.

## Type-one fragment bindings

`15136C3C` obtains the actor type through `15134070`. For type 1, pointer
`80089A24` and count `800A3F18` select eight words at `800A3C94`:
`2, 3, 48, 146, 146, 145, 49, 49`. The reviewed caller permits either all eight
words or the prefix of six. Model lookup selectors 145 and 146 resolve to
bank-09 entries 269 and 270. Other identities retain their existing proofs.

`1513A24C` selects callback 1 for this type and builds a twelve-byte payload.
Its texture selector is at payload `+4`, target segment 6 at `+6`, and loader
argument 3 at `+8`. `1515080C` copies the payload to object `+0x170` after
allocation. The constructor and copy instructions are checked together with
their full function spans.

The texture selector comes from four ROM halfwords at `800A4258`. Parent byte
`+0x128`, clamped to 3, selects one of these alternatives:

| Parent selector | Descriptor selector | ROM flat asset | Image |
| ---: | ---: | ---: | --- |
| 0 | 131 | 7241 | 32 x 32 CI8 |
| 1 | 129 | 7239 | 32 x 32 CI8 |
| 2 | 130 | 7240 | 32 x 32 CI8 |
| 3 | 132 | 7242 | 32 x 32 CI8 |

The inspection preset uses selector 0. The two meshes are labelled descriptively
as red-and-white clothing fragments; this does not establish their character
identity, motion or assembled effect.

## Paired effect-surface bindings

The second and third submissions in `151C9198` select model lookup indices
55 and 56, resolving to entries 304 and 305. The shared template at `sp+0x58`
has callback byte 2. A twenty-byte payload at `sp+0x40` contains count 2 and
two eight-byte records. Each constructed object receives its own payload copy.

| Model | Caller argument low byte | Segment 4 descriptor / flat | Segment 6 descriptor / flat |
| ---: | --- | --- | --- |
| 304 | Nonzero | 135 / 2968 | 136 / 2969 |
| 304 | Zero | 139 / 2977 | 140 / 2978 |
| 305 | Nonzero | 137 / 2970 | 138 / 2971 |
| 305 | Zero | 141 / 2979 | 142 / 2980 |

All eight images are 32 x 64 CI8 with trailing 512-byte palettes. The argument
is the low byte of the word at entry `sp+0x14`. The inspection preset selects
the nonzero branch; alternatives remain paired by branch rather than allowing
arbitrary combinations. The two models have identical stored geometry but
different texture bindings and remain separate ROM identities.

Intervening `15133760` / `15142838` matrix work writes bounded 64-byte outputs
at object `+0x90` and `+0xD0`, outside the callback byte and payload. These helper
spans and their output functions are pinned as part of the consumer proof.
The descriptive blue effect-surface labels do not claim a native effect name.

## Verification and remaining work

Six focused tests cover exact contexts, correlated alternatives, changed ROM
spans, instruction and dispatch guards, descriptor bounds and missing inputs.
An independent ROM-only export verifies all four geometry exports and manually
decodes all twelve distinct images: 20,480 pixels, including odd-row word
swapping and RGBA5551 palette expansion. Mutations in all 33 pinned function
and data spans are rejected, as are four forged exported callback bindings.

Local audit scripts and reports are under
`build/assets/models/reference/runtime-bindings-20260912/`. The audit includes
source snapshots, ROM-only file access, pixel and geometry checks, reviewed
previews, production reproduction and final packed-file checks. See the
[asset roadmap](../asset-roadmap.md) for current publication and validation totals.

The [direct pixel-segment proof](us_direct_segment_texture_bindings.md) resolves
timer 186 and attachments 153, 141 and 147. The
[attachment UV update proof](us_attachment_uv_updates.md) resolves attachment 80.
Four runtime-segment cases remain. These are
investigation leads, not export eligibility:

- Bank 04 entry 59, segment 23 has a direct scene-59 placement with updater
  zero; the source of its inherited segment-4/5 texture binding remains unknown.
- Bank 09 attachment 47 has a static action with initial texture selectors
  zero. The renderer preserves inherited segment-6/7 state on that path.
- Attachments 165 and 185 still lack a reviewed action/consumer path.


These exports preserve stored geometry and UVs. Later selector updates,
visibility, assembly, colours, lighting and native appearance remain separate.
