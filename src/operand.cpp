#include "../h/operand.h"
#include <regex>
#include "../h/regexes.h"
#include <iostream>
#include "../h/symbol.h"
#include "../h/symTable.h"
#include "../h/assembler.h"

Operand::OperandTypeCode Operand::OperandTypeCode_ = {
    {Type::LITERAL_DIR, 4},
    {Type::LITERAL_IMM, 0},
    {Type::SYMBOL_IMM, 0},
    {Type::REG_DIR, 1},
    {Type::REG_IND, 2},
    {Type::LITERAL_REG_OFF, 3},
    {Type::SYMBOL_REG_OFF, 3},
    {Type::PC_RELATIVE, 3},
    {Type::SYMBOL_DIR, 4},
    {Type::JMP_LITERAL_IMM, 0}, //
    {Type::JMP_SYMBOL_IMM, 0},  //
    {Type::JMP_REG_DIR, 1},     ///
    {Type::JMP_REG_IND, 2},
    {Type::JMP_LITERAL_REG_OFF, 3},
    {Type::JMP_SYMBOL_REG_OFF, 3},
    {Type::JMP_PC_RELATIVE, 3},
    {Type::JMP_LITERAL_DIR, 4},
    {Type::JMP_SYMBOL_DIR, 4},
};

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
        type = Type::JMP_PC_RELATIVE;
        opCode[0] = OperandTypeCode_[type] << 5 | 7 << 1 | horl;
        addSymbolToCode(m[1].str(), m);
    }
    else if (std::regex_match(name, m, reg_jmp_reg_dir))
    {
        type = Type::JMP_REG_DIR;
        extractReg(m);
    }
    else if (std::regex_match(name, m, reg_jmp_reg_ind))
    {
        type = Type::JMP_REG_IND;
        extractReg(m);
    }
    else if (std::regex_match(name, m, reg_literal_dir))
    {
        type = Type::LITERAL_DIR;
        extractLiteral(m);
    }
    else if (std::regex_match(name, m, reg_literal_imm))
    {
        type = Type::LITERAL_IMM;
        extractLiteral(m);
    }
    else if (std::regex_match(name, m, reg_symbol_imm))
    {
        type = Type::SYMBOL_IMM;
        addSymbolToCode(name, m);
    }
    else if (std::regex_match(name, m, reg_symbol_dir))
    {
        type = Type::SYMBOL_DIR;
        addSymbolToCode(name, m);
    }
    else if (std::regex_match(name, m, reg_literal_reg_off))
    {
        type = Type::LITERAL_REG_OFF;
        extractLiteralAndOffset(m);
    }
    else if (std::regex_match(name, m, reg_symbol_reg_off))
    {
        type = Type::SYMBOL_REG_OFF;
        if (m[3].length())
        {
            regNum = stoi(m[3].str());
        }
        else
        {
            regNum = 7;
        }
        opCode[0] = regNum << 1;

        addSymbolToCode(name, m);
    }
    else if (std::regex_match(name, m, reg_pc_rel))
    {
        type = Type::PC_RELATIVE;
        opCode[0] = OperandTypeCode_[type] << 5 | 7 << 1 | horl;

        addSymbolToCode(m[1].str(), m);
    }
    else if (std::regex_match(name, m, reg_reg_dir))
    {
        type = Type::REG_DIR;
        extractReg(m);
    }
    else if (std::regex_match(name, m, reg_reg_ind))
    {
        type = Type::REG_IND;
        extractReg(m);
    }
    else if (std::regex_match(name, m, reg_jmp_literal_dir))
    {
        type = Type::JMP_LITERAL_DIR;
        extractLiteral(m);
    }
    else if (std::regex_match(name, m, reg_jmp_literal_imm))
    {
        type = Type::JMP_LITERAL_IMM;
        extractLiteral(m);
    }
    else if (std::regex_match(name, m, reg_jmp_symbol_imm))
    {
        type = Type::JMP_SYMBOL_IMM;

        addSymbolToCode(name, m);
    }
    else if (std::regex_match(name, m, reg_jmp_symbol_dir))
    {
        type = Type::JMP_SYMBOL_DIR;

        addSymbolToCode(name, m);
    }
    else if (std::regex_match(name, m, reg_jmp_literal_reg_off))
    {
        type = Type::JMP_LITERAL_REG_OFF;
        extractLiteralAndOffset(m);
    }
    else if (std::regex_match(name, m, reg_jmp_symbol_reg_off))
    {
        type = Type::JMP_SYMBOL_REG_OFF;

        addSymbolToCode(name, m);
    }

    opCode[0] |= OperandTypeCode_[type] << 5;
}

unsigned char *Operand::getOpCode()
{
    return opCode;
}

int Operand::getType(int i)
{
    return OperandTypeCode_[type];
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

void Operand::addSymbolToCode(std::string name, std::smatch &m)
{
    std::cout << name << std::endl;
    std::shared_ptr<Symbol> sym = SymTable::instance().getSymbol(name);
    if (!sym)
    {
        this->name = m.str(1);
        sym = std::make_shared<Symbol>(m.str(1), 0, SymTable::instance().getUND()->getNumber());
        if (SymTable::instance().addSymbol(sym))
        {
            sym->setNumber(Assembler::instance().numGen++);
            //relokacija
            opCode[1] = 0x00;
            opCode[2] = 0x00;
        }
    }
    else
    {
        opCode[1] = sym->getOffset() & 0xFF;
        opCode[2] = sym->getOffset() >> 8;
    }
    size = 3;
}