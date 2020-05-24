#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Token.h"
#include <map>

class Instruction
{
protected:
    std::string opCode;
    int size;
    typedef std::map<std::string, int> InstructionOpNum;
    typedef std::map<std::string, char> InstructionCode;
    static InstructionOpNum InstructionOpNum_;
    static InstructionCode InstructionCode_;
    int numOfOp;

public:
    Instruction(std::string name, int num, std::shared_ptr<std::vector<Token>> tokens);

    virtual std::string getOpCode() = 0;

    int getSize();
};