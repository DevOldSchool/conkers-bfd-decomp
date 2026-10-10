# HUD layout naming evidence

The eight matched helpers below use descriptive C names through source-local
aliases, preserving types, widths, padding, expressions and linked symbols.
The two existing multiline macros are joined onto single physical lines with
identical replacement tokens so alias-aware tooling can parse the source.
No new C match follows. [Confidence/provenance](model_name_confidence_review.md)
separates source descriptors, conditional behavior and runtime appearance.

## Queue and state roles

| Linked symbol | Descriptive role | Renamed parameters/locals |
|---|---|---|
| `func_15042D78` | `hud_set_layout_flags` | `arg0` → `flagsRaw` |
| `func_15042D94` | `hud_queue_layout_at` | `arg0/arg1/arg2/arg3` → `x/y/flagsRaw/format`; `storage/i` → `argumentWords/argumentIndex` |
| `func_15042E3C` | `hud_queue_layout_at_current_position` | `arg0` → `format`; `storage/i` → `argumentWords/argumentIndex` |
| `func_15042ECC` | `hud_parse_and_queue_layout` | `arg_data/arg_index/format_index` → `argumentWords/argumentIndex/conversionIndex` |
| `func_150432BC` | `hud_set_layout_scale` | `arg0` → `scale` |
| `func_150432CC` | `hud_attach_layout_to_object` | `arg0/arg1` → `attachedObject/verticalOffset` |
| `func_150432FC` | `hud_set_layout_position` | `arg0/arg1` → `x/y` |
| `func_1504332C` | `hud_set_primary_rgba` | `arg0/arg1/arg2/arg3` → `red/green/blue/alpha` |

Both wrappers copy sixteen argument words and call the parser at `0x15042E24`
and `0x15042EB4`. Their `format` parameters remain `s32`, and the attachment
parameter remains `s32`: naming does not change these ABI declarations.
The parser allocates `0x5C` bytes at `0x15042F30`, links nodes through
`D_800CBD64`/`D_800CBD68`, initializes kind to zero at `0x15042F74`, takes an
inline control argument at `0x15043108`, and advances Y by 11 for text.

## Existing source-local fields

| Structure | Offset(s) | Existing field → supported name |
|---|---|---|
| `Game70200TextNode` | `+0x00` | `field_0` → `attachedObject` |
| | `+0x04` | `field_4` → `scale` |
| | `+0x08` | `field_8` → `x` |
| | `+0x0A` | `field_A` → `yOrVerticalOffset` |
| | `+0x0C` | `field_C` → `flagsRaw` |
| | `+0x0D` | `field_D` → `kindSelector` |
| | `+0x0E/+0x0F/+0x10/+0x11` | `field_E/field_F/field_10/field_11` → `primaryRed/primaryGreen/primaryBlue/primaryAlpha` |
| `Game70200Effect` | `+0/+1/+2/+3/+4` | `width/height/scale/flags/data` → `tileColumns/tileRows/scaleByte/flagsRaw/flatAssetIndex` |
| `Game70200TextureInfo` | `+0/+6/+8` | `field_0/field_6/field_8` → `flatAssetIndex/tileWidth/tileHeight` |

The node's `+0x0A` is screen Y without attachment; with attachment it is an
offset added to object world Y before projection (`0x150434F8`–`0x1504352C`),
then reused for projected Y. Node `+0x0E..+0x11` feed glyph color arguments at
`0x15043658`–`0x150436AC` and the sprite environment-color command.
`field_12..field_15` remain unresolved; the `+0x15` text-measurement test alone
does not establish a secondary alpha or shadow role. `next`, `text`, and all
padding remain unchanged. The separate `Game70200Entry` fields remain unchanged despite their overlapping
spellings; its function aliases have separate [ring evidence](../../matching/naming/record_ring_helper_semantics.md).

The raw renderer reads metadata `+2` and multiplies it by `1/128`
(`0x150436D4`–`0x15043710`); `+3` is tested as raw bits at `0x15043720`–`0x15043730`.
Metadata `+0/+1` supply tile counts, while `+4` is copied to descriptor `+0`
(`0x15043788`–`0x150437B4`, `0x15043858`–`0x150438B8`).
`func_151ED430` reads descriptor `+6/+8` as tile dimensions at `0x151ED4B0`
and `0x151ED4EC`, and passes descriptor `+0` through the nested tile loop to
`func_1510D0EC` at `0x151ED5E0`. This proves a flat-resource index.
`Game70200TextureInfo` remains a partial declaration; its `field_4` is unresolved
and no extra fields are introduced. These metadata renames affect only the
preserved deferred C candidate, not a newly matched renderer body.

## Exact numeric domains

- Node kind 0 selects ordinary text. Kinds 1..92 are one-based HUD sprite
  metadata selectors; the raw renderer subtracts one at `0x15043444` and uses
  an eight-byte stride at `0x150436CC`. This describes the table's supported
  domain, not a bounds check added to the parser or renderer
- The table is `[0x800859E0, 0x80085CC0)`: 736 bytes, 92 records, 86 distinct
  base runtime flat indices, reaching 159 runtime flat resources with tile and
  animation expansion. The separately addressed parser format begins at its end
- Selector 26 uses runtime flat indices 2023..2028; selectors 59/60 use
  2224/2225 with 16×16 tile dimensions. Selector 69 uses 2099..2101. These are
  HUD selector/resource associations and establish no scene or model identities
- Runtime flat IDs are 0..7761, indexing 7,762 `u16` compressed sizes at
  `D_80091D20`; slots 1767 and 1768 are empty. `func_1510D374` sums preceding
  sizes onto ROM base `0x1A37E0`. Physical stream ordinal is not runtime ID
- Glyph mapping is separate: `D_80085930` contains 95 bytes; space uses sentinel
  `0x60`. These node/metadata names do not promote raw font consumers to C

Table SHA-1: `90d9e1abd749d082969413520cdb4d63bf91a7a6`
Table SHA-256: `399170eaeb28e9c23fab2a4fbfc999d07c44b6ea103c8979cefeb679a468b62f`
Flat size-table SHA-256: `51b40c4080feea4e04b7e4921bce202c67a5d1c27f04ee92086255b6b38d6454`

Use `./conker hud-assets survey` for the instruction/table verifier;
[HUD/menu metadata](../interface/us_hud_menu_assets.md) owns the extraction contracts.
`func_15043384` remains raw with its disabled `CURRENT (3873)` candidate.
