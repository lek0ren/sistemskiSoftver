#include "../h/section.h"
#include "../h/util.h"

Section::Section(std::string name, int off, int &s) : Symbol(name, off, s)
{
    size = 0;
    code = std::make_shared<std::vector<unsigned char>>();
    relocations = std::make_shared<std::vector<std::shared_ptr<Relocation>>>();
}

void Section::appendCode(std::vector<unsigned char> opCode)
{
    for (auto c : opCode)
    {
        code->push_back(c);
    }
}

std::ostream &operator<<(std::ostream &output, const Section &s)
{
    output << s.name << '\t' << s.size << '\t' << std::endl;
    for (auto code : *(s.code))
    {
        output << hex(code) << " ";
    }
    std::cout << std::endl;
    return output;
}

void Section::addRelocation(int offset, Relocation::Type type, int &value)
{
    relocations->push_back(std::make_shared<Relocation>(offset, type, &value));
}

std::shared_ptr<std::vector<std::shared_ptr<Relocation>>> Section::getRelTable()
{
    return relocations;
}

void Section::setToGlobal()
{
    local = false;
}