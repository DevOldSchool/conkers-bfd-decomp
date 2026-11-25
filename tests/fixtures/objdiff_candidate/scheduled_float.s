.set noreorder
.set noat
.text
.globl scheduled_float
.ent scheduled_float
scheduled_float:
    lui $1, %hi(.rodata)
    lw $8, 0($sp)
    mtc1 $8, $f4
    add.s $f6, $f4, $f4
    lwc1 $f2, %lo(.rodata)($1)
    lui $1, %hi(.rodata + 8)
    swc1 $f2, 4($sp)
    ldc1 $f0, %lo(.rodata + 8)($1)
    jr $ra
    nop
.end scheduled_float
.section .rodata, "a"
.float 1.0
.word 0
.double 2.0
