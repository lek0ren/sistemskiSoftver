#include "../h/word.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include <string>

Word::Word(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    // opCode = std::vector<unsigned char>();
    if (operands->size() == 1)
    {
        if ((*operands)[0].getType() == Operand::Type::LITERAL_DIR)
        {
            opCode.clear();
            int operandCode = stoi((*operands)[0].getName());
            opCode.push_back(operandCode & 0xFF);
            opCode.push_back((operandCode >> 8) & 0xFF);
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