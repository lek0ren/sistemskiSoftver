.global a
.extern b, d
.section data:
g: .skip 10
z: .word 3
a: .word 300

.section text:
push $5
push $5
pop simbol
push 1000(%r6)
jmp *a(%pc)
add 2 , a
jmp *c(%r7)
.equ ra, a + c - simbol 
call *labela
c: .byte 2
simbol: .word 9
labela: .skip 4
.section bss:

.end