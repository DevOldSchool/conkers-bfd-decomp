# US menu text reconstruction

Bank `1C` contributes **3,107 newly reconstructed bytes**: its nested four-record
index (32 bytes) and four compressed text tables (3,075 bytes). The already
credited 40-byte outer directory is separate. Thirteen bytes between or after
compressed streams remain excluded.

## Native consumers

`151E6964` (664 bytes) selects bank `1C` with loader depth three, language and
text-table indices. At `151E6A70..151E6AB0` and `151E6AF8..151E6B40` it walks
nonzero string bytes and skips consecutive NUL bytes to construct pointers.
The US bank has one populated language child and four explicitly empty language
slots. Its child directory selects the four compressed tables.

All **438 strings** start on halfword boundaries. Each ends with exactly one
NUL and the minimum additional zero byte needed for the following halfword.
The source encoder derives these bytes from the text lengths; it does not
retain an opaque separator count. The counts are 200, 23, 71 and 144 strings,
in decoded tables of 2,444, 166, 864 and 1,960 bytes respectively.

Printable input characters are retained as text, including lowercase: the
native lookup `15042C40` folds lowercase for display and searches the checked
95-byte map at `80085930`. A space has its dedicated path. Literal `*` menu
section markers are retained; this format does not claim every source character
is an ordinary rendered glyph. The credits consumer also interprets `=`.

The four non-ASCII input codes are inline icons, not Latin-1 text. The checked
dispatch table at `80098B14` maps `B6..B9` to handlers `15041E14`, `15041E24`,
`15041E34`, `15041E44`, which select descriptors `80091710`, `80091720`,
`80091730`, `80091740` respectively. Editable sources name those native
identities without inferring artwork names. Complete spans of `150417AC`,
`150415E0` and `15042C40`, and both full data tables, are hash checked.

## Editable inputs and credit

`build/assets/asset-directories/us/bank1C/menu-text/` contains `manifest.json`
and `text.json`. The latter contains typed nested directory fields and text/icon
segments. NUL bytes and unknown binary escapes are rejected. Fresh raw DEFLATE
at level six, prefixed with the decoded length, reproduces each stored stream.

The builder preserves all existing parent inputs and initializes only an absent
child directory. Edits or missing files fail without overwriting them. Explicit
`./conker asset-directories recover --part bank1C` backs up the entire parent,
including the child, before restoring reviewed inputs. Make tracks child edits
and deletions.

The report compares all five fresh ranges against independent ROM bytes and
the complete actual `asset_bank_1c.o` linker object. The nested directory is
credited only once. Neither the outer directory nor unexplained inter-stream
bytes receive credit through this family.

## Validation

An independent reader checked every string and derived separator. All 4,780
text/icon byte mutations changed exactly the corresponding native byte; twelve
consumer-span endpoint mutations were rejected. The complete bank is reproduced
and all three existing parent hashes are preserved.

Six focused tests cover string and icon semantics, alignment, invalid inputs,
compression extents, source preservation, recovery, source races, and actual
linked-object comparisons. A real Makefile test checks edited and deleted text
sources. The 42 report tests also pass.

The full Docker suite passed **2,940 tests** (eight skipped). The required
`./conker build --assets` reproduced all 67,108,864 US ROM bytes. The native
report has zero compile errors and adds exactly 3,107 matched and complete data
bytes in one new unit. All 26,807 previously recorded source hashes remain
unchanged, with exactly two new source files.

Data matching is **63,100,336 / 65,120,512 bytes (96.89779%)**, leaving
2,020,176 unmatched bytes. Complete data is 63,079,392 bytes. Code totals and
all existing unit measures remain unchanged except for the bank-1C raw remainder,
which falls from 3,120 to 13 bytes. Snapshot freshness, progress and whitespace
checks pass.

Tested base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, with local
uncommitted changes. [Machine-readable acceptance evidence](us_menu_text.json)
records the report hash, source fingerprint, independent audit and gates.
