.global l3, data_reloc
.extern l4, l5

.equ const,  4 - 6 - 8 + 10 + 8
.equ text_reloc, 10 + l1
.equ data_reloc, 10 + labela
.equ apsolut, l1 - l3
.equ b, 5 - 30

.section data:
    mov l1(%pc), 5
    mov 5, l1(%pc)
    jmp *apsolut(%pc)
    movw text_reloc, (%r4)
    .byte labela, l1, l3, l4
    labela: .word labela, l1, l3, l4, 15, extern, apsolut
.section text:
    push (%r2)
    l1: .byte 150
    l3: .word l1, 20, data_reloc, const
    .equ extern, l4 + 4
.end

.equ a, b
.equ b, a
 .equ error, l1 + labela
  .equ extern_err, l4 - l5