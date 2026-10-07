# Attachment 80 texture and UV controller

The ROM-only controller export extends the existing
[initial attachment preset](us_attachment_uv_updates.md). It recovers both
8 x 64 RGBA32 texture alternatives, the conditional state transitions and 101
exact tile-origin samples. It does not replace the initial model preview or add
gallery cards. No geometry, alpha or native command is rewritten in the source.

The authorized US ROM SHA-1 is
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The complete 440-byte updater
`150D83D8` has SHA-1 `73966a1646839351ecf831823d1709127b61db0b`.
Existing action-102, constructor, loader and renderer guards remain required.
Recovery branch `4f80ae55eeb322a170837319257ed0ab9da58c97` does not change this
controller or its initial preset.

## Texture selection

The two words at `80090304..8009030C` are `00001C23 00000CB1`:

| Flat | Selection | Bytes | Payload SHA-1 |
| ---: | --- | ---: | --- |
| 7203 | Phase-zero reset | 2,048 | `42f06a65a9452441a32ed8062f9ab4abe148e59b` |
| 3249 | Phase-zero parent threshold succeeds | 2,048 | `8121e5736d5ad8a71860409e5c1446c6d8e62cfb` |

The second flat is 3249, not the consecutive archive entry after 7203.
The existing renderer binds descriptor halfword `+0x18` to segment 6. The
model's own commands prove the format, complete LoadBlock, masks and disabled
TLUT. Both textures pass that same material decoder without inherited-state
substitution. An independent byte-index calculation checks all 1,024 decoded
RGBA pixels, including odd-row eight-byte swaps and PNG vertical orientation.

## One update at a time

Descriptor `+0x38` is the phase word; `+0x3C` is the signed accumulator;
`+0x18` is the texture halfword. Delta comes from `800BE9E4`. Parent action
is unsigned halfword `+0x84`, and the conditional float input is loaded from
`*(parent+0x2D0)+0x08`. Its semantic role beyond these comparisons remains
unproven; the API calls it `parent_frame` without asserting a playback clock.

| Incoming phase | Native action | Transition |
| ---: | --- | --- |
| 0 | Reset accumulator to 50 and texture to 7203 | Parent action 397 and float input >= 46 select texture 3249 and phase 1 |
| 1 | Add delta to accumulator | Signed result >= 100 clamps to 100 and enters phase 2 |
| 2 | Preserve accumulator and texture | Parent action 398 and float input >= 34 enter phase 3 |
| 3 | Subtract four times delta | Signed result <= 0 clamps to zero and enters phase 4 |
| Other values, including 4 | Preserve accumulator and texture | No phase assignment |

Only one arm runs per invocation. A 0-to-1 transition still uses accumulator
50, and a 2-to-3 transition does not decrement until the next invocation.
Only phase zero assigns a texture. Entering another phase with an arbitrary
texture value does not prove that 3249 was selected previously. Ordered native
float comparisons do not accept NaN; a parent float is only dereferenced in
the applicable action/phase branch.

Native integer operations wrap at 32 bits before signed comparisons. The
reusable `step` helper deliberately accepts accumulator and delta in 0..100,
where those operations cannot overflow; it rejects other values. These are
inspection bounds, not proven runtime limits. Phase and selector widths retain
their native unsigned ranges. No frame rate or sequence of parent inputs is
invented.

## Exact UV values

Every arm then replaces the first F2 word at model offset `0x340`. The model
payload is pinned to SHA-1 `d9667ef7783f87f1dbfd616d278539a7f7664fcb`, and the
existing preset validates the command location and affected material span.
The second word `0001E0FE` stays unchanged. Only the first 16 faces receive
this origin; the next F2 restores the remaining 44 faces' stored coordinates.

The origin is computed with float32 rounding after conversion and each
operation: accumulator times scale (`3C23D70A`), times 120, plus 2, then
truncation toward zero. The low twelve bits are combined with `F2002000`.
For example, accumulators 5/10/50/80/100 produce origins 7/13/62/97/122 in
quarter-texel units. Replacing that calculation with host-double
`accumulator * 1.2 + 2` gives incorrect results. The export preserves every
integer-accumulator result from 0 through 100 and its normalized V shift from
the stored origin, `(origin - 2) / 256`.

These are a state lookup table, not a sampled animation timeline. Parent
identity, reachable gameplay state, update timing, visibility and native
raster appearance remain separate evidence requirements.

## Reproduce and verify

```sh
./conker model-assets attachment-controller \
  --output build/assets/models/attachment80-controller
./conker model-assets attachment-controller \
  --output build/assets/models/attachment80-controller --verify
python3 -m unittest discover -s tests -p 'test_model_attachment_controller.py'
```

Generation requires a new output directory and writes `manifest.json` plus
two PNGs. Verification rederives the metadata and PNG bytes from the ROM and
compares every output without writing. The normal gallery model remains the
existing initial preset; the controller export is available as extraction
data. Tests cover transition delay, texture persistence, float32 thresholds,
rounding, unsupported arithmetic inputs and changed consumer/data guards.
