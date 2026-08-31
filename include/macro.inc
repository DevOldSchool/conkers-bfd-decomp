.macro glabel symbol
    .globl \symbol
\symbol:
.endm

.macro jlabel symbol
\symbol:
.endm

.macro dlabel symbol
\symbol:
.endm
