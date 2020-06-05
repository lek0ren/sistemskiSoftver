#include "../h/relocation.h"
#include "../h/symbol.h"
#include "../h/symTable.h"
#include <iostream>

Relocation::Relocation(int offset_, Type type_, int *value_)
{
    offset = offset_;
    type = type_;
    value = value_;
}

std::ostream &operator<<(std::ostream &output, const Relocation &s)
{
    output << s.offset << "\t|    " << (s.type == Relocation::Type::R_16 ? "R_16" : (s.type == Relocation::Type::R_16_PC ? "R_16_PC" : "R_8"))
           << "\t|   " << (*(s.value) == -1 ? 0 : *(s.value)) << std::endl;
    return output;
}
