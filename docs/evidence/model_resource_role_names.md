# Model resource and bounded attachment roles

These are descriptive names inferred from the reviewed US ROM, not recovered
original source names. Seven existing matched C functions gain role comments
and supported parameter/local names. Linked symbols, types, existing declarations,
numeric values, operation order and layouts remain unchanged. The later bounded
enum trial below additionally replaces the spelling of two reviewed action
operands with named constants. No new C match or runtime-activation claim follows.

## Shared resource helpers

| Symbol | Descriptive role | Evidence boundary |
| --- | --- | --- |
| `func_1500390C` | `flat_asset_find_cached_index` | Returns the first equal cached address, or -1; duplicate pointers/sentinels prevent a unique inverse |
| `func_1510D374` | `flat_asset_rom_address` | Sums preceding compressed sizes onto ROM base `0x1A37E0`; no helper-local index validation is claimed |
| `func_1510D608` | `flat_asset_update_nonzero_state` | Nonzero state becomes `(previousState & 0x40) | stateBits`; bit `0x40` retains no invented meaning |
| `func_151EDB58` | `ui_release_model_resources` | Releases the resource at owner `+0x24`, then tags owner and copied display-list allocations with value four |

Runtime flat IDs span `0..7761`, through 7,762 unsigned-halfword sizes at
`D_80091D20`. Empty slots 1767/1768 remain part of that identity domain; physical
stream ordinal is different. `func_1510D0EC` calls the ROM-address helper at
`0x1510D1D8`; HUD's descriptor renderer reaches that shared loader at
`0x151ED5E0`. `func_15040CC8` calls the reverse cache search at `0x15040D40`.
State-helper calls at `0x1510D708` and `0x1510D794` establish shared resource use,
not a HUD-exclusive lifecycle. See [HUD/menu evidence](us_hud_menu_assets.md).

The UI owner `func_151EB06C` constructs bank-09 models 164/162 with animation
selectors 23/8 and stores the results in `D_80090058`/`D_8009005C`. It draws those
same pointers and later passes them to `func_151EDB58`. The constructor stores
its display-list count at `+0x14` and list pointers from `+0x04` at four-byte
strides. This supports `uiModel`, `displayListIndex` and `displayListCursor`.
Allocation tagging is not described as immediate deallocation: the helper
continues reading the owner after tagging it. No named character or world
placement is inferred from this UI path.

## Attachment action 35 and 68 requests

`func_1514DCAC` has the bounded role
`actor_request_attachment_actions_35_and_68`; its pointer parameter is `parentActor`.
It first stores numeric `0x6000` at parent `+0x9C`, whose meaning is left unnamed,
then unconditionally requests action 35 followed by action 68 on the same
saved pointer. Its existing raw `s32` argument words, including `0x3F800000`,
are retained without changing the call ABI.

Action 35 has one kind-two record: model byte 133, animation selector two.
The descriptor selector at `+0x17` therefore takes the animated loader path
through `func_1503F62C` and `func_1502FE10`. Action 68 has one kind-one record:
model byte 29 and selector -1, taking `func_1502FE10` directly. Both loaders
resolve bank 09. Numeric-ROM/preview joins identify the exact source records. Prior visual
inspection supports only helmet-like and cigar-like appearance descriptions for
models 133 and 29 respectively. Their item identities, military role and
gameplay use are not confirmed by those images or earlier gallery labels.

Action selectors 35/68 are not model IDs 133/29. Parent `+0x3B` equal to zero,
duplicate suppression, allocation failure or model-load failure can prevent
creation. The caller ignores the returns, so the role describes requests,
not guaranteed attachments or exclusive character ownership.

## Digital timer

| Symbol | Descriptive role | Boundary |
| --- | --- | --- |
| `func_15093818` | `timer_display_set_enabled` | Nonzero request initializes only on a disabled-to-enabled transition; zero clears the enable byte |
| `func_15093878` | `timer_display_init` | Loads bank-09 model 186 and allocates `0x80` bytes for matrix storage |

The direct model loader `func_1518C900` supplies the timer display-list address to
`D_800D2448`; the allocation goes to `D_800D244C`. The raw renderer
`func_150938BC` selects digit textures, installs four segment pointers, chooses
matrix storage and submits that display list. The two globals retain their
linked names and types. Clearing the enable byte is not called deallocation.
The inspected `00:00` texture selection is an explicit preview preset, not an
initial or observed runtime timer reading. Timer units and the existing
excluded renderer candidate remain unchanged.

## Exact model source identities and full spans

All evidence uses normalized US ROM SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`. The three source-bound model records are
bank09, segment zero; IDs are decimal:

| Entry | Source bytes | SHA-1 | SHA-256 |
| --- | ---: | --- | --- |
| 29 | 552 | `48ddf0a838a1d41c2bf79ae90b00f02e512bc684` | `a080b44823b83bae5639e1d89b1b8da26ccc535a835394f430562ae56c040efc` |
| 133 | 2072 | `06e1fe5e7dbfad273d74fb96fd936e01db76681f` | `6e9e414e702b8cc63ceb100e06ed76c051c812cc27b6d6c222e39e5567c2ea5b` |
| 186 | 1928 | `80f62bb6324297fde4ab3ad5f05cb0efe89641ea` | `efd0fb9de977d69539b88b9539c0d642642a378aa372527d19e5d108207bfbd2` |

The following hashes cover current registered full function spans, independently
decoded from that ROM:

| Symbol | Bytes | SHA-1 |
| --- | ---: | --- |
| `func_1500390C` | 164 | `db44c54f402b6ef45a864efe5de985d4751f69c2` |
| `func_1510D374` | 144 | `b56e9f67e46ac44069b229680a76dde3e42baba0` |
| `func_1510D608` | 40 | `c8d0d9a81517e56fbe70ad2b5c00e8faa8e19a83` |
| `func_151EDB58` | 132 | `b4ca5861b440d0051774f539120029dfae355c43` |
| `func_1514DCAC` | 72 | `39365f94e0a7a6b0bfa482f77edee0c0c042b57b` |
| `func_15093818` | 96 | `1142c92237dec6384ab2461097c44dc21bba37e5` |
| `func_15093878` | 68 | `c56384d3d2abd16a21d08fd633b729741368243f` |

Acceptance requires full-span focused zeros, unchanged source-unit layout, a
clean batch, byte-exact ROM/game and mapped data/rodata, full tests, progress
and whitespace. None of the existing raw or deferred consumers is promoted.

## Accepted resource-role slice

This acceptance describes the original seven-role slice, before the separate
enum trial below.

All seven functions retain full-span `CURRENT (0)` and reviewed source-unit
layout. Clean batch verification reaches `BATCH_COMPLETE`; full ROM, integrated
game code, mapped rodata, progress and whitespace gates pass. Both complete
1,718-test suites pass: 37 host skips and one optional skip in the ROM-enabled
pinned fixture. Independent review authenticates the selected raw spans,
source-wide identifier equivalence, model pins and caller/constructor chains.
This adds seven descriptive function roles and no C matches or matched bytes.

## Bounded source-local action constants

The two calls in `func_1514DCAC` now spell their reviewed selectors as
`ACTION_SELECTOR_35 = 35` and `ACTION_SELECTOR_68 = 68`. These anonymous enum
constants are declared after the reviewed source-unit comment and before use.
They describe action-table selectors, not model IDs or guaranteed creation.
Only the two unsuffixed integer call operands change spelling. Signatures,
parameter types, numeric function definitions, other literals and linked symbols
remain intact; no shared header or enum-typed ABI is introduced.

Whole-source m2c context remains available and all recovered signatures are
unchanged. Running the pinned m2c parser on the same raw function with the full
pre/post contexts succeeds in both cases and produces identical output. That
output retains numeric literals, so regeneration does not automatically preserve
the semantic spelling. The enum declarations must remain before their uses.
This result does not authorize enum replacements for unsigned literals, masks,
address offsets, pointer arithmetic, signatures or automatic declaration repair.

The bounded enum trial retains full-span `CURRENT (0)` and the source-unit
layout for `func_1514DCAC`. Its combined nine-function batch reaches
`BATCH_COMPLETE`, with byte-exact ROM/game and mapped rodata, clean progress
and whitespace, and both full 1,721-test suites passing (37 host skips; one
optional ROM-enabled pinned skip). Independent review confirms the exact
source inverse, constructor distinction, and retained source-context/discovery
behavior. This accepts two source-local action-selector constants and no new
C match or linked name.

## Confidence correction before publication

The two source-local constants and the request-role comment use neutral action
selector numbers. Earlier helmet/cigar wording was an appearance-based inference,
not a confirmed item identity. The proved selector-to-model routing and
conditional request behavior remain unchanged. See the
[confidence review](model_name_confidence_review.md) for the current distinction
between character-label provenance, appearance descriptions and semantic identity.
