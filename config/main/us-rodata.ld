/* Reviewed main tables; see docs/evidence/main_init_2e50_integration_proposal.json
 * and docs/evidence/main_init_11fa0_integration.json.
 * Keep relocated bytes for verification while original raw data supplies ROM bytes.
 */
SECTIONS
{
    __main_rodata_saved_dot = ABSOLUTE(.);
    .main_rodata_init_2e50 0x8002C080 (INFO) : SUBALIGN(4)
    {
        *init_2E50.o(.rodata)
    }
    .main_rodata_init_11fa0 0x8002C410 (INFO) : SUBALIGN(4)
    {
        *init_11FA0.o(.rodata)
    }
    . = __main_rodata_saved_dot;
}
ASSERT(SIZEOF(.main_rodata_init_2e50) == 0 || SIZEOF(.main_rodata_init_2e50) == 0x20,
       "main queue-thread switch table extent changed")
ASSERT(SIZEOF(.main_rodata_init_11fa0) == 0 || SIZEOF(.main_rodata_init_11fa0) == 0x40,
       "main selector switch table and literal pool extent changed")
