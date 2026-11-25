# Original ROM-free fixture of IDO's bounded stack-initializer copy.
.set noreorder
.set noat
.text
.globl initialize
.type initialize, @function
initialize:
    lui $t6, %hi(.Linitializer)
    addiu $t6, $t6, %lo(.Linitializer)
    addiu $t7, $t6, 24
    addiu $t8, $sp, 32
.Lcopy:
    lw $t9, 0($t6)
    addiu $t6, $t6, 12
    addiu $t8, $t8, 12
    sw $t9, -12($t8)
    lw $t9, -8($t6)
    sw $t9, -8($t8)
    lw $t9, -4($t6)
    bne $t6, $t7, .Lcopy
    sw $t9, -4($t8)
    lw $t9, 0($t6)
    sw $t9, 0($t8)
    lui $at, %hi(.Lfloat)
    lwc1 $f4, %lo(.Lfloat)($at)
    jr $ra
    nop
.size initialize, . - initialize
.section .rodata
.globl anchor
.type anchor, @object
anchor:
    .word 42
.size anchor, . - anchor
.Linitializer:
    .word 11, 22, 33, 44, 55, 66, 77
.Lfloat:
    .float 0.25
