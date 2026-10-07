# B1B0 literal-pool integration

US ROM SHA1 4cbadd3c4e0729dec46af64ad018050eada4f47a verified against config/roms.json and size.

Current full mixed object .rodata is 32 bytes, alignment16, flags2, and equals ROM 0x2C220..0x2C240 byte-for-byte including trailing zero word. SHA256 76a3a9dd9215a4e3ee3e9603efa0b6fa98e48f718d47170c931ae857b27e2092.

Raw BCBC references six sequential floats at 0x8002C220..234; matched C7E8 references 0x8002C238. Both are members of the existing reviewed init_B1B0 unit. The 21 symbolic mentions in reference/us/asm comprise 14 instruction HI/LO references in B1B0.s and seven storage labels in data/2BE20.data.s. This is a bounded symbolic-reference check, not proof excluding all computed pointers. Next named storage at0x8002C240 is referenced by EB00/11EB8, outside this unit.

The user approved this shared manifest integration on 2026-10-06. config/main/private-data.json records the complete pool; the existing verifier consumes it with no tool/ASM/flag changes. No individual constant relocation or discarded storage is proposed.

Required acceptance: full-span BCBC finish with current mixed-layout gate; independent same-unit C7E8 recheck; clean verify-batch and full-ROM proof. This storage evidence alone does not establish a C match.

Raw reference rows:

reference/us/asm/B1B0.s: /* BD2C 8000BD2C 3C018003 */  lui        $at, %hi(D_8002C220)
reference/us/asm/B1B0.s: /* BD30 8000BD30 C426C220 */  lwc1       $ft1, %lo(D_8002C220)($at)
reference/us/asm/B1B0.s: /* BD38 8000BD38 3C018003 */  lui        $at, %hi(D_8002C224)
reference/us/asm/B1B0.s: /* BD3C 8000BD3C C430C224 */  lwc1       $ft4, %lo(D_8002C224)($at)
reference/us/asm/B1B0.s: /* BD70 8000BD70 3C018003 */  lui        $at, %hi(D_8002C228)
reference/us/asm/B1B0.s: /* BD74 8000BD74 C432C228 */  lwc1       $ft5, %lo(D_8002C228)($at)
reference/us/asm/B1B0.s: /* BD78 8000BD78 3C018003 */  lui        $at, %hi(D_8002C22C)
reference/us/asm/B1B0.s: /* BD7C 8000BD7C C426C22C */  lwc1       $ft1, %lo(D_8002C22C)($at)
reference/us/asm/B1B0.s: /* BE40 8000BE40 3C018003 */  lui        $at, %hi(D_8002C230)
reference/us/asm/B1B0.s: /* BE44 8000BE44 C42CC230 */  lwc1       $fa0, %lo(D_8002C230)($at)
reference/us/asm/B1B0.s: /* BE4C 8000BE4C 3C018003 */  lui        $at, %hi(D_8002C234)
reference/us/asm/B1B0.s: /* BE68 8000BE68 C432C234 */  lwc1       $ft5, %lo(D_8002C234)($at)
reference/us/asm/B1B0.s: /* C874 8000C874 3C018003 */  lui        $at, %hi(D_8002C238)
reference/us/asm/B1B0.s: /* C894 8000C894 C432C238 */  lwc1       $ft5, %lo(D_8002C238)($at)
reference/us/asm/data/2BE20.data.s: dlabel D_8002C220
reference/us/asm/data/2BE20.data.s: dlabel D_8002C224
reference/us/asm/data/2BE20.data.s: dlabel D_8002C228
reference/us/asm/data/2BE20.data.s: dlabel D_8002C22C
reference/us/asm/data/2BE20.data.s: dlabel D_8002C230
reference/us/asm/data/2BE20.data.s: dlabel D_8002C234
reference/us/asm/data/2BE20.data.s: dlabel D_8002C238

Validation: unchanged BCBC C body passed full 676-byte `CURRENT (0)` in
attempt `b63577caa7bd44fb9bae0b0f62973de6`. Independent C7E8 passed its
full 332-byte span in `8736af5634e14ad3acc55d564df6bf60`. Both passed
reviewed mixed-unit layout, progress and whitespace gates. Clean batch
`init-20261006/batch-02.log` returned `BATCH_COMPLETE`, with exact US ROM
and 1,928 successful tests (41 skipped). The focused linked proofs validate
the actual mixed-object pool at its reviewed address against ROM. This unit
remains partially matched and is not yet integrated into the full build;
the clean ROM build continues to use its registered assembly source.
Whole-unit C integration and its private-data build check remain required
when the remaining unit functions match.
