/* SDK-owned VI storage backed by the existing main BSS allocation.
 * See docs/evidence/data-layout/main_init_vi_layout.md. INFO prevents duplicate allocation.
 */
SECTIONS
{
    __main_vi_saved_dot = ABSOLUTE(.);
    .main_vi_bss 0x80036DD0 (INFO) : SUBALIGN(16)
    {
        *init_34E0.o(.bss)
    }
    . = __main_vi_saved_dot;
}
ASSERT(SIZEOF(.main_vi_bss) == 0x1070,
       "VI private BSS extent changed")
