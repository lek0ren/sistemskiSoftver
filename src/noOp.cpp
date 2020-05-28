#include "../h/noOp.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include "../h/assembler.h"
#include <string>

NoOp::NoOp(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    if (operands->size() != 0)
    {
        std::cout << "Greska, neispravan broj operanada!" << std::endl;
        Assembler::instance().toContinue = false;
        // ne valja
    }
}