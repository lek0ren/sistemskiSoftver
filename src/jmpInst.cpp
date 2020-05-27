#include "../h/jmpInst.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include "../h/assembler.h"
#include <string>

JmpInst::JmpInst(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    if (operands->size() == 1)
    {
        if ((*operands)[0].getType() == Operand::Type::LITERAL_DIR || (*operands)[0].getType() == Operand::Type::PC_RELATIVE || (*operands)[0].getType() == Operand::Type::REG_DIR || (*operands)[0].getType() == Operand::Type::REG_IND || (*operands)[0].getType() == Operand::Type::SYMBOL_DIR || (*operands)[0].getType() == Operand::Type::SYMBOL_REG_OFF)
        {
            Assembler::instance().toContinue = false;
            //ispis greske
        }
    }
    else
    {
        Assembler::instance().toContinue = false;
        // ne valja
    }
}