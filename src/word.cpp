#include "../h/word.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include <string>

Word::Word(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    if (operands->size() == 2)
    {
        if ((*operands)[0].getType() == Operand::Type::LITERAL_DIR)
        {
            unsigned char *operandCode = (*operands)[0].getOpCode();
            if ((*operands)[0].getSize() == 1)
            {
                opCode.push_back(operandCode[0]);
                opCode.push_back('0');
                opCode.push_back('0');
                opCode.push_back('0');
            }
            else if ((*operands)[0].getSize() == 2)
            {
                opCode.push_back(operandCode[1]);
                opCode.push_back(operandCode[0]);
                opCode.push_back('0');
                opCode.push_back('0');
            }
            else
            {
                opCode.push_back(operandCode[2]);
                opCode.push_back(operandCode[1]);
                opCode.push_back(operandCode[0]);
                opCode.push_back('0');
            }
        }
    }
    else if (operands->size() > 2)
    {
        //lista operanada, relokacija
    }
    else
    {
        // ne valja
    }
    size = 2;
}