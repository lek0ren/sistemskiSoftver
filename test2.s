.global l3
.extern l4
.equ simbol, l1 + 4 - 6
.section data:
    mov l1(%pc), 5
    .byte labela, l1, l3, l4
.section text:
    push (%r2)
   l1:.byte 150
    l3:.word l3, 20
labela:
.end