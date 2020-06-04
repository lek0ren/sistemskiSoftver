#include "../h/twoOp.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include <string>
#include <iostream>
#include "../h/assembler.h"
#include "../h/symTable.h"

TwoOp::TwoOp(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    if (operands->size() == 2)
    {
        for (int i = 0; i < operands->size(); i++)
        {
            int firstOperandOffset = i == 0 ? 0 : (*operands)[1].getSize();
            Operand::Type type = (*operands)[i].getType();
            if (type == Operand::Type::JMP_PC_RELATIVE || (*operands)[i].getType() == Operand::Type::JMP_REG_DIR || (*operands)[i].getType() == Operand::Type::JMP_REG_IND || (*operands)[i].getType() == Operand::Type::JMP_SYMBOL_REG_OFF || (*operands)[i].getType() == Operand::Type::JMP_LITERAL_REG_OFF || (*operands)[i].getType() == Operand::Type::JMP_SYMBOL_DIR || (*operands)[i].getType() == Operand::Type::JMP_LITERAL_IMM)
            {

                std::cout << "Greska, neispravan tip operanda! " << (int)(*operands)[i].getType() << std::endl;
                Assembler::instance().toContinue = false;
            }
            else if (type == Operand::Type::SYMBOL_DIR || type == Operand::Type::SYMBOL_IMM || type == Operand::Type::SYMBOL_REG_OFF || type == Operand::Type::PC_RELATIVE || type == Operand::Type::JMP_SYMBOL_IMM)
            { // check whether is correct type
                std::cout << "Created relocation for " << (*operands)[i].getName() << std::endl;
                std::shared_ptr<Symbol> sym = SymTable::instance().getSymbol((*operands)[i].getSymbolIfExists());
                std::shared_ptr<Section> currSection = Assembler::instance().getCurrentSection();
                int symPosition = Assembler::instance().getLocationCounter() + firstOperandOffset + 2;
                if (sym)
                {
                    if (type == Operand::Type::PC_RELATIVE)
                    {
                        int toRemove = i == 0 ? (*operands)[1].getSize() : 0;
                        toRemove += 2;
                        std::cout << "oper 1 " << toRemove << std::endl;
                        //proveri da li moze pc relative i sta da se radi tu
                        if (sym->getLocal())
                        {

                            currSection->addRelocation(symPosition, Relocation::Type::R_16_PC, sym->getSection());
                            if (!sym->getDefined())
                            {
                                sym->addPatch(symPosition, true);
                            }
                            opCode.at(firstOperandOffset + 3) = (sym->getOffset() - toRemove) >> 8;
                            opCode.at(firstOperandOffset + 2) = (sym->getOffset() - toRemove) & 0xFF;
                        }
                        else
                        {
                            currSection->addRelocation(symPosition, Relocation::Type::R_16_PC, sym->getNumber());
                            if (!sym->getDefined())
                            {
                                sym->addPatch(symPosition, true);
                            }
                            opCode.at(firstOperandOffset + 3) = (sym->getOffset() - toRemove) >> 8;
                            opCode.at(firstOperandOffset + 2) = (sym->getOffset() - toRemove) & 0xFF;
                        }
                    }
                    else
                    {
                        if (sym->getLocal())
                        {
                            currSection->addRelocation(symPosition, Relocation::Type::R_16, sym->getSection());
                            if (!sym->getDefined())
                            {
                                sym->addPatch(symPosition);
                            }
                            opCode.at(firstOperandOffset + 3) = sym->getOffset() >> 8;
                            opCode.at(firstOperandOffset + 2) = sym->getOffset() & 0xFF;
                        }
                        else
                        {
                            currSection->addRelocation(symPosition, Relocation::Type::R_16, sym->getNumber());
                            if (!sym->getDefined())
                            {
                                sym->addPatch(symPosition);
                            }
                            opCode.at(firstOperandOffset + 3) = sym->getOffset() >> 8;
                            opCode.at(firstOperandOffset + 2) = sym->getOffset() & 0xFF;
                        }
                    }
                }
                else
                {
                    std::cout << "Greska u izvrsavanju\n";
                    Assembler::instance().toContinue = false;
                }
            }
        }
    }
    else
    {
        std::cout << "Greska, neispravan broj operanada!" << std::endl;
        Assembler::instance().toContinue = false;
        // ne valja
    }
}