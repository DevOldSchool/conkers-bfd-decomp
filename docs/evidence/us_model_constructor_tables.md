# US model constructor tables and material cohorts

The ROM exporter supports constructor descriptor tables, complementary selector
loops and static attachment actions. A separate discovery report groups missing
texture lookups by their remaining decoder or renderer blocker. Discovery does
not authorize an export; the pinned consumer proofs remain the admission gate.
All evidence uses normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. Captures are not extraction inputs.

## Shared intensity decoding

The decoder recognizes the two-cycle I8 formula `TEXEL0 * SHADE` with shade-only
alpha followed by environment alpha. Both opaque and translucent render-table
variants produce the same texture: intensity RGB and image alpha 255. Vertex
and environment alpha belong to the draw state, not the intensity image.

The mip decoder also recognizes a trilinear first cycle followed by shaded
colour and either shade/environment alpha or texture/environment alpha. It
accepts the reviewed native I/IA 16-bit transfer tiles, checks the selected
render tile, and preserves the complete load and mip payload bounds. IA alpha
is retained when the combiner uses it. Partial OtherMode, missing levels and
payload overreads remain unresolved. The exported base image does not reproduce
native filtering, LOD or dynamic lighting.

## Descriptor selection

`15134070` maps actor types through the two ROM jump tables at `800A4350`
(129 words) and `800A4554` (23 words). Literal return destinations select
indices 0–19 or sentinel 99. `15138BC0` rejects the sentinel and passes a valid
index to `15138424`.

That constructor addresses `800A3FD8 + index * 16`, loads the selector halfword
at record `+0xC`, and stores it at `sp+0x11E`: template `sp+0xC8 + 0x56`.
It writes flags `0x39E9` at template `+0x50` and submits through `1513264C`
at `15138728`. Callback flag bit 16 is clear. The ordinary renderer's segment-8
binding therefore survives to the model draw.

| Descriptor indices | Lookup selector | Bank-09 entry |
| --- | ---: | ---: |
| 0, 7, 19 | 58 | 307 |
| 1, 12, 13 | 48 | 226 |
| 2, 15 | 68 | 320 |
| 3 | 75 | 327 |
| 4 | 129 | 377 |
| 5, 6 | 178 | 335 |
| 8 | 187 | 336 |
| 9, 10 | 188 | 337 |
| 11 | 152 | 283 |
| 14 | 218 | 238 |
| 16 | 227 | 248 |
| 17, 18 | 211 | 230 |

The 320-byte descriptor table is pinned to SHA-1
`0e8101c4aae51031a32f923f252098a9eba039c6`. Both jump tables and the complete
selector, wrapper and constructor functions are pinned. All valid indices must
be represented, and selectors resolve through the ROM's 233-word model table.
Already supported models retain their existing sufficient proof.

## Two-entry mask loops

`1513B0F8` uses the same complementary loop protocol as `1513A6E0`, with
indices 0–1 and masks `00 01 02` at `800A4324`, selected by `RNG % 3`.

| Array | Selectors | Entries | Mask | Flags | Submission |
| --- | --- | --- | --- | --- | --- |
| `800A4328` | 227, 229 | 248, 250 | Bit set | `0x101900` | `1513B2C4` |
| `800A4330` | 228, 230 | 249, 251 | Bit clear | `0x1039E9` | `1513B564` |

The shared loop decoder checks the array count and hash, mask table, full
32-bit flags, selector stores, loop bounds and submission instructions. The
complete constructor pin covers intervening control and data flow. Renderer
evidence alone does not repair the incomplete I8 payload on entries 248/249.

## Static attachment actions

The ordinary attachment consumer chain also covers two exact action records:

| Action | Record address | Bytes | Bank-09 entry |
| --- | --- | --- | ---: |
| 48 | `8009D8C0` | `790c0001000000000000000000000000` | 121 |
| 167 | `8009D8F0` | `80020001000000000000000000000000` | 128 |

Both records select kind 1 and updater zero. Their model IDs take the no-op
default in `15031A50`; dispatch slot `800841C0` must be null. `150311C4` binds
segment 8 to `80082FC0` or `80083140`, then binds only segments 1, 3, 6 and 7
before the model draw. No updater or callback can replace that segment-8 table
on this reviewed path. These models use ROM flat textures directly, without a
runtime texture-binding preset. Attachment pose and visibility remain separate.

## Automated diagnosis and remaining cohort

Run the supported interface from the repository root:

```sh
./conker model-assets constructors --bank 09
./conker model-assets constructors --bank 04
```

The report records 112 direct submission/helper calls in the ROM executable,
candidate search boundaries and hashes, reviewed contexts, and per-run material
diagnoses. Candidate boundaries are prologue search hints, not established
function boundaries. No speculative register slice supplies a model identity.
Texture consensus is tried across every verified segment-8 table, independently
of whether renderer evidence exists. This separates successful decoding with
missing renderer proof from actual texture failures.

The resumable form, `./conker model-assets batch --constructors --bank 09`,
stores the result in the shared batch journal. Its bounded initial-ROM argument
pass analyzes 73 candidate regions and leaves 14 incomplete. It recovers model
candidates at 31 submission sites, with no candidate for entries 213 or 407–412.
The report preserves unsupported instructions and indirect-jump barriers for
the next consumer investigation. Constants from table loads are initial data,
not proof that runtime writes leave them unchanged. Joins discard disagreeing
values; calls invalidate volatile registers and stack memory. Missing control
flow or exhausted analysis budgets discard all argument claims for that region.

The targeted 27-record lookup-state cohort has 16 publishable models. Seven
bank-09 models still decode consistently without a reviewed renderer: entry
213 and entries 407–412. Entries 230, 248 and 249 request 368 I8 load bytes from
352-byte payloads; the exporter does not pad or ignore the missing bytes. Entry
203 lacks the combiner/inherited-state evidence needed for diagnosis. These
counts describe this cohort, not the entire material backlog.

## Fragment arrays and the disabled callback sentinel

`15132B80` reads object `+0x79` as a signed byte and compares it with `-1` at
`15132C48`. That sentinel skips the optional callback even when flag bit 16 is
set. Both ordinary opacity-dependent segment-8 bindings survive this path.

`15136C3C` obtains a type index from the already pinned `15134070`, rejects
sentinel 99 and reads a selector-array pointer from `80089A20[index]` and a
count from `800A3F14[index]`. It passes these to `1513A24C`. The full array or
its prefix excluding the final two selectors is eligible, according to the
pinned caller branch. This describes conditional initial draws, not a claimed
simultaneous set of body parts or a reconstructed gameplay event.

`1513A24C` preserves the array pointer/count arguments and forwards them to
`1515080C`. It stores `-1` at caller `sp+0x20`, except when type index is 1:
that branch changes the value to callback index 1 and is excluded by this
callback-disabled resolver. The separate [callback-binding proof](us_object_callback_texture_bindings.md)
follows that type-one payload and admits entries 269/270 with explicit texture
selector alternatives. The helper
allocates a separate used-index bitmap and selects array elements without
replacement. Its word load is stored as the model selector at template `+0x56`.
The callback argument's low byte is loaded at `1515097C` and stored at
`151509C8` to template `+0x69`. `1513264C` copies the template to object `+0x10`,
placing the signed sentinel at object `+0x79`.

The helper's vector outputs end before its flags, model selector and callback
fields. Neither flag branch overwrites the callback byte. The constructor copy
is 0x7C bytes; post-allocation payload copies start at object `+0x170` and cannot
overlap `+0x79`. Complete function pins cover the intervening lifetimes, loop
bounds and submission path. Additional instruction guards check the signed
load, sentinel branch, field copies, selector load and final call.

| ROM data | Extent | SHA-1 |
| --- | --- | --- |
| Array pointers `80089A20` | 20 words | `fc31239198497a530d95521b430bea024ce7a081` |
| Array counts `800A3F14` | 20 words | `03eb3d6d44ad2b1f1075be7cf65ed6e800c878d2` |
| Selector arrays `800A3C6C` | 680 bytes | `e1d0e2b9ac6c6818d798a994f0e8bb32c61de8e2` |
| Separate array `800A18C0` | Three words | `9b86e97e5a7793f59e956182524b84cee02860e3` |

Each admitted array must fit its pinned span, and every selector must fit the
233-word model lookup. The separate caller `150F1D10` supplies selectors
189–191, count 3 and the same callback sentinel directly to `1515080C`.
Whole-function SHA-1 pins are:

- `15136C3C`: 788 bytes, `585f34d7cf570b402f1f7f7bf4d1fa1c7f713846`.
- `1513A24C`: 576 bytes, `1859f5c6b74be313881963173a0c69a803bdaed7`.
- `1515080C`: 1,296 bytes, `8a76782a5c5b96ff73e269d77038908f01dfc5db`.
- `150F1D10`: 992 bytes, `77c321a9f44d4758a8f5b249b431ada52469e419`.

This path supplies the missing renderer proof for entries 232, 246, 254,
273–277, 309 and 312–314. Their 32 recovered material runs cover 315 faces and
12 unique images. All 26,624 pixels pass independent intensity/IA4/CI4 decoding,
including three-bit intensity expansion, row-word swapping, shade-only alpha
and trailing palettes. Sixty-nine ROM mutations and 12 forged glTF renderer
contexts are rejected. The changed constructor suite passes 14 focused tests;
unchanged shared decoder test evidence is reused.

ROM-only exports prohibit capture and other model-output reads. Reviewed
previews, pixel/geometry checks, source reproduction and final GLB checks are in
`build/assets/models/reference/callback-cohort-20260912/`. The array evidence
covers initial ROM contents. Later table mutation, attachment assembly, motion,
lighting, visibility and native appearance remain outside this contract.

## Verification

The 17 selected exports pass independent geometry and material comparison
against the ROM. Forty recovered runs cover 349 faces; 16 unique images contain
30,720 independently decoded pixels. Checks cover three-bit intensity
expansion, intensity and IA alpha, odd-row word swapping, CI4 trailing palettes
and RGBA5551 base images. Sixty-nine consumer/table mutations and 12 exported
renderer-context mutations are rejected.

The changed constructor suite passes 14 tests and the RGBA16 mipmap paths pass
three focused tests. Unchanged decoder test evidence is reused. The full Python
suite was not rerun. Fresh ROM-only exports deny save-state, capture-stream and
other model-output reads. Audit inputs and results are under
`build/assets/models/reference/callback-cohort-20260912/`. The five scene panels
use the [standard shaded RGBA16 mipmap formula](us_direct_rgba16_mipmaps.md),
with all complete-load and mip-level guards retained.

See the [asset roadmap](../asset-roadmap.md) for current gallery and final
validation totals. Import and baseline success do not prove native appearance.
