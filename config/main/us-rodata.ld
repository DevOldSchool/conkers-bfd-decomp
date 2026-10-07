/* Queue table evidence: docs/evidence/data-layout/main_init_2e50_integration_proposal.json.
 * The selector pool at ROM 0x2C410 contains five runtime-aliased switch pointers,
 * nine float literals and eight padding bytes (64 bytes total). Keep both pools
 * as non-allocated INFO so original raw data supplies ROM bytes without shifting
 * BSS. verify_main_rodata.py checks every linked byte, including padding, against
 * the checksum-validated US ROM.
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
