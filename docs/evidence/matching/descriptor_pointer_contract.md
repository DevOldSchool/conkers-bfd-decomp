# Repeated descriptor pointer contract (US)

`func_15189FF0` takes a descriptor pointer as its first argument. Its independent
raw body forwards incoming a0 unchanged to a2 at `1518A004`, then calls
`func_151407D0`. That callee saves a2 at `151407E0`, reloads it into a0 at
`151407E8`, reads pointer+0x40 at `151407F4`, and writes pointer+1 and
pointer+0x40 at `151407F8` and `15140804`. References are
`reference/game/us/asm/189FF0.s` and `1407D0.s`.

The source-local declaration in `game_179F30.c` used `s32` for that pointer.
Correcting it to `void *` and removing integer casts is distinct from the
previous address-spelling, scoped aggregate and union experiments for the
800-byte `func_1514D64C` candidate.

The candidate improved from 7859 to 7239 with the pointer contract, to 7053
when its redundant second-setup pointer was removed, and to 5162 when the
actual allocation result was named before the setup aggregate. The original
frame size and most aggregate offsets were recovered. Initializer scheduling,
register allocation and remaining spill/control differences persist. It remains
deferred with original assembly active, and adds no matched bytes.

The declaration also serves already-matched `func_1514E00C`, `func_1514E194`
and `func_1514E31C`. Their redundant integer casts were removed; all three
independently rechecked at `CURRENT (0)`. Their clean regression batch returned
`BATCH_COMPLETE`, with the complete US game-code image and mapped external
rodata byte-identical, 1,068 tests passing, 12 skipped, and metadata, progress
and whitespace gates passing. Those three are rechecks, not new matches.
