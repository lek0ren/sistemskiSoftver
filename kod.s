.global a
.extern b, d

.section text:
.equ a , b
mov eax,b
iret
halt
push $56
pop simbol
pop %r5
push (%r7)
pop %r5l
pop %r5h
push (%r2)
jmp *%r2
call labela
jmp 54
jeq *54
jne *(%r6)
jgt *simbol(%r2)
pushw %r1

           c: .byte 2

.section data:
a: .long 8

.end
