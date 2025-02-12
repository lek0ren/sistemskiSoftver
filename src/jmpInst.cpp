#include "../h/jmpInst.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include "../h/assembler.h"
#include "../h/symTable.h"
#include <string>

JmpInst::JmpInst(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    if (operands->size() == 1)
    {
        if ((*operands)[0].getType() == Operand::Type::PC_RELATIVE || (*operands)[0].getType() == Operand::Type::REG_DIR || (*operands)[0].getType() == Operand::Type::REG_IND || (*operands)[0].getType() == Operand::Type::SYMBOL_REG_OFF)
        {

            std::cout << "Greska, neispravan tip operanda! " << (int)(*operands)[0].getType() << std::endl;
            Assembler::instance().toContinue = false;
        }
        else
        {

            if ((*operands)[0].getType() == Operand::Type::JMP_SYMBOL_DIR || (*operands)[0].getType() == Operand::Type::JMP_SYMBOL_IMM || (*operands)[0].getType() == Operand::Type::JMP_SYMBOL_REG_OFF || (*operands)[0].getType() == Operand::Type::SYMBOL_DIR || (*operands)[0].getType() == Operand::Type::JMP_PC_RELATIVE)
            {
                std::cout << "Created relocation for " << (*operands)[0].getName() << std::endl;
                std::shared_ptr<Symbol> sym = SymTable::instance().getSymbol((*operands)[0].getSymbolIfExists());
                std::shared_ptr<Section> currSection = Assembler::instance().getCurrentSection();
                int symPosition = Assembler::instance().getLocationCounter() + 2;
                if (sym)
                {
                    if ((*operands)[0].getType() == Operand::Type::JMP_PC_RELATIVE)
                    {
                        std::cout << "Created pc rel relocation for " << (*operands)[0].getName() << std::endl;
                        if (sym->getLocal())
                        {

                            if (!sym->getDefined())
                            {
                                sym->addPatch(symPosition, true);
                                currSection->addPendingRelocation(sym, symPosition, Relocation::Type::R_16_PC, sym->getSection());
                                std::cout << "Created pc rel pending relocation for " << (*operands)[0].getName() << std::endl;
                            }
                            else
                            {
                                currSection->addRelocation(symPosition, Relocation::Type::R_16_PC, sym->getSection());
                            }
                            opCode.at(3) = (sym->getOffset() - 2) >> 8;
                            opCode.at(2) = (sym->getOffset() - 2) & 0xFF;
                        }
                        else
                        {
                            if (!sym->getDefined())
                            {
                                sym->addPatch(symPosition, true);
                                currSection->addPendingRelocation(sym, symPosition, Relocation::Type::R_16_PC, sym->getNumber());
                            }
                            else
                            {
                                currSection->addRelocation(symPosition, Relocation::Type::R_16_PC, sym->getNumber());
                            }
                            opCode.at(3) = (-2) >> 8;
                            opCode.at(2) = (-2) & 0xFF;
                        }
                    }
                    else
                    {
                        if (!sym->getDefined())
                        {
                            if (sym->getLocal())
                            {
                                currSection->addPendingRelocation(sym, symPosition, Relocation::Type::R_16, sym->getSection());
                            }
                            else
                            {
                                currSection->addPendingRelocation(sym, symPosition, Relocation::Type::R_16, sym->getNumber());
                            }
                            sym->addPatch(symPosition);
                        }
                        else
                        {
                            if (sym->getLocal())
                            {
                                currSection->addRelocation(symPosition, Relocation::Type::R_16, sym->getSection());
                            }
                            else
                            {
                                currSection->addRelocation(symPosition, Relocation::Type::R_16, sym->getNumber());
                            }
                        }
                        opCode.at(3) = sym->getOffset() >> 8;
                        opCode.at(2) = sym->getOffset() & 0xFF;
                    }
                }
                else
                {
                    // greska u izvrasavanju
                }
            }
        }
    }
    else
    {
        std::cout << "Greska, neispravan broj operanada" << operands->size() << " !" << std::endl;
        Assembler::instance().toContinue = false;
        // ne valja
    }
}