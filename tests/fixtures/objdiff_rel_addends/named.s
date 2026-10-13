# ROM-free example: named-label R_MIPS_32 has an encoded addend of zero.
.set noreorder
.text
.globl function
.type function, @function
function:
    nop
.globl entry
entry:
    jr $ra
    nop
.size function, . - function
.section .rodata, "a"
.globl table
.type table, @object
table:
    .word entry
.size table, . - table
