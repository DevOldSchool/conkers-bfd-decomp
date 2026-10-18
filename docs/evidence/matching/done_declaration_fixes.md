# Completed-source declaration fixes

Reviewed on 2026-10-18 from main revision `3138d7aa`, on
`codex/done-declaration-fixes`. Changes are source-local; no shared headers,
assembly, compiler options, asset reconstruction or storage definitions change.
Padding, overwritten float parameters, SDK type migration and `game_EBD00.c`
are outside this batch.

## Independent input and RNG comparison

US ROM SHA-1: `4cbadd3c4e0729dec46af64ad018050eada4f47a`.
Freshly extracted game-code SHA-1: `90d7bf2f61e5fd4e2e6b72ea4d21ce9447382fe5`.
The reference was regenerated from that ROM in the isolated worktree.

Both complete-source variants of `func_150F51E8` were compiled by the pinned
IDO toolchain with `./conker probe`:

| Declaration and calls | Full-span score | Frame |
| --- | --- | --- |
| `u32 func_150ADA20();`, retaining both pointer arguments | CURRENT (0) | 0x20 |
| `u32 func_150ADA20(void);`, omitting both arguments | CURRENT (0) | 0x20 |

The requested tie-breaker selects the `(void)` variant. This comparison does
not establish the original source signature. In the raw caller, the first
address in `$a0` also supplies the counter load at `0x150F5220`; the second
supplies the counter store at `0x150F526C` in the second call's delay slot.
Thus these address constructions do not independently establish an argument.
The raw RNG overwrites incoming `$a0` immediately at `0x150ADA20`.

The prototype is local to `game_122650.c`; its only two calls are in
`func_150F51E8`. Other translation units' prototypes and callers are unchanged.
Probe sources and scores are retained under
`build/us/manual-attempts/done-declarations/` (ignored).

## Cache storage declarations

`func_15008DD0` now declares `D_800DD460` as `u8 *[2]`, consistent with the
existing pointer-array declaration in `src/game/game_1A8060.c`. The raw
allocation/teardown family and its two-entry evidence are documented in
[the compact display/resource boundary evidence](../boundaries/game/families/game_raw_compact_display_resource_pairs.md).
The unused `D_800DD468` extern is removed. The two stores are preserved.

`func_15012780` likewise declares `D_800DD410` as `u8 *[2]`. Raw
`func_15177410` allocates a 0x2C-byte record at `0x15177450`, retains its
pointer in `$s1`, and stores it into the indexed table at `0x1517747C`.
`func_15177A94` traverses those pointers. The adjacent counter is at
`0x800DD418`; the reset's two stores bound its table span to eight bytes.
The previously ineffective `volatile` declaration and qualifier-stripping
cast for the counter become a plain `s8` declaration and assignment.

These local declarations affect only their respective reset functions.
No declarations in the unmatched consumer units were changed.

## Bitset: investigation only, declaration unchanged

`func_15016588` clears exactly eight bytes: raw `0x150165B8` calls the clear
routine with `a1 = 8` in its delay slot. Its loop limit is `0x43` at
`0x150165D0`, so indices 64 through 66 can read/write byte eight at
`0x800BE588`. The byte access is explicit at `0x15016624` / `0x1501662C`.
The reader `func_15080738` computes the byte index through `arg0 >> 3` and
loads from the same base at `0x1508075C`; it supplies no allocation bound.

The checksum-validated ROM's initialized game data spans
`[0x80082B20, 0x800B0DC0)`. The bitset lies outside that data, inside the
startup-cleared interval `[0x800B0DC0, 0x800E9D00)` established by raw
`func_15007A20` (`0x15007A24` through `0x15007A3C`). There are no initialized
ROM bytes at `0x800BE588` from which to recover its ownership.

A scan of the regenerated main/debugger and game assembly finds the bitset base at
`0x800BE580` and the next directly referenced global at `0x800BE590`.
No separate direct label at `0x800BE588` was found. This bounded negative
result does not prove an original allocation boundary: the gap could include
alignment or otherwise unidentified storage. No original BSS symbol size or
allocation definition establishing a ninth owned byte was found.

Therefore the accessed extent is at least nine bytes, but the original
allocated extent remains unresolved. Under the user's extent-confirmation
condition, `game_439B0.c` remains unchanged, including its redundant extern.
Neither the eight-byte clear nor the loop is altered. This is an unresolved
review finding, not a claim that the original code was memory-safe.

## Validation

The three edited functions each passed `./conker finish` with independent
full-span US `CURRENT (0)`, source-unit layout, progress and whitespace checks.
Each required one applied candidate and one successful finish. The RNG also
had one two-variant probe batch. No permutation or frame reconstruction was used.

The first clean batch stopped before compilation because the fresh worktree
lacked `reference/us/asm`. The supported
`./conker _prepare-reference --profile us` command regenerated that independent
reference successfully; this is a setup repair, not a source/layout change.
Clean batch validation after that repair completed successfully:

```sh
./conker verify-batch func_15008DD0 func_15012780 func_150F51E8
```

Result: `AGENT_ACTION: BATCH_COMPLETE` (clean). The integrated game image is
byte-identical to the US reference. The Docker matching subset ran 980 tests
across 67 modules, with six skipped; the suite passed. Project metadata,
canonical progress, source-unit layout and whitespace gates passed.
No asset reconstruction changed, so an asset build was not required.
Validation preceded commit creation. The tested source state is base
`3138d7aa` plus the three source changes below (SHA-256):

- `src/done/game/game_122650.c`: `1788041ed218428618802371bd6b6bba078cedffcda785cdba8264b104ad7952`
- `src/done/game/game_36280.c`: `df32e0089df957258aad20a0fdf16087757f24be5571ba01f0c0093809b4493a`
- `src/done/game/game_3FC30.c`: `926db17d483ebb7a6b86aca0b4547dca6db4fb0715de1c6da65d373d68c32649`
