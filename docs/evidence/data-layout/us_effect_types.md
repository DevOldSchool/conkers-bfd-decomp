# US effect-type records

`D_8008B4A8` contains 104 records of 52 bytes, covering exactly
`8008B4A8..8008C9C8` (5,408 bytes). The new data-only owner is
`src/game/data/effect_types.c`. This does not establish an original C-object
boundary, complete a function, or replace the runtime GAME data archive.

## Native extent and layout

The initialization loop at `15167010` advances by `0x34` to an endpoint at
`base + 0x1484`, visiting records 0 through 100. It does not establish the
whole table's extent. Separately, `15169040` supplies the interval `[0,104)`;
`15169070` passes it through `15143D18` with bounds 2 and 104 and traverses
records 2 through 103 with the same 52-byte stride. The original interval
helper was executed for 169 signed boundary pairs, including the native
constant call, which produces `[2,104)`. `1516944C` also caps high indices at
103. Together these native paths establish all 104 records. This does not
claim arbitrary invalid callers are safe.

| Offset | C field | Native use |
| --- | --- | --- |
| `00` | `process` | Callback with node in a0 |
| `04` | `process_secondary` | Alternate callback with node in a0 |
| `08` | `render` | Display-list cursor, node, signed selector; cursor returned in v0 |
| `0C` | `update` | Callback with node in a0 |
| `10` | `before_display_list` | Pointer emitted into a DE display-list command |
| `14` | `pre_render` | Cursor, type, group, signed selector; cursor returned in v0 |
| `18` | `initialize` | Initialization callback |
| `1C` | `traverse` | Node, context, byte-masked event |
| `20` | `post_render` | Cursor, type, signed selector; cursor returned in v0 |
| `24` | `after_display_list` | Pointer emitted into a DE display-list command |
| `28` | `destroy` | Callback with node in a0 |
| `2C` | `destroy_secondary` | Alternate callback with node in a0 |
| `30` | `render_mode` | Signed byte; original values are -1, 0 and 1 |
| `31..33` | Compiler alignment | Three zero bytes per record |

There are 409 nonnull pointer fields, naming 202 distinct callbacks and 46
aligned display-list destinations. Null fields remain null. The C record
uses symbolic function/data references and a signed mode byte. Its 312
alignment bytes come from the compiler's structure layout. No arbitrary
padding arrays or numeric code addresses generate the table.

## Callback and pointer evidence

The source preserves 121 active matched function definitions and three unique
active project prototypes. The shared `func_15169824` declaration comes directly
from `game_functions.h`. For the other 78 callbacks, native dispatch sites
establish integer-register ABI views. These are address-only declarations,
not claims about original C prototypes. The source never calls through its
heterogeneous function-address holder. Native views carry the existing
declaration-evidence exclusion marker so generic matching tools cannot reuse
them as general signature evidence; renderer views still retain the returned
cursor. Disabled deferred candidates are excluded from declaration evidence.

Tagged pointer types need only local forward declarations. Anonymous types
used by active matched definitions retain their exact existing definitions,
including nested unions, to preserve cross-unit compatibility. Shared headers,
function bodies and function/source-unit inventories remain unchanged.

`func_1516D400` is the initializer pointer in record 102, outside the 101-record
initialization loop. Its no-argument view follows from the complete native
232-byte leaf body, which reads globals and defines a1 before using it. An
interpreter executes the original instructions for 1,280 byte-boundary cases
with all incoming argument registers undefined; none is read. The four output
bytes agree with saturating addition in every case. No claim is made that the
initialization loop calls this record.

The 46 display-list destination symbols are explicitly named in the canonical
symbol map. Native loads at record offsets `10` and `24` and subsequent DE
commands prove that these words are pointers. At this batch's acceptance,
the declarations assigned no sizes to the destination lists and claimed no
bytes from their contents. The subsequent [effect-graphics reconstruction](us_effect_graphics.md)
adds typed list extents while preserving this table's bytes and pointer
destinations; its contents receive credit only through their own validation.

## Build placement and acceptance

The compiled table has an explicit 5,408-byte INFO placement at its native
address. The original GAME archive remains runtime backing: this work can
add matched data but no complete data. The independent reference is assembled
from the checked US ROM and must preserve the entire GAME data image.

Accepted at base `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7` plus
uncommitted changes. [The machine-readable audit](us_effect_types.json) records
native spans, declarations and pointer destinations.

The actual IDO object and independently assembled target match all 5,408
bytes and all 409 pointer relocations. Mutating each of the 5,408 byte positions
or each of the 409 relocation destinations rejects a perfect native match;
all 26 tested native-span endpoint mutations also reject. The final compiled
object preserves the mutation-tested allocated sections, relocations and
symbols after the required shared-header inclusion.

All 3,032 Docker tests pass (eight skips, 244.985 seconds). The US asset build
passes in 224 seconds, including 196.214 seconds for compile/link/verification.
Independent extraction of the linked ELF reproduces the entire 67,108,864-byte
US ROM. Native report preparation takes 440.6 seconds and report/validation
34.7 seconds, with zero compile errors and a current input fingerprint.
Progress and whitespace checks pass.

The report adds exactly **5,408 matched data bytes**, bringing matched data to
**63,302,647 / 65,120,512 (97.20846%)**, with **1,817,865 bytes remaining**.
Complete data stays at 63,245,911 bytes; code and function totals are unchanged.
The old unassigned range at `80088510` becomes a 12,184-byte prefix and a
20,392-byte suffix beginning at `8008C9C8`, with this table between them.
No display-list contents gain matching credit from their symbol declarations.

All 27,301 prior editable asset-input hashes and all 11,836 prior asset-object
hashes are preserved. All 724 retained GAME objects preserve allocated bytes,
relocations and symbols; the complete 2,072,880-byte GAME code image remains
identical. The independent linked CPU code/data reference images and original
runtime ELF are also preserved.
