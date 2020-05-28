.global a
.extern b, d
.section data:
g: .skip 10
a: .word 300

.section text:
.equ a , b
iret
halt
push $56
pop $simbol
pop %r5
push 1000(%r6)
pop %r5l
pop %r5h
push (%r2)
jmp *%r2l
call labela
jmp 256
add a, (%r2)
jeq *54
jne *(%r6)
jgt *simbol(%r2)
pushw %r1

           c: .byte 2
           simbol: .word 9

.end
