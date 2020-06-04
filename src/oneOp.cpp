#include "../h/oneOp.h"
#include "../h/instruction.h"
#include "../h/operand.h"
#include "../h/util.h"
#include "../h/assembler.h"
#include "../h/symTable.h"
#include <string>

OneOp::OneOp(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens) : Instruction(name, tokens)
{
    if (operands->size() == 1)
    {
        Operand::Type type = (*operands)[0].getType();
        if (type == Operand::Type::JMP_PC_RELATIVE || (*operands)[0].getType() == Operand::Type::JMP_REG_DIR || (*operands)[0].getType() == Operand::Type::JMP_REG_IND || (*operands)[0].getType() == Operand::Type::JMP_SYMBOL_REG_OFF || (*operands)[0].getType() == Operand::Type::JMP_LITERAL_REG_OFF || (*operands)[0].getType() == Operand::Type::JMP_SYMBOL_DIR || (*operands)[0].getType() == Operand::Type::JMP_LITERAL_IMM)
        {

            std::cout << "Greska, neispravan tip operanda! " << (int)(*operands)[0].getType() << std::endl;
            Assembler::instance().toContinue = false;
        }
        else if (type == Operand::Type::SYMBOL_DIR || type == Operand::Type::SYMBOL_IMM || type == Operand::Type::SYMBOL_REG_OFF || type == Operand::Type::PC_RELATIVE || type == Operand::Type::JMP_SYMBOL_IMM)
        { // check whether is correct type
            std::cout << "Created relocation for " << (*operands)[0].getName() << std::endl;
            std::shared_ptr<Symbol> sym = SymTable::instance().getSymbol((*operands)[0].getSymbolIfExists());
            std::shared_ptr<Section> currSection = Assembler::instance().getCurrentSection();
            int symPosition = Assembler::instance().getLocationCounter() + 2;
            if (sym)
            {
                if (type == Operand::Type::PC_RELATIVE)
                {
                    //proveri da li moze pc relative i sta da se radi tu
                    if (sym->getLocal())
                    {
                        currSection->addRelocation(symPosition, Relocation::Type::R_16_PC, sym->getSection());
                        if (!sym->getDefined())
                        {
                            sym->addPatch(symPosition, true);
                        }
                        opCode.at(3) = sym->getOffset() >> 8;
                        opCode.at(2) = sym->getOffset() & 0xFF;
                    }
                    else
                    {
                        currSection->addRelocation(symPosition, Relocation::Type::R_16_PC, sym->getNumber());
                        if (!sym->getDefined())
                        {
                            sym->addPatch(symPosition, true);
                        }
                        opCode.at(3) = sym->getOffset() >> 8;
                        opCode.at(2) = sym->getOffset() & 0xFF;
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
                        opCode.at(3) = sym->getOffset() >> 8;
                        opCode.at(2) = sym->getOffset() & 0xFF;
                    }
                    else
                    {
                        currSection->addRelocation(symPosition, Relocation::Type::R_16, sym->getNumber());
                        if (!sym->getDefined())
                        {
                            sym->addPatch(symPosition);
                        }
                        opCode.at(3) = 0;
                        opCode.at(2) = 0;
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
    else
    {
        std::cout << "Greska, neispravan broj operanada " << operands->size() << "!" << std::endl;
        Assembler::instance().toContinue = false;
        // ne valja
    }
}