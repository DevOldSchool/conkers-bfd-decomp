# Quaternion and sight candidate pass (US)

This pass adds three source-valid deferred candidates and records one genuine raw
blocker. It adds no C matches or completed source units. All implementations stay
behind the supported deferred-candidate guards with their original assembly active.

## Matrix to quaternion: 15049CB8

The fresh 548-byte helper in `game_770F0.c` has two direct callers, both in raw
`15038620`. Each supplies a complete 64-byte matrix and a disjoint 16-byte output.
The caller's bounded normalization loops initialize every one of the nine matrix
floats read by the helper. Subsequent quaternion consumers read all four outputs.

The low-trace path copies a real 12-byte local index table. Independent US data
contains exactly `{1, 2, 0}` at `D_80085FF0`; the largest-diagonal choice and cycle
lookups keep every index in 0..2. `D_80099090` is binary32 `0x3C23D70A` (0.01f).
Both objects keep their external data ownership. The existing
`f32 func_10026530(f32)` call is preserved rather than replaced by an intrinsic.

The candidate uses real row pointers and column offsets, scalar float output
stores, and the original operation grouping. No speculative aggregate write or
uninitialized local is required. It measures `CURRENT (3127)`; frame,
output-pointer allocation and arithmetic scheduling remain unmatched.

## Sight dispatcher blocker: 151C9BA0

The 584-byte dispatcher reads `D_800CBFA8 + index * 0x32C`, where the index is
loaded from a nested owner's byte +0x65 and is only checked for nonzero. The
available source declarations, reviewed evidence and previous ledgers do not
establish the complete backing-array extent or valid index range. Nearby scalar
aliases and other deferred pool walks do not establish that contract.

The supported raw-block transaction records this missing proof. No C starter,
fabricated array declaration or integer-address workaround was added. This is a
blocker record, not a matched or translated function.

## Two-object sight constructor: 151CC524

The 600-byte constructor has two actual 0x58-byte locals: a spawn descriptor and a
custom payload. The allocator copies the entire spawn record and reserves 0x70
base bytes plus the 0x58 payload, giving a 0xC8-byte owner. Both allocation results
are tested before the payload copy.

Two narrowly scoped local contracts were corrected:

- The target's forward declaration now returns void, with all six s32 arguments
  retained. Both complete-GAME direct callers discard v0, no initialized data
  entry points to the target, and the raw epilogue has no separate result
  production after its final conditional copy. No result was invented from a
  transient register to satisfy the old declaration
- Four local `func_10022EC0` declarations now use the verified SDK memcpy contract,
  `void *(void *, const void *, u32)`. All four existing local calls discard its
  result. Three are deferred; the one active call copies a real owner pointer

The payload's owner is actual u8-pointer storage, matching accepted updater
`151CC77C`. Conversion from the existing s32 address formal uses the fixed 32-bit
IDO representation, not an integer lvalue read as a pointer object. The payload
flags and nested selector are initialized to zero. Registered updater 9 and event
handler 7 use this initialized prefix; no reserved-tail value read was found.
The remaining payload bytes are real byte storage transferred as representation,
not a fabricated short object or newly evaluated uninitialized scalars.

The dynamic flag shift is unsigned and explicitly masks its count to five bits,
matching raw `sllv` semantics without assuming an unproved signed-shift range.
The descriptor flag field is u16, matching its unsigned halfword consumer.

One ordinary trial measured 5208 with a 0xE8 candidate frame versus raw 0xE0.
It is retained without shortening either required record, forcing alignment,
changing accepted bodies, or narrowing fullword formals.

## Sight flash callback: 151CC2BC

The fresh 616-byte callback's established table type is
`void (void *, void **, u8)`. Independent initialized data maps table slot 3 to the
target, and the actual dispatcher forwards the same three arguments. The byte
formal therefore comes from an existing contract, not a register-matching guess.

The event producer `151CC290` passes a real s32 local. The body reads that word
through an s32 lvalue and compares it with the constructor-backed s32 payload
identity; it does not dereference the public `void **` formal as a pointer object.
The callback then sets one flag, writes a 35.0f timer, and copies four color values
through ordinary unsigned float-to-word and word-to-byte conversions.

The constructor initializes those source floats to `{255, 0, 0, 255}` and reserves
all required owner bytes. The registered update and draw paths do not overwrite
or expose the source-color locations. The values remain finite and representable
for all four conversions. Event dispatch is synchronous, and the reviewed
retirement paths retain owner storage through this callback. No FCSR instructions
were handwritten or hidden behind a helper.

The retained form measures CURRENT (10): only the two identity-load register
assignments differ; the entire conversion sequences, control flow and stores
otherwise match. The candidate remains assembly-backed and receives no exact
match credit.

## Acceptance scope

Independent source reviews cover all retained forms and local contract changes.
The regression set contains 15 existing accepted members across two units, with
50 registered members in total. All 15 accepted functions retained full focused
CURRENT (0), all 50 registered spans and layouts passed, and the canonical clean
batch returned BATCH_COMPLETE. The full US ROM, GAME, RSP and mapped data/rodata
remain identical. The ordinary and pinned-toolchain/ROM suites each ran 1,703
tests and passed, with 37 and one skips respectively. Progress and whitespace
checks passed. Candidate scores do not substitute for any of these gates.

At the common pre-mapping compile stage, allocated section bytes, sizes and
alignment and semantic relocation targets match the baseline. Explicit extern
declarations may add size annotations to undefined symbols; these allocate no
storage and do not change linked targets. No compiler option, comparator, tool
gate, assembly or shared header changed.
