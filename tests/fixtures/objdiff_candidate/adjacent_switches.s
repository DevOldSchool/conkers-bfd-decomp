# ROM-free IDO shape with empty delay slots and adjacent bounded tables.
.set noreorder
.set noat
.text
.globl dispatch_a
.type dispatch_a,@function
dispatch_a:
 sltiu $at,$a0,2
 beq $at,$zero,.Ldefault_a
 nop
 sll $t6,$a0,2
 lui $at,%hi(.Ltable_a)
 addu $at,$at,$t6
 lw $t6,%lo(.Ltable_a)($at)
 jr $t6
 nop
.Lcase_a0:
 jr $ra
 addiu $v0,$zero,1
.Lcase_a1:
 jr $ra
 addiu $v0,$zero,2
.Ldefault_a:
 jr $ra
 move $v0,$zero
.size dispatch_a,.-dispatch_a
.globl dispatch_b
.type dispatch_b,@function
dispatch_b:
 sltiu $at,$a1,3
 beq $at,$zero,.Ldefault_b
 nop
 sll $t7,$a1,2
 lui $at,%hi(.Ltable_b)
 addu $at,$at,$t7
 lw $t7,%lo(.Ltable_b)($at)
 jr $t7
 nop
.Lcase_b0:
 jr $ra
 addiu $v0,$zero,3
.Lcase_b1:
 jr $ra
 addiu $v0,$zero,4
.Lcase_b2:
 jr $ra
 addiu $v0,$zero,5
.Ldefault_b:
 jr $ra
 move $v0,$zero
.size dispatch_b,.-dispatch_b
.section .rodata
.Ltable_a:
 .word .Lcase_a0,.Lcase_a1
.Ltable_b:
 .word .Lcase_b0,.Lcase_b1,.Lcase_b2
.bss
.globl owned_state
.type owned_state,@object
owned_state:
 .space 4
.size owned_state,4
.globl unused_sdk_declaration
