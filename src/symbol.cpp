#include "../h/symbol.h"
#include <iostream>

std::ostream &operator<<(std::ostream &output, const Symbol &s)
{
    output << s.getName() << std::endl;
    return output;
}

Symbol::Symbol(std::string name, int off, std::shared_ptr<Section> s)
{
    this->name = std::regex_replace(name, reg_labelWout, "$1");
    offset = off;
    section = s;
}