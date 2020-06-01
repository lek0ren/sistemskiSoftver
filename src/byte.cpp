#include "../h/byte.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include <string>
#include <iostream>
#include "../h/symbol.h"
#include "../h/symTable.h"
#include "../h/assembler.h"

Byte::Byte(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    size = 0;
    std::cout << ".byte direktiva " << operands->size() << std::endl;
    if (operands->size() >= 1)
    {
        for (int i = 0; i < operands->size(); i++)
        {
            Operand::Type type = (*operands)[i].getType();
            if (type == Operand::Type::LITERAL_DIR)
            {
                unsigned char *operandCode = (*operands)[i].getOpCode();
                /*if (*operandCode < 16)
                {
                    opCode.push_back('0');
                }*/
                opCode.at(i) = operandCode[1];
            }
            else if (type == Operand::Type::SYMBOL_DIR || type == Operand::Type::SYMBOL_IMM || type == Operand::Type::SYMBOL_REG_OFF || type == Operand::Type::PC_RELATIVE || type == Operand::Type::JMP_SYMBOL_IMM)
            { // check whether is correct type
                std::cout << "Created relocation for " << (*operands)[i].getName() << std::endl;
                std::shared_ptr<Symbol> sym = SymTable::instance().getSymbol((*operands)[i].getSymbolIfExists());
                std::shared_ptr<Section> currSection = Assembler::instance().getCurrentSection();
                int symPosition = Assembler::instance().getLocationCounter() + i;
                if (sym)
                {
                    if (sym->getLocal())
                    {

                        currSection->addRelocation(symPosition, Relocation::Type::R_8, currSection->getNumber());
                        if (!sym->getDefined())
                        {
                            sym->addPatch(symPosition, false, false);
                        }
                        opCode.at(i) = sym->getOffset() & 0xFF;
                    }
                    else
                    {
                        currSection->addRelocation(symPosition, Relocation::Type::R_8, sym->getNumber());
                        if (!sym->getDefined())
                        {
                            sym->addPatch(symPosition, false, false);
                        }
                        opCode.at(i) = sym->getOffset() & 0xFF;
                    }
                }
                else
                {
                    std::cout << "Greska u izvrsavanju\n";
                    Assembler::instance().toContinue = false;
                }
            }
            else
            {
                // ne valja
            }
            size += 1;
        }
        opCode.erase(opCode.begin() + operands->size(), opCode.end());
    }
}