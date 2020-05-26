#include "../h/operand.h"
#include <regex>
#include "../h/regexes.h"
#include <iostream>
#include "../h/symbol.h"
#include "../h/symTable.h"
#include "../h/assembler.h"

Operand::Operand(std::string name)
{
    std::smatch m;
    this->name = name;
    size = 1;

    int regNum;
    int horl = 0;
    opCode[0] = 0;
    opCode[1] = 0;
    opCode[2] = 0;

    if (std::regex_match(name, m, reg_jmp_pc_rel))
    {
        type = JMP_PC_RELATIVE;
        opCode[0] = type << 5 | 7 << 1 | horl;
        //relokacija
        opCode[1] = 0x12;
        opCode[2] = 0x12;
        size = 3;
    }
    else if (std::regex_match(name, m, reg_jmp_reg_dir))
    {
        type = JMP_REG_DIR;
        extractReg(m);
    }
    else if (std::regex_match(name, m, reg_jmp_reg_ind))
    {
        type = JMP_REG_IND;
        extractReg(m);
    }
    else if (std::regex_match(name, m, reg_literal_dir))
    {
        type = LITERAL_DIR;
        extractLiteral(m);
    }
    else if (std::regex_match(name, m, reg_literal_imm))
    {
        type = LITERAL_IMM;
        extractLiteral(m);
    }
    else if (std::regex_match(name, m, reg_symbol_imm))
    {
        type = SYMBOL_IMM;
        std::cout << "usao\n";
        std::shared_ptr<Symbol> sym = SymTable::instance().getSymbol(m.str(1));
        if (!sym)
        {
            sym = std::make_shared<Symbol>(m.str(1), Assembler::instance().getLocationCounter(), SymTable::instance().getUND()->getNumber());
            SymTable::instance().addSymbol(sym);
        }
        std::cout << sym << std::endl;
    }
    else if (std::regex_match(name, m, reg_symbol_dir))
    {
        type = SYMBOL_DIR;
        std::cout << "usao 2\n";
        std::shared_ptr<Symbol> sym = SymTable::instance().getSymbol(name);
        if (!sym)
        {
            sym = std::make_shared<Symbol>(m.str(1), Assembler::instance().getLocationCounter(), SymTable::instance().getUND()->getNumber());
            if (SymTable::instance().addSymbol(sym))
            {
                sym->setNumber(Assembler::instance().numGen++);
            }
        }
        std::cout << *sym << std::endl;
    }
    else if (std::regex_match(name, m, reg_literal_reg_off))
    {
        type = LITERAL_REG_OFF;
        extractLiteralAndOffset(m);
    }
    else if (std::regex_match(name, m, reg_symbol_reg_off))
    {
        type = SYMBOL_REG_OFF;
        if (m[3].length())
        {
            regNum = stoi(m[3].str());
        }
        else
        {
            regNum = 7;
        }
        opCode[0] = regNum << 1;
        size = 3;

        //relokacija
        opCode[1] = 0x12;
        opCode[2] = 0x12;
    }
    else if (std::regex_match(name, m, reg_pc_rel))
    {
        type = PC_RELATIVE;
        opCode[0] = type << 5 | 7 << 1 | horl;
        //relokacija
        opCode[1] = 0x12;
        opCode[2] = 0x12;
        size = 3;
    }
    else if (std::regex_match(name, m, reg_reg_dir))
    {
        type = REG_DIR;
        extractReg(m);
    }
    else if (std::regex_match(name, m, reg_reg_ind))
    {
        type = REG_IND;
        extractReg(m);
    }
    else if (std::regex_match(name, m, reg_jmp_literal_dir))
    {
        type = JMP_LITERAL_DIR;
        extractLiteral(m);
    }
    else if (std::regex_match(name, m, reg_jmp_literal_imm))
    {
        type = JMP_LITERAL_IMM;
        extractLiteral(m);
    }
    else if (std::regex_match(name, m, reg_jmp_symbol_imm))
    {
        type = JMP_SYMBOL_IMM;
        //relokacija
    }
    else if (std::regex_match(name, m, reg_jmp_symbol_dir))
    {
        type = JMP_SYMBOL_DIR;
        //relokacija
    }
    else if (std::regex_match(name, m, reg_jmp_literal_reg_off))
    {
        type = JMP_LITERAL_REG_OFF;
        extractLiteralAndOffset(m);
    }
    else if (std::regex_match(name, m, reg_jmp_symbol_reg_off))
    {
        type = JMP_SYMBOL_REG_OFF;

        //relokacija
    }

    opCode[0] |= type << 5;
}

unsigned char *Operand::getOpCode()
{
    return opCode;
}

Operand::Type Operand::getType()
{
    return type;
}

int Operand::getSize()
{
    return size;
}

std::string Operand::getName()
{
    return name;
}

void Operand::extractLiteralAndOffset(std::smatch &m)
{
    int regNum = 0;
    extractLiteral(m);
    size = 3;
    if (m[3].length())
    {
        regNum = stoi(m[3].str());
    }
    else
    {
        regNum = 7;
    }
    opCode[0] = regNum << 1;
}
void Operand::extractLiteral(std::smatch &m)
{
    if (std::stoi(m[1].str()) > 255)
    {
        size = 3;
        opCode[2] = std::stoi(m[1].str()) >> 8;
    }
    else
    {
        size = 2;
    }
    opCode[1] = std::stoi(m[1].str()) & 0xff;
}
void Operand::extractSymbolAndOffset(std::smatch &m)
{
}
void Operand::extractSymbol(std::smatch &m)
{
}
void Operand::extractReg(std::smatch &m)
{
    int regNum, horl = 0;
    if (m[2].length())
    {
        regNum = stoi(m[2].str());
    }
    else
    {
        regNum = 7;
    }

    if (m[3].length())
    {
        if (m[3].str() == "h")
        {
            horl = 1;
        }
    }
    opCode[0] = regNum << 1 | horl;
}