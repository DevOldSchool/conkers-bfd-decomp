# US actor paths and navigation graphs

This batch reconstructs 69 bank-10 actor path tables (23,194 stored bytes)
and 31 bank-19 navigation graphs (20,619 bytes), for 43,813 additional ROM
bytes. Editable sources contain coordinates, controls, path references and
graph links. Fresh level-six raw DEFLATE with the native length prefix
reproduces every selected entry. No original compressed stream is an input.
The [JSON evidence](us_route_reconstruction.json) records selected extents,
complete native consumer hashes and independent mutation results.

## Actor paths

func_150169A0 appends bank-0E actor placements to a built-in actor prefix.
It divides the returned placement size by the native 48-byte actor stride;
the difference between D_800D2100 and D_800D2101 is this appended actor count.
It then calls func_15017114 for the same scene. That loader reads bank 10
as an eight-byte directory: a relative pointer and a point count for each
appended actor. It adds the payload base to each nonzero pointer and stores
the count in the actor's byte-sized path-count table. Zero pointers remain
absent. The full loader source unit and bank readers are pinned.

Each point contains signed 16-bit X, Y and Z plus an unsigned 16-bit control.
func_150611E8 reads X/Z in a stride-eight nearest-point loop and uses the next
point's control as a movement parameter (zero selects its default value).
func_15077DBC reads the next point's X/Y/Z into actor position fields; the
next-point offset is eight bytes and is preserved in the evidence, rather
than inferred from a C structure name. func_1507B974 compares a selected
point's control against a script value. The codec calls this field control
because its meaning depends on the consumer.

The source schema contains actor_paths, an ordered array of nullable path
indices, and paths, an ordered array of coordinate/control records. It
derives all relative pointers and counts. Four directory aliases across the
selected data share the same physical path; their pointer identity remains
intact. All physical paths must be referenced and contiguous, and shared
pointers must have identical counts. All 69 payloads use zero alignment to
16 bytes, including the empty-table cases. Any gap, overlap, nonzero padding,
unknown field, invalid alias or out-of-width value fails.

Actor count is checked independently against the original bank-0E decoded
size. Those actor placement bytes are evidence for dimensions, not newly
credited data. Each source manifest records their hash and count.

## Navigation graphs

func_15085B70 loads bank 19, takes the first header halfword as the node
count and exposes the records at header + 4. Each record is 16 bytes:

| Bytes | Source field | Native evidence |
| --- | --- | --- |
| 0–5 | Signed X/Y/Z position | func_15085DF8 distance calculation |
| 6 | Height band, 0–5 | func_15085BE8 indexes six vertical groups |
| 7 | Identifier | func_15086D48 searches this byte |
| 8 | Stored radius | func_15086098 doubles it and compares squared distance |
| 9–13 | Five ordered neighbor references | func_15086098 / func_15086364 traverse them; 255 means absent |
| 14 | Group | func_15085DF8 filters candidate nodes |
| 15 | Trigger | func_15088A08 selects progression events |

func_1508B2A8 also walks all five neighbor slots. The source uses null for
255; all other references must address an existing node. Ordering and
repeated links are retained. The selected headers' second halfword is zero,
and their final four alignment bytes are zero. These are derived constants
of this bounded format, not opaque source fields.

Entry 26 has an unexplained secondary header of 61. Entry 38 uses the special
link value 253 outside its node range. Both remain raw and receive no credit;
this batch does not assign semantics to either variant. Bank index and gap
bytes also remain raw. Other graph fields are range-checked at their native
width without imposing names for unproved enum values.

## Build, inputs and independent checks

scripts/route_codec.py supplies strict semantic encoders/decoders.
scripts/route_build.py verifies the reference ROM and full native consumers,
checks actor counts, publishes editable routes.json files on first use and
packs actual ROM bank parts. Run ./conker route-assets build, optionally
with --bank 10 or --bank 19. Inputs live under build/assets/routes/us/bank10
and bank19. Edited, malformed or missing sources fail without overwriting
them; explicit recover --bank backs up the entire chosen directory first.
Source hashes are checked before and after packing.

Make rebuilds the two actual asset-bank objects incrementally. An unchanged
bank retains its object timestamp when the other bank changes. Missing
manifests, semantic sources, backing files or generated parts are handled by
explicit prerequisites. Native objdiff uses only the regenerated physical
ranges from those actual linked objects and independently checks them against
the original ROM. Unselected bytes are retained in the raw-storage units.

Nine focused route tests and all 34 Make scheduling tests pass (39.035 seconds
for the Make suite). The focused tests exercise shared pointer identity,
coordinate/control changes, graph fields, invalid bounds, unexplained
padding, recovery, races and rejection of stale linker objects.
The independent audit checks 962 actor directory entries, 917 physical paths,
4,012 points, four aliases and 1,686 graph nodes. All 7,328 endpoint path-field
mutations and 624 endpoint graph-field mutations produce exactly the changed
native records; all 34 consumer endpoint mutations fail their hash guards.
Both complete banks remain byte-identical. All 25,987 prior source-file hashes
are unchanged. Full ROM/native-report acceptance is recorded below.

## Accepted checkpoint

The full reconstructed 67,108,864-byte US ROM matches SHA-1
4cbadd3c4e0729dec46af64ad018050eada4f47a exactly (101 seconds wall clock).
All 2,560 tests pass in 128.278 seconds, with eight existing skips. Native
objdiff, progress and whitespace gates pass. Matched Data is
61,707,691 / 65,120,512 bytes (94.759224%), a gain of 43,813 bytes.
Code measures and denominators are unchanged. The only pre-existing measure
changes are the raw bank-10 and bank-19 storage units. All 10,652 prior asset
proofs and 25,987 prior unique source hashes are preserved.

Tested base commit: 094102644c4c2f5aefaa0fc4b609416918f66f58 plus the
uncommitted reconstruction sources. Source fingerprint:
78e3fb80d8d28179670186fb44a514ff204f473ccf5c76de0cf89773cb7163e6.
Report SHA-256:
fb88a11f48c9f03d45d5c19d0d9cd28a61a220a8ffe2c97c04adb1adde109dcd.
