# Reconciled named US singleton at `0xEB20`

Evidence kind: `structural_analysis`. The existing named raw split
`game_3BFD0` and the independent US function inventory agree that
`func_1500EB20` occupies the complete range `0xEB20:0xEB30`. The source path
`src/game/game_3BFD0.c` preserves that established identity.

The function is an exact 16-byte return stub. Its `jr ra` and delay-slot `nop`
are followed by two alignment `nop` instructions before the next reviewed
source unit begins at `0xEB30`. The range SHA-1 is
`d7f1995b974090cca53d1bc6d536259a7fbfcdb3`.

The function already has zero-difference US evidence in the canonical function
inventory. Assigning the same range to its existing source file records the
missing source-unit boundary without replacing the converted C or inventing a
generic source identity.
