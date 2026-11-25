# US effect graphics data

The data owners in `src/game/data/effect_graphics/` reconstruct 2,536 native
bytes in 31 disjoint ranges. These ranges contain 63 typed objects: 52 `Gfx`
command lists (1,896 bytes), seven `Vtx` arrays (544 bytes), one 64-byte `Mtx`,
two eight-byte selector arrays, and four proven display-list pointer slots
(16 bytes). Their placement does not establish original C-object boundaries.

## Native consumers and bounds

The effect-type table at `8008B4A8` supplies 46 distinct setup/teardown list
addresses. Native renderers read the table's pointer fields and submit them
as display-list commands; see [the effect-table evidence](us_effect_types.md).
Following pushed display-list calls adds the shared list at `8008CE60`.
All 47 lists terminate, and their call graph is acyclic. Their 199 commands
occupy 1,592 bytes. Each command is reconstructed with SDK macros, including
the exact combiner selectors, mode bits, signed conversion coefficients,
texture fields, colours and geometry flags. A terminating command determines
each list extent; adjacent unrelated bytes are excluded.

Native matrix-load commands in 18 of these lists point to `80089470`.
The SDK's `Mtx` representation and `guMtxF2L` packing establish the high
integer plane followed by the low fractional plane. The reconstructed
64 bytes are the exact fixed-point identity matrix, without a raw byte array.

The guarded native consumers in `model_embedded_geometry.py` establish the
four type-06 vertices at `8008D538`, six type-08 vertices at `8008CD90`, and
six type-13 vertices at `8008B3E0`. Type 08 also has a bounded six-command
static display list at `8008CDF0`. Type 13 modifies texture coordinates at
runtime; its stored initial values remain unchanged in this reconstruction.

For type 55, `func_1518A3C0` masks a random result with one and selects from
`8008D5B0` or `8008D5B8`. The arrays contain `(0,1)` and `(2,3)`, respectively.
Both native branches store the selected value in descriptor byte 6 and call
`func_151580B0`. That constructor copies the descriptor to object offset
`10`; the renderer `func_151582C8` reads object byte `16`, multiplies it by
four, and reads the pointer table at `8008AFB8`. Full native spans and the
selector producer's instruction anchors are recorded in the JSON evidence.
This proves pointer slots 0 through 3 and their four display lists and vertex
arrays. The arrays contain 5, 4, 5 and 4 vertices at `800A6080`, `800A60D0`,
`800A6170` and `800A61C0`.

The fifth pointer at `8008AFC8`, list at `8008AEE0` and vertices at `800A6110`
remain unclaimed. The existing inspection gallery's five variants do not
establish a native selector bound. The four-slot declaration describes a
proven prefix, not the original pointer table's full extent.

## Source and reference representation

The shared header `include/game_effect_graphics.h` uses the pinned SDK's
F3DEX2 `Gfx`, `Vtx` and `Mtx` types. Its normal include-directory placement
also supports the report's temporary copies of these C sources.
`PR/mbi.h` supplies the SDK's constant-expression packing macros. The
effect-type owner now uses `Gfx *` for its two display-list fields. Its 5,408
stored bytes and 409 pointer destinations remain unchanged. The compiler
records sizes for the 46 existing undefined graphics symbols and emits 17
additional unused declarations from the header; these are symbol metadata,
not additional storage or table entries.

The canonical symbol map records all 63 exact extents with scalar pointer
inference disabled. `config/relocs/game-data-us.txt` explicitly identifies
the 31 actual address words: 18 matrix pointers, five vertex pointers,
four selector pointers and four nested display-list calls. Scalar graphics
words must not acquire guessed relocations merely because their bit patterns
resemble an address. The independent target is assembled from the checked
US ROM, preserving the entire GAME data image.

Each owner is linked at its original address in an INFO section. The
original GAME archive still supplies runtime data. This batch can therefore
add matched data, with no complete-data credit. The compiler's 72 trailing
alignment bytes and all gaps between owners are excluded from matching
credit. All selected ranges were unassigned in the accepted effect-table
baseline, so no prior data is counted twice.

The Makefile declares the shared header as a prerequisite of all 31 owners
and `effect_types.o`. A dry-run dependency check verifies that changing the
header rebuilds all 32 objects.

## Accepted validation

Base commit: `38f3c3348cf5dbeeb0a0b191f3f4576c85a97bc7`, plus uncommitted
work. The US GAME build and 79 focused tests pass (two host-only skips).
The compiled and linked graphics payloads reproduce all 2,536 original
bytes and 31 address fields. All 725 retained GAME objects preserve allocated
bytes and relocations; the effect table has only the declaration metadata
changes described above. The entire 2,072,880-byte GAME code image and both
function/source-unit inventories are unchanged.

The independently assembled native targets match all 2,536 graphics bytes
and the existing 5,408-byte effect table. Mutating each of the 2,536 graphics
byte positions and each of the 31 pointer destinations rejects a perfect
match: all 2,567 negative cases are detected. The report's 32 temporary C
copies compile and preserve the actual linked objects' allocated sections,
relocations and symbols. These same sections remain equal to the
mutation-tested objects after the include-path repair.

The final-state Docker suite passes all 3,033 tests with eight skips
(370.301 seconds). The complete asset build passes in 270 seconds including
setup, with 264.572 seconds for the build and 242.642 seconds for
compile/link/verification. An independent extraction from the linked ELF
reproduces the original 67,108,864-byte US ROM, SHA-1
`4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The final native report passes with zero compile errors: 428.2 seconds of
preparation and 26.3 seconds for reporting and validation. It adds exactly
**2,536 matched data bytes**, reaching **63,305,183 / 65,120,512
(97.21235%)**, with **1,815,329 bytes remaining**. Complete data remains
63,245,911 bytes. Code and function totals are unchanged.

The four prior unassigned ranges beginning at `80085EC0`, `80088510`,
`8008C9C8` and `800A6004` are partitioned into the 31 owners and their
remaining gaps. All other existing report measures are preserved. All
27,301 prior editable asset-input hashes and 11,836 asset-object hashes
remain unchanged. The independent linked CPU code/data images and original
runtime ELF are also unchanged. All 31 actual INFO objects agree with the
report's compiled candidates; INFO objects do not enter the runtime
link-input graph or gain complete-data credit.

Progress and whitespace checks pass. [The machine-readable evidence](us_effect_graphics.json)
records native bounds, compiled objects, negative checks, header dependency
verification, final report comparison and recovery of an unintended
host-tool-generated assembly header. The pinned container is used for target
generation; the tracked assembly header is restored unchanged.
