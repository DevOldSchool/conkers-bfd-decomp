# Original ROM-free first-argument string ABI fixture; no target/ROM names.
.set noreorder
.set noat
.text
.globl string_calls
.type string_calls,@function
string_calls:
 lui $a0,%hi(.Lfirst)
 addiu $a0,$a0,%lo(.Lfirst)
 lbu $t1,0($s0)
 or $a1,$t1,$zero
 jal osSyncPrintf
 or $a2,$t1,$zero
 lui $a0,%hi(.Lsecond)
 addiu $a0,$a0,%lo(.Lsecond)
 jal osSyncPrintf
 lbu $a1,0($s0)
 jr $ra
 nop
.size string_calls,.-string_calls
.section .rodata
.Lfirst:
 .asciz "first %d\n"
 .align 2
.Lsecond:
 .asciz "second"
