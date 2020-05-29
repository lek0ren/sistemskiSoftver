.global a
.extern b, d
.section data:
g: .skip 10
a: .word 300

.section text:
pop $simbol
push 1000(%r6)
jmp *a(pc)
jmp *c(%r7)
call labela
   c: .byte 2
           simbol: .word 9
           labela: .skip 4

.end
