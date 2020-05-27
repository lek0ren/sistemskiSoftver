#pragma once

#include "instruction.h"

class Byte : public Instruction
{
public:
    Byte(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens);
};