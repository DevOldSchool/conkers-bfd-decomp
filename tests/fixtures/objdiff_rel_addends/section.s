# Same destination using a section-relative R_MIPS_32 addend.
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
    .word .text + 4
.size table, . - table
