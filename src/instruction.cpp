#include "../h/instruction.h"
#include "../h/regexes.h"
#include "../h/Token.h"
#include <map>
#include <regex>
#include <iostream>

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

Instruction::Instruction(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens)
{
    std::smatch match_name;
    opSize = 2;

    if (std::regex_match(name, match_name, reg_oneOpInstr) || std::regex_match(name, match_name, reg_twoOpInstr))
    {
        name = match_name[1].str();
        if (match_name[2].str() == "b")
            opSize = 1;
    }

    size = InstructionCode_[name];
    numOfOp = InstructionOpNum_[name];

    /*if (std::regex_match(name, match_name, reg_oneOpInstr))
    {
        if (match_name[2].str() == "b")
            opSize = 1;
    }

    if (std::regex_match(name, match_name, reg_twoOpInstr))
    {
        if (match_name[2].str() == "b")
            opSize = 1;
    }*/

    operands = std::make_shared<std::vector<Operand>>();

    if (tokens->size() == numOfOp)
    {
        for (auto &tok : *tokens)
        {
            Operand op = Operand(tok->getToken());
            operands->push_back(op);
        }
    }
    else
    {
        //greska
    }

    for (auto op : *operands)
    {
        {
            std::cout << "Op name = " << op.getName() << "\t"
                      << "Op type = " << op.getType() << "\t"
                      << "Op size = " << op.getSize() << "\t"
                      << "Op code = ";
            auto flags = std::cout.flags();
            for (int i = 0; i < op.getSize(); i++)
            {
                std::cout << std::hex << +op.getOpCode()[i];
                std::cout << "\t";
            };
            std::cout.flags(flags);
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}