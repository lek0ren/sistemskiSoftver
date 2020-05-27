#pragma once

#include "instruction.h"

class Skip : public Instruction
{
public:
    Skip(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens);
};