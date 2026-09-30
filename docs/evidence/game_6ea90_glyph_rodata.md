# Glyph helper switch and floating constants (US)

`func_150415E0` handles special glyph dimensions, scale and flags. Its existing
reviewed source family is documented in
[the glyph pipeline boundary evidence](game_raw_record_glyph_emitter_groups.md).
This mapping does not change that boundary or claim an original filename.

The independent US raw dispatch at `0x15041600` bounds the switch to 19 entries,
for selectors `0xA8` through `0xBA`. The unchanged HI16/LO16 pair at
`0x15041610/0x15041618` addresses the table at `0x80098AB0`. Its 76 bytes are
followed immediately by five four-byte floating literals, consumed at
`0x80098AFC`, `0x80098B00`, `0x80098B04`, `0x80098B08` and `0x80098B0C`.
The corresponding C literals are `3.1f`, `0.603f`, `-1.6f`, `0.2f` and `0.726f`.

The compiled `game_6EA90.o` emits a single 96-byte `.rodata` section in precisely
that order: 19 `R_MIPS_32` case relocations and the five literals, with no trailing
alignment bytes. `config/game/us-rodata.ld` assigns the section its original
runtime address as informational data and asserts its exact extent. This keeps
it out of the code-only image; the original game-data archive supplies it at
runtime. `verify_game_rodata.py` checks the complete relocated payload against
the checksum-validated US ROM during the clean integrated build.

The bounds branch schedules `swc1` in its delay slot. The candidate-time verifier
recognizes this store as not writing any GPR, including when its FPR index equals
the guard or index GPR number. Regression tests retain rejection of GPR clobbers,
an inverted branch, missing relocation evidence and incorrect case targets.
This extension leaves raw-ROM instruction verification, bounds, table extent,
relocation coverage and all case-target comparisons intact.

Focused instruction equality, complete table equality and source-unit layout
remain separate required checks. A clean batch is required before acceptance.

Validation on 2026-09-30: `func_150415E0` passed authoritative `CURRENT (0)`
with source-unit layout preserved. The clean batch verified the complete
2,072,880-byte US game-code image and this section's full 96-byte ROM payload.
All 1,068 Python tests passed (12 skipped); metadata, generated progress and
whitespace checks passed. The batch ended `BATCH_COMPLETE`.
