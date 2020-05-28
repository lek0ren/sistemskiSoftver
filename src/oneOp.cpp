#include "../h/oneOp.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include "../h/assembler.h"
#include <string>

OneOp::OneOp(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    if (operands->size() == 1)
    {
        if ((*operands)[0].getType() == Operand::Type::JMP_PC_RELATIVE || (*operands)[0].getType() == Operand::Type::JMP_REG_DIR || (*operands)[0].getType() == Operand::Type::JMP_REG_IND || (*operands)[0].getType() == Operand::Type::JMP_SYMBOL_REG_OFF || (*operands)[0].getType() == Operand::Type::JMP_LITERAL_REG_OFF || (*operands)[0].getType() == Operand::Type::JMP_SYMBOL_DIR || (*operands)[0].getType() == Operand::Type::JMP_LITERAL_IMM)
        {

            std::cout << "Greska, neispravan tip operanda! " << (int)(*operands)[0].getType() << std::endl;
            Assembler::instance().toContinue = false;
        }
    }
    else
    {
        std::cout << "Greska, neispravan broj operanada!" << std::endl;
        Assembler::instance().toContinue = false;
        // ne valja
    }
}