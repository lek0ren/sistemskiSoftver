#include "../h/instruction.h"
#include <map>

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

Instruction::Instruction(std::string name, int num, std::shared_ptr<std::vector<Token>> tokens)
{
    numOfOp = num;
    size = InstructionCode_[name];
}