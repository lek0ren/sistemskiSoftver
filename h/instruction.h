#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Token.h"
#include "operand.h"
#include <map>

class Instruction
{
protected:
    std::vector<unsigned char> opCode;
    int size;
    int opSize;
    int instCode;
    typedef std::map<std::string, int> InstructionOpNum;
    typedef std::map<std::string, char> InstructionCode;
    static InstructionOpNum InstructionOpNum_;
    static InstructionCode InstructionCode_;
    int numOfOp;
    std::shared_ptr<std::vector<Operand>> operands;

public:
    Instruction(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens);

    std::vector<unsigned char> getOpCode();

    int getSize();
};