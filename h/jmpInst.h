#pragma once

#include "instruction.h"

class JmpInst : public Instruction
{
public:
    JmpInst(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens);
};