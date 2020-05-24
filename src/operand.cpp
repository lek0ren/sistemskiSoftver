#include "../h/operand.h"
#include <regex>
#include "../h/regexes.h"

Operand::Operand(std::string name)
{
    std::smatch m;
    if (std::regex_search(name, m, reg_jmpInstr))
    {
        }
}
