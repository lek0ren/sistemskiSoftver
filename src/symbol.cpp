#include "../h/symbol.h"
#include "../h/section.h"
#include "../h/assembler.h"
#include "../h/util.h"
#include <iostream>

std::ostream &operator<<(std::ostream &output, const Symbol &s)
{
    output << std::dec;
    output << std::left << std::setw(20) << std::setfill(' ') << s.getName() << (s.section < 0 ? 0 : s.section) << "\t|  " << s.offset << "\t|  " << (s.local ? "l" : "g") << "\t|  " << s.num << "\t|  " << s.defined << "\t|  ";
    /* for (auto f : *(s.flink))
    {
        output << f.patch << " ";
    }*/
    output << std::endl;
    return output;
}

Symbol::Symbol(std::string name, int off, int &s)
{
    std::smatch match_name;
    std::regex_match(name, match_name, reg_labelWout);
    this->name = match_name.str(1);
    offset = off;
    section = s;
    this->num = 0;
    defined = 0;
    flink = std::make_shared<std::vector<ST_forwardref>>();
    local = true;
}

int &Symbol::getNumber()
{
    return num;
}

bool Symbol::getDefined()
{
    return defined != 0;
}

std::string Symbol::getName() const
{
    return name;
}

void Symbol::setDefined()
{
    defined = 1;
}

void Symbol::setDefined(int i)
{
    defined = 2;
}

void Symbol::setNumber(int num)
{
    if (section == -1)
    {
        section = num;
    }
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
    return section;
}

void Symbol::setOffset(int off)
{
    offset = off;
}

void Symbol::setName(std::string name)
{
    this->name = name;
}

void Symbol::setSection(int s)
{
    section = s;
}

void Symbol::addPatch(int p, bool rel, bool twoByte)
{
    // obratiti paznju ako je bila instrukcija skoka da moze da se sabira vrednost
    std::shared_ptr<ST_forwardref> ref = std::make_shared<ST_forwardref>();
    ref->patch = p;
    ref->rel = rel;
    ref->twoByte = twoByte;
    ref->section = Assembler::instance().getCurrentSection();
    flink->push_back(*ref);
    std::cout << "dodat patch u " << name << " i velicina je " << flink->size() << '\n';
}

void Symbol::setApsRelocatable()
{
    apsRelocatable = true;
}

bool Symbol::getApsRelocatable()
{
    return apsRelocatable;
}