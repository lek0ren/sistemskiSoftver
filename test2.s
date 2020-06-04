.global l3
.extern l4
.equ simbol, l1 + 4 - 6
.section data:
    mov l1(%pc), 5
    mov 5, l1(%pc)
    jmp *l1(%pc)
    movw $2, (%r4)
    .byte labela, l1, l3, l4
    .word labela, l1, l3, l4, 15
.section text:
    push (%r2)
    l1: .byte 150
    l3: .word l3, 20
    l4:
labela:
.end