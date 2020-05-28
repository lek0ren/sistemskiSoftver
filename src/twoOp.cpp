#include "../h/twoOp.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include <string>
#include <iostream>
#include "../h/assembler.h"

TwoOp::TwoOp(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    if (operands->size() == 2)
    {
        if ((*operands)[0].getType() == Operand::Type::JMP_PC_RELATIVE || (*operands)[0].getType() == Operand::Type::JMP_REG_DIR || (*operands)[0].getType() == Operand::Type::JMP_REG_IND || (*operands)[0].getType() == Operand::Type::JMP_SYMBOL_REG_OFF || (*operands)[0].getType() == Operand::Type::JMP_LITERAL_REG_OFF || (*operands)[0].getType() == Operand::Type::JMP_SYMBOL_DIR || (*operands)[0].getType() == Operand::Type::JMP_LITERAL_IMM)
        {

            std::cout << "Greska, neispravan tip operanda! " << (int)(*operands)[0].getType() << std::endl;
            Assembler::instance().toContinue = false;
        }
        if ((*operands)[1].getType() == Operand::Type::JMP_PC_RELATIVE || (*operands)[1].getType() == Operand::Type::JMP_REG_DIR || (*operands)[1].getType() == Operand::Type::JMP_REG_IND || (*operands)[1].getType() == Operand::Type::JMP_SYMBOL_REG_OFF || (*operands)[1].getType() == Operand::Type::JMP_LITERAL_REG_OFF || (*operands)[1].getType() == Operand::Type::JMP_SYMBOL_DIR || (*operands)[1].getType() == Operand::Type::JMP_LITERAL_IMM)
        {

            std::cout << "Greska, neispravan tip operanda! " << (int)(*operands)[1].getType() << std::endl;
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