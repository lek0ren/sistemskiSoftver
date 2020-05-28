#pragma once

#include "instruction.h"

class TwoOp : public Instruction
{
public:
    TwoOp(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens);
};