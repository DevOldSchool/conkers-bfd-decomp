# HUD layout naming evidence

This identifier/comment-only clarification covers `src/game/game_70200.c`.
Original linked symbols, parameter types, field widths, padding, expressions,
statement order and literal values are retained. The eight queue/state helpers
were already registered `matched`; this change earns no new C-match credit.
`func_15043384` remains a disabled `CURRENT (3873)` candidate with its existing
`GLOBAL_ASM` fallback and registered `raw_asm` state.

Evidence comes from the owned normalized US ROM, with no external decompilation
source or inferred scene, character, screen or music identity:

- ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`
- ROM SHA-256: `32e6a8b970ec12ac5f782344945aa0c98a193832eefb687529d03bab6948714b`

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
padding remain unchanged. The separate `Game70200Entry` and every later source
line remain byte-for-byte unchanged despite their overlapping field spellings.

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

## Full registered raw-ROM spans

These SHA-1/SHA-256 values cover each complete registered span decoded directly
from the normalized ROM, including the raw consumers used to justify the fields.
They are semantic provenance, not substitutes for authoritative matching gates.
End addresses are exclusive.

| Function | VRAM span | Bytes / registered state | SHA-1 | SHA-256 |
|---|---|---|---|---|
| `func_15042D78` | `0x15042d78`–`0x15042d94` | 28 / `matched` | `38fc2a649e741f130d03ae9158e9b5e15fb80981` | `f3a875ebe1cbc2d6827ab4c42b5ba2484919664b81f27b82bae5546244ce1570` |
| `func_15042D94` | `0x15042d94`–`0x15042e3c` | 168 / `matched` | `a2b953e07350ede14afc773966ea4f658dec1f91` | `8c5bf4eb9cbb5300bfdd0b3f1a2446145df8e98a1da7bc2ec7c52c7a369b137e` |
| `func_15042E3C` | `0x15042e3c`–`0x15042ecc` | 144 / `matched` | `66a68b65b070ce34fad5125d65ab84433be65a38` | `960b46d7d58ab64501ae1b5c769920c38ce12c5d9833b30f0abfee63db919a0a` |
| `func_15042ECC` | `0x15042ecc`–`0x150432bc` | 1008 / `matched` | `79a05875c18667f06098187ba5cffc5a58463bbc` | `60d41bf0bda9299e4e28568a77b906117b497c17963292ec4031e00c453fc8fa` |
| `func_150432BC` | `0x150432bc`–`0x150432cc` | 16 / `matched` | `2bdb9d828c000138badbbc7a8f8650dc01738ea5` | `c894b1bb6a591c2cb7349f40560e095216675de806ba4dae460c8b892af56dcf` |
| `func_150432CC` | `0x150432cc`–`0x150432fc` | 48 / `matched` | `5f0352a1700b304bb94dedc6f389d046e3800498` | `f39cbb07cc79742fe200fe5b577beaa13539451ebce8863ecdeb16a168667250` |
| `func_150432FC` | `0x150432fc`–`0x1504332c` | 48 / `matched` | `f10d1c316b6cbc684d92a840f3f2cf86d8bfdecb` | `84b4565f67a3af1fd205ea61239b3dab3a2c41f3e401636ec2aaf20a131f4765` |
| `func_1504332C` | `0x1504332c`–`0x15043384` | 88 / `matched` | `1d976bd9d669e23482346fac2b64b57bdc64041f` | `27d8962c610304258752efd393afc1223980202c7b44d5763c56d9660107a69b` |
| `func_15043384` | `0x15043384`–`0x15043a00` | 1660 / `raw_asm` | `7cac7bc6fe71941e6513d45d18caf1b83f99dc02` | `45ce8b202f578a1a75a2d27768dce5cf15d7f6bd033bc9756267d37b48755d43` |
| `func_151ED430` | `0x151ed430`–`0x151ed90c` | 1244 / `raw_asm` | `900522a88e522f04c6834172be22b92ee7cfe7cd` | `788c9e4d96c2e4b017374a813b5e2471992c3db7da411e0ebbe3b04694938747` |
| `func_1510D0EC` | `0x1510d0ec`–`0x1510d374` | 648 / `raw_asm` | `47b67aab9ed8a4eb1706ced5424981ff21373aba` | `4a073d41f9ff67477c0ad6e8dcf73df2b875d7280a472319fbccd8667aff1f4c` |
| `func_1510D374` | `0x1510d374`–`0x1510d404` | 144 / `matched` | `b56e9f67e46ac44069b229680a76dde3e42baba0` | `f7f5772ba3623a9370e5013672480c7011e8285fb53031a1ebaff445b5c2aaac` |

For the existing instruction/table verifier, run `./conker hud-assets survey`.
See [HUD/menu metadata](us_hud_menu_assets.md) for the established extraction
contracts. Accept this source edit only after the eight existing matches pass
`finish`/batch verification and the integration layout, full-ROM, test and
whitespace gates. Renaming fields in a disabled candidate does not change its
status or establish any C match.

## Accepted result

All eight selected functions retain full-span `CURRENT (0)` and reviewed
source-unit layout. The clean batch reaches `BATCH_COMPLETE`, with byte-exact
full ROM, integrated game code and mapped rodata, plus current progress and
clean whitespace. The combined HUD/registry checkpoint passes 1,718 tests on
the host (37 skips) and in the ROM-enabled pinned fixture (one optional skip).
Independent review confirms all twelve raw consumer spans and whole-source
identifier equivalence. This adds eight descriptive roles and eighteen local
field names; it adds no C matches or matched bytes.
