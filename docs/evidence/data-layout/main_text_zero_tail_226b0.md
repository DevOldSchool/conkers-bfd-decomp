# Main text zero-tail classification at `0x226B0`

The 64-byte interval `0x226B0:0x226F0` is a known zero-filled text tail.
It is outside the complete exact 592-byte `n_resample.o` ending at `0x226B0`
and before independently matched `bzero.o` beginning at `0x226F0`; see the
[existing object evidence](../libraries/libultrare_us_continued_reconstruction.md).
The preceding resampler returns before this interval. All sixteen owned ROM
words are zero. No conditional branch crosses the interval, no main/game
J/JAL selects an interior address, and initialized main/game data has no
pointer into it. These negative scans supplement the complete adjacent object
proofs; they are not a claim of universal runtime unreachability.

The canonical profile classifies it as `data` with explicit `.text` linker
ordering, preserving its exact position and all 64 bytes. The neutral name
`main/data/padding_226B0` describes the storage, not its unknown original
object owner. The independent raw-reference map remains unchanged. No function
or source unit is invented for the tail, and no C-match credit is awarded.

This follows the established text-resident data representation used by the
[game data tail](../boundaries/game/mapping/game_reconciled_text_data_tail_aa470.md). Full US ROM equality
is required after regeneration, along with the map and metadata test suites.

The range SHA-1 is `c8d7d0ef0eedfa82d2ea1aa592845b9a6d4b02b7`.
Regeneration with this classification passes full US ROM equality at
SHA-1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`.

The final suite passes 1,071 tests (12 declared skips); metadata/progress and
whitespace checks pass. Existing function and source-unit records are preserved.
