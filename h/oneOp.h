#pragma once

#include "instruction.h"

class OneOp : public Instruction
{
public:
    OneOp(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens);
};