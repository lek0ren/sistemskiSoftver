.global a
.extern b, d
.section data:
g: .skip 10
a: .word 300

.section text:
push $5
push $5
pop simbol
push 1000(%r6)
jmp *a(%pc)
add $2,a
add $2,c
jmp *c(%r7)
call *labela
c: .byte 2
simbol: .word 9
labela: .skip 4
.section .bssa:

.end
