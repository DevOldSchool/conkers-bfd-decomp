# US particle variant pointer tables

This batch reconstructs 1,128 bytes in sixteen typed pointer tables.
The 282 entries use real references into `D_8008ED80`, the independently
reconstructed 56-byte particle descriptors. These definitions do not change
function bodies, shared types, assembly or the runtime game-data archive.
They remain INFO verification owners, not completed original source units.

## Native selection and extent evidence

The complete registered US functions are pinned against the checksum-validated
ROM in the accompanying JSON. Raw assembly, where present, is independently
checked over each complete registered span.

`func_1518D6E0` follows the category root to its table and signed filter count.
It reads the actor's applied representation ordinal at `+0x1C8`. Each row
contains `filterCount + 2` pointers: filter-specific slots, a default slot,
and a final slot used by the alternate selection path. Native loads at
`1518D8BC`, `1518D90C` and `1518D970` establish these pointer roles and the
four-byte element width. The selected value becomes the descriptor pointer
used by the already reviewed parameter and point consumers.

There is a concrete producer for ordinal five. In `func_15065A5C`, literal six
at `150669B8` reaches the actor's override byte `+0x1C9` at `150669D4`.
`func_1502FBE8` subtracts one, checks the result against total count `+0x2C9`,
loads the selected model byte, calls the assignment helper, and restores the
saved ordinal before writing `+0x1C8` at `1502FC8C`. The call cannot substitute
its return value for this saved ordinal.

The count is independently grounded in ROM defaults. `func_1503D774` loads
bank `0x11` and saves the first relocated segment as the model's defaults.
`func_150839B8` installs the representation list from defaults byte five,
loads the automatic count from byte four, then adds defaults byte `0x38`
to form total count. The native bank includes counts of six and seven.
Model zero has seven model bytes `[0, 1, 2, 3, 4, 130, 150]`; ordinal five
therefore passes the native count guard and selects model 130.

Each source covers six rows through that concrete ordinal. The category's
native filter count supplies the row width. All entries are read individually
from the original image and checked as aligned references to the descriptor
array; repeated rows are not synthesized from a single sample. The extent
calculation does not use neighbouring labels.

## Limits

Each table's six rows fill its storage up to the next object; that is a storage
extent, not a universal upper bound on the ordinal. Model zero's seven-entry list prevents
such a bound claim. The particle constructor rejects current model 150, but
that check does not establish that an existing effect cannot persist into
ordinal six. That runtime question remains unresolved.

The common table format and native ordinal producer establish storage typing;
they do not prove that every category/ordinal combination executes. Category
zero has no observed call in the reviewed constructor dispatch. Its root and
category record share the independently established format, and its runtime
activation remains unproven. These limitations do not alter stored values.

## Validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted work.
The pinned compiler's sixteen pilot objects reproduce all 1,128 bytes and
282 pointer destinations/addends. Fifty-six compiler alignment-tail bytes
are excluded from matching credit. The independent whole-GAME reference is
byte-identical, and native objdiff matches all sixteen pilot owners.
Integrated preservation passed for all 792 prior GAME objects, including
allocated bytes, symbols and relocations. The 2,072,880-byte GAME code image
and function/source-unit inventories are unchanged.

Native objdiff rejected all 1,692 mutations: one at each of the 1,128 byte
positions, plus wrong destinations and wrong addends for all 282 pointers.
The independent ROM-byte gate also rejected every payload-byte mutation.
The full suite passed 3,033 tests with eight skips (283.114 seconds).
`./conker build --assets` passed in 200 seconds wall time, and the independently
extracted 67,108,864-byte US ROM is byte-identical.

The full report adds exactly 1,128 matched bytes: 63,319,927 of 65,120,512
(97.234996%), leaving 1,800,585. Complete data remains 63,245,911; code and
function measures are unchanged. All 27,301 prior asset input hashes and
11,836 asset object hashes are preserved. Sixteen actual integrated INFO
objects match their report candidates. The runtime link graph is unchanged.

Report SHA-256: `c1707966a2de2a5b0b5e73b8ea51b212a39029790b2c0c625e01537d1ecc8fa3`.
Source fingerprint: `840c61315ff3fb2956da3381f6470663d6b941f1aa0fee85e1a4a86ca955a1de`.
Report preparation took 455.1 seconds; reporting and validation took 28.2 seconds.

Temporary scripts and snapshots are under
`build/us/data-completion/particle-variants-*`.
