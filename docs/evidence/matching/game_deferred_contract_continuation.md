# Deferred GAME contract and descriptor continuation (US)

This checkpoint records source-valid candidate improvements and contract repairs.
It adds no accepted C matches or completed source units. All six candidates below
remain assembly-backed. Exact assembly equivalence and source validity are separate
requirements; a rejected focused zero is not progress credit.

## Plane-test intrinsic: 1510AEE0

The sole 400-byte member of `game_138390.c` uses two `abs.s` instructions in
independent raw assembly. Its preserved `__builtin_fabsf` spelling compiled calls.
The already established file-scope `f32 fabsf(f32);` and
`#pragma intrinsic(fabsf)` mechanism removes those calls without changing the ten
argument slots, arithmetic grouping, comparisons or optional outputs.

The retained form measures `CURRENT (1394)`. It names the actual horizontal and
vertical projections and reuses each scalar for its scaled magnitude. It
naturally recovers the raw 0x10 frame
and vertical-result spill. Register/evaluation order and extent differences remain.
No volatile, artificial storage, padding, flag change or permutation was used.

## Consumed cleanup-owner arguments: 15101090 and 15101148

`game_12E540.c` declared `1513CA6C` and `1513CAA0` as taking no arguments.
Their accepted definitions in `game_169510.c` consume and forward a full word.
Independent raw final call delay slots in both deferred cleanup functions reload
the original owner into a0. Accepted wrappers `151011E8` and `15101210` likewise
preserve original a0 while clearing the linked resource through v0.

The four local declarations now take s32 and all four calls explicitly pass the
original owner. The pointer-to-s32 value conversion follows the pinned 32-bit
IDO representation; it is not a portable pointer encoding or an lvalue-punning
operation. Callee implementations and shared headers are unchanged.

The unsupported top-level volatile parameter on `15101148` was removed.
Corrected 15101148 measures 1223; corrected 15101090 measures 2446. Earlier forms
omitted the consumed argument, so their lower scores do not establish valid
source improvements. Both changed accepted wrappers
retain full focused CURRENT (0).

The wrappers' pre-existing s32 clear at linked-owner +0x138 has an unresolved
representation relationship to pointer-shaped loads elsewhere. The producer and
backlink chain was insufficient to require a specific typed-null rewrite. This
checkpoint certifies the argument correction, not the entire older storage model.
No unrelated cleanup declarations or bodies were changed.

## Triangle-vector helper: 15144E80

A fresh implementation uses six genuine three-float vectors: three converted
vertices, two edges and an optional normal fallback. It preserves the four-pointer
interface, nine signed-halfword conversions, repeated-vertex checks and two calls
to the existing cross-product helper. Ordinary x/y/z edge order produced focused
CURRENT (0) across all 564 bytes and preserved the reviewed layout.

That form was rejected by independent source review because its final aggregate
store did not have a compatible destination object on known active caller paths.
Accepted `1514FEFC` and `15153C84` declare byte scratch arrays and pass their
interiors through `1514F640`. Writable extent alone does not establish a vector
aggregate. The match was transactionally reopened and receives no C credit.

The retained candidate uses the SDK-compatible ordinary memcpy contract for the
12-byte final copy. It measures 1615 because the compiler emits a call. No
undocumented intrinsic, incompatible word view or fake object was substituted.
A complete GAME search found 14 direct calls; the bounded ready output showed only
eight. The other twelve direct owners are raw stack callers.

A natural 0x2C descriptor is supported for the two active byte-scratch owners, but
no caller edit is included. Further issues remain: a failed triangle conversion
leaves vectors uninitialized before later normalization, and a local normalizer
prototype conflicts with its existing vector-pointer definition. A storage-only
rewrite would not establish the necessary whole-path invariant.

## Combined descriptors: 151568F8 and 15156D24

The fresh 604-byte splitter in `game_183640.c` constructs two complete records.
The first consumer, `151539B4`, reads through byte +0x46, establishing a naturally
aligned 0x48-byte burst descriptor. Accepted `15130374` forwards the second record
to accepted `15130280`, which copies exactly 0x70 bytes. The sprite record therefore
includes real byte storage for untouched ranges; no uninitialized scalar is
newly evaluated and no extra zero stores were added.

The input's first twelve bytes are an actual XYZ float vector, backed by the
finite 3-by-10 point-table producer traversal and its initializer. The +0x6C/+0x70
pair consists of two real float scale fields. Typed aggregate copies stay between
compatible, complete fields. The splitter reads only through input byte +0x88.
Its sole observed producer writes four additional bytes through +0x8C, so the
shared local combined-record type is a complete, naturally aligned 0x90 bytes.
Unknown trailing fields retain neutral names rather than invented meanings.

The splitter has no pre-existing concrete declaration establishing a narrow
selector formal. It retains s32 and explicitly normalizes the low byte.
Normalizing the same formal once produces `CURRENT (1075)`, the exact 0xE0 frame,
and every descriptor offset. Argument-home and GPR scheduling differences remain.
No narrow ABI was inferred to remove them.

The 624-byte producer retains its established `(void *, u8)` interface, all actual
field stores, the exact external float constants, all seven calls including a
discarded PRNG result, and both independent flag updates. Its complete record and
genuine scale-local form measures 2335. The larger candidate frame does not
justify truncating the record, introducing an unused scalar or forcing alignment.

## Validation scope

The changed units remain mixed or raw-backed. Independent reviews checked the
new arithmetic, complete storage, consumed arguments and caller evidence. The
checkpoint regression set contains 65 previously accepted functions across the
four changed source units; candidate coverage does not count as matching coverage.
The clean batch returned BATCH_COMPLETE, and all 65 accepted functions reported
full focused CURRENT (0). All 114 registered member spans and layouts, the full
US ROM/GAME/RSP images, and existing data/rodata mappings passed. The ordinary
and pinned-toolchain/ROM suites each ran 1,703 tests and passed (37 and one skips).

At the common pre-mapping compile stage, every allocated section byte, size and
alignment and every normalized relocation match the baseline. The only external
symbol metadata difference is st_size=4 instead of 0 on five explicitly declared
undefined float symbols; their names, values, relocation sites and kinds are
unchanged. Existing external-rodata mapping is checked separately by the full
production-image gates. No repository comparator, compiler option or gate changed.
