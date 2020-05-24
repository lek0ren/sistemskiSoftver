#include "../h/section.h"

Section::Section(std::string name, int off, int &s) : Symbol(name, off, s)
{
    size = 0;
    code = std::make_shared<std::vector<std::string>>();
}

void Section::appendCode(std::vector<std::string> opCode)
{
    for (auto c : opCode)
    {
        code->push_back(c);
    }
}
