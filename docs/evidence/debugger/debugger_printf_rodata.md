# Debugger Putfld external table integration

The independently checksum-validated US debugger image contains the 52-entry
Putfld switch table at VRAM `[0x1600487C, 0x1600494C)`, ROM
`[0x1A3304, 0x1A33D4)`. Its 208 bytes have SHA-1
`d1df6f79b540cfcccfc89d76dd0783f081156d03`. See the reviewed
[debugger data map](us_debugger_data_objects.json) and
[formatter provenance](../libraries/libultrare_us_xprintf_reconstruction.md).

The recovered C switch in `src/debugger/debugger_1AD0.c` emits one `0xD0`
`.rodata` section. The full registered Putfld instruction span and all 52 object
case relocations must pass the existing focused verification independently.
Neither compiler output nor this placement map establishes an original source
object boundary.

`config/debugger/us-rodata.ld` consumes this section before the generated US
full-ROM script, maps it to `0x1600487C` with `SUBALIGN(4)`, and asserts its exact
size. It restores the incoming location counter afterward so the generated
script's address-less header and boot sections retain their original placement.
Its `INFO` output retains relocated bytes in the ELF for verification and
does not add a second copy to the ROM. The existing raw debugger data remains
unchanged and supplies the bytes loaded at runtime.

Every US `raw-build` checks this non-allocated read-only section's name, address,
size, and complete relocated payload against `rom_span.debugger_image` before
reporting success. The full ROM must still compare byte for byte. Missing,
additional, differently placed, or altered table data fails verification.
The four bytes at `0x1600494C` and the double at `0x16004950` are outside the
mapped table. No extra payload or neighboring padding is accepted.

Validation on the working branch passed independent full-span `CURRENT (0)` for
Putfld, all 52 object case targets, all 208 linked table bytes, and full US ROM
equality. Clean batch verification passed 1,658 tests (11 skipped), metadata,
progress, and whitespace gates. The linked header remains at VMA `0x0` with size
`0x40`, and boot at VMA `0x40` with size `0xFC0`. The external table is non-allocated
read-only PROGBITS at the reviewed address with exact size `0xD0`.
