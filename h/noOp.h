#pragma once

#include "instruction.h"

class NoOp : public Instruction
{
public:
    NoOp(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens);
};