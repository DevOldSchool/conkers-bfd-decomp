/* Reviewed main queue-thread switch table; see docs/evidence/data-layout/main_init_2e50_integration_proposal.json.
 * Keep relocated bytes for verification while original raw data supplies ROM bytes.
 */
SECTIONS
{
    __main_rodata_saved_dot = ABSOLUTE(.);
    .main_rodata_init_2e50 0x8002C080 (INFO) : SUBALIGN(4)
    {
        *init_2E50.o(.rodata)
    }
    . = __main_rodata_saved_dot;
}
ASSERT(SIZEOF(.main_rodata_init_2e50) == 0x20,
       "main queue-thread switch table extent changed")
