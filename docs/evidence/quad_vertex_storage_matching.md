# Quad vertex storage and paired coordinate writes (US)

This manual group preserves the existing reviewed boundaries of
`game_177480.c` and `game_176A00.c`. The two functions allocate or obtain a
four-vertex block, initialize both backing buffers when requested, and write
paired coordinates derived from the existing direction tables. Their working
owner and 16-byte vertex types use the field offsets in the independent raw
assembly; they do not establish original source type or member names.

## Matches

- `func_15149FD0`, 460 bytes: the full registered span reports `CURRENT (0)`.
  Natural chained coordinate assignments recover the two stores from each
  float-to-integer conversion. Keeping the failed-allocation return before the
  coordinate section recovers the original branch shape. Direct buffer-index
  expressions remove two unnecessary named pointer temporaries and recover
  the original 0x48-byte frame without added padding or volatile accesses.
  Four vertex flag halfwords are explicitly zeroed as in the raw reference.
- `func_15149D18`, 428 bytes: the independently inspected sibling omits those
  four flag stores. Applying the proven source shape also removes the earlier
  redundant owner-pointer local and recovers the original stack placement.
  Its first revised candidate reports full-span `CURRENT (0)`, improving the
  preserved 208 candidate. No scale expression is duplicated to shrink storage.

Both individual gates preserve reviewed source-unit symbol layouts and pass
progress and whitespace checks. Both source units remain mixed. No shared
header, compiler setting, assembly body, or linker mapping was changed.

The first function's successive manual scores were 2215, 1853, 903, 228, 236,
and 0. The fourth revision followed a concrete control-flow improvement; the
final revision removed actual named expression temporaries after the remaining
mismatch was isolated to stack placement. The non-improving suffix-scope
experiment was discarded. No automated permutation was run.

## Other bounded candidates

The same pass preserves three disabled candidates, leaving their original
assembly active and adding no matched bytes:

- `func_15113C88`: best 2105 after typed entry fields and the evidenced callback
  contract. Combined condition, explicit branch, and direct logical-assignment
  shapes scored 2460, 2105, and 4814. Boolean/control-flow scheduling remains.
- `func_15147A80`: best 922 after a typed allocation record and a real 0x24-byte
  by-value packet. Precomputing allocation size and reusing its stored start
  pointer improved 4025 to 922; a ternary allocation-type expression scored
  1133 and was discarded. Saved-register allocation and branch shape remain.
- `func_1516295C`: first typed light-payload candidate scored 3909. Its stack
  layout agrees, but float promotion, load/store scheduling, and the threshold
  comparison chain differ. No speculative volatile accesses were introduced.

## Clean batch verification

The clean two-function gate on 2026-09-30 returned `BATCH_COMPLETE`. The
complete 2,072,880-byte US game-code image and all mapped external rodata
matched the owned ROM. All 1,068 tests passed (12 skipped), with metadata,
generated-progress and whitespace gates passing. This adds two batch-verified
matches totaling 888 bytes; it does not complete either mixed source unit.
