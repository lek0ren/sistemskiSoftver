#include "../h/symbol.h"
#include "../h/section.h"
#include <iostream>

std::ostream &operator<<(std::ostream &output, const Symbol &s)
{
    output << s.getName() << "\t" << *s.section << "\t" << s.offset << "\t" << (s.local ? "l" : "g") << "\t" << s.num << "\t" << s.defined << std::endl;
    return output;
}

Symbol::Symbol(std::string name, int off, int &s)
{
    std::smatch match_name;
    std::regex_match(name, match_name, reg_labelWout);
    this->name = match_name.str(1);
    offset = off;
    std::cout << "Section " << s << std::endl;
    section = s == -1 ? &num : &s;
    this->num = 0;
    defined = false;
    flink = nullptr;
    local = true;
}

int &Symbol::getNumber()
{
    return num;
}

bool Symbol::getDefined()
{
    return defined;
}

std::string Symbol::getName() const
{
    return name;
}

void Symbol::setDefined()
{
    defined = true;
}

void Symbol::setNumber(int num)
{

    this->num = num;
}

void Symbol::setToGlobal()
{
    local = false;
}

int Symbol::getOffset()
{
    return offset;
}

std::string Symbol::getName()
{
    return name;
}

int &Symbol::getSection()
{
    return *section;
}

void Symbol::setOffset(int off)
{
    offset = off;
}

void Symbol::setName(std::string name)
{
    this->name = name;
}

void Symbol::setSection(int &s)
{
    *section = s;
}