# Original ROM-free fixture in IDO's output shape: an anonymous switch table
# and double in .rodata, both referenced through the .rodata section symbol.
# Table words are section-plus-addend R_MIPS_32 entries, like IDO's.
.set noreorder
.set noat

.section .text
.globl dispatch
.type dispatch, @function
dispatch:
    sltiu $at, $a0, 4
    beq $at, $zero, .Ldefault
    sll $t6, $a0, 2
    lui $at, %hi(.Ltable)
    addu $at, $at, $t6
    lw $t6, %lo(.Ltable)($at)
    jr $t6
    nop
.Lcase0:
    jr $ra
    addiu $v0, $zero, 10
.Lcase1:
    jr $ra
    addiu $v0, $zero, 11
.Lcase2:
    jr $ra
    addiu $v0, $zero, 12
.Lcase3:
    jr $ra
    addiu $v0, $zero, 13
.Ldefault:
    jr $ra
    move $v0, $zero
.size dispatch, . - dispatch

.globl scale
.type scale, @function
scale:
    lui $at, %hi(.Ldouble)
    ldc1 $f4, %lo(.Ldouble)($at)
    jr $ra
    mul.d $f0, $f12, $f4
.size scale, . - scale

.section .rodata
.globl prefix
.type prefix, @object
prefix:
    .asciz "a"
.size prefix, 2
    .align 2
.Ltable:
    .word .Lcase0, .Lcase1, .Lcase2, .Lcase3
    .align 3
.Ldouble:
    .double 1e8
