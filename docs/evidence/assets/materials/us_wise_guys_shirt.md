# Wise Guys shirt selection

Bank 01 entry 59 (`0x3B`) contains the Wise Guys mesh. Its shirt was previously
published as coloured noise because the generic bank-11 header initializes
segment 10's descriptor selector to zero. Descriptor zero is a 64-by-32 head
texture, flat 7244. The shirt display lists request a 32-by-32 CI8 image and a
palette at offset `0x400`; these offsets fall inside that head's pixel data.
The resulting bytes are bounded, but are not a valid appearance selection.

## Native selection

The normalized US ROM SHA-1 is `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
The exporter checks these complete instruction spans in the decompressed ROM
code before enabling the instance preset:

| Address | Bytes | SHA-1 | Contract |
| --- | ---: | --- | --- |
| `0x150830A8` | 92 | `6fe91bd3f6baebebc9c39947b34abec05214eaad` | Multiplayer-only initializer calls the team resolver, caps its result at 3, compares model ID with `0x3B`, then stores team index plus one at actor `+0x68`. |
| `0x151E5F64` | 72 | `1b834e4fee9f6356e1a4dd532bd755bfa98ee275` | In multiplayer the team resolver reads the signed team table and replaces negative values with zero. |
| `0x151E8194` | 24 | `fa3015883f323cd01b5214373b18072081e62d9a` | The multiplayer character-switch path repeats the model comparison and index-plus-one selector store. |

The existing verified `func_1502F01C` consumer maps actor `+0x68` to texture
segment 10. The model's six 12-byte descriptors retain their original order:

| Descriptor | Flat asset | Dimensions | Observed texture |
| ---: | ---: | --- | --- |
| 0 | 7244 | 64 x 32 | Head |
| 1 | 7246 | 32 x 32 | Red and white striped shirt |
| 2 | 7230 | 32 x 32 | Blue and white striped shirt |
| 3 | 7231 | 32 x 32 | Green and white striped shirt |
| 4 | 7232 | 32 x 32 | Yellow and white striped shirt |
| 5 | 7245 | 32 x 32 | Fur mip chain |

The preview now deliberately selects the first valid multiplayer variant,
team index zero / descriptor one. This is a representative appearance policy,
not a claim that every Wise Guy instance is red. The manifest preserves the
unmodified bank-11 header selectors, the four proven choices, the chosen
variant, the actor field and the consumer hashes separately. Materials retain
the override evidence alongside the original header hash. A changed consumer
fails closed; no texture is chosen from similarity or a screenshot.

## Result and scope

Material runs 3, 6 and 8 cover the shirt's 44 faces. They now decode flat 7246,
using the recorded LoadBlock/TLUT offsets and odd-row word swap. The resulting
PNG SHA-1 is `6b767a90c7b3962d7a3686ecab801d3ad9a23958`. Geometry, rig,
UV coordinates and the remaining materials are retained.

The [Wise Guys reference](https://conker.fandom.com/wiki/Wise_Guys) identifies
the red character as Paulie, blue as Frankie, green as Chicho and yellow as Ali.
Those names and the visual comparison are semantic evidence only. The exported
shirt pixels, palette and selector rule come exclusively from the ROM.
Lighting, animation selection and exact native raster appearance remain
outside this correction. The other three shirt images are decoded as local
comparison evidence, not separately published models.

Regenerate and validate using:

```sh
./conker model-assets preview --bank 01 --rom-defaults \
  --output build/assets/models/rom-only/us-bank-01-preview --force
./conker model-assets validate
./conker model-assets inspect
```

Before/after hashes, four decoded shirts and validation results are kept under
the ignored `build/assets/models/reference/wise-guys-shirt/` directory.

The regenerated corpus passes all 4,002 glTF/Blender file checks; banks 01, 03,
04 and 09 rebuild byte-identically. The corrected preview shows the red and
white stripes. Its regression comparison remains `changed-image-needs-review`
against the old shirt image; the baseline was not silently replaced. The full
test run has 730 passes and one unrelated documentation failure because the
separately edited `AGENTS.md` omits the automation command expected by
`test_unified_automation_uses_public_authoritative_gates`.

The published GLB independently imports into Blender with all 152 triangles
and its three embedded images intact, and passes Khronos validation with no
errors or warnings. Only this model's GLB and PNG changed among the 616
published asset files. Gallery preview and GLB links include their content
hashes to prevent a browser from continuing to show an earlier export after
regeneration; the seven inspection tests pass after that gallery-only change.
