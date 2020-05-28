#include "../h/skip.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include <string>

Skip::Skip(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    opCode.clear();
    if (operands->size() == 1)
    {
        if ((*operands)[0].getType() == Operand::Type::LITERAL_DIR)
        {
            int operandCode = stoi((*operands)[0].getName());
            size = operandCode;
            for (int i = operandCode; i > 0; i--)
                opCode.push_back(0);
        } // proveriti ako se dobije jedan simbol// relokacija
    }
    else if (operands->size() >= 2)
    {
        //lista operanada, relokacija
    }
    else
    {
        // ne valja
    }
}