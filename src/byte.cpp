#include "../h/byte.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include <string>

Byte::Byte(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    if (operands->size() == 1)
    {
        if ((*operands)[0].getType() == Operand::Type::LITERAL_DIR)
        {
            unsigned char *operandCode = (*operands)[0].getOpCode();
            if (*operandCode < 16)
            {
                opCode.push_back('0');
            }
            opCode.push_back(*operandCode);
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
    size = 1;
}