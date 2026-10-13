# US visibility node-set reconstruction

Sixteen bank-05 visibility bitstreams now have editable node-set sources,
adding 151,949 reconstructed ROM bytes. Together with the previously accepted
20 codebooks, the visibility unit covers 164,494 bytes. The selected even
entries are 4, 12, 14, 22, 38, 52, 54, 60, 72, 86, 88, 90, 96, 104, 110 and 120.

The original codebook acceptance remains recorded in
[the preceding evidence](us_visibility_reconstruction.md). The new
[JSON evidence](us_visibility_bitmaps.json) contains per-scene dimensions,
complete native consumer hashes, independent decoding and mutation checks.

## Native meaning and dimensions

The scene loader takes the primary model from bank 04. func_15003668 installs
its geometry in mode zero: func_15002724 counts triangle commands and
func_15001460 records their vertex pointers. Other model parts and dynamic
objects use separate modes. func_150038A0 resets the counters, constructs the
mode-zero quadtree, and passes its node and leaf counts to func_150025FC.
The wrapper func_1510F800 selects geometry through func_150A49F4.

The independent CPU display-list replay follows func_15001460's actual
vertex-cache loop and its one-, two- and four-triangle instruction formats.
All admitted primary lists use segment-one vertices with cache start zero.
The native loop ends at count, rather than cache start plus count; other
loads are rejected. The independent replay agrees with the established
model parser on every triangle in all 19 populated bitmap scenes: 46,000
triangles and 2,146 vertex loads.

func_15001BC8 starts with center X/Z zero and half extent 32,768.
func_15001DE0 retains triangles intersecting the current square and stops
when fewer than ten remain or the half extent is below 512. Otherwise it
allocates four children in (-X,-Z), (-X,+Z), (+X,-Z), (+X,+Z) order.
func_15001B10 counts all nodes, and the leaf path counts rows.

func_15002248 translates vertices into the box frame, with unchanged Y,
and invokes func_15049260 / func_150AAD98. func_150492CC sets the box's
full vertical extent to 32,000. All reviewed vertices lie strictly within
[-16,000, 16,000], so an inclusive integer triangle/square separating-axis
test independently reconstructs these scenes' X/Z subdivision. The builder
rejects geometry outside that vertical slab. This bounded model is not a
claim of general floating-point equivalence for arbitrary new scenes.
Its node/leaf counts agree with the unique full-stream dimensions of all
19 original populated visibility bitstreams.

The full four-child tree gives rows = (3 * nodes + 1) / 4. func_150025FC
loads bank-05 entries scene * 2 and scene * 2 + 1 and computes row stride as
align16(ceil(nodes / 8)). func_150183D0 walks the Huffman tree MSB first to
locate each row. func_150A6760 applies each decoded byte's bits LSB first
in native node order. Complete source-unit spans pin the quadtree, scene
setup, embedded collision helpers and geometry selector, in addition to
the previously pinned Huffman and bank-loading consumers.

## Editable representation and exclusions

Each bitmaps.json record contains a format, node_count and one sorted list
of visible node indices per leaf. The encoder derives the row stride,
LSB-first flag bytes, zero unused bits, Huffman codes from the paired
editable codebook, and final zero alignment to eight bytes. It then uses
the reviewed bounded level-six encoder to regenerate the complete RZIP
entry. Original Huffman bytes and compression tokens are not source inputs.

Entries 24, 46 and 58 have 34, 245 and 90 nonzero bits beyond their derived
node counts. Their meaning is unproved; the strict codec rejects them.
Their combined 13,372 stored bytes remain raw and uncredited. Bank index,
gaps and all other unselected ranges also remain uncredited.

The existing visibility input directory is extended through the normal
recover transaction after checking every previous source hash. All old
files are preserved in the recovery backup. Current codebooks.json and
backing.bin remain byte-identical; only manifest.json changes and
bitmaps.json is added. Packing rejects missing, malformed or edited inputs
without overwriting them, and checks source hashes again after packing.
The actual ROM linker object must equal the regenerated bank. Native
objdiff receives only the proved physical ROM slices.

## Validation

Fifteen focused visibility tests pass. They cover independent native
Huffman decoding, flag order, node mutations, row and dimension bounds,
unused-bit rejection, EOF/alignment errors, CPU cache/opcode semantics,
exact quadtree thresholds, geometry disagreements, source preservation
and source races. All 33 Make scheduling tests also pass (36.799 seconds),
including missing bitmap source rejection.

The independent original-ROM audit decodes 481,424 flag bytes containing
1,616,288 visible-node references. All 32 first/last-row node mutations
change the regenerated stream and decode to exactly the changed flags;
all 28 first/last-byte native consumer mutations fail. The complete bank
matches the original. All 25,986 prior source hashes are preserved, with
the previous visibility manifest retained in its recovery backup.

Full asset reconstruction passes in 98 seconds (95.128 seconds in the
build process, 84.279 seconds compiling/linking/verifying) and reproduces
all 67,108,864 ROM bytes. SHA-1 is 4cbadd3c4e0729dec46af64ad018050eada4f47a.
The Docker suite passes 2,550 tests in 124.806 seconds, with eight skips.
Native objdiff has no compile errors; progress and whitespace checks pass.

Matched Data is 61,663,878 / 65,120,512 (94.69194%). Matched and complete
Data each gain 151,949 bytes; Code and the denominator are unchanged.
Only the visibility and corresponding raw bank-05 measures change. All
10,651 unaffected prior asset proofs and 25,986 prior source hashes remain
preserved. The source snapshot is current.

Tested base: 094102644c4c2f5aefaa0fc4b609416918f66f58 with local changes.
Source fingerprint: 23b9ae6683232c63151cff96cb3f0fd9cb191a50a781c97a3cd1fc1c074604b2.
Report SHA-256: c109d1502a9f9f022e09ffaed05b49f0a01432cb8efed29665d5f1ac76ccf646.
