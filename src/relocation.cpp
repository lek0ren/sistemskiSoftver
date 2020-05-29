#include "../h/relocation.h"
#include "../h/symbol.h"
#include "../h/symTable.h"
#include <iostream>

Relocation::Relocation(int offset_, Type type_, int &value_)
{
    offset = offset_;
    type = type_;
    value = value_;
}

std::ostream &operator<<(std::ostream &output, const Relocation &s)
{
    output << s.offset << "\t|    " << (s.type == Relocation::Type::R_64 ? "R_64" : "R_64_PC")
           << "\t|   " << s.value << std::endl;
    return output;
}
