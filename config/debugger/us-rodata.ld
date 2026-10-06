/* Reviewed external debugger table; see docs/evidence/debugger/debugger_printf_rodata.md.
 * Consume this input before the generated full-ROM script. INFO retains linked
 * bytes for verification; the unchanged raw debugger data supplies runtime bytes.
 */
SECTIONS
{
    __debugger_rodata_saved_dot = ABSOLUTE(.);
    .debugger_rodata_1ad0 0x1600487C (INFO) : SUBALIGN(4)
    {
        *debugger_1AD0.o(.rodata)
    }
    . = __debugger_rodata_saved_dot;
}
ASSERT(SIZEOF(.debugger_rodata_1ad0) == 0xD0,
       "debugger formatter rodata extent changed")
