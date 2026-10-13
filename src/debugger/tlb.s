/* US debugger TLB snapshot. Maintained source, not generated disassembly.
 * Evidence and ABI: docs/evidence/debugger/us_debugger_tlb.md
 * Reads all 32 entries into EntryLo0, EntryLo1, EntryHi and PageMask arrays.
 * Clobbers at, a0-a3, t0-t4 and CP0 Index/EntryLo0/EntryLo1/EntryHi/PageMask.
 * No arguments, stack frame or return value; ra is preserved.
 * Keep the original CP0 hazard spacing and branch delay slots unchanged.
 */
.include "macro.inc"
.set noat
.set noreorder
.set gp=64
.section .text, "ax"
.balign 4

.globl func_16003650
.type func_16003650, @function
func_16003650:
    addiu   $t0, $zero, 0
    lui     $a0, %hi(D_160038AC)       /* EntryLo0[32] */
    addiu   $a0, $a0, %lo(D_160038AC)
    lui     $a1, %hi(D_1600392C)       /* EntryLo1[32] */
    addiu   $a1, $a1, %lo(D_1600392C)
    lui     $a2, %hi(D_160039AC)       /* EntryHi[32] */
    addiu   $a2, $a2, %lo(D_160039AC)
    lui     $a3, %hi(D_16003A2C)       /* PageMask[32] */
    addiu   $a3, $a3, %lo(D_16003A2C)
.Lread_entry:
    mtc0    $t0, $0                   /* Select CP0 Index. */
    nop
    nop
    tlbr                             /* Read selected TLB entry into CP0. */
    nop
    nop
    nop
    nop
    mfc0    $t1, $2                   /* EntryLo0 */
    nop
    mfc0    $t2, $3                   /* EntryLo1 */
    nop
    mfc0    $t3, $10                  /* EntryHi */
    nop
    mfc0    $t4, $5                   /* PageMask */
    nop
    sw      $t1, 0($a0)
    sw      $t2, 0($a1)
    sw      $t3, 0($a2)
    sw      $t4, 0($a3)
    addi    $t0, $t0, 1
    addi    $a0, $a0, 4
    addi    $a1, $a1, 4
    addi    $a3, $a3, 4
    addiu   $at, $zero, 32
    bne     $t0, $at, .Lread_entry
     addi   $a2, $a2, 4               /* Advance EntryHi in the delay slot. */
    jr      $ra
     nop
.size func_16003650, . - func_16003650

/* Original unit alignment: included in the 160-byte ROM proof, not the
 * 152-byte function size used for native matching progress. */
    nop
    nop
