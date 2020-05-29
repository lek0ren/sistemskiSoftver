#include "../h/symbol.h"
#include "../h/section.h"
#include "../h/assembler.h"
#include <iostream>

std::ostream &operator<<(std::ostream &output, const Symbol &s)
{
    output << s.getName() << "\t|  " << *s.section << "\t|  " << s.offset << "\t|  " << (s.local ? "l" : "g") << "\t|  " << s.num << "\t|  " << s.defined << "\t|  ";
    for (auto f : *(s.flink))
    {
        std::cout << f.patch << " " << std::endl;
    }
    return output;
}

Symbol::Symbol(std::string name, int off, int &s)
{
    std::smatch match_name;
    std::regex_match(name, match_name, reg_labelWout);
    this->name = match_name.str(1);
    offset = off;
    section = s == -1 ? &num : &s;
    this->num = 0;
    defined = false;
    flink = std::make_shared<std::vector<ST_forwardref>>();
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

int Symbol::getOffset()
{
    return offset;
}

std::string Symbol::getName()
{
    return name;
}

bool Symbol::getLocal()
{
    return local;
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

void Symbol::addPatch(int p, bool rel)
{

    // obratiti paznju ako je bila instrukcija skoka da moze da se sabira vrednost
    ST_forwardref ref;
    ref.patch = p;
    ref.rel = rel;
    ref.section = Assembler::instance().getCurrentSection();
    flink->push_back(ref);
}