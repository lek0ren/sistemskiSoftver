#include "../h/word.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include <string>
#include "../h/symbol.h"
#include "../h/symTable.h"
#include "../h/assembler.h"

Word::Word(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    size = 0;
    Operand::Type type = (*operands)[0].getType();
    // opCode = std::vector<unsigned char>();
    if (operands->size() >= 1)
    {
        for (int i = 0; i < operands->size(); i++)
        {
            Operand::Type type = (*operands)[i].getType();
            if (type == Operand::Type::LITERAL_DIR)
            {
                unsigned char *operandCode = (*operands)[i].getOpCode();
                std::cout << "op 0 " << hex(operandCode[0]) << " op 1 " << hex(operandCode[1]) << " op 2 " << hex(operandCode[2]) << std::endl;
                opCode.at(2 * i) = operandCode[1];
                if (operandCode[1] < 255)
                {
                    opCode.at(2 * i) = 0;
                }
                else
                {
                    opCode.at(2 * i + 1) = operandCode[2];
                }
            }
            else if (type == Operand::Type::SYMBOL_DIR || type == Operand::Type::SYMBOL_IMM || type == Operand::Type::SYMBOL_REG_OFF || type == Operand::Type::PC_RELATIVE || type == Operand::Type::JMP_SYMBOL_IMM)
            { // check whether is correct type
                std::cout << "Created relocation for " << (*operands)[i].getName() << std::endl;
                std::shared_ptr<Symbol> sym = SymTable::instance().getSymbol((*operands)[i].getSymbolIfExists());
                std::shared_ptr<Section> currSection = Assembler::instance().getCurrentSection();
                int symPosition = Assembler::instance().getLocationCounter() + 2 * i;
                if (sym)
                {
                    if (sym->getLocal())
                    {

                        currSection->addRelocation(symPosition, Relocation::Type::R_8, currSection->getNumber());
                        if (!sym->getDefined())
                        {
                            sym->addPatch(symPosition, false, false);
                        }
                        opCode.at(2 * i) = sym->getOffset() & 0xFF;
                        opCode.at(2 * i + 1) = sym->getOffset() >> 8;
                    }
                    else
                    {
                        currSection->addRelocation(symPosition, Relocation::Type::R_8, sym->getNumber());
                        if (!sym->getDefined())
                        {
                            sym->addPatch(symPosition, false, false);
                        }
                        opCode.at(2 * i) = sym->getOffset() & 0xFF;
                        opCode.at(2 * i + 1) = sym->getOffset() >> 8;
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
            size += 2;
        }
        opCode.erase(opCode.begin() + 2 * operands->size(), opCode.end());
    }
    else
    {
        // ne valja
    }
}