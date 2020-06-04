#include "../h/instruction.h"
#include "../h/regexes.h"
#include "../h/Token.h"
#include <map>
#include <regex>
#include <iostream>
#include "../h/util.h"
#include "../h/symTable.h"
#include "../h/symbol.h"
#include "../h/assembler.h"

Instruction::InstructionOpNum Instruction::InstructionOpNum_ = {
    {"halt", 0},
    {"iret", 0},
    {"ret", 0},
    {"int", 1},
    {"call", 1},
    {"jmp", 1},
    {"jeq", 1},
    {"jne", 1},
    {"jgt", 1},
    {"push", 1},
    {"pop", 1},
    {"xchg", 2},
    {"mov", 2},
    {"add", 2},
    {"sub", 2},
    {"mul", 2},
    {"div", 2},
    {"cmp", 2},
    {"not", 2},
    {"and", 2},
    {"or", 2},
    {"xor", 2},
    {"test", 2},
    {"shl", 2},
    {"shr", 2}};

Instruction::InstructionCode Instruction::InstructionCode_ = {
    {"halt", 0},
    {"iret", 1},
    {"ret", 2},
    {"int", 3},
    {"call", 4},
    {"jmp", 5},
    {"jeq", 6},
    {"jne", 7},
    {"jgt", 8},
    {"push", 9},
    {"pop", 10},
    {"xchg", 11},
    {"mov", 12},
    {"add", 13},
    {"sub", 14},
    {"mul", 15},
    {"div", 16},
    {"cmp", 17},
    {"not", 18},
    {"and", 19},
    {"or", 20},
    {"xor", 21},
    {"test", 22},
    {"shl", 23},
    {"shr", 24}};

int Instruction::getSize()
{
    return size;
}

std::vector<unsigned char> Instruction::getOpCode()
{
    return opCode;
}

Instruction::Instruction(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens)
{
    std::smatch match_name;
    opSize = 1;
    size = 1;
    opCode = std::vector<unsigned char>();

    if (std::regex_match(name, match_name, reg_oneOpInstr) || std::regex_match(name, match_name, reg_twoOpInstr))
    {
        name = match_name[1].str();
        if (match_name[2].str() == "b")
            opSize = 0;
    }

    instCode = InstructionCode_[name] << 3;
    numOfOp = InstructionOpNum_[name];
    instCode |= opSize << 2;
    opCode.push_back(instCode);
    std::cout << "instruction :  " << instCode << std::endl;
    operands = std::make_shared<std::vector<Operand>>();

    if (name != ".byte" && name != ".word" && name != ".skip")
    {
        if (tokens->size() == numOfOp)
        {
            for (auto &tok : *tokens)
            {
                std::shared_ptr<Operand> op = std::make_shared<Operand>(tok->getToken());
                operands->push_back(*op);
                /*if (op->getType() == Operand::Type::SYMBOL_DIR || op->getType() == Operand::Type::SYMBOL_IMM || op->getType() == Operand::Type::SYMBOL_REG_OFF || op->getType() == Operand::Type::JMP_SYMBOL_DIR || op->getType() == Operand::Type::JMP_SYMBOL_IMM || op->getType() == Operand::Type::JMP_SYMBOL_REG_OFF)
                {
                    std::shared_ptr<Symbol> sym = SymTable::instance().getSymbol(op->getName());
                    std::shared_ptr<Section> currSection = Assembler::instance().getCurrentSection();
                    int symPosition = Assembler::instance().getLocationCounter() + size + 1;

                    if (!sym->getDefined())
                    {
                        sym->addPatch(symPosition); // +1 jer prvo ide kod adresiranja
                    }
                }*/
                size += op->getSize();
            }
        }
        else
        {
            //greska
        }
    }
    else
    {
        numOfOp = 0;
        size = 0;
        opCode.clear();
        for (auto &tok : *tokens)
        {
            Operand op = Operand(tok->getToken());
            operands->push_back(op);
            numOfOp++;
            //prosiri operand da moze da prepozna + i -
        }
    }

    for (auto op : *operands)
    {
        {
            std::cout << "Op name = " << op.getName() << "\t"
                      << "Op type = " << op.getType(1) << "\t"
                      << "Op size = " << op.getSize() << "\t"
                      << "Op code = ";
            auto flags = std::cout.flags();
            for (int i = 0; i < op.getSize(); i++)
            {
                opCode.push_back(op.getOpCode()[i]);
                std::cout << std::hex << +op.getOpCode()[i];
                std::cout << "\t";
            };
            std::cout.flags(flags);
            std::cout << std::endl;
        }
    }
}